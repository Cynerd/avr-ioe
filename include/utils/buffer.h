#ifndef _IOE_BUFFER_H_
#define _IOE_BUFFER_H_

// Define new buffer
#define IOEBUFFER(type, name, size) struct { \
		uint8_t rindex, windex; \
		type data[size]; \
	} name;

#define IOEBUFFER_INIT(name, size) { \
	name.windex = size - 1; \
	name.rindex = size - 1; \
	}

#define IOEBUFFER_MODE_BLOCK 0
#define IOEBUFFER_MODE_OVERWRITE 1
#define IOEBUFFER_MODE_DROP 2
#define IOEBUFFER_MODE_ERROR 3
// Add data to buffer. If buffer is full then behavior is defined by selected mode.
#define IOEBUFFER_PUT(name, size, idata, mode) { \
	if (mode == IOEBUFFER_MODE_BLOCK) { \
		if (name.windex == 0) { \
			while (name.rindex == size - 1); \
		} else { \
			while (name.rindex == name.windex - 1); \
		} \
	} \
	name.data[name.windex] = idata; \
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
	} }

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

/////////////////////////////////////////////////////////////////////

#ifdef CONFIG_IOE_BUFFER
#include <stdint.h>

#define IOEBUFFER_F_MODE_BLOCK 0x0
#define IOEBUFFER_F_MODE_OVERWRITE 0x1
#define IOEBUFFER_F_MODE_DROP 0x2
#define IOEBUFFER_F_MODE_ERROR 0x3

typedef struct {
	uint8_t rindex, windex, size, flags;
	void **data;
} IOEBuffer;

int8_t ioebuffer_init(IOEBuffer * buf, uint8_t size, uint8_t flags);
void ioebuffer_uninit(IOEBuffer * buf);
int8_t ioebuffer_put(IOEBuffer * buf, void *data);
int8_t ioebuffer_get(IOEBuffer * buf, void **data);
void ioebuffer_clean(IOEBuffer * buf);
uint8_t ioebuffer_cnt(IOEBuffer * buf);

#endif /* CONFIG_IOE_BUFFER */
#endif /* _IOE_BUFFER_H_ */
