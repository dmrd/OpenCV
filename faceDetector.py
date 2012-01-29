import cv
#Obviously incredibly slow since it is in Python...

#Create window, init camera
cv.NamedWindow("camera", 1)
capture = cv.CaptureFromCAM(0)

haar = cv.Load("/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml")

while True:
    img = cv.QueryFrame(capture)
    out = cv.CloneImage(img)
    cv.Flip(img, out, 1) #Flips the image to the right side

    #Returns bounding boxes on all detected faces in the image
    faces = cv.HaarDetectObjects(out, haar, cv.CreateMemStorage())
    for (x, y, w, h),n in faces:
        cv.Rectangle(out, (x,y), (x+w, y+h), 255)
    cv.ShowImage("camera", out)
    if cv.WaitKey(10) == 27: #Break on esc
        break
cv.DestroyWindow("camera")
