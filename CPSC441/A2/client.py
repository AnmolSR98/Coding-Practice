import socket
import os

# needed for image saving
import requests

# methods are separated out for both image and regular reponses
def handleImageResponse(response, url):

    with open(response, "r") as file:
        print(file.readlines)

    return

def handleNormalResponse(response, url):

     # Attempt to split the response into headers and body
    
    parts = response.split(b'\r\n\r\n', 1)
    if len(parts) == 2:
        headers, body = parts
        filename = os.path.basename(url)
        if not filename:
            filename = "downloaded_file"

        with open(filename, 'wb') as file:
            file.write(body)
            print(f"File has been saved as {filename}")
    else:
        print("Unexpected response format.")

# just following along for the template with this
def send_request(host, port, url):

    # create a socket object
    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect to the proxy server
    mySocket.connect((host, port))

    # create a get request
    request = f"GET {url} HTTP/1.1\r\nHost: testfile.org\r\nConnection: close\r\n\r\n"

    # send the get requets
    mySocket.send(request.encode())

    # check for response
    # Receive the response from the proxy server
    response = b""
    while True:
        part = mySocket.recv(4096)
        if not part:
            break
        response += part

    # Check if the response is returning an image or not, if not then proceed normally
    if not(response.decode()[-4:] == ".jpg"):
        handleNormalResponse(response, url)
    
    # otherwise access whatever has been left to us in the cache
    else:
        handleImageResponse(response, url)

    # close the client socket
    mySocket.close()

if __name__ == "__main__":
    HOST = "127.0.0.1"
    PORT = 8080
    URL = "https://s28.q4cdn.com/392171258/files/doc_downloads/test.pdf"
    ALT = "https://upload.wikimedia.org/wikipedia/commons/b/bf/Federer_serving_Cropped.jpg"
    EASTER = "https://www.google.ca"
    send_request(HOST, PORT, EASTER)