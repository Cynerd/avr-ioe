/* This defines common buffer code for whole library.
 * It is preprocessor generated code.
 * Preprocessor variables chose different implementations. But final
 * implementation is only few lines of code. This way it is included directly
 * to code.
 */
#include "tasks.h"

#ifndef _IOE_BUFFERS_H_
#define _IOE_BUFFERS_H_

// Define new buffer
#define IOEBUFFER(name, size) struct { \
        uint8_t rindex, windex; \
        uint8_t data[size]; \
    } name;

#define IOEBUFFER_INIT(name, size) { \
    name.windex = size - 1; \
    name.rindex = size - 1; \
    }

#define IOEBUFFER_MODE_BLOCK 0
#define IOEBUFFER_MODE_OVERWRITE 1
#define IOEBUFFER_MODE_DROP 2
// Add data to buffer. If buffer is full then behavior is defined by selected mode.
#define IOEBUFFER_PUT(name, size, data, mode) \
    if (mode == IOEBUFFER_MODE_BLOCK) { \
        if (name.windex == 0) { \
            while (name.rindex == size - 1); \
        } else { \
            while (name.rindex == name.windex - 1); \
        } \
    } \
    name.data[name.windex] = data; \
    if (mode != IOEBUFFER_MODE_DROP || \
            (name.windex == 0 && name.rindex == size - 1) || \
            (name.rindex + 1 == name.windex)) { \
        if (name.windex == 0) \
            name.windex = size - 1; \
        else \
            name.windex--; \
    } \
    if (mode == IOEBUFFER_MODE_OVERWRITE && name.windex == name.rindex) { \
        if (name.windex == size - 1) \
            name.windex = 0; \
        else \
            name.windex++; \
    } else;

// Get data from buffer and store it to variable
#define IOEBUFFER_GET(name, size, variable) \
    if (name.rindex != name.windex) { \
        variable = name.data[name.rindex]; \
        if (name.rindex == 0) \
            name.rindex = size - 1; \
        else \
            name.rindex--; \
    } else { \
        variable = 0; \
    }

// Set count of buffered data to variable
#define IOEBUFFER_CNT(name, size, variable) \
    if (name.windex < name.rindex) \
        variable = name.rindex - name.windex; \
    else if (name.windex > name.rindex) \
        variable = size - name.windex + name.rindex; \
    else \
        variable = 0;

#endif /* _IOE_BUFFERS_H_ */
