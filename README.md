# Ambu-Trackers-Hackfest
This is our project for Hackfest' 24 organized by IIT(ISM) Dhanbad.

Team Name : Ambu Trackers

Team Members:-

1.Jyotika Jayani

2.Tanisha Basu

3.Shreya Ojha

4.Shiven Sisodia
# PROBLEM STATEMENT:-
In the transition of patients from high acuity environments such as operating
rooms (OR) or intensive care units (ICU) to lower acuity wards, significant
physiological changes may occur due to the altered environmental conditions.
Among these patients, individuals experiencing frequent seizure attacks and several critical health issues present in a particularly critical scenario,
often necessitating immediate medical attention. However, the timely arrival of ambulance services may pose
challenges, potentially exacerbating the patient's condition.
To address this challenge, our solution entails the utilization of 
monitoring devices capable of real-time data collection and analysis. By
leveraging advanced hardware and software components, we establish a
comprehensive monitoring system integrated with Internet of Things (IoT) and ML
cloud infrastructure, specifically utilizing the Blynk and ubidots platform.
This system enables continuous monitoring of the patient's physiological
parameters, including vital signs and seizure activity, during the transition
period from high to low acuity environments and beyond. By aggregating
and analyzing this real-time data, healthcare providers can remotely
assess the patient's condition and make informed decisions regarding the
necessity of hospital admission or discharge.
# OUR APPROACH :-
1.We will use sensors like MAX 30102 pulse oximeter and AD8232 ECG sensor to collect  the data from the patient's body to monitor the physiological changes.
2.We will then send this data through ESP32 Microcontroller to process  and transmit the data.
3.We will then send this processsed data through Blink IOT and Ubidots platform to  the hospital dashboard that will update with patient’s condition.
4.We will use  Techniques of Machine Learning algorithm to collect data via ECG electrodes through patient’s body and monitor the changes(using the coolterm software and converting the data into csv file for applying ML Model) .


The MAX30102 pulse oximeter and heart rate sensor is an I2C-based low-power plug-and-play biometric sensor. It can be used by students, hobbyists, engineers, manufacturers, and game & mobile developers who want to incorporate live heart-rate data into their projects.

ECG can be analyzed by studying components of the waveform. These waveform components indicate cardiac electrical activity. The first upward of the ECG tracing is the P wave. It indicates atrial contraction.The QRS complex begins with Q, a small downward deflection, followed by a larger upwards deflection, a peak (R); and then a downwards S wave. This QRS complex indicates ventricular depolarization and contraction. Finally, the T wave, which is normally a smaller upwards waveform, representing ventricular re-polarization.

![EKG-oneBeat](https://github.com/JyotikaJayani-08/Ambu-Trackers-Hackfest/assets/158709375/816e12fe-87a0-452d-8d45-0b804d940e9c)


Medical uses of ECG
An electrocardiogram can be a useful way to find out whether your high blood pressure has caused any damage to your heart or blood vessels. Because of this, you may be asked to have an ECG when you are first diagnosed with high blood pressure.

Some of the things an ECG reading can detect are:
1. cholesterol clogging up your heart’s blood supply
2. a heart attack in the past
3. enlargement of one side of the heart
4. abnormal heart rhythms

The implementation of this solution offers several key benifits
including:-
Timely intervention: Immediate detection of changing severe health condition of patients allows for prompt medical response, 
even in the absence of onsite healthcare professionals.
Cost savings: By avoiding unnecessary hospital admissions
for patients whose condition is stable, significant cost savings
can be achieved within the healthcare system.
Enhanced patient outcomes: Continuous monitoring
facilitates early detection of signs of recovery, enabling
timely discharge and improving overall patient outcomes.
In summary, our solution combines cutting-edge hardware,
software, and cloud-based infrastructure to address the critical need
for continuous monitoring of patients transitioning between high
and low acuity environments. By leveraging wearable technology
and IoT connectivity, we empower healthcare providers to deliver
timely and effective care, ultimately improving patient outcomes
and reducing healthcare costs.

# TECH STACK USED-
IOT, esp32,BLYNK SOFTWARE and Ubidots, AI/ML,CoolTerm Software(To Convert ECG dataset into csv file), WEB DEVELOPMENT 
# BASIC OVERFLOW :- 
1. Assemble and test each sensor with the ESP32 individually.
2. Integrate all sensors with the ESP32, ensuring stable
simultaneous operation.
3. Implement signal processing algorithms to extract clean data
from the sensors.
4.We will use  Techniques of Machine Learning algorithm to collect data via ECG electrodes through patient’s body and monitor the changes(using the coolterm software and converting the data into csv file for applying ML Model) .
5. Establish connectivity with the Blink IoT platform and ensure
reliable data transmission.
6. Develop or set up the hospital dashboard to receive and display
patient data.
Test the entire system for accuracy, reliability, and user
experience.

Libraries used in our code:

![WhatsApp Image 2024-05-11 at 09 44 53_2e98924a](https://github.com/JyotikaJayani-08/Ambu-Trackers-Hackfest/assets/158709375/c6519b49-622f-452d-b71e-7d0ee6c9098c)


FLOWCHART:-
![flowchart1](https://github.com/JyotikaJayani-08/Ambu-Trackers-Hackfest/assets/158709375/a285302e-5a47-499d-9100-6872e2eb5ed3)

![Flowchart2](https://github.com/JyotikaJayani-08/Ambu-Trackers-Hackfest/assets/158709375/8be35b2c-c3a5-4ea1-8ebe-9675b1182fc6)















![WhatsApp Image 2024-05-11 at 07 59 52_d6774a7f](https://github.com/JyotikaJayani-08/Ambu-Trackers-Hackfest/assets/158709375/a61305d4-b74f-4476-9eb3-25c95ce8897b)

