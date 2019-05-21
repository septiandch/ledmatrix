
/*
 *
 * Arial_Black_16_ISO_8859_1
 *
 * Font containing all characters of the ISO-8859-1 (aka. ISO Latin-1) charset.
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Arial_Black_16_ISO_8859_1.h
 * Date                : 04.10.2014
 * Font size in bytes  : 25654
 * Font width          : 10
 * Font height         : 16
 * Font first char     : 32
 * Font last char      : 256
 * Font used chars     : 224
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

#ifndef ARIAL_BLACK_16_H
#define ARIAL_BLACK_16_H

#define ARIAL_BLACK_16_WIDTH 10
#define ARIAL_BLACK_16_HEIGHT 16

static const unsigned char Arial16[] PROGMEM = {
    0x64, 0x36, // size
    0x0A, // width
    0x10, // height
    0x20, // first char
    0xE0, // char count
    
    // char widths
    0x00, 0x03, 0x07, 0x08, 0x07, 0x0B, 0x0A, 0x03, 0x04, 0x04, 
    0x05, 0x06, 0x03, 0x04, 0x03, 0x04, 0x07, 0x06, 0x07, 0x07, 
    0x09, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x07, 0x07, 
    0x07, 0x07, 0x0A, 0x09, 0x08, 0x08, 0x08, 0x07, 0x07, 0x09, 
    0x09, 0x03, 0x08, 0x0A, 0x07, 0x0A, 0x09, 0x09, 0x07, 0x09, 
    0x09, 0x07, 0x09, 0x09, 0x09, 0x0D, 0x09, 0x0A, 0x07, 0x05, 
    0x04, 0x05, 0x06, 0x07, 0x03, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x05, 0x08, 0x08, 0x03, 0x03, 0x09, 0x03, 0x0B, 0x08, 0x08, 
    0x08, 0x08, 0x06, 0x07, 0x06, 0x08, 0x08, 0x0C, 0x09, 0x08, 
    0x06, 0x04, 0x02, 0x04, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x03, 
    0x08, 0x07, 0x08, 0x09, 0x02, 0x08, 0x04, 0x0A, 0x05, 0x07, 
    0x07, 0x04, 0x0A, 0x07, 0x03, 0x06, 0x05, 0x05, 0x03, 0x08, 
    0x09, 0x00, 0x04, 0x03, 0x05, 0x07, 0x0C, 0x0C, 0x0D, 0x07, 
    0x09, 0x09, 0x09, 0x09, 0x09, 0x0A, 0x0C, 0x08, 0x07, 0x07, 
    0x07, 0x07, 0x03, 0x04, 0x05, 0x05, 0x09, 0x09, 0x09, 0x09, 
    0x09, 0x09, 0x09, 0x07, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0A, 
    0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x03, 0x04, 0x04, 0x04, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 
    
    // font data
    0xF8, 0xF8, 0xF8, 0x1D, 0x1D, 0x1D, // 33
    0x38, 0x38, 0x38, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x60, 0x60, 0xE0, 0xF8, 0x78, 0xE0, 0xF8, 0x78, 0x06, 0x1E, 0x1F, 0x07, 0x1E, 0x1F, 0x07, 0x06, // 35
    0x70, 0xF8, 0x98, 0xFC, 0x98, 0xB8, 0x30, 0x0C, 0x1C, 0x19, 0x3F, 0x19, 0x1F, 0x0F, // 36
    0x70, 0xF8, 0x88, 0xF8, 0x70, 0x80, 0x60, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0C, 0x02, 0x01, 0x0E, 0x1F, 0x11, 0x1F, 0x0E, // 37
    0x00, 0x70, 0xF8, 0xD8, 0xD8, 0x78, 0x30, 0x00, 0x00, 0x00, 0x0E, 0x1F, 0x1F, 0x19, 0x1B, 0x1F, 0x1F, 0x0E, 0x0F, 0x1F, // 38
    0x38, 0x38, 0x38, 0x00, 0x00, 0x00, // 39
    0x80, 0xE0, 0x70, 0x10, 0x1F, 0x7F, 0xE0, 0x80, // 40
    0x10, 0x70, 0xE0, 0x80, 0x80, 0xE0, 0x7F, 0x1F, // 41
    0x10, 0x50, 0x38, 0x50, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x80, 0x80, 0xE0, 0xE0, 0x80, 0x80, 0x01, 0x01, 0x07, 0x07, 0x01, 0x01, // 43
    0x00, 0x00, 0x00, 0xDC, 0x7C, 0x3C, // 44
    0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, // 45
    0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, // 46
    0x00, 0x00, 0xE0, 0x18, 0x18, 0x07, 0x00, 0x00, // 47
    0xE0, 0xF0, 0xF8, 0x18, 0xF8, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x18, 0x1F, 0x0F, 0x07, // 48
    0xC0, 0xC0, 0x60, 0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, // 49
    0x30, 0x38, 0x38, 0x18, 0xF8, 0xF0, 0xE0, 0x18, 0x1C, 0x1E, 0x1F, 0x1B, 0x19, 0x18, // 50
    0x30, 0x38, 0x38, 0x98, 0xF8, 0xF0, 0x60, 0x0C, 0x1C, 0x1C, 0x19, 0x1F, 0x0F, 0x06, // 51
    0x00, 0x80, 0xC0, 0x60, 0x30, 0xF8, 0xF8, 0xF8, 0x00, 0x07, 0x07, 0x07, 0x06, 0x06, 0x1F, 0x1F, 0x1F, 0x00, // 52
    0xC0, 0xF8, 0xF8, 0xD8, 0xD8, 0xD8, 0x98, 0x0C, 0x1D, 0x1C, 0x18, 0x1F, 0x0F, 0x07, // 53
    0xE0, 0xF0, 0xF8, 0x18, 0xB8, 0xB8, 0x30, 0x07, 0x0F, 0x1F, 0x19, 0x1F, 0x1F, 0x0F, // 54
    0x18, 0x18, 0x18, 0xD8, 0xF8, 0x78, 0x18, 0x00, 0x1C, 0x1F, 0x1F, 0x03, 0x00, 0x00, // 55
    0x70, 0xF8, 0xF8, 0x98, 0xF8, 0xF8, 0x70, 0x0E, 0x1F, 0x1F, 0x19, 0x1F, 0x1F, 0x0E, // 56
    0xF0, 0xF8, 0xF8, 0x98, 0xF8, 0xF0, 0xE0, 0x0C, 0x1D, 0x1D, 0x18, 0x1F, 0x0F, 0x07, // 57
    0xC0, 0xC0, 0xC0, 0x1D, 0x1D, 0x1D, // 58
    0xC0, 0xC0, 0xC0, 0xDD, 0x7D, 0x3D, // 59
    0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x60, 0x03, 0x03, 0x03, 0x06, 0x06, 0x06, 0x0C, // 60
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, // 61
    0x60, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x0C, 0x06, 0x06, 0x06, 0x03, 0x03, 0x03, // 62
    0x30, 0x38, 0x18, 0x98, 0xF8, 0xF8, 0x70, 0x00, 0x00, 0x1B, 0x1B, 0x1B, 0x00, 0x00, // 63
    0xC0, 0x20, 0x90, 0xC8, 0x28, 0xC8, 0xE8, 0xE8, 0x10, 0xE0, 0x07, 0x08, 0x17, 0x2F, 0x28, 0x2F, 0x2F, 0x28, 0x14, 0x13, // 64
    0x00, 0xE0, 0xF8, 0xF8, 0x38, 0xF8, 0xF8, 0xE0, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x06, 0x07, 0x1F, 0x1F, 0x1C, // 65
    0xF8, 0xF8, 0xF8, 0x98, 0x98, 0xF8, 0xF8, 0x70, 0x1F, 0x1F, 0x1F, 0x19, 0x19, 0x1F, 0x1F, 0x0E, // 66
    0xE0, 0xF0, 0xF8, 0x18, 0x18, 0x38, 0x30, 0x20, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1E, 0x0E, 0x04, // 67
    0xF8, 0xF8, 0xF8, 0x18, 0x18, 0xF8, 0xF0, 0xE0, 0x1F, 0x1F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 68
    0xF8, 0xF8, 0xF8, 0x98, 0x98, 0x98, 0x98, 0x1F, 0x1F, 0x1F, 0x19, 0x19, 0x19, 0x19, // 69
    0xF8, 0xF8, 0xF8, 0x98, 0x98, 0x98, 0x18, 0x1F, 0x1F, 0x1F, 0x01, 0x01, 0x01, 0x00, // 70
    0xC0, 0xF0, 0xF8, 0x38, 0x18, 0x98, 0xB8, 0xB8, 0xB0, 0x07, 0x0F, 0x1F, 0x1C, 0x18, 0x19, 0x1F, 0x0F, 0x0F, // 71
    0xF8, 0xF8, 0xF8, 0x80, 0x80, 0x80, 0xF8, 0xF8, 0xF8, 0x1F, 0x1F, 0x1F, 0x01, 0x01, 0x01, 0x1F, 0x1F, 0x1F, // 72
    0xF8, 0xF8, 0xF8, 0x1F, 0x1F, 0x1F, // 73
    0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0x06, 0x0E, 0x1E, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 74
    0xF8, 0xF8, 0xF8, 0xC0, 0xE0, 0xF0, 0xB8, 0x18, 0x08, 0x00, 0x1F, 0x1F, 0x1F, 0x01, 0x00, 0x03, 0x0F, 0x1F, 0x1C, 0x10, // 75
    0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x18, 0x18, 0x18, 0x18, // 76
    0xF8, 0xF8, 0x78, 0xE0, 0x00, 0x00, 0xE0, 0x78, 0xF8, 0xF8, 0x1F, 0x1F, 0x00, 0x03, 0x1F, 0x1F, 0x03, 0x00, 0x1F, 0x1F, // 77
    0xF8, 0xF8, 0x70, 0xE0, 0xC0, 0x80, 0x00, 0xF8, 0xF8, 0x1F, 0x1F, 0x00, 0x01, 0x03, 0x07, 0x0E, 0x1F, 0x1F, // 78
    0xE0, 0xF0, 0xF8, 0x38, 0x18, 0x38, 0xF8, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0F, 0x07, // 79
    0xF8, 0xF8, 0xF8, 0x98, 0xF8, 0xF8, 0xF0, 0x1F, 0x1F, 0x1F, 0x01, 0x01, 0x01, 0x00, // 80
    0xE0, 0xF0, 0xF8, 0x18, 0x18, 0x38, 0xF8, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x18, 0x1E, 0x1C, 0x1F, 0x1F, 0x37, // 81
    0xF8, 0xF8, 0xF8, 0x98, 0x98, 0xF8, 0xF8, 0xF0, 0x00, 0x1F, 0x1F, 0x1F, 0x01, 0x03, 0x0F, 0x1E, 0x1C, 0x10, // 82
    0x70, 0xF8, 0xF8, 0x98, 0x98, 0xB8, 0x30, 0x0C, 0x1C, 0x19, 0x19, 0x1F, 0x1F, 0x0F, // 83
    0x18, 0x18, 0x18, 0xF8, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 84
    0xF8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 85
    0x18, 0xF8, 0xF8, 0xE0, 0x00, 0xE0, 0xF8, 0xF8, 0x18, 0x00, 0x00, 0x07, 0x1F, 0x1C, 0x1F, 0x07, 0x00, 0x00, // 86
    0x18, 0xF8, 0xF8, 0x00, 0xC0, 0xF8, 0x78, 0xF8, 0xC0, 0x00, 0xF8, 0xF8, 0x18, 0x00, 0x03, 0x1F, 0x1F, 0x1F, 0x07, 0x00, 0x07, 0x1F, 0x1F, 0x1F, 0x03, 0x00, // 87
    0x08, 0x38, 0x78, 0xF0, 0xC0, 0xF0, 0x78, 0x38, 0x08, 0x10, 0x1C, 0x1F, 0x0F, 0x03, 0x0F, 0x1F, 0x1C, 0x10, // 88
    0x08, 0x18, 0x78, 0xF0, 0xE0, 0x80, 0xE0, 0xF0, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 89
    0x18, 0x18, 0x18, 0x98, 0xF8, 0x78, 0x38, 0x1C, 0x1E, 0x1F, 0x19, 0x18, 0x18, 0x18, // 90
    0xF0, 0xF0, 0xF0, 0x30, 0x30, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, // 91
    0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18, // 92
    0x30, 0x30, 0xF0, 0xF0, 0xF0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, // 93
    0x80, 0xE0, 0x38, 0x38, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // 95
    0x08, 0x18, 0x10, 0x00, 0x00, 0x00, // 96
    0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x0A, 0x1F, 0x1F, 0x1F, // 97
    0xF8, 0xF8, 0xF8, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x1F, 0x1F, 0x1F, 0x08, 0x18, 0x1F, 0x1F, 0x0F, // 98
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1D, 0x0D, 0x05, // 99
    0x80, 0xC0, 0xC0, 0xC0, 0x80, 0xF8, 0xF8, 0xF8, 0x0F, 0x1F, 0x1F, 0x18, 0x08, 0x1F, 0x1F, 0x1F, // 100
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x1A, 0x1A, 0x1B, 0x1B, 0x0B, // 101
    0xF0, 0xF8, 0xF8, 0xC8, 0x08, 0x1F, 0x1F, 0x1F, 0x00, 0x00, // 102
    0x80, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0x4F, 0xDF, 0xDF, 0xD8, 0xC8, 0xFF, 0xFF, 0x7F, // 103
    0xF8, 0xF8, 0xF8, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x1F, // 104
    0xD8, 0xD8, 0xD8, 0x1F, 0x1F, 0x1F, // 105
    0xD8, 0xD8, 0xD8, 0xFF, 0xFF, 0x7F, // 106
    0xF8, 0xF8, 0xF8, 0x00, 0x80, 0xC0, 0xC0, 0x40, 0x00, 0x1F, 0x1F, 0x1F, 0x07, 0x07, 0x0F, 0x1E, 0x18, 0x10, // 107
    0xF8, 0xF8, 0xF8, 0x1F, 0x1F, 0x1F, // 108
    0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x1F, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x1F, // 109
    0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x1F, // 110
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 111
    0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0xFF, 0xFF, 0xFF, 0x08, 0x18, 0x1F, 0x1F, 0x0F, // 112
    0x80, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0x0F, 0x1F, 0x1F, 0x18, 0x08, 0xFF, 0xFF, 0xFF, // 113
    0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0x40, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 114
    0x80, 0xC0, 0xC0, 0x40, 0x40, 0xC0, 0x80, 0x09, 0x1B, 0x13, 0x17, 0x1E, 0x1E, 0x0C, // 115
    0xC0, 0xF0, 0xF0, 0xF8, 0xC0, 0x00, 0x00, 0x0F, 0x1F, 0x1F, 0x18, 0x18, // 116
    0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x0F, 0x1F, 0x1F, 0x18, 0x08, 0x1F, 0x1F, 0x1F, // 117
    0xC0, 0xC0, 0x80, 0x00, 0x80, 0xC0, 0xC0, 0x40, 0x01, 0x07, 0x1F, 0x1C, 0x1F, 0x07, 0x01, 0x00, // 118
    0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0x40, 0x03, 0x1F, 0x1F, 0x1C, 0x07, 0x01, 0x07, 0x1C, 0x1F, 0x1F, 0x03, 0x00, // 119
    0x40, 0xC0, 0xC0, 0x80, 0x00, 0x80, 0xC0, 0xC0, 0x40, 0x10, 0x18, 0x1F, 0x0F, 0x07, 0x0F, 0x1F, 0x18, 0x10, // 120
    0xC0, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x40, 0xC3, 0xCF, 0xFF, 0xF8, 0x7F, 0x0F, 0x03, 0x00, // 121
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x18, 0x1C, 0x1E, 0x1B, 0x19, 0x18, // 122
    0x00, 0xE0, 0xF0, 0x30, 0x06, 0x7F, 0xF9, 0xC0, // 123
    0xF8, 0xF8, 0xFF, 0xFF, // 124
    0x30, 0xF0, 0xE0, 0x00, 0xC0, 0xF9, 0x7F, 0x06, // 125
    0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, // 126
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 127
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 128
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 129
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 130
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 131
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 132
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 133
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 134
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 135
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 136
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 137
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 138
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 139
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 140
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 141
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 142
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 143
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 144
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 145
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 146
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 147
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 148
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 149
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 150
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 151
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 152
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 153
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 154
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 155
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 156
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 157
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 158
    0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, // 159
    0xC0, 0xC0, 0xC0, 0xFD, 0xFD, 0xFD, // 161
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xF0, 0x80, 0x00, 0x07, 0x0F, 0x7F, 0x1E, 0x19, 0x1D, 0x0D, 0x05, // 162
    0xF0, 0xF8, 0xD8, 0xD8, 0xD8, 0x18, 0x10, 0x1C, 0x0F, 0x0F, 0x0C, 0x18, 0x18, 0x08, // 163
    0x40, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0x40, 0x08, 0x1F, 0x0F, 0x0C, 0x0C, 0x0F, 0x1F, 0x08, // 164
    0x88, 0xB8, 0xF8, 0xF0, 0xC0, 0xF0, 0xF8, 0xB8, 0x88, 0x0D, 0x0D, 0x0D, 0x1F, 0x1F, 0x1F, 0x0D, 0x0D, 0x0D, // 165
    0xF8, 0xF8, 0xF9, 0xF9, // 166
    0x00, 0xF0, 0xF8, 0xF8, 0xD8, 0x98, 0xB8, 0x30, 0x63, 0x67, 0xCF, 0xCE, 0xDD, 0xFF, 0xFF, 0x77, // 167
    0x18, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, // 168
    0xC0, 0x30, 0xD0, 0xE8, 0x28, 0x28, 0x68, 0x50, 0x30, 0xC0, 0x03, 0x0C, 0x0B, 0x17, 0x14, 0x14, 0x16, 0x0A, 0x0C, 0x03, // 169
    0xC8, 0xE8, 0xA8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, // 170
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x02, 0x0F, 0x1D, 0x13, 0x0F, 0x1D, 0x10, // 171
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, // 172
    0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, // 173
    0xC0, 0x30, 0x10, 0xE8, 0xE8, 0x28, 0xE8, 0xD0, 0x30, 0xC0, 0x03, 0x0C, 0x08, 0x17, 0x17, 0x11, 0x17, 0x0C, 0x0C, 0x03, // 174
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 175
    0x38, 0x28, 0x38, 0x00, 0x00, 0x00, // 176
    0xC0, 0xC0, 0xF0, 0xF0, 0xC0, 0xC0, 0x18, 0x18, 0x1B, 0x1B, 0x18, 0x18, // 177
    0x90, 0xD8, 0xE8, 0xB8, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, // 178
    0x90, 0x98, 0xA8, 0xF8, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, // 179
    0x10, 0x18, 0x08, 0x00, 0x00, 0x00, // 180
    0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0x18, 0x18, 0x1F, 0x1F, 0x1F, // 181
    0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0x18, 0xF8, 0xF8, 0x18, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, // 182
    0x00, 0x00, 0x00, 0x00, 0xA0, 0xA0, 0xE0, 0xE0, // 184
    0x10, 0xF8, 0xF8, 0x00, 0x00, 0x00, // 185
    0x70, 0xF8, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, // 186
    0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x10, 0x1D, 0x0F, 0x12, 0x1C, 0x0F, 0x02, // 187
    0x10, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x80, 0x60, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x01, 0x00, 0x0C, 0x0E, 0x0A, 0x1F, 0x1F, // 188
    0x10, 0xF8, 0xF8, 0x00, 0x00, 0x80, 0x60, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x01, 0x00, 0x00, 0x12, 0x1B, 0x1D, 0x17, 0x16, // 189
    0x90, 0x98, 0xA8, 0xF8, 0x50, 0x00, 0x00, 0x80, 0x60, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x01, 0x00, 0x0C, 0x0E, 0x0A, 0x1F, 0x1F, // 190
    0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x70, 0xF8, 0xFE, 0xCE, 0xC6, 0xE0, 0x60, // 191
    0x00, 0xE0, 0xF8, 0xF9, 0x3B, 0xFA, 0xF8, 0xE0, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x06, 0x07, 0x1F, 0x1F, 0x1C, // 192
    0x00, 0xE0, 0xF8, 0xF8, 0x3A, 0xFB, 0xF9, 0xE0, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x06, 0x07, 0x1F, 0x1F, 0x1C, // 193
    0x00, 0xE0, 0xFA, 0xFB, 0x39, 0xFB, 0xFA, 0xE0, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x06, 0x07, 0x1F, 0x1F, 0x1C, // 194
    0x00, 0xE0, 0xF8, 0xFB, 0x39, 0xFA, 0xFB, 0xE0, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x06, 0x07, 0x1F, 0x1F, 0x1C, // 195
    0x00, 0xE0, 0xFB, 0xFB, 0x38, 0xFB, 0xFB, 0xE0, 0x00, 0x1C, 0x1F, 0x1F, 0x07, 0x06, 0x07, 0x1F, 0x1F, 0x1C, // 196
    0x00, 0x00, 0xC0, 0xF8, 0xFC, 0x3A, 0xFC, 0xF8, 0xC0, 0x00, 0x10, 0x1E, 0x1F, 0x0F, 0x07, 0x06, 0x06, 0x07, 0x1F, 0x1E, // 197
    0x00, 0x00, 0xC0, 0xF0, 0xF8, 0x18, 0xF8, 0xF8, 0xF8, 0x98, 0x98, 0x98, 0x10, 0x1E, 0x1F, 0x07, 0x06, 0x06, 0x1F, 0x1F, 0x1F, 0x19, 0x19, 0x19, // 198
    0xE0, 0xF0, 0xF8, 0x18, 0x18, 0x38, 0x30, 0x20, 0x07, 0x0F, 0xBF, 0xB8, 0xF8, 0xFE, 0x0E, 0x04, // 199
    0xF8, 0xF8, 0xF9, 0x9B, 0x9A, 0x98, 0x98, 0x1F, 0x1F, 0x1F, 0x19, 0x19, 0x19, 0x19, // 200
    0xF8, 0xF8, 0xF8, 0x9A, 0x9B, 0x99, 0x98, 0x1F, 0x1F, 0x1F, 0x19, 0x19, 0x19, 0x19, // 201
    0xF8, 0xFA, 0xFB, 0x99, 0x9B, 0x9A, 0x98, 0x1F, 0x1F, 0x1F, 0x19, 0x19, 0x19, 0x19, // 202
    0xF8, 0xFB, 0xFB, 0x98, 0x9B, 0x9B, 0x98, 0x1F, 0x1F, 0x1F, 0x19, 0x19, 0x19, 0x19, // 203
    0xF9, 0xFB, 0xFA, 0x1F, 0x1F, 0x1F, // 204
    0xF8, 0xFA, 0xFB, 0x01, 0x1F, 0x1F, 0x1F, 0x00, // 205
    0x02, 0xFB, 0xF9, 0xFB, 0x02, 0x00, 0x1F, 0x1F, 0x1F, 0x00, // 206
    0x03, 0xFB, 0xF8, 0xFB, 0x03, 0x00, 0x1F, 0x1F, 0x1F, 0x00, // 207
    0x80, 0xF8, 0xF8, 0xF8, 0x98, 0x18, 0xF8, 0xF0, 0xE0, 0x00, 0x1F, 0x1F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 208
    0xF8, 0xF8, 0x70, 0xE3, 0xC1, 0x82, 0x03, 0xF8, 0xF8, 0x1F, 0x1F, 0x00, 0x01, 0x03, 0x07, 0x0E, 0x1F, 0x1F, // 209
    0xE0, 0xF0, 0xF8, 0x39, 0x1B, 0x3A, 0xF8, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0F, 0x07, // 210
    0xE0, 0xF0, 0xF8, 0x38, 0x1A, 0x3B, 0xF9, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0F, 0x07, // 211
    0xE0, 0xF0, 0xFA, 0x3B, 0x19, 0x3B, 0xFA, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0F, 0x07, // 212
    0xE0, 0xF0, 0xF8, 0x3B, 0x19, 0x3A, 0xFB, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0F, 0x07, // 213
    0xE0, 0xF0, 0xFB, 0x3B, 0x18, 0x3B, 0xFB, 0xF0, 0xE0, 0x07, 0x0F, 0x1F, 0x1C, 0x18, 0x1C, 0x1F, 0x0F, 0x07, // 214
    0x40, 0xE0, 0xC0, 0x80, 0xC0, 0xE0, 0x40, 0x04, 0x0E, 0x07, 0x03, 0x07, 0x0E, 0x04, // 215
    0xE0, 0xF0, 0xF8, 0x38, 0x98, 0xD8, 0xF8, 0xF0, 0xF8, 0x1F, 0x0F, 0x1F, 0x1B, 0x19, 0x1C, 0x1F, 0x0F, 0x07, // 216
    0xF8, 0xF8, 0xF8, 0x01, 0x03, 0x02, 0xF8, 0xF8, 0xF8, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 217
    0xF8, 0xF8, 0xF8, 0x00, 0x02, 0x03, 0xF9, 0xF8, 0xF8, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 218
    0xF8, 0xF8, 0xFA, 0x03, 0x01, 0x03, 0xFA, 0xF8, 0xF8, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 219
    0xF8, 0xF8, 0xFB, 0x03, 0x00, 0x03, 0xFB, 0xF8, 0xF8, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 220
    0x08, 0x18, 0x78, 0xF0, 0xE0, 0x82, 0xE3, 0xF1, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 221
    0xF8, 0xF8, 0xF8, 0x60, 0xE0, 0xE0, 0xC0, 0x1F, 0x1F, 0x1F, 0x06, 0x07, 0x07, 0x03, // 222
    0xE0, 0xF0, 0xF8, 0x18, 0x98, 0xF8, 0xF8, 0x30, 0x1F, 0x1F, 0x1F, 0x00, 0x19, 0x1B, 0x1F, 0x0E, // 223
    0x80, 0xC0, 0xC8, 0xD8, 0xD0, 0xC0, 0xC0, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x0A, 0x1F, 0x1F, 0x1F, // 224
    0x80, 0xC0, 0xC0, 0xD0, 0xD8, 0xC8, 0xC0, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x0A, 0x1F, 0x1F, 0x1F, // 225
    0x80, 0xC0, 0xD0, 0xD8, 0xC8, 0xD8, 0xD0, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x0A, 0x1F, 0x1F, 0x1F, // 226
    0x80, 0xC0, 0xD8, 0xC8, 0xD0, 0xD8, 0xC0, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x0A, 0x1F, 0x1F, 0x1F, // 227
    0x80, 0xC0, 0xD8, 0xD8, 0xC0, 0xD8, 0xD8, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x0A, 0x1F, 0x1F, 0x1F, // 228
    0x80, 0xC0, 0xC0, 0xDC, 0xD4, 0xDC, 0xC0, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x0A, 0x1F, 0x1F, 0x1F, // 229
    0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x0D, 0x1D, 0x1D, 0x1A, 0x1A, 0x0F, 0x0F, 0x1F, 0x1A, 0x1B, 0x1B, 0x0B, // 230
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x07, 0x0F, 0xBF, 0xB8, 0xF8, 0xFD, 0x0D, 0x05, // 231
    0x00, 0x80, 0xC8, 0xD8, 0xD0, 0xC0, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x1A, 0x1A, 0x1B, 0x1B, 0x0B, // 232
    0x00, 0x80, 0xC0, 0xD0, 0xD8, 0xC8, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x1A, 0x1A, 0x1B, 0x1B, 0x0B, // 233
    0x00, 0x80, 0xD0, 0xD8, 0xC8, 0xD8, 0x90, 0x00, 0x07, 0x0F, 0x1F, 0x1A, 0x1A, 0x1B, 0x1B, 0x0B, // 234
    0x00, 0x80, 0xD8, 0xD8, 0xC0, 0xD8, 0x98, 0x00, 0x07, 0x0F, 0x1F, 0x1A, 0x1A, 0x1B, 0x1B, 0x0B, // 235
    0xC8, 0xD8, 0xD0, 0x1F, 0x1F, 0x1F, // 236
    0xC0, 0xD0, 0xD8, 0x08, 0x1F, 0x1F, 0x1F, 0x00, // 237
    0xD8, 0xC8, 0xD8, 0x10, 0x1F, 0x1F, 0x1F, 0x00, // 238
    0xD8, 0xC0, 0xD8, 0x18, 0x1F, 0x1F, 0x1F, 0x00, // 239
    0x00, 0x80, 0xE0, 0xD8, 0xF8, 0xF8, 0xE8, 0x80, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 240
    0xC0, 0xC0, 0xD8, 0x88, 0xD0, 0xD8, 0xC0, 0x80, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x1F, // 241
    0x00, 0x80, 0xC8, 0xD8, 0xD0, 0xC0, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 242
    0x00, 0x80, 0xC0, 0xD0, 0xD8, 0xC8, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 243
    0x00, 0x80, 0xD0, 0xD8, 0xC8, 0xD8, 0x90, 0x00, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 244
    0x00, 0x80, 0xD8, 0xC8, 0xD0, 0xD8, 0x80, 0x00, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 245
    0x00, 0x80, 0xD8, 0xD8, 0xC0, 0xD8, 0x98, 0x00, 0x07, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x07, // 246
    0x80, 0x80, 0xB8, 0xB8, 0xB8, 0x80, 0x80, 0x01, 0x01, 0x1D, 0x1D, 0x1D, 0x01, 0x01, // 247
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x20, 0x27, 0x1F, 0x1F, 0x1E, 0x19, 0x1F, 0x0F, 0x07, // 248
    0xC0, 0xC0, 0xC8, 0x18, 0x10, 0xC0, 0xC0, 0xC0, 0x0F, 0x1F, 0x1F, 0x18, 0x08, 0x1F, 0x1F, 0x1F, // 249
    0xC0, 0xC0, 0xC0, 0x10, 0x18, 0xC8, 0xC0, 0xC0, 0x0F, 0x1F, 0x1F, 0x18, 0x08, 0x1F, 0x1F, 0x1F, // 250
    0xC0, 0xC0, 0xD0, 0x18, 0x08, 0xD8, 0xD0, 0xC0, 0x0F, 0x1F, 0x1F, 0x18, 0x08, 0x1F, 0x1F, 0x1F, // 251
    0xC0, 0xC0, 0xD8, 0x18, 0x00, 0xD8, 0xD8, 0xC0, 0x0F, 0x1F, 0x1F, 0x18, 0x08, 0x1F, 0x1F, 0x1F, // 252
    0xC0, 0xC0, 0x00, 0x10, 0x18, 0xC8, 0xC0, 0x40, 0xC3, 0xCF, 0xFF, 0xF8, 0x7F, 0x0F, 0x03, 0x00, // 253
    0xF8, 0xF8, 0xF8, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0xFF, 0xFF, 0xFF, 0x08, 0x18, 0x1F, 0x1F, 0x0F, // 254
    0xC0, 0xD8, 0x18, 0x00, 0x18, 0xD8, 0xC0, 0x40, 0xC3, 0xCF, 0xFF, 0xF8, 0x7F, 0x0F, 0x03, 0x00 // 255
    
};

#endif
