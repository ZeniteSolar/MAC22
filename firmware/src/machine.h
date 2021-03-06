/**
 * @file machine.h
 *
 * @defgroup MACHINE State Machine Module
 *
 * @brief Implements the main state machine of the system.
 *
 * @{
 */

#ifndef MACHINE_H
#define MACHINE_H

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

#include "conf.h"

// Equations for mode 2 (CTC with TOP OCR2A)
// Note the resolution. For example.. at 150hz, ICR1 = PWM_TOP = 159, so it
#define MACHINE_TIMER_TOP ((F_CPU/(2*MACHINE_TIMER_PRESCALER))/(MACHINE_TIMER_FREQUENCY) -1)

#include "dbg_vrb.h"
#ifdef ADC_ON
#include "adc.h"
#endif
#ifdef USART_ON
#include "usart.h"
#endif
#ifdef CAN_ON
#include "can.h"
#include "can_app.h"
extern const uint8_t can_filter[];
#endif

typedef enum state_machine{
    STATE_INITIALIZING,
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_RESET,
} state_machine_t;

typedef union system_flags{
    struct{
        uint8_t     none          :1;
    };
    uint8_t   all;
} system_flags_t;

typedef union error_flags{
    struct{
        uint8_t     no_canbus     :1;
    };
    uint8_t   all;
}error_flags_t;

typedef enum contactor_request{
    CONTACTOR_REQUEST_TURN_OFF,
    CONTACTOR_REQUEST_SET_FORWARD,
    CONTACTOR_REQUEST_SET_REVERSE,
    CONTACTOR_REQUEST_UNKNOWN = 0xFF,
}contactor_request_t;

typedef struct contactor{
    uint8_t request_available;
    contactor_request_t request;
}contactor_t;

// machine checks
void check_buffers(void);
void reset_measurements(void);

// debug functions
void print_configurations(void);
void print_system_flags(void);
void print_error_flags(void);

// machine tasks
void task_initializing(void);
void task_idle(void);
void task_running(void);
void task_error(void);
void task_reset(void);

// the machine itself
void set_machine_initial_state(void);
void machine_init(void);
void machine_run(void);
void set_state_error(void);
void set_state_initializing(void);
void set_state_idle(void);
void set_state_running(void);
void set_state_reset(void);

// Contactor functions
void contactor_init(void);
void control_contactor_coil(contactor_request_t request);

// machine variables
extern volatile state_machine_t state_machine;
extern volatile system_flags_t system_flags;
extern volatile error_flags_t error_flags;
extern volatile uint8_t machine_clk;
extern volatile uint8_t machine_clk_divider;
extern volatile uint8_t total_errors;           // Contagem de ERROS

// other variables
extern volatile uint8_t led_clk_div;
extern volatile contactor_t contactor;

/**
 * @}
 */

#endif /* ifndef MACHINE_H */
