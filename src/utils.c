/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:54:33 by bapasqui          #+#    #+#             */
/*   Updated: 2025/03/11 12:23:43 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ping.h"

int reverse_dns_lookup(char *ip, t_data *data)
{
    if (!ip || !data)
        return (1);
    struct addrinfo hints, *res;
    char ipstr[INET_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(ip, NULL, &hints, &res))
    {
        printf("ft_ping: unknown host\n");
        return (1);
    }
    struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
    inet_ntop(AF_INET, &addr->sin_addr, ipstr, sizeof(ipstr));

    strcpy(data->ip_addr, ipstr);
    freeaddrinfo(res);
    printf("FT_PING %s (%s): %d data bytes\n", data->domain, data->ip_addr, PAYLOAD);
    return (0);
}

void clean_exit(Arena *arena)
{
    arena_free(arena);
    exit(1);
}

int get_IP(char  **argv, t_data *data)
{
    for (int i = 1; argv[i]; i++)
    {
        if (argv[i][0] != '-')
        {
            data->domain = argv[i];
            return (0);
        }
    }
    return (1);
}

unsigned short checksum(void *b, int len) 
{
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}



void setup_ping(t_data *data)
{
    int ttl;
    struct timeval tv_out;

    ttl = TTL_VAL;
    tv_out.tv_sec = COOLDOWN;
    tv_out.tv_usec = 0;
    setsockopt(data->sockfd, SOL_IP, IP_TTL, &ttl, sizeof(ttl));
    setsockopt(data->sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));
    *data->network->tv_out = tv_out;
}