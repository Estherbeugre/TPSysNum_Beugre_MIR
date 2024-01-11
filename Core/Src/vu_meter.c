/*

 */
#include "vu_meter.h"
#include "spi.h"

#define VU_ADDR 0x40
#define VU_IODIRA_ADDRESS 0x00
#define VU_IODIRB_ADDRESS 0x01
#define VU_GPIOA_ADDRESS 0x12
#define VU_GPIOB_ADDRESS 0x13
#define VU_PORTA 1
#define VU_PORTB 0
#define DATA_SIZE 3

int vu_init(h_vu_t *h_vu){
	HAL_GPIO_WritePin(VU_nRESET_GPIO_Port, VU_nRESET_Pin, SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_RESET);
	h_vu->spi_buffer[0]=VU_ADDR;
	h_vu->spi_buffer[1]=VU_IODIRA_ADDRESS;
	h_vu->spi_buffer[2]=VU_PORTB;
	HAL_SPI_Transmit(&hspi3, h_vu->spi_buffer, DATA_SIZE, 100);

	HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_RESET);


	h_vu->spi_buffer[0]=VU_ADDR;
	h_vu->spi_buffer[1]=VU_IODIRB_ADDRESS;
	h_vu->spi_buffer[2]=VU_PORTB;
	HAL_SPI_Transmit(&hspi3, h_vu->spi_buffer, DATA_SIZE, 100);

	HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_SET);

	return 1;
}

int vu_led(h_vu_t *h_vu, uint8_t port, uint8_t led, uint8_t state){
	h_vu->led[port]=led;
	if(port==0){
		HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_RESET);
		h_vu->spi_buffer[0]=VU_ADDR;
		h_vu->spi_buffer[1]=VU_GPIOB_ADDRESS;
		h_vu->spi_buffer[2]=0xF0;
		HAL_SPI_Transmit(&hspi3, h_vu->spi_buffer, DATA_SIZE, 100);
		HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_SET);
	}
	else if (port==1){
		HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_RESET);
		h_vu->spi_buffer[0]=VU_ADDR;
		h_vu->spi_buffer[1]=VU_GPIOA_ADDRESS;
		h_vu->spi_buffer[2]=0x55;
		HAL_SPI_Transmit(&hspi3, h_vu->spi_buffer, DATA_SIZE, 100);
		HAL_GPIO_WritePin(VU_nCS_GPIO_Port, VU_nCS_Pin, GPIO_PIN_SET);
	}


}
