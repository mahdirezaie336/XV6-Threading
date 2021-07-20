#include "types.h"
#include "param.h"
#include "syscall.h"
#include "traps.h"
#include "fs.h"
#include "mmu.h"


int thread_create(void (*fn) (void *), void *arg)
{
    void *ptr = malloc(2 * PGSIZE);

    if ((uint)ptr%PGSIZE)
        ptr += PGSIZE - (uint) ptr%PGSIZE;

    int tid = clone(ptr);
    if (tid < 0)
    {
        return -1;
    }
    else if (tid == 0)
    {
        (*fn)(arg);
        free(ptr);
        exit();
    }
    else
    {
        return tid;
    }
}

int thread_join(void)
{
    return join();
}