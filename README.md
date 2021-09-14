# chat

Direct messaging two-user chat application that utilizes network socket programming with C.

## Technologies

### C

### Socket Programming

### Threading

## Launch

To run, open two terminals, go to project directory and type in first terminal:

```
gcc -pthread -o server server.c chat.c
./server
```

Then type in the second terminal:

```
gcc -pthread -o client client.c chat.c
./client
```

Note: Currently the code contains the loop back IP address. To message between different machines, the IP address of the server must be entered in the client file.
