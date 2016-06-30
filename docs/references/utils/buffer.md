buffer
======
In whole project are used ring buffers. This is so common that handling them is
exported to separated header file. In fact it contains two implementations of
buffers. One implementation is defined using preprocessor macros. Another one is
plain C code.

## Preprocessor implementation
Preprocessor implementation is expected to be faster and less memory intense. Also
more suitable for buffers of simple types (such us int). But this buffer has to be
defined with known size at compile time and can't be resized. All this makes it
good implementation for IO devices input and output buffers, but less for more
complicated tasks containing for example sorting.

### Macros
#### IOEBUFFER
```C
IOEBUFFER(type, name, size)
```
This macro defines buffer. Use it to define new buffer.
##### Parameters
| type | Specify type of elements in buffer. Can be any valid C type |
| name | Name of buffer. This is C variable name.                    |
| size | Numerical value of buffer size                              |

#### IOEBUFFER_INIT
```C
IOEBUFFER_INIT(name, size)
```
Use this to initialize buffer. Parameter `size` must be same as for IOEBUFFER
(definition of buffer). You can use this also to reset buffer (remove all data
from buffer).
##### Parameters
| name | Name if buffer. This is C variable name. |
| size | Numerical value of buffer size           |

#### IOEBUFFER_PUT
```C
IOEBUFFER_PUT(name, size, data, mode)
```
Use this macro to add new data to buffer.
##### Parameters
| name | Name of buffer. This is C variable name. |
| size | Numerical value of buffer size           |
| data | Data to be stored to buffer              |
| mode | This specifies action if buffer is full. |
##### Modes
| IOEBUFFER_MODE_BLOCK     | Block execution until buffer has some free space. |
| IOEBUFFER_MODE_OVERWRITE | Overwrites oldest added (fist to be read)         |
| IOEBUFFER_MODE_DROP      | New data won't be stored to buffer if full        |

#### IOEBUFFER_GET
```C
IOEBUFFER_GET(name, size, variable)
```
Get value from buffer. Value is stored in `variable` (it is variable of same type
as buffer data, not pointer to variable of same type). If no data is in buffer,
variable is set to NULL.
##### Parameters
| name     | Name of buffer. This is C variable name.  |
| size     | Numerical value of buffer size.           |
| variable | Variable in which data will be stored in. |

#### IOEBUFFER_CNT
```C
IOEBUFFER_CNT(name, size, variable)
```
Counts number of data entries in buffer and saves value to variable.
##### Parameters
| name     | Name of buffer. This is C variable name.                    |
| size     | Numerical value of buffer size.                             |
| variable | Int/Unsigned type variable where data count will be stored. |

## C implementation
C implementation is more general. Size is defined by calling initialization
function. But it is using general pointers, so it is only able store pointers.

As buffer identification is used defined type `IOEBuffer`. All functions takes
pointer to this type as parameter. Because of this, it won't be described for
every function.

### Functions
#### ioebuffer_init
```C
int8_t ioebuffer_init(IOEBuffer *buf, uint8_t size, uint8_t flags)
```
Initialized buffer and allocates required resources.
##### Parameters
| size  | Number of elements to be maximally stored in buffer |
| flags | TODO
##### Flags
TODO

#### ioebuffer_uninit
```C
void ioebuffer_uninit(IOEBuffer *buf)
```
Frees all resources allocated during initialization of buffer. Use this every time
you are freeing buffer.

#### ioebuffer_put
```C
int8_t ioebuffer_put(IOEBuffer *buf, void *data)
```
Add `data` to buffer
