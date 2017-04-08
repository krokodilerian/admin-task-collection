#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <mhash.h>

// should come from the makefile
//#define DEFAULT_KEY_LEN 7

unsigned char *psbl = "123456789ABCDEFGHIJKLMNPQRSTWXYZZZ";

int main(int argc,char **argv)
{

	unsigned char *key=NULL,final[32],*tmp,*outp;
        int i,kt=7;
	FILE *urand;
        unsigned long k;

        MHASH h1;



	if (argc==2)
	{
                kt=atoi(argv[1]);
	}

        if (kt==0) kt=DEFAULT_KEY_LEN;


	urand=fopen("/dev/urandom","r");
	if (urand==NULL)
	{
		printf("Error opening /dev/urandom -- %s\n",strerror(errno));
                return 2;
	}

	// generate serial number XXX-XXX
	key=(char *) malloc(kt+1);
	i=0;
	while (i<kt+1)
	{
		fread(&k,sizeof(long),1,urand);
		key[i]=psbl[k%33];
		if (  ((i%4)==3) && (i<kt-2) && (i!=0) ) key[i]='-';
		i++;

	}
	key[kt]=0;


	fclose(urand);

	printf("%s\n",key);

	final[0]=0;
	h1=mhash_init(MHASH_MD5);
	mhash(h1,key,strlen(key));
	outp=mhash_end(h1);
        tmp=(char *) malloc(5);
        for (i = 0; i < 16; i++) {
                snprintf(tmp,4,"%.2X",outp[i]);
                strcat(final,tmp);
        }
        printf("%s\n",final);
        return 0;
}
