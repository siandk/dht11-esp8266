/*
 * DHT.c
 *
 * Created: 04-11-2020 09:14:46
 *  Author: Simon
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include "DHT.h"

#include <avr/interrupt.h>
#include <avr/wdt.h>

// Not really DHT init, but setup of timer
void DHTInit()
{
	// TIMER 3 CONFIG
	
	// Set /1024 prescaler, CTC Mode - See table 17-6 & 17.11.5
	TCCR3B |= (1<<WGM32) | (1<<CS32) | (1<<CS30);
	// Enable interrupt for output compare OCR1A
	TIMSK3 |= (1<<OCIE3A);
	// 2 second delay
	OCR3A = 31249;
	
	sei();
	// Enable watchdog timer (4 second timeout)
	wdt_enable(WDTO_4S);
}

void DHTSensorStart()
{
	set_dht_output();
	set_dht_low();
	_delay_ms(20);
	set_dht_high();
}

uint8_t DHTSensorResponse()
{
	int timeout = 0;
	set_dht_input();
	while (dht_read())
	{
		if (timeout > 50)
		{
			return 0;
		}
		timeout += 1;
		_delay_us(1);
	}
	timeout = 0;
	while (!dht_read())
	{
		if (timeout > 90)
		{
			return 0;
		}
		timeout += 1;
		_delay_us(1);
	}
	timeout = 0;
	while (dht_read())
	{
		if (timeout > 90)
		{
			return 0;
		}
		timeout += 1;
		_delay_us(1);
	}
	return 1;
	
}

uint8_t DHTSensorRead(uint8_t sensorData[5])
{
	uint8_t success = 1;
	
	DHTSensorStart();
	success = DHTSensorResponse();
	if (success)
	{
		for (int i = 0; i < 5; i++)
		{
			sensorData[i] = 0;
			uint8_t timer;
			for (int j = 7; j >= 0; j--)	// DHT sends MSB first
			{
				timer = 0;
				while (!dht_read());	// Wait for data
				while (dht_read())
				{
					timer += 1;
					_delay_us(1);
					if (timer > 90)
					{
						success = 0;
						break;
					}
				}
				if (timer > 30)
				{
					sensorData[i] |= (1<<j);
				}
			}
		}
		success = DHTSensorChecksum(sensorData);
	}
	return success;
}
// Last byte of data is checksum
// Datasheet 5
uint8_t DHTSensorChecksum(uint8_t data[5])
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += data[i];
	}
	return (sum & 0xff) == data[4]; // Extract last 8 bits from sum and compare to checksum
}