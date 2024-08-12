
#include "pw.h"

extern Memspace Heap;
extern int16 nid;
extern int16 numneedles;

// each tread will launch this funtion as its main funtion

char thread1[16];
char thread2[16];
char thread3[16];
char thread4[16];
void threadmain(int16 _nid){
    // will have 4 main needles from 0 to 3
    // every thread begin by these particular character will be hold by the particular thread
    thread 1 "aei"

}

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage: /pw HASH\n");
        return -1;
    }
    return 0;


}

// for encrypting password
char *pwencrypt(char *password){

    
    struct crypt_data settings;  
    char *out;

    memset(&settings, 0, sizeof(struct crypt_data));

    out = crypt_r(password, Salt, &settings)
    // out = (struct crypt_data)crypt("apple", (const char *))
    printf("%s/n", out.output());
    return out;
}