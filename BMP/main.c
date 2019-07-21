#include <stdio.h>
#define bmSign 'MB'

struct BitMapHeader{
    char bfType[4];
    unsigned char bfSize[4];
    unsigned char  bfReserved1[2];
    unsigned char  bfReserved2[2];
    unsigned char  bfOffBits[4];
};
struct BitMapInFo
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

void readFromFile(FILE* fp, struct BitMapHeader bmhd, struct BitMapInFo bmif){;

    fread(&bmhd,sizeof(struct BitMapHeader),1,fp);
    fread(&bmif,sizeof(struct BitMapInFo),1,fp);

    printf("\n%s",bmhd.bfType);
    printf("\n%s",bmhd.bfSize);
    printf("\n%s",bmif.biSize);
    printf("\n%s",bmif.biWidth);
    printf("\n%s",bmif.biHeight);

    if (bmhd.bfType != bmSign)
    {
        printf("Khong phai file bitmap");
    }
    else printf("Day la file bitmap");

}


int main() {
    FILE* fp = NULL;
    fp = fopen("D:\\bitmap.in","r+b");

    if(!fp){
        printf("Open file fail ...");
        return 0;
    }

    readFromFile(fp);
    //fseek(fp,0,SEEK_SET);

//Nhap vao 1 con so bat ky tu -100 den 100, chinh do sang toi cua anh

    fclose(fp);
    getchar();
    return 0;
}