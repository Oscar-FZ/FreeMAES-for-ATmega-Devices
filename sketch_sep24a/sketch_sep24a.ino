#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <supporting_functions.h>
#include <maes-rtos.h>
#include <SoftPWM.h>


#include "mode_handler_agent.h"
#include "wifi_agent.h"
#include "rgb_agent.h"
#include "car_control_agent.h"
#include "soft_servo_agent.h"

using namespace MAES;


Agent_Platform AP_GALAXY_RVR("windows");


void setup() {
  Serial.begin(115200);
  SoftPWMBegin();
  while (!Serial) {;}

  Serial.println(F("FreeMAES \n"));
  AP_GALAXY_RVR.agent_init(&WiFi_Agent, wifi);
  AP_GALAXY_RVR.agent_init(&Mode_Handler_Agent, mode);
  AP_GALAXY_RVR.agent_init(&RGB_Control, rgb);
  AP_GALAXY_RVR.agent_init(&Car_Control, car);
  AP_GALAXY_RVR.agent_init(&Servo_Control, servo);
	
  AP_GALAXY_RVR.boot();

  Serial.println(F("boot exitoso \n"));
  vTaskStartScheduler();
  for (;;);
}
