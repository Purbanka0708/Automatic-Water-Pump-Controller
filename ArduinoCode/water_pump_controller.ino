const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int RELAY_PIN = 8;

const int LOW_LEVEL_CM = 15;
const int HIGH_LEVEL_CM = 5;

bool pumpOn = false;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  long duration;
  float distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  distance = duration * 0.034 / 2;
  if (distance <= 0 || distance > 200 || duration == 0)
  {
    Serial.println("Invalid distance reading. Skipping...");
    delay(1000);
    return;
  }

  Serial.print("Distance to water: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > LOW_LEVEL_CM && !pumpOn)
  {
    digitalWrite(RELAY_PIN, LOW);
    pumpOn = true;
    Serial.println("Water LOW → Pump turned ON");
  }
  else if (distance < HIGH_LEVEL_CM && pumpOn)
{
    digitalWrite(RELAY_PIN, HIGH);
    pumpOn = false;
    Serial.println("Tank FULL → Pump turned OFF");
  }

  Serial.print("Pump Status: ");
  Serial.println(pumpOn ? "ON" : "OFF");

  delay(1000);
}
