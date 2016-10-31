// EPOS Mutex Abstraction Declarations

#ifndef __mutex_h
#define __mutex_h

#include <synchronizer.h>
#include <pi_simple.h>

__BEGIN_SYS

class Mutex: protected Synchronizer_Common, protected Simple_Priority_Inv_Handler
{
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

private:
    volatile bool _locked;
};

__END_SYS

#endif
