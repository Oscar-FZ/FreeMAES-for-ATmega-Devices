#include "rgb_agent.h"



// Instancia global del agente
Agent RGB_Control("RGB Agent", 2, 99);

/* Comportamiento del agente RGB */
class rgbBehaviour : public CyclicBehaviour {
public:
  void setup() override {
    for (uint8_t i = 0; i < 3; i++) {
      SoftPWMSet(RGB_PINS[i], 0);
      SoftPWMSetFadeTime(RGB_PINS[i], 100, 100);
    }
  }

  void action() override {
    rgbControlPackage* central_rgb_pckg;
    msg.receive(portMAX_DELAY);

    if (msg.get_msg_type() == INFORM) {
      //Serial.println("Mensaje recibido:");
      central_rgb_pckg = (rgbControlPackage*) msg.get_msg_content();

      // Serial.print("Instruccion: ");
      // Serial.println(central_rgb_pckg->instruction);

      // Serial.print(" | Color: 0x");
      // Serial.println(central_rgb_pckg->color, HEX);

      // Serial.print(" | Red: ");
      // Serial.println(central_rgb_pckg->red);

      // Serial.print(" | Green: ");
      // Serial.println(central_rgb_pckg->green);

      // Serial.print(" | Blue: ");
      // Serial.println(central_rgb_pckg->blue);

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

          SoftPWMSet(RGB_PINS[0], r);
          SoftPWMSet(RGB_PINS[1], g);
          SoftPWMSet(RGB_PINS[2], b);
          break;

        case RGB_Off:
          //Serial.println("-- Off --");
          for (uint8_t i = 0; i < 3; i++) {
            SoftPWMSet(RGB_PINS[i], 0);
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
