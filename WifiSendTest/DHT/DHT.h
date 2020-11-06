/*
 * DHT.h
 *
 * Created: 04-11-2020 09:14:56
 *  Author: Simon
 */ 


#ifndef DHT_H_
#define DHT_H_

#define DHT_PIN PINB
#define DHT_PORT PORTB
#define DHT_DDR DDRB
#define DHT_BIT PB3
#define DHT_BITMASK (1<<DHT_BIT)


#define set_dht_output()			(set_bit(DHT_DDR, DHT_BITMASK))
#define set_dht_input()				(clear_bit(DHT_DDR, DHT_BITMASK))
#define set_dht_high()				(set_bit(DHT_PORT, DHT_BITMASK))
#define set_dht_low()				(clear_bit(DHT_PORT, DHT_BITMASK))
#define dht_read()					(DHT_PIN & DHT_BITMASK)

#define set_bit(port, mask)			(port |= mask)
#define clear_bit(port, mask)		(port &= ~mask)

void DHTSensorStart();
void DHTInit();
uint8_t DHTSensorResponse();
uint8_t DHTSensorRead(uint8_t data[5]);
uint8_t DHTSensorChecksum(uint8_t data[5]);


#endif /* DHT_H_ */