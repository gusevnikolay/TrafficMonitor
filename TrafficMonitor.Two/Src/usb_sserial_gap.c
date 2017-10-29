#include "usb_sserial_gap.h"
#include "usbd_cdc_if.h"


uint8_t UsbUartDataGap;
uint8_t txBuffer[256];
uint8_t txCursor = 0;

extern void sserial_set_devname(const char* devname);
extern void sserial_poll_uart(unsigned char portindex);

uint8_t dataLen = 0;
void sserial_append_data(uint8_t *data, uint8_t dLen)
{
	dataLen = dLen;
	for(int i=0;i<(int)dLen && i<255;i++)
	{
		UsbUartDataGap = data[i];
		sserial_poll_uart(0);
	}
}
void sserial_send_start(unsigned char portindex){
	txCursor = 0;
}

void sserial_send_end(unsigned char portindex){
	if(txCursor>0){
			CDC_Transmit_FS(txBuffer, txCursor);
			txCursor = 0;
	}
}

void uart_send(unsigned char port, unsigned char data){
		if(txCursor<255)txBuffer[txCursor++] = data;	  
}

unsigned char uart_get(unsigned char port){
		return UsbUartDataGap;
}

unsigned char uart_received(unsigned char port)
{
		return 1;
}

void var_delay_ms(int ms)
{
		HAL_Delay(ms);
}

