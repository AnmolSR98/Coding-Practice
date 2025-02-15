# import socket
import socket

# import time for timeout function
import time

# import threading to be used for timeout function
import threading

# importing encrytion library
import encryption as en

# variable for the encryption
encrypt = 5

def getMessage(socket, list):

    # get a message and then place it into a receiving list, taking advantage of the fact that lists are mutable in python
    try:
        msg = socket.recv(1024)
        list.append(msg)
    except Exception as e:
        print("", end ="") # Do nothing in this case

def main(): 

    # setting up two variables to handle timeouts
    sendTime, currentTime = 0, 0

    # counter var for the number of failed tries
    connectTries = 0

    # create a socket object
    mySocket = socket.socket()

    # defining the port and host to connect to
    port = 5000
    host = 'localhost'

    # setting mode to be undefined by default
    mode = -1

    try:
        # connect to local computer server
        mySocket.connect((host, port)) # always the address for the immediate LAN

        # main loop here
        while True:

            while (mode == -1):
                # get the input from the user
                userin = input("What would you like to do (select one of the following options)?:\n1. Simple Palindrome Check.\n2. Advanced Palindrome Check\n3. Close connection.\n")
                # run a loop if it doesn't go through
                try:
                    mode = int(userin)
                except Exception as e:
                    mode = -1
                    print("Enter a valid option!\n")

            # close the connection if the user requests
            if (mode == 3):
                # send a socket close message
                mySocket.send(en.encrypt("{0}".format(mode), encrypt).encode())
                mySocket.close()
                break

            # otherwise get string for the palindrome checks
            elif (mode == 1):
                userin = input("Enter a string for the simple palindrome check: ")

            else:
                userin = input("Enter a string for the advanced palindrome check: ")

            # send the actual string itself
            mySocket.send(en.encrypt("{0}.".format(mode) + userin, encrypt).encode())

            # get the send time
            sendTime = time.time()

            # create a receiving list to get the message from the server
            recvList = []

            # start a thread for receiving a message 
            recvThread = threading.Thread(target = getMessage, args = (mySocket, recvList))
            recvThread.start()

            # run a while loop waiting for the server response
            while (len(recvList) == 0):

                # get the current time
                currentTime = time.time()

                # if the server hasn't replied and the client hasn't tried three reconnects 
                if (connectTries < 3) and (currentTime - sendTime > (connectTries + 1) * 5):
                    # attempt to reconnect
                    print("Attempting to reestablish connection!\n")
                    # disconnect socket first
                    mySocket.close()
                    # reconstruct it
                    mySocket = socket.socket()
                    # connect to local computer server
                    mySocket.connect((host, port))
                    # send the actual string itself
                    mySocket.send(en.encrypt("{0}.".format(mode) + userin, encrypt).encode())
                    # create a receiving list to get the message from the server
                    recvList = []
                    # start a thread for receiving a message 
                    recvThread = threading.Thread(target = getMessage, args = (mySocket, recvList))
                    recvThread.start()

                    connectTries += 1

                # if it has tried three times to no success break this current loop
                if connectTries == 3:
                    print("Connection retries have failed, client shutting down!")
                    break

            # and then break the overall loop too
            if connectTries == 3:
                mySocket.close()    
                break

            # receive data from server and then decode the string
            print(en.decrypt(recvList[0].decode(), encrypt)) 

            # resetting mode so that user menu shows back up again
            mode = -1

            # also resetting the connection tries variable too
            connectTries = 0

    # exception handling for connection refused error and extraneous categories
    except ConnectionRefusedError:
        print(f"Connection to {host}:{port} failed")

    except Exception as e:
        print(e)

if __name__ == "__main__":
    main()