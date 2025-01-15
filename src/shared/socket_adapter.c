// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #ifdef _WIN32
// #include <winsock2.h>
// #include <ws2tcpip.h>
// #pragma comment(lib, "ws2_32.lib")
// #else
// #include <arpa/inet.h>
// #include <unistd.h>
// #endif
// #include "socket_adapter.h"

// #define BUFFER_SIZE 1024

// int start_server(int port) {
//     int server_fd, client_socket;
//     struct sockaddr_in address;
//     int addrlen = sizeof(address);

// #ifdef _WIN32
//     WSADATA wsaData;
//     if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//         perror("WSAStartup failed");
//         exit(EXIT_FAILURE);
//     }
// #endif

//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("Socket creation failed");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(port);

//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
//         perror("Bind failed");
//         exit(EXIT_FAILURE);
//     }

//     if (listen(server_fd, 3) < 0) {
//         perror("Listen failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Server is listening on port %d\n", port);

//     if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
//         perror("Accept failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Client connected.\n");
//     return client_socket;
// }

// void communicate_with_client(int client_socket, double *x, double *y, double *vx, double *vy, double *fuel_mass) {
//     char buffer[BUFFER_SIZE];
//     while (1) {
//         memset(buffer, 0, BUFFER_SIZE);
//         int valread = recv(client_socket, buffer, BUFFER_SIZE, 0);
//         if (valread <= 0) break;

//         double thrust_x, thrust_y;
//         sscanf(buffer, "%lf %lf", &thrust_x, &thrust_y);

//         // Simulate simple physics update (replace with actual physics later)
//         *vx += thrust_x * 0.01;
//         *vy += thrust_y * 0.01;
//         *x += *vx * 0.01;
//         *y += *vy * 0.01;
//         *fuel_mass -= 0.1;

//         snprintf(buffer, BUFFER_SIZE, "%.6f %.6f %.6f %.6f %.2f", *x, *y, *vx, *vy, *fuel_mass);
//         send(client_socket, buffer, strlen(buffer), 0);
//     }

// #ifdef _WIN32
//     closesocket(client_socket);
//     WSACleanup();
// #else
//     close(client_socket);
// #endif
// }
