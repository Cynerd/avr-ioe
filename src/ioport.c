#include <ioport.h>
#ifdef CONFIG_IOPORTS
#ifdef CONFIG_PCINT

struct PCIW {
    uint8_t flags;
    uint8_t mask;
    void (*change) (uint8_t group, uint8_t mask);
};

// Exploiting implementation of libc malloc
#define PCIW_LEN(INPCIW) (*((uint16_t *) INPCIW - 1) / sizeof(struct PCIW) - 1)

#if (defined MCUSUPPORT_PCINT0 && defined MCUSUPPORT_PCINT1 && defined MCUSUPPORT_PCINT2)
#define PCI_COUNT 3
#elif (defined MCUSUPPORT_PCINT0 && defined MCUSUPPORT_PCINT1 || \
        defined MCUSUPPORT_PCINT1 && defined MCUSUPPORT_PCINT2 || \
        defined MCUSUPPORT_PCINT2 && defined MCUSUPPORT_PCINT0)
#define PCI_COUNT 2
#elif (defined MCUSUPPORT_PCINT0 || defined MCUSUPPORT_PCINT1 || defined MCUSUPPORT_PCINT2)
#define PCI_COUNT 1
#else
#define PCI_COUNT 0
#endif

#define GROUP2INDEX(GRP) (GRP - MCUSUPPORT_PCINT0)

static struct PCIW *pciw[PCI_COUNT];
static uint8_t pci_state[PCI_COUNT];
static void pci(int8_t group, int8_t pinmax) {
    int8_t i, y;
    int8_t index = GROUP2INDEX(group);
    int8_t len = (int8_t) PCIW_LEN(pciw[index]);
    // WARN Is possible that PCINT0 is not corresponding with B group and so on?
    uint8_t state = IOE_IO_PIN(group);
    for (i = len; i >= 0; i--) {
        uint8_t stA = state & pciw[index][i].mask;
        uint8_t stB = pci_state[index] & pciw[index][i].mask;
        if (((~stA & stB) && pciw[index][i].flags & IOE_IO_RISING) ||
            ((stA & ~stB) && pciw[index][i].flags & IOE_IO_FALLING)) {
            pciw[index][i].change(IOE_IO_B, mask);
        }
    }
    pci_state[index] = state;
}

void io_change_sethook(uint8_t group, uint8_t mask, uint8_t edge,
                       void (*change) (uint8_t group, uint8_t mask)) {
    int8_t index = (int8_t) GROUP2INDEX(group);
    int8_t len = (int8_t) PCIW_LEN(pciw[index]);
    pciw[index] = realloc(pciw[index], len + 1);
    pciw[index][len].flags = edge;
    pciw[index][len].mask = mask;
    pciw[index][len].change = change;
    switch (group) {
#ifdef MCUSUPPORT_PCINT0 // TODO this wont work with attiny4313 and meaby others
    case IO_B:
        PCICR |= (1<<0);
        PCMSK0 |= mask;
        break;
#endif
#ifdef MCUSUPPORT_PCINT1
    case IO_C:
        PCICR |= (1<<1);
        PCMSK1 |= mask;
        break;
#endif
#ifdef MCUSUPPORT_PCINT2
    case IO_D:
        PCICR |= (1<<2);
        PCMSK2 |= mask;
        break
#endif
    }
}

void io_change_remhook(void (*change) (uint8_t group, uint8_t mask)) {
    int8_t i, y;
    int8_t len;
    for (i = PCI_COUNT - 1; i >= 0; i--) {
        len = (int8_t)PCIW_LEN(pciw[index]);
        for (y = len - 1; y >= 0; y--) {
            if (pciw[i][y].change == change) {

            }
        }
    }
}

void io_change_clearhooks(void) {
}

// WARN This will work only if C is only defined on MCU with also B defined.
#ifdef MCUSUPPORT_PCINT0
ISR(PCINT0_vect, ISR_BLOCK) {
    pci(IO_B, MCUSUPPORT_PCINT0);
}
#endif /* MCUSUPPORT_PCINT0 */

#ifdef MCUSUPPORT_PCINT1
ISR(PCINT1_vect, ISR_BLOCK) {
    pci(IO_C, MCUSUPPORT_PCINT1);
}
#endif /* MCUSUPPORT_PCINT1 */

#ifdef MCUSUPPORT_PCINT2
ISR(PCINT2_vect, ISR_BLOCK) {
    pci(IO_D, MCUSUPPORT_PCINT2);
}
#endif /* MCUSUPPORT_PCINT2 */

#endif /* CONFIG_PCINT */
#endif /* CONFIG_IOPORTS */
