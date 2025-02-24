# meant to function as a proxy server
import socket, threading, time
from urllib.parse import urlparse

# should probably just use meme directly here
import meme

# thing to get to download images
import requests

# going to define global variables to make for easier use
HOST = '127.0.0.1'
PORT = 8080
DELAY = 1.0
CHUNK_SIZE = 1024 # size of data to send (in bytes)

# for replacing image requests if needed
def intercept(host: str, path: str):

    # if the client isn't requesting an image do nothing
    if not(path[:-4] == ".jpg"):
        return None
    
    # otherwise forward it along
    else:
        # special case for google
        if (host == "www.google.ca"):
            return meme.googleEasterEgg

        # otherwise just replacement basic meme algorithm
        return meme.replaceMeme(path)

# holder function right now
def handleClient(ction):
    
    # getting a message from the 
    request = ction.recv(4096)

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

        # checking for any necessary intercepts
        potentialIntercept = intercept(host, path)

        # cut the whole process out if it should be intercept
        if potentialIntercept is not None:

            time.sleep(DELAY)
            ction.send(potentialIntercept)

        # create a new socket and forward the request through
        newSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        newSocket.connect((host, port))
        newSocket.send(request)

        # set up the listening loop here for the response
        while True:
            # get the response
            response = newSocket.recv(CHUNK_SIZE)
            # ction.send(response)

            parts = response.split(b'\r\n\r\n', 1)
            if len(parts) == 2:
                headers, body = parts
                filename = os.path.basename(url)
                if not filename:
                    filename = "downloaded_file"

                img_data = requests.get(url).content
                #print(headers)
                with open(filename, 'wb') as file:
                    file.write(img_data)
                    print(f"File has been saved as {filename}")
            else:
                print("Unexpected response format.")

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

            # enmeshing potential connections into their own handleClient thread
            threading.Thread(target= handleClient, args = (ction, )).start()

    except Exception as e:
        print(e)

if __name__ == "__main__":
    startProxy()
