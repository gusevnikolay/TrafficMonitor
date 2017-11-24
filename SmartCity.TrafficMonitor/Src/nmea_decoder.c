#include "nmea_decoder.h"
#include <string.h>
#include <math.h>
#include <stdint.h>
char          line[255];
unsigned char cursor_pointer = 0;

extern GPS_t GPS;


int ps;
void nmea_append(char ch)
{
	if(cursor_pointer>255)cursor_pointer = 0;
	if(ch == '\n'){
			if(strstr (line,"$GPGGA")){
					for(int i=0;i<12;i++){
							GPS.latitude_string[i] = 0x30;
							GPS.longitude_string[i] = 0x30;
					}
					for(int i=0;i<cursor_pointer;i++){
							if(line[i]==71 && line[i+1]==80 && line[i+2]==71 && line[i+3]==71 && line[i+4]==65){
									unsigned char p = 0;
									for(int j=i; j<cursor_pointer;j++){
											if(line[j]==','){
													switch(p++){
														case 0:
																GPS.hh = (line[j+1]-0x30)*10+(line[j+2]-0x30);
																GPS.mm = (line[j+3]-0x30)*10+(line[j+4]-0x30);
																GPS.ss = (line[j+5]-0x30)*10+(line[j+6]-0x30);
														break;
														
														case 1:
																for(int x=1;x<15;x++){
																		if(line[j+x]==',') x = 20; else
																		GPS.latitude_string[x-1] = line[j+x];
																}
														break;
														case 2:
															GPS.isNorth = (line[j+1]==78)?1:0;
														break;
														case 3:
																for(int x=1;x<15;x++){
																		if(line[j+x]==',') x = 20; else
																		GPS.longitude_string[x-1] = line[j+x];
																}
														break;
														case 4:
															GPS.isEast = (line[j+1]==69)?1:0;
														break;
														case 6:
																GPS.sats =(line[j+1]-0x30)*10+(line[j+2]-0x30);
														break;
														
														default:
															
														break;
													}
											}
									}
									break;
							}
					}
			}
			cursor_pointer = 0;
	}else{
			line[cursor_pointer++] = ch;
	}
}
