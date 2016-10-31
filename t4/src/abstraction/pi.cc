// EPOS Priority Inversion Abstraction Declarations

#include <utility/ostream.h>
#include <pi.h>
#include <thread.h>

__BEGIN_SYS

OStream cout;

void Priority_Inversion_Common::p_check() {
    
} 

void Priority_Inversion_Common::p_owner() {
    Thread::lock();
    Thread *running = Thread::self();
    if (!running->has_original_priority) {
        // Only sets original priority once..
        running->original_priority = (const Thread::Priority) running->priority();
        running->has_original_priority = true;
        
        cout << "Armazenando prioridade original " << running->priority() <<" para thread " << running << endl;
    }
    Thread::unlock();
}

void Priority_Inversion_Common::v_owner() {
    Thread::lock();
    Thread *running = Thread::self();
    cout << "Verificando se thread " << running << " tem prioridade original.." << endl;
    if (running->has_original_priority) {
        const Thread::Priority p = (const Thread::Priority) running->original_priority;
        cout << "Setando prioridade original " << p <<" para thread " << running << endl;
        running->priority(p);
        running->original_priority = 0;
    }
    Thread::unlock();
}


__END_SYS