# for the socket which is the primary method by which this works
import socket

# for multithreading, which is the concurrency solution
import threading

# logging to assist with writing stuff down in the server log txt
import logging

# importing palindrome for use
import palindrome as p

# importing encrytion library
import encryption as en

# variable for decrypting messages
encrypt = 5

# Set up basic logging configuration
logging.basicConfig(filename='server_log.txt', level=logging.INFO, format='%(asctime)s - %(message)s')

# setting up a generalized handleClient function that will have to be enmeshed in a thread
def handleClient(ction, addr):

    # insert a thing for logging the initial connection from here
    logging.info("Server received connection from {0}\n".format(addr))

    # setting up the server listening loop here
    while True:

        try:
            # get a message
            msg = ction.recv(1024)

            # need to add statement here about receiving a message from a specific connection
            logging.info("Server received message <{0}> from connection {1}\n".format(msg.decode(), addr))

            # if msg is blank, break this whole loop
            if en.decrypt(msg.decode(), encrypt) == "3":
                break

            else:
                # splitting the message after decoding it
                mode, word = int(  en.decrypt(msg.decode(), encrypt).split(".")[0] ), en.decrypt(msg.decode(), encrypt).split(".")[1]

            if mode == 1:
                # set the result in the message
                ction.send(en.encrypt( "{0}".format(p.isPalindrome(word)), encrypt ).encode())

            elif mode == 2:
                # set the result in the message
                ction.send(en.encrypt( "{0} {1}".format(p.canBePalindrome(word), p.getPalindromeComplexity(word)), encrypt ).encode())
        
        except Exception as e:
            break


    # close the connection
    ction.close()

    # insert a log thing for the connection being shut down
    logging.info("Server connection from {0} has been shut down.\n".format(addr))



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

        # log thing about server starting to listen
        logging.info("Server is listening on (Host:{0}, Port:{1}).\n".format(host, port))

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