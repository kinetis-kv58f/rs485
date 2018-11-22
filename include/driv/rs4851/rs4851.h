// � 2011. Ravi Teja Gudapati. All rights reserved.

#ifndef INCLUDE_DRIV_RS4851_RS4851_H_
#define INCLUDE_DRIV_RS4851_RS4851_H_

#include "types.h"

/// \brief Init RS485
/// \param[in] baud	Desired baudrate
extern bool_t rs4851_init(uint32_t const baud);

/// \brief Turn off RS485
extern void rs4851_off(void);

/// \brief Write single byte to RS485
///
///	Blocks until RS485 buffer is empty, then it writes the character to
///	UART and returns.
/// \param[in] data	Byte of data to send
extern void rs4851_putc(uint8_t const data);

/// \brief Read single byte from RS485
///
/// \returns -1 if
extern int16_t rs4851_getc(void);

/// \brief Writes [data] as hex characters to RS485
/// \param[in] data Data
extern void rs4851_print_hex(uint8_t const data);

/// \brief Writes [data] as hex characters to RS485
/// \param[in] data Data
extern void rs4851_print_hex_byte(uint8_t const data);

/// \brief Writes [data] as hex characters to RS485
/// \param[in] data Data
extern void rs4851_print_hex_halfword(uint16_t const data);

/// \brief Writes [data] as hex characters to RS485
/// \param[in] data Data
extern void rs4851_print_hex_word(uint32_t const data);

/// \brief Writes newline to RS485
extern void rs4851_print_newline(void);

#endif /* INCLUDE_DRIV_RS485_RS485_H_ */
