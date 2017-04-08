#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() 
{
	char *envv;
	char inp[32];
	char zz[32]={109, 111, 109, 100, 107, 118, 106, 104, 114, 97, 100, 106, 124, 108, 124, 96, 124, 112, 115, 126, 117, 123, 119, 126, 118, 106, 110, 114, 114, 124, 63, 0};
	int i=0;

	memset(inp, 0, sizeof(inp));
	envv=getenv("TMPDIR");

	if (envv[0]=='/')  i++;
	printf("Init done %d .\n", i);	
	printf("Enter password: ");
	fgets(inp, sizeof(inp)-1, stdin);
	printf("\n");
	
	for (int i=0;i<30;i++) {
		if ((inp[i]^i)!=zz[i]) {
			printf("WRONG\n");
			exit(4);
		}
	}
	
	printf("OK.\n");
	return 0;
}
