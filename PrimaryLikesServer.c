// Include the header file "PrimaryLikesServer.h"
#include "PrimaryLikesServer.h"

// Function to write logs to a file
void write_log(char *message) {
    // Open the log file in append mode
    FILE *file = fopen("/tmp/PrimaryLikesLog", "a");
    // Get the current time
    time_t now;
    time(&now);
    // Write the current time and message to the log file
    fprintf(file, "%s: %s\n", ctime(&now), message);
    // Close the log file
    fclose(file);
}

int main() {
    // Create a new socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Set the address family to AF_INET (IPv4)
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    // Set the port number to 9002
    server_address.sin_port = htons(9002);
    // Set the IP address to INADDR_ANY (0.0.0.0)
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP address and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // Start listening for incoming connections
    listen(server_socket, 5);

    // Generate a unique key for shared memory
    key_t key = ftok("shmfile",65);

    // Create a new shared memory segment
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // Attach the shared memory segment to the process's address space
    int *total_likes = (int*) shmat(shmid,(void*)0,0);

    // Initialize the total likes count to 0
    *total_likes = 0;

    while(1) {
        // Accept a new client connection
        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);

        if(fork() == 0) { // Create a new child process to handle the client connection
            // Attach the shared memory segment to the child process's address space
            total_likes = (int*) shmat(shmid,(void*)0,0);

            while(1) {
                char server_response[256];
                // Receive data from the client
                int data_received = recv(client_socket, &server_response, sizeof(server_response), 0);

                // If no data was received or an error occurred
                if(data_received <= 0) {
                    char message[50];
                    if(data_received == 0) { // If the client disconnected
                        // Create a disconnect message
                        char *server_name = strtok(server_response, " ");
                        sprintf(message, "%s %s", server_name, DISCONNECT_MESSAGE);
                    } else {
                        // Create a failure message
                        strcpy(message, FAILURE_MESSAGE);
                    }

                    // Send the message to the client
                    send(client_socket, message, sizeof(message), 0);

                    // Print the message
                    printf("%s\n", message);

                    break;
                }

                // Print the received data
                printf("The server received data: %s\n", server_response);

                // Create a response message
                char message[50] = "Received likes count";

                // Send the response message to the client
                send(client_socket, message, sizeof(message), 0);

                // Find the last space character in the received data
                char *likes_str = strrchr(server_response, ' ');

                if (likes_str != NULL) {
                    // Convert the string after the last space character to an integer
                    int likes = atoi(likes_str + 1);

                    // Add the likes count to the total likes count
                    *total_likes += likes;

                    // Create a log message
                    char log_message[300];
                    sprintf(log_message, "%s\nTotal\t%d", server_response, *total_likes);

                    // Write the log message to the log file
                    write_log(log_message);
                }
            }

            // Detach the shared memory segment from the child process's address space
            shmdt(total_likes);

            // Close the client socket
            close(client_socket);

            // Terminate the child process
            exit(0);
        }
    }

    // Detach the shared memory segment from the parent process's address space
    shmdt(total_likes);

    // Remove the shared memory segment
    shmctl(shmid,IPC_RMID,NULL);

    // Close the server socket
    close(server_socket);

    // Return 0 to indicate successful execution
    return 0;
}
