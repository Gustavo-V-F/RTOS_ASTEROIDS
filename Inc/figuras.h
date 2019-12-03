#ifndef FIGURAS_H_
#define FIGURAS_H_

#include "NOKIA5110_fb.h"
//504 bytes por figura - 48x84 pixels

const unsigned char background [504] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x03, 0x00, 0x06, 0x1e, 0x1e, 0x1c, 0x0e, 0x3e, 0x7c, 0xf8, 0xf0, 0xc0, 0xc0, 0xc0, 0xe0, 0xf0, 0xf0, 0x78, 0xfc, 0xfc, 0xfc, 0xfd, 0x79, 0x03, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x10, 0xc0, 0xe0, 0xe0, 0xc1, 0x81, 0x03, 0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x03, 0x43, 0x01, 0x10, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf8, 0xd8, 0x7c, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x0f, 0x06, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x06, 0x06, 0x41, 0x00, 0x00, 0x00, 0x41, 0x03, 0x03, 0x01, 0xe0, 0xe0, 0xc0, 0xc0, 0xc6, 0xce, 0x8e, 0x80, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0xbc, 0x9c, 0x1c, 0x0f, 0x0c, 0x01, 0x03, 0x07, 0x07, 0x07, 0x03, 0x01, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0xff, 0xff, 0xff, 0xbb, 0x3b, 0x73, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf8, 0xc0, 0x84, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x80, 0x84, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x00, 0x80, 0x98, 0x80, 0x04, 0x30, 0x31, 0x60, 0xec, 0x40, 0x00, 0x00, 0x00, 0x00, 0x38, 0x80, 0x41, 0x03, 0x01, 0x00, 0x1c, 0x18, 0x18, 0x38, 0x38, 0x18, 0x38, 0x39, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe7, 0x83, 0x83, 0x07, 0xc7, 0xff, 0xff, 0xfe, 0xfe, 0xf0, 0xc0, 0xd2, 0xd8, 0xf8, 0xf0, 0xb1, 0x83, 0x80, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x10, 0x38, 0xf8, 0xf8, 0xb9, 0x03, 0x07, 0x0e, 0x3c, 0x30, 0xe0, 0xd1, 0xfc, 0xfc, 0xfe, 0xfe, 0xf8, 0xf8, 0xf6, 0xfe, 0x34, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xf3, 0x4f, 0x0f, 0x0f, 0x0f, 0x0f, 0x3f, 0x3f, 0x33, 0x17, 0x0f, 0x00, 0x01, 0x00, 0x44, 0xc0, 0x00, 0x00, 0x01, 0x01, 0x00, 0x13, 0xff, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7e, 0xfe, 0xc0, 0x04, 0x01, 0x81, 0x05, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80};

// ---------------------------------------------------------------------------------------
// Os pixeis n�o empregados na definic�o dos bytes DEVEM ser ZERO, ou seja, os pixeis que n�o devem ser impressos
// A figura � desenhada conforme trabalho do LCD, do LSB to MSB (bytes alinhados verticalmente, ver manual do LCD5110)
//-----------------------------------------------------------------------------------------------------------------
#endif /* FIGURAS_H_ */
