/*  
 *   
 *   Gait Analysis System - Team 05
 *   Right Ankle Bracelet Subsystem (For testing)
 *   Published: 11-15-2020
 *   Goal: Ensure that if the "inner" PIR detects motion, we output 1 distance measurement between the feet
 *   
 */
  
// port numbers
const int trig = 10;
const int echo = 9;
const int PIRout = 6;
int ledPin = 13;

// variables
float duration;
int calibrationTime = 30;
float distance = 0.00;
int PIRstat = LOW;
int loopcounter = 0;
int count = 0;
int num_dist_measurements = 0;
int flag = 0;

// setup
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(PIRout, INPUT);

  // set things low
  digitalWrite(trig, LOW);
  digitalWrite(PIRout, LOW);
  delay(1);
  Serial.begin(9600);
 Serial.print("Calibrating ");
  for (int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("Sensor Active");
  delay(50);

}

void loop() {
  // read the PIR
  PIRstat = digitalRead(PIRout);
  
  if( PIRstat == 1 ) {
    count = 0;
    flag = 1; //flag that indicates a motion state has been entered
    Serial.println("Motion Detected!");
    loopcounter++;
    if (loopcounter == 1) {
    num_dist_measurements++;
    
    // read echo and calculate distance
      digitalWrite(trig, LOW); 
      delayMicroseconds(2); 
      digitalWrite(trig, HIGH); 
      delayMicroseconds(4000); 
      digitalWrite(trig, LOW); 
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    Serial.println("Distance: " + String(distance) + " cm");
    }
  }
  
  else {
    count++;
    Serial.println("No motion detected!");
  }

  if (count > 3 and flag == 1) {
    flag = 0; //clear motion state
    loopcounter = 0; //reset motion state; gets it ready to take a new distance once new motion occurs
    Serial.println("Total num. of distance measurements taken: ");
    Serial.println(num_dist_measurements);
  }
}
