#include <stdio.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include <stdint-gcc.h>

#pragma once

#define bmSign 'MB'
#pragma pack(1)



struct BitMapHeader{
    char bfType[4];
    unsigned char bfSize[4];
    unsigned char  bfReserved1[2];
    unsigned char  bfReserved2[2];
    unsigned char  bfOffBits[4];
};

struct DIB
{
    unsigned char biSize[4];
    unsigned char biWidth[4];
    unsigned char biHeight[4];
//so lop mau
    unsigned char biPlanes[2];
//do sau mau
    unsigned char biBitCount[2];
    unsigned char stuff1[16];
//so mau su dung
    unsigned char biClrUsed[4];
//so luong mau chinh yeu trong bang mau sd
    unsigned char biClrImportant[4];
};

void readBmpFile(FILE* fp, struct BitMapHeader* header, struct DIB* bmif) {

    if (fp == NULL)
        return;

    fseek(fp, 0, SEEK_SET);
    fread(header, sizeof(struct BitMapHeader), 1, fp);

    fseek(fp, sizeof(struct BitMapHeader), 0);
    fread(&bmif,sizeof(struct DIB),1,fp);

    printf("\n%s",header->bfType);
    printf("\n%s",header->bfSize);
    printf("\n%s",bmif->biSize);
    printf("\n%s",bmif->biWidth);
    printf("\n%s",bmif->biHeight);

    if (header->bfType != bmSign)
    {
        printf("Khong phai file bitmap");
    }
    else printf("Day la file bitmap");

}



struct Color{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
};

struct PixelArray{
    struct Color** pixel;
    uint32_t rowCount;
    uint32_t columnCount;
};



}

void readPixelArray(FILE* fp, struct BitMapHeader bmhd, struct DIB bmif, struct PixelArray pixel){

}

struct Bitmap {
    struct BitMapHeader header;
    struct DIB bmif;
    struct Color color;
    struct PixelArray pixel;
};

void readFromFile(FILE* f, struct Bitmap* bmp) {

    f = fopen("D:\\bitmap.in","r+b");
    if (!f)
        return;
    char* link = NULL;
    scanf("%s", link);

    FILE* buffer = NULL;
    buffer = fopen(link, "r+b");

    fread(&bmp->header, sizeof(struct BitMapHeader), 1, buffer);
    fread(&bmp->bmif, sizeof(struct DIB), 1, buffer);
    fread(&bmp->bmif, sizeof(struct Color), 1, buffer);
    fread(&bmp->bmif, sizeof(struct PixelArray), 1, buffer);
}

void main() {
    FILE* fp1 = NULL;



    struct Bitmap* bmp1;

    readFromFile(fp1, bmp1);

    readBmpFile(fbmp1, );
    //fseek(fp,0,SEEK_SET);

    FILE* fp2 = NULL;
    fp2 = fopen("D:\\bitmap.out","w");

    if(!fp2){
        printf("Open file 2 fail ...");
        return;
    }


//Nhap vao 1 con so bat ky tu -100 den 100, chinh do sang toi cua anh

    char paddingCount = (4 - (struct DIB.biWidth) * (struct DIB.biBitCount /8) % 4)) % 4;

    fclose(fp1);
    fclose(fp2);
    getchar();

    HWND console = GetConsoleWindow();
    HDC hdc = GetDC(console);

    return
}