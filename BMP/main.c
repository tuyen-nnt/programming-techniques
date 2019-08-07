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

typedef struct Bitmap {
    BitMapHeader header;
    Dib bmif;
    Rgb color;
    PixelArray pixel;
} BitMap;

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



void readFromFile(BitMap* bmp){
    FILE* f = NULL;
    f = fopen("D:\\bitmap.in","r+b");

    if (!f)
        return;

    char* link = NULL;
    link = (char*) malloc (strlen(link)*sizeof(char));
    scanf("%s", link);

    FILE* buffer = NULL;
    buffer = fopen(link, "r+b");

    //fread(&bmp->header, sizeof(struct BitMapHeader), 1, buffer);

    readBmpFile(buffer, &bmp->header, &bmp->bmif);
    readPixelArray(buffer, bmp->header, bmp->bmif, &bmp->pixel);

    fclose(f);
    fclose(buffer);
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

    int a = 0;
    int b = 0;
    int c = 0;

    for (int cot = 0; cot < bmif.biHeight; cot++)
        for (int hang = 0; hang < bmif.biWidth; hang++)
        {
            //Ngoai ra con co ham data = GetPixel(cot, hang) co the tham khao de lay mau cua Pixel luu vao bien data
            Rgb pixel = data.pixel[cot][hang];

            if ((pixel.Red + input) > 255) {
                a = 255;
            } else
                if ((pixel.Red + input) < 0) {
                    a = 0;
                } else {
                    a = pixel.Red + input;
                }

            if ((pixel.Green + input) > 255) {
                b = 255;
            } else
                if ((pixel.Green + input) < 0) {
                    b = 0;
                }
                else {
                    b = pixel.Green + input;
                }

            if ((pixel.Blue + input) > 255) {
                c = 255;
            } else
                if ((pixel.Blue + input) < 0) {
                    c = 0;
                }  else {
                    b = pixel.Blue + input;
                }


            //Mau trang co chi so la 255, 255, 255
            SetPixel(hdc, cot, hang, RGB (a, b, c));
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
    BitMap* bmp1;
    bmp1 = (BitMap*) malloc (sizeof(BitMap));

    readFromFile(bmp1);

    drawBmp(bmp1->bmif, bmp1->pixel);

    releaseBmpPixel(&bmp1->pixel);

    getchar();

    return
}