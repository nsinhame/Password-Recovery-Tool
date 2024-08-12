
#define _GNU_SOURCE
#include <needle.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <crypt.h>


#define Salt    "$y$j9T$"
// list of characters we are going to use in hit and trial method
#define Chars   "abcdefghijklmnopqrstuvwxyz0123456789"
#define Size    6



// going to call this funtion to geerate all possible sequence
char *generate(void);
char *pwencrypt(char*);
int main(int, char**);
