# Inpaint mask editor

Here in this repo you can find a simple program that allows you to draw masks for OpenCV inpaint function and see the result of the algorithm.

Both python and c++ code available.


## C++
#### Installation
Go to **c++** folder and create and open a new folder **build**. Once inside **build** launch:

`cmake ..`

and after that:

`make`

#### Usage
Once builded, from build folder, simply launch:

` ./PhotoRestoration <image_path>`

where **\<image_path\>** is the path of your image
## Python

Python code does not need installation, once you've cloned the repo and navigated to the python folder type:

`python3 photo_restoration.py <image_path>`

where **\<image_path\>** is the path of your image    

### Commands
- <kbd>l</kbd> : enable drawing
- <kbd>z</kbd> : undo last line
- <kbd>r</kbd> : repair image
- <kbd>esc</kbd> : close program
