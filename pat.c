#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#define MAX_WORD 100
#define MAX_CHAR 100

void remove_endOfLine(char line[]){
    int i =0;
    while(line[i] != '\n')
        i++;

    line[i] = '\0';
}

void read_line(char line[]){
    fgets(line,MAX_CHAR,stdin);
    remove_endOfLine(line);


}

int process_line(char* args[], char line[]){
    int i =0;
   // args[i] = strtok(line, " ");

    /*while(args[i] != NULL){
        i++;
        args[i] = strtok(NULL, " ");

    }
    args[i]=".";
    args[++i]=NULL;*/
    for(int x = 0; x < MAX_CHAR; x++) {
        args[x] = strsep(&line, " ");
        if(args[x] == NULL) break;
    }
    return 1;
}

int read_parse_line(char* args[], char line[]){

    read_line(line);

    process_line(args, line);
    return 1;
}
/*int execute_agr(char**args){
    return execvp(args[0], args);
}*/
int mulCmd(char **args)
{
    int i = 0;
    while (args[i] != 0)
    {
        if (strcmp(args[i], ";") == 0)
            return i;
        i++;
    }
    return -1;
}

int readBatch(char* args[]){
                //if (!fork())
                //{
        int fd;
        char *buff = (char *)malloc(MAX_CHAR * sizeof(char));
        //char *buff[MAX_COMMAND];
        char *line = (char *)malloc(MAX_CHAR * sizeof(char));
        char line2[MAX_CHAR];
        fd = open("testshell.txt", O_RDONLY);
        if (fd == -1){
                printf("can't open file\n");
                exit(1);
        }
        read(fd, buff, MAX_CHAR);
        close(fd);
       // printf("%sEND", buff);
       // printf("%c", buff[0]);

        int i = 0;
        int x = 0;

        while (buff[i] != '\0'){

                if (buff[i] == '\n'){
                        line[x] = ' ';
                        line[x+1] = ';';
                        line[x+2] = ' ';
                        x += 3;
                }else{
                        line[x] = buff[i];
                        x++;
                }
                i++;
        }


                line[x-1] = '\0';

                process_line(args, line);
                //execute_agr(args);
                //}
               // wait(0);
}


int execute_agr(char**args){
    //return execvp(args[0], args);
        //pid_t pid = fork();
        int idx = mulCmd(args);
        args[idx] = 0;
        pid_t pid = fork();
    // Error
    if (pid == -1) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }

    // Child process
    else if (pid == 0) {
        // Execute command
        execvp(args[0], args);

        // Error occurred
        char* error = strerror(errno);
        printf("Prompt> : %s: %s\n", args[0], error);

         /*if (idx != -1)
        {
         args = &args[idx + 1];
         execute_agr(args);
        }*/

        return 0;
    }

    // Parent process
    else {
        // Wait for child process to finish
        int childStatus;
                 if (idx != -1)
        {
         args = &args[idx + 1];
         execute_agr(args);
        }
        waitpid(pid, &childStatus, 0);
        return 1;
    }

   /* //check concurrent
    int idx = mulCmd(args);
    args[idx] = 0;
    // child exec
    if (!fork())
    {
        if (execvp(args[0], args) < 0)
            printf("No command : %s\n", args[0]);
        exit(0);
    }
    // check if have concurrent
    if (idx != -1)
    {
        args = &args[idx + 1];
        execute_agr(args);
    }
    // parent exec
    wait(0);*/
}
/*void kuy(int idx, char**args){
        args = &args[idx + 1];
}*/

int main(int argc, char *argv[]){
    char* args[MAX_WORD];
    char line[MAX_CHAR];
    int status;
    printf("Promptmain> ");
    while(read_parse_line(args, line)){
        if (strcmp(args[0], "exit") == 0)
                exit(0);
        //execute_agr(args);
        else if (strcmp(args[0], "shell") == 0){
                readBatch(args);
                execute_agr(args);
                printf("Prompt> ");
        }
        else {
                execute_agr(args);
                printf("Prompt> ");
        }
       /* pid_t child_pid = fork();
        printf("%d",child_pid);

        if(child_pid ==0){
                printf("YEAHHH");
                /*int idx = mulCmd(args);
                args[idx] = 0;
                printf("kuy %d\n",idx);
                status = execute_agr(args);
                //execvp(args[0], args);
                printf("haha");
                if (idx != -1)
                {
                        printf("KAO");
                        //args = &args[idx + 1];
                        //status = execute_arg(args);
                        kuy(idx,args);
                        status = execute_agr(args);
                        //execvp(args[0], args);
                }

          status =  execute_agr(args);
          if(status==-1){
            printf("No command!\n");
          }
          printf("Prompterror> ");

        }else{
            printf("Promptelse> ");
            waitpid(child_pid,&status, 0);
        }*/
    }

    return 0;
}