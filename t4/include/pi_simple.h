// EPOS Priority Inversion Abstraction Declarations

#ifndef __pi_simple_h
#define __pi_simple_h

#include <thread.h>
#include <pi.h>

__BEGIN_SYS

class Simple_Priority_Inv_Handler : protected Priority_Inversion_Common {
 protected:
    Thread *_owner;
    
    void p_check();
    
    void p_owner();
    
    void v_owner();
};

__END_SYS

#endif
