#include "mode_handler_agent.h"
#include "rgb_agent.h"
#include "car_control_agent.h"
#include "soft_servo_agent.h"

/* Instancia global del agente */
Agent Mode_Handler_Agent("Mode Handler Agent", "1", "192");

uint32_t rgb_blink_interval = 500; // ms
uint32_t rgb_blink_start_time = 0;
bool rgb_blink_flag = false;


/* ---------------------------------------------------------- */
/* Comportamiento del agente Mode_Handler_Agent               */
/* ---------------------------------------------------------- */
class modeHandlerBehaviour : public CyclicBehaviour {
private:
  rgbControlPackage central_rgb_pckg;
	rgbInstructions rgb_inst = RGB_Off;
  uint32_t color = 0x00000000; 
  uint8_t red = (color >> 16) & 0xFF;
  uint8_t green = (color >> 8) & 0xFF;
  uint8_t blue = color & 0xFF;

  carControlPackage central_car_pckg;
	carInstructions car_inst = Car_Stop;
	int8_t power1 = 0;
	int8_t power2 = 0;

  servoControlPackage central_servo_pckg;
  servoInstructions servo_inst = Servo_Write;
  uint8_t angle = 90;



public:
  void setup() override {
    msg.add_receiver(RGB_Control.AID());
    msg.add_receiver(Car_Control.AID());
    msg.add_receiver(Servo_Control.AID());
  }

  void action() override {
    //Serial.print(F("Mode Handler Agent | Watermark: "));
    //Serial.println(uxTaskGetStackHighWaterMark(NULL));
    switch (currentMode) {
      case MODE_NONE:
        //Serial.println("MODE_NONE");
        rgb_inst = RGB_Write;
        color = 0xFFFFFF;
        car_inst = Car_Stop;
        power1 = 0;
        power2 = 0; 
        angle = 90;
        break;

      case MODE_DISCONNECT:
        //Serial.println("MODE_DISCONNECT");  
        color = RED;
        car_inst = Car_Stop;
        power1 = 0;
        power2 = 0;
        angle = 90;
        break;

      case MODE_OBSTACLE_FOLLOWING:
        //Serial.println("MODE_OBSTACLE_FOLLOWING");
        rgb_inst = RGB_Write;
        color = BLUE;
        car_inst = Car_Forward;
        power1 = 50;
        power2 = 0;
        angle = 10;
        break;

      case MODE_OBSTACLE_AVOIDANCE:
        //Serial.println("MODE_OBSTACLE_AVOIDANCE");
        rgb_inst = RGB_Write;
        color = PURPLE;
        car_inst = Car_Backward;
        power1 = 50;
        power2 = 0;
        angle = 100;
        break;

      case MODE_APP_CONTROL:
        //Serial.println("MODE_APP_CONTROL");
        rgb_inst = RGB_Write;
        color = CYAN;
        car_inst = Car_SetMotors;
        power1 = leftMotorPower;
        power2 = rightMotorPower;
        angle = servoAngle;
        break;

      case MODE_VOICE_CONTROL:
        //Serial.println("MODE_VOICE_CONTROL");
        rgb_inst = RGB_Write;
        color = CYAN;
        car_inst = Car_TurnRight;
        power1 = 50;
        power2 = 0;
        angle = 90;
        break;

      default:
        //Serial.println("Instrucción desconocida");
        break;
    }
    
    red = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;
    central_rgb_pckg = { rgb_inst, color, red, green, blue };
    msg.set_msg_content((char*)&central_rgb_pckg);
    msg.set_msg_type(INFORM);
    msg.send(RGB_Control.AID(), 1);

    central_car_pckg = {car_inst, power1, power2};
    msg.set_msg_content((char*)&central_car_pckg);
    msg.send(Car_Control.AID(), 1);

    central_servo_pckg = {servo_inst, angle};
    msg.set_msg_content((char*)&central_servo_pckg);
    msg.send(Servo_Control.AID(), 1);
  }
};

/* ---------------------------------------------------------- */
/* Tarea asociada al agente Mode_Handler_Agent                */
/* ---------------------------------------------------------- */
void mode(void* pvParameters) {
  modeHandlerBehaviour b;
  b.execute();
}
