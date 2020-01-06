//
//  main.cpp
//  EtherdreamBridge
//
//  Created by Gabriel Valky on 1/6/20.
//  Copyright © 2020 Gabriel Valky. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "etherdream.h"
#include "websocket/websock.h"
#include <csignal>

class Etherdream
{
	etherdream *mDevice{nullptr};
	uint32_t mSamplingFrequency{2000};
	
public:
	bool Connect(const std::string& ip)
	{
		etherdream_lib_start();
		mDevice = etherdream_ip(ip.c_str());
		
		if (etherdream_connect(mDevice) < 0)
			return false;
		
		return true;
	}
	
	bool Transfer(const std::vector<etherdream_point>& points)
	{
		etherdream_wait_for_ready(mDevice);
		return etherdream_write(mDevice, &points[0], (int)points.size(), mSamplingFrequency, -1) == 0;
	}
};

Etherdream laser;

class Websocket
{
	std::vector<etherdream_point> mPoints;
	libwebsock_context *mCtx{nullptr};

public:
	Websocket()
	{
		mPoints.reserve(10000);
	}
	
protected:
	void OnMessage(const std::string& msg)
	{
		mPoints.clear();
		etherdream_point point;
		memset(&point, 0, sizeof(point));

		//std::cout << msg;
		const char* raw = msg.c_str();
		const char* pos = raw+1;
		while ((pos = strstr(pos, "[")) != nullptr)
		{
			int x, y, c;
			if (sscanf(pos+1, "%d,%d,%d", &x, &y, &c) != 3)
				raise(SIGABRT);
			
			//std::cout << x << "," << y << "," << c << "; ";

			etherdream_point point;
			point.x = x;
			point.y = y;
			point.r = (c & 1) ? 0xffff : 0;
			point.g = (c & 2) ? 0xffff : 0;
			point.b = (c & 4) ? 0xffff : 0;
			mPoints.push_back(point);
			pos++;
		}
		laser.Transfer(mPoints);
		std::cout << "ws: transfered " << mPoints.size() << " points" << std::endl;
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
			self->OnConnect();
			return 0;
		};
		mCtx->onclose = [](libwebsock_client_state *state)
		{
			self->OnClose();
			return 0;
		};
		return true;
	}
	
	void Wait()
	{
	  libwebsock_wait(mCtx);
	}
};

Websocket websocket;

int main(int argc, const char * argv[]) {
	std::cout << "Hello, World!\n";
	laser.Connect("192.168.1.109");
	websocket.Create(6699);
	while (1)
		websocket.Wait();
	//_main();
	return 0;
}
