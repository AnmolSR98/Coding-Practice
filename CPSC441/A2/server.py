# socket for basic functionality, time for delays, and threading for concurrency
import socket, threading, time
from urllib.parse import urlparse

# random seed value for the replacement image algorithm
import random

# meme replacement library
import meme

# host, port, delay, and chunk size value (in bytes)
HOST = '127.0.0.1'
PORT = 8080
DELAY = 1.0
CHUNK_SIZE = 1024 * 512

# constructing a new response for when an algorithm requests an image
def constructNewResponse(responseArray):

    # random seed value string
    seedString = random.randint(1, 15) * "a"

    # getting the image data itself
    image = meme.replaceMeme(seedString)

    # reconstructing the response 
    newResponse = b''
    for portion in responseArray:
        # leave the very last bit of the response (the original image out)
        if portion != responseArray[len(responseArray) - 1]:
            # update content-length to the new value
            if b'Content-Length' in portion:
                portion = 'Content-Length: {0}'.format(len(image)).encode()

            # add the new portion of the response on
            newResponse += portion + b'\r\n'

    # finally, add the image back on and return the response
    newResponse += image

    return newResponse


# client handler function, doesn't really do keep-alive connections right now though
def handleClient(ction):
    
    # getting a message from the client socket
    request = ction.recv(4096)

    # try except block for handling 
    try: 
        # decode the request
        decodedRequest = request.decode()

        # split up into the url components
        first_line = decodedRequest.split('\r\n')[0]
        url = first_line.split(' ')[1]
        parsed_url = urlparse(url)

        port = parsed_url.port if parsed_url.port else 80

        host = parsed_url.hostname
        path = parsed_url.path + '?' + parsed_url.query if parsed_url.query else parsed_url.path
        if not path:
            path = '/'

        # if the url is for http google then just send the meme html page and exit the client handler
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

            # get the response from the new socket
            response = newSocket.recv(CHUNK_SIZE)
            if not response:
                break

            # redirection response handling
            if b'HTTP/1.1 301' in response:
                headers = response.split(b'\r\n')
                for header in headers:
                    if b'Location: ' in header:
                        new_url = header.split(b'Location: ')[1].strip()
                        print(f"Redirecting to {new_url.decode('utf-8')}")
                        return handleClient(newSocket)  # Recursive call with new URL
            
            # normal response handling
            if b'HTTP/1.1 200 OK' in response:
                responseArray = response.split(b'\r\n')
                for section in responseArray:
                    # if the response contains an image, intercept it
                    if b'Content-Type' in section:
                        if b'image' in section:
                            response = constructNewResponse(responseArray)

            # send the response over the connection
            ction.send(response) 
            time.sleep(DELAY)  

            # close the socket
            newSocket.close()
            break

    except Exception as e:
        print(e)

    #close the connection
    finally:
        ction.close()

# start proxy function to get the server up and running
def startProxy():

    # notification message that the proxy server has started up
    print(f"Sloxy running on {HOST}:{PORT}, with a delay of {DELAY} seconds per {CHUNK_SIZE} bytes.")

    try:
        # creating a socket for use
        mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        mySocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        # binding the socket to the PORT
        mySocket.bind((HOST, PORT))
        
        # set into listening mode
        mySocket.listen(5)

        # running the while loop
        while True:

            # check for any connections and accept
            ction, addr = mySocket.accept()

            # have the server print an accept message
            print(f"Server has received a connection from <{ction}:{addr}>.")

            # enmeshing potential connections into their own handleClient thread
            threading.Thread(target= handleClient, args = (ction, )).start()

    # exception handler
    except Exception as e:
        print("Server has encountered error: " + e)

if __name__ == "__main__":
    startProxy()
