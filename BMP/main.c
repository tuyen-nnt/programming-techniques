#include <stdio.h>
#define _WIN32_WINNT 0x0500
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

/*typedef struct Bitmap {
    BitMapHeader header;
    Dib bmif;
    Rgb color;
    PixelArray pixel;
} BitMap; */

void readBmpFile(FILE* fp, BitMapHeader* header, Dib* bmif) {

    if (fp == NULL)
        return;

    fseek(fp, 0, SEEK_SET);
    fread(&header, sizeof(BitMapHeader), 1, fp);

    fseek(fp, sizeof(BitMapHeader), 0);
    fread(&bmif,sizeof(struct DIB),1,fp);


    printf("\n%s",header->bfType);
    printf("\n%s",header->bfSize);
    printf("\n%s",bmif->biSize);
    printf("\n%d",bmif->biWidth);
    printf("\n%d",bmif->biHeight);

    if (header->bfType != bmSign)
    {
        printf("Khong phai file bitmap");
    }
    else printf("Day la file bitmap");
}

void scanBmpPixelLine(FILE* fp, Rgb* color, uint32_t lengthColumn){
    if (!fp)
        return;

    color = (Rgb*) malloc (sizeof(Rgb)*lengthColumn);

    fread(color, sizeof(Rgb), lengthColumn, fp);
}

void skipPadding(FILE* fp, char count){
    if (!fp)
        return;

    if (count == 0)
        return;

    char* padding = NULL;
    padding = (char*) malloc(3);

    fread(padding, count, 1, fp);
}

void readPixelArray(FILE* fp, BitMapHeader bmhd, Dib bmif, PixelArray* data){
//read het cac thong so de nhap vao bien pixel
    if (!fp)
        return;

    (*data).rowCount = bmif.biHeight;
    (*data).columnCount = bmif.biWidth;
    (*data).pixel = (Rgb**) malloc (bmif.biHeight*(sizeof(Rgb*)));

    //Phan can cong voi chieu rong de la boi so cua 4
    char paddingCount = (4 - (bmif.biWidth) * ((int)bmif.biBitCount/8) % 4) % 4;

    fseek(fp, (long) bmhd.bfOffBits, SEEK_SET);

    for (int i = 0; i < (*data).rowCount; i++) {
        scanBmpPixelLine(fp, data->pixel[(*data).rowCount - i - 1], (*data).columnCount);
        skipPadding(fp, paddingCount);
    }
}

void readFromFile(FILE* fp, BitMapHeader* header, Dib* bmif, PixelArray* data){
    if (!fp)
        return;

    readBmpFile(fp, &header, &bmif);
    readPixelArray(fp, &header, &bmif, &data);

    fclose(fp);
}

void drawBmp(Dib bmif, PixelArray data) {
    HWND console = GetConsoleWindow();
    HDC hdc = GetDC(console);

    //Co 2 cach de lay mau: 1) RGB(R, G, B) ; 2) RGB color; color.Red/color.Green/color.Blue

    int input = 0;
    char buffer[4];
    //Nhap vao 1 con so bat ky tu -100 den 100, chinh do sang toi cua anh:

    do {
        printf("Nhap vao so nguyen bat ky de chinh do sang toi (tu -100 -> 100) : ");
        scanf("%s", buffer);
        input = (int) strtol(buffer, NULL, 10);
    } while ((input < -100) || (input) > 100);

    for (int cot = 0; cot < bmif.biHeight; cot++)
        for (int hang = 0; hang < bmif.biWidth; hang++)
        {
            //Ngoai ra con co ham data = GetPixel(cot, hang) co the tham khao de lay mau cua Pixel luu vao bien data
            Rgb pixel = data.pixel[cot][hang];

            //Mau trang co chi so la 255, 255, 255
            SetPixel(hdc, cot, hang, RGB (pixel.Red + input, pixel.Green + input, pixel.Blue + input));
        }
    ReleaseDC(console, hdc);
}

void releaseBmpPixel(PixelArray* data){

    for (int i = 0; i < data->rowCount; i++)
    {
        free(data->pixel[i]);
    }
    free(data->pixel);
}

int main() {
    //Khoi tao 1 file BMP de nhan du lieu file bmp ban dau tu link
    /*BitMap* bmp1;
    bmp1 = (BitMap*) malloc (sizeof(BitMap));*/
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;

    FILE* f = NULL;
    f = fopen("D:\\bitmap.in","r+b");

    if (!f)
        printf("Loi doc file bmp");

    line_size = getline(&line_buf, &line_buf_size, fp);

    line_buf = (char*) malloc (line_buf_size*sizeof(char));

    FILE* buffer = NULL;
    buffer = fopen(line_buf, "r+b");

    //KHoi tao 3 bien de ghi thong so Bmp cho file Bmp
    BitMapHeader* header;
    Dib* bmif;
    PixelArray* data;

    readFromFile(buffer);

    drawBmp(bmif, data);

    releaseBmpPixel(data);
    fclose(buffer);
    getchar();

    return
}