#include "systemc.h"
#include "mem.h"
#include "stub.h"
//#include  "transaction.h"


class top : public sc_core::sc_module
{
    public:
        top  (sc_core::sc_module_name name);

    sc_in<bool> clk;

    //transaction trans;
    //mem dram;
    mem sram;
    stub cpu;
    mem dram;

}; 