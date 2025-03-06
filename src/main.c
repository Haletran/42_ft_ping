#include "includes/ping.h"
#include <arpa/inet.h>
#include <netdb.h>

void sig_ctrl_c(int signum)
{
    (void)signum;
    run_ping = false;
}

int ft_isdigit(char *ip)
{
    for (int i = 0; ip[i]; i++)
    {
        if (!isdigit(ip[i]))
            return (0);
    }
    return (1);
}

void reverse_dns_lookup(char *ip, t_data *data)
{
    (void)data;
    struct addrinfo hints, *res;
    char ipstr[INET_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(ip, NULL, &hints, &res);
    struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
    inet_ntop(AF_INET, &addr->sin_addr, ipstr, sizeof(ipstr));

    strcpy(data->ip_addr, ipstr);
    freeaddrinfo(res);
}

bool get_IP(char **argv, t_token *parse)
{
    for (int i = 1; argv[i]; i++)
    {
        if (argv[i][0] != '-')
        {
            parse->ip = argv[i];
            return true;
        }
    }

    return (false);
}

int main(int argc, char **argv)
{
    if (argc <= 1)
        return (printf(NO_ARGS), 1);

    int opt;
    t_data *data;
    t_token *parse;
    data = malloc(1000);
    parse = malloc(1000);
    // struct sockaddr_in servaddr;

    data->vflag = false;
    data->sock_len = sizeof(struct sockaddr_in);
    run_ping = true;

    struct icmphdr *icmp = (struct icmphdr *)data->buffer;
    icmp->type = ICMP_ECHO;
    icmp->checksum = 0;

    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        switch (opt)
        {
        case 'v':
            data->vflag = true;
            break;
        default:
            free(parse);
            free(data);
            exit(1);
        }
    }

    signal(CTRL_C, sig_ctrl_c);

    if (get_IP(argv, parse) == false)
    {
        free(data);
        free(parse);
        exit(1);
    }

    reverse_dns_lookup(parse->ip, data);
    printf("PING %s (%s) %d(%d) bytes of data\n", parse->ip, data->ip_addr, PAYLOAD, PACKET_SIZE);

    data->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // add protection if fails

    while (run_ping)
    {
        // setsockopt to setup the socket timeout and some other stuff
        // sendto to send the ICMP ECHOREQUEST
        // recvfrom to receive the ECHO REPLY
    }

    // Example final print even if the while is stopped:
    // --- gnu.org ping statistics ---
    // 3 packets transmitted, 0 received, 100% packet loss, time 2032ms
    return (0);
}