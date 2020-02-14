//
// Created by just on 13.02.2020.
//

#include "klient.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


int main()
{
    printf("Jestem klientem!\n");

    char* FIpath = (char*) calloc (20, sizeof(char));
    FIpath = getEnvironmentVariable("CAMP");
/*    char* recruit_dly = getEnvironmentVariable("RECRUIT_DLY");
    char* recruit_max = getEnvironmentVariable("RECRUIT_MAX");
    char* ring_reg = getEnvironmentVariable("RING_REG");
    char* totem_op = getEnvironmentVariable("TOTEM_OP");
    char* totem_cl = getEnvironmentVariable("TOTEM_CL");*/

   /* printf("%s\n", FIpath);
    printf("%s\n", recruit_dly);
    printf("%s\n", recruit_max);
    printf("%s\n", ring_reg);
    printf("%s\n", totem_op);
    printf("%s\n", totem_cl);*/


    char* FOpath = (char*) calloc (20, sizeof(char));
    strcpy(FOpath, FIpath);
    strcat(FIpath, "/FI");
    strcat(FOpath, "/FO");

    int fifd;
    int fofd;
    fifd = openFIfile(FIpath);
    fofd = openFOfile(FOpath);

    //char* buffer = (char*) calloc (1, sizeof(char));

    struct childData child = {1, 2};


    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 1000000;


    int i = 1;
    while(i)
    {

        if(readFOfile(fofd) == 1)
        {
            child = createChild();
        }

        writeFIfile(fifd, child);

        //printf("%s\n", buffer);
        nanosleep(&tim, NULL);
    }


    return 0;
}


char* getEnvironmentVariable(const char* name)
{
    char* p = getenv(name);

    if(p == 0)
    {
        printf("Cannot get environment variable!\n");
        exit(-1);
    }
    return p;
}


int openFIfile(char* path)
{
    int fd;
    while((fd = open(path, O_WRONLY)) == -1)
    {
        printf("Cannot open fi file\n");
        //exit(-1);
    }
    printf("Opened fi file\n");
    return fd;
}


int openFOfile(char* path)
{
    int fd;
    while((fd = open(path, O_RDONLY)) == -1)
    {
        printf("klient - Cannot open fo file\n");
        //exit(-1);
    }
    printf("klient - Opened fo file\n");
    return fd;
}

void closeFIFOfile(int fd)
{
    if(close(fd) == -1)
    {
        printf("klient - Cannot close fifo file\n");
        //exit(-1);
    }
    printf("klient - Closed fifo file\n");
}

void writeFIfile(int fd, struct childData data)
{
    int flag = 0;
    char* pid = (char*) calloc (6, sizeof(char));
    char* gpid = (char*) calloc (6, sizeof(char));

    sprintf(pid, "%d", data.pid);
    sprintf(gpid, "%d", data.gpid);

    char* concaten;
    char newLine[] = "\n";

    concaten = strcat(pid, gpid);
    concaten = strcat(concaten, newLine);

    while(flag == 0)
    {
        if (write(fd, concaten, sizeof(concaten)) == -1)
        {
            printf("klient - Cannot write to fi file\n");
        }
        else
        {
            flag = 1;
        }
    }
    printf("klient - All written to fi file\n");

}

int readFOfile(int fd)
{
    char* buf = (char*) calloc (1, sizeof(char));
    if(read(fd, buf, 1) == 1)
        return 1;
    else
        return 0;

}

struct childData createChild()
{
    printf("klient - create child \n");
    struct childData child = {1,2};
    return child;
}
