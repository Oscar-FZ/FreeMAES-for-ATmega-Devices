// #include "infrared_agent.h"

// Agent Ir_Control("Infrared Control Agent", 1, 120);

// byte ir_result = 0b00000000;

// class irBehaviour : public CyclicBehaviour {
// public:
//   void setup() override {
//     pinMode(IR_LEFT_PIN, INPUT);
//     pinMode(IR_RIGHT_PIN, INPUT);
//   }

//   void action() override {
//     byte left = digitalRead(IR_LEFT_PIN);
//     byte right = digitalRead(IR_RIGHT_PIN);
//     ir_result = (left << 1) | right;
//   }
// };

// void ir(void* pvParameters) {
//   irBehaviour b;
//   b.execute();
// }