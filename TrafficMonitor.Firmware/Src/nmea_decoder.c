#include "nmea_decoder.h"
#include <string.h>

char          line[255];
unsigned char cursor_pointer = 0;

void nmea_append(char ch)
{
	if(cursor_pointer>255)cursor_pointer = 0;
	if(ch == '\n'){
			if(strstr (line,"$GPGGA")){
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
																latitude = (line[j+1]-0x30)*1000+(line[j+2]-0x30)*100+(line[j+3]-0x30)*10+(line[j+4]-0x30)+(line[j+6]-0x30)*0.1 + (line[j+7]-0x30)*0.01 + (line[j+8]-0x30)*0.001+ (line[j+9]-0x30)*0.0001;
														break;
														
														case 3:
																longitude = (line[j+1]-0x30)*1000+(line[j+2]-0x30)*100+(line[j+3]-0x30)*10+(line[j+4]-0x30)+(line[j+6]-0x30)*0.1 + (line[j+7]-0x30)*0.01 + (line[j+8]-0x30)*0.001+ (line[j+9]-0x30)*0.0001;
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
