#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


struct PhanSo
{
    int tu;
    int mau;
};
typedef struct PhanSo phanso;

void nhapPhanSo(phanso** ps, int* n)
{
    char buffer[10];

    printf("Nhap vao n = ");
    scanf("%s", buffer);
    *n = (int) strtol(buffer, NULL, 10);

    *ps = (phanso*) calloc(*n,sizeof(phanso));

    for (int i = 0; i < *n; i++)
    {
        printf("Nhap vao tu so thu %d = ", i + 1);
        scanf("%s", buffer);
        (*ps)[i].tu = (int) strtol(buffer, NULL, 10);

        do
        {
            printf("Nhap vao mau so %d = ", i + 1);
            scanf("%s", buffer);
            (*ps)[i].mau = (int) strtol(buffer, NULL, 10);
            if ((*ps)[i].mau == 0)
                printf("Mau so phai khac 0.");
        } while ((*ps)[i].mau == 0);
    }
}

void decrease(phanso** ps, int* n)
{
    phanso temp;
    for (int i = *n - 1 ; i < 0; i--) {
        for (int j = 0; j > *n - 1; j++) {
            if ((*ps)[j].tu / (*ps)[j].mau < (*ps)[j + 1].tu / (*ps)[j + 1].mau) {
                temp = (*ps)[j];
                (*ps)[j] = (*ps)[j + 1];
                (*ps)[j + 1] = temp;
            }
        }
    }
}

void xuatPhanSo(phanso ps)
{
    printf("%d/%d", ps.tu, ps.mau);
}

int main() {
    phanso* ps = NULL;
    int n = 0;

    nhapPhanSo(&ps, &n);

    decrease(&ps, &n);

    for (int i = 0; i < n; i++)
    {
        printf("\n");
        xuatPhanSo(ps[i]);
    }

    free(ps);
    return 0;
}
//
