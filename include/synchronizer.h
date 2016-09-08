// EPOS Synchronizer Abstractions Common Package

#ifndef __synchronizer_h
#define __synchronizer_h

#include <cpu.h>
#include <thread.h>
#include <utility/ostream.h>

__BEGIN_SYS


class Synchronizer_Common
{
private:
    OStream c;
protected:
    Thread::Queue _waiting; 
    
    Synchronizer_Common() {
         _waiting = Thread::Queue();
    }
    
    
    // Atomic operations
    bool tsl(volatile bool & lock) { return CPU::tsl(lock); }
    int finc(volatile int & number) { return CPU::finc(number); }
    int fdec(volatile int & number) { return CPU::fdec(number); }

    // Thread operations
    void begin_atomic() { Thread::lock(); }
    void end_atomic() { Thread::unlock(); }
    
    //Exercise
    void block() { 
        //begin_atomic();
        Thread *current = Thread::self();
        _waiting.insert(&current->_link);
        current->wait();
    }
    
    void release() { 
        //begin_atomic();
        if (!_waiting.empty()) {
            Thread *next = _waiting.remove()->object();
            next->sinalize();
        }
    }
    //
    
    void sleep() { Thread::yield(); } // implicit unlock()
    void wakeup() { end_atomic(); }
    void wakeup_all() { end_atomic(); }
};

__END_SYS

#endif

