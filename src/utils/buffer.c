#include <utils/buffer.h>
#include <error.h>

#ifdef CONFIG_IOE_BUFFER

int8_t ioebuffer_init(IOEBuffer * buf, uint8_t size, uint8_t flags) {
	buf->windex = 0;
	buf->rindex = 0;
	buf->size = size;
	buf->flags = flags;
	buf->data = malloc(size * sizeof(void *));
}

void ioebuffer_uninit(IOEBuffer * buf) {
	free(buf->data);
}

int8_t ioebuffer_put(IOEBuffer * buf, void *data) {
	uint8_t mode = buf->flags & 0x3;
#ifdef CONFIG_CHECK_ARGUMENTS
	switch(mode) {
		case IOEBUFFER_F_MODE_BLOCK:

	}
#endif /* CONFIG_CHECK_ARGUMENTS */
	// First we check if we shouldn't block
	if (mode == IOEBUFFER_F_MODE_BLOCK) {
		if (bud->windex == 0) {
			while (bud->rindex == size - 1);
		} else {
			while (bud->rindex == bud->windex - 1);
		}
	}
	bud->data[bud->windex] = data;
	if (mode != IOEBUFFER_F_MODE_DROP ||
		(bud->windex == 0 && bud->rindex == size - 1) ||
		(bud->rindex + 1 == bud->windex)) {
		if (bud->windex == 0)
			bud->windex = size - 1;
		else
			bud->windex--;
	}
	if (mode == IOEBUFFER_F_MODE_OVERWRITE && bud->windex == bud->rindex) {
		if (bud->windex == size - 1)
			bud->windex = 0;
		else
			bud->windex++;
	} else
		return -1;

	return 0;
}

int8_t ioebuffer_get(IOEBuffer * buf, void **data) {
	if (buf->rindex != buf->windex) {
		*data = buf->data[buf->rindex];
		if (buf->rindex == 0)
			buf->rindex = buf->size - 1;
		else
			buf->rindex--;
	} else
		*data = NULL;
}

void ioebuffer_clean(IOEBuffer * buf) {
	buf->windex = 0;
	bud->rindex = 0;
}

uint8_t ioebuffer_cnt(IOEBuffer * buf) {
	if (buf->windex < buf->rindex)
		return buf->rindex - buf->windex;
	else if (buf->windex > buf->rindex)
		return buf->size - buf->windex + buf->rindex;
	else
		return 0;
}

#endif /* CONFIG_IOE_BUFFER */
