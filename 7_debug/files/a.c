#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd;

	size_t sz=0;
	char buff[1024];
	char *nbuff;

	fd = open("./pesho", O_RDONLY);
	sz = read(fd, buff, sizeof(buff));
	close(fd);
	nbuff = (char *) malloc(sz);
	memcpy(nbuff, buff, sizeof(buff));

	for(int i=0;i<sz;i++) {
		printf("%d %d\n", i, nbuff[i]);
	}
	return 0;

}
