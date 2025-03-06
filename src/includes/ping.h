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
#define CTRL_C SIGINT

#include "msg.h"

bool run_ping;

struct s_data
{
    socklen_t sock_len;
    bool vflag;
    int sockfd;
    char rbuffer[128];
} t_data;