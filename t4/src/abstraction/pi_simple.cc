#include <pi_simple.h>
#include <pi.h>
#include <thread.h>

__BEGIN_SYS

void Simple_Priority_Inv_Handler::p_check() {
    Thread::lock();
    if (!_owner) {
        Thread::unlock();
        return;
    } 
    Priority_Inversion_Common::p_check();
    Thread *running = Thread::self();
    if (running->priority() < _owner->priority()) {
        
        const Thread::Priority &p = (const Thread::Priority) running->priority();
        _owner->priority(p);
    }
    Thread::unlock();
}

void Simple_Priority_Inv_Handler::p_owner() {
    Thread::lock();
    _owner = Thread::self();
    Thread::unlock();
}

void Simple_Priority_Inv_Handler::v_owner() {
    Thread::lock();
    _owner = 0;
    Thread::unlock();
}


__END_SYS