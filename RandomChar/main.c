#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void RandomStringGenerator(char* code, int codeLength)
{
    char* box = "!@#$%^&*()";
    int boxLength = strlen(box);

    for (int i = 0; i < codeLength; i++)
    {
        code[i] = box[rand() % boxLength];
        printf("%c", code[i]);
    }
    code[codeLength] = '\0';
}

int main()
{
    char* code;
    int codeLength = 0;
    char buffer[10];
    printf("Nhap vao so luong ki tu = ");
    scanf("%s", buffer);
    codeLength = (int) strtol (buffer, NULL, 10);

    code = malloc(sizeof(char)*(codeLength+1));

    RandomStringGenerator(code, codeLength);
    return 0;
}