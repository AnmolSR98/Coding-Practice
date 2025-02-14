import socket
# Still need to wrap everything in try except block

def main(): 

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
                mySocket.send(("{0}".format(mode)).encode())
                mySocket.close()
                break

            # otherwise get string for the palindrome checks
            elif (mode == 1):
                userin = input("Enter a string for the simple palindrome check: ")

            else:
                userin = input("Enter a string for the advanced palindrome check: ")

            # send the actual string itself
            mySocket.send(("{0}.".format(mode) + userin).encode())

            # receive data from server and then decode the string
            print(mySocket.recv(1024).decode()) # 1024 is buffer I think ???

            # resetting mode so that user menu shows back up again
            mode = -1

    # exception handling for connection refused error and extraneous categories
    except ConnectionRefusedError:
        print(f"Connection to {host}:{port} failed")

    except Exception as e:
        print(e)

if __name__ == "__main__":
    main()