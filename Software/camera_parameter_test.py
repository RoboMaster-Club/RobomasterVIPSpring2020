import cv2
import numpy as np

CV_CAP_PROP_BRIGHTNESS = 10
CV_CAP_PROP_CONTRAST = 11
CV_CAP_PROP_SATURATION = 12
CV_CAP_PROP_HUE = 13
CV_CAP_PROP_GAIN = 14
CV_CAP_PROP_EXPOSURE = 15

#Note: invalid set values will not be registered, last valid value is used

cap = cv2.VideoCapture(0) #may be 0 or 1
_, frame = cap.read()
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

def showHSV(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN: #checks mouse left button down condition
        print("HSV: ", hsv[y,x,0], hsv[y,x,1], hsv[y,x,2])

cv2.namedWindow('hsv')
cv2.setMouseCallback('hsv', showHSV)

cap.set(CV_CAP_PROP_BRIGHTNESS, 0)
#0 lower limit, image is dark, light is white
#128 default
#255 upper limit, image is bright

cap.set(CV_CAP_PROP_CONTRAST, 32)
#0 lower limit, nothing is visible
#32 default
#128 image is dark, light is white
#255 upper limit, image is dark, light is white

cap.set(CV_CAP_PROP_SATURATION, 32)
#0 lower limit, image is grayscale
#32 default
#128 colors slightly more vibrant, light is white
#255 upper limit, image looks fuzzy, light is white, 

cap.set(CV_CAP_PROP_HUE, -1)
#-1 default, hue likely isn't supported on a longitech webcam

cap.set(CV_CAP_PROP_GAIN, 0)
#0 lower limit, image is slightly darker, light is white
#44 default
#128 image is bright, light is white
#255 upper limit, image is bright, light is white

cap.set(CV_CAP_PROP_EXPOSURE, 0)
#-9 lower limit?
#-6 default
#-3 image is dark, light is the same
#0 image is black, light is green, upper limit

while True:
    _, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    #print(cap.get(CV_CAP_PROP_BRIGHTNESS))

    cv2.imshow('frame', frame)
    cv2.imshow('hsv', hsv)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()