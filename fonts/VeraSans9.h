

/*
 *
 * VeraSans9
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : VeraSans9.h
 * Date                : 23.02.2019
 * Font size in bytes  : 4662
 * Font width          : 10
 * Font height         : 10
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <pgmspace.h>

#ifndef VERASANS9_H
#define VERASANS9_H

#define VERASANS9_WIDTH 10
#define VERASANS9_HEIGHT 10

static uint8_t VeraSans9[] PROGMEM = {
    0x12, 0x36, // size
    0x0A, // width
    0x09, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x02, 0x03, 0x06, 0x05, 0x08, 0x07, 0x01, 0x03, 0x03, 
    0x05, 0x05, 0x02, 0x03, 0x02, 0x03, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x02, 0x02, 0x06, 0x06, 
    0x06, 0x04, 0x08, 0x07, 0x05, 0x06, 0x06, 0x05, 0x05, 0x06, 
    0x07, 0x02, 0x03, 0x06, 0x05, 0x07, 0x06, 0x06, 0x05, 0x06, 
    0x06, 0x05, 0x06, 0x06, 0x07, 0x09, 0x07, 0x06, 0x06, 0x03, 
    0x03, 0x03, 0x04, 0x05, 0x02, 0x05, 0x05, 0x04, 0x05, 0x05, 
    0x04, 0x05, 0x05, 0x02, 0x03, 0x05, 0x02, 0x08, 0x05, 0x05, 
    0x05, 0x05, 0x03, 0x04, 0x03, 0x05, 0x06, 0x08, 0x06, 0x06, 
    0x04, 0x04, 0x01, 0x04, 0x06, 0x05, 
    
    // font data
    0xDE, 0xDE, 0x00, 0x00, // 33
    0x06, 0x00, 0x06, 0x00, 0x00, 0x00, // 34
    0x28, 0xF8, 0x2E, 0xF8, 0x2E, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x98, 0xB4, 0xFE, 0xB4, 0x64, 0x00, 0x00, 0x40, 0x00, 0x00, // 36
    0x0C, 0x12, 0xD2, 0x7C, 0x78, 0x96, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x60, 0xFC, 0x9E, 0xB2, 0x62, 0xE0, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x06, 0x00, // 39
    0x3C, 0xFF, 0x81, 0x00, 0x00, 0x00, // 40
    0x81, 0xFF, 0x3C, 0x00, 0x00, 0x00, // 41
    0x14, 0x18, 0x3E, 0x18, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0xC0, 0xC0, 0x40, 0x00, // 44
    0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // 45
    0xC0, 0xC0, 0x00, 0x00, // 46
    0xC0, 0x38, 0x06, 0x00, 0x00, 0x00, // 47
    0x7C, 0xFE, 0x82, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x82, 0x82, 0xFE, 0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 49
    0xC2, 0xE2, 0xB2, 0x9E, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x82, 0x92, 0x92, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x60, 0x58, 0x44, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0x9E, 0x9E, 0x92, 0xF2, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0x7C, 0xFE, 0x96, 0xF2, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x82, 0xE2, 0x7A, 0x1E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x6C, 0xEE, 0x92, 0xEE, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0x8C, 0x9E, 0xD2, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0xD8, 0xD8, 0x00, 0x00, // 58
    0xD8, 0xD8, 0x40, 0x00, // 59
    0x20, 0x50, 0x50, 0x50, 0xD8, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x88, 0xD8, 0x50, 0x50, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x02, 0xDA, 0xDE, 0x0E, 0x00, 0x00, 0x00, 0x00, // 63
    0x78, 0x84, 0x32, 0x4A, 0x4A, 0xFA, 0x44, 0x38, 0x00, 0x00, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, // 64
    0x80, 0xF0, 0x7E, 0x26, 0x7E, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xFE, 0xFE, 0x92, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0x38, 0x7C, 0xC6, 0x82, 0x82, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xFE, 0xFE, 0x82, 0xC2, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xFE, 0xFE, 0x92, 0x92, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, // 69
    0xFE, 0xFE, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0x38, 0xFC, 0x86, 0x92, 0xF2, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xFE, 0xFE, 0x10, 0x10, 0x10, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0xFE, 0xFE, 0x00, 0x00, // 73
    0x00, 0xFE, 0xFE, 0x80, 0xC0, 0x40, // 74
    0xFE, 0xFE, 0x38, 0x6C, 0xC6, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xFE, 0xFE, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 76
    0xFE, 0xFE, 0x0C, 0x30, 0x0C, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xFE, 0xFE, 0x0C, 0x30, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0x7C, 0xFE, 0x82, 0x82, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xFE, 0xFE, 0x12, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0x7C, 0xFE, 0x82, 0x82, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, // 81
    0xFE, 0xFE, 0x12, 0x7E, 0xEC, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0xCC, 0x9E, 0x92, 0xF2, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x02, 0x02, 0xFE, 0xFE, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0x7E, 0xFE, 0x80, 0x80, 0xFE, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x02, 0x1E, 0xF8, 0xC0, 0xF8, 0x1E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0x0E, 0xFE, 0xE0, 0x3C, 0x06, 0x3C, 0xE0, 0xFE, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x82, 0xC6, 0x7C, 0x10, 0x7C, 0xC6, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x06, 0x0E, 0xF8, 0xF8, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0xC2, 0xE2, 0xB2, 0x9A, 0x8E, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    0xFF, 0xFF, 0x81, 0x00, 0x00, 0x00, // 91
    0x06, 0x38, 0xC0, 0x00, 0x00, 0x00, // 92
    0x81, 0xFF, 0xFF, 0x00, 0x00, 0x00, // 93
    0x04, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x01, 0x02, 0x00, 0x00, // 96
    0xE8, 0xE8, 0xA8, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0xFF, 0xFF, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, // 98
    0x70, 0xF8, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, // 99
    0x70, 0xF8, 0x88, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, // 100
    0x70, 0xF8, 0xA8, 0xB8, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0x08, 0xFE, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, // 102
    0x70, 0xF8, 0x88, 0xF8, 0xF8, 0x00, 0x80, 0x80, 0xC0, 0x40, // 103
    0xFF, 0xFF, 0x08, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, // 104
    0xFB, 0xFB, 0x00, 0x00, // 105
    0x00, 0xFB, 0xFB, 0x80, 0xC0, 0x40, // 106
    0xFF, 0xFF, 0x70, 0xD8, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, // 107
    0xFF, 0xFF, 0x00, 0x00, // 108
    0xF8, 0xF8, 0x08, 0xF8, 0xF8, 0x08, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0xF8, 0xF8, 0x08, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x70, 0xF8, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0xF8, 0xF8, 0x88, 0xF8, 0x70, 0xC0, 0xC0, 0x00, 0x00, 0x00, // 112
    0x70, 0xF8, 0x88, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0xC0, 0xC0, // 113
    0xF8, 0xF8, 0x08, 0x00, 0x00, 0x00, // 114
    0xB0, 0xB8, 0xE8, 0x68, 0x00, 0x00, 0x00, 0x00, // 115
    0xFC, 0xFC, 0x88, 0x00, 0x00, 0x00, // 116
    0xF8, 0xF8, 0x80, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0x18, 0x78, 0xC0, 0xC0, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0x18, 0xF8, 0xE0, 0x38, 0x38, 0xE0, 0xF8, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0x88, 0xD8, 0x70, 0x70, 0xD8, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0x08, 0x38, 0xE0, 0xE0, 0x38, 0x08, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x00, // 121
    0xC8, 0xE8, 0xB8, 0x98, 0x00, 0x00, 0x00, 0x00, // 122
    0x08, 0xFF, 0xF7, 0x81, 0x00, 0x00, 0x00, 0x00, // 123
    0xFE, 0xC0, // 124
    0x81, 0xF7, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, // 125
    0x20, 0x10, 0x10, 0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFC, 0x04, 0x04, 0x04, 0xFC, 0xC0, 0x80, 0x80, 0x80, 0xC0 // 127
    
};

#endif
