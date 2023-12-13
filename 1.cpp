#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 4096

int main() {
    char *shared_memory = mmap(NULL, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); //Crea un mapeo de memoria compartida
    if (shared_memory == MAP_FAILED) { // Verifica si el mapeo falló
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // Crea un proceso hijo

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child reads: %s\n", shared_memory);
        munmap(shared_memory, SIZE);// Unmap the shared memory
        exit(EXIT_SUCCESS);
    } else {
        strcpy(shared_memory, "Hello, child process!");
        wait(NULL); // Espera a que el proceso hijo termine
        munmap(shared_memory, SIZE); // Unmap the shared memory
    }

    return 0;
}
