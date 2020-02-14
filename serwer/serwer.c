//
// Created by just on 13.02.2020.
//

#include "serwer.h"
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
#include <sys/random.h>
#include <time.h>

#define mld 1000000000

int main()
{

    printf("Jestem serwerem!\n");

    char* FIpath = (char*) calloc (20, sizeof(char));
    FIpath = getEnvironmentVariable("CAMP");
    char* recruit_dly = getEnvironmentVariable("RECRUIT_DLY");
    char* recruit_max = getEnvironmentVariable("RECRUIT_MAX");
    char* ring_reg = getEnvironmentVariable("RING_REG");
    //char* totem_op = getEnvironmentVariable("TOTEM_OP");
    //char* totem_cl = getEnvironmentVariable("TOTEM_CL");

    long int recruitMAX = strtol(recruit_max, NULL, 10);
    printf("%ld \n", recruitMAX);

    long int recruitDly = strtol(recruit_dly, NULL, 10);
    recruitDly = decyToNano(recruitDly);
    printf("%ld\n", recruitDly);

    long int ringReg = strtol(ring_reg, NULL, 10);
    ringReg = decyToNano(ringReg);
    printf("%ld \n", recruitMAX);



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

    createFifoFiles(FIpath);
    createFifoFiles(FOpath);

   /* fifd = openFIfile(FIpath);
    fofd = openFOfile(FOpath);*/


    int i = 1;
    while(i)
    {
//        fifd = openFIfile(FIpath);
//        fofd = openFOfile(FOpath);


        manageFIfile(FIpath, ringReg);
        manageFOfile(FOpath, recruitDly);


    }

    //closeFIFOfile(fifd);
    //closeFIFOfile(fofd);


    printf("Opened fifo files\n");
    printf("Closed fifo files\n");




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


void createFifoFiles(char* camp)
{

    if( mkfifo(camp, 0666) == -1)
    {
        printf("Cannot create FI file\n");
        exit(-1);
    }

    printf("%s\n", camp);
}

int openFIfile(char* path)
{
    int fd;
    if((fd = open(path, O_RDWR)) == -1)
        printf("Cannot open FI file\n");

    return fd;
}

int openFOfile(char* path)
{
    int fd;
    if((fd = open(path, O_WRONLY)) == -1)
        printf("Cannot open FI file\n");

    return fd;
}

void closeFIFOfile(int fd)
{
    if(close(fd) == -1)
    {
        printf("Cannot close file descriptor\n");
    }
}

char* randomPermissionForRing()
{
    char* stream = (char*) calloc (1, sizeof(char));

    getrandom(stream , 1, GRND_NONBLOCK);

    return stream;
}

void randomNanosleep()//nieregularne odtepy czasu na otwieranie pliku FI
{
    struct timespec time;
    time.tv_sec = 0;
    time.tv_nsec = rand() % mld;
    nanosleep(&time, NULL);
}



void manageFIfile(char* path, long int ringReg)
{
    randomNanosleep();

    char* buffer = (char*) calloc (13, sizeof(char));

    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 0;

    if(ringReg > (mld - 1))
    {
        tim.tv_sec = ringReg / mld;
        tim.tv_nsec = ringReg % mld;
    }
    else
    {
        tim.tv_nsec = ringReg;
    }


    int fifd = openFIfile(path);
    nanosleep(&tim, NULL);
    read(fifd, buffer, 13);


    printf("%s\n", buffer);


    closeFIFOfile(fifd);

}


void manageFOfile(char* path, long int sleepTime)
{
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 0;

    if(sleepTime > (mld - 1))
    {
        tim.tv_sec = sleepTime / mld;
        tim.tv_nsec = sleepTime % mld;
    }
    else
    {
        tim.tv_nsec = sleepTime;
    }

    nanosleep(&tim, NULL);

    int fofd = openFOfile(path);

    char* randomByte;
    randomByte = randomPermissionForRing();

    write(fofd, randomByte, 1);

    closeFIFOfile(fofd);

}

long int decyToNano(long int num)
{
    return (num * mld / 10);
}


















