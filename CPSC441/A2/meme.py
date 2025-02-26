

def replaceMeme(imageName):
    
    # just take the name of the image in binary, convert it to a number and replace with appropriate jpeg
    repImage = (len(imageName) - 4) % 15
    newImage = f"./memes/{repImage}.jpg"

    return newImage.encode()

def googleEasterEgg():

    return f"Federer_serving_Cropped.jpg"

if __name__ == "__main__":

    with open('./memes/15.jpg', 'rb') as file:
        rawdata = file.read()
        print(rawdata)