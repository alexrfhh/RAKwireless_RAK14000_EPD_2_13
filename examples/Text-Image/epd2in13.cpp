/*****************************************************************************
* | File      	:   epd2in13_V3.cpp
* | Author      :   Waveshare team
* | Function    :   2.13inch e-paper V3
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-11-01
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include <stdlib.h>
#include "epd2in13.h"

unsigned char lut_full_update[] = {
	0x80, 0x4A, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x4A, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x4A, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x40, 0x4A, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x02, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x22, 0x17, 0x41, 0x00, 0x32, 0x36};

unsigned char lut_partial_update[] = {
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x22, 0x17, 0x41, 0x00, 0x32, 0x36};

EPD_213_BW::~EPD_213_BW(){};

/******************************************************************************
function :	Pin definition
parameter:
******************************************************************************/
EPD_213_BW::EPD_213_BW()
{
	reset_pin = RST_PIN;
	dc_pin = DC_PIN;
	cs_pin = CS_PIN;
	busy_pin = BUSY_PIN;
	width = 122;
	height = 250;
};

/******************************************************************************
function :	send command
parameter:
	 command : Command register
******************************************************************************/
void EPD_213_BW::SendCommand(unsigned char command)
{
	DigitalWrite(dc_pin, LOW);
	SpiTransfer(command);
}

/******************************************************************************
function :	send data
parameter:
	Data : Write data
******************************************************************************/
void EPD_213_BW::SendData(unsigned char data)
{
	DigitalWrite(dc_pin, HIGH);
	SpiTransfer(data);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void EPD_213_BW::WaitUntilIdle(void)
{
	while (1)
	{ // LOW: idle, HIGH: busy
		if (DigitalRead(busy_pin) == 0)
			break;
		DelayMs(10);
	}
}

/******************************************************************************
function :	Setting the display window
parameter:
	Xstart : X-axis starting position
	Ystart : Y-axis starting position
	Xend : End position of X-axis
	Yend : End position of Y-axis
******************************************************************************/
void EPD_213_BW::SetWindows(unsigned char Xstart, unsigned char Ystart, unsigned char Xend, unsigned char Yend)
{
	SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
	SendData((Xstart >> 3) & 0xFF);
	SendData((Xend >> 3) & 0xFF);

	SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
	SendData(Ystart & 0xFF);
	SendData((Ystart >> 8) & 0xFF);
	SendData(Yend & 0xFF);
	SendData((Yend >> 8) & 0xFF);
}

/******************************************************************************
function :	Set Cursor
parameter:
	Xstart : X-axis starting position
	Ystart : Y-axis starting position
******************************************************************************/
void EPD_213_BW::SetCursor(unsigned char Xstart, unsigned char Ystart)
{
	SendCommand(0x4E); // SET_RAM_X_ADDRESS_COUNTER
	SendData(Xstart & 0xFF);

	SendCommand(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
	SendData(Ystart & 0xFF);
	SendData((Ystart >> 8) & 0xFF);
}

/******************************************************************************
function :	Send lut data and configuration
parameter:
	lut :   lut data
******************************************************************************/
void EPD_213_BW::Lut(unsigned char *lut)
{
	unsigned char count;
	SendCommand(0x32);
	for (count = 0; count < 153; count++)
	{
		SendData(lut[count]);
	}

	SendCommand(0x3f);
	SendData(*(lut + 153));
	SendCommand(0x03); // gate voltage
	SendData(*(lut + 154));
	SendCommand(0x04);		// source voltage
	SendData(*(lut + 155)); // VSH
	SendData(*(lut + 156)); // VSH2
	SendData(*(lut + 157)); // VSL
	SendCommand(0x2c);		// VCOM
	SendData(*(lut + 158));
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
	Mode : Mode selection
******************************************************************************/
int EPD_213_BW::Init(char Mode)
{
	/* this calls the peripheral hardware interface, see epdif */
	if (IfInit() != 0)
	{
		return -1;
	}

	Reset();

	int count;
	if (Mode == FULL)
	{
		WaitUntilIdle();
		SendCommand(0x12); // soft reset
		WaitUntilIdle();

		SendCommand(0x01); // Driver output control
		SendData(0xF9);
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x11); // data entry mode
		SendData(0x03);

		SetWindows(0, 0, width - 1, height - 1);
		SetCursor(0, 0);

		SendCommand(0x3C); // BorderWavefrom
		SendData(0x05);

		SendCommand(0x21); //  Display update control
		SendData(0x00);
		SendData(0x80);

		SendCommand(0x18); // Read built-in temperature sensor
		SendData(0x80);

		WaitUntilIdle();
		Lut(lut_full_update);
	}
	else if (Mode == PART)
	{

		DigitalWrite(reset_pin, LOW); // module reset
		DelayMs(1);
		DigitalWrite(reset_pin, HIGH);

		Lut(lut_partial_update);

		SendCommand(0x37);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x40);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x3C); // BorderWavefrom
		SendData(0x80);

		SendCommand(0x22); // Display Update Sequence Option
		SendData(0xC0);	   // Enable clock and  Enable analog
		SendCommand(0x20); // Activate Display Update Sequence
		WaitUntilIdle();

		SetWindows(0, 0, width - 1, height - 1);
		SetCursor(0, 0);
	}
	else
	{
		return -1;
	}

	return 0;
}

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
void EPD_213_BW::Reset(void)
{
	DigitalWrite(reset_pin, HIGH);
	DelayMs(20);
	DigitalWrite(reset_pin, LOW); // module reset
	DelayMs(2);
	DigitalWrite(reset_pin, HIGH);
	DelayMs(20);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_213_BW::Clear(void)
{
	int w, h;
	w = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
	h = height;
	SendCommand(0x24);
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			SendData(0xff);
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xC7);
	SendCommand(0x20);
	WaitUntilIdle();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
	frame_buffer : Image data
******************************************************************************/
void EPD_213_BW::Display(const unsigned char *frame_buffer)
{
	int w = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
	int h = height;

	if (frame_buffer != NULL)
	{
		SendCommand(0x24);
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xC7);
	SendCommand(0x20);
	WaitUntilIdle();
}

/******************************************************************************
function :	Refresh a base image
parameter:
	frame_buffer : Image data
******************************************************************************/
void EPD_213_BW::DisplayPartBaseImage(const unsigned char *frame_buffer)
{
	int w = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
	int h = height;

	if (frame_buffer != NULL)
	{
		SendCommand(0x24);
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}

		SendCommand(0x26);
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xC7);
	SendCommand(0x20);
	WaitUntilIdle();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and partial refresh
parameter:
	frame_buffer : Image data
******************************************************************************/
void EPD_213_BW::DisplayPart(const unsigned char *frame_buffer)
{
	int w = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
	int h = height;

	if (frame_buffer != NULL)
	{
		SendCommand(0x24);
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0x0f);
	SendCommand(0x20);
	WaitUntilIdle();
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_213_BW::ClearPart(void)
{
	int w, h;
	w = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
	h = height;
	SendCommand(0x24);
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			SendData(0xff);
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0x0f);
	SendCommand(0x20);
	WaitUntilIdle();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_213_BW::Sleep()
{
	SendCommand(0x10); // enter deep sleep
	SendData(0x01);
	DelayMs(200);

	DigitalWrite(reset_pin, LOW);
}

/* END OF FILE */
