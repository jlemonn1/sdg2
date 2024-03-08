/**
 * @file interr.c
 * @brief Interrupt service routines for the STM32F4 platform.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */
// Include HW dependencies:
#include "port_system.h"
#include "port_button.h"

// Include headers of different port elements:
// Declare the volatile variable msTicks to avoid race conditions
static volatile uint32_t msTicks = 0;

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief Interrupt service routine for the System tick timer (SysTick).
 *
 * @note This ISR is called when the SysTick timer generates an interrupt.
 * The program flow jumps to this ISR and increments the tick counter by one millisecond.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. **Increment the System tick counter `msTicks` in 1 count.** To do so, use the function `port_system_get_millis()` and `port_system_get_millis()`.
 *
 * @warning **The variable `msTicks` must be declared volatile!** Just because it is modified by a call of an ISR, in order to avoid [*race conditions*](https://en.wikipedia.org/wiki/Race_condition). **Added to the definition** after *static*.
 *
 */
void SysTick_Handler(void)
{
    msTicks++;
}


/**
 * @brief Handles Px10-Px15 global interrupts.
 *
 * This function identifies the line/pin which has raised the interruption, reads the value of the GPIO of the user button,
 * and performs the desired action. Before leaving, it cleans the interrupt pending register.
 *
 * @note Version 1
 * @todo Read the value of the GPIO of the user button. Use the BUTTON_0_ID index to get the port and pin from the buttons_arr.
 * @todo If the value is HIGH, it means that the button has been released, therefore set the field flag_pressed to false.
 * @todo If the value is LOW, it means that the button has been pressed, therefore set the field flag_pressed to true.
 * @todo Clean the corresponding bit of the PR register. Use the macro BIT_POS_TO_MASK.
 * @todo To clean an interrupt in the Pending Register (PR), we must write '1' in the corresponding bit.
 *
 * @see See section "Ejemplo de interrupción externa" of the reference book for an example of cleaning interrupt in PR.
 * @see Refer to the reference manual STM32F446xx Advanced ARM-based 32-bit MCUs, section "10.3.6 Pending register (EXTI_PR)".
 */
void EXTI15_10_IRQHandler(void)
{
    /* ISR user button */
    if (EXTI->PR & BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin))
    {
        // Read the value of the GPIO of the user button
        bool button_value = port_system_gpio_read(buttons_arr[BUTTON_0_ID].p_port, buttons_arr[BUTTON_0_ID].pin);

        // If the value is HIGH, set the field flag_pressed to false
        if (button_value == HIGH)
        {
            buttons_arr[BUTTON_0_ID].flag_pressed = false;
        }
        // If the value is LOW, set the field flag_pressed to true
        else
        {
            buttons_arr[BUTTON_0_ID].flag_pressed = true;
        }

        // Clean the corresponding bit of the PR register
        EXTI->PR |= BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin);
    }
}
