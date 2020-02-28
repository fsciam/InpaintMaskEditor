import sys
import cv2 as cv
import numpy as np
import copy

class LiveSketcher:
    def __init__(self, windowname, image):
        self.prev_pt = None
        self.windowname = windowname
        self.dests = [image.copy(),np.zeros(image.shape[:2],np.uint8)]
        self.steps=[]
        self.show()
        cv.setMouseCallback(self.windowname, self.on_mouse)

    def show(self):
        cv.imshow(self.windowname, self.dests[0])

    def undoLast(self):
        if self.steps:
            print("Undoing last line")
            self.dests=copy.deepcopy(self.steps.pop())
            self.show()
        else:
            print("Nothing to undo")

    def on_mouse(self, event, x, y, flags, param):
        pt = (x, y)
        if event == cv.EVENT_LBUTTONDOWN:
            if self.prev_pt == None:
                print("Saving")
                self.steps.append(copy.deepcopy(self.dests))

            self.prev_pt = pt

        elif event == cv.EVENT_LBUTTONUP:
            self.prev_pt = None

        if self.prev_pt and flags & cv.EVENT_FLAG_LBUTTON:

            for dst in self.dests:
                cv.line(dst, self.prev_pt, pt, (255,255,255), 5)
            self.prev_pt = pt
            self.show()

def photo_restoration(image_path):
    print("Opening: "+image_path)
    image=cv.imread(image_path)

    if image is not None:

        sketch = LiveSketcher("Original", image)
        cv.createTrackbar("InPaint radius","Original",0,20,lambda val : None)
        cv.imshow('Repaired')
        while True:
            ch = cv.waitKey()
            if ch == 27:
                break
            elif ch==ord('z'):
                sketch.undoLast()
            elif ch==ord('r'):
                result = cv.inpaint(image, sketch.dests[1], cv.getTrackbarPos("InPaint radius","Original"), cv.INPAINT_TELEA)
                cv.imshow('Repaired', result)
        cv.destroyAllWindows()
    else:
        print("[ERROR]: File "+image_path+" does not exists")


def main():
    if len(sys.argv) == 2:
        photo_restoration(sys.argv[1])
    else:
        print("Usage: photo_restoration.py <image-path>")

if __name__ == "__main__":
    main()
