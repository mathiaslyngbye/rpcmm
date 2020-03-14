#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv)
{
    
    if(argc > 3 && (argc % 2))
    {
        unsigned int index_param1 = 1;
        unsigned int index_param2 = (argc/2)+1;
        unsigned int index_max = (argc-3)/2;
        int sum = 0;

        for(unsigned int i = 0; i <= index_max; ++i)
        {
            sum += atoi(argv[index_param1+i])*atoi(argv[index_param2+i]);
        }
        printf("%i\r\n", sum);
    }
    return 0;
}
