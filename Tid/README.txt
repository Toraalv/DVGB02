These programs are part of assignment 3 in lab assignment 1 in DVGB02 at
Karlstad University and are only available for Linux.

The assignment is to create a UDP time client and server that implements RFC
868. The provided programs are binary-only solutions to the assignment that you
can use to verify if your solution is correct. They both conform to the UDP
version of the RFC 868, and they print debugging output when used.

Examples of how to run the client:
Terminal 1:
[student@farfaraway ]RFC868_udp$ ./server -h
sage: ./server [port]
A UDP based RFC868 server

      -h     display this help and exit

The server needs root priviliges to run on ports lower than 1024.
[student@farfaraway ]RFC868_udp$ ./server 8037

Terminal 2:
[student@farfaraway ]RFC868_udp$ ./client 127.0.0.1 8037

Note: if you want to run the server on the default port 37, then you will need
root privileges; therefore, use the following:
Terminal 1:
[student@farfaraway ]RFC868_udp$ sudo ./server

Terminal 2:
[student@farfaraway ]RFC868_udp$ ./client 127.0.0.1
