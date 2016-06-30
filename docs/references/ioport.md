IO port
=======
And define: `CONFIG_IOE_IOPORT`

Defines simple access to io ports. This allows runtime access to any pin with just
serialized identifier.

Most of the functions has group and mask arguments. Group is letter, but in this
library is represented as number and exact number is defined as macro definition.
Mask is one shifted by index number(use \_BV macro). This way can be
addressed all IO ports. Exact identification consult with datasheet. You can also
use more than one index number and control more ports in single group with single
command.

WARNING: No check is implemented for right group number. Usage of unsupported
value is undefined (write to other parts of memory can happen).

Configuration
-------------
To use this part, you must enable `CONFIG_IOPORTS` option.  
This part also handles pin change interrupts. Enable it using
`CONFIG_IOPORTS_PCINT` option.

References
----------
### For output
#### Function io_setout
```C
static inline void io_setout(uint8_t group, uint8_t mask)
```
Configures port of `group` with `mask` as output.  
Parameters:  
__group__ - Character specifying exact port group  
__mask__  - Binary shifted 1. Shift is equal to port index in specified group.  

#### Function io_hight
```C
static inline void io_hight(uint8_t group, uint8_t mask)
```
Sets output port to hight (also can be called as 1).  
WARNING: Invoke this only if io_setout is called before.

Parameters:  
__group__ - Character specifying exact port group  
__mask__  - Binary shifted 1. Shift is equal to port index in specified group.  

#### Function io_low
```C
static inline void io_low(uint8_t group, uint8_t mask)
```
Sets output port to low (also called as 0).  
WARNING: Invoke this only if io_setout is called before.

Parameters:  
__group__ - Number specifying exact port group  
__mask__  - Binary shifted 1. Shift is equal to port index in specified group.  

#### Function io_set
```C
static inline void io_set(uint8_t group, uint8_t mask, int8_t val)
```
Sets output port to value passed as argument.  
WARNING: Invoke this only if io_setout is called before.  
Parameters:  
__group__ - Number specifying exact port group  
__mask__  - Binary shifted 1. Shift is equal to port index in specified group.  

### For input
#### Function io_setin
```C
static inline void io_setin(uint8_t group, uint8_t mask,
                                enum ioeIOInResistor resistor)
```
Configures port of `group` with `mask` as input with specified pull-up/down
resistor.

Parameters:  
__group__ - Number specifying exact port group  
__mask__  - Binary shifted 1. Shift is equal to port index in specified group.  

#### Function io_get
```C
static inline int8_t io_get(uint8_t group, uint8_t mask)
```
Returns current value of port. Note that you can use this also if port is
configured as output.

Parameters:  
__group__ - Number specifying exact port group  
__mask__  - Binary shifted 1. Shift is equal to port index in specified group.  

#### Enum ioeIOInResistor
```C
enum ioeIOInResistor {
    IOE_IO_PULLUP,
    IOE_IO_PULLDOWN
};
```
This enum is used as argument for io_setin. Names should be self explanatory
in this case.

### Pin change interrupts
#### Function io_change_sethook
```C
int8_t io_change_sethook(uint8_t group, uint8_t mask, uint8_t edge,
                           void (*change) (uint8_t group, uint8_t mask))
```
Registers function `change` as hook for pin change interrupt. `group` and `mask`
specifies port and edge specifies on what edge should hook be called. `edge` can
be IO_RISING or IO_FALLING or their binary combination with operator
`|`.  
WARNING: `change` call is call during interrupt handling. You shouldn't be
blocking execution for long time.

Parameters:  
__group__  - Number specifying exact port group.  
__mask__   - Binary shifted 1. Shift is equal to port index in specified group.  
__edge__   - Signals on what edge should be hook called.  
__change__ - Pointer to function used as interupt hook.  

#### Function io_change_remhook
```C
int8_t io_change_remhook(void (*change) (uint8_t group, uint8_t mask))
```
Removes `change` hook.

Parameters:  
__change__ - Pointer to function used as hook

### Others
#### Definitions IO_{GROUP}
This defines exact numbers related to data-sheet groups. Always use these
definition not direct numbers, you can ensure cross MCU support this way.

#### Definitions IO_{GROUP}{INDEX}
Because specifying group and mask as separate parameters is not always optimal,
mcu support file should define all ports in form of single line definition in
format `IOE_IO_{GROUP}{INDEX}`. Disadvantage is that with these definitions you
can't use binary conjunction and so only one pin can be controlled with it.

Relevant examples
-----------------
* blink
* pcinterrupt

Adding support
--------------
For more information on how add support, see [Adding MCU support](/add_support.md).
Main definition is `MCUSUPPORT_IOPORT`. Define it to enable support.

### IO_{GROUP}
This should define any number that is handy for implementation of `IOE_IOE_PIN`,
`IOE_IO_DDR` and `IOE_IO_PORT`.

### IO_{PIN/DDR/PORT}
These should calculate exact pointers to register `PORT{GROUP}` for PORT variant
and likewise for others with group as argument. Common implementation would be
like this:
```C
#define IOE_IO_PIN(GROUP)  (* (volatile uint8_t *)(PINB + 0x3*GROUP))
```
### IO_{GROUP}{INDEX}
This should be pair of group and one binary shifted to left relative to index.

### MCUSUPPORT_PCINT{NUM}
This defines that MCU supports specific pin change interrupt group. Also it
defines value that is number of pins in group.
