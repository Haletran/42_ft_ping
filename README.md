# 42_ft_ping

Recreate the ping command in C based on the inetutils-2.0 implementation.


## Instructions 

- [ ] Be realized in a virtual machine running on Debian (>= 7.0)
- [ ] Use C and submit a Makefile
- [ ] Authorised to use the libc functions
- [ ] Executable must be named `ft_ping`
- [ ] Take as reference the ping implementation from `inetutils-2.0` (ping -V)
- [ ] Manage the -v -? options
- [ ] Manage a simple IPv4 (address/hostname) as parameters
- [ ] Manage FQDN without doing the DNS resolution in the packet


```
-v, --verbose
    Verbose output. ICMP packets other than ECHO_RESPONSE that are received are listed.
```

Here is the output of the original `ping` command:

```bash
$> ping gnu.org

PING gnu.org (209.51.188.116) 56(84) bytes of data.
64 bytes from wildebeest1p.gnu.org (209.51.188.116): icmp_seq=1 ttl=54 time=111 ms
64 bytes from wildebeest1p.gnu.org (209.51.188.116): icmp_seq=2 ttl=54 time=104 ms
64 bytes from wildebeest1p.gnu.org (209.51.188.116): icmp_seq=3 ttl=54 time=106 ms

--- gnu.org ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2003ms
rtt min/avg/max/mdev = 103.695/106.628/110.551/2.884 ms
$> 
```

# DIAGRAM

if the server is reachable :
ICMP ECHOREQUEST -> INTERNET <- ECHO REPLY REQUEST

if the server is not reachable :
ICMP ECHOREQUEST -> INTERNET -X- DESTINATION UNREACHABLE (TIMEOUT)


## Infos

### Which protocol does the ping command?

The ping command uses ICMP protocol. ICMP protocol allows devices to exchange messages about various network conditions. It contains three types of messages: errors, queries, and responses.

Error messages are used to inform the sender about a condition or cause that prevents the sender's packets from reaching their destination. Query and response messages are used to exchange information about various network conditions.

Query and response messages are always used in pairs where one device sends a query message and another sends a reply or response to the query message. The ping command uses query-response messages.

### What is ICMP?

ICMP (Internet Control Message Protocol) is a network protocol used for sending error messages and operational information about network conditions. It's commonly used for diagnostic and control purposes within IP networks.


## How to code the ping command?

Lib:
- `getopt` to parse the command line arguments
- `socket` to create a socket
- `sendto` to send the ICMP packet
- `recvfrom` to receive the ICMP packet
- `gettimeofday` to get the current time
- `getaddrinfo` to get the IP address of a hostname
- `select` to wait for a response
- `signal` to handle signals


## References

- [Ping command explanation](https://www.computernetworkingnotes.com/networking-tutorials/ping-command-explained-with-examples.html)
- [What is ICMP](https://www.computernetworkingnotes.com/networking-tutorials/icmp-internet-control-message-protocol.html)
- [What is Ping video](https://www.youtube.com/watch?v=tVOHTjf94M8)
- [Making Ping command in ASM](https://www.youtube.com/watch?v=SxtX0VWZuME)
- [Simple tutorial for making ping](https://medium.com/@future_fanatic/how-to-ping-a-host-in-c-in-5-steps-88d22415109c)
- [ICMP more in depth explanation](https://inc0x0.com/icmp-ip-packets-ping-manually-create-and-send-icmp-ip-packets/)
- [ICMP echo responder](https://www.cs.dartmouth.edu/~sergey/cs60/lab3/lab3.pdf)