#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

int GetRowCount(std::string file_name_input)
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

int GetColsCount(std::string file_name_input)
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
    std::string docker = "docker service create";
    std::string restart_condition = "--restart-condition none";
    std::string replicas = "--replicas 3";
    std::string mounting = "--mount type=volume,dst=/mount/,volume-driver=local,volume-opt=type=nfs,\\\"volume-opt=o=nfsvers=4,addr=10.42.0.181\\\",volume-opt=device=:/clusterfs";
    std::string dist = "alpine";
    std::string command_container = "/bin/sh -c \"while true; do ls /mount/; sleep 2; done\"";

    std::string command = docker + " " +replicas+" "+mounting+" "+dist+" "+command_container;

    //Call the docker service
    //std::cout << command << std::endl;
    //system(command.c_str());

    int matrix1_rows = 0, matrix1_cols = 0;
    int matrix2_rows = 0, matrix2_cols = 0;

    matrix1_rows = GetRowCount("/clusterfs/share/input1.csv");
    matrix1_cols = GetColsCount("/clusterfs/share/input1.csv");

    matrix2_rows = GetRowCount("/clusterfs/share/input2.csv");
    matrix2_cols = GetColsCount("/clusterfs/share/input2.csv");


    if (matrix1_cols != matrix2_rows)
    {
        std::cout << "The dimensions of the matrix do not match... exiting" << std::endl;
        return 0;
    }

    // Generate commands for multiplying
    for (int cols = 0; cols < matrix2_cols; cols++)
    {
        for (int rows = 0; rows < matrix1_rows; rows++)
        {
            std::string index1 = std::to_string(rows+1);
            std::string index2 = std::to_string(cols+1);

            command_container = "/bin/sh -c \"sleep 10 && /mount/slave.out " + index1 + " " + index2 + "\"";
            
	    command =  docker + " ";
	    command += restart_condition + " ";
	    command += mounting + " ";
	    command += dist + " ";
	    command += command_container;
            std::cout << command << std::endl;
   	    
	    system(command.c_str());
        }
    }

    //Assemble the answers
    std::string file_name = "/clusterfs/share/answer.csv";
    std::ofstream myfileans;
    std::ifstream myfileread;

    myfileans.open(file_name);

    //Go through all the rows and cols which need to be filled
    for(int answer_rows = 0; answer_rows < matrix1_rows; answer_rows++)
    {
        for(int answer_cols = 0; answer_cols < matrix2_cols; answer_cols++)
        {
            //Open file for read
            std::string file_name = "/clusterfs/share/out-r" + std::to_string(answer_rows+1)+'c'+std::to_string(answer_cols+1)+".csv";
            myfileread.open(file_name);

            while (!myfileread.is_open())
            {
                usleep(100);
                continue;
            }

            std::string temp_read;
            getline(myfileread,temp_read);

            int remove_count = 0;
            for (size_t remove_intdex = 0; remove_intdex < temp_read.size(); remove_intdex++)
            {
                if (remove_count == 2)
                {
                    break;
                }

                if(temp_read.at(0) == ',')
                {
                    remove_count += 1;
                }

                temp_read.erase(0, 1);
            }

            temp_read.erase(0, 1);

            if(answer_cols == matrix2_cols-1)
            {
                myfileans << temp_read << "\n";
            }
            else
            {
                myfileans << temp_read << ",";
            }

            //Close file after read
            myfileread.close();
        }
    }
    std::cout << "End of main" << std::endl;
    myfileans.close();

    return 0;
}
