#include "pipe_networking.h"
#define WKP "SWAG"
#define PRIVATE_PIPE "559328"


//IMPORTANT COMMENT: The entire assignment was complete before the due date, I just forgot to delete the pipes in the program and I added a few extra print statements after the due date, hope thats okay


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int fd;
  int fd2;
  mkfifo(WKP, 0666);
  fd = open(WKP, O_RDONLY);
  char private_pipe[80];
  read(fd, private_pipe, sizeof(private_pipe));
  printf("%s\n", private_pipe);
  mkfifo(private_pipe, 0666);
  fd2 = open(private_pipe, O_WRONLY);
  char conf[20] = "confirmation";
  write(fd2, conf, sizeof(conf));
  char second_conf_recieved[30];
  read(fd, second_conf_recieved, sizeof(second_conf_recieved));
  printf("%s\n", second_conf_recieved);
  printf("Connection established! Handshake complete\n");
  close(fd);
  close(fd2);
  if (!fork()) {
    execlp("rm", "rm", "-f", WKP, NULL);
  }
}


/*=========================
  client_handshake
  args: int * to_server
  
  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int fd;
  int fd2;
  mkfifo(PRIVATE_PIPE, 0666);
  fd = open(WKP, O_WRONLY);
  write(fd, PRIVATE_PIPE, sizeof(PRIVATE_PIPE));
  fd2 = open(PRIVATE_PIPE, O_RDONLY);
  char first_conf_recieved[30];
  read(fd2, first_conf_recieved, sizeof(first_conf_recieved));
  printf("%s\n", first_conf_recieved);
  printf("confirmation message recieved! ... sending confirmation message\n");
  char second_conf[30] = "recieved confirmation";
  write(fd, second_conf, sizeof(second_conf));
  close(fd);
  close(fd2);
  if (!fork()) {
    execlp("rm", "rm", "-f", PRIVATE_PIPE, NULL);
  }
  return 0;
}
