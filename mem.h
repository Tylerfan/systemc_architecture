#include  "systemc.h"
#include  "tlm.h"

const int WORD_SIZE = 8;
const int ADDR_SIZE = 6;
const int MEM_SIZE = 100;

class mem: public sc_core::sc_module
{
    public:
    SC_HAS_PROCESS(mem);
    mem(sc_core::sc_module_name module_name);
    /* slave bus port */
    tlm_utils::simple_target_socket<mem,32,tlm::tlm_base_protocol_types>  slave;
    void custom_b_transport( tlm::tlm_generic_payload &gp, sc_core::sc_time &delay );
    void prc_memory();
    /*      signals     */
    sc_in<bool> en,rw,clk;
    sc_in<sc_uint<ADDR_SIZE> > addr;
    sc_inout_rv<8> data;
    sc_uint<6> ram[MEM_SIZE]; // 100 size of ram

};
