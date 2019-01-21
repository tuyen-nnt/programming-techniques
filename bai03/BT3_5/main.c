#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define e 0.0000000000001

int lamtron(float x)
{
    int k = 0;
    if (x < (int) x + 1)
    {
        k = (int) x;
        return k;
    }
    else
        return (int) x;
}

void mangsonguyen(float** matrix, int m, int n, int** intarray, int* k)
{
    *k = 0;

    *intarray = (int*) malloc(*k * sizeof(int));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] - lamtron(matrix[i][j]) < e)
            {
                *intarray[k] = lamtron(matrix[i][j]);
                *k += 1;
            }
        }
    *k += 1;
}

int CheckPrimeNumber(int* intarray, int k)
{
    printf("Cac so nguyen to trong mang so thuc:\n");

    for (int i = 0; i < k; i++)
    {
        if (intarray[i] < 2)
            break;
        else if (intarray[i] == 2)
            printf("%d.0   ", intarray[i]);
        else {
            for (int j = 3; j <= sqrt(intarray[i]); j += 2)
            {
                if (intarray[i]/j == 0) {
                    break;
                }
            }
            printf("%d   ", intarray[i]);
        }
    }
}

/*int soNguyenTo(int soA)
{
    if (soA < 2)
        return 0;

    for (int i = 2; i <= sqrt((float)soA); i ++)
    {
        if (soA%i==0)
        {
            return 0;
        }
    }
    return 1;
}
*/
void nhapmatrix(float*** matrix, int m, int n)
{
    char buffer[10];

    //cap phat bo nho cho dong
    *matrix = (float**) malloc(m* sizeof(float*));

    for (int i = 0; i < m; i++)
    {
        //tiep tuc cap bo nho cho cac phan tu cua dong
        (*matrix)[i] = (float*) malloc(n* sizeof(float));

        for (int k = 0; k < n; k++)
        {
            printf("Nhap vao matrix[%d][%d]", i, k);
            scanf("%s", buffer);
            (*matrix)[i][k] = strtof(buffer, NULL);
        }
    }
}

int main()
{
    int m = 0;
    int n = 0;
    int k = 0;
    char buffer[10];
    float** matrix;
    int* intarray;

    do {
        printf("Nhap vao so hang ma tran, m = ");
        scanf("%s", buffer);
        m = (int) strtol(buffer, NULL, 10);
    } while (m < 0);

    do {
        printf("Nhap vao so hang ma tran, n = ");
        scanf("%s", buffer);
        n = (int) strtol(buffer, NULL, 10);
    } while (n < 0);

    nhapmatrix(&matrix, m, n);

    mangsonguyen(matrix, m, n, &intarray, &k);

    CheckPrimeNumber(intarray, k);

    free(matrix);
    free(intarray);

    return 0;
}