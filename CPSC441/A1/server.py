import socket
import os

# importing palindrome for use
import palindrome as p

def main():

    # creating a socket for use
    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # creating a port number to be whatevers
    port = 5000

    try:
        # binding the socket generated to the port
        mySocket.bind(('', port))

        # put the socket into listening mode
        mySocket.listen(1)

        # get connection from some client
        ction, addr = mySocket.accept()

        # get a message
        msg = ction.recv(1024)

        # set the result of that message
        ction.send(f"{p.isPalindrome(msg.decode())}".encode())

        # close the connection
        ction.close()

    except Exception as e:
        print(e)

if __name__ == "__main__":
    main()