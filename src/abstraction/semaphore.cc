// EPOS Semaphore Abstraction Implementation

#include <semaphore.h>
#include <thread.h>



__BEGIN_SYS

Semaphore::Semaphore(int v): _value(v)
{
    db<Synchronizer>(TRC) << "Semaphore(value=" << _value << ") => " << this << endl;
}


Semaphore::~Semaphore()
{
    db<Synchronizer>(TRC) << "~Semaphore(this=" << this << ")" << endl;
}


void Semaphore::p()
{
    db<Synchronizer>(TRC) << "Semaphore::p(this=" << this << ",value=" << _value << ")" << endl;

    fdec(_value);
    begin_atomic();
    if(_value < 0) { // Insert a lock and unlock to grant that nothing will change.
        block();
    } else {
        end_atomic();
    }
        
}


void Semaphore::v()
{
    db<Synchronizer>(TRC) << "Semaphore::v(this=" << this << ",value=" << _value << ")" << endl;

    finc(_value);
    begin_atomic();
    if(_value < 1) {
        release();
    } else {
        end_atomic();
        //notify to remove process from the queue.
    }
}

__END_SYS
