import numpy as np 
import cv2

img=cv2.imread("./Indoor_normal_illumination.jpg",0)
cv2.imshow("img normal",img)
cv2.waitKey(0)
cv2.destroyAllWindows()