#include "top.h"


top::top(sc_core::sc_module_name name)
: sc_core::sc_module(name)
, trans("trans")
//, dram("dram")
, sram("sram")
, cpu("cpu")
{
cpu.master_port_one(trans);
cpu.master_port_two(trans);
}
