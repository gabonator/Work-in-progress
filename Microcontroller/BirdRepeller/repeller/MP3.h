/*****************************************************************************/
/**
	@file    	MP3.h
	@author  	ELECHOUSE
	@version 	V0.2
	@brief      head file for Arduino MP3 Shield
	
	@section  HISTORY
	V0.2	2012-12-13	Add software serial support.
	
	V0.1	2012-08-02	Initial version.
	
	Copyright (c) 2012 www.elechouse.com  All right reserved.
*/
/*****************************************************************************/

#ifndef __MP3_H
#define __MP3_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "wiring_private.h"
#include "SoftwareSerial.h"
#ifndef __TYPE_REDEFINE
#define __TYPE_REDEFINE
typedef uint8_t u8;
typedef int8_t  s8;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
#endif

/** Serial port definition */
#define COM         Serial

typedef enum{
	MP3_HARDWARE_SERIAL,
	MP3_SOFTWARE_SERIAL
}serial_type_t;

class MP3{
public:
    /** constructor */
    MP3();
    /** begin function, Arduino style */
    void begin(serial_type_t st=MP3_HARDWARE_SERIAL );
    /** MP3 shield basic send command function */
    void send_cmd(u8 *cmd);
    /** play music in SD, and choose SD mode */
    void play_sd(u16 num);
    /** play music in USB, and choose USB mode */
    void play_usb_disk(u16 num);
    /** play music in SPI FLASH */
    void play_spi_flash(u16 num);
    /** play next music */
    void next();
    /** play previous music */
    void previous();
    /** pause when play, play when pause */
    void pause();
    /** stop playing */
    void stop();
    /** set volume */
    void volume(u8 vol);
    /** set mode, Use SINGLE, REPEAT, CYCLE or RANDOM as parameter */
    void set_mode(u8 mode);
    enum {SINGLE=0, REPEAT=1, CYCLE=2, RANDOM=3};
    /** copy files from SD to SPI FLASH */
    void sd_to_flash(void);
    /** copy files from USB to SPI FLASH */
    void usb_to_flash(void);
private:
    /** command buffer */
    enum {CMD_BUF_LEN = 10};
    u8 cmd_buf[CMD_BUF_LEN];
	serial_type_t serial_type;
};

#endif
