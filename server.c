#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PORT 3000
#define BUF_SIZE 100

int server_fd;
struct sockaddr_in address;
socklen_t addrlen = sizeof(address);

char *flag = "flag{------------------------}";

char *create_random_passcode();
int clean_input(char *buffer, size_t buffer_len);
void socket_setup();
int socket_listen();
#define socket_send(S, M) send(S, M, strlen(M), 0);

int main(int argc, char const *argv[]) {
  char buffer[BUF_SIZE] = {0};

  socket_setup();

  while (true) {
    int socket = socket_listen();
    char *passcode = create_random_passcode();

    socket_send(socket, "Enter the one-time passcode and get the flag: ");

    read(socket, buffer, BUF_SIZE - 1);
    clean_input(buffer, BUF_SIZE);

    if (strcmp(buffer, passcode) == 0) {
      socket_send(socket, "Congrats, the flag is \"");
      socket_send(socket, flag);
      socket_send(socket, "\"\n");
    } else {
      socket_send(socket, "Inncorrect, the passcode was actually \"");
      socket_send(socket, passcode);
      socket_send(socket, "\"\nPlease try again later\n");
    }

    close(socket);

    free(passcode);
  }

  close(server_fd);
  return 0;
}

// generates a completely random passcode each call probably
char *create_random_passcode() {
  srand(time(NULL));

  char *passcode = malloc(25);
  passcode[24] = '\0';

  for (int i = 0; i < 24; i++) {
    char c = rand() % 25;
    bool lower = rand() % 2;

    c += lower ? 97 : 65;

    passcode[i] = c;
  }

  return passcode;
}

// NOTHING BELOW IS NEEDED TO SOLVE THE CHALLENGE

// Cleans user input, mainly for removing enter space, but also other
// non-printable characters
int clean_input(char *buffer, size_t buffer_len) {
  int validated = 0;

  for (int i = 0; i < buffer_len - 1; i++) {
    char c = buffer[i];

    if (c == '\0') {
      break;
    }

    if (c < ' ') {
      continue;
    }

    if (c == ' ' && validated == 0) {
      continue;
    }

    buffer[validated++] = c;
  }
  buffer[validated] = '\0';

  return validated;
}

// Sets up the server socket
void socket_setup() {
  ssize_t valread;
  char buffer[1024] = {0};

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
}

// Listening for a socket connection and returns the new connection
int socket_listen() {
  int new_socket;

  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) <
      0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  return new_socket;
}
