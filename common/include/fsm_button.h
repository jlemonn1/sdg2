/**
 * @file fsm_button.h
 * @brief Header for fsm_button.c file.
 * @author Javier Limon
 * @author Alejandro Garcia
 * @date hoy
 */

#ifndef FSM_BUTTON_H_
#define FSM_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Other includes */
#include "fsm.h"
#include "port_button.h"

/* Defines and enums ----------------------------------------------------------*/
/* Enums */
enum FSM_BUTTON {
  BUTTON_RELEASED = 0, /*!< Acaba de ser presioando */
  BUTTON_RELEASED_WAIT, /*!< Esperando que vuelva a ser presioando */
  BUTTON_PRESSED, /*!< Acaba de ser presioando */
  BUTTON_PRESSED_WAIT /*!< Ha sido presioando y esta esperando */
};


/* Typedefs --------------------------------------------------------------------*/
 typedef struct{
    fsm_t f;
    uint32_t debounce_time;
    uint32_t next_timeout;
    uint32_t tick_pressed;
    uint32_t duration;
    uint32_t button_id;
} fsm_button_t ;

/* Function prototypes and explanation -------------------------------------------------*/

/**
 * @brief Crea un nuevo objeto de estado finito para el botón.
 *
 * Esta función reserva memoria para un nuevo objeto fsm_button_t,
 * inicializa sus campos según los valores recibidos y devuelve un puntero a él.
 *
 * @param debounce_time Tiempo antirrebote en milisegundos.
 * @param button_id Número de identificación único del botón.
 * @return Puntero al nuevo objeto fsm_button_t.
 */
fsm_t* fsm_button_new(uint32_t debounce_time, uint32_t button_id);

/**
 * @brief Inicializa un FSM de botón.
 *
 * Esta función inicializa los valores predeterminados de la estructura FSM
 * y llama al puerto para inicializar el hardware asociado al ID dado.
 *
 * @param p_this Puntero a una estructura fsm_t que contiene un fsm_button_t.
 * @param debounce_time Tiempo antirrebote en milisegundos.
 * @param button_id Número de identificación único del botón.
 */
void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id);

/**
 * @brief Devuelve la duración de la última pulsación del botón.
 *
 * Esta función devuelve la duración de la última pulsación del botón.
 *
 * @param p_this Puntero a una estructura fsm_t que contiene un fsm_button_t.
 * @return Duración de la última pulsación del botón en milisegundos.
 */
uint32_t fsm_button_get_duration(fsm_t *p_this);

/**
 * @brief Reinicia la duración de la última pulsación del botón.
 *
 * Esta función reinicia la duración de la última pulsación del botón a cero.
 *
 * @param p_this Puntero a una estructura fsm_t que contiene un fsm_button_t.
 */
void fsm_button_reset_duration(fsm_t * p_this);


/**
 * @brief Comprueba si el FSM del botón está activo o no.
 *
 * El botón está inactivo cuando se encuentra en el estado BUTTON_RELEASED.
 *
 * @param p_this Puntero a una estructura fsm_t que contiene un fsm_button_t.
 * @return true si el botón está activo, false si está inactivo.
 */
bool fsm_button_check_activity(fsm_t *p_this) ;







#endif
