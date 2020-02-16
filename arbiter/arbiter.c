//
// Created by just on 14.02.2020.
//

#include "arbiter.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

#define mld 1000000000

int arbiterState;


int main()
{

    printf("Jestem arbitrem\n");


    const char* path = "../FIFO_files";
    char* totem_opa = (char*) calloc (7, sizeof(char));
    gcvt(1.0, 2, totem_opa);
    char* totem_cla = (char*) calloc (7, sizeof(char));
    gcvt(1.0, 2, totem_cla);

    if(setenv("CAMP", path, 0) == -1)
    {
        printf("Cannot set CAMP\n");
        exit(-1);
    }
    if(setenv("TOTEM_OP", totem_opa, 0) == -1)
    {
        printf("Cannot set TOTEM_OP\n");
        exit(-1);
    }
    if(setenv("TOTEM_CL", totem_cla, 0) == -1)
    {
        printf("Cannot set TOTEM_CL\n");
        exit(-1);
    }




    sigact();
    arbiterState = 0;

    char* totemPath = (char*) calloc (20, sizeof(char));
    totemPath = getEnvironmentVariable("CAMP");
    char* totem_op = getEnvironmentVariable("TOTEM_OP");
    char* totem_cl = getEnvironmentVariable("TOTEM_CL");


    long int totemOp = charToLong(totem_op);
    long int totemCl = charToLong(totem_cl);
    printf("open: %ld\nclose: %ld\n", totemOp, totemCl);

    strcat(totemPath, "/Totem");

    createTotem(totemPath);
    int totemFd;

    printf("arbiter - Przed while\n");
    int i = 1;
    while(i)
    {
        while(arbiterState == 0)
        {
            printf("sleeping...\n");
            pause();
        }
        while(arbiterState == 1)
        {
            totemFd = openTotem(totemPath);
            printf("Opened totem\n");
            nSleep(totemOp);

            closeTotem(totemFd);
            printf("Closed totem\n");
            nSleep(totemCl);

            sleep(1);
        }
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

long int charToLong(char* num)
{
    float res = strtof(num, NULL);

    long int result = res * mld /10;

    return result;
}


void createTotem(char* camp)
{

    int res;
    if( (res = mkfifo(camp, 0666)) == 17)
    {
        printf("arbiter - Totem file exists\n");
    }
    else if(res == -1)
    {
        printf("arbiter - Cannot create Totem file\n");
        exit(-1);
    }

    printf("%s\n", camp);
}


int openTotem(char* path)
{
    int fd;
    if((fd = open(path, O_RDWR)) == -1)
        printf("Cannot open FI file\n");

    return fd;
}


void closeTotem(int fd)
{
    if(close(fd) == -1)
    {
        printf("Cannot close file descriptor\n");
    }
}



void nSleep(long int time)
{
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 0;

    if(time > (mld - 1))
    {
        tim.tv_sec = time / mld;
        tim.tv_nsec = time % mld;
    }
    else
    {
        tim.tv_nsec = time;
    }

    nanosleep(&tim, NULL);

}


void sigHandler()
{
    if(arbiterState == 0)
        arbiterState = 1;
    else if(arbiterState == 1)
        arbiterState = 0;
}


void sigact()
{
    struct sigaction sigact;
    sigact.sa_flags = 0;
    sigact.sa_handler = sigHandler;
    if(sigaction(47, &sigact, NULL) == -1)
    {
        write(1, "Sigact error\n", sizeof("Sigact error\n"));
        exit(-1);
    }
}