// This line checks if PARENTPROCESS_H is not defined in the preprocessor.
#ifndef PARENTPROCESS_H
// This line defines PARENTPROCESS_H in the preprocessor.
#define PARENTPROCESS_H

// This line includes the standard input/output library, which provides facilities for input/output operations.
#include <stdio.h>
// This line includes the standard library, which provides several general purpose functions, including dynamic memory management, random number generation, 
// communication with the environment, integer arithmetics, searching, sorting and converting.
#include <stdlib.h>
// This line includes the unistd.h library, which provides access to the POSIX operating system API.
#include <unistd.h>
// This line includes sys/types.h, which is a header file that contains numerous data types used in system calls.
#include <sys/types.h>
// This line includes sys/socket.h, which is necessary for socket programming.
#include <sys/socket.h>
// This line includes netinet/in.h, which contains constants and structures needed for internet domain addresses.
#include <netinet/in.h>
// This line includes string.h, which is a header file that contains several functions for manipulating arrays of characters.
#include <string.h>
// This line includes time.h, which is a header file that includes several time types.
#include <time.h>
// This line includes sys/wait.h, which is necessary for the wait system call.
#include <sys/wait.h> 

// This line declares a function named write_log that takes two parameters: a filename and a message. Both parameters are pointers to characters (strings).
void write_log(char *filename, char *message);

// This line ends the conditional directive started by #ifndef. It's the end of the header guard.
#endif
