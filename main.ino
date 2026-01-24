#define PIEZO_PIN 9  
#define TRIGGER 6
#define ECHO 7

int16_t distance; //In mm

int16_t thresholds[] = {51, 508, 762, 1016, 1270, 1524}; //In mm

// Inclusive of both bounds
bool inRange(int16_t var, int16_t min, int16_t max) {
  if (var >= min && var <= max) {
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PIEZO_PIN, OUTPUT);
}

void loop() {
  //Creating ultrasonic pulse
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  // Max: 24000*343/1000/2 = 4116mm = 411.6cm = 162in (HC-SR04 has reliable range of 400cm)
  distance = pulseIn(ECHO, HIGH, 24000) * 343/1000/2;

  // Determine the tone based on distance thresholds
  if (inRange(distance, thresholds[0], thresholds[1])) {
    tone(PIEZO_PIN, 1725);
    delay(50);
  } else if (inRange(distance, thresholds[1], thresholds[2])) {
    tone(PIEZO_PIN, 1675);
    delay(125);
  } else if (inRange(distance, thresholds[2], thresholds[3])) {
    tone(PIEZO_PIN, 1550);
    delay(150);
  } else if (inRange(distance, thresholds[3], thresholds[4])) {
    tone(PIEZO_PIN, 1475);
    delay(175);
  } else if (inRange(distance, thresholds[4], thresholds[5])) {
    tone(PIEZO_PIN, 1400);
    delay(225);
  }
  noTone(PIEZO_PIN);

  Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println("mm");
  Serial.print(distance*5/127);
  Serial.println("in");


  delay(50);
}
