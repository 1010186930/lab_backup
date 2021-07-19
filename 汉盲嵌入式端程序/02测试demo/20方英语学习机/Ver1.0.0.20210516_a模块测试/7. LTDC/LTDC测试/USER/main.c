#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
/************************************************
 ALIENTEK 阿波罗STM32F429开发板实验14
 LTDC LCD实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com  
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
#define LOGO_W	200
#define LOGO_H	100
#define FRAME_COUT		1
#define LOGO_W	200
#define LOGO_H	100
#define FRAME_COUT		1
const unsigned char gImage_1[2816] = { 0x01,0x10,0x24,0x00,0x27,0x00,0x01,0x1B,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x66,0x19,0x66,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x11,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x11,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x11,0x66,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x66,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x66,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x11,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x11,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x11,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x11,0x25,0x11,0x25,0x11,
0xE4,0x10,0x82,0x08,0x41,0x00,0x00,0x00,0x20,0x00,0xC3,0x10,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x66,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x21,0x04,0x39,0xE3,0x40,0x61,0x08,0x20,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x21,0x00,0xC3,0x08,0x25,0x11,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x25,0x11,0x24,0x11,0x04,0x11,
0xE4,0x38,0xA2,0x90,0x61,0xC0,0x61,0xA8,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xA2,0x08,0x24,0x11,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x65,0x21,
0x65,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x04,0x11,0x82,0x08,0x41,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x41,0x68,
0x61,0xD8,0x82,0xE8,0x61,0xC8,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x20,0x00,0x82,0x08,0x24,0x11,0x45,0x19,0x85,0x21,0xC3,0xA3,0x84,0x62,
0x65,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0xC3,0x08,0x41,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x48,0x61,0xD8,
0x82,0xE8,0x82,0xD8,0xA2,0x60,0x04,0x21,0x45,0x29,0x45,0x29,0x04,0x21,0xC3,0x18,
0x61,0x08,0x00,0x00,0x20,0x00,0xC3,0x10,0x44,0x52,0x21,0xED,0x04,0x73,0x65,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x66,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x25,0x11,0x82,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x61,0xC8,0x82,0xE8,
0x82,0xE0,0xAE,0xE3,0x3C,0xEF,0x7D,0xEF,0x7D,0xEF,0x7D,0xEF,0xDB,0xDE,0x55,0xAD,
0x0C,0x63,0xA2,0x10,0x20,0x00,0x61,0x62,0x61,0xF5,0x03,0x7B,0x65,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x04,0x11,0x61,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xA0,0x18,0x60,0x39,0x00,0x00,0x00,0x18,0x61,0xB8,0x82,0xE0,0x82,0xE8,
0x45,0xE9,0x28,0xEA,0x28,0xEA,0x28,0xEA,0x2C,0xF3,0x9E,0xFF,0xFF,0xFF,0xBE,0xF7,
0xB6,0xB5,0x86,0x31,0xA0,0x18,0x40,0xC4,0x23,0x83,0x45,0x19,0x66,0x19,0x45,0x11,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x82,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0xA2,0x10,0xC3,0x18,0x00,0x00,0x00,0x00,
0x20,0x62,0x60,0xCC,0x80,0x18,0x00,0x10,0x61,0xA8,0x82,0xE0,0x82,0xE8,0x82,0xE8,
0x82,0xE8,0x82,0xE8,0x82,0xE8,0x04,0xE9,0x5D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x9A,0xD6,0x24,0x29,0x60,0x72,0x03,0x7B,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x25,0x11,0x41,0x00,
0x00,0x00,0x20,0x00,0xAE,0x73,0x1C,0xE7,0x5D,0xEF,0x34,0xA5,0xC3,0x18,0x20,0x93,
0x41,0xF5,0x60,0x6A,0x00,0x08,0x41,0x98,0x82,0xE0,0x82,0xE8,0x82,0xE8,0x82,0xE8,
0x82,0xE8,0x82,0xE8,0xC3,0xE8,0x5D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x75,0xAD,0x40,0x39,0x83,0x62,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x04,0x11,0x00,0x00,0x00,0x00,
0xA2,0x10,0x38,0xC6,0xD7,0xBD,0xAE,0x73,0x9A,0xD6,0xEB,0x5A,0xE0,0xB3,0x61,0xFD,
0x40,0xC4,0x20,0x08,0x41,0x90,0x82,0xE0,0x82,0xE8,0x82,0xE8,0x86,0xE9,0xC7,0xE9,
0xC7,0xE9,0x49,0xEA,0x7D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7D,0xEF,
0x26,0x52,0xC3,0x41,0x65,0x19,0x45,0x19,0x66,0x19,0x66,0x19,0x66,0x19,0x66,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0xE3,0x10,0x00,0x00,0x00,0x00,0x20,0x00,
0xCB,0x5A,0x51,0x8C,0x6D,0x6B,0xAE,0x73,0x23,0x21,0x40,0xC4,0x61,0xFD,0xC0,0xDC,
0xA0,0x20,0x41,0x88,0x82,0xE0,0x82,0xE8,0xC3,0xE8,0xF7,0xFD,0x3C,0xFF,0x3C,0xFF,
0x5D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4B,0x6B,
0x63,0x29,0x45,0x19,0x45,0x19,0x66,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0xC3,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,
0x82,0x10,0x82,0x10,0x41,0x08,0x40,0x08,0x40,0xCC,0x61,0xFD,0xE0,0xE4,0x00,0x29,
0x41,0x88,0x82,0xE0,0x82,0xE8,0x82,0xE8,0x79,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x73,0x23,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x11,
0x45,0x19,0x45,0x19,0xE3,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0xE3,0x18,0x08,0x42,
0xC7,0x39,0x86,0x31,0x81,0x10,0x40,0xCC,0x61,0xFD,0xE0,0xE4,0xE0,0x28,0x41,0x88,
0x82,0xE0,0x82,0xE8,0xA2,0xE8,0x9A,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8D,0x73,0x23,0x21,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,
0x45,0x19,0xE4,0x10,0x00,0x00,0x00,0x00,0x82,0x10,0x14,0xA5,0x59,0xCE,0xF3,0x9C,
0x9A,0xD6,0x69,0x4A,0x20,0xC4,0x61,0xFD,0xA0,0xDC,0x60,0x10,0x41,0x88,0x82,0xE0,
0x82,0xE8,0x04,0xE9,0xBA,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBE,0xF7,0xC9,0x62,0x83,0x31,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x04,0x11,0x20,0x00,0x00,0x00,0xA2,0x10,0x38,0xC6,0x59,0xCE,0xD3,0x9C,0x9E,0xF7,
0xCB,0x5A,0xC0,0xAB,0x61,0xF5,0xC0,0xAB,0x00,0x08,0x41,0x90,0x82,0xE0,0x82,0xE8,
0x65,0xE9,0xDB,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x3C,0xE7,0xC4,0x41,0x03,0x4A,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x11,0x25,0x11,
0x41,0x00,0x00,0x00,0x00,0x00,0xAA,0x52,0xB6,0xB5,0x96,0xB5,0xCF,0x7B,0x61,0x08,
0xE0,0x8A,0x21,0xF5,0xC0,0x51,0x00,0x08,0x41,0xA0,0x82,0xE0,0x82,0xE8,0x28,0xEA,
0x1C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xDF,0xFF,0x51,0x8C,0x60,0x41,0xA3,0x6A,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x11,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0xC3,0x10,
0x20,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x41,0x08,0x00,0x00,0x00,0x00,0x80,0x41,
0x20,0x93,0x40,0x08,0x00,0x18,0x61,0xB0,0x82,0xE0,0x82,0xE8,0x2C,0xF3,0x7D,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7D,0xEF,0x30,0x84,
0xA2,0x18,0x40,0x93,0x23,0x7B,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x11,0x45,0x19,0xC3,0x08,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x08,0x60,0x10,
0x00,0x00,0x00,0x20,0x61,0xC0,0x82,0xE8,0x82,0xE8,0x10,0xF4,0xDF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xDE,0x2C,0x63,0x82,0x10,0x40,0x39,
0xE0,0xE4,0x23,0x83,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0xC3,0x10,
0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x30,0x61,0xD0,0x82,0xE8,0xA2,0xE0,0x4D,0xC3,0xD7,0xBD,0x38,0xC6,0x38,0xC6,
0xF7,0xBD,0xF3,0x9C,0x0C,0x63,0xE3,0x18,0x20,0x00,0x41,0x00,0xE2,0x72,0x61,0xFD,
0x03,0x7B,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x04,0x11,
0x82,0x08,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x50,
0x61,0xD8,0x82,0xE8,0x61,0xD0,0x20,0x40,0x00,0x00,0x20,0x00,0x41,0x08,0x20,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x62,0x08,0x04,0x11,0xE4,0x39,0xE1,0xDC,0xE3,0x72,
0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x65,0x19,0x65,0x19,0x45,0x19,
0x65,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x25,0x11,0xE4,0x10,0xA3,0x08,0x82,0x08,0x62,0x08,0x61,0x08,0x61,0x60,0x61,0xD0,
0x82,0xE8,0x61,0xC0,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x00,
0x82,0x08,0xE3,0x10,0x45,0x19,0x45,0x19,0x65,0x19,0xE4,0x6A,0x24,0x42,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x65,0x19,0x45,0x19,0x45,0x19,0x25,0x21,0x04,0x49,0xA2,0x80,
0x61,0x80,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x62,0x08,0x24,0x11,
0x45,0x19,0x45,0x19,0x65,0x19,0x45,0x11,0x65,0x19,0x65,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x65,0x19,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x25,0x21,
0xE3,0x10,0x82,0x08,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x61,0x00,0x25,0x11,
0x45,0x19,0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x11,0x45,0x19,0x65,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x24,0x11,0xC3,0x10,0x62,0x08,0x41,0x00,0x21,0x00,0xC3,0x08,0x45,0x19,
0x65,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x65,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x11,0x45,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x11,0x45,0x19,
0x66,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,
0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x66,0x19,
0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x66,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19,0x45,0x19,0x45,0x19,0x45,0x19,
0x45,0x19,0x45,0x19,0x45,0x19,0x66,0x19};





int main(void)
{
    u8 x=0;
  	u8 lcd_id[12];
	u16 color[]={BLUE};
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    uart_init(115200);              //初始化USART
    LED_Init();                     //初始化LED 
    KEY_Init();                     //初始化按键
    SDRAM_Init();                   //SDRAM初始化
    LCD_Init();                     //LCD初始化
	POINT_COLOR=RED; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。	
    while(1)
    {
//        switch(x)
//		{
//			case 0:LCD_Clear(WHITE);break;
//			case 1:LCD_Clear(BLACK);break;
//			case 2:LCD_Clear(BLUE);break;
//			case 3:LCD_Clear(RED);break;
//			case 4:LCD_Clear(MAGENTA);break;
//			case 5:LCD_Clear(GREEN);break;
//			case 6:LCD_Clear(CYAN);break; 
//			case 7:LCD_Clear(YELLOW);break;
//			case 8:LCD_Clear(BRRED);break;
//			case 9:LCD_Clear(GRAY);break;
//			case 10:LCD_Clear(LGRAY);break;
//			case 11:LCD_Clear(BROWN);break;
//		}
		POINT_COLOR=RED;
		LCD_Clear(YELLOW);
//		LCD_ShowString(10,40,260,32,32,"Apollo STM32F4/F7"); 	
//		LCD_ShowString(10,80,240,24,24,"LTDC TEST");
//		LCD_ShowString(10,110,240,16,16,"ATOM@ALIENTEK");
// 		LCD_ShowString(10,130,240,16,16,lcd_id);		//显示LCD ID	 
		
		LTDC_Color_Fill(0,0,28,16,gImage_1);
		LTDC_Fill(60,60,110,110,GREEN);	
	    x++;
		if(x==12)x=0;      
		LED0=!LED0;	 
		delay_ms(1000);	
	}
}
