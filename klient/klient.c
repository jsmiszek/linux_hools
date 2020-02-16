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

   childNo = 0;


    char* FOpath = (char*) calloc (20, sizeof(char));
    strcpy(FOpath, FIpath);
    strcat(FIpath, "/FI");
    strcat(FOpath, "/FO");

    int fifd;
    int fofd;
    //fifd = openFIfile(FIpath);
    //fofd = openFOfile(FOpath);


    //char* buffer = (char*) calloc (1, sizeof(char));

    struct childData* child = (struct childData*) calloc (1, sizeof(struct childData));
    struct childData* helpChild = child;


    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000000;


    printf("klient - przed while\n");
    int i = 1;
    while(i)
    {
        printf("klient - Jestem w while\n");
        fifd = openFIfile(FIpath);
        fofd = openFOfile(FOpath);

        if(readFOfile(fofd) == 1)
        {
            printf("klient - readFOfile\n");
            if (childNo < 50) {
                child = createChild(child->gpid);
                child = (struct childData *) realloc(child, sizeof(struct childData));
                child++;
            }
        }

        if(childNo >= 3)
        {
            writeFIfile(fifd, helpChild);
            helpChild++;
        }
        sleep(1);
        //printf("%s\n", buffer);
        //nanosleep(&tim, NULL);
    }


    return 0;
}


char* getEnvironmentVariable(const char* name)
{
    char* p = getenv(name);

    if(p == 0)
    {
        printf("klient - Cannot get environment variable!\n");
        exit(-1);
    }
    return p;
}


int openFIfile(char* path)
{
    int fd;
    while((fd = open(path, O_WRONLY | O_NONBLOCK)) == -1)
    {
        printf("klient - Cannot open fi file\n");
        //exit(-1);
        sleep(1);
    }

    printf("klient - Opened fi file\n");
    return fd;
}


int openFOfile(char* path)
{
    int fd;
    while((fd = open(path, O_RDONLY | O_NONBLOCK)) == -1)
    {
        printf("klient - Cannot open fo file\n");
        //exit(-1);
        sleep(1);
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

void writeFIfile(int fd, struct childData* data)
{
    int flag = 0;
    char* pid = (char*) calloc (6, sizeof(char));
    char* gpid = (char*) calloc (6, sizeof(char));

    sprintf(pid, "%d", data->pid);
    sprintf(gpid, "%d", data->gpid);

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

struct childData* createChild(int gpid)
{
    printf("klient - create child \n");

    int pid;

    switch(pid = fork())
    {
        case -1:
            printf("klient - cannot create child!");
            break;
        case 0:
            if (execl("../potomek/potomek", "potomek", (char*)NULL) == -1 )
            {
                printf("execl error\n");
                exit(-1);
            }
            //break;
        default: {
            struct childData *child = (struct childData *) calloc(1, sizeof(struct childData));

            if (childNo == 0) {
                child->gpid = pid;
                child->pid = pid;
            } else {
                child->gpid = gpid;
                child->pid = pid;
            }
            childNo++;

            return child;
        }
    }


}




























