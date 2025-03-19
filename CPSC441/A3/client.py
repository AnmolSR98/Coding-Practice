import socket

# adding multithreading for the purposes of printing messages received from the server
import threading

def listen(socket, fluff):

    while True:

        try:
            response = socket.recv(1024)
            # claers the previous line
            print("\033[A                             \033[A")
            print(response.decode())
            print()
            print("You: ", end = "")
        
        except Exception as e:
            print(e)
            break

def message(socket, clientName):

    print("You: ", end = "")
    
    # message input thread
    while True:

        try:
            # Step 1: Get input from the user
            user_input = input()
            if user_input.lower() == "exit":
                print("Exiting...")
                socket.sendall("exit".encode())
                break

            message = clientName + ": " + user_input

            # Step 2: Send the message to the server
            socket.sendall(message.encode())
            print("You: ", end = "")

        except Exception as e:
            print(e)
            break

def main():
    host = '127.0.0.1'  # Server's hostname or IP address
    port = 12345        # Server's port

    try:
        # Step 1: Create a socket
        print("Creating socket...")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            # Step 2: Connect to the server
            print(f"Connecting to server at {host}:{port}...")
            client_socket.connect((host, port))
            print(f"Connected to server at {host}:{port}")

            threading.Thread(target = listen, args = (client_socket, 0)).start()

            # creating a global username for the client
            clientName = "has_no_name"

            messageThread = threading.Thread(target = message, args = (client_socket, clientName))
            messageThread.start()

            while (messageThread.is_alive):
                pass

    except ConnectionRefusedError:
        print(f"Connection to {host}:{port} failed. Ensure the server is running.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == "__main__":
    main()
