# the meme library contains all the functions needed to replace a potential request
def replaceMeme(imageName):

    # just take the name of the image and convert it to a random digit between 1 and 15
    repImage = ((len(imageName) - 4) % 15) + 1
    newImage = f"./memes/{repImage}.jpg"
    
    # error handling in case of wrong path or empty meme folder
    try:
        # read in binary mode, not utf-8
        image = open(newImage, 'rb')
        imageData = image.read()

    except Exception:
        print("Error with image reading.")

    else:
        image.close()

    # return the image data
    return imageData

# function for replacing the google home page
def googleReplacement():

    # open the html file, read it in binary
    page = open('zazu.html', 'rb')
    pageData = page.read()
    page.close()

    # then add onto response and return it
    response = f'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: {len(pageData)}'.encode()
    response += pageData
    return response