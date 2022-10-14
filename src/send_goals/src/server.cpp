#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#define PORT 8080

int main(int argc, char const* argv[]){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    std::string hello = "Hello from server";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
	perror("socket failed");
	exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
	perror("setsockopt");
	exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
	perror("bind failed");
	exit(EXIT_FAILURE);
    }

    

    if (listen(server_fd, 3) < 0){
	perror("listen");
	exit(EXIT_FAILURE);
    }

    std::cout << hello << std::endl;

    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    std::cout << new_socket << std::endl;
    
    if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
	perror("accept");
	exit(EXIT_FAILURE);
    }


    std::cout << hello << std::endl;
    
    valread = read(new_socket, buffer, 1024);
    std::cout << buffer << std::endl;
    send(new_socket, &hello, hello.length(), 0);
    std::cout << "Hello message sent" << std::endl;
    return 0;
}

