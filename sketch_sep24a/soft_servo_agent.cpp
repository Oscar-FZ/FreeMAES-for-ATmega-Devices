#include "soft_servo_agent.h"

/* ------------------- Instancia global del agente ------------------- */
Agent Servo_Control("Soft Servo Control Agent", 1, 192);

/* ------------------- Función para mover el servo ------------------- */
void SoftServo_Write(uint8_t angle) {
  // Convierte ángulo a PWM (SoftPWM no usa microsegundos, sino duty 0–255)
  uint16_t pulseWidth = map(angle, 0, 180, 500, 2500);   
  uint16_t value = map(pulseWidth, 0, 16666, 0, 255);    
  SoftPWMSet(SERVO_PIN, value);
}

/* ------------------- Comportamiento del agente ------------------- */
class servoBehaviour : public CyclicBehaviour {
public:
  void setup() override {
    pinMode(SERVO_PIN, OUTPUT);
    SoftPWMSet(SERVO_PIN, 0);
    SoftPWMSetFadeTime(SERVO_PIN, 100, 100);
    //Serial.println(F("Soft Servo Agent inicializado"));
  }

  void action() override {
    servoControlPackage* central_servo_pckg;
    msg.receive(portMAX_DELAY);

    if (msg.get_msg_type() == INFORM) {
      central_servo_pckg = (servoControlPackage*) msg.get_msg_content();

      switch (central_servo_pckg->instruction) {
        case Servo_Write:
          //Serial.print(F("Servo angle: "));
          //Serial.println(central_servo_pckg->angle);
          SoftServo_Write(central_servo_pckg->angle);
          break;

        default:
          break;
      }
    }
  }
};

/* ------------------- Tarea asociada al agente ------------------- */
void servo(void* pvParameters) {
  servoBehaviour b;
  b.execute();
}
