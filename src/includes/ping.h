/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:54:39 by bapasqui          #+#    #+#             */
/*   Updated: 2025/03/11 13:26:22 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <assert.h>
#include <netinet/ip.h> 
#include "msg.h"

#define CTRL_C SIGINT
#define BUFFER_SIZE 1024
#define ICMP_ECHO 8
#define IP_LEN 15
#define PAYLOAD 64
#define PACKET_SIZE 84
#define TTL_VAL 64
#define COOLDOWN 1000000

typedef struct ping_pkt {
    struct icmphdr hdr;
    char msg[PAYLOAD - sizeof(struct icmphdr)];
} ping_pkt;


typedef struct {
    size_t capacity;
    size_t size;
    uint8_t *data;
} Arena;


typedef struct s_network {
    struct ping_pkt pckt;
    struct sockaddr_in *r_addr;
    struct timeval *tv_out;
}   t_network;

typedef struct s_data
{
    bool vflag;
    int sockfd;
    int msg_count;
    char *ip_addr;
    char *domain;
    int msg_received_count;
    struct s_network *network;
} t_data;

// ARENA and alloc
Arena arena_init(size_t capacity);
void *arena_alloc(Arena *arena, size_t size);
void *arena_reset(Arena *arena);
void  *arena_free(Arena *arena);
void clean_exit(Arena *arena);

// NETWORK utils
int get_IP(char  **argv, t_data *data);
int reverse_dns_lookup(char *ip, t_data *data);
void setup_ping(t_data *data);
unsigned short checksum(void *b, int len);