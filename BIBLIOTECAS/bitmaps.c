#include "bitmaps.h"
#include "pico/stdlib.h"

const uint8_t mensagem_sem_calibrar[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x1e, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0xf0, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x90, 0xe0, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x90, 0xe0, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x10, 0xe0, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x30, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x12, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0xf0, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x90, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x90, 0xe0, 0xe1, 0x01, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0xe1, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0xe0, 0xe1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0xe0, 0xe1, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0xe0, 0xe1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe1, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0xe0, 0xe1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0xe0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x90, 0xe0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x10, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x30, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0x90, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0x90, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0x90, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0xf0, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0x90, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0xfe, 0xe0, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0x80, 0xe0, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 
	0x80, 0xe0, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0x00, 0xe0, 0xc1, 0x03, 0xe0, 0xff, 0xff, 0xff, 
	0xfa, 0xe0, 0xc1, 0x03, 0xe0, 0x03, 0x0f, 0xf0, 0x00, 0xe0, 0xc1, 0x03, 0xe0, 0x01, 0x0f, 0xf0, 
	0x00, 0xe0, 0xc1, 0x03, 0xe0, 0x01, 0x0f, 0xf0, 0xfe, 0xe0, 0xc1, 0x03, 0xe0, 0x01, 0x0f, 0xf0, 
	0x90, 0xe0, 0xc1, 0x03, 0xe0, 0x81, 0x0f, 0xf0, 0x90, 0xe0, 0xe1, 0x07, 0xe0, 0x81, 0x0f, 0xf0, 
	0x90, 0xe0, 0xf1, 0x0f, 0xe0, 0x81, 0x0f, 0xf0, 0xf0, 0xe0, 0xff, 0xff, 0xe7, 0x81, 0x0f, 0xf0, 
	0x00, 0xe0, 0xff, 0xff, 0xe7, 0xc1, 0x0f, 0xf0, 0xf0, 0xe0, 0xff, 0xff, 0xe7, 0xc1, 0x0f, 0xf0, 
	0x10, 0xc0, 0x3f, 0xfe, 0xe7, 0xc1, 0x0f, 0xf0, 0x30, 0x00, 0x00, 0x00, 0xe0, 0xc1, 0x1f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xe1, 0x1f, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0xe0, 0xfb, 0x3f, 0xfc, 
	0xa8, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xa8, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 
	0x00, 0xe0, 0x01, 0x00, 0xe0, 0xff, 0xfc, 0x7f, 0x00, 0xe0, 0x01, 0x00, 0xc0, 0x7f, 0xf8, 0x3f, 
	0x00, 0xe0, 0x01, 0x00, 0x00, 0x3f, 0xe0, 0x1f, 0xf0, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x90, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xf0, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x9c, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xac, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0xa4, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xac, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xec, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0xfc, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x04, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x04, 0xe0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0xfc, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0xa4, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0xa4, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0xfc, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0x04, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0xfc, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 0xfc, 0xe0, 0xc1, 0x83, 0x07, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};