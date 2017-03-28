#ifndef _IAD_CAL_H_
#define _IAD_CAL_H_
#ifdef __cplusplus			//定义对CPP进行C处理
extern "C" {
#endif

#include "Config.h"

#define FID_Address 0x0002


unsigned  int Read_FixtureID(void);
void Write_FixtureID(char *id);
void Reset_Tester(void);
void Firmware(void); 
void ControlBoard(void);
void Tester_Control(void);
void Start_Control(void);
void PUSH_CONNECT(void);
void PUSH_DISCONNECT(void);
void Reset_Test(void);
void Help_Cmd(void);
#ifdef __cplusplus
}
#endif

#endif
