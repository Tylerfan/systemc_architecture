
#ifndef __STUB_H__
#define __STUB_H__

#include <tlm.h>
#include <systemc.h>
#include "transactor_if.h"

class stub
: public sc_core::sc_module                       
{
public:
    sc_port<transactor_if> master_port_one;

    sc_port<transactor_if> master_port_two;

    SC_HAS_PROCESS(stub);  
    stub(sc_core::sc_module_name name);
    void main(void);

};


#endif /* __STUB_H__ */
