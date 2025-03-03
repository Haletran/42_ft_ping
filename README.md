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