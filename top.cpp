#include "top.h"


top::top(sc_core::sc_module_name name)
: sc_core::sc_module(name)
//, dram("dram")
, sram("sram")
, cpu("cpu")
, dram("dram")
{
    cpu.master_sram.bind(sram.slave);
    cpu.master_dram.bind(dram.slave);
    sram.clk(clk);
    cpu.clk(clk);
    dram.clk(clk);
}
