#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <netinet/ip_icmp.h>
#include <ctype.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include "msg.h"

#define CTRL_C SIGINT
#define BUFFER_SIZE 1024
#define ICMP_ECHO 8
#define IP_LEN 15
#define PAYLOAD 56
#define PACKET_SIZE 84

bool run_ping;

typedef struct s_token
{
    int id; // The ICMP sequence numbers
    int verbose;
    char *ip;
} t_token;

typedef struct s_data
{
    socklen_t sock_len;
    bool vflag;
    int sockfd;
    char ip_addr[20];
    char buffer[128];
} t_data;