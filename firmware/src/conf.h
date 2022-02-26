/**
 * @file conf.h
 *
 * @defgroup CONF Configurations
 *
 * @brief General configuration of the system.
 *
 * @{
 */

#ifndef CONF_H
#define CONF_H

#ifndef F_CPU
#define F_CPU 16000000UL    //define a frequencia do microcontrolador - 16MHz
#endif /* ifndef F_CPU */


// CONFIGURACOES DE COMPILACAO
#define DEBUG_ON
#define VERBOSE_ON
#define VERBOSE_ON_CAN_APP
//#define VERBOSE_ON_MACHINE
//#define VERBOSE_ON_ADC
#define VERBOSE_ON_INIT
#define VERBOSE_ON_ERROR
//#define PRINT_INFOS

#define CAN_SIGNATURE_SELF      CAN_SIGNATURE_MAC22

// MODULES ACTIVATION
#define USART_ON
#define CAN_ON
#define CAN_DEPENDENT
// #define ADC_ON
#define MACHINE_ON
#define LED_ON
#define WATCHDOG_ON
//#define SLEEP_ON
#define CONTACTOR_ON

#ifdef CONTACTOR_ON
#define CONTACTOR_FORWARD_COIL PC0
#define CONTACTOR_REVERSE_COIL PC1
#define CONTACTOR_DDR DDRC
#define CONTACTOR_PIN PINC
#define CONTACTOR_PORT PORTC
#endif

#ifdef MACHINE_ON
#define MACHINE_TIMER_FREQUENCY             300           //<! machine timer frequency in Hz
#define MACHINE_TIMER_PRESCALER             1024          //<! machine timer prescaler
#define MACHINE_FREQUENCY                   100           //<! machine frequency in Hz
#define MACHINE_CLK_DIVIDER_VALUE           (MACHINE_TIMER_FREQUENCY)/(MACHINE_FREQUENCY)  //<! machine_run clock divider
#endif // MACHINE_ON

#ifdef LED_ON
#define     LED_PORT                PORTD
#define     LED_PIN                 PIND
#define     LED_DDR                 DDRD
#define     LED1                    PD5
#define     LED2                    PD6
#define     cpl_led(y)              cpl_bit(LED_PORT, y)
#define     set_led(y)              set_bit(LED_PORT, y)
#define     clr_led(y)              clr_bit(LED_PORT, y)
#else
#define     cpl_led()
#define     set_led()
#define     clr_led()
#endif // LED_ON


#ifdef CAN_ON
#define SPI_ON
#define CAN_APP_SEND_STATE_FREQ             10//36000     //<! state msg frequency in Hz

// CANBUS DEFINITONS
// ----------------------------------------------------------------------------
/* Global settings for building the can-lib and application program.
 *
 * The following two #defines must be set identically for the can-lib and
 * your application program. They control the underlying CAN struct. If the
 * settings disagree, the underlying CAN struct will be broken, with
 * unpredictable results.
 * If can.h detects that any of the #defines is not defined, it will set them
 * to the default values shown here, so it is in your own interest to have a
 * consistent setting. Ommiting the #defines in both can-lib and application
 * program will apply the defaults in a consistent way too.
 *
 * Select if you want to use 29 bit identifiers.
 */
#define	SUPPORT_EXTENDED_CANID	0

/* Select if you want to use timestamps.
 * Timestamps are sourced from a register internal to the AT90CAN.
 * Selecting them on any other controller will have no effect, they will
 * be 0 all the time.
 */
#define	SUPPORT_TIMESTAMPS		0

#endif // CAN_ON

/**
 * @}
 */

#endif /* ifndef CONF_H */
