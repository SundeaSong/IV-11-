#ifndef USB_HID_H_
#define USB_HID_H_

//typedef enum {FALSE = 0, TRUE = !FALSE} bool;

/* DATA TYPE ------------------------------------------------------------------*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity         */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity         */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity         */
typedef signed   short INT16S;                   /* Signed   16 bit quantity         */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity         */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity         */
typedef float          FP32;                     /* Single precision floating point  */
typedef double         FP64;                     /* Double precision floating point  */

/* Includes ------------------------------------------------------------------*/
#include "Config.h"
#include "stm32f10x.h"
#include "usb_type.h"

//BYTE1 --
//       |--bit0:   Left Control是否按下，按下为1 
//       |--bit1:   Left Shift  是否按下，按下为1 
//       |--bit2:   Left Alt    是否按下，按下为1 
//       |--bit3:   Left GUI    是否按下，按下为1 
//       |--bit4:   Right Control是否按下，按下为1  
//       |--bit5:   Right Shift 是否按下，按下为1 
//       |--bit6:   Right Alt   是否按下，按下为1 
//       |--bit7:   Right GUI   是否按下，按下为1 
#define  FKEY_NULL 		    0x00
#define  FKEY_LEFT_CTRL 	0x01
#define  FKEY_LEFT_SHIFT 	0x02
#define  FKEY_LEFT_ALT 		0x04
#define  FKEY_LEFT_GUI 		0x08
#define  FKEY_RIGHT_CTRL 	0x10
#define  FKEY_RIGHT_SHIFT 	0x20
#define  FKEY_RIGHT_ALT 	0x40
#define  FKEY_RIGHT_GUI 	0x80

#define KEY_TAB 0x2B

#define KEY_RELEASE 0x00		//按键释放
#define KEY_F1 0x3A
#define KEY_F2 0x3B
#define KEY_F3 0x3C
#define KEY_F4 0x3D
#define KEY_F5 0x3E
#define KEY_F6 0x3F
#define KEY_F7 0x40
#define KEY_F8 0x41
#define KEY_F9 0x42
#define KEY_F10 0x43
#define KEY_F11 0x44
#define KEY_F12 0x45

#define KEY_1 0x1E 
#define KEY_2 0x1F
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26
#define KEY_0 0x27

void SendKeyValue(unsigned char fun,unsigned char val);

#endif
