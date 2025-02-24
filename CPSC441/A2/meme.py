

def replaceMeme(imageName):
    
    # just take the name of the image in binary, convert it to a number and replace with appropriate jpeg
    repImage = (len(imageName) - 3) % 15
    newImage = f"/memes/{repImage}.jpg"

    return newImage

def googleEasterEgg():

    return f"Federer_serving_Cropped.jpg"

if __name__ == "__main__":
    print(replaceMeme("Federer_serving_Cropped.jpg"))