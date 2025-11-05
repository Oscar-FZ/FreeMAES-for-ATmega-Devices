#ifndef SOFT_SERVO_AGENT_H
#define SOFT_SERVO_AGENT_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <supporting_functions.h>
#include <maes-rtos.h>
#include <SoftPWM.h>

using namespace MAES;

/* ------------------- Configuración del Servo ------------------- */
#define SERVO_PIN 6

/* ------------------- Enumeración de instrucciones ------------------- */
typedef enum servoInstructions : uint8_t {
    Servo_Write
} servoInstructions;

/* ------------------- Paquete de datos para el agente ------------------- */
typedef struct {
    servoInstructions instruction;
    uint8_t angle;   // 0–180 grados
} servoControlPackage;

/* ------------------- Declaración del agente ------------------- */
extern Agent Servo_Control;

/* ------------------- Prototipo de la tarea asociada ------------------- */
void servo(void* pvParameters);

/* ------------------- Función auxiliar ------------------- */
void SoftServo_Write(uint8_t angle);

#endif // SOFT_SERVO_AGENT_H
