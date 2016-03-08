#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "spi.h"
#include "global.h"

#ifndef _IOE_CAN_MCP2515_H_
#define _IOE_CAN_MCP2515_H_
#ifdef CONFIG_IOE_CAN_MCP2515
#ifndef CONFIG_IOE_SPI
#error "Please define CONFIG_IOE_SPI. MCP2515 requires SPI."
#endif

// TODO registers
#define CAN_MCP2515_CANCTL
// TODO buffers

typedef struct {
    uint8_t group, mask;
} CanMcp2515;

int8_t can_mcp2515_init(CanMcp2515 * can, uint8_t group, uint8_t mask);

void can_mcp2515_reset(CanMcp2515 * can);
uint8_t can_mcp2515_read(CanMcp2515 * can, uint8_t address);
uint8_t can_mcp2515_readrx(CanMcp2515 * can, uint8_t buffer);
void can_mcp2515_write(CanMcp2515 * can, uint8_t address, uint8_t data);
void can_mcp2515_loadrx(CanMcp2515 * can, uint8_t buffer, uint8_t data);
uint8_t can_mcp2515_rdstat(CanMcp2515 * can);
uint8_t can_mcp2515_rxstat(CanMcp2515 * can);
void can_mcp2515_bitmod(CanMcp2515 * can, uint8_t address, uint8_t mask,
                        uint8_t data);

#endif /* CONFIG_IOE_CAN_MCP2515 */
#endif /* _IOE_CAN_MCP2515_H_ */
