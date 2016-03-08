#include <can/mcp2515.h>

#ifdef CONFIG_IOE_CAN_MCP2515
// TODO check
#define CAN_MCP2515_RESET   0xC0
#define CAN_MCP2515_READ    0x03
#define CAN_MCP2515_READRX  0x90
#define CAN_MCP2515_WRITE   0x02
#define CAN_MCP2515_LOADTX  0x40
#define CAN_MCP2515_RTS     0x80
#define CAN_MCP2515_RDSTAT  0xA0
#define CAN_MCP2515_RXSTAT  0xB0
#define CAN_MCP2515_BITMOD  0x05

inline void can_mcp2515_init(canMcp2515 * can, uint8_t group, uint8_t mask) {
    can->group = group;
    can->mask = mask;
    can_mcp2515_reset(can);
    // TODO
    return 0;
};

inline void can_mcp2515_reset(canMcp2515 * can) {
    take_mutex(spi_mutex);
    spi_join();

    release_mutex(spi_mutex);
};

inline uint8_t can_mcp2515_read(canMcp2515 * can, uint8_t address) {
};

inline uint8_t can_mcp2515_readrx(canMcp2515 * can, uint8_t buffer) {
};

inline void can_mcp2515_write(canMcp2515 * can, uint8_t address, uint8_t data) {
};

inline void can_mcp2515_loadrx(canMcp2515 * can, uint8_t buffer, uint8_t data) {
};

inline uint8_t can_mcp2515_rdstat(canMcp2515 * can) {
};

inline uint8_t can_mcp2515_rxstat(canMcp2515 * can) {
};

inline void can_mcp2515_bitmod(canMcp2515 * can, uint8_t address, uint8_t mask,
                        uint8_t data) {
};

#endif /* CONFIG_IOE_CAN_MCP2515 */
