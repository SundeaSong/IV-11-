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
void LockBotton_Control(void);
void Reset_Test(void);
void Help_Cmd(void);
void Reset_Control(void);
void TOGGLE_LIFE(void);
void TOGGLE_RIGHT(void);
void PULL_ON(void);
void PULL_OFF(void);
void PUSH_IN(void);
void PUSH_OUT(void);
void LOCK_ON(void);
void LOCK_OFF(void);
#ifdef __cplusplus
}
#endif

#endif
