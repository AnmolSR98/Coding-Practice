This chat server consists of two files, server and client that were based off the chat client and chat server files from D2L.

The server operates as a chat room, forwarding messages it receives from one client to all of the others, inserting panda emoticons to standard
messages via getEmoji. Each client is handled in its own thread handleClient thread. For @bamboo, it uses getFact to get panda facts. For @grove, it keeps both a dictionary of all connections and their
nicknames (given by the client) and a list of current sockets and uses the socket as the key value for a user (this means multiple users can have 
the same nicknames), using the sockets to return a list of nicknames. Nicknames update upon receiving a message from a user with a username that
doesn't match the user's recorded nickname. For both proper @leaves and ungraceful connections, the server deletes the 
socket from its list of sockets while also broadcast the users departure to the other active users. It also sends the SHUTDOWN message to a user 
which has requested a @leaves, which causes the listen thread in the client to end.

The client operates as two separate threads: one for sending (encased in a thread for message()) and one for receiving (encased in a thread for
listen()). The receiving thread is somewhat self explanatory, receiving from other users forwarded by the server, printing them and shifting the
user's typebox down a line. It breaks in the event of receiving the message SHUTDOWN from the server, which is the final step in the graceful 
disconnect. The sending thread is slightly more complex, as it handles the @rename operation. The client takes the user input, tacks on the 
client's nickname and sends it to the server. 

I've decided to provide a separate paragraph on the @leaves procedure. The user simply types in @leaves in the typebox, which triggers the message
function to print an exit message, send the @leaves message to the server, and break its own input loop. The server then receives this @leaves
message, removes the client from its list, broadcasts its departure and then sends a SHUTDOWN message to the client to break the loop within the
client's listen thread, and the client prints another exit message.