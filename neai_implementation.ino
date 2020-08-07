#include <NanoEdgeAI.h>             //Import Cartesiam's NanoEdge AI Library

int sensorPin = A0;                 // Select the input pin for the potentiometer
float sensor_buffer[SAMPLES] = {0}; // Array buffering the samples from the sensor before Learning/Detecting

#define SAMPLES 128                 // Nbr samples collected
#define NUMBER_LEARN 65             // Nbr of learn cycles needed

float sim1 = 100.0;
float sim2 = 100.0;
float avg = 0.0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  //Comment out when using without serial readouts
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Start Learning");
  NanoEdgeAI_initialize();
  for (int i = 0; i < NUMBER_LEARN; i++) {
    get_current_data();
    NanoEdgeAI_learn(sensor_buffer);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(500);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Learning Done!");
}

void loop() {
  get_current_data();
  float similarity = NanoEdgeAI_detect(sensor_buffer);
  avg = (similarity + sim1 + sim2) / 3.0;
  sim2 = sim1;
  sim1 = similarity;
  
  if (avg <= 90.0){
    Serial.println(avg);
    sim1 = 100.0;
    sim2 = 100.0;
    blink_quick();
    delay(10000);
      }
  }
  delay(200);
}

void get_current_data() {
  for (uint16_t i = 0; i < SAMPLES; i++) {
    sensor_buffer[i] = analogRead(sensorPin);
  }
}

void blink_quick(){
  while (1) {
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(100);                  
    digitalWrite(LED_BUILTIN, LOW);
    delay(100)
  }
}
