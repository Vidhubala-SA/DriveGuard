
const int eyeBlinkSensor = 2;
const int motorPin = 3;
const int buzzerPin = 4;

long blinkStartTime = 0;
const int threshold = 2000; // 2 seconds

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(eyeBlinkSensor, INPUT);

  digitalWrite(motorPin, HIGH);   // Motor ON
  digitalWrite(buzzerPin, LOW);   // Buzzer OFF
}

void loop() {
  int eyeState = digitalRead(eyeBlinkSensor);

  Serial.print("Eye Sensor: ");
  Serial.println(eyeState);

  if (eyeState == LOW) {   // Eye closed
    if (blinkStartTime == 0) {
      blinkStartTime = millis();   // start timer
    }

    // Check if eye closed for long time
    if (millis() - blinkStartTime > threshold) {
      digitalWrite(buzzerPin, HIGH);  // Alarm ON
      digitalWrite(motorPin, LOW);    // Motor OFF
      Serial.println("DROWSY! ALERT!");
    }

  } else {   // Eye open
    blinkStartTime = 0;  // reset timer
    digitalWrite(buzzerPin, LOW);   // Alarm OFF
    digitalWrite(motorPin, HIGH);   // Motor ON
    Serial.println("Driver Active");
  }

  delay(100); // small stability delay
}