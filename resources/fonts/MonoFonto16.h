

/*
 *
 * new Font
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : MonoFonto16
 * Date                : 01.06.2019
 * Font size in bytes  : 9775
 * Font width          : 10
 * Font height         : 17
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
#include "common/pgmspace.h"

#ifndef MONOFONTO_H
#define MONOFONTO_H

#define MONOFONTO_WIDTH 10
#define MONOFONTO_HEIGHT 17

static uint8_t MonoFonto16[] PROGMEM = {
    0x26, 0x2F, // size
    0x0A, // width
    0x11, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x02, 0x04, 0x08, 0x06, 0x08, 0x08, 0x02, 0x04, 0x04, 
    0x08, 0x08, 0x02, 0x04, 0x02, 0x08, 0x06, 0x03, 0x06, 0x06, 
    0x07, 0x06, 0x06, 0x07, 0x06, 0x06, 0x02, 0x02, 0x08, 0x08, 
    0x08, 0x06, 0x08, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x07, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 
    0x07, 0x06, 0x08, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08, 0x03, 
    0x08, 0x03, 0x06, 0x08, 0x04, 0x06, 0x06, 0x06, 0x06, 0x08, 
    0x06, 0x06, 0x06, 0x06, 0x05, 0x06, 0x03, 0x08, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x08, 0x08, 0x06, 0x08, 
    0x06, 0x04, 0x02, 0x04, 0x08, 0x07, 
    
    // font data
    0xF8, 0xF8, 0x3B, 0x3B, 0x00, 0x00, // 33
    0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0x40, 0xC0, 0x78, 0x48, 0xE0, 0x78, 0x40, 0x04, 0x3E, 0x0F, 0x06, 0x3E, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0xF0, 0xF8, 0x8E, 0x8E, 0x18, 0x18, 0x30, 0x31, 0xE3, 0xE3, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
    0xF8, 0x88, 0xF8, 0x00, 0x80, 0xE0, 0x98, 0x88, 0x20, 0x30, 0x0C, 0x03, 0x01, 0x3F, 0x20, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x00, 0x70, 0xF8, 0x98, 0xF8, 0x70, 0x00, 0x00, 0x0C, 0x3E, 0x33, 0x33, 0x3E, 0x1C, 0x36, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x78, 0x78, 0x00, 0x00, 0x00, 0x00, // 39
    0x00, 0xF0, 0x3E, 0x04, 0x03, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x80, 0x80, // 40
    0x04, 0x3E, 0xF8, 0x00, 0x00, 0xE0, 0x7F, 0x03, 0x80, 0x80, 0x00, 0x00, // 41
    0x60, 0x60, 0x40, 0xF8, 0xF8, 0x40, 0x60, 0x60, 0x00, 0x02, 0x03, 0x01, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x80, 0x80, 0x80, 0xE0, 0xE0, 0x80, 0x80, 0x80, 0x01, 0x01, 0x01, 0x0F, 0x0F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0xF0, 0x30, 0x00, 0x00, // 44
    0x80, 0x80, 0x80, 0x80, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0x38, 0x38, 0x00, 0x00, // 46
    0x00, 0x00, 0x00, 0x00, 0x80, 0xF0, 0x1C, 0x04, 0x00, 0xC0, 0x78, 0x0E, 0x03, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 47
    0xF0, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x1F, 0x3F, 0x30, 0x30, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x70, 0xF8, 0xFC, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, // 49
    0x30, 0x38, 0x18, 0x18, 0xF8, 0xF0, 0x20, 0x38, 0x3C, 0x3F, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x30, 0x38, 0x18, 0x18, 0xF8, 0xF0, 0x18, 0x38, 0x30, 0x31, 0x3F, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x00, 0xC0, 0x70, 0x18, 0xF8, 0x00, 0x00, 0x0F, 0x0D, 0x0C, 0x3C, 0x3F, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0xF8, 0xF8, 0x98, 0x98, 0x98, 0x18, 0x13, 0x3B, 0x31, 0x31, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0x00, 0xC0, 0xF0, 0xB8, 0x88, 0x00, 0x1F, 0x3F, 0x31, 0x31, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x18, 0x18, 0x18, 0xD8, 0xF8, 0x38, 0x08, 0x20, 0x38, 0x3F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x70, 0xF8, 0x98, 0x98, 0xF8, 0x70, 0x1F, 0x3B, 0x31, 0x31, 0x3B, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0xF0, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x01, 0x23, 0x3B, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0xC0, 0xC0, 0x39, 0x39, 0x00, 0x00, // 58
    0xC0, 0xC0, 0xF1, 0x31, 0x00, 0x00, // 59
    0x00, 0x80, 0x80, 0x40, 0x40, 0x60, 0x20, 0x30, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x30, 0x20, 0x60, 0x40, 0xC0, 0x80, 0x80, 0x00, 0x18, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x30, 0x38, 0x18, 0x98, 0xF8, 0x70, 0x00, 0x00, 0x3B, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 63
    0x00, 0xC0, 0x60, 0x20, 0x20, 0x20, 0x40, 0x80, 0x1F, 0x71, 0xC0, 0x9E, 0x12, 0x1E, 0x10, 0x0F, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, // 64
    0x00, 0xE0, 0xF8, 0xF8, 0xE0, 0x00, 0x3C, 0x3F, 0x0D, 0x0F, 0x3F, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xF8, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x3F, 0x3F, 0x31, 0x31, 0x3E, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0xF0, 0xF8, 0x18, 0x18, 0x38, 0x30, 0x1F, 0x3F, 0x30, 0x30, 0x38, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xF8, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x3F, 0x3F, 0x30, 0x30, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xF8, 0xF8, 0x98, 0x98, 0x98, 0x18, 0x3F, 0x3F, 0x31, 0x31, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 69
    0xF8, 0xF8, 0x98, 0x98, 0x98, 0x18, 0x3F, 0x3F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0xF0, 0xF8, 0x18, 0x98, 0xB8, 0xB0, 0x1F, 0x3F, 0x30, 0x31, 0x1F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xF8, 0xF8, 0x80, 0x80, 0xF8, 0xF8, 0x3F, 0x3F, 0x01, 0x01, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x30, 0x30, 0x3F, 0x3F, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 73
    0x00, 0x00, 0x00, 0x18, 0xF8, 0xF8, 0x30, 0x30, 0x30, 0x30, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 74
    0xF8, 0xF8, 0x80, 0xE0, 0x78, 0x18, 0x00, 0x3F, 0x3F, 0x03, 0x0F, 0x3C, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 76
    0xF8, 0xF8, 0xC0, 0xC0, 0xF8, 0xF8, 0x3F, 0x00, 0x07, 0x0F, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xF8, 0xF8, 0xF0, 0x80, 0xF8, 0xF8, 0x3F, 0x3F, 0x03, 0x0F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0xF0, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x1F, 0x3F, 0x30, 0x30, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xF8, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x40, 0x3F, 0x3F, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0xF0, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x1F, 0x3F, 0x30, 0x70, 0xFF, 0x9F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 81
    0xF8, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0x00, 0x3F, 0x3F, 0x07, 0x1F, 0x3D, 0x31, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0xF0, 0xF8, 0x98, 0x98, 0x38, 0x30, 0x18, 0x39, 0x31, 0x33, 0x3F, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0xF8, 0xF8, 0x00, 0x00, 0xF8, 0xF8, 0x1F, 0x3F, 0x30, 0x30, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x08, 0xF8, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x08, 0x00, 0x00, 0x0F, 0x3F, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0x38, 0xF8, 0xC0, 0x80, 0xE0, 0xC0, 0xF8, 0x38, 0x00, 0x1F, 0x3F, 0x0F, 0x0F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x08, 0x18, 0xF8, 0xE0, 0xE0, 0xF8, 0x18, 0x08, 0x20, 0x30, 0x3E, 0x0F, 0x0F, 0x3E, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x08, 0x38, 0xF8, 0xC0, 0xC0, 0xF8, 0x38, 0x08, 0x00, 0x00, 0x01, 0x3F, 0x3F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0x00, 0x18, 0x18, 0x98, 0xF8, 0xF8, 0x18, 0x08, 0x20, 0x38, 0x3E, 0x3F, 0x33, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    0xFE, 0xFE, 0x06, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, // 91
    0x04, 0x1C, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0E, 0x78, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, // 92
    0x06, 0xFE, 0xFE, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0x80, // 93
    0xC0, 0x70, 0x18, 0x18, 0x70, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x08, 0x18, 0x38, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96
    0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x1C, 0x3E, 0x36, 0x36, 0x0F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0xF8, 0xF8, 0x80, 0xC0, 0xC0, 0x80, 0x3F, 0x3F, 0x10, 0x30, 0x39, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 98
    0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x1F, 0x3F, 0x30, 0x30, 0x30, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 99
    0x80, 0xC0, 0xC0, 0x80, 0xF8, 0xF8, 0x1F, 0x3F, 0x30, 0x10, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 100
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x04, 0x1F, 0x3F, 0x32, 0x32, 0x3B, 0x13, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0xC0, 0xF0, 0xF8, 0xD8, 0xD8, 0x18, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 102
    0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDF, 0xBF, 0xB0, 0xB0, 0xFF, 0xFF, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, // 103
    0xF8, 0xF8, 0x80, 0xC0, 0xC0, 0xC0, 0x3F, 0x3F, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 104
    0xC0, 0xC0, 0xD8, 0xD8, 0x00, 0x00, 0x30, 0x30, 0x3F, 0x3F, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 105
    0x00, 0xC0, 0xC0, 0xD8, 0xD8, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x00, // 106
    0xF8, 0xF8, 0x00, 0x80, 0xC0, 0x40, 0x3F, 0x3F, 0x07, 0x1F, 0x38, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 107
    0x18, 0xF8, 0xF8, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, // 108
    0xC0, 0xC0, 0x80, 0xC0, 0x80, 0xC0, 0xC0, 0x80, 0x3F, 0x3F, 0x00, 0x3F, 0x3F, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0x3F, 0x3F, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x1F, 0x3F, 0x30, 0x30, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0xC0, 0x00, 0xC0, 0xC0, 0xC0, 0x80, 0xFF, 0x09, 0x30, 0x30, 0x3F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 112
    0x80, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0x1F, 0x3F, 0x30, 0x10, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, // 113
    0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0x80, 0x3F, 0x3F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 114
    0x80, 0xC0, 0x40, 0x40, 0xC0, 0x80, 0x11, 0x33, 0x26, 0x26, 0x3E, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 115
    0xC0, 0xC0, 0xF0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x3F, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 116
    0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0x1F, 0x3F, 0x30, 0x30, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0x40, 0xC0, 0xC0, 0x00, 0x00, 0x80, 0xC0, 0x40, 0x00, 0x01, 0x1F, 0x3E, 0x3C, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0x40, 0xC0, 0x80, 0x00, 0xC0, 0x00, 0xC0, 0x40, 0x00, 0x0F, 0x3F, 0x1F, 0x1F, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0x40, 0xC0, 0x00, 0x00, 0xC0, 0x40, 0x30, 0x39, 0x0F, 0x0F, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0x40, 0xC0, 0xC0, 0x00, 0x00, 0x80, 0xC0, 0x40, 0x00, 0x01, 0x1F, 0xFE, 0xFC, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, // 121
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x40, 0x30, 0x38, 0x3E, 0x37, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 122
    0x00, 0xFC, 0xFE, 0x06, 0x03, 0xFF, 0xFC, 0x80, 0x00, 0x00, 0x80, 0x80, // 123
    0xFC, 0xFC, 0xFF, 0xFF, 0x80, 0x80, // 124
    0x06, 0xFE, 0xFC, 0x00, 0x80, 0xFC, 0xFF, 0x03, 0x80, 0x80, 0x00, 0x00, // 125
    0x80, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFF, 0xE3, 0x73, 0x33, 0x03, 0x87, 0xFC, 0xFF, 0xFF, 0xC6, 0xCE, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 127
    
};

#endif
