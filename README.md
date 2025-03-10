# Sema Cerebrum
This software has been built using C++17 and VC++ Compiler entirely on Windows.
It was made to run on Windows.

## Requirements
The only thing you need to worry about is that you need to run the program on Windows 10 or 11

## Libraries
- SDL2
- ONNX Runtime
- nlohmann/json
- ImGui
- ImPlot

## How to build
Use Visual Studio ( L'arnaque de Microsoft ) 

Because the project has been compiled with VC++ and were using the project structure of Visual Studio. 
For the ease of using libraries and project configurations.

1. Open the .sln file once the project has been cloned
2. Made the changes you need

Using Visual studio solutions, we don't have to worry about losing the project settings and properties so the properties should be the same.

## How to run
When running for the first time, you should see a Windows Popup asking something. Refusing will make the software not be capable of receiving any data from any client. 
This popup is related to Windows Socket. Click the accept button.
### From Visual Studio
Check what configuration did you choose and simply build and run the project through Visual Studio
### From a Release
Run the executable in the Release folder  
![what-you-should-see](https://github.com/user-attachments/assets/14532d3c-13d3-4f1b-95f3-4bfaadb5d179)

## Logging View
The logging view is responsible of displaying all the received data. Serve as an historic of data that you can consult to check weird values
- The number in purple is the delta time value ( Used to track when the data has been received ) 
- All the values from 1 to 8 correspond to the received values from each of the channels. We have 8 electrodes plugged so we have 8 values coming from the client.
- The range that goes from 100 to 2000 is the number of data visible through the logging history. Putting 100 will display the last 100 values that have been received.
- Putting it to a higher number will result to framedrop so be careful.

![logging-view](https://github.com/user-attachments/assets/b444bcda-2df3-4c44-8495-8e3f7d7e9e84)

## Training View
The training view is what we should look at when we start the training phase
The goal by making this was to automate the training phase by doing some timing events that, once triggered, make an actioner flash to indicate which actioner to look at.
Sadly we didnt have enough time to do it but each actioners in the training view is still able to flash to indicate which one you need to look at during the training phase.

![training-view-geeked](https://github.com/user-attachments/assets/a14d9662-30f1-4482-8726-26932e0b7f14)
![training-view](https://github.com/user-attachments/assets/79199119-db74-4d61-89f1-2a7851c5f6b6)

## Plotting View
The plotting view is used to visualize the coming data. The graph use delta time to move and use a custom structure that we made to dynamically remove the oldest data from it ( around 10% ).
- It has a maximum capacity of 3000 values.
- Theres 8 colored squares. Each of them correspond to an electrode/channel. It is possible to click on one of them to hide its line.
- The graph can be zoomed in and be explored when paused. 
- It is possible to pause the graph by pressing the Space Bar or by clicking on the Pause checkbox on top of it.
![plotting](https://github.com/user-attachments/assets/f6ded891-bf2f-43c0-af53-d786a13078e2)


## Profile View
The profile loader view contain all the profiles that came from our REST API. 
- It's possible to load ONNX file by clicking on the Load button using the Onnx Runtime.
- When the Start button is pressed, the training should be started. 
Training phase was supposed to be automated. We plan to make it happen it soon.

![profile-view](https://github.com/user-attachments/assets/a2ef2409-adfc-40c8-982e-bb5bd2e7b884)

## Doc
All namespaces, classes, structures and functions has been documented [here](https://semacerebrum-doc.static.domains/)
### ps - Can be found in the docs folder too


## What we need to finish
- Profile Loader
- Automate the training phase
- ICA ( Independent Component analysis ) model 

## Videos
[SEMA-CEREBRUM – YOUTUBE](https://youtu.be/Nd4Kb7TSLpA)










 
