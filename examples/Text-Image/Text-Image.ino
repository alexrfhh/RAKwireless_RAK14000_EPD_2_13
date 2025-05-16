/**
 * @file Text-Image.ino
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Simple example to draw text and images on the EPD.
 * @version 0.1
 * @date 2024-01-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <Arduino.h>
//#include <rak14000.h>
#include "image.h"
#include "epdif.h"
#include "epdpaint.h"
#include "epdfonts.h"
#include "epd2in13.h"

/** Power control for RAK14000 */
#define POWER_ENABLE WB_IO2

/** Display buffer */
unsigned char image[4000];
/** Instance to EPD */
EPD_213_BW epd;
/** Instance for paint and write */
Paint paint(image, 122, 250);

/** Color definitions */
uint16_t bg_color = 1;
uint16_t txt_color = 0;

// Forward declarations
void clear_rak14000(void);
void rak14000_text(int16_t x, int16_t y, char *text);

/**
 * @brief Arduino setup()
 * 
 */
void setup(void)
{
	pinMode(LED_GREEN, OUTPUT);
	digitalWrite(LED_GREEN, HIGH);
	pinMode(LED_BLUE, OUTPUT);
	digitalWrite(LED_BLUE, HIGH);

	pinMode(WB_IO2, OUTPUT);
	digitalWrite(WB_IO2, HIGH);

	Serial.begin(115200);
	time_t serial_timeout = millis();

	while (1)
	{
		if ((millis() - serial_timeout) < 5000)
		{
			delay(100);
			digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
		}
		else
		{
			break;
		}
	}

	pinMode(POWER_ENABLE, INPUT_PULLUP);
	digitalWrite(POWER_ENABLE, HIGH);

	clear_rak14000();

	paint.drawBitmap(5, 5, (uint8_t *)rak_img, 59, 56);

	rak14000_text(60, 65, "RAKWireless");
	rak14000_text(60, 85, "IoT Made Easy");

	epd.Display(image);
}

/**
 * @brief Arduino loop()
 * 
 */
void loop(void)
{

	delay(5000);

	clear_rak14000();

	paint.drawBitmap(185, 57, (uint8_t *)rak_img, 59, 56);

	rak14000_text(5, 5, "WisBlock");
	rak14000_text(5, 25, "Modular IoT");

	epd.Display(image);

	delay(60000);
}

/**
 * @brief Clear display
 * 
 */
void clear_rak14000(void)
{
	paint.SetRotate(ROTATE_270);
	epd.Init(FULL);
	// epd.Clear();
	paint.Clear(1);
}

/**
 * @brief Write a text
 * 
 * @param x Start X
 * @param y Start Y
 * @param text Text to write
 */
void rak14000_text(int16_t x, int16_t y, char *text)
{
	sFONT *use_font;
	use_font = &Font20;
	paint.DrawStringAt(x, y, text, use_font, 0);
}
