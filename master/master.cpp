#include <iostream>
#include <stdlib.h>


int main(int argc, char** argv)
{
    std::string docker = "docker service create ";
    std::string replicas = "--replicas 3";
    std::string mounting = "--mount type=volume,dst=/mount/,volume-driver=local,volume-opt=type=nfs,\\\"volume-opt=o=nfsvers=4,addr=10.42.0.181\\\",volume-opt=device=:/clusterfs";
    std::string dist = "alpine";
    std::string command_container = "/bin/sh -c \"while true; do ls /mount/; sleep 2; done\"";

    std::string command = docker+replicas+" "+mounting+" "+dist+" "+command_container;

    std::cout << command << std::endl;
    //system(command.c_str());

    return 0;
}
