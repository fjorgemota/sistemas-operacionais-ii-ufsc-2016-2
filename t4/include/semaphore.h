// EPOS Semaphore Abstraction Declarations

#ifndef __semaphore_h
#define __semaphore_h

#include <synchronizer.h>
#include <pi_mult.h>

__BEGIN_SYS

class Semaphore: protected Synchronizer_Common, protected Mult_Priority_Inv_Handler
{
public:
    Semaphore(int v = 1);
    ~Semaphore();

    void p();
    void v();

private:
    volatile int _value;
};


__END_SYS

#endif
