import socket

# creating a socket for use
mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# creating a port number to be whatevers
port = 1976

# binding the socket generated to the port
mySocket.bind(('', port))

# put the socket into listening mode
mySocket.listen(5)

# setting up a loop where the server is forever listening until shutdown
while True:

    # get connection from some client
    ction, addr = mySocket.accept()

    # acknowledge message from client
    ction.send('Message received!'.encode())

    # close the connection
    ction.close()

    break