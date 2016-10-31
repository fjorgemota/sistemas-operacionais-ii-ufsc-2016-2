// EPOS Priority Inversion Abstraction Declarations

#ifndef __pi_mult_h
#define __pi_mult_h

#include <thread.h>
#include <pi.h>

__BEGIN_SYS

class Mult_Priority_Inv_Handler : protected Priority_Inversion_Common {
    public: 
        Mult_Priority_Inv_Handler();
     protected:
        Thread::Queue  _owners;
    
        void p_check();
        
        void p_owner();
        
        void v_owner();
};

__END_SYS

#endif
