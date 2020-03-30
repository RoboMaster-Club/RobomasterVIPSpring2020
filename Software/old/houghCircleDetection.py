import cv2
import numpy as np

cap = cv2.VideoCapture(0)
_, frame = cap.read()
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

hArray = []
sArray = []
vArray = []

def showHSV(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN: #checks mouse left button down condition
        hArray.append(hsv[y,x,0])
        sArray.append(hsv[y,x,1])
        vArray.append(hsv[y,x,2])
        print("HSV: ", hsv[y,x,0], hsv[y,x,1], hsv[y,x,2])

def showBGR(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN: #checks mouse left button down condition
        print("BGR: ", frame[y,x,0], frame[y,x,1], frame[y,x,2])

# Read an image, a window and bind the function to window
cv2.namedWindow('hsv')
cv2.setMouseCallback('hsv', showHSV)

cv2.namedWindow('frame')
cv2.setMouseCallback('frame', showBGR)

while True:
    _, frame = cap.read()

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # yellow tape measure
    # lower = np.array([8, 80, 160])
    # upper = np.array([40, 255, 255])

    # red paper circle
    lower = np.array([164, 120, 112])
    upper = np.array([178, 233, 193])

    mask = cv2.inRange(hsv, lower, upper)

    kernel = np.ones((3,3), np.uint8)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
    mask = cv2.medianBlur(mask,5)

    circles = cv2.HoughCircles(mask,cv2.HOUGH_GRADIENT, 1, mask.shape[0]/4, param1=200,param2=10,minRadius=0,maxRadius=0)

    if circles is not None:
        circles = np.uint16(np.around(circles))
        for i in circles[0,:]:
            # draw the outer circle
            cv2.circle(frame,(i[0],i[1]),i[2],(0,255,0),2)
            # draw the center of the circle
            cv2.circle(frame,(i[0],i[1]),2,(0,0,255),3)

    cv2.imshow('frame', frame)
    cv2.imshow('hsv', hsv)
    cv2.imshow('mask', mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()

if len(hArray) != 0:
    print ('H min max: ', min(hArray), max(hArray))
    print ('S min max: ', min(sArray), max(sArray))
    print ('V min max: ', min(vArray), max(vArray))