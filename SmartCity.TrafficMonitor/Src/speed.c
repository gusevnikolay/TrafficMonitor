#include "speed.h"
#include "stm32f1xx_hal.h"

#define BUFFER_SIZE 128

uint16_t sensor_one_buffer[BUFFER_SIZE];
uint16_t sensor_one_cursor = 0;
uint16_t sensor_two_buffer[BUFFER_SIZE];
uint16_t sensor_two_cursor = 0;

Doppler_t SpeedSensors;

void fill_struct()
{
		uint16_t min_val_1 = 65535;
		uint32_t sum_1 = 0;
		uint16_t max_val_1 = 0;
		uint16_t min_val_2 = 65535;
		uint32_t sum_2 = 0;
		uint16_t max_val_2 = 0;
		for(int i=0;i<BUFFER_SIZE;i++){
				if(min_val_1>sensor_one_buffer[i])min_val_1 = sensor_one_buffer[i];
			  if(min_val_2>sensor_two_buffer[i])min_val_2 = sensor_two_buffer[i];
				if(max_val_1<sensor_one_buffer[i])max_val_1 = sensor_one_buffer[i];
			  if(max_val_2<sensor_two_buffer[i])max_val_2 = sensor_two_buffer[i];
			  sum_1 += sensor_one_buffer[i];
			  sum_2 += sensor_two_buffer[i];
		}
		SpeedSensors.SENSOR_ONE_AVERAGE = sum_1/BUFFER_SIZE;
		SpeedSensors.SENSOR_TWO_AVERAGE = sum_2/BUFFER_SIZE;
		SpeedSensors.SENSOR_ONE_MAX = max_val_1;
		SpeedSensors.SENSOR_TWO_MAX = max_val_2;
		SpeedSensors.SENSOR_ONE_MIN = min_val_1;
		SpeedSensors.SENSOR_TWO_MIN = min_val_2;
}

void speed_append_sensor_one(uint16_t tim)
{
		sensor_one_buffer[sensor_one_cursor++] = tim;
		if(BUFFER_SIZE==sensor_one_cursor){ sensor_one_cursor = 0; fill_struct();}
}

void speed_append_sensor_two(uint16_t tim)
{
		sensor_two_buffer[sensor_two_cursor++] = tim;
		if(BUFFER_SIZE==sensor_two_cursor){sensor_two_cursor = 0; fill_struct();}
}

void doppler_state_set(char sensor, char state)
{
		if(sensor == 1){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, state==0?GPIO_PIN_RESET:GPIO_PIN_SET);
		}else if(sensor == 2){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, state==0?GPIO_PIN_RESET:GPIO_PIN_SET);
		}
}

