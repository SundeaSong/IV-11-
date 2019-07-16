#ifndef _LED_H_	
#define _LED_H_

#ifdef __cplusplus			//???CPP??C??
extern "C" {
#endif

#include "Config.h"

void	led_display_line(unsigned char volt);
void led_display_point(unsigned char volt);
unsigned char conversion_volt(void);


#ifdef __cplusplus		  
}
#endif

#endif

