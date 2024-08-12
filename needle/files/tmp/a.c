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

#define IdentOk         0
#define IdentTaken      1
#define IdentBadFormat  2

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

   struct abc {
        int32 id;
        int8 identifier[64];
        pid_t pid;
        bool lock;

    };

int main() {
 int8 n;

 n = (int8)sizeof(struct abc);
 printf("%d\n", (int8)n);

 return 0;
}
