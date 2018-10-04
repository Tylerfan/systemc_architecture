#include  "systemc.h"
#include  <tlm.h>
#include "tlm_utils/simple_target_socket.h"

const int WORD_SIZE = 8;
const int ADDR_SIZE = 6;
const int MEM_SIZE = 100;

class mem: public sc_core::sc_module
{
    public:
    SC_HAS_PROCESS(mem);
    mem(sc_core::sc_module_name module_name);
    /* slave bus port */
    tlm_utils::simple_target_socket<mem>  slave;
    void custom_b_transport( tlm::tlm_generic_payload &gp, sc_core::sc_time &delay );
    //void prc_memory();
    /*      signals     */
    sc_in<bool>clk;

    sc_signal<uint32_t> en, rw;
    sc_signal<sc_uint<ADDR_SIZE> > addr;
    sc_signal<sc_lv<8> > data;
    unsigned char  *m_array;
     sc_lv<8> ram[MEM_SIZE];

};
