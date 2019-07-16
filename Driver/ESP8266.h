#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "config.h"

u8 ESP_PortAnalysis(char *buff);
void ESP_RST(void);
void ESP_AppMode(u8 *mode);
void ESP_Connect_AP(u8 *user,u8 *password);
void ESP_Dis_Connect_AP(void);
void ESP_Set_CIPMUX(u8 *mode);
void ESP_CIPSTART(u8 *analysis, u8 *adderss);
void ESP_Send_Len(u8 *len);















#endif
