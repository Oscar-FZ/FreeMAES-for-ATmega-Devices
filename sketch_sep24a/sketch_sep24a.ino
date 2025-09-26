#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <supporting_functions.h>
#include <maes-rtos.h>
#include <SoftPWM.h>
#include <SunFounder_AI_Camera.h>



#include "rgb_agent.h"
#include "car_control_agent.h"

using namespace MAES;

/*Agentes*/
Agent Central("Central Agent", 1, 256);

/*Declaraci�n de funciones de tarea*/
void central(void* pvParameters);

/*plataforma*/
Agent_Platform AP_GALAXY_RVR("windows");


/*Comportamiento del agente central*/
class centralBehaviour :public CyclicBehaviour {
public:
	void setup() {
    msg.add_receiver(RGB_Control.AID());
		msg.add_receiver(Car_Control.AID());
	}

	void action() {
		// rgbControlPackage central_rgb_pckg;
		// rgbInstructions rgb_inst = RGB_Write;
		// uint32_t color = RED; 
		// uint8_t red = (color >> 16) & 0xFF;
		// uint8_t green = (color >> 8) & 0xFF;
		// uint8_t blue = color & 0xFF;

		// central_rgb_pckg = { rgb_inst, color, red, green, blue };
		// msg.set_msg_content((char*)&central_rgb_pckg);
		// msg.set_msg_type(INFORM);
		// msg.send();
		// AP_GALAXY_RVR.agent_wait(pdMS_TO_TICKS(2000));



    carControlPackage central_car_pckg;
		carInstructions car_inst = Car_SetMotors;
		int8_t power1 = 10;
		int8_t power2 = -10;
		central_car_pckg = {car_inst, power1, power2};
		msg.set_msg_content((char*)&central_car_pckg);
		msg.set_msg_type(INFORM);
		msg.send();
		AP_GALAXY_RVR.agent_wait(pdMS_TO_TICKS(2000));


	}
};


/*Definicion de la funcion del agente central*/
void central(void* pvParameters) {
	centralBehaviour b;
	b.execute();
}

void setup() 
{
    Serial.begin(9600);
    SoftPWMBegin();
    while (!Serial) {;}   // espera a que el monitor serie esté listo (opcional)

    Serial.println("FreeMAES \n");
    AP_GALAXY_RVR.agent_init(&Central, central);
    //AP_GALAXY_RVR.agent_init(&RGB_Control, rgb);
    AP_GALAXY_RVR.agent_init(&Car_Control, car);
    AP_GALAXY_RVR.boot();
    Serial.println("boot exitoso \n");

    vTaskStartScheduler();

    for (;;); // ??
}

//void loop() {}
