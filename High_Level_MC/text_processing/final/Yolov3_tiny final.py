#!/usr/bin/env python
# coding: utf-8

# In[1]:


import cv2
import numpy as np
import matplotlib.pyplot as plt


# In[2]:
max_pair = -1

net=cv2.dnn.readNetFromDarknet("yolov3-tiny_custom.cfg","yolov3-tiny_custom_40000.weights")


# In[3]:


classes=['Arla sour cream','Arla ecological sour cream','Arla sour milk','Alpro blueberry soyghurt','Alpro vanilla soyghurt',
         'Alpro fresh soymilk','Arla mild vanilla yoghurt','Arla natural mild low fat yoghurt','Arla natural yoghurt',
         'Valio vanilla yoghurt','Yoggi strawberry yoghurt','Yoggi vanilla yoghurt','Bravo-Apple-Juice','Bravo-Orange-Juice',
         'God-Morgon-Apple-Juice','God-Morgon-Orange-Juice','God-Morgon-Orange-Red-Grapefruit-Juice','God-Morgon-Red-Grapefruit-Juice',
         'Tropicana-Apple-Juice','Tropicana-Golden-Grapefruit','Tropicana-Juice-Smooth','Tropicana-Mandarin-Morning',
         'Arla-Ecological-Medium-Fat-Milk','Arla-Lactose-Medium-Fat-Milk','Arla-Medium-Fat-Milk','Arla-Standard-Milk',
         'Garant-Ecological-Medium-Fat-Milk','Garant-Ecological-Standard-Milk','Oatly-Oat-Milk','Oatly-Natural-Oatghurt',
         'Red-Kideny-Beans','White-Beans','Green-Beans','Cake','Muffin','Water','Cocacola','Pepsi']


# In[4]:


net.getUnconnectedOutLayers()


# In[5]:


layer_names = net.getLayerNames()
layer_names=list(layer_names)
outputlayers = [layer_names[i[0] - 1] for i in ([[36], [48]])]
outputlayers
#layer_names


# In[6]:


colors= np.random.uniform(0,255,size=(len(classes),3))


# ## Generate a method to detect videos
# 

# In[7]:


def convert_id_to_name(class_id):
    if class_id==0:
        return 'Arla sour cream'
    elif class_id==1:
        return 'Arla ecological sour cream'
    elif class_id==2:
        return 'Arla sour milk'
    elif class_id==3:
        return 'Alpro blueberry soyghurt'
    elif class_id==4:
        return 'Alpro vanilla soyghurt'
    elif class_id==5:
        return 'Alpro fresh soymilk'
    elif class_id==6:
        return 'Arla mild vanilla yoghurt'
    elif class_id==7:
        return 'Arla natural mild low fat yoghurt'
    elif class_id==8:
        return 'Arla natural yoghurt'
    elif class_id==9:
        return 'Valio vanilla yoghurt'
    elif class_id==10:
        return 'Yoggi strawberry yoghurt'
    elif class_id==11:
        return 'Yoggi vanilla yoghurt'
    elif class_id==12:
        return 'Bravo-Apple-Juice'
    elif class_id==13:
        return 'Bravo-Orange-Juice'
    elif class_id==14:
        return 'God-Morgon-Apple-Juice'
    elif class_id==15:
        return 'God-Morgon-Orange-Juice'
    elif class_id==16:
        return 'God-Morgon-Orange-Red-Grapefruit-Juice'
    elif class_id==17:
        return 'God-Morgon-Red-Grapefruit-Juice'
    elif class_id==18:
        return 'Tropicana-Apple-Juice'
    elif class_id==19:
        return 'Tropicana-Golden-Grapefruit'
    elif class_id==20:
        return 'Tropicana-Juice-Smooth'
    elif class_id==21:
        return 'Tropicana-Mandarin-Morning'
    elif class_id==22:
        return 'Arla-Ecological-Medium-Fat-Milk'
    elif class_id==23:
        return 'Arla-Lactose-Medium-Fat-Milk'
    elif class_id==24:
        return 'Arla-Medium-Fat-Milk'
    elif class_id==25:
        return 'Arla-Standard-Milk'
    elif class_id==26:
        return 'Garant-Ecological-Medium-Fat-Milk'
    elif class_id==27:
        return 'Garant-Ecological-Standard-Milk'
    elif class_id==28:
        return 'Oatly-Oat-Milk'
    elif class_id==29:
        return 'Oatly-Natural-Oatghurt'
    elif class_id==30:
        return 'Red-Kideny-Beans'
    elif class_id==31:
        return 'White-Beans'
    elif class_id==32:
        return 'Green-Beans'
    elif class_id==33:
        return 'Cake'
    elif class_id==34:
        return 'Muffin'
    elif class_id==35:
        return 'Water'
    elif class_id==36:
        return 'Cocacola'
    elif class_id==37:
        return 'Pepsi'

import time
def detect_videos():
    #For videos
    #cap=cv2.VideoCapture('pepsi.webm')
    #For Webcam
    cap = cv2.VideoCapture(0)
    font = cv2.FONT_HERSHEY_PLAIN
    starting_time= time.time()
    frame_id = 0
    
    while True:
        ret,frame= cap.read()
        frame_id+=1
        height,width,channels = frame.shape
        #Detecting objects
        blob = cv2.dnn.blobFromImage(frame,0.00392,(320,320),(0,0,0),True,crop=False) #reduce 416 to 320 
        net.setInput(blob)
        outs = net.forward(outputlayers)
        #print(outs[1])
        
        #Showing info on screen/ get confidence score of algorithm in detecting an object in blob
        class_ids=[]
        confidences=[]
        boxes=[]
        for out in outs:
            for detection in out:
                scores = detection[5:]
                class_id = np.argmax(scores)
                confidence = scores[class_id]
                
                if confidence > 0.7:
                    #onject detected
                    center_x= int(detection[0]*width)
                    center_y= int(detection[1]*height)
                    w = int(detection[2]*width)
                    h = int(detection[3]*height)
                    
                    #cv2.circle(img,(center_x,center_y),10,(0,255,0),2)
                    #rectangle co-ordinaters
                    x=int(center_x - w/2)
                    y=int(center_y - h/2)
                    #cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)

                    boxes.append([x,y,w,h]) #put all rectangle areas
                    confidences.append(float(confidence)) #how confidence was that object detected and show that percentage
                    class_ids.append(class_id) #name of the object tha was detected
            
        indexes = cv2.dnn.NMSBoxes(boxes,confidences,0.4,0.6)
        
        for i in range(len(boxes)):
            if i in indexes:
                x,y,w,h = boxes[i]
                label = str(classes[class_ids[i]])
                confidence= confidences[i]
                #color = colors[class_ids[i]]
                color = (0,0,255)
                cv2.rectangle(frame,(x,y),(x+w,y+h),color,2)
                cv2.putText(frame,label+" "+str(round(confidence,2)),(x,y+30),font,1,(255,255,255),2)
            
        elapsed_time = time.time() - starting_time
        fps=frame_id/elapsed_time
        cv2.putText(frame,"FPS:"+str(round(fps,2)),(10,50),font,2,(0,0,255),1)
    
        cv2.imshow("Image",frame)
        key = cv2.waitKey(1) #wait 1ms the loop will start again and we will process the next frame
    
        def save_to_text(textfile_path):
            result = max_pair
            # Open a file in write mode
            file = open(textfile_path, "w")
            # Convert each item to a string and write it to the file
            #for item in pair:
            item=convert_id_to_name(result[0])
            confidence_score=result[1]
            file.write(str(item) + "\t" + str(price(result[0])))
            # Close the file    
            file.close()
            
        # In[23]:
        save_to_text('Detection.txt')


        if key == 27: #esc key stops the process
            break;        
    cap.release()    
    cv2.destroyAllWindows() 
    return class_ids,confidences


# In[10]:


detect_videos()


# In[11]:





# In[18]:


def price(class_id):
    if class_id==36:
        return '4$'
    elif class_id==37:
        return '5$'


# ### Extract the return of the detect_videos function and store them in list1(class id) & list2(confidence score)

# In[19]:


list1,list2=detect_videos()


# ### Print each class id corresponding to its confidence score in a list

# In[20]:


pairs = []

for value1, value2 in zip(list1, list2):
    result =[value1,value2]
    pairs.append(result)

print("Class ID corresponding to its confidence score:\n", pairs)


# ### Print the object having the maximum confidence score

# In[21]:


max_value = float('-inf')  # Initialize max_value with negative infinity
max_pair = None

for pair in pairs:
    second_number = pair[1]
    if second_number > max_value:
        max_value = second_number
        max_pair = pair
print("Pair with the maximum confidence score:", max_pair)


# ### Save the class name and its confidence score to a textfile

# In[22]:



