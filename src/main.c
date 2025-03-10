#include "includes/ping.h"

void sig_ctrl_c(int signum)
{
    (void)signum;
    run_ping = false;
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
            parse->id = rand() % (9999 - 1000 + 1);
            return true;
        }
    }

    return (false);
}

int free_all(t_data *data, t_token *parse, int exit_code)
{
    if (data)
        free(data);
    if (parse)
        free(parse);
    return (exit_code);
}

int main(int argc, char **argv)
{
    if (argc <= 1)
        return (printf(NO_ARGS), 1);

    int opt, n;
    t_data *data;
    t_token *parse;
    data = malloc(1000);
    parse = malloc(1000);
    srand(time(NULL));
    struct sockaddr_in *servaddr;

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
            exit(free_all(data, parse, 1));
        }
    }

    signal(CTRL_C, sig_ctrl_c);

    if (get_IP(argv, parse) == false)
        exit(free_all(data, parse, 1));

    reverse_dns_lookup(parse->ip, data);
    printf("PING %s (%s): %d data bytes", parse->ip, data->ip_addr, PAYLOAD);
    if (data->vflag == true)
        printf(", id 0x%x = %d\n", parse->id, parse->id);
    else
        printf("\n");

    data->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (!data->sockfd)
        exit(free_all(data, parse, 1));

    //  IP_HDRINCL
    const int on = 1;
    char buffer[1024];
    char recvline[1000];
    // setsockopt to setup the socket timeout and some other stuff
    setsockopt(data->sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));

    while (run_ping)
    {
        // sendto to send the ICMP ECHOREQUEST
        sendto(data->sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)servaddr, data->sock_len);
        // recvfrom to receive the ECHO REPLY
        n = recvfrom(data->sockfd, recvline, 1000, 0, 0, NULL);
    }

    // Example final print even if the while is stopped:
    // --- gnu.org ping statistics ---
    // 3 packets transmitted, 0 received, 100% packet loss, time 2032ms
    return (0);
}