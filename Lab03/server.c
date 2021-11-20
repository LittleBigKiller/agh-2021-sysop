#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);   // atoi - string na int [man atoi]

    int option = 1;
    int listenfd = 0, conndf = 0;
    // struct sockaddr_in   -   przechowuje dane adresowe potrzebne socketowi ip   [man ip]
    // POLA:
    // sa_family_t  -   przechowuje rodzinę adresową (AF_INET = IPv4)
    // in_port_t    -   port
    // struct in_addr   -   adres internetowy (tylko jedno pole - s_addr)
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    pthread_t tid;

    // DEF socket(domena, typ, protokół)    [man socket]
    // AF_INET = IPv4
    // SOCK_STREAM = dwókierunkowa, oparata na połączeniach komunikacja strumieniowa
    // 0 = domyślny protokół dla SOCK_STREAM (TCP)
    listenfd = socket(AF_INET, SOCK_STREAM, 0)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    // htons - konwertowanie kolejności bajtów hosta (najpewniej little endian) na sieciową (big endian)    [man htons]
    serv_addr.sin_port = htons(port);

    // signal(sygnał, handler)      [man 2 signal]
    // przypisanie SIGPIPE (piszemy do pipe'a bez słuchaczy)
    // do SIG_IGN - ignorujemy, że piszemy do nikogo
    signal(SIGPIPE, SIG_IGN);

    if(setsockopt)

    return EXIT_SUCCESS;
}