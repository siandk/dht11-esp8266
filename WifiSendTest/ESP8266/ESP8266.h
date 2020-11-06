/*
 * ESP8266.h
 *
 * Created: 04-11-2020 12:38:31
 *  Author: Simon
 */ 


#define F_CPU 16000000UL			/* Define CPU Frequency e.g. here its Ext. 16MHz */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>				/* Include standard boolean library */
#include "../USART/USART_RS232_H_file.h"		/* Include USART header file */

#ifndef ESP8266_H_
#define ESP8266_H_

#define SREG    _SFR_IO8(0x3F)

#define DEFAULT_BUFFER_SIZE		160
#define DEFAULT_TIMEOUT			10000

/* Connection Mode */
#define SINGLE					0
#define MULTIPLE				1

/* Application Mode */
#define NORMAL					0
#define TRANSPERANT				1

/* Application Mode */
#define STATION							1
#define ACCESSPOINT						2
#define BOTH_STATION_AND_ACCESPOINT		3

/* Define Required fields shown below */
#define DOMAIN				"192.168.43.83"
#define PORT				"5000"
#define API_WRITE_KEY		"FAPEQ7SZ701O8CCS"
#define CHANNEL_ID			"1217129"

#define SSID				"Simon"
#define PASSWORD			"aat55fbh"

enum ESP8266_RESPONSE_STATUS{
	ESP8266_RESPONSE_WAITING,
	ESP8266_RESPONSE_FINISHED,
	ESP8266_RESPONSE_TIMEOUT,
	ESP8266_RESPONSE_BUFFER_FULL,
	ESP8266_RESPONSE_STARTING,
	ESP8266_RESPONSE_ERROR
};

enum ESP8266_CONNECT_STATUS {
	ESP8266_CONNECTED_TO_AP,
	ESP8266_CREATED_TRANSMISSION,
	ESP8266_TRANSMISSION_DISCONNECTED,
	ESP8266_NOT_CONNECTED_TO_AP,
	ESP8266_CONNECT_UNKNOWN_ERROR
};

enum ESP8266_JOINAP_STATUS {
	ESP8266_WIFI_CONNECTED,
	ESP8266_CONNECTION_TIMEOUT,
	ESP8266_WRONG_PASSWORD,
	ESP8266_NOT_FOUND_TARGET_AP,
	ESP8266_CONNECTION_FAILED,
	ESP8266_JOIN_UNKNOWN_ERROR
};


extern int8_t Response_Status;
extern volatile int16_t Counter;
extern volatile int16_t pointer;
extern uint32_t TimeOut;
extern char RESPONSE_BUFFER[DEFAULT_BUFFER_SIZE];

void Read_Response(char* _Expected_Response);
void ESP8266_Clear();
void Start_Read_Response(char* _ExpectedResponse);
void GetResponseBody(char* Response, uint16_t ResponseLength);
void ESP8266_Init();
void SendApiData(char sensor[], uint8_t sensorRead, uint8_t sensorData[]);
bool WaitForExpectedResponse(char* ExpectedResponse);
bool SendATandExpectResponse(char* ATCommand, char* ExpectedResponse);
bool ESP8266_ApplicationMode(uint8_t Mode);
bool ESP8266_ConnectionMode(uint8_t Mode);
bool ESP8266_Begin();
bool ESP8266_Close();
bool ESP8266_WIFIMode(uint8_t _mode);
uint8_t ESP8266_JoinAccessPoint(char* _SSID, char* _PASSWORD);
uint8_t ESP8266_connected();
uint8_t ESP8266_Start(uint8_t _ConnectionNumber, char* Domain, char* Port);
uint8_t ESP8266_Send(char* Data);
int16_t ESP8266_DataAvailable();
uint8_t ESP8266_DataRead();
uint16_t Read_Data(char* _buffer);


#endif /* ESP8266_H_ */