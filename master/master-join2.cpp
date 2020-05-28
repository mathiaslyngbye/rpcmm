#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

int getRowCount(std::string file_name_input)
{
    //Open two matrices
    std::string file_name = file_name_input;
    std::ifstream myfile;

    myfile.open(file_name);

    std::string temp;

    //Find the size of the first matrix
    int matrix_rows = 0;
    if(myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile,temp);
            matrix_rows++;
        }
        matrix_rows = matrix_rows-1;
    }

    return matrix_rows;
}

int getColCount(std::string file_name_input)
{
    //Open two matrices
    std::string file_name = file_name_input;
    std::ifstream myfile;

    myfile.open(file_name);

    std::string temp;
    size_t lineLength = 0;

    getline(myfile, temp);
    lineLength = temp.size();

    int colCount = 1;
    for (size_t i = 0; i < lineLength; i++)
    {
        if(temp.at(i) == ',')
        {
            colCount++;
        }
    }

    return colCount;
}


int main(int argc, char** argv)
{
    //Configure arguments for launching a docker service
    int rows_max = getRowCount("./share/input1.csv");
    int cols_max = getColCount("./share/input2.csv");

    if (cols_max != rows_max)
    {
        std::cout << "The dimensions of the matrix do not match... exiting" << std::endl;
        return -1;
    }

    char filler = '.';
    std::ifstream file_in;
    file_in.open("./share/out-r2c2.csv");
    std::string tmp_read;
    std::getline(file_in,tmp_read); 
    int remove_index = 0; 
    int delimiter_count = 0;
    while(true)
    {
        if(tmp_read.at(remove_index) == ',')
            delimiter_count++;

        if(delimiter_count == 2)
        {
            tmp_read.erase(0,remove_index+1);
            break;
        }
        remove_index++;
    }
    std::cout << tmp_read << std::endl;

    return 0;
}
