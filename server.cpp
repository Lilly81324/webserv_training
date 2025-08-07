#include <iostream>
#include <cstring>      // for memset, strerror
#include <cstdlib>      // for exit
#include <unistd.h>     // for close()
#include <sys/socket.h>
#include <netinet/in.h> // for sockaddr_in
#include <arpa/inet.h>  // for htons()

// 1:1 COPIED FROM CHATGPT

int main() {
    // 1. Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "socket() failed: " << strerror(errno) << std::endl;
        exit(1);
    }

    // 2. Allow address reuse (optional but good for development)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "setsockopt() failed: " << strerror(errno) << std::endl;
        exit(1);
    }

    // 3. Bind socket to port
    struct sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;        // 0.0.0.0 — accept on any interface
    server_addr.sin_port = htons(8080);              // Convert port to network byte order

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "bind() failed: " << strerror(errno) << std::endl;
        close(server_fd);
        exit(1);
    }

    // 4. Listen for connections
    if (listen(server_fd, 10) < 0) {
        std::cerr << "listen() failed: " << strerror(errno) << std::endl;
        close(server_fd);
        exit(1);
    }

    std::cout << "Server is listening on port 8080...\n";

    // 5. Accept a single client connection (blocking call)
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        std::cerr << "accept() failed: " << strerror(errno) << std::endl;
        close(server_fd);
        exit(1);
    }

    std::cout << "Client connected!\n";

    // 6. Receive data from client
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));

    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        std::cerr << "recv() failed: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Received: " << buffer << std::endl;
    }

    // 7. Send a response
    const char *response = "Hello from server!\n";
    send(client_fd, response, std::strlen(response), 0);

    // 8. Close sockets
    close(client_fd);
    close(server_fd);

    return 0;
}