
#include "pw.h"

extern Memspace Heap;
extern int16 nid;
extern int16 numneedles;

char thread[4][16];
char *thehash;
char **thepassword[8];
char **pwlist;
// this function will be called by each thread to encrypt password
void threadmain(int16 _nid){
    char activebl;
    char *bl;
    int8 size;
    int32 x, y, z, a, b, c; // our password is of 6 letters
    char yy, zz, aa, bb, cc;
    int numchars;
    char testpw[8];
    char *pw;
    int32 n=0;

    bl = thread[_nid-1];
    size = (int8)strlen(bl);
    numchars = strlen(Chars);

    for(x=0; x<size; x++){
        activebl = thread[_nid-1][x];
        for(y=0; y<numchars; y++){
            yy = Chars[y];
        }
        for(z=0; z<numchars; z++){
            zz = Chars[z];
        }
        for(a=0; a<numchars; a++){
            aa = Chars[a];
        }
        for(b=0; b<numchars; b++){
            bb = Chars[b];
        }
        for(c=0; c<numchars; c++){
            cc = Chars[c];

            // iterate every possible password
            testpw[0] = activebl;
            testpw[1] = yy;
            testpw[2] = zz;
            testpw[3] = aa;
            testpw[4] = bb;
            testpw[5] = cc;
            testpw[6] = '\0';

            // checking the encrypted password
            pw = pwencrypt(testpw);
            if(!strcmp(pw, thehash)){
                strncpy(thepassword, testpw, 7); //7 is max limit
                put(correct, 1);

            }
            n++;
            if(!(n%1000)){
                printf("Checked 1000 new passwords");
                fflush(stdout);
            }

            if((unsigned long int)get(correct)){
                exit(0);
            }
        }

    }
}

int main(int argc, char *argv[]){
    
    if(argc < 2){
        fprintf(stderr, "Usage: /pw HASH\n");
        return -1;
    }
    // specifying how many bytes we are going to use
    ninit(kb(20));
    let(correct);

    memset(thepassword, 0, 8);
    put(correct, 0);
    thehash = argv[1];
    // will have 4 main needles from 1 to 4
    // every thread begin by these particular character will be hold by the particular thread

    stncpy(thread[0], "aeimquy26", 15);
    stncpy(thread[1], "bfjnrvz37", 15);
    stncpy(thread[2], "cgkosw048", 15);
    stncpy(thread[3], "dhlptx159", 15);

    spawn_multiple(threadmain);
    nuninit();
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