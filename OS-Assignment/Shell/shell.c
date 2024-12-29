#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80
#define MAX_ARGS 10

void parse_command(char *command, char **args, int *arg_count) {
    char *token;
    *arg_count = 0;
    
    token = strtok(command, " \n");
    while (token != NULL && *arg_count < MAX_ARGS) {
        args[*arg_count] = token;
        *arg_count += 1;
        token = strtok(NULL, " \n");
    }
    args[*arg_count] = NULL;
}

// Function to check if command has redirection
int has_redirection(char **args, int arg_count) {
    for (int i = 0; i < arg_count; i++) {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0) {
            return 1;
        }
    }
    return 0;
}

// Modified redirection handling function that returns success/failure
int handle_redirection(char **args, int *arg_count) {
    int i;
    int in_fd, out_fd;
    
    for (i = 0; i < *arg_count; i++) {
        if (strcmp(args[i], "<") == 0) {
            if (i + 1 < *arg_count) {
                in_fd = open(args[i + 1], O_RDONLY);
                if (in_fd < 0) {
                    perror("Input redirection failed");
                    return -1;
                }
                if (dup2(in_fd, STDIN_FILENO) < 0) {
                    perror("Input duplication failed");
                    close(in_fd);
                    return -1;
                }
                close(in_fd);
                args[i] = NULL;
                *arg_count -= 2;
            }
        }
        else if (strcmp(args[i], ">") == 0) {
            if (i + 1 < *arg_count) {
                out_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out_fd < 0) {
                    perror("Output redirection failed");
                    return -1;
                }
                if (dup2(out_fd, STDOUT_FILENO) < 0) {
                    perror("Output duplication failed");
                    close(out_fd);
                    return -1;
                }
                close(out_fd);
                args[i] = NULL;
                *arg_count -= 2;
            }
        }
    }
    return 0;
}

void execute_command(char **args, int *arg_count) {  // Modified to accept arg_count parameter
    pid_t pid;
    int has_redir = has_redirection(args, *arg_count);
    
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {  // Child process
        if (has_redir) {
            // Save original file descriptors only if we have redirection
            int stdout_copy = dup(STDOUT_FILENO);
            int stdin_copy = dup(STDIN_FILENO);
            
            // Handle redirection
            if (handle_redirection(args, arg_count) < 0) {  // Pass arg_count instead of MAX_ARGS
                // Restore descriptors before exiting on error
                dup2(stdout_copy, STDOUT_FILENO);
                dup2(stdin_copy, STDIN_FILENO);
                close(stdout_copy);
                close(stdin_copy);
                exit(1);
            }
        }
        
        execvp(args[0], args);
        perror("Command execution failed");
        exit(1);
    }
    else {  // Parent process
        wait(NULL);
    }
}

void handle_pipe(char *command) {
    char *cmd1, *cmd2;
    char *args1[MAX_ARGS], *args2[MAX_ARGS];
    int arg_count1, arg_count2;
    int pipefd[2];
    pid_t pid1, pid2;
    
    cmd1 = strtok(command, "|");
    cmd2 = strtok(NULL, "\n");
    
    parse_command(cmd1, args1, &arg_count1);
    parse_command(cmd2, args2, &arg_count2);
    
    if (pipe(pipefd) < 0) {
        perror("Pipe creation failed");
        return;
    }
    
    pid1 = fork();
    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        execvp(args1[0], args1);
        perror("Command 1 execution failed");
        exit(1);
    }
    
    pid2 = fork();
    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
        execvp(args2[0], args2);
        perror("Command 2 execution failed");
        exit(1);
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main() {
    char command[MAX_LINE];
    char *args[MAX_ARGS];
    int arg_count;
    
    while (1) {
        printf("\nmyshell> ");
        fflush(stdout);
        
        if (fgets(command, MAX_LINE, stdin) == NULL) {
            break;
        }
        
        if (strcmp(command, "exit\n") == 0) {
            break;
        }
        
        if (strchr(command, '|') != NULL) {
            handle_pipe(command);
            continue;
        }
        
        parse_command(command, args, &arg_count);
        if (arg_count == 0) continue;
        
        execute_command(args, &arg_count);  // Pass the address of arg_count
    }
    
    return 0;
}