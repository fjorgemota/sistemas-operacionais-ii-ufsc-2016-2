#include <thread.h>
#include <pi_mult.h>
#include <pi.h>
#include <utility/ostream.h>
#include <system/kmalloc.h>

__BEGIN_SYS

Thread::Queue  _owners;
OStream mcout;

Mult_Priority_Inv_Handler::Mult_Priority_Inv_Handler() {
    _owners = Thread::Queue();
}

void Mult_Priority_Inv_Handler::p_check() {
    Priority_Inversion_Common::p_check();
    
    Thread::lock();
    Thread *running = Thread::self();
    Thread *lowestPriority = _owners.tail()->object();
    if (running->priority() < lowestPriority->priority()) {
        const Thread::Priority &p = (const Thread::Priority) running->priority();
        mcout << "Setando prioridade da thread " << lowestPriority << " para " << p << " visto que a thread " << running << " esta esperando" << endl;
        lowestPriority->priority(p); // Implicit unlock()
        // So we update the order of the code
        Thread::lock();
        _owners.remove(lowestPriority);
        _owners.insert(&(lowestPriority->_linkOwner));
        Thread::unlock();
    }
    Thread::unlock();
}

void Mult_Priority_Inv_Handler::p_owner() {
    Priority_Inversion_Common::p_owner();
    Thread::lock();
    // _owners.insert(&(Thread::self()->_linkOwner));
    Thread *running = Thread::self();
    Thread::Queue::Element *link = new (kmalloc(sizeof(Thread::Queue::Element))) Thread::Queue::Element(running, running->_link.rank());
    _owners.insert(link);
    Thread::unlock();
}

void Mult_Priority_Inv_Handler::v_owner() {
    Priority_Inversion_Common::v_owner();
    Thread::lock();
    Thread::Queue::Element *e = _owners.remove(Thread::self());
    kfree(e);
    Thread::unlock();
}

__END_SYS