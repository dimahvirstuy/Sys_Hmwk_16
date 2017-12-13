#include "pipe_networking.h"
#define WKP "SWAG"
#define PRIVATE_PIPE "559328"

/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo(WKP, 0666);
  
}


/*=========================
  client_handshake
  args: int * to_server
  
  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  mkfifo(PRIVATE_PIPE, 0666);
  return 0;
}
