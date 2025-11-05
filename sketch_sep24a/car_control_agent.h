// #ifndef CAR_CONTROL_AGENT_H
// #define CAR_CONTROL_AGENT_H

// #include <Arduino.h>
// #include <Arduino_FreeRTOS.h>
// #include <task.h>
// #include <queue.h>
// #include <supporting_functions.h>
// #include <maes-rtos.h>

// using namespace MAES;

// /* Pines de los motores */
// #define MOTOR_PINS       (uint8_t[4]){2, 3, 4, 5} 
// /* Direcciones de los motores */
// #define MOTOR_DIRECTIONS (uint8_t[2]){0, 1}

// /* Enum que define las instrucciones del carro */
// typedef enum carInstructions : uint8_t {
//     Car_Begin,
//     Car_Forward,
//     Car_Backward,
//     Car_TurnLeft,
//     Car_TurnRight,
//     Car_Stop,
//     Car_SetMotors
// } carInstructions;

// /* Paquete que Central envía a Car_Control */
// typedef struct {
//     carInstructions instruction;
//     int8_t power1;
//     int8_t power2;
// } carControlPackage;

// /* Declaración del agente Car_Control */
// extern Agent Car_Control;

// /* Declaración de la tarea asociada */
// void car(void* pvParameters);

// /* Función para controlar motores */
// void carSetMotors(int8_t power0, int8_t power1);

// #endif // CAR_CONTROL_AGENT_H