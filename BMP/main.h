#pragma once
#include <stdio.h>
#include<windows.h>
#include <stdint-gcc.h>

#pragma once

#define bmSign 'MB'
#pragma pack(1)

typedef struct BitMapHeaders{
    char bfType[4];
    unsigned char bfSize[4];
    unsigned char  bfReserved1[2];
    unsigned char  bfReserved2[2];
    unsigned char  bfOffBits[4];
} BitMapHeader ;

typedef struct DIB
{
    unsigned char biSize[4];
    uint32_t biWidth;
    uint32_t biHeight;
//so lop mau
    unsigned char biPlanes[2];
//do sau mau
    unsigned char biBitCount[2];
    unsigned char stuff1[16];
//so mau su dung
    unsigned char biClrUsed[4];
//so luong mau chinh yeu trong bang mau sd
    unsigned char biClrImportant[4];
} Dib;

typedef struct Color{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
} Rgb;

typedef struct PixelArrays{
    struct Color** pixel;
    uint32_t rowCount;
    uint32_t columnCount;
} PixelArray;

void readBmpFile(FILE* fp, BitMapHeader* header, Dib* bmif)
void scanBmpPixelLine(FILE* fp, Rgb* color, uint32_t lengthColumn);
void skipPadding(FILE* fp, char count);
void readPixelArray(FILE* fp, BitMapHeader bmhd, Dib bmif, PixelArray* data);
void drawBmp(Dib bmif, PixelArray data);
void releaseBmpPixel(PixelArray* data);