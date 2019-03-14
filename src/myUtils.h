#ifndef MYUTILS_H
#define MYUTILS_H
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include <crypt.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX 100


void strip(char *array);

int isValidName(char * name);

int isValidInt(char * array);

int isValidPassword(char * password);

int isValidFile(char * file);

void getFname(char * fname, size_t len);

void getLname(char * lname, size_t len);

long getNum();

void getFin(char * finName, size_t len);

void getFout(char * foutName, char * finName, size_t len);

void verifyHashes();

void writeToFile(char * fin, char * fout);

char * hashedPass(char * password);

char * verifyHash(char * password, char * hashOriginal);

#endif
