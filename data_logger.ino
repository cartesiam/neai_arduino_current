
#define SAMPLES 128

int sensorPin = A0;    // select the input pin for the potentiometer
float sensor_buffer[SAMPLES] = {0};

void setup() 
{
  Serial.begin(9600);
  while (!Serial);
}
void loop() 
{
  get_current_data();
  delay(300);
}
void get_current_data() {
  for (uint16_t i = 0; i < SAMPLES; i++) {
    sensor_buffer[i] = analogRead(sensorPin);
  }
  for (uint16_t i = 0; i < SAMPLES; i++) {
    Serial.print(sensor_buffer[i]);
    Serial.print(' ');
  }
  Serial.println();
}