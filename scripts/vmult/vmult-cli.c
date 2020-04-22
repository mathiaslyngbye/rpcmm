#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    unsigned int size = (argc/2);
    float sum = 0;
    for(unsigned int i = 1; i <= size; i++)
        sum += atoi(argv[i])*atoi(argv[size+i]);
    printf("%f\r\n", sum);
    return 0;
}
