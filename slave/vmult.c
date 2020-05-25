#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

const char* getfield(char* line, int index)
{
    const char* token;
    for (token = strtok(line, ",");
            token && *token;
            token = strtok(NULL, ",\n"))
    {
        if(!--index)
            return token;
    }
}

int main(int argc, char** argv)
{
    size_t in_row = 0;
    size_t in_col = 0; 
    
    if(argc == 3)
    {
        in_row = atoi(argv[1]);
        in_col = atoi(argv[2]); 
    }
    else
    {
        printf("Wrong input format.\n");
        return -1;
    }

    FILE* stream1 = fopen("input1.csv", "r");
    FILE* stream2 = fopen("input2.csv", "r");
      
    char line1[MAX_LINE_SIZE];
    char line2[MAX_LINE_SIZE];
    
    // Get specific row of input 1
    for(size_t i = 0; i < in_row; i++)
    {
        fgets(line1,1024,stream1);
    }
    
    // Multiply with each column element of input 1
    size_t iterations = 1;
    int sum = 0;
    while(fgets(line2,MAX_LINE_SIZE,stream2))
    {
        char* tmp1 = strdup(line1);
        char* tmp2 = strdup(line2);
        sum += atoi(getfield(tmp2,in_col)) * atoi(getfield(tmp1,iterations));
        free(tmp1);
        free(tmp2);
        iterations++;
    }
    printf("Product: %i\n", sum);
    return 0;
}
