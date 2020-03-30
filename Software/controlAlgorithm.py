import cv2
import numpy as np

CV_CAP_PROP_BRIGHTNESS = 10
CV_CAP_PROP_CONTRAST = 11
CV_CAP_PROP_SATURATION = 12
CV_CAP_PROP_HUE = 13
CV_CAP_PROP_GAIN = 14
CV_CAP_PROP_EXPOSURE = 15

class Fin:
    def __init__(self):
        self.pos = 0 #assumes a position between 100 (up/left) and -100 (down/right)

    def setPos(self, pos):
        pos = min(pos, -100)
        pos = max(pos, 100)
        self.pos = pos

    def getPos(self):
        return self.pos

class PIDController:
    def __init__(self, target, delta, p, i, d, reversed=False):
        self.target = target
        self.delta = delta #time between each step
        self.deltaCurr = delta #time between each step with input
        self.reversedValue = -1 if reversed else 1 #to reverse output

        self.kp = p #porportional constant
        self.ki = i #integral constant
        self.kd = d #derivitive constant

        self.integralPrev = 0
        self.errorPrev = 0
        self.timePrev = None

    def step(self, input):
        error = self.target - input
        integral = self.integralPrev + error * self.deltaCurr
        derivitive = (error - self.errorPrev) / self.deltaCurr
        
        self.errorPrev = error
        self.integralPrev = integral
        self.deltaCurr = self.delta

        return self.reversedValue * (self.kp*error + self.ki*integral + self.kd*derivitive)

    def stepNoInput(self):
        self.deltaCurr += self.delta

class LightDetector:
    def __init__(self):
        self.cap = cv2.VideoCapture(0) #may be 0 or 1
        self.cap.set(CV_CAP_PROP_BRIGHTNESS, 0)
        self.cap.set(CV_CAP_PROP_CONTRAST, 32)
        self.cap.set(CV_CAP_PROP_SATURATION, 32)
        self.cap.set(CV_CAP_PROP_GAIN, 0)
        self.cap.set(CV_CAP_PROP_EXPOSURE, 0)

        self.lower = np.array([50, 140, 0])
        self.upper = np.array([94, 255, 156])

    def getLightPosition(self):
        _, frame = self.cap.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Thresholding
        mask = cv2.inRange(hsv, self.lower, self.upper)

        # Morphology
        kernel = np.ones((3,3), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

        # Fit Circles
        contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        maxRadius = -1
        xResult = None
        yResult = None
        for contour in contours:
            (x,y), radius = cv2.minEnclosingCircle(contour)
            x = int(x)
            y = int(y)
            radius = int(radius)

            if radius > maxRadius:
                xResult = x
                yResult = y
                maxRadius = radius

        if maxRadius == -1: #no light found
            return (xResult, yResult) #return None, None
        else:
            #return light coordinates centered at 0, 0
            #left is neg, right is pos, up is pos, down is neg
            height, width, channels = frame.shape
            return (-1 * (width//2 - xResult), height//2 - yResult)

if __name__ == "__main__":
    lightDetector = LightDetector()

    leftElevator = Fin()
    rightElevator = Fin()
    rudder = Fin()

    pitchController = PIDController(target=0, delta=0.033, p=0.1, i=0, d=0.01, reversed=True)
    yawController = PIDController(target=0, delta=0.033, p=0.1, i=0, d=0.01)

    while (True):
        x, y = lightDetector.getLightPosition()

        if x == None and y == None:
            pitchController.stepNoInput()
            yawController.stepNoInput()

            #print('Not Found')
        else:
            pitchOutput = pitchController.step(y)
            yawOutput = yawController.step(x)

            leftElevator.setPos(pitchOutput)
            rightElevator.setPos(pitchOutput)
            rudder.setPos(yawOutput)

            #print(round(yawOutput, 2), x, round(pitchOutput, 2), y)

    """
    import smbus

    channel = 1
    address = 0x60
    reg_write_dac = 0x40

    bus = smbus.SMBus(channel)

    msg = [rudder.getPos(), leftElevator.getPos(), rightElevator.getPos()]
    bus.write_i2c_block_data(address, reg_write_dac, msg)
    """
