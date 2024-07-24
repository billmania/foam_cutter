// Constants
const float X_LEFT_DRUM = -100.0;      // X coordinate of the left drum
const float Y_LEFT_DRUM = 250.0;       // Y coordinate of the left drum
const float X_RIGHT_DRUM = 400.0;      // X coordinate of the right drum
const float Y_RIGHT_DRUM = 250.0;      // Y coordinate of the right drum
const float DRUM_DIAMETER = 111.408;   // Diameter of the drums
const int STEPS_PER_REV = 1600;        // Number of steps per revolution for the stepper motors
const int GEAR_REDUCTION = 25;         // Gear reduction ratio
const float CIRCUMFERENCE = PI * DRUM_DIAMETER; // Circumference of the drums

// Target position
const float TARGET_X = 200.0;          // Target X coordinate
const float TARGET_Y = -75.0;          // Target Y coordinate

// Initial positions
float initialX = 0; // Initial X position
float initialY = 0; // Initial Y position

void setup() {
  Serial.begin(115200);                // Initialize serial communication for debugging
  Serial.println("Starting");

  // Variables to hold the results
  int stepsLeft = 0;
  int stepsRight = 0;

  // Compute the steps required to reach the target position
  computeJointTransformation(TARGET_X, TARGET_Y, stepsLeft, stepsRight);

  // Print the results for debugging
  Serial.print("Steps Left: ");
  Serial.println(stepsLeft);
  Serial.print("Steps Right: ");
  Serial.println(stepsRight);
}

void loop() {
  // Hold position indefinitely
  while (1);
}

/**
 * Computes the steps required for the left and right drums to reach the target coordinates.
 * 
 * @param targetX The target X coordinate.
 * @param targetY The target Y coordinate.
 * @param stepsLeft Reference to store the computed steps for the left drum.
 * @param stepsRight Reference to store the computed steps for the right drum.
 */
void computeJointTransformation(float targetX, float targetY, int &stepsLeft, int &stepsRight) {
  // Left drum calculations
  float leftDistanceToTarget = sqrt(pow(X_LEFT_DRUM - targetX, 2) + pow(Y_LEFT_DRUM - targetY, 2));
  float leftTangentToTarget = sqrt(pow(leftDistanceToTarget, 2) - pow(DRUM_DIAMETER / 2, 2));
  float theta1Left = -atan((X_LEFT_DRUM - targetX) / (Y_LEFT_DRUM - targetY));
  float theta2Left = atan((DRUM_DIAMETER / 2) / leftTangentToTarget);
  float thetaLeft = theta1Left + theta2Left;
  float leftArcLength = thetaLeft * (DRUM_DIAMETER / 2);
  float leftTargetLength = leftTangentToTarget + leftArcLength;
  float deltaLeft = leftTargetLength - 296.237; // Initial length from the PDF
  float leftTurns = deltaLeft / CIRCUMFERENCE;
  stepsLeft = round(leftTurns * STEPS_PER_REV * GEAR_REDUCTION);

  // Right drum calculations
  float rightDistanceToTarget = sqrt(pow(X_RIGHT_DRUM - targetX, 2) + pow(Y_RIGHT_DRUM - targetY, 2));
  float rightTangentToTarget = sqrt(pow(rightDistanceToTarget, 2) - pow(DRUM_DIAMETER / 2, 2));
  float theta1Right = atan((X_RIGHT_DRUM - targetX) / (Y_RIGHT_DRUM - targetY));
  float theta2Right = atan((DRUM_DIAMETER / 2) / rightTangentToTarget);
  float thetaRight = theta1Right + theta2Right;
  float rightArcLength = thetaRight * (DRUM_DIAMETER / 2);
  float rightTargetLength = rightTangentToTarget + rightArcLength;
  float deltaRight = rightTargetLength - 531.375; // Initial length from the PDF
  float rightTurns = deltaRight / CIRCUMFERENCE;
  stepsRight = round(rightTurns * STEPS_PER_REV * GEAR_REDUCTION);
}
