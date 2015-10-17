#ifdef CONFIG_IOE_SPI
#ifdef MCUSUPPORT_USART

volatile int8_t _spi_busy;

////// Interrupts ////////////////////////////////
void (*spi_receive) (uint8_t data) = 0;

#ifdef CONFIG_IOE_CAN_MCP2515
extern void can_mcp2515_spi_hook(uint8_t);
#endif /* CONFIG_IOE_CAN_MCP2515 */

ISR(SPI_STC_vect, ISR_BLOCK) {
    _spi_busy = 0;
#ifdef CONFIG_IOE_CAN_MCP2515
    can_mcp2515_spi_hook(SPDR);
#endif /* CONFIG_IOE_CAN_MCP2515 */
    if (spi_receive)
        spi_receive(SPDR);
}

#endif /* MCUSUPPORT_SPI */
#endif /* CONFIG_IOE_SPI */
