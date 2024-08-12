/* needle.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdbool.h>

#define Registersize    8
#define MAP_HUGE_2MB    (21 << MAP_HUGE_SHIFT)
#define MAP_HUGE_1GB    (30 << MAP_HUGE_SHIFT)
#define mb(x)           (1024*1024*(x))

#define IdentChars      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_'"
#define IdentOk         0
#define IdentTaken      1
#define IdentBadFormat  2
#define SizeofAllocs   76

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

typedef unsigned char IdentResult;

struct s_memspace {
    bool initialized;
    int32 size;
    int32 capacity;
    int32 allocations;
    struct {
        int32 id;
        int8 identifier[64];
        pid_t pid;
        bool lock;

    } *allocs;
    int8 *memspace;
};
typedef struct s_memspace Memspace;

bool validchar(char);
IdentResult nverifyident(char*);
void *nalloc(char*);
void ninit(int32);
void nuninit(void);
int main(int,char**);