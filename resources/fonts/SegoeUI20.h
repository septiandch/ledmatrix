#include <inttypes.h>
#include <common/pgmspace.h>

#ifndef SEGOEUI20_H
#define SEGOEUI20_H

#define SEGOEUI20_H_WIDTH 10
#define SEGOEUI20_H_HEIGHT 21

static const uint8_t SegoeUI20[] PROGMEM =
{
    0x42, 0x84, // size
    0x0A, // width
    0x15, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x02, 0x05, 0x0A, 0x09, 0x0F, 0x0D, 0x02, 0x06, 0x05, 
    0x08, 0x0A, 0x03, 0x06, 0x02, 0x08, 0x09, 0x05, 0x08, 0x08, 
    0x0A, 0x07, 0x09, 0x09, 0x09, 0x09, 0x02, 0x03, 0x08, 0x0A, 
    0x08, 0x07, 0x10, 0x0D, 0x09, 0x0A, 0x0B, 0x07, 0x07, 0x0B, 
    0x0B, 0x02, 0x06, 0x0A, 0x08, 0x0E, 0x0B, 0x0D, 0x09, 0x0D, 
    0x0A, 0x09, 0x0A, 0x0A, 0x0D, 0x13, 0x0C, 0x0C, 0x0C, 0x04, 
    0x08, 0x04, 0x0A, 0x08, 0x04, 0x08, 0x0A, 0x08, 0x09, 0x09, 
    0x07, 0x09, 0x09, 0x03, 0x03, 0x09, 0x02, 0x10, 0x09, 0x0A, 
    0x0A, 0x09, 0x06, 0x07, 0x06, 0x09, 0x0A, 0x0F, 0x0A, 0x0A, 
    0x09, 0x06, 0x02, 0x06, 0x0A, 0x09, 
    
    // font data
    0xFC, 0xFC, 0xE7, 0xE7, 0x00, 0x00, // 33
    0x3C, 0x3C, 0x00, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0x40, 0xC0, 0xFC, 0x5C, 0x40, 0xC0, 0xFC, 0x5C, 0x40, 0x04, 0x74, 0x7F, 0x07, 0x04, 0x74, 0x7F, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0xF0, 0xF8, 0x9C, 0x8C, 0xFF, 0x0C, 0x0C, 0x1C, 0x00, 0x60, 0xC1, 0xC1, 0xC3, 0xFF, 0xC7, 0xE6, 0x7C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, // 36
    0xF0, 0xF8, 0x8C, 0x04, 0x8C, 0xFC, 0x78, 0x00, 0xC0, 0x60, 0x38, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x01, 0x81, 0xC1, 0x71, 0x18, 0x0E, 0x03, 0x79, 0xFC, 0xC6, 0x82, 0xC6, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x00, 0x00, 0x78, 0xFC, 0x8C, 0x8C, 0xCC, 0xFC, 0x78, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7E, 0xE6, 0xC3, 0xC3, 0xC7, 0xCE, 0x7C, 0x78, 0x78, 0xFF, 0xC7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00, // 39
    0x80, 0xE0, 0x70, 0x1C, 0x0C, 0x04, 0x3F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x38, 0x30, 0x00, // 40
    0x04, 0x0C, 0x78, 0xF0, 0x80, 0x00, 0x00, 0xC0, 0xFF, 0x3F, 0x20, 0x30, 0x18, 0x08, 0x00, // 41
    0x10, 0x90, 0xD0, 0x7C, 0x7C, 0xD0, 0x90, 0x10, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x7F, 0x7F, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x38, 0x38, 0x00, // 44
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, // 46
    0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x3C, 0x04, 0x00, 0xC0, 0xF8, 0x3E, 0x07, 0x01, 0x00, 0x00, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 47
    0xE0, 0xF8, 0x38, 0x0C, 0x0C, 0x0C, 0x3C, 0xF8, 0xE0, 0x1F, 0x7F, 0xF0, 0xC0, 0xC0, 0xC0, 0x70, 0x7F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x30, 0x38, 0x18, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, // 49
    0x00, 0x18, 0x0C, 0x0C, 0x0C, 0x1C, 0xF8, 0xF0, 0xE0, 0xF8, 0xD8, 0xCC, 0xC6, 0xC3, 0xC1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x00, 0x08, 0x0C, 0x0C, 0x0C, 0x9C, 0xF8, 0x70, 0xE0, 0xC3, 0xC3, 0xC3, 0xC3, 0xE7, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x00, 0x00, 0x00, 0xC0, 0xE0, 0x38, 0xFC, 0xFC, 0x00, 0x00, 0x1C, 0x1E, 0x1B, 0x19, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0xFC, 0xFC, 0x8C, 0x8C, 0x8C, 0x0C, 0x00, 0xC1, 0xC1, 0xC1, 0xC1, 0xE3, 0x7F, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0xC0, 0xF0, 0x38, 0x9C, 0x8C, 0x8C, 0x8C, 0x0C, 0x00, 0x1F, 0x7F, 0x63, 0xC1, 0xC1, 0xC1, 0xE3, 0x7F, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x0C, 0x0C, 0x0C, 0x0C, 0x8C, 0xEC, 0xFC, 0x3C, 0x0C, 0x00, 0x00, 0xE0, 0xFC, 0x7F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x70, 0xF8, 0x9C, 0x0C, 0x0C, 0x0C, 0x9C, 0xF8, 0x70, 0x3C, 0x7F, 0xE7, 0xC3, 0xC3, 0xC3, 0xE7, 0x7F, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0xF0, 0xF8, 0x1C, 0x0C, 0x0C, 0x0C, 0x1C, 0xF8, 0xE0, 0x01, 0xC3, 0xC7, 0xC6, 0xC6, 0xE6, 0x73, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0xC0, 0xC0, 0xE1, 0xE1, 0x00, 0x00, // 58
    0x00, 0xC0, 0xC0, 0x00, 0xC1, 0xC1, 0x38, 0x38, 0x00, // 59
    0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0x60, 0x06, 0x0E, 0x0F, 0x19, 0x19, 0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x60, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x30, 0x19, 0x19, 0x0F, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x18, 0x0C, 0x0C, 0x8C, 0x8C, 0xFC, 0x78, 0x00, 0x00, 0xE6, 0xE7, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 63
    0x80, 0xE0, 0x70, 0x18, 0x08, 0x8C, 0xC4, 0x44, 0x44, 0x44, 0xC4, 0xC8, 0x18, 0x30, 0xE0, 0xC0, 0x1F, 0x7F, 0xE0, 0x80, 0x1F, 0x3F, 0x30, 0x20, 0x20, 0x10, 0x1F, 0x3F, 0x20, 0x30, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x08, 0x08, 0x18, 0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, // 64
    0x00, 0x00, 0x00, 0x80, 0xF0, 0xFC, 0x0C, 0x7C, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x80, 0xF0, 0xFE, 0x7F, 0x1F, 0x18, 0x18, 0x18, 0x1B, 0x1F, 0x7E, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x9C, 0xF8, 0x70, 0x00, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xE6, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0xC0, 0xF0, 0x78, 0x18, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1C, 0x0F, 0x3F, 0x78, 0x60, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x38, 0xF0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0x60, 0x38, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 69
    0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0xC0, 0xE0, 0x70, 0x18, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1C, 0x0F, 0x3F, 0x70, 0x60, 0xC0, 0xC0, 0xC3, 0xC3, 0xC3, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0xFC, 0xFC, 0xFF, 0xFF, 0x00, 0x00, // 73
    0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xC0, 0xC0, 0xC0, 0xE0, 0x7F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 74
    0xFC, 0xFC, 0x00, 0x80, 0xE0, 0x70, 0x38, 0x1C, 0x0C, 0x04, 0xFF, 0xFF, 0x03, 0x07, 0x1E, 0x3C, 0x70, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 76
    0xFC, 0xFC, 0x3C, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x3C, 0xFC, 0xFC, 0xFF, 0xFF, 0x00, 0x01, 0x07, 0x3F, 0xF8, 0xF0, 0x3E, 0x07, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xFC, 0xFC, 0x3C, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x07, 0x0E, 0x3C, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0xC0, 0xF0, 0x78, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x38, 0xF0, 0xC0, 0x0F, 0x3F, 0x78, 0x60, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x60, 0x70, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x1C, 0xF8, 0xF0, 0xFF, 0xFF, 0x06, 0x06, 0x06, 0x06, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0xC0, 0xF0, 0x78, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x38, 0xF0, 0xC0, 0x0F, 0x3F, 0x78, 0x60, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xF0, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x18, 0x10, // 81
    0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x9C, 0xF8, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x03, 0x03, 0x07, 0x1F, 0x7D, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0x70, 0xF8, 0x9C, 0x8C, 0x0C, 0x0C, 0x0C, 0x1C, 0x00, 0x60, 0xC0, 0xC1, 0xC3, 0xC3, 0xC7, 0xE6, 0x7E, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x0C, 0x0C, 0x0C, 0x0C, 0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x1F, 0x7F, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0x60, 0x7F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x04, 0x3C, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0x3C, 0x04, 0x00, 0x00, 0x01, 0x0F, 0x3F, 0xF8, 0xC0, 0xF8, 0x3F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0x0C, 0x7C, 0xFC, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0xFC, 0x1C, 0xFC, 0xF0, 0x00, 0x00, 0x00, 0xC0, 0xFC, 0x7C, 0x0C, 0x00, 0x00, 0x07, 0x3F, 0xFC, 0xE0, 0xFE, 0x1F, 0x01, 0x00, 0x01, 0x0F, 0xFF, 0xF0, 0xF8, 0x7F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x04, 0x0C, 0x3C, 0xF8, 0xE0, 0x80, 0x80, 0xE0, 0x78, 0x3C, 0x0C, 0x04, 0x80, 0xC0, 0xF0, 0x7C, 0x1F, 0x07, 0x07, 0x1F, 0x7C, 0xF0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x04, 0x1C, 0x7C, 0xF0, 0xC0, 0x00, 0x00, 0xC0, 0xE0, 0x78, 0x1C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x8C, 0xEC, 0xFC, 0x3C, 0x1C, 0x0C, 0xC0, 0xE0, 0xF0, 0xFC, 0xDE, 0xC7, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    0xFC, 0xFC, 0x0C, 0x0C, 0xFF, 0xFF, 0x00, 0x00, 0x38, 0x38, 0x30, 0x30, // 91
    0x04, 0x3C, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x3E, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x10, // 92
    0x0C, 0x0C, 0xFC, 0xFC, 0x00, 0x00, 0xFF, 0xFF, 0x30, 0x30, 0x38, 0x38, // 93
    0x00, 0x80, 0xE0, 0x78, 0x1C, 0x1C, 0x70, 0xC0, 0x80, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 95
    0x02, 0x06, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x70, 0xF9, 0xC8, 0xCC, 0xCC, 0x6C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0xFE, 0xFE, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0xFF, 0xFF, 0x61, 0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0x7F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 98
    0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x1E, 0x7F, 0x61, 0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 99
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0xFE, 0xFE, 0x3E, 0x7F, 0xE1, 0xC0, 0xC0, 0xC0, 0x61, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 100
    0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x3E, 0x7F, 0xED, 0xCC, 0xCC, 0xCC, 0xCD, 0x6F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0xC0, 0xC0, 0xF8, 0xFC, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 102
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0x3E, 0x7F, 0xE1, 0xC0, 0xC0, 0xC0, 0x61, 0xFF, 0xFF, 0x00, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0x60, 0x78, 0x18, // 103
    0xFE, 0xFE, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 104
    0x0E, 0xCE, 0xCE, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, // 105
    0x0E, 0xCE, 0xCE, 0x00, 0xFF, 0xFF, 0xE0, 0x78, 0x38, // 106
    0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x40, 0xFF, 0xFF, 0x0C, 0x1E, 0x3F, 0x33, 0x61, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 107
    0xFE, 0xFE, 0xFF, 0xFF, 0x00, 0x00, // 108
    0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x1E, 0x7F, 0x61, 0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0x7F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0xC0, 0xC0, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0xFF, 0xFF, 0x61, 0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0x7F, 0x1F, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 112
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0x3E, 0x7F, 0xE1, 0xC0, 0xC0, 0xC0, 0x61, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, // 113
    0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 114
    0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0xE3, 0xC7, 0xCC, 0xCC, 0xCC, 0x79, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 115
    0xC0, 0xC0, 0xF8, 0xF8, 0xC0, 0xC0, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 116
    0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x3F, 0x7F, 0xE0, 0xC0, 0xC0, 0xC0, 0x60, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0x40, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x40, 0x00, 0x03, 0x1F, 0x7E, 0xF0, 0xF0, 0x7E, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0x00, 0x07, 0x3F, 0xFC, 0xC0, 0xFC, 0x0F, 0x01, 0x0F, 0xFE, 0xE0, 0xF8, 0x3F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0x40, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x40, 0x80, 0xC0, 0xF3, 0x7F, 0x1E, 0x1E, 0x7F, 0xF3, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0x40, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x40, 0x00, 0x03, 0x0F, 0x7E, 0xF0, 0xE0, 0x7C, 0x0F, 0x03, 0x00, 0xC0, 0xC0, 0xC0, 0x70, 0x38, 0x18, 0x00, 0x00, 0x00, 0x00, // 121
    0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xF0, 0xF8, 0xDC, 0xC7, 0xC3, 0xC1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 122
    0x00, 0x00, 0xF8, 0xFC, 0x0C, 0x0C, 0x06, 0x0F, 0xFF, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x30, // 123
    0xFE, 0xFE, 0xFF, 0xFF, 0xF8, 0xF8, // 124
    0x0C, 0x0C, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xF3, 0xFF, 0x1E, 0x0C, 0x30, 0x30, 0x38, 0x18, 0x00, 0x00, // 125
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1E, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18, 0x1E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFC, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xFC, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 127
    
};

#endif