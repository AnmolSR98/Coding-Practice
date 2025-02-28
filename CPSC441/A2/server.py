# meant to function as a proxy server
import socket, threading, time
from urllib.parse import urlparse

# random seed value for the thing
import random

# should probably just use meme directly here
import meme

# going to define global variables to make for easier use
HOST = '127.0.0.1'
PORT = 8080
DELAY = 1.0
CHUNK_SIZE = 1024 * 128 * 4 # size of data to send (in bytes)

# construct a response, which for now doesn't contain an image
def constructNewResponse(responseArray):

    # random seed value string
    seedString = random.randint(1, 15) * "a"

    image = meme.replaceMeme(seedString)

    newResponse = b''
    for portion in responseArray:
        if portion != responseArray[len(responseArray) - 1]:
            if b'Content-Length' in portion:
                portion = 'Content-Length: {0}'.format(len(image)).encode()

            newResponse += portion + b'\r\n'

    newResponse += image

    return newResponse


# holder function right now
def handleClient(ction):
    
    # getting a message from the 
    request = ction.recv(4096)
    print(request)

    try: 
        decodedRequest = request.decode()

        first_line = decodedRequest.split('\r\n')[0]
        url = first_line.split(' ')[1]
        parsed_url = urlparse(url)

        port = parsed_url.port if parsed_url.port else 80

        host = parsed_url.hostname
        path = parsed_url.path + '?' + parsed_url.query if parsed_url.query else parsed_url.path
        if not path:
            path = '/'

        if url == "http://google.ca/":
            ction.send(meme.googleReplacement())
            time.sleep(DELAY)
            ction.close()
            return

        # create a new socket and forward the request through
        newSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        newSocket.connect((host, port))
        newSocket.send(request)

        # set up the listening loop here for the response
        while True:
            # get the response
            response = newSocket.recv(CHUNK_SIZE)
            if not response:
                break

            if b'HTTP/1.1 301' in response:
                headers = response.split(b'\r\n')
                for header in headers:
                    if b'Location: ' in header:
                        new_url = header.split(b'Location: ')[1].strip()
                        print(f"Redirecting to {new_url.decode('utf-8')}")
                        return handleClient(newSocket)  # Recursive call with new URL
            
            # here is my actual snippet of my own code
            if b'HTTP/1.1 200 OK' in response:
                responseArray = response.split(b'\r\n')
                for section in responseArray:
                    if b'Content-Type' in section:
                        print(section)
                        if b'image' in section:
                            response = constructNewResponse(responseArray)


            ction.send(response)  # Forward to client
            time.sleep(DELAY)  # Slow down response

            # close the socket
            newSocket.close()
            break

    except Exception as e:
        print(e)

    #close the connection
    ction.close()

def startProxy():

    print(f"Sloxy running on {HOST}:{PORT}, with a delay of {DELAY} seconds per {CHUNK_SIZE} bytes.")

    try:
        #creating a socket for use
        mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        mySocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # binding the socket to the PORT
        mySocket.bind((HOST, PORT))
        # set into listening mode
        mySocket.listen(5)

        # running the while loop
        while True:

            # check for any connections
            ction, addr = mySocket.accept()

            # have the server print an accept message
            print(f"Server has received a connection from <{ction}:{addr}>.")

            # enmeshing potential connections into their own handleClient thread
            threading.Thread(target= handleClient, args = (ction, )).start()

    except Exception as e:
        print(e)

if __name__ == "__main__":
    startProxy()
