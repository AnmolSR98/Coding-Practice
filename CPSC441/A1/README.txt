The code is divided into four separate segments: the client, the server, the encryption library, and the palindrome library. 
    
The client will simply present some options to the user, and will attempt reconnection in the case of a late server reply. This is done by 
running a separate thread that places the response into a list, and the check loop will terminate if it detects the list has indeed received
a response. It also encrypts the message prior to sending it.

The server is more straightforward, logging interactions and running each client in its own thread to handle many different connections. The
server handles the palindrome functionality, although it imports this from the palindrome library. It also decrypts the message prior to 
processing it.

The palindrome library can run a simple check and advanced check as specified within the assignment description, and it also filters through 
any non alphabetical characters in the strings that are passed along to it. 

The encryption library makes use of a Caesar cipher as a form of basic encryption, which both the client and server make use of.