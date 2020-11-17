//Gait Analysis System - Team 05
//Left Ankle Bracelet Subsystem Source Code
//Published 11-15-2020
//Goal: Ensure that left ankle inner PIR sensor can detect step motion and calculate step count and step speed
//      Ensure that outer PIR sensor stops inner PIR from taking any measurements

int calibrationTime = 30;
int ledPin = 13;                // LED 
int pirPinI = 2;                 // PIR Out pin - inner
int pirPinO = 8;                 //PIR Out pin - outer
int pirStatI = LOW;                   // PIR status: inner
int pirStatO = LOW;              //PIR status: outer
int stepcount = 0;
int loopcounter = 0;
float timestamp = 0.00;
float timer1;
bool endtime1 = false;
int count = 0;
int flag = 0;

void setup() {
 pinMode(ledPin, OUTPUT);   
 pinMode(pirPinI, INPUT);    
 pinMode(pirPinO, INPUT); 
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
 pirStatI = digitalRead(pirPinI); //inner
 pirStatO = digitalRead(pirPinO); //outer

 if (pirStatO == 1) {
  pirStatI == 0; //make sure the inner ankle is not recording anything
  count = 0; //reset counter
  digitalWrite(ledPin, HIGH);  // turn LED ON
  Serial.println("Outer object detected - no data recorded.");
 }
 else if (pirStatI == 1) {
  loopcounter++;
  if (loopcounter == 1) {
    timestamp = millis();
  }
  count = 0; //reset counter
  flag = 1;
  digitalWrite(ledPin, HIGH);  // turn LED ON
  Serial.println("Movement detected by inner PIR sensor!");
 }
 else {
  count++;
  digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
  Serial.println("No motion detected.");
 }
  if ((count > 0) and (flag ==1)){
    endtime1 = true; //motion is 100% finished
    flag = 0; //reset flag: this basically means we are resetting the motion state
  }
  if (endtime1) {
    stepcount++; 
    timer1 = (millis() - timestamp); //get actual timing elapsed
    Serial.println("Time elapsed: ");
    Serial.println(timer1);
    Serial.println("Num. of steps: ");
    Serial.println(stepcount);
    endtime1 = false;
    count = 0;
  }

}
