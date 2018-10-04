
#ifndef __STUB_H__
#define __STUB_H__

#include <tlm.h>
#include <systemc.h>
//#include "transactor_if.h"
#include <tlm_utils/simple_initiator_socket.h>

class stub
: public sc_core::sc_module                       
{
public:
    tlm_utils::simple_initiator_socket<stub> master_dram;

     tlm_utils::simple_initiator_socket<stub> master_sram;
    //sc_port<transactor_if> master_port_one;

    //sc_port<transactor_if> master_port_two;
    sc_uint<8> data;
    sc_uint<8> address;
    bool en ;
    uint8_t l_data;
    sc_in<bool> clk;

    SC_HAS_PROCESS(stub);  
    stub(sc_core::sc_module_name name);
    void main(void);
    //sc_signal<bool> en ;
    sc_signal<bool> rw ;

};


#endif /* __STUB_H__ */
