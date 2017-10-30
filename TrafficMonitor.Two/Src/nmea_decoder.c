#include "nmea_decoder.h"
#include <string.h>
#include <math.h>
#include <stdint.h>
char          line[255];
unsigned char cursor_pointer = 0;

unsigned int  hh,mm,ss;
unsigned int sats = 0;
unsigned char latitude_string[12];
unsigned char longitude_string[12];
unsigned char isEast = 0;
unsigned char isNorth = 0;


int ps;
void nmea_append(char ch)
{
	if(cursor_pointer>255)cursor_pointer = 0;
	if(ch == '\n'){
			if(strstr (line,"$GPGGA")){
					for(int i=0;i<12;i++){
							latitude_string[i] = 0x30;
							longitude_string[i] = 0x30;
					}
					for(int i=0;i<cursor_pointer;i++){
							if(line[i]==71 && line[i+1]==80 && line[i+2]==71 && line[i+3]==71 && line[i+4]==65){
									unsigned char p = 0;
									for(int j=i; j<cursor_pointer;j++){
											if(line[j]==','){
													switch(p++){
														case 0:
																hh = (line[j+1]-0x30)*10+(line[j+2]-0x30);
																mm = (line[j+3]-0x30)*10+(line[j+4]-0x30);
																ss = (line[j+5]-0x30)*10+(line[j+6]-0x30);
														break;
														
														case 1:
																for(int x=1;x<15;x++){
																		if(line[j+x]==',') x = 20; else
																		latitude_string[x-1] = line[j+x];
																}
														break;
														case 2:
															isNorth = (line[j+1]==78)?1:0;
														break;
														case 3:
																for(int x=1;x<15;x++){
																		if(line[j+x]==',') x = 20; else
																		longitude_string[x-1] = line[j+x];
																}
														break;
														case 4:
															isEast = (line[j+1]==69)?1:0;
														break;
														case 6:
																sats =(line[j+1]-0x30)*10+(line[j+2]-0x30);
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
