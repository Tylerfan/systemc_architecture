/*************************************************

SystemC Transaction Level Modeling Tutorial
(c) 2/3/2013 W. Rhett Davis (rhett_davis@ncsu.edu)

**************************************************/

#include "stub.h"

using namespace std;

stub::stub (sc_core::sc_module_name name)
  : sc_module(name)
 { 

    //master(*this);
    //master.register_invalidate_direct_mem_ptr(this, &Initiator::invalidate_direct_mem_ptr);
    //dmi_ptr_valid = false;
    SC_THREAD(main);
 }
 
void stub::main(void)
{
    sc_uint<6> read_address = 0;
    sc_uint<6> write_addr = 0;
    sc_lv<8> data = 1;
    bool en = 1;
    bool rw = 0;
    bool clk;

    master_port_one->write(write_addr,data,rw,en,clk);
    master_port_one->read(read_address,data,1,en,clk);

}