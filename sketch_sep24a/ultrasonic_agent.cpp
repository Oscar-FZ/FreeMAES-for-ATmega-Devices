// #include "ultrasonic_agent.h"

// Agent Ultrasonic_Control("Ultrasonic Control Agent", 1, 120);

// float   ultrasonic_distance     = -1;
// bool    ultrasonic_IsObstacle   = 1;
// bool    ultrasonic_IsClear      = false;

// class ultrasonicBehaviour : public CyclicBehaviour {
// public:
//   void setup() override {

//   }

//   void action() override {
//     delay(4); 

//     pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
//     digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
//     delayMicroseconds(2);
//     digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
//     pinMode(ULTRASONIC_ECHO_PIN, INPUT);

//     float duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_READ_TIMEOUT);
  
//     float distance = duration  * 0.017; 
    
//     if (distance > MAX_DISTANCE || distance == 0) {
//       ultrasonic_distance = -1;
//     } 
//     ultrasonic_distance = distance;

//     bool ultrasonic_IsObstacle = distance < ULTRASONIC_AVOIDANCE_THRESHOLD;

//     if (distance > ULTRASONIC_AVOIDANCE_THRESHOLD || distance < 0) {
//       ultrasonic_IsClear = true;
//     } 
//     else {
//       ultrasonic_IsClear = false;
//     }

//   }
// };

// void ultrasonic(void* pvParameters) {
//   ultrasonicBehaviour b;
//   b.execute();
// }
