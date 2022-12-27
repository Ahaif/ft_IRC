# ft_IRC
    - This project is about creating our own Internet Relay Chat server-side
    - Connection and communication is used via sockets via TCP/IP (v4).
    - Using the IRC client with our server must be similar to using it with any official IRC server. However, we only have to implement the following features:
    - We must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using the IRC client.
    - All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel.
    - We must have operators and regular users.
    - Then, we have to implement the commands that are specific to operators.
    - check Subject
# Run 
    - make To start the Server, use:
    - ./ircserv <port> <password>
    - port: The port number on which your IRC server will be listening to for incoming IRC connections.
    - password: The connection password. It will be needed by any IRC client that tries to connect to your server. To connect to the server, you can use:
    - nc <IP ADDRESS> <PORT>
    - IP ADDRESS: Host IP address.
    - PORT: The PORT that the server listening on.
    - You can also use an IRC Client e.g LimeChat, WeeChat...


