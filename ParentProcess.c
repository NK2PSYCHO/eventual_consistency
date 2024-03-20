// Include the header file "ParentProcess.h"
#include "ParentProcess.h"

// Function to write a message to a log file
void write_log(char *filename, char *message) {
    // Open the file in append mode
    FILE *file = fopen(filename, "a");
    // Get the current time
    time_t now;
    time(&now);
    // Write the current time and message to the file
    fprintf(file, "%s: %s\n", ctime(&now), message);
    // Close the file
    fclose(file);
}

int main() {
    int i;
    // Array to store the process IDs of the child processes
    pid_t pids[10];
    for(i = 0; i < 10; i++) {
        // Create a new child process
        pids[i] = fork();
        if(pids[i] == 0) {  // This block of code is executed by the child process
            // Seed the random number generator
            srand(time(NULL) ^ (getpid()<<16));

            char serverName[20];
            // Generate the server name
            sprintf(serverName, "LikesServer%d", i);
            // Print a message to the console
            printf("Hello, world from %s\n", serverName);

            int network_socket;
            // Create a new socket
            network_socket = socket(AF_INET, SOCK_STREAM, 0);

            struct sockaddr_in server_address;
            // Use the internet address family
            server_address.sin_family = AF_INET;
            // Set the port number
            server_address.sin_port = htons(9002);
            // Use any IP address available on the machine
            server_address.sin_addr.s_addr = INADDR_ANY;

            // Connect to the remote socket
            int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
            if (connection_status == -1) {
                printf("There was an error making a connection to the remote socket \n");
                return 1; 
            }

            // Set the end time for the loop
            time_t end_time = time(NULL) + 5;
            while(time(NULL) < end_time) {
                // Generate a random number of likes
                int likes = rand() % 43;
                char message[50];
                // Generate a message to send to the server
                sprintf(message, "%s %d", serverName, likes);
                // Send the message to the server
                send(network_socket, message, sizeof(message), 0);

                char response[256];
                // Receive a response from the server
                recv(network_socket, &response, sizeof(response), 0);
                char filename[30];
                // Generate a filename for the log file
                sprintf(filename, "/tmp/%s", serverName);
                char log_message[300];
                // Generate a log message
                sprintf(log_message, "%s received message: %s", serverName, response);
                // Write the log message to a file
                write_log(filename, log_message);

                // Generate a random interval
                int interval = (rand() % 5) + 1;
                sleep(interval); 
            }

            // Close the socket
            close(network_socket);

            // Terminate the child process
            exit(0);
        } else {  // This block of code is executed by the parent process
            char log_message[50];
            // Generate a log message
            sprintf(log_message, "Child process LikesServer%d started", i);
            // Write the log message to a file
            write_log("/tmp/ParentProcessStatus", log_message);
            // Pause the execution of the parent process for 1 second
            sleep(1);
        }
    } for(i = 0; i < 10; i++) {
        int status;
        // Wait for the child process to terminate
        waitpid(pids[i], &status, 0);
        char log_message[50];
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1) {
            // Generate a log message
            sprintf(log_message, "Child process LikesServer%d failed", i);
        } else {
            // Generate a log message
            sprintf(log_message, "Child process LikesServer%d ended", i);
        }
        // Write the log message to a file
        write_log("/tmp/ParentProcessStatus", log_message);
    }
return 0;
}