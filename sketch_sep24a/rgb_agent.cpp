#include "rgb_agent.h"



// Instancia global del agente
Agent RGB_Control("RGB Control Agent", 1, 192);

/* Comportamiento del agente RGB */
class rgbBehaviour : public CyclicBehaviour {
public:
  void setup() override {
    for (uint8_t i = 0; i < 3; i++) {
      pinMode(RGB_PINS[i], OUTPUT);
      analogWrite(RGB_PINS[i], 0);
    }
  }

  void action() override {
    //Serial.print(F("RGB Control Agent | Watermark: "));
		//Serial.println(uxTaskGetStackHighWaterMark(NULL));
    rgbControlPackage* central_rgb_pckg;
    msg.receive(portMAX_DELAY);

    if (msg.get_msg_type() == INFORM) {
      central_rgb_pckg = (rgbControlPackage*) msg.get_msg_content();

      switch (central_rgb_pckg->instruction) 
      {
        case RGB_Begin:
          //Serial.println("-- Begin --");
          break;

        case RGB_Write: 
          //Serial.println("-- Write --");
          uint8_t r = (central_rgb_pckg->color >> 16) & 0xFF;
          uint8_t g = (central_rgb_pckg->color >>  8) & 0xFF;
          uint8_t b = (central_rgb_pckg->color >>  0) & 0xFF;

          r = int(r * R_OFFSET);
          g = int(g * G_OFFSET);
          b = int(b * B_OFFSET);

          analogWrite(RGB_PINS[0], r);
          analogWrite(RGB_PINS[1], g);
          analogWrite(RGB_PINS[2], b);
          break;

        case RGB_Off:
          //Serial.println("-- Off --");
          for (uint8_t i = 0; i < 3; i++) {
            analogWrite(RGB_PINS[i], 0);
          }
          break;

        default:
          //Serial.println("Instruccion no reconocida");
          break;
      }
    }
  }
};

/* Tarea asociada al agente */
void rgb(void* pvParameters) {
    rgbBehaviour b;
    b.execute();
}
