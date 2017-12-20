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
    int from_client;
    char buffer[HANDSHAKE_BUFFER_SIZE];
    signal(SIGINT,sighandler);

    while (1) {
        from_client = server_setup(buffer);

        int f = fork();
        if (f == 0) {
            
            subserver(from_client);

            exit(0);
        }
	else{
	  //char name[256];
	  //sprintf(name,"%d",from_client);
	  //close(from_client);
	  //remove(name);
	  //remove(buffer);
	}
    }
    return 0;
}

void subserver(int from_client) {
    int to_client = server_connect(from_client);
    char buffer[BUFFER_SIZE];
    while (read(from_client, buffer, sizeof(buffer))) {
        printf("[SERVER %d] received: %s\n", getpid(), buffer);
        process(buffer);
        write(to_client, buffer, sizeof(buffer));
    }
}

void process(char * str) {
    unsigned char *my_str = (unsigned char *) str;
    int i = 0;
    for (; my_str[i]; i++) {
        my_str[i] = toupper(my_str[i]);
    }
}
