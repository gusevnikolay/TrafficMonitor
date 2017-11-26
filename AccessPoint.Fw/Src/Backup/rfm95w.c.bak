#include "rfm95w.h"

#define REG_FIFO      						 0x0
#define REG_OPMODE    						 0x1
#define REG_FRF_MSB  						   0x6
#define REG_FRF_MID   						 0x7
#define REG_FRF_LSB   						 0x8
#define REG_PA_CONFIG 						 0x9
#define REG_PA_RAMP   						 0xA
#define REG_OCP       						 0xB

#define REG_LNA                    0xC
#define REG_FIFO_ADDR_PTR          0xD
#define REG_FIFO_TX_BASE_ADDR      0xE
#define REG_FIFO_RX_BASE_ADDR      0xF
#define REG_FIFO_RX_CURRENT_ADDR   0x10
#define REG_IRQ_FLAGS_MASK         0x11
#define REG_IRQ_FLAGS              0x12
#define REG_RX_NB_BYTES 					 0x13
#define REG_RX_HEADER_CNT_MSB 		 0x14
#define REG_RX_HEADER_CNT_LSB 		 0x15
#define REG_RX_PACKET_CNT_MSB 		 0x16
#define REG_RX_PACKET_CNT_LSB 		 0x17
#define REG_MODE_STAT 						 0x18
#define REG_PACKET_SNR_VALUE 		   0x19

#define REG_PACKET_RSSI 					 0x1A
#define REG_RSSI 								   0x1B
#define REG_HOP_CHANNEL 					 0x1C
#define REG_MODEM_CONFIG1 				 0x1D
#define REG_MODEM_CONFIG2 				 0x1E
#define REG_MODEM_CONFIG3 				 0x26
#define REG_SYMB_TIMEOUT_LSB 		   0x1F
#define REG_PREAMBLE_MSB 				   0x20
#define REG_PREAMBLE_LSB 				   0x21
#define REG_PAYLOAD_LENGTH 			   0x22
#define REG_MAX_PAYLOAD_LENGTH 	   0x23
#define REG_HOPE_PERIOD 					 0x24
#define REG_FIFO_RX_BYTE_ADDR 		 0x25
		
void rfm95w_init()
{
	  var_delay_ms(300);
		rfm_write(REG_OPMODE, 0x0);
    var_delay_ms(100);
		rfm_write(REG_OPMODE, 0x80);
		rfm_write(REG_OPMODE, 0x81);
		rfm_write(REG_FRF_MSB, 0xD9);
		rfm_write(REG_FRF_MID, 0x6);
		rfm_write(REG_FRF_LSB, 0x8B);
		rfm_write(REG_PA_CONFIG, 0xFF);
		rfm_write(REG_MODEM_CONFIG1, 0x72);
		rfm_write(REG_MODEM_CONFIG2, 0x74);
		rfm_write(REG_PREAMBLE_MSB, 0x0);
		rfm_write(REG_PREAMBLE_LSB, 0x8);
		rfm_write(0x39, 0x34);
		rfm_write(0x33, 0x27);
		rfm_write(0x3B, 0x1D);
		rfm_write(REG_FIFO_TX_BASE_ADDR, 0x80);
		rfm_write(REG_FIFO_RX_BASE_ADDR, 0x0);
}
