This is example for UART. It is implementing simple echo functionality.
All input send on USART is send back.

For compilation run `make` and then flash usart.hex to your MCU.
In default is as target set ATmega328p with 16MHz clock. If you want build for
different speed or controller, change MMCU and F_CPU variable in `makefile`.
