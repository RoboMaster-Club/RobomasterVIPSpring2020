import cv2
import numpy as np
from matplotlib import pyplot as plt

cap = cv2.VideoCapture(0)

while True:
    _, frame = cap.read()
    
    frame = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    darkFrame = frame.copy()
    darkFrame[:,:,2] = darkFrame[:,:,2]*0.3

    frame = cv2.cvtColor(frame,cv2.COLOR_HSV2BGR)
    darkFrame = cv2.cvtColor(darkFrame,cv2.COLOR_HSV2BGR)
    
    cv2.imshow('frame', frame)
    cv2.imshow('darkFrame', darkFrame)

    if cv2.waitKey(5) == 113: #q key
        break

plt.figure(1)
plt.imshow(darkFrame)
plt.show()
  
cv2.destroyAllWindows()
cap.release() 