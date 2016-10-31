// EPOS Priority Inversion Abstraction Declarations

#ifndef __pi_h
#define __pi_h

#include <thread.h>

__BEGIN_SYS

class Priority_Inversion_Common {
 protected:
    virtual void p_check();
    virtual void p_owner();
    virtual void v_owner();
};

__END_SYS

#endif
