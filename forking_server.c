#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
    if (signo == SIGINT) {
        remove("WKP");
        exit(0);
    }
}

int main() {
    int to_client, from_client;
    char buffer[HANDSHAKE_BUFFER_SIZE];

    while (1) {
        from_client = server_setup(buffer);

        int f = fork();
        if (f == 0) {
            to_client = server_connect(from_client);
            /* subserver(from_client); */

            exit(0);
        }
    }
    return 0;
}

void subserver(int from_client) {
    char buffer[MESSAGE_BUFFER_SIZE];
    while (read(from_client, buffer, sizeof(buffer))) {
        printf("[SERVER %d] received: %s\n", getpid(), buffer);
        process(buffer);
        write(to_client, buffer, sizeof(buffer));
    }
}

void process(char * s) {
    unsigned char *my_str = (unsigned char *) str;
    int i = 0;
    for (; my_str[i]; i++) {
        my_str[i] = toupper(my_str[i]);
    }
    return my_str;
}
