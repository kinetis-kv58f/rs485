/*
 * delay.h
 *
 *  Created on: Sep 12, 2017
 *      Author: teja
 */

#ifndef INCLUDE_DRIV_DELAY_DELAY_H_
#define INCLUDE_DRIV_DELAY_DELAY_H_

#include "types.h"

/// \brief Initialize hardware (timer) required for delay module
///
/// Initialize hardware (timer) required for delay module
///
/// Initializes timer hardware required to create delays with 1us granularity
/// \return void
extern void delay_init(void);

/// \brief Blocking micro-second grain delay for workhorse module only!
/// \param[in] us Time to delay in microseconds
extern void delay_us_workhorse(uint16_t const us);

/// \brief Blocking milli-second grain delay for workhorse module only!
/// \param[in] ms	Time to delay in milliseconds
extern void delay_ms_workhorse(uint32_t const ms);

/// \brief Get current timer counter value
/// \returns Returns current time of delay timer
/* TODO static inline */
uint32_t delay_get_current_time(void);

/// \brief Registers a non-blocking micro-second granular delay with monitor
/// timer
/// \param[in] us Time to delay in microseconds
extern void delay_us_nonblocking_monitor(uint16_t const us);

/// \brief Checks if non-blocking micro-second granular monitor delay
/// has expired
/// \returns Boolean status representing if the delay timeout has expired
extern bool_t delay_hasExpired_us_nonblocking_monitor(void);

#endif /* INCLUDE_DRIV_DELAY_DELAY_H_ */
