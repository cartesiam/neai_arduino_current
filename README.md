# Smart current monitor
This project contains the source code to create your own smart current sensor using Cartesiam's NanoEdge AI Library.

## What is NanoEdge AI Library ?
NanoEdge AI Library is an artificial intelligence static library developed by Cartesiam, for embedded C software running on ARM Cortex microcontroller. This static library is generated from NanoEdge AI Studio. 
NanoEdge AI Studio's purpose is to select the best NanoEdge AI Library possible for your final hardware application, i.e. the piece of code that contains the most relevant machine learning model to your application, tuned with the optimal parameters.

See [NanoEdge AI Studio Documentation](https://cartesiam-neai-docs.readthedocs-hosted.com/) for more information about NanoEdge AI Studio and NanoEdge AI Library.

## Hardware requirements
We will need the following hardware (or equivalent):
  * 1 Arduino Nano IoT 33
  * 1 Current clamp such as CR3111-3000 from CR Magnetics Inc.
  * 2 10 k ohm resistors
  * 1 150 ohm resistor
  * 1 10 uF capacitor
  * A breadboard is recommended
  * Some electrical wires
  
## Software requirements
We will require the following softwares:
  * The Arduino IDE: https://www.arduino.cc/en/main/software
  * NanoEdge AI Studio: https://cartesiam.ai/download/
  
## Hardware setup
![Image of circuit setup](https://cartesiam-neai-docs.readthedocs-hosted.com/_images/pince_amp_bb2.png)

## Making a Data Logger
Our first step will be to make a data logger. This will be used to collect the data to find and test the best Machine Learning model in NEAI (NanoEdge AI) Studio.
If you are using the setup presented above and the Arduino Nano IoT 33 flash the code attached in datalogger.
Else use the code as a starting point and modify it based on your needs.
The data logger will be used to send data from the board to the computer running NEAI Studio. 
Once we have our data logger up and running we can check it using Arduino's serial monitor to chek that the data is coming in properly.


## Finding the best Machine Learning library using NanoEdge AI Studio
Downloading and install NEAI Studio (the email containing the license key can end up in gmail Promotion or Spam filters).
Let's now run NEAI Studio (enter your license key) and we will create a new project. 
### Step 1: Global Settings
Input project Name: "Smart_Hall_sensor"
A description: "Using a hall sensor and a stripped extension cord we create a ML library to monitor our vacuum cleaner."
A target: In the case of this demo we select the M0+, if you are using another board selet the proper Cortex M target. If you are using one of Cartesiam ST demo boards (Nucleo-F401RE Cortex M4, Nucleo-L432KC Cortex-M4, or STM32L562QE-DK Cortex-M33) select those.
Max RAM: In this case we will try with 12Kb but if you have a board with a smaller RAM select something that will take about 1/2 of it at most. 
We will select the sensor type as Hall sensor 1 axis.
And click create to move on to the next step.

### Step 2: Regular Signals
We will collect data when the vacuum is working 'normally' so make sure that the bag/reservoir is empty, the sensor is plugged and that your vacuum is running.
In NEAI Studio click 'Choose signals', 
then the tab 'From serial (USB)', 
the serial port on which your board is connected,
the baudrate should be set at 9600 
We can check the gray box next to 'Max lines' and leave the value at 200. 
Making sure the vacuum is running we can then click on the red circle to start collecting data. Feel free to run the vacuum normally while this is happening.
Click validate import and you are done collecting your data.

### Step 3: Abnormal Signals
In step 3 we repeat the procedure of step2 but do it with a full vacuum bag/reservoir or simulating a full bag reservoir by placing paper in front of the filter.
Repeat step 2.

### Step 4: Optimize and Benchmark
Step 4 is where the software work and we watch. 
Now that we have our data we will let NEAI Studio find the best Machine Learning library for our use case. 
Let's click 'Start', Select the number of cores to use (the more, the better but the slower your computer will get if you are runnign other tasks) and then validate.
The studio starts looking for the best library. During this process you can see the progress made with hte 3 indicators that are being optimized: Balanced accuracy, Confidence and RAM. I recommand letting it run until Balanced Accuracy and Confidence are below 90%. Once the process is over (or once you click stop) you will see on the right a number of iterations. In my case it is 85. Take note of that value it will be useful later.


## Testing our Machine Learning library
We will now test the library found in step 4
### Step 5: Emulator
We will emulate our MCU and feed the library we selected in step 4 data. This will let us test the algorithm in real world conditions easily. 
Click on 'Initialize Emulator', then the 'serial data' tab.
We repeat the procedure from step 2 and 3 for the setup: selectt the port, baudrate at 9600 and the max number of lines will the number we got at the end of step 4 (in my case 85). 
This is when we will 'learn' what the current looks like when the vacuum runs wihtout a full bag/reservoir. Ensure your vacuum is empty, running and click on the record button. 

Once this is over the library has been trained and now knows how it behaves with an empty bag. 
The next step is Detection. We will here again set the values for Port and baudrate but will not check the Max Lines option. 
We can start our vacuum and we'll see the output of the detection by the now trained library. If the bag is full the value will go down indicating that the bag is full and needs to be changed. 

## Building our smart sensor [Pro]
In case you do not have a NanoEdge AI Studio pro license you can also find tutorials that let you create a smart sensor at https://cartesiam-neai-docs.readthedocs-hosted.com/tutorials/tutorials.html using the ST dev boards indicated.

To include your NEAI Studio library on your Arduino board follow on. 

