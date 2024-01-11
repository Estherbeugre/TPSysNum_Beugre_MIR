/*
 * vu_meter.h
 *
 *  Created on: Nov 9, 2023
 *      Author:
 */
#include "spi.h"

#ifndef INC_VU_METER_H_
#define INC_VU_METER_H_

typedef struct h_vu_struct{
   uint8_t led[2];
   uint8_t spi_buffer[3];
} h_vu_t;

int vu_init(h_vu_t *h_vu);
int vu_led(h_vu_t *h_vu, uint8_t port, uint8_t led, uint8_t state);

#endif /* INC_VU_METER_H_ */
