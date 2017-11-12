/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Generic SX1276 driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#ifndef __SX1276_H__
#define __SX1276_H__
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "radio.h"
#include "sx1276Regs-Fsk.h"
#include "sx1276Regs-LoRa.h"

#define RADIO_WAKEUP_TIME                           1 // [ms]
#define LORA_MAC_PRIVATE_SYNCWORD                   0x12
#define LORA_MAC_PUBLIC_SYNCWORD                    0x34

void SX1276OnDio0Irq( void );
void SX1276OnDio1Irq( void );
void SX1276OnDio2Irq( void );
void SX1276OnDio3Irq( void );
void SX1276OnDio4Irq( void );
void SX1276OnDio5Irq( void );

typedef struct
{
    int8_t   Power;
    uint32_t Fdev;
    uint32_t Bandwidth;
    uint32_t BandwidthAfc;
    uint32_t Datarate;
    uint16_t PreambleLen;
    bool     FixLen;
    uint8_t  PayloadLen;
    bool     CrcOn;
    bool     IqInverted;
    bool     RxContinuous;
    uint32_t TxTimeout;
    uint32_t RxSingleTimeout;
}RadioFskSettings_t;

/*!
 * Radio FSK packet handler state
 */
typedef struct
{
    uint8_t  PreambleDetected;
    uint8_t  SyncWordDetected;
    int8_t   RssiValue;
    int32_t  AfcValue;
    uint8_t  RxGain;
    uint16_t Size;
    uint16_t NbBytes;
    uint8_t  FifoThresh;
    uint8_t  ChunkSize;
}RadioFskPacketHandler_t;

/*!
 * Radio LoRa modem parameters
 */
typedef struct
{
    int8_t   Power;
    uint32_t Bandwidth;
    uint32_t Datarate;
    bool     LowDatarateOptimize;
    uint8_t  Coderate;
    uint16_t PreambleLen;
    bool     FixLen;
    uint8_t  PayloadLen;
    bool     CrcOn;
    bool     FreqHopOn;
    uint8_t  HopPeriod;
    bool     IqInverted;
    bool     RxContinuous;
    uint32_t TxTimeout;
    bool     PublicNetwork;
}RadioLoRaSettings_t;

typedef struct
{
    int8_t SnrValue;
    int16_t RssiValue;
    uint8_t Size;
}RadioLoRaPacketHandler_t;

typedef struct
{
    RadioState_t             State;
    RadioModems_t            Modem;
    uint32_t                 Channel;
    RadioFskSettings_t       Fsk;
    RadioFskPacketHandler_t  FskPacketHandler;
    RadioLoRaSettings_t      LoRa;
    RadioLoRaPacketHandler_t LoRaPacketHandler;
}RadioSettings_t;


typedef struct SX1276_s
{
    RadioSettings_t Settings;
}SX1276_t;


typedef void ( DioIrqHandler )( void );

#define XTAL_FREQ                                   32000000
#define FREQ_STEP                                   61.03515625

#define RX_BUFFER_SIZE                              256


void SX1276Init( RadioEvents_t *events );
RadioState_t SX1276GetStatus( void );
void SX1276SetModem( RadioModems_t modem );
void SX1276SetChannel( uint32_t freq );
bool SX1276IsChannelFree( RadioModems_t modem, uint32_t freq, int16_t rssiThresh, uint32_t maxCarrierSenseTime );
uint32_t SX1276Random( void );
void SX1276SetRxConfig( RadioModems_t modem, uint32_t bandwidth,
                         uint32_t datarate, uint8_t coderate,
                         uint32_t bandwidthAfc, uint16_t preambleLen,
                         uint16_t symbTimeout, bool fixLen,
                         uint8_t payloadLen,
                         bool crcOn, bool freqHopOn, uint8_t hopPeriod,
                         bool iqInverted, bool rxContinuous );


void SX1276SetTxConfig( RadioModems_t modem, int8_t power, uint32_t fdev,
                        uint32_t bandwidth, uint32_t datarate,
                        uint8_t coderate, uint16_t preambleLen,
                        bool fixLen, bool crcOn, bool freqHopOn,
                        uint8_t hopPeriod, bool iqInverted, uint32_t timeout );

uint32_t SX1276GetTimeOnAir( RadioModems_t modem, uint8_t pktLen );
void SX1276Send( uint8_t *buffer, uint8_t size );
void SX1276SetSleep( void );
void SX1276SetStby( void );
void SX1276SetRx( uint32_t timeout );
void SX1276StartCad( void );
void SX1276SetTxContinuousWave( uint32_t freq, int8_t power, uint16_t time );
int16_t SX1276ReadRssi( RadioModems_t modem );
void SX1276Write( uint8_t addr, uint8_t data );
uint8_t SX1276Read( uint8_t addr );
void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size );
void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size );
void SX1276SetMaxPayloadLength( RadioModems_t modem, uint8_t max );
void SX1276SetPublicNetwork( bool enable );

#endif // __SX1276_H__
