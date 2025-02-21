import socket
import os

# just following along for the template with this
def send_request(host, port, url):

    # create a socket object
    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect to the proxy server
    mySocket.connect((host, port))

    # create a get request
    request = f"GET {url} HTTP/1.1\r\nHost: testfile.org\r\nConnection:close\r\nAccept-language:en\r\n"

    # send the get requets
    mySocket.send(request.encode())

    # check for response
    response = mySocket.recv(1024).decode()

    if ("OK" in response):
        # do something here if 
        print(response)

    # close the client socket
    mySocket.close()

def main():

    # set up the standard stuff here
    print("placeholder")

if __name__ == "__main__":
    send_request("127.0.0.1", 8080, "https://s28.q4cdn.com/392171258/files/doc_downloads/test.pdf")