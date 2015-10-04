/*****************************************************************************/
/**
	@file    	MP3.cpp
	@author  	ELECHOUSE
	@version 	V0.2
	@brief      head file for Arduino MP3 Shield
	
	@section  HISTORY
	V0.2	2012-12-13	Add software serial support.
	
	V0.1	2012-08-02	Initial version.
	
	Copyright (c) 2012 www.elechouse.com  All right reserved.
*/
/*****************************************************************************/
#include "MP3.h"

SoftwareSerial COM_SOFT(7, 8);

MP3::MP3()
{
	serial_type_t st=MP3_HARDWARE_SERIAL;
}

void MP3::begin(serial_type_t st)
{
	delay(3000);
	serial_type = st;
	if(serial_type == MP3_HARDWARE_SERIAL){
		COM.begin(9600);
	}else{
		COM_SOFT.begin(9600);
	}
}

void MP3::send_cmd(u8 *cmd)
{
    u8 i;
    u8 length;
    length = cmd[1]+2;
    if(length>CMD_BUF_LEN){
        return;
    }
    cmd[0] = 0x7E;
    cmd[length-1] = 0x7E;
    for(i=0; i<length; i++){
		if(serial_type == MP3_HARDWARE_SERIAL){
			COM.write(cmd[i]);
		}else{
			COM_SOFT.write(cmd[i]);
		}
    }
}

void MP3::next()
{
    cmd_buf[1]=0x02;
    cmd_buf[2]=0xA5;
    send_cmd(cmd_buf);
}

void MP3::pause()
{
    cmd_buf[1]=0x02;
    cmd_buf[2]=0xA3;
    send_cmd(cmd_buf);
}

void MP3::stop()
{
    cmd_buf[1]=0x02;
    cmd_buf[2]=0xA4;
    send_cmd(cmd_buf);
}

void MP3::play_sd(u16 num)
{
    cmd_buf[1]=0x04;
    cmd_buf[2]=0xA0;
    cmd_buf[3]=(u8)(num>>8);
    cmd_buf[4]=(u8)num;
    send_cmd(cmd_buf);
}

void MP3::play_spi_flash(u16 num)
{
    cmd_buf[1]=0x04;
    cmd_buf[2]=0xA1;
    cmd_buf[3]=(u8)(num>>8);
    cmd_buf[4]=(u8)num;
    send_cmd(cmd_buf);
}

void MP3::play_usb_disk(u16 num)
{
    cmd_buf[1]=0x04;
    cmd_buf[2]=0xA2;
    cmd_buf[3]=(u8)(num>>8);
    cmd_buf[4]=(u8)num;
    send_cmd(cmd_buf);
}

void MP3::volume(u8 vol)
{
    cmd_buf[1]=0x03;
    cmd_buf[2]=0xA7;
    cmd_buf[3]=vol&0x01F;
    send_cmd(cmd_buf);
}

void MP3::set_mode(u8 mode)
{
    cmd_buf[1]=0x03;
    cmd_buf[2]=0xA9;
    cmd_buf[3]=mode;
    send_cmd(cmd_buf);
}

void MP3::sd_to_flash(void)
{
    cmd_buf[1]=0x03;
    cmd_buf[2]=0xAA;
    cmd_buf[3]=0;
    send_cmd(cmd_buf);
}

void MP3::usb_to_flash(void)
{
    cmd_buf[1]=0x03;
    cmd_buf[2]=0xAB;
    cmd_buf[3]=0;
    send_cmd(cmd_buf);
}
