/**
 * @file port_button.h
 * @brief Header for port_button.c file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h" 

/* HW dependent includes */
#include "port_system.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define BUTTON_0_ID                 0
#define BUTTON_0_GPIO               GPIOC
#define BUTTON_0_PIN                13
#define BUTTON_0_DEBOUNCE_TIME_MS   150


/* Typedefs --------------------------------------------------------------------*/
typedef struct
{
    GPIO_TypeDef *p_port;
    uint8_t pin;
    bool flag_pressed;
} port_button_hw_t;

/* Global variables */
extern port_button_hw_t buttons_arr[];

/**
 * @brief Inicializa el botón especificado.
 *
 * Esta función inicializa el hardware asociado con el botón especificado.
 *
 * @param button_id Identificador único del botón.
 */
void port_button_init(uint32_t button_id);

/**
 * @brief Comprueba si el botón especificado está presionado.
 *
 * Esta función comprueba si el botón especificado está actualmente presionado.
 *
 * @param button_id Identificador único del botón.
 * @return true si el botón está presionado, false en caso contrario.
 */
bool port_button_is_pressed(uint32_t button_id);

/**
 * @brief Obtiene el valor actual del contador de ticks del sistema en milisegundos.
 *
 * Esta función devuelve el valor actual del contador de ticks del sistema en milisegundos.
 *
 * @return Valor actual del contador de ticks del sistema en milisegundos.
 */
uint32_t port_button_get_tick();


#endif
