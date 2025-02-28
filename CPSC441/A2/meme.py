

def replaceMeme(imageName):
    
    # just take the name of the image in binary, convert it to a number and replace with appropriate jpeg
    repImage = ((len(imageName) - 4) % 15) + 1
    newImage = f"./memes/{repImage}.jpg"
    exceptionOccured = True

    while exceptionOccured:
        try:
            image = open(newImage, 'rb')
            imageData = image.read()

        except Exception:
            print("Error with image reading, will try again")

        else:
            exceptionOccured = False

        finally:
            image.close()

    return imageData

def googleReplacement():

    page = open('zazu.html', 'rb')
    pageData = page.read()
    print(pageData)
    page.close()

    response = f'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: {len(pageData)}'.encode()
    response += pageData

    return response