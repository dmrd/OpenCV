import cv

#Create window, init camera
cv.NamedWindow("camera", 1)
capture = cv.CaptureFromCAM(0)

while True:
    img = cv.QueryFrame(capture)
    out = cv.CloneImage(img)
    cv.Flip(img, out, 1) #Flips the image to the right side
    cv.ShowImage("camera", out)
    if cv.WaitKey(10) == 27: #Break on esc
        break
cv.DestroyWindow("camera")
