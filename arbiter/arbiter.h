//
// Created by just on 14.02.2020.
//

#ifndef LINUX_HOOLS_ARBITER_H
#define LINUX_HOOLS_ARBITER_H


char* getEnvironmentVariable(const char* name);

void createTotem(char* camp);

void nSleep(long int time);

long int charToLong(char* num);


int openTotem(char* path);

void closeTotem(int fd);

////////////////////////////////////// signals
void sigHandler();
void sigact();

#endif //LINUX_HOOLS_ARBITER_H
