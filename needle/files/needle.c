/* needle.c */
#include "needle.h"

Memspace Heap = {0};

bool validchar(char c) {
    char *valid, *p;
    bool ret;

    valid = IdentChars;
    ret = false;

    for (p=valid; *p; p++)
        if (*p == c) {
            ret = true;
            break;
        }

    return ret;
}

IdentResult nverifyident(char *identifier) {
    bool exists;
    char *p;
    int32 n;

    exists = false;
    for (n=0; n<Heap.allocations; n++)
        if (!strcmp(identifier,
            (char *)Heap.allocs[n].identifier)) {
                exists = true;
                break;
            }

    if (exists)
        return IdentTaken;

    n = strlen(identifier);
    exists = true; // "exists" now means "is ok"

    for (p=identifier; *p && n; p++, n--)
        if (!validchar(*p)) {
            exists = false;
            break;
        }
    
    if (!exists)
        return IdentBadFormat;
    
    return IdentOk;
}

void ninit(int32 size) {
    assert(!(size % Registersize));

    Heap.memspace = (int8 *)mmap((void *)0, (unsigned long int)size,
        PROT_READ|PROT_WRITE,
        MAP_SHARED|MAP_ANONYMOUS/*|MAP_FIXED*/
        |MAP_LOCKED|MAP_NORESERVE|MAP_STACK,
        -1, 0
    );

    if (Heap.memspace == (void *)-1)
        assert_perror(errno);
    
    Heap.size = size;
    Heap.capacity = (size / Registersize);
    Heap.allocations = 0;
    memset(Heap.memspace, 0, (unsigned long int)size);
    Heap.allocs = malloc(Heap.capacity * SizeofAllocs);
    assert(Heap.allocs);
    Heap.initialized = true;

    return;
}

void nuninit() {

   munmap(Heap.memspace, (unsigned long int)Heap.size);
   Heap.size = 0;
   Heap.initialized = false;

   return;
}

void *nalloc(char *identifier) {
    void *ret;
    int32 offset;
    int32 id;
    IdentResult res;

    if (Heap.capacity < Heap.allocations) {
        errno = 1;
        return (void *)0;
    }
    res = nverifyident(identifier);
    switch (res) {
        case IdentBadFormat:
            errno = 2;
            return (void *)0;
        case IdentTaken:
            errno = 1;
            return (void *)0;
        case IdentOk:
        default:
            break;
    }
    
    id = Heap.allocations;
    offset = (Heap.allocations * Registersize);
    ret = (void *)Heap.memspace + offset;
    Heap.allocations++;

    Heap.allocs[id].id = id;
    Heap.allocs[id].lock = false;
    strncpy((char *)Heap.allocs[id].identifier, identifier, 63);

    return ret;
}

#define nfree(x) ->"Deallocations not supported, instead: deallocate all by calling nuninit()."

int main(int argc, char *argv[]) {
    void *alloc;
    unsigned int *n;

    ninit(20000);
    alloc = nalloc("alloc");
    printf("%p\n", alloc);
    alloc = nalloc("alloc'");
    printf("%p\n", alloc);
    printf("%d\n", errno);

    n = (unsigned int *)alloc;
    *n = 1000000000;
    printf("%d\n", *n);
    nuninit();

    return 0;
}