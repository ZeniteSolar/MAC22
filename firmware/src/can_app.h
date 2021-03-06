/**
 * @file can_app.h
 *
 * @defgroup CANAPP    Application Module for canbus
 *
 * @brief The application layer module for canbus
 *
 * @{
 */

#ifndef CAN_APP_H
#define CAN_APP_H

#include "conf.h"
#include "dbg_vrb.h"
#include "../lib/bit_utils.h"
#include "can.h"
#include "can_ids.h"
#include "machine.h"
#include "usart.h"

void can_app_print_msg(can_t *msg);
void can_app_task(void);
void can_app_send_state(void);
void can_app_send_contactor_response(uint8_t response);
void can_app_msg_extractors_switch(can_t *msg);
void can_app_extractor_mam19_state(can_t *msg);
void can_app_extractor_mam19_contactor_request(can_t *msg);
void check_can(void);

#ifdef CAN_ON
#define CAN_APP_SEND_STATE_CLK_DIV  CAN_APP_SEND_STATE_FREQ
#else
#define CAN_APP_SEND_STATE_CLK_DIV  1
#endif

extern uint32_t can_app_send_state_clk_div;
extern uint32_t can_app_send_measurements_clk_div;
#define CAN_APP_CHECKS_WITHOUT_MAM19_MSG 1000
extern uint16_t can_app_checks_without_mam19_msg;

/**
 * @}
 */

#endif /* ifndef CAN_APP_H */
