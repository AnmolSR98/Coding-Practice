# meant to function as a proxy server
import socket, threading

# going to define global variables to make for easier use
host = '127.0.0.1'
port = 8080
delay = 1.0
chunk_size = 1024 # size of data to send (in bytes)

# holder function right now
def handleClient(ction, addr):
    
    # getting a message from the 
    request = ction.recv(4096)

    try: 
        decodedRequest = request.decode()

        # create a new socket and forward the request through
        newSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        newSocket.bind((host, port))
        newSocket.listen(5)
        newSocket.send(request)

        # set up the listening loop here for the response
        while True:
            # get the response
            response = newSocket.recv(chunk_size)
            # print what the response was and send it to the client
            print(response.decode())
            ction.send(response)
            # close the socket
            newSocket.close()
            break

    except Exception as e:
        print(e)

def main():
    # creating a socket for use
    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # binding the socket to the port
        mySocket.bind((host, port))

        # set into listening mode
        mySocket.listen(5)

        # running the while loop
        while True:

            # check for any connections
            ction, addr = mySocket.accept()

            # enmeshing potential connections into their own handleClient thread
            threading.Thread(target= handleClient, args = (ction, addr)).start()

        

    except Exception as e:
        print(e)

    if __name__ == "__main__":
        main()
