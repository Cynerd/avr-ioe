Serial peripheral interface
---------------------------
This interface is link to MOSI and MISO pins. Also SS pin is used when slave mode initialized.

## Functions
### spi_init
```C
static inline void spi_init(enum spiMode mode)
```
Initializes SPI interface.  
Parameters:  
    mode - Specify mode of SPI interface  
  
NOTE: Global interrupt must be enabled for right function of SPI.

### spi_busy
```C
static inline int8_t spi_busy(void)
```
Returns NULL when device is not busy.  
When device is busy return values in non-zero.

### spi_join    
```C
static inline void spi_join(void)
```
Blocks processor until device is not busy.

### spi_send
```C
static inline uint8_t spi_send(uint8_t data)
```
Swap bytes with slave over SPI.  
This function blocks execution until device isn't busy (transfer completed).  
WARNING: Invoke this only when interface is initialized in MASTER mode.

### spi_transfer
```C
static inline void spi_transfer(uint8_t data)
```
Transfer byte to slave over SPI.  
This function isn't blocking execution until transfer is complete.  
Always call spi_join before this function when called outside of spi_receive().  
WARNING: Invoke this only when interface is initialized in MASTER mode.

### spi_expose
```C
static inline void spi_expose(uint8_t data)
```
Expose data for next master request.
Please don't use this when device is busy.
Best place to call this is spi_receive().  
WARNING: Invoke this only when interface is initialized in SLAVE mode.

## Function pointer spi_receive
```C
extern void (*spi_receive)(uint8_t data)
```
This function is called every time transfer is finished.
And until return from this function interrupts are disabled.

## Enum spiMode
```C
enum spiMode {
    SPI_MODE_MASTER,
    SPI_MODE_SLAVE
};
```
This is used as parameter for spi_init function.
