import cv2
import numpy as np


def version():
    print("OpenCV : version ", cv2.__version__)


def showImage():
    img = cv2.imread("lena.png")
    cv2.imshow("Lena", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def readCamera():
    cap = cv2.VideoCapture(0)
    while (True):
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Display the resulting frame
        cv2.imshow('camera', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()


def main():
    version()
    showImage()
    readCamera()


if __name__ == '__main__':
    main()
