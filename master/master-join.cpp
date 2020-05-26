#include <iostream>
#include <fstream>
#include <stdlib.h>

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
    std::ofstream file_out;
    file_out.open("./share/output1.csv", std::fstream::app);
    for (int rows = 1; rows <= rows_max; rows++)
    {
        for (int cols = 1; cols <= cols_max; cols++)
        {
            // file_out << filler;

            if(cols != cols_max)
                file_out << ',';
        }
        file_out << "\n";
    }

    return 0;
}
