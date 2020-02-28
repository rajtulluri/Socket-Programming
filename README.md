# Socket-Programming
Sample codes for socket programming in C

The folder "Sample TCP Codes" contains the following codes :-
  1. A TCP Server-Client program which sorts and Integer array and searches in Integer array. The client sends the Integer array along with the option. The server performs the option and reverts with the result.
  2. A TCP Server-Client program which checks whether the string is a Palindrome or not. The client sends a string, server checks the string for Palindrome and reverts with the result.

The folder "File Handling Codes" contains the following codes :-
  1. TCP Server-Client program which Sorts the file based on ASCII, Searches for string in file and replaces string in the file. The Client sends the option along with the string if needed and server performs the option.
  2. The above code in UDP protocol style
  
The folder "Full & Half Duplex" contains the following codes :-
  1. TCP Server-Client program demonstrating full duplex chat.
  2. TCP Server-Client program demonstrating half duplex communication. The Client sends a string and the Server prints all permutations of the string.

The folder "DNS Implementation" contains codes to implement DNS protocol. The Client sends the domain name to the Server. Server searches in the database (sample given) and retrieAves the A record, the corresponding IP address is sent to the Client.

The folder "Multiple Client Connections" contains the following codes :-
  1. TCP Server-Client program to demonstrate a Concurrent Server. Everytime a Client connects to the Server, Server forks and assigns a child to the Client. In this program the 2 Clients send individual strings which the server combines and prints the result. At any time Server supports just 2 Clients.
  2. TCP Server_Client program to demonstrates an Iterative Server. The Clients are allowed to connect one after the other.
  
The folder "Network Simulations" contains codes for the widely used network simulator ns-2. The software helps visualize the network topology and traffic flows between nodes of the network. 
  1. Network Simulator ns-2 code to visualize the star topology with 5 nodes n0 to n4. The nodes n0 and n1 are source of the traffic, n2 and n3 are the sinks.
  2. Network Simulator ns-2 code to visualize the ring topology with 4 nodes n0 to n3 arranged in a square. The nodes n0 and n2 are the source, n1 and n3 are the sinks. The code also demonstartes link failure.
  3. Network Simulator ns-2 code to visualize a LAN network as shown in the picture below. All Server nodes send traffic to all Client nodes at the same time.
