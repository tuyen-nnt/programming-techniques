#include <stdio.h>

/*int main() {

        int *x;
        int y;
        int *z;
        y = 2;
        z = &y;
        *x = *x + y;
        printf("%d", y);
}*/


int main()
{

    int x = 1023;
    char *p = (char*)&x;
    printf("%d %d %d %d \n", p[0], p[1], p[2], p[3]);
    printf("%d", p[0]);
    return 0;
}
