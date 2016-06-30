Tasks
=====
Tasks can be used for sharing processor for example during period of waiting for
interrupt. Planing is based on priority.

## Functions
### tasks_run
```C
int8_t tasks_run(void)
```
This function starts tasks execution. Should be called after all task slots are
prepared and at least one task is started. This function exits if no task exist or
all existing tasks exited.

### task_init

## Structures
### Task
```C
typedef struct {
    uint8_t flags;
    void (*func) (void);
} Task;
```

### TaskSlot
```C
typedef struct {
    uint8_t flags;
    Task *task;
    uint8_t stack_size;
    uint8_t stack[];
} TaskSlot;
```

### Mutex

### Semaphore
