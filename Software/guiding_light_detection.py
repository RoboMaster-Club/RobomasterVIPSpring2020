import cv2
import numpy as np

CV_CAP_PROP_BRIGHTNESS = 10
CV_CAP_PROP_CONTRAST = 11
CV_CAP_PROP_SATURATION = 12
CV_CAP_PROP_HUE = 13
CV_CAP_PROP_GAIN = 14
CV_CAP_PROP_EXPOSURE = 15

cap = cv2.VideoCapture(0) #may be 0 or 1

cap.set(CV_CAP_PROP_BRIGHTNESS, 0)
cap.set(CV_CAP_PROP_CONTRAST, 32)
cap.set(CV_CAP_PROP_SATURATION, 32)
cap.set(CV_CAP_PROP_GAIN, 0)
cap.set(CV_CAP_PROP_EXPOSURE, 0)

while True:
    _, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Thresholding
    lower = np.array([57, 140, 0])
    upper = np.array([94, 255, 156])
    mask = cv2.inRange(hsv, lower, upper)

    # Morphology
    kernel = np.ones((3,3), np.uint8)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

    # Fit Circles
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    cv2.drawContours(hsv, contours, -1, (0, 0, 255), 3)

    for contour in contours:
        (x,y), radius = cv2.minEnclosingCircle(contour)
        center = (int(x), int(y))
        radius = int(radius)
        cv2.circle(frame, center, radius, (255,0,0), 2)

    cv2.imshow('frame', frame)
    cv2.imshow('hsv', hsv)
    cv2.imshow('mask', mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()