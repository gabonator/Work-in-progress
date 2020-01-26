// AmScope MT1000 camera (Anchor Chips Inc. 10M USBCam) websocket bridge application
// Reverse engineered camera driver using Wireshark by Gabriel Valky
// libusb code based on Christophe Augier CDC-ACM USB example

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <cassert>
#include <libusb-1.0/libusb.h>

#include <thread>
#include "websocket/websock.h"
#include <string>
#include <csignal>
#include <mutex>
#include <vector>
#include <iostream>

using namespace std;

class Camera
{
	libusb_device_handle *devh{NULL};
	std::thread mThread;
	std::atomic_bool mRunning{false};
	std::atomic<uint8_t*> mCurrentBuffer;
	std::atomic<int> mCurrentSize;
	std::mutex mBufferAccess;

public:
	bool Start()
	{
		mRunning = true;
		mThread = std::thread(&Camera::Thread, this);
		return true;
	}
	
	void Stop()
	{
		if (mRunning.exchange(false))
		{
			mThread.join();
			Release();
		}
	}

	void Release()
	{
		libusb_release_interface(devh, 0);
		
		if (devh)
			libusb_close(devh);
		libusb_exit(NULL);
	}
	
	bool Initialize()
	{
		int rc;

		rc = libusb_init(NULL);
		if (rc < 0) {
			fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(rc));
			return false;
		}

		//libusb_set_debug(NULL, 3);

		devh = libusb_open_device_with_vid_pid(NULL, 0x0547, 0x92a0);
		if (!devh) {
			fprintf(stderr, "Error finding USB device\n");
			return false;
		}

		rc = libusb_claim_interface(devh, 0);
		if (rc < 0) {
			fprintf(stderr, "Error claiming interface: %s\n",
					libusb_error_name(rc));
			return false;
		}
		
		configureCamera();
		return true;
	}

	bool GetBuffer(std::vector<uint8_t>& buffer)
	{
		std::lock_guard<std::mutex> guard(mBufferAccess);
		if (!mCurrentBuffer)
			return false;
		
		buffer.resize(mCurrentSize);
		memcpy(&buffer[0], mCurrentBuffer, mCurrentSize);
		mCurrentBuffer = nullptr;
		return true;
	}

	void Control(int index, int value)
	{
		_recv(0xc0, 10, value, index, 1, 0x08);
	}

private:
	int readCameraBuffer(unsigned char * data, int size)
	{
		data[0] = 0;
		int actual_length;
		int rc = libusb_bulk_transfer(devh, 0x82, data, size, &actual_length, 1000);
		if (rc == LIBUSB_ERROR_TIMEOUT) {
			printf("timeout (%d)\n", actual_length);
			return rc;
		} else if (rc < 0) {
			fprintf(stderr, "Error while waiting for char\n");
			return rc;
		}

		return actual_length;
	}

	void _recv(int bmRequestType, int bRequest, int wValue, int wIndex, int wLength, int result)
	{
		uint8_t buffer[32] = {0};
		int rc = libusb_control_transfer(devh, bmRequestType, bRequest, wValue, wIndex, buffer, wLength, 1000);
		if (rc<0)
		{
			fprintf(stdout, "control error\n");
			return;
		}
		
		int val = 0;
		if (wLength==3)
		  val = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
		if (wLength==2)
		  val = (buffer[0] << 8) | buffer[1];
		if (wLength==1)
		  val = buffer[0];
		if (result == -1)
			return;
		if (val != result)
			fprintf(stdout, "control %d mismatch %x = %x\n", wIndex, val, result);
	}

	void _send(uint8_t request_type, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, int len)
	{
		int rc = libusb_control_transfer(devh, request_type, bRequest, wValue, wIndex, NULL, 0, 0);
		if (rc < 0) {
			fprintf(stderr, "Error during control transfer: %s\n",
					libusb_error_name(rc));
		}
	}

	void configureCamera()
	{
		_send(0x40, 2, 1, 15, 0);
		_recv(0xc0, 17, 0, 0, 3,  0xc24708);
		_recv(0xc0, 17, 0, 2, 3,  0x05a008);
		_recv(0xc0, 17, 0, 4, 3,  0x920008);
		_recv(0xc0, 17, 0, 6, 3,  0x000008);
		_recv(0xc0, 17, 0, 8, 3,  0x000608);
		for (int t = 10; t<=158; t+=2)
			_recv(0xc0, 17, 0, t, 3,  -1);
		_recv(0xc0, 10, 0x17a0, 5792, 1,  0x08);
		_recv(0xc0, 10, 0x16a0, 5795, 1,  0x07);
		_recv(0xc0, 10, 0x16a0, 5796, 1,  0x08);
		_send(0x40, 9, 0, 0, 0);
		_recv(0xc0, 10, 0x16a0, 5796, 1,  0x08);
		_recv(0xc0, 10, 0x1580, 5348, 1,  0x08);
		_recv(0xc0, 10, 0x1bbd, 5352, 1,  0x08);
		_recv(0xc0, 10, 0x1630, 5350, 1,  0x08);
		_recv(0xc0, 10, 0x1ead, 5354, 1,  0x08);
		_recv(0xc0, 10, 0x1563, 10208, 1,  0x08);
		_recv(0xc0, 10, 0x17a0, 5024, 1,  0x08);
		_recv(0xc0, 10, 0x17b0, 5028, 1,  0x08);
		_recv(0xc0, 10, 0x12a0, 5356, 1,  0x08);
		_recv(0xc0, 10, 0x1460, 5358, 1,  0x08);
		_recv(0xc0, 10, 0x13f1, 5344, 1,  0x08);
		_recv(0xc0, 10, 0x1cf4, 5346, 1,  0x08);
		_recv(0xc0, 10, 0x17a0, 5796, 1,  0x08);
		_recv(0xc0, 10, 0x17a1, 5796, 1,  0x08);
		_recv(0xc0, 10, 0x17a0, 5792, 1,  0x08);
		_recv(0xc0, 10, 0x17a2, 5284, 1,  0x08);
		_recv(0xc0, 10, 0x1788, 5286, 1,  0x08);
		_recv(0xc0, 10, 0x17a5, 5280, 1,  0x08);
		_recv(0xc0, 10, 0x17a1, 5282, 1,  0x08);
		_recv(0xc0, 10, 0x17aa, 5288, 1,  0x08);
		_recv(0xc0, 10, 0x17a2, 5290, 1,  0x08);
		_recv(0xc0, 10, 0x8778, 10170, 1,  0x08);
		_recv(0xc0, 10, 0x17a0, 5796, 1,  0x08);
		_recv(0xc0, 10, 0x16a0, 5792, 1,  0x08);
		_recv(0xc0, 10, 0x1416, 10162, 1,  0x08);
		_send(0x40, 9, 0x1069, 1, 0);
		_recv(0xc0, 17, 0, 9408, 3,  0xaa2208);
		_recv(0xc0, 17, 0, 9420, 3,  0x020208);
		_recv(0xc0, 17, 0, 9422, 3,  0x001008);
		for (int t = 10272; t<=10334; t+=2)
			_recv(0xc0, 17, 0, t, 3,  -1);
		_send(0x40, 3, 1, 14, 0);
		
		
		//_recv(0xc0, 10, 0x1416, 10162, 1,  0x08);
		//_send(0x40, 9, 0x1069, 1, 0);
	}

	void Thread()
	{
		constexpr int bufferSize = 2000000;
		uint8_t* buf1 = new uint8_t[bufferSize];
		uint8_t* buf2 = new uint8_t[bufferSize];
		mCurrentBuffer = nullptr;

		bool first = true;
		bool initialized = false;
		int timeouts = 0;

		int len;
		
		while(mRunning)
		{
			if (timeouts > 20)
			{
				timeouts = 0;
				initialized = false;
			}
			
			if (!initialized)
			{
				if (first)
					first = false;
				else
					usleep(1000*1000*1);
				fprintf(stdout, "Connecting... ");
				initialized = Initialize();
				if (initialized)
					fprintf(stdout, "Ok!\n");
				else
					fprintf(stdout, "Error!\n");
				continue;
			}
			uint8_t* buf = buf1;
			
			{
				std::lock_guard<std::mutex> guard(mBufferAccess);
				len = readCameraBuffer(buf, bufferSize);
			}
			if (len > 0)
			{
				fprintf(stdout, "Received %d bytes: %02x %02x %02x %02x %02x %02x...\n", len,
						buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

				std::lock_guard<std::mutex> guard(mBufferAccess);
				mCurrentBuffer = buf;
				mCurrentSize = len;
				timeouts = 0;
			}
			else if (len == LIBUSB_ERROR_TIMEOUT)
			{
				fprintf(stdout, "Timeout\n");

				std::lock_guard<std::mutex> guard(mBufferAccess);
				mCurrentBuffer = nullptr;
				mCurrentSize = 0;
				timeouts++;
			} else //if (len == LIBUSB_ERROR_IO)
			{
				initialized = false;
			}

			usleep(3000);

			buf = buf2;
			{
				std::lock_guard<std::mutex> guard(mBufferAccess);
				len = readCameraBuffer(buf, bufferSize);
			}
			if (len > 0)
			{
				fprintf(stdout, "Received %d bytes: %02x %02x %02x %02x %02x %02x...\n", len,
						buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

				std::lock_guard<std::mutex> guard(mBufferAccess);
				mCurrentBuffer = buf;
				mCurrentSize = len;
				timeouts = 0;
			}
			else if (len == LIBUSB_ERROR_TIMEOUT)
			{
				fprintf(stdout, "Timeout\n");

				std::lock_guard<std::mutex> guard(mBufferAccess);
				mCurrentBuffer = nullptr;
				mCurrentSize = 0;
				timeouts++;
			} else //if (len == LIBUSB_ERROR_IO)
			{
				initialized = false;
			}

			usleep(3000);
		}
		mCurrentBuffer = nullptr;
		
		delete[] buf1;
		delete[] buf2;
	}
};

class Websocket
{
	libwebsock_context *mCtx{nullptr};
	libwebsock_client_state* mCurrent{nullptr};
	std::mutex mDataMutex;
	std::string mData;
	
public:
	std::string GetMessage()
	{
		std::lock_guard<std::mutex> guard(mDataMutex);
		return mData;
	}

protected:
	void OnMessage(const std::string& msg)
	{
		std::lock_guard<std::mutex> guard(mDataMutex);
		mData = msg;
	}
	
	
	void OnConnect()
	{
		std::cout << "websocket connected" << std::endl;
	}
	
	void OnClose()
	{
		std::cout << "websocket closed"  << std::endl;
	}
	
public:
	bool Create(int port)
	{
		char strPort[32];
		sprintf(strPort, "%d", port);
		
		mCtx = libwebsock_init();
		if(mCtx == NULL) {
		  fprintf(stderr, "Error during libwebsock_init.\n");
			return false;
		}
		
		libwebsock_bind(mCtx, (char*)"0.0.0.0", strPort);
		static Websocket* self = this;
		mCtx->onmessage = [](libwebsock_client_state *state, libwebsock_message *msg)
		{
			self->OnMessage(std::string(msg->payload));
			return 0;
		};
		mCtx->onopen = [](libwebsock_client_state *state)
		{
			self->mCurrent = state;
			self->OnConnect();
			return 0;
		};
		mCtx->onclose = [](libwebsock_client_state *state)
		{
			if (state == self->mCurrent)
				self->mCurrent = nullptr;
			self->OnClose();
			return 0;
		};
		return true;
	}

	void Send(std::vector<uint8_t>& buffer)
	{
		if (mCurrent)
			libwebsock_send_binary(mCurrent, (char*)&buffer[0], (int)buffer.size());
	}

	void Wait()
	{
	  libwebsock_wait(mCtx);
	}
};

int main()
{
	std::vector<uint8_t>data;
	Websocket websocket;
	Camera camera;
	camera.Start();
	websocket.Create(6699);

	std::thread ws([&](){
//		while (1)
			websocket.Wait();
	});

	while (1)
	{
		std::string msg = websocket.GetMessage();

		if (!msg.empty())
		{
			int adr, val;
			if (sscanf(msg.c_str(), "%d,%d", &adr, &val) == 2)
			{
				camera.Control(adr, val);
			}
		}
		usleep(20000);
		if (camera.GetBuffer(data))
			websocket.Send(data);
		
	}
	camera.Stop();
	return 0;
}
