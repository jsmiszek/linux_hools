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

    long int recruitMAX = charToLong(recruit_max);
    printf("%ld \n", recruitMAX);
    long int recruitDly = charToLong(recruit_dly);
    printf("%ld\n", recruitDly);
    long int ringReg = charToLong(ring_reg);
    printf("%ld\n", ringReg);

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


    printf("serwer - przed while\n");
    int i = 1;
    while(i)
    {
//        fifd = openFIfile(FIpath);
//        fofd = openFOfile(FOpath);

        printf("serwer - petla while\n");
        manageFIfile(FIpath, ringReg);
        manageFOfile(FOpath, recruitDly);

        sleep(1);
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
    int res;
    if( (res = mkfifo(camp, 0666)) == 17)
    {
        printf("FI file exist\n");
    }
    else if(res == -1)
    {
        printf("Cannot create FI file\n");
        exit(-1);
    }

    printf("%s\n", camp);
}

int openFIfile(char* path)
{
    int fd;
    if((fd = open(path, O_RDWR | O_NONBLOCK)) == -1)
        printf("Cannot open FI file\n");

    return fd;
}

int openFOfile(char* path)
{
    int fd;
    if((fd = open(path, O_WRONLY | O_NONBLOCK)) == -1)
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


long int charToLong(char* num)
{
    float res = strtof(num, NULL);

    long int result = res * mld /10;

    return result;
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
    printf("serwer - manageFIfile\n");
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
    printf("serwer - Opened FI file\n");
    nanosleep(&tim, NULL);
    read(fifd, buffer, 13);


    printf("%s\n", buffer);


    //closeFIFOfile(fifd);
    //printf("closed - Closed FI file\n");
}


void manageFOfile(char* path, long int sleepTime)
{
    printf("serwer - manageFOfile\n");
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
    printf("serwer - Opened FO file\n");

    char* randomByte;
    randomByte = randomPermissionForRing();

    write(fofd, randomByte, 1);

    //closeFIFOfile(fofd);
    //printf("serwer - closed FO file\n");

}

long int decyToNano(long int num)
{
    return (num * mld / 10);
}


















