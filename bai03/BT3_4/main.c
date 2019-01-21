#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct HocSinh
{
    char hoten[50];
    float dvan;
    float dtoan;
    float dngoaingu;
    float dtb;
};


struct HocSinh* nhapds(int n)
{
    struct HocSinh* hocsinh = (struct HocSinh*) malloc(n* sizeof(struct HocSinh));
    char buffer[10];

    for (int i = 0; i < n; i++)
    {
        printf("Nhap vao ho va ten hoc sinh thu %d : ", i+1);
        scanf(" %[a-zA-Z0-9 ]", hocsinh[i].hoten);

        do {
            printf("Diem van: ");
            scanf("%s", buffer);
            hocsinh[i].dvan = strtof(buffer, NULL);
        } while (hocsinh[i].dvan < 0 || hocsinh[i].dvan > 10);

        do{
            printf("Diem toan: ");
            scanf("%s", buffer);
            hocsinh[i].dtoan = strtof(buffer, NULL);
        } while (hocsinh[i].dtoan < 0 || hocsinh[i].dtoan > 10);

        do {
            printf("Diem ngoai ngu: ");
            scanf("%s", buffer);
            hocsinh[i].dngoaingu = strtof(buffer, NULL);
        } while (hocsinh[i].dngoaingu < 0 || hocsinh[i].dngoaingu > 10);

        hocsinh[i].dtb = (hocsinh[i].dvan*2 +hocsinh[i].dtoan*2 +hocsinh[i].dngoaingu)/5;
    }
    return hocsinh;
}

void danhsachgioi(struct HocSinh* hocsinh, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = n-1; k <= 0; k++)
        {
            if (hocsinh[i].dtb < hocsinh[i+1].dtb)
            {
                float t = hocsinh[i].dtb;
                hocsinh[i].dtb = hocsinh[i+1].dtb;
                hocsinh[i+1].dtb = t;
            }
        }
    }

    printf("\nDanh sach hs gioi theo thu tu giam dan: \n");

    for (int i = 0; i < n; i++)
    {
        if (hocsinh[i].dtb >= 8.0)
        {
            printf("%s\n", hocsinh[i].hoten);
        }
        else
            break;
    }
	free(hocsinh);
}
int main() {
    int n = 0;
    char buffer[10];

    while (n <= 0)
    {
        printf("Nhap vao so luong hoc sinh, n = ");

        scanf("%s", buffer);
        n = (int) strtol(buffer, NULL, 10);
    }

    struct HocSinh* hocsinh = nhapds(n);

    printf("\n");

    danhsachgioi(hocsinh, n);

    free(hocsinh);

    return 0;
}
