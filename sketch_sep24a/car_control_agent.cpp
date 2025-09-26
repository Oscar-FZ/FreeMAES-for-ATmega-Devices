#include "car_control_agent.h"
#include <SoftPWM.h>

#define MOTOR_POWER_MIN 28

Agent Car_Control("Car Agent", 2, 95);

/* Función para controlar motores (versión demo con Serial) */
void carSetMotors(int8_t power0, int8_t power1) {
  //Serial.print("Set motors: ");
  //Serial.print(power0);
  //Serial.print(" , ");
  //Serial.println(power1);

  /* Implementacion del Arduino */
	bool dir[2];
	int8_t power[2] = { power0, power1 };
	int8_t newPower[2];

	for (uint8_t i = 0; i < 2; i++) {
		dir[i] = power[i] > 0;

		if (MOTOR_DIRECTIONS[i]) dir[i] = !dir[i];

		if (power[i] == 0) {
			newPower[i] = 0;
		}
		else {
			newPower[i] = map(abs(power[i]), 0, 100, MOTOR_POWER_MIN, 255);
		}
		
		SoftPWMSet(MOTOR_PINS[i * 2], dir[i] * newPower[i]);
		SoftPWMSet(MOTOR_PINS[i * 2 + 1], !dir[i] * newPower[i]);
		
	}
}

/* ------------------- Comportamiento del agente Car_Control ------------------- */
class carBehaviour : public CyclicBehaviour {
public:
  void setup() override {
    for (uint8_t i = 0; i < 4; i++) {
      SoftPWMSet(MOTOR_PINS[i], 0);
      SoftPWMSetFadeTime(MOTOR_PINS[i], 100, 100);
    }
  }

  void action() override {
    //Serial.print(Car_Control.AID());
    //Serial.println(": Controlando el carro...");

    
    carControlPackage* central_car_pckg;
    msg.receive(portMAX_DELAY);

    if (msg.get_msg_type() == INFORM) {
      //Serial.println("Mensaje recibido:");
      central_car_pckg = (carControlPackage*) msg.get_msg_content();

      //Serial.print("Instruccion: ");
      //Serial.println(central_car_pckg->instruction);
      //Serial.print(" | Valor1: ");
      //Serial.println(central_car_pckg->power1);
      //Serial.print(" | Valor2: ");
      //Serial.println(central_car_pckg->power2);

      switch (central_car_pckg->instruction) {
        case Car_Begin:
          //Serial.println("-- Begin --");
          break;

        case Car_Forward:
          //Serial.println("-- Forward --");
          carSetMotors(central_car_pckg->power1, (central_car_pckg->power1));
          break;

        case Car_Backward:
          //Serial.println("-- Backward --");
          //carSetMotors(-(central_car_pckg->power1), -(central_car_pckg->power1));
          break;

        case Car_TurnLeft:
          //Serial.println("-- Turn Left --");
          //carSetMotors(-(central_car_pckg->power1), (central_car_pckg->power1));
          break;

        case Car_TurnRight:
          //Serial.println("-- Turn Right --");
          //carSetMotors(central_car_pckg->power1, -(central_car_pckg->power1));
          break;

        case Car_Stop:
          //Serial.println("-- Stop --");
          //carSetMotors(0, 0);
          break;

        case Car_SetMotors:
          //Serial.println("-- Set Motors --");
          carSetMotors(central_car_pckg->power1, central_car_pckg->power2);
          break;

        default:
          //Serial.println("Instruccion no reconocida");
          break;
      }
    }
  }
};

/* Tarea asociada al agente Car_Control */
void car(void* pvParameters) {
    carBehaviour b;
    b.execute();
}
