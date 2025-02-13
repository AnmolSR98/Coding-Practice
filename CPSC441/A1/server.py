import socket
import threading
import logging
from collections import Counter

# importing palindrome for use
import palindrome as p

# Set up basic logging configuration
logging.basicConfig(filename='server_log.txt', level=logging.INFO, format='%(asctime)s - %(message)s')

# setting up a generalized handleClient function that will have to be enmeshed in a thread
def handleClient(ction, addr):

    try:

        # setting up the server listening loop here
        while True:

            # get a message
            msg = ction.recv(1024)

            # if msg is blank, break this whole damn loop
            if msg.decode() == "3":
                print("whatevs")
                break

            else:
                # splitting the message after decoding it
                mode, word = int( msg.decode().split(".")[0] ), msg.decode().split(".")[1]

            if mode == 1:
                # set the result of that message
                ction.send(f"{p.isPalindrome(word)}".encode())

            elif mode == 2:
                # set the result of that message
                ction.send(f"{p.canBePalindrome(word)} {p.getPalindromeComplexity(word)}".encode())

    finally:

        # close the connection
        ction.close()



def main():

    # creating a socket for use
    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # setting a host
    host = 'localhost'

    # creating a port number to be whatevers
    port = 5000

    try:
        # binding the socket generated to the port
        mySocket.bind((host, port))

        # put the socket into listening mode
        mySocket.listen(5)

        # while 
        while True:
            # get connection from some client
            ction, addr = mySocket.accept()
            # enmeshing any potential connection into a thread
            threading.Thread(target = handleClient, args = (ction, addr)).start()

    except Exception as e:

        # print the value of exception
        print(e)

if __name__ == "__main__":
    main()