#define dirPinL 2
#define stepPinL 3
#define dirPinR 4
#define stepPinR 5

#define PIN_STATE_DELAY 100

#define motorStepsPerRevolution 1600
#define gearReductionRatio 25
#define drumRevolutions 0.5

void setup() {
  pinMode(dirPinL, OUTPUT);
  pinMode(stepPinL, OUTPUT);
  pinMode(dirPinR, OUTPUT);
  pinMode(stepPinR, OUTPUT);
  
  digitalWrite(dirPinL, HIGH);
  digitalWrite(dirPinR, HIGH);

  Serial.begin(115200);
  Serial.println('Starting');
}

void loop() {
  int stepsToMove = drumRevolutions * (gearReductionRatio * motorStepsPerRevolution);

  for (int i = 0; i < stepsToMove; i++) {
    digitalWrite(stepPinL, HIGH);
    delayMicroseconds(PIN_STATE_DELAY);
    digitalWrite(stepPinL, LOW);
    delayMicroseconds(PIN_STATE_DELAY);

    digitalWrite(stepPinR, HIGH);
    delayMicroseconds(PIN_STATE_DELAY);
    digitalWrite(stepPinR, LOW);
    delayMicroseconds(PIN_STATE_DELAY);
  }

  while(1);
}
