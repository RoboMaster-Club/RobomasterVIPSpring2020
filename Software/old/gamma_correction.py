import numpy as np
import cv2
from matplotlib import pyplot as plt

GAMMA = 0.05

def adjust_gamma(image, gamma=1.0):
	invGamma = 1.0 / gamma
	table = np.array([((i / 255.0) ** invGamma) * 255
		for i in np.arange(0, 256)]).astype("uint8")

	return cv2.LUT(image, table)

cap = cv2.VideoCapture(0)

while True:
    _, frame = cap.read()
    darkFrame = frame.copy()
    darkFrame = adjust_gamma(darkFrame, GAMMA)

    greenDarkFrame = darkFrame.copy()
    greenDarkFrame = cv2.cvtColor(greenDarkFrame, cv2.COLOR_BGR2HSV)
    lower_green = np.array([120, 100, 100])
    upper_green = np.array([180, 255, 255])
    mask = cv2.inRange(greenDarkFrame, lower_green, upper_green)
    greenDarkFrame = cv2.bitwise_and(greenDarkFrame, greenDarkFrame, mask=mask)
    greenDarkFrame = cv2.cvtColor(greenDarkFrame, cv2.COLOR_HSV2BGR)

    cv2.imshow('frame', frame)
    cv2.imshow('darkFrame', darkFrame)
    cv2.imshow('greenDarkFrame', greenDarkFrame)

    if cv2.waitKey(5) == 113: #q key
        break

plt.figure(1)
plt.imshow(darkFrame)
plt.show()
  
cv2.destroyAllWindows()
cap.release() 

