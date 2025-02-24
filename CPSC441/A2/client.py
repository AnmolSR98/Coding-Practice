import socket
import os

# needed for image saving
import requests

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
    
    # Attempt to split the response into headers and body
    parts = response.split(b'\r\n\r\n', 1)
    print(parts)
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

    # close the client socket
    mySocket.close()

if __name__ == "__main__":
    HOST = "127.0.0.1"
    PORT = 8080
    URL = "https://s28.q4cdn.com/392171258/files/doc_downloads/test.pdf"
    ALT = "https://upload.wikimedia.org/wikipedia/commons/b/bf/Federer_serving_Cropped.jpg"
    send_request(HOST, PORT, ALT)