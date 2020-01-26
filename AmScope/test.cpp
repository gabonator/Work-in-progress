// AmScope MT1000 camera (Anchor Chips Inc. 10M USBCam) test application
// Reverse engineered camera driver using Wireshark by Gabriel Valky
// libusb code based on Christophe Augier CDC-ACM USB example

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <cassert>
#include <libusb-1.0/libusb.h>

static struct libusb_device_handle *devh = NULL;

int readCameraBuffer(unsigned char * data, int size)
{
	data[0] = 0;
    int actual_length;
    int rc = libusb_bulk_transfer(devh, 0x82, data, size, &actual_length, 1000);
    if (rc == LIBUSB_ERROR_TIMEOUT) {
        printf("timeout (%d)\n", actual_length);
        return -1;
    } else if (rc < 0) {
        fprintf(stderr, "Error while waiting for char\n");
        return -1;
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
	
	
	_recv(0xc0, 10, 0x1416, 10162, 1,  0x08);
	_send(0x40, 9, 0x1069, 1, 0);
}

#define EXIT     {if (devh)		libusb_close(devh); libusb_exit(NULL); return rc;}

int main(int argc, char **argv)
{
    int rc;

    rc = libusb_init(NULL);
    if (rc < 0) {
        fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(rc));
        exit(1);
    }

	libusb_set_debug(NULL, 3);

    devh = libusb_open_device_with_vid_pid(NULL, 0x0547, 0x92a0);
    if (!devh) {
        fprintf(stderr, "Error finding USB device\n");
        EXIT;
    }

	rc = libusb_claim_interface(devh, 0);
	if (rc < 0) {
		fprintf(stderr, "Error claiming interface: %s\n",
				libusb_error_name(rc));
		EXIT;
	}
	
	configureCamera();

	// 640x640x3=1228800
    unsigned char buf[327680*8+1];
    int len;
    
    while(1)
	{
        len = readCameraBuffer(buf, 327680*8);
		if (len > 0)
			fprintf(stdout, "Received %d bytes: %02x %02x %02x %02x %02x %02x...\n", len,
					buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
		else
			 fprintf(stdout, "Timeout\n");

		usleep(3000);
    }

    libusb_release_interface(devh, 0);

	EXIT;
}