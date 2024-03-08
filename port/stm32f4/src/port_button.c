/**
 * @file port_button.c
 * @brief File containing functions related to the HW of the button.
 *
 * This file defines an internal struct which contains the HW information of the button.
 *
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include "port_button.h"
#include "stm32f4xx.h" 

// Definiciones para GPIO_MODE
#define GPIO_MODE_INPUT      0x00
#define GPIO_MODE_OUTPUT     0x01
#define GPIO_MODE_AF         0x02
#define GPIO_MODE_ANALOG     0x03

// Definiciones para GPIO_PULLUP y GPIO_PULLDOWN
#define GPIO_NOPULL         0x00
#define GPIO_PULLUP         0x01
#define GPIO_PULLDOWN       0x02

// Definiciones para EXTI_MODE
#define EXTI_MODE_INTERRUPT       0x00
#define EXTI_MODE_EVENT           0x04
#define EXTI_MODE_BOTH_EDGES      0x0C
#define EXTI_MODE_RISING_EDGE     0x08
#define EXTI_MODE_FALLING_EDGE    0x04

/* Global variables ------------------------------------------------------------*/
port_button_hw_t buttons_arr[] = {
    [BUTTON_0_ID] = {.p_port = BUTTON_0_GPIO, .pin = BUTTON_0_PIN, .flag_pressed = false},
};

/**
 * @brief Configura las especificaciones de hardware de un botón dado.
 *
 * Esta función configura las especificaciones de hardware de un botón dado, incluyendo
 * la configuración del GPIO como entrada sin conexión de pull-up ni pull-down, la configuración
 * de la interrupción en ambos flancos (rising y falling edges) y la habilitación de la línea
 * de interrupción con prioridad 1 y subprioridad 0.
 *
 * @param button_id Identificador del botón. Este índice se utiliza para seleccionar el elemento
 *                 del array buttons_arr[].
 */
void port_button_init(uint32_t button_id)
{
    // Obtener el puerto y el pin del botón desde el array buttons_arr[]
    GPIO_TypeDef *p_port = buttons_arr[button_id].p_port;
    uint8_t pin = buttons_arr[button_id].pin;

    // Configurar el GPIO como entrada sin conexión de pull-up ni pull-down
    port_system_gpio_config(p_port, pin, 0x03, GPIO_PULLUP);

    // Configurar la interrupción en ambos flancos (rising y falling edges)
    port_system_gpio_config_exti(p_port, pin, EXTI_MODE_BOTH_EDGES);

    // Habilitar la línea de interrupción y configurar la prioridad y subprioridad
    port_system_gpio_exti_enable(pin, 1, 0);

    // Habilitar la petición de interrupción para el botón específico en el registro EXTI_IMR
    EXTI->IMR |= (1 << pin);

}

/**
 * @brief Return the status of the button (pressed or not).
 *
 * This function returns the status of the button specified by button_id.
 *
 * @param button_id Button ID. This index is used to select the element of the buttons_arr[] array.
 * @return true If the button has been pressed, false If the button has not been pressed.
 */
bool port_button_is_pressed(uint32_t button_id)
{
    // Obtener el estado del botón desde el array buttons_arr[]
    bool flag_pressed = buttons_arr[button_id].flag_pressed;

    // Retornar el estado del botón
    return flag_pressed;
}

/**
 * @brief Return the count of the System tick in milliseconds.
 *
 * This function retrieves the count of the System tick in milliseconds.
 *
 * @return The count of the System tick in milliseconds.
 */
uint32_t port_button_get_tick()
{
    // Call function port_system_get_millis() to get the current system tick
    return port_system_get_millis();
}





