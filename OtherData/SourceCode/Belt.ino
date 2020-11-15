//Gait Analysis System - Team 5
//Belt Subsystem Sourcecode

int calibrationTime = 30;
int ledPin = 13;                // LED 
int pirPin1 = 2;                 // PIR Out pin - LEFT ARM
int pirPin2 = 8;                 //PIR Out pin - RIGHT ARM
int pirStat1 = LOW;                   // PIR status: LEFT ARM
int pirStat2 = LOW;              //PIR status: RIGHT ARM
int count = 0; //counter: to be used for delay time
float timestamp1 = 0.00;
float timestamp2 = 0.00;
//float timestamp = 0.00;
float timer1 = 0.00;
float timer2 = 0.00;
boolean endtime1 = false; //determines whether or not it's time to output time
boolean endtime2 = false;
int flag1 = 0;
int flag2 = 0;
int rightcount = 0;
int leftcount = 0;
int loopcounter1 = 0;
int loopcounter2 = 0;

void setup() {
 pinMode(ledPin, OUTPUT);   
 pinMode(pirPin1, INPUT);    
 pinMode(pirPin2, INPUT); 
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

void loop(){
 pirStat1 = digitalRead(pirPin1); //left
 pirStat2 = digitalRead(pirPin2); //right

 if (pirStat1 == 1) {            // if motion detected
  loopcounter1++;
  if (loopcounter1 == 1) {
    timestamp1 = millis(); //start timing
  }
  flag1 = 1; //raise a FLAG indicating that there has been motion
  count = 0; //reset counter (thise is useful for the delay time!)
   digitalWrite(ledPin, HIGH);  // turn LED ON
   Serial.println("Left arm - motion detected!");
 } 
 else if (pirStat2 == 1){
  loopcounter2++;
   if (loopcounter2 == 1) {
    timestamp2 = millis(); //start timing
  }
  flag2 = 1; //raise a FLAG indicating that there has been motion
  count = 0; //reset counter
  //timestamp2 = millis(); //start timing
   digitalWrite(ledPin, HIGH); 
  
   Serial.println("Right arm - motion detected!");
 }
 else {
  count++; //this COUNTER keeps track of how often motion is "off" - we need this for the delay time because our motion will sometimes be interrupted by "no motion" due to the PIR's delay
  digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
   Serial.println("No motion detected.");
 }
 if ((count > 3) and (flag1 ==1)){
    endtime1 = true; //motion is 100% finished
    flag1 = 0; //reset flag: this basically means we are resetting the motion state
  }
 if ((count > 4) and (flag2==1)){
  endtime2 = true;
  flag2 = 0;
 }
  if (endtime1) {
    leftcount++;
    timer1 = (millis() - timestamp1); //get actual timing for 1 movement
    Serial.println("Left arm: ");
    Serial.println(timer1);
    Serial.println("Num. of left arm swings: ");
    Serial.println(leftcount);
    endtime1 = false;
    count = 0;
  }
  if (endtime2) {
    rightcount++;
    timer2 = (millis() - timestamp2); //get actual timing for 1 movement
    Serial.println("Right arm: ");
    Serial.println(timer2);
    Serial.println("Num. of right arm swings: ");
    Serial.println(rightcount);
    endtime2 = false;
    count = 0;
  }
} 
