/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:51:05 by bapasqui          #+#    #+#             */
/*   Updated: 2025/03/12 10:50:07 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ping.h"
#include <bits/getopt_core.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

bool run_ping = true;

void sig_ctrl_c(int signum) {
  (void)signum;
  run_ping = false;
}

int ping_command(Arena *arena, t_data *data) {
  char rbuffer[1024];
  int i;
  socklen_t addr_len;
  struct sockaddr_in dest_addr;
  struct timeval stop, start;

  memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr(data->ip_addr);
  signal(CTRL_C, sig_ctrl_c);
  data->msg_count = 0;
  data->msg_received_count = 0;

  while (run_ping) {
    memset(&data->network->pckt, 0, sizeof(data->network->pckt));
    data->network->pckt.hdr.type = ICMP_ECHO;
    data->network->pckt.hdr.code = 0;
    data->network->pckt.hdr.un.echo.id = getpid();

    for (i = 0; i < (int)sizeof(data->network->pckt.msg) - 1; i++)
      data->network->pckt.msg[i] = i + '0';

    data->network->pckt.msg[i] = 0;
    data->network->pckt.hdr.un.echo.sequence = data->msg_count++;
    data->network->pckt.hdr.checksum =
        checksum(&data->network->pckt, sizeof(data->network->pckt));

    usleep(COOLDOWN);
    gettimeofday(&start, NULL);

    int m =
        sendto(data->sockfd, &data->network->pckt, sizeof(data->network->pckt),
               0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (m <= 0) {
      perror("Error: ");
      clean_exit(arena);
    }
    addr_len = sizeof(*data->network->r_addr);
    int n = recvfrom(data->sockfd, rbuffer, sizeof(rbuffer), 0,
                     (struct sockaddr *)&data->network->r_addr, &addr_len);
    if (n <= 0 && data->msg_count > 1) {
      perror("Error: ");
      clean_exit(arena);
    }
    struct icmphdr *recv_hdr = (struct icmphdr *)(rbuffer + 20);
    if (!(recv_hdr->type == 0 && recv_hdr->code == 0)) {
      // printf("Error: 0 bytes from %s\n", data->ip_addr);
    } else {
      gettimeofday(&stop, NULL);
      double elapsed_time = ((stop.tv_sec - start.tv_sec) * 1000.0) +
                            ((stop.tv_usec - start.tv_usec) / 1000.0);
      printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%f ms\n", PAYLOAD,
             data->ip_addr, data->msg_count - 1, TTL_VAL, elapsed_time);
      data->msg_received_count++;
    }
  }
  printf("--- %s ping statistics ---\n", data->domain);
  printf("%d packets transmitted, %d packets received\n", data->msg_count,
         data->msg_received_count);
  return (0);
}

// PING gnu.org (209.51.188.116): 56 data bytes
// 64 bytes from 209.51.188.116: icmp_seq=0 ttl=63 time=113.686 ms
// 64 bytes from 209.51.188.116: icmp_seq=1 ttl=63 time=106.311 ms
// 64 bytes from 209.51.188.116: icmp_seq=2 ttl=63 time=110.723 ms
// ^C--- gnu.org ping statistics ---
// 3 packets transmitted, 3 packets received, 0% packet loss
// round-trip min/avg/max/stddev = 106.311/110.240/113.686/3.030 ms

int main(int argc, char **argv) {
  if (argc <= 1)
    return (printf(NO_ARGS), 1);

  Arena arena = arena_init(3024);
  t_data *data = arena_alloc(&arena, sizeof(t_data));
  int opt;

  data->ip_addr = arena_alloc(&arena, sizeof(struct sockaddr_in));
  data->network = arena_alloc(&arena, sizeof(struct s_network *));
  data->network->tv_out = arena_alloc(&arena, sizeof(struct timeval *));
  data->network->r_addr = arena_alloc(&arena, sizeof(struct sockaddr_in *));

  while ((opt = getopt(argc, argv, "v?")) != -1) {
    switch (opt) {
    case 'v':
      if (argc < 3)
        clean_exit(&arena);
      data->vflag = true;
      break;
    case '?':
      printf(USAGE_MSG);
    default:
      clean_exit(&arena);
    }
  }
  if (get_IP(argv, data))
    clean_exit(&arena);
  if (reverse_dns_lookup(data->domain, data) == 1)
    clean_exit(&arena);

  data->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (data->sockfd < 0) {
    perror("Error: ");
    clean_exit(&arena);
  }

  setup_ping(data);
  ping_command(&arena, data);
  arena_free(&arena);
  return (0);
}