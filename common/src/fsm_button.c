/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm_button.h"
#include "port_button.h"
#include <stdlib.h>



/* State machine input or transition functions */
fsm_trans_t fsm_trans_button[] ;

/* State machine output or action functions */


/* Other auxiliary functions */

fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_button_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_button_init(p_fsm, debounce_time, button_id);
    return p_fsm;
}

/**
 * @brief Initialize a button FSM.
 *
 * This function initializes the default values of the FSM struct and calls the port function
 * to initialize the hardware associated with the given button ID.
 *
 * @param p_this Pointer to an fsm_t struct that contains an fsm_button_t.
 * @param debounce_time Anti-debounce time in milliseconds.
 * @param button_id Unique button identifier number.
 */
void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id) {
    fsm_button_t *p_fsm_button = (fsm_button_t *)(p_this);
    fsm_init(p_this, fsm_trans_button);
 //Aqui hay lio

    p_fsm_button->debounce_time = debounce_time;
    p_fsm_button->button_id = button_id;
    p_fsm_button->tick_pressed = 0;
    p_fsm_button->duration = 0;

    port_button_init(button_id);
}

/**
 * @brief Check if the button has been pressed.
 *
 * This function checks if the button has been pressed by calling the function port_button_is_pressed()
 * and retrieves the status.
 *
 * @param p_this Pointer to an fsm_t struct that contains an fsm_button_t.
 * @return true if the button has been pressed, false otherwise.
 */
static bool check_button_pressed(fsm_t *p_this) {
    // TO-DO alumnos:
    // 1. Llamar a la función port_button_is_pressed() y obtener el estado
    // 2. Devolver el estado

    // Verificar si el puntero p_this es válido
    if (p_this == NULL) {
        // Si el puntero no es válido, devolver false
        return false;
    }
    
    // Llamar a la función port_button_is_pressed() para comprobar si el botón está presionado
    bool status = port_button_is_pressed();
    
    // Devolver el estado del botón
    return status;
};

/**
 * @brief Check if the button has been released.
 *
 * This function checks if the button has been released by calling the function port_button_is_pressed()
 * and retrieves the status. It returns the inverse of the status.
 *
 * @param p_this Pointer to an fsm_t struct that contains an fsm_button_t.
 * @return true if the button has been released, false otherwise.
 */
static bool check_button_released(fsm_t *p_this) {
    // TO-DO alumnos:
    // 1. Llamar a la función port_button_is_pressed() y obtener el estado
    // 2. Devolver el inverso del estado

    // Verificar si el puntero p_this es válido
    if (p_this == NULL) {
        // Si el puntero no es válido, devolver false
        return false;
    }
    
    // Llamar a la función port_button_is_pressed() para comprobar si el botón está presionado
    bool status = port_button_is_pressed();
    
    // Devolver el inverso del estado del botón
    return !status;
};


/**
 * @brief Check if the debounce-time has passed.
 *
 * This function checks if the debounce-time has passed by calling the function port_button_get_tick()
 * to retrieve the current system tick, and compares it with the field next_timeout. It returns true
 * if the current system tick is higher than the field next_timeout, otherwise it returns false.
 *
 * @param p_this Pointer to an fsm_t struct that contains an fsm_button_t.
 * @return true if the debounce-time has passed, false otherwise.
 */
static bool check_timeout(fsm_t *p_this) {

    // Verificar si el puntero p_this es válido
    if (p_this == NULL) {
        // Si el puntero no es válido, devolver false
        return false;
    }
    
    // Obtener el tick del sistema actual llamando a la función port_button_get_tick()
    uint32_t current_tick = port_button_get_tick();
    
    // Obtener el campo next_timeout de p_this
    fsm_button_t* p_fsm_button = (fsm_button_t*)p_this;
    uint32_t next_timeout = p_fsm_button->next_timeout;
    
    // Verificar si el tick del sistema actual es mayor que el campo next_timeout
    if (current_tick > next_timeout) {
        // Si es mayor, devolver true
        return true;
    } else {
        // Si no es mayor, devolver false
        return false;
    }
};

/**
 * @brief Store the system tick when the button was pressed.
 *
 * This function stores the system tick when the button was pressed by calling the function
 * port_button_get_tick() to retrieve the current system tick, and stores it in the field
 * tick_pressed. It also updates the field next_timeout considering the current tick and
 * the field debounce_time.
 *
 * @param p_this Pointer to an fsm_t struct that contains an fsm_button_t.
 */
static void do_store_tick_pressed(fsm_t *p_this) {

    // Verificar si el puntero p_this es válido
    if (p_this == NULL) {
        // Si el puntero no es válido, salir de la función
        return;
    }
    
    // Obtener el tick del sistema actual llamando a la función port_button_get_tick()
    uint32_t current_tick = port_button_get_tick();
    
    // Obtener un puntero a la estructura fsm_button_t
    fsm_button_t* p_fsm_button = (fsm_button_t*)p_this;
    
    // Almacenar el tick del sistema actual en el campo tick_pressed
    p_fsm_button->tick_pressed = current_tick;
    
    // Actualizar el campo next_timeout considerando el tick actual y el debounce_time
    p_fsm_button->next_timeout = current_tick + p_fsm_button->debounce_time;
};

/**
 * @brief Store the duration of the button press.
 *
 * This function stores the duration of the button press by calling the function
 * port_button_get_tick() to retrieve the current system tick, and updating the field
 * duration considering it and the field tick_pressed. It also updates the field
 * next_timeout considering the current tick and the field debounce_time.
 *
 * @param p_this Pointer to an fsm_t struct that contains an fsm_button_t.
 */
static void do_set_duration(fsm_t *p_this) {
    // TO-DO alumnos:
    // 1. Llamar a la función port_button_get_tick() y obtener el tick del sistema actual
    // 2. Actualizar el campo duration considerando el tick actual y el campo tick_pressed
    // 3. Actualizar el campo next_timeout considerando el tick actual y el debounce_time

    // Verificar si el puntero p_this es válido
    if (p_this == NULL) {
        // Si el puntero no es válido, salir de la función
        return;
    }
    
    // Obtener el tick del sistema actual llamando a la función port_button_get_tick()
    uint32_t current_tick = port_button_get_tick();
    
    // Obtener un puntero a la estructura fsm_button_t
    fsm_button_t* p_fsm_button = (fsm_button_t*)p_this;
    
    // Calcular la duración de la pulsación del botón y almacenarla en el campo duration
    p_fsm_button->duration = current_tick - p_fsm_button->tick_pressed;
    
    // Actualizar el campo next_timeout considerando el tick actual y el debounce_time
    p_fsm_button->next_timeout = current_tick + p_fsm_button->debounce_time;
};

fsm_trans_t fsm_trans_button[] = {
    // Definir aquí las transiciones de la FSM del botón
    {BUTTON_RELEASED, check_button_pressed, BUTTON_PRESSED, do_store_tick_pressed},
    {BUTTON_PRESSED, check_timeout, BUTTON_RELEASED_WAIT, do_set_duration},
    {BUTTON_RELEASED_WAIT, check_button_released, BUTTON_RELEASED, NULL},
    {BUTTON_PRESSED_WAIT, check_timeout, BUTTON_RELEASED, do_set_duration},
    {-1, NULL, -1, NULL} // Fila final para indicar el fin de la tabla de transiciones
};



uint32_t fsm_button_get_duration(fsm_t *p_this) {
    // Verificamos si el puntero p_this es válido
    if (p_this == NULL) {
        // Si el puntero no es válido, devolvemos un valor por defecto o gestionamos el error según sea necesario
        return 0; // En este caso, devolvemos 0 como valor por defecto
    }
    
    // Convertimos el puntero a fsm_t* a fsm_button_t* ya que sabemos que es un puntero a una fsm_button_t
    fsm_button_t* p_fsm_button = (fsm_button_t*)p_this;
    
    // Devolvemos el valor del campo duration de p_fsm_button
    return p_fsm_button->duration;
};

/**
 * @brief Reinicia la duración de la última pulsación del botón.
 *
 * Esta función reinicia la duración de la última pulsación del botón a cero.
 *
 * @param p_this Puntero a una estructura fsm_t que contiene un fsm_button_t.
 */
void fsm_button_reset_duration(fsm_t * p_this){
    // Verificamos si el puntero p_this es válido
    // Convertimos el puntero a fsm_t* a fsm_button_t* ya que sabemos que es un puntero a una fsm_button_t
    fsm_button_t* p_fsm_button = (fsm_button_t*)p_this;

    p_fsm_button->debounce_time = 0;
    
};


