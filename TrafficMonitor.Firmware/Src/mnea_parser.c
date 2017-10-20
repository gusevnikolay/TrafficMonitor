#include "mnea_parser.h"

char          mnea_line[255];
unsigned char current_position = 0;

unsigned char hour      = 0;
unsigned char minutes   = 0;
unsigned char seconds   = 0;

float x_position        = 0.0;
float y_position        = 0.0;
unsigned char sat_count = 0.0;

void parse_line()
{
	
}

void mnead_append_char(unsigned char ch)
{
		mnea_line[current_position++] = ch;
		if(ch == 0xD) parse_line();
}

