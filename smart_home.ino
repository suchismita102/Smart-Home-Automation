#define BUZZER_PIN 11 

long duration; 
int distance; 
int x; 
int val; 
int fan = 7; 

void setup() 
{ 
  pinMode(5, OUTPUT);   // Trigger
  pinMode(2, INPUT);    // Echo
  pinMode(4, OUTPUT);   // LED for distance
  pinMode(A3, INPUT);   // LDR
  pinMode(8, OUTPUT);   // Bulb
  pinMode(fan, OUTPUT); 
  pinMode(A0, INPUT);   // Temperature
  pinMode(A5, INPUT);   // Smoke
  pinMode(BUZZER_PIN, OUTPUT); 

  Serial.begin(9600); 
} 

void loop() 
{ 
  // -------- Distance Sensor --------
  digitalWrite(5, LOW); 
  delayMicroseconds(2); 
  digitalWrite(5, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(5, LOW);  

  duration = pulseIn(2, HIGH); 
  distance = duration * 0.034 / 2; 

  if (distance < 20) 
  {
    digitalWrite(4, HIGH); 
    delay(1000); 
    digitalWrite(4, LOW); 
    delay(1000); 
  } 
  else 
  { 
    digitalWrite(4, LOW); 
  } 

  // -------- LDR (Light Sensor) --------
  x = analogRead(A3); 
  Serial.print("Darkness: "); 
  Serial.println(x); 

  if (x > 300)  
  { 
    digitalWrite(8, HIGH); 
    Serial.println("The bulb is on"); 
  }  
  else 
  { 
    digitalWrite(8, LOW); 
    Serial.println("The bulb is off"); 
  } 

  // -------- Temperature Sensor --------
  val = analogRead(A0); 
  float nv = (val / 1024.0) * 500; 
  float cel = nv / 10; 

  if (cel > 30) 
  { 
    digitalWrite(fan, HIGH); 
  } 
  else 
  { 
    digitalWrite(fan, LOW); 
  } 

  // -------- Smoke Detector --------
  int sensorValue = analogRead(A5); 

  if (sensorValue > 500) 
  { 
    analogWrite(BUZZER_PIN, 150); 
  } 
  else 
  { 
    analogWrite(BUZZER_PIN, 0); 
  }     

  // -------- Serial Output --------
  Serial.print("Temperature: "); 
  Serial.print(cel);  
  Serial.println(" C"); 

  Serial.print("Distance: "); 
  Serial.print(distance); 
  Serial.println(" cm"); 

  Serial.print("Smoke Level: "); 
  Serial.println(sensorValue); 

  Serial.println("----------------------");

  delay(1000); 
}