#include <stdint.h>

#ifndef _IOE_CAN_GLOBAL_
#define _IOE_CAN_GLOBAL_

typedef struct {
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} CanFrame;

typedef struct {
    CanFrame **buffer;
    void *udata;
} Can;


void can_send(Can *can, CanFrame *frame);

#endif /* _IOE_CAN_GLOBAL_ */
