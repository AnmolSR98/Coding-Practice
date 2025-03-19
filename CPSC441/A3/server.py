import socket

# need to add multithreading here
import threading

# Panda facts and emojis (feel free to add more)
PANDA_EMOJIS = ["", "", "", "", ""]
PANDA_FACTS = [
 "Pandas spend around 14 hours a day eating bamboo! ",
 "Baby pandas are born pink and weigh only about 100 grams! ",
 "A group of pandas is called an embarrassment! ",
 "Pandas can swim and are excellent tree climbers! ",
 "There are only about 1,800 giant pandas left in the wild. "
]

# using a list to get all of the clients
allClients = []

def getFact():
    return "fact"

def getGrove():
    return allClients

def checkForCommands(message: str):
    
    if message.split(":")[1] == " @bamboo":
        return getFact()

    elif message.split(":")[1] == " @grove":
        return getGrove()

    elif message.split(":")[1] == " @leaves":
        print() # change to do the same thing that exit does

# wrapping into a thread for handling multiple clients
def handleClient(conn, addr):

    while True:

        try:
            # Step 1: Receive data from the client
            data = conn.recv(1024).decode()
            if not data or data.lower().find(": exit") != -1:
                print("Client disconnected.")
                break

            # Step 2: Potentially replace the username
            response = data
            if response.find("has_no_name") != -1:
                pieces = response.split(":")
                response = f"client{addr}: " + pieces[1]


            # Step 3: Send to the remaining clients
            for client in allClients:
                if client is not conn:
                    client.sendall(response.format(response).encode())

        except Exception:
            break 



def main():
    host = '127.0.0.1'  # Localhost
    port = 12345        # Port to listen on

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))
        server_socket.listen(1)  # Listen for 1 connection at a time
        print(f"Chatbot server is running on {host}:{port}...")

        while True:

            conn, addr = server_socket.accept()  # Accept incoming connections
            print(f"Connected by {addr}")

            allClients.append(conn) # adding to the master client list

            threading.Thread(target = handleClient, args = (conn, addr)).start() # encase each connection in its own thread
                    

if __name__ == "__main__":
    main()
