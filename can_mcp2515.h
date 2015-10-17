#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "spi.h"

#ifndef _IOE_CAN_MCP2515_H_
#define _IOE_CAN_MCP2515_H_
#ifdef CONFIG_IOE_CAN_MCP2515

void can_mcp2515_init(void);

#endif /* CONFIG_IOE_CAN_MCP2515 */
#endif /* _IOE_CAN_MCP2515_H_ */
