//
// Created by just on 13.02.2020.
//

#ifndef LINUX_HOOLS_SERWER_H
#define LINUX_HOOLS_SERWER_H

char* getEnvironmentVariable(const char* name);

void createFifoFiles(char* camp);

int openFIfile(char* path);
int openFOfile(char* path);


void closeFIFOfile(int fd);

char* randomPermissionForRing();

long int charToLong(char* num);

/////////////////////////////////

void manageFIfile(char* path, long int ringReg);
void manageFOfile(char* path, long int sleepTime);

long int decyToNano(long int num);

void randomNanosleep(); //nieregularne odtepy czasu na otwieranie pliku FI

#endif //LINUX_HOOLS_SERWER_H
