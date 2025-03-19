# obviously using socket module
import socket

# adding multithreading for the purposes of printing messages received from the server
import threading

# listen function that gets wrapped into its own thread
def listen(socket):

    while True:

        try:
            # get the response from the socket
            response = socket.recv(1024)

            # case where the server is shutting down the client's listen thread so the client terminates
            if response.decode() == "SHUTDOWN":
                print("Shutting down listening thread...")
                break

            else:

                # claers the previous line and print the new line
                # print("\033[A                             \033[A")
                print("\r" + response.decode())
                print("You: ", end = "")
        
        # in the case of an error 
        except Exception as e:
            print(e)
            break

# message handling function that gets wrapped in its own thread
def message(socket, clientName):

    print("You: ", end = "")
    
    # message input thread
    while True:

        try:
            # get the input from the user
            user_input = input()

            # case where the user is attempting to exit
            if user_input.lower() == "@leaves":
                print("Exiting message thread...")

                # forward the message to the server
                socket.sendall("@leaves".encode())
                break

            elif user_input.lower() == "@rename":
                clientName = input("Enter your new username: ")

            else:

                # add the client name to the message
                message = clientName + ": " + user_input

                # Send the message to the server and come to a new line
                socket.sendall(message.encode())
                print("You: ", end = "")

        # If an error occurs, print the error message and exit
        except Exception as e:
            print(e)
            break

def main():
    
    host = '127.0.0.1'  # Server's hostname or IP address
    port = 12345        # Server's port

    try:
        # create a socket
        print("Creating socket...")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:

            # connect to the server
            print(f"Connecting to server at {host}:{port}...")
            client_socket.connect((host, port))
            print(f"Connected to server at {host}:{port}")

            # NEED TO ADD SOMETHING INCASE THE THREADS FAIL TO INITIALIZE PROPERLY

            # create the listen thread and start it up
            listenThread = threading.Thread(target = listen, args = (client_socket, ))
            listenThread.start()

            # creating a global username for the client
            clientName = "has_no_name"

            # create a message thread and start it up
            messageThread = threading.Thread(target = message, args = (client_socket, clientName))
            messageThread.start()

            # to keep the socket alive, otherwise it reverts to a null object
            while (messageThread.is_alive() or listenThread.is_alive()):
                pass

    # error handling
    except ConnectionRefusedError:
        print(f"Connection to {host}:{port} failed. Ensure the server is running.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == "__main__":
    main()
