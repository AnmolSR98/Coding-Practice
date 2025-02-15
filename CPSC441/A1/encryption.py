# just using a simple caesar cipher for encryption, basically just prevents those
# who have somehow tapped into the connection from directly reading the messages
# ala if they had access to the server logs

# technically, not a true caesar cipher since it doesn't loop back from z to a, but it still works

# encryption just adds an offset to the chars
def encrypt(someString, offset):
    newString = ""
    for elem in someString:
        newString += chr(ord(elem) + offset)

    return newString

# decryption just takes them away
def decrypt(someString, offset):
    newString = ""
    for elem in someString:
        newString += chr(ord(elem) - offset)

    return newString

if __name__ == "__main__":
    # test code
    newString = encrypt("3", 12)
    print(newString)
    newString = decrypt(newString, 12)
    print(newString)