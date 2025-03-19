import socket

# need to add multithreading here
import threading

# need to use random
import random

# add something to store the whole chat log up until this point??? MAYBE

# Panda facts and emojis
PANDA_EMOJIS = ["ʕ•ᴥ•ʔ", "ʕ>ᴥ<ʔ", "ʕOᴥOʔ", "ʕ-ᴥ-ʔ", "ʕ^ᴥ^ʔ"]
PANDA_FACTS = [
 "Pandas spend around 14 hours a day eating bamboo! ",
 "Baby pandas are born pink and weigh only about 100 grams! ",
 "A group of pandas is called an embarrassment! ",
 "Pandas can swim and are excellent tree climbers! ",
 "There are only about 1,800 giant pandas left in the wild. "
]

# using a list to get all of the clients
allClients = []

# also have a dictionary that contains all the names
clientNames = {}

# these two functions just return randomly picked emojis/facts
def getFact():
    return random.choice(PANDA_FACTS)

def getEmoji():
    return random.choice(PANDA_EMOJIS)

# to broadcast a message to all the other clients
def clientBroadcast(conn, message):
    for client in allClients:
        if client != conn:
            client.sendall(message.encode())

# wrapping into a thread for handling multiple clients
def handleClient(conn, addr):

    while True:

        try:
            # eeceive data from the client
            data = conn.recv(1024).decode()

            # check for the exit command
            if data.lower().find("@leaves") != -1:
                conn.sendall("SHUTDOWN".encode())

                # sends disconnect message to all clients
                clientBroadcast(conn, f"{clientNames[conn]} has left the chat.")

                allClients.remove(conn)
                print("Client disconnected.")
                break

            # check for the facts command
            elif data.lower().find("@bamboo") != -1:
                conn.sendall(getFact().encode())

            # check for the grove command
            elif data.lower().find("@grove") != -1:
                names = []
                for client in allClients:
                    names.append(clientNames[client])
                conn.sendall(f"{names}".encode())

            # miscellaneous for the other messages
            else:
                # replace the name with the addr if no unique name and add the panda emoji
                response = data
                if response.find("has_no_name") != -1:
                    clientNames[conn] = addr
                    pieces = response.split(":")
                    response = f"client{addr}: " + pieces[1] + f" {getEmoji()}"

                # otherwise just add the emoji at the end
                else:
                    clientNames[conn] = response.split(":")[0]
                    response += f" {getEmoji()}"

                # the above means that usernames wont update in the server database until message is sent with the new username

                # send to the remaining clients
                clientBroadcast(conn, response)

        except Exception:
            allClients.remove(conn)
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
            clientBroadcast(conn, f"client{addr} has joined the chat.") # broadcast to the other clients that someone has joined the chat room

            threading.Thread(target = handleClient, args = (conn, addr)).start() # encase each connection in its own thread
                    

if __name__ == "__main__":
    main()
