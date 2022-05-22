import cv2
import numpy as np
import kociemba 

cam=cv2.VideoCapture(0)
values=[(100,100),(100,210),(100,320),(210,100),(210,210),(210,320),(320,100),(320,210),(320,320)]
#red,green,blue,white,yellow,orange
colors=[ 'R','R','G' ,'B' , 'Y', 'O']
finals=''
lower=[ [0,50,100],[170,100,86],[58,27,100],[100,100,100],[24,50,100],[7,50,100] ]
upper=[ [6,255,255],[179,255,255],[83,255,255],[130,255,255],[42,255,255],[22,255,255] ]

while True:
    _, frame = cam.read()
    regionhsv=frame
    regionhsv=cv2.cvtColor(regionhsv, cv2.COLOR_BGR2HSV)
    s=''
    for j in values:
        color='W'
        
        for i in range(6):
            lower_bound = np.array(lower[i])
            upper_bound= np.array(upper[i])
            mask = cv2.inRange(regionhsv, lower_bound, upper_bound)
            region=mask[j[0]+50][j[1]+50]
            if(region>0):
                color=colors[i]
                break
        cv2.rectangle(frame,j,(j[0]+100,j[1]+100),(255,0,0),3)
        s+=color
    cv2.imshow('myCam',frame)

    cv2.moveWindow('myCam',0,0)
    cv2.rectangle(frame,(100,100),(200,200),(255,0,0),3)
    if cv2.waitKey(1)==ord('q'):
        break
    if cv2.waitKey(1)==ord('v'):
        print(s)
        finals+=s 
        if len(finals)==54:
            break
cam.release()
cv2.destroyAllWindows()

f=open('input.txt','w')
f.write(finals)
f.close()
