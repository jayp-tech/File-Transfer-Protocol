# File-Transfer-Protocol
Send a text file from one computer to another using File Transfer Protocol using C programming.

![image](https://user-images.githubusercontent.com/82361158/115295435-61dd3800-a177-11eb-9871-a56b486a8053.png)

The source code for server and client is given in "server.c" and "client.c".

# For compiling the code

On server

```   $ gcc server.c -o server  ```

On client

```  $ gcc client.c -o client ``` 

# To run the code

First on the server node

``` $ ./server <Server Port number> ```

The on Client’s terminal run

``` $ ./client <Server IP Address> <Server Port number> ```

After running the code, enter the commands in client’s terminal in legal command format. The server code needs to executed once and shall be closed using “Ctrl + C” in the server machine. Every client on execution develops a connection with the server and the same socket connection is maintained. until the client program exit. USE COMMAND “EXIT” to quit client program. This will disconnect the client. Running the client program again shall develop a new connection again.
