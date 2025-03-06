#include "includes/ping.h"

void sig_ctrl_c(int signum)
{
    (void)signum;
    run_ping = false;
}

int main(int argc, char **argv)
{
    if (argc <= 1)
        return (printf(NO_ARGS), 1);

    int opt;
    struct s_data data;
    // struct sockaddr_in servaddr;

    data.vflag = false;
    data.sock_len = sizeof(struct sockaddr_in);
    run_ping = true;

    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        switch (opt)
        {
        case 'v':
            printf("--Verbose mode activated--\n");
            data.vflag = true;
            break;
        default:
            break;
        }
    }
    signal(CTRL_C, sig_ctrl_c);

    printf("IP ADDRESS = %s\n", argv[2]);
    data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
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