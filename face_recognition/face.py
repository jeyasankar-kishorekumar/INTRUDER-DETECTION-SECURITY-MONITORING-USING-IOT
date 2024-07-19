import face_recognition
import cv2
import numpy as np
import os
import six.moves.urllib as urllib
import datetime
import pandas as pd

import serial
ser = serial.Serial('COM3',baudrate=9600,timeout=0.3)



cam='http://192.168.233.200/cam-hi.jpg'
    

print("Data Train_1")
kishore_image = face_recognition.load_image_file("kishore.jpeg")
kishore_face_encoding = face_recognition.face_encodings(kishore_image)[0]
print("Data Train_2")
mahadeven_image = face_recognition.load_image_file("mahadeven.jpeg")
mahadeven_face_encoding = face_recognition.face_encodings(mahadeven_image)[0]



print("Data Train Completed")
# Create arrays of known face encodings and their names
known_face_encodings = [
  kishore_face_encoding,
  mahadeven_face_encoding
]
known_face_names = [
  "kishore",
  "mahadeven",
   
]
# Initialize some variables
face_locations = []
face_encodings = []
face_names = []
process_this_frame  = True




while True:
##    serial_func()
    
##        ret, frame = cam.read()
    img_resp = urllib.request.urlopen(cam)
    img_arr = np.array(bytearray(img_resp.read()), dtype=np.uint8)

    # Grab a single frame of video
    frame = cv2.imdecode(img_arr, -1)
    # Resize frame of video to 1/4 size for faster face recognition processing
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
    # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
    rgb_small_frame = small_frame[:, :, ::-1]
    # Only process every other frame of video to save time
    if process_this_frame:
        # Find all the faces and face encodings in the current frame of video
        face_locations = face_recognition.face_locations(rgb_small_frame)
        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
        face_names = []
        for face_encoding in face_encodings:
            # See if the face is a match for the known face(s)
            matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
            name = "Unknown"
            

            # Or instead, use the known face with the smallest distance to the new face
            face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
            best_match_index = np.argmin(face_distances)
            if matches[best_match_index]:
                name = known_face_names[best_match_index]

            face_names.append(name)

    process_this_frame = not process_this_frame


    # Display the results
    for (top, right, bottom, left), name in zip(face_locations, face_names):
        # Scale back up face locations since the frame we detected in was scaled to 1/4 size
        top *= 4
        right *= 4
        bottom *= 4
        left *= 4

        # Draw a box around the face
        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)

        # Draw a label with a name below the face
        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
        
        
        

##        cv2.imwrite("capture.jpg",frame)
        if(name=="Unknown"):
            cv2.imwrite('capture.jpg',frame)
            ser.write('1'.encode())
            print("unknown")

        if(name=="kishore"):
            print("kishore")

            


        if(name=="mahadeven"):
            print("mahadeven")




        
            
           
            

           
            
##            
            
    cv2.imshow('frame',cv2.resize(frame,(800,600)))
    # Hit 'q' on the keyboard to quit!
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release handle to the webcam
video_capture.release()
cv2.destroyAllWindows()

