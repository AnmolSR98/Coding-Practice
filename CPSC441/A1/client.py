import socket

# create a socket object
mySocket = socket.socket()

# defining the port to connect to
port = 1976

# connect to local computer server
mySocket.connect(('127.0.0.1', port)) # always the address for the immediate LAN

# receive data from server and then decode the string
print(mySocket.recv(1024)) # 1024 is buffer I think ???

# closing the socket
mySocket.close()