#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define CHECK_ERR(a,msg) {if ((a) == -1) { perror((msg)); exit(EXIT_FAILURE); } }
#define CHECK_ERR_MMAP(a,msg) {if ((a) == MAP_FAILED) { perror((msg)); exit(EXIT_FAILURE); } }

#define FILE_SIZE (1024*1024)

void create_file_set_size(char *file_name, unsigned int file_size) {
	int res;
	int fd = open(file_name,
	O_CREAT | O_TRUNC | O_RDWR, // apriamo il file in lettura e scrittura
	S_IRUSR | S_IWUSR // l'utente proprietario del file avrà i permessi di lettura e scrittura sul nuovo file
	);
	CHECK_ERR(fd, "open file")

	res = ftruncate(fd, file_size);
	CHECK_ERR(res, "ftruncate()")

	close(fd);
}

int main(int argc, char *argv[]) {
  char * file_name;

	if (argc == 1) {
		printf("specificare come parametro il nome del file da leggere\n");
		exit(EXIT_FAILURE);
	}
	file_name = argv[1];

  create_file_set_size(file_name, FILE_SIZE);

  return 0;
}