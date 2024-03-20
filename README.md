# Eventual Consistency Project

This project demonstrates the concept of eventual consistency using a server-client model. It consists of two main components: `PrimaryLikesServer` and `ParentProcess`.

## Components

### PrimaryLikesServer

`PrimaryLikesServer` is a server program that accepts client connections, receives data from the clients, and writes logs to a file. It uses shared memory to keep track of the total likes count. Each client connection is handled by a separate child process. The server continues to accept and handle client connections in an infinite loop. When a client disconnects or an error occurs, the child process handling that client terminates. The server also cleans up the shared memory segment before it exits.

### ParentProcess

`ParentProcess` is a client program that creates multiple child processes to connect to the `PrimaryLikesServer`. Each child process sends a random number of likes to the server at random intervals. The server responds to each message from the client. The child process writes the server's responses to a log file. The parent process writes the status of the child processes to a log file.

## Building the Project

This project uses CMake for building. The minimum required version of CMake is 3.10. The project is set to use the C11 standard.

To build the project, navigate to the project directory and run the following commands:

bash\\
mkdir build\\
cd build\\
cmake ..\\
make

## Running the Project
To run the project, you need to start the server and the parent process. Here are the steps:

Open a terminal and navigate to the directory containing the executables.\\
Start the server by running the following command:\\
./PrimaryLikesServer

Open a new terminal and navigate to the same directory.\\
Start the parent process by running the following command:\\
./ParentProcess

## Logs
The server and the parent process write logs to files. Here are the details:

The server writes logs to\\
/tmp/PrimaryLikesLog.\\
Each child process of the parent process writes logs to /tmp/LikesServerX, where X is the index of the child process.\\
The parent process writes logs to\\
/tmp/ParentProcessStatus.\\
You can view the logs by opening the log files in any text editor.
