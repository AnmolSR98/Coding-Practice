The proxy server runs off the code in server.py, using meme.py to intercept certain requests and responses and replacing the images
with content from the memes folder, or replaces it with zazu.html in the case of a google http request.

The meme folder contains jpeg images, mostly comprised of impressionist artwork instead of memes (I repurposed a folder I already had
on my computer). 

meme.py functions to stick replacement data directly onto the end of HTTP responses, while also handling errors (ie. in the case of
invalid image paths, such as with an empty memes folder). There is also error handling for issues reading zazu.html

zazu.html is a simple html file used to replace the google.ca page.

