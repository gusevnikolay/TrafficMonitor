#ifndef __NMEA_DECODER_H
#define __NMEA_DECODER_H
//void nmea_append(char ch);

typedef struct
{
		unsigned int  hh;
		unsigned int  mm; 
		unsigned int  ss;
		unsigned int  sats;
		unsigned char latitude_string[12];
		unsigned char longitude_string[12];
		unsigned char isEast;
		unsigned char isNorth;        
} GPS_t;

#endif
