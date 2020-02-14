//
// Created by just on 13.02.2020.
//

#ifndef LINUX_HOOLS_KLIENT_H
#define LINUX_HOOLS_KLIENT_H

struct childData{
    int pid;    //pid procesu
    int gpid;   //pid grupy procesów
};

char* getEnvironmentVariable(const char* name);

int openFIfile(char* path);
int openFOfile(char* path);

void closeFIFOfile(int fd);

void writeFIfile(int fd, struct childData data);
int readFOfile(int fd);

struct childData createChild();


#endif //LINUX_HOOLS_KLIENT_H
