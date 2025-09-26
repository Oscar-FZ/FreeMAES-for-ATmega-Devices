#ifndef RGB_AGENT_H
#define RGB_AGENT_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <SoftPWM.h>
#include <supporting_functions.h>
#include <maes-rtos.h>

using namespace MAES;

/** Indicate whether RGB leds are common-anodes or not 
 * - 0 common cathode
 * - 1 common anode
*/
#define COMMON_ANODE 0

/** Set the pins of RGB leds, the order is R,G,B */
#define RGB_PINS (uint8_t[3]){12, 13, 11}

/**
 * @name Defines the hexadecimal value of the color
 */
#define RED           0xFF0202
#define ORANGE        0xFFA500
#define YELLOW        0xFFFF0A
#define YELLOW_GREEN  0xA5FF0A
#define GREEN         0x0AFF0A
#define GREEN_CYAN    0x0AFFA5
#define CYAN          0x0AFFFF
#define CYAN_BLUE     0x0AA5FF
#define BLUE          0x0A0AFF
#define PURPLE        0xA50AFF
#define VOILET        0xFF0AFF
#define MAGENTA       0xFF0AA5

/* Calibrate brightness */
#define R_OFFSET  1.0
#define G_OFFSET  0.25
#define B_OFFSET  0.45

/* Enum de los tipos de instrucciones que RGB_Control puede hacer */
typedef enum rgbIntructions : uint8_t {
    RGB_Begin,
    RGB_Write,
    RGB_Off
} rgbInstructions;

/* Struct del tipo de paquete que Central envia a RGB_Control */
typedef struct {
    rgbInstructions instruction;
    uint32_t color;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgbControlPackage;

/* Declaración global del agente */
extern Agent RGB_Control;

/* Función de tarea asociada */
void rgb(void* pvParameters);

#endif // RGB_AGENT_H
