Universal synchronous/asynchronous receive/transmitter
======================================================
This part acts as UART intended as text base interface with computer. It is
using hardware termed as USART by Atmel. This hardware also supports synchronous
communication and can behave as SPI master, but this is not supported by this
library (I don't require this feature, but implementation is welcomed).

This part implements, if enabled, whole stack for binding input and output to
stdin and stdout. This is handy during development. You can use `printf` and
`scanf` directly.

This part can be enabled by `CONFIG_USART` configuration option. This enables
more detailed configuration in sub-menu.

## Usage


## References
### usart_init_async
```C
void usart_init_async(void)
```

