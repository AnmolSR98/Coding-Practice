import socket
# Still need to wrap everything in try except block

def main(): 

    # create a socket object
    mySocket = socket.socket()

    # defining the port and host to connect to
    port = 5000
    host = '127.0.0.1'

    try:
        # connect to local computer server
        mySocket.connect((host, port)) # always the address for the immediate LAN

        # get the input from the user
        userin = input("\n")

        mySocket.send(userin.encode())

        # receive data from server and then decode the string
        print(mySocket.recv(1024).decode()) # 1024 is buffer I think ???

    except ConnectionRefusedError:
        print(f"Connection to {host}:{port} failed")

    except Exception as e:
        print(e)

    # closing the socket
    mySocket.close()

if __name__ == "__main__":
    main()