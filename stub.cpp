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
    //master(*this);
    SC_THREAD(main);
    sensitive << clk.pos();
 }
 
void stub::main(void)
{
    address = 1;
    sc_uint<8> data;
    en = 1;
    rw = 0;

    sc_core::sc_time start_time;
    tlm::tlm_generic_payload trans;
    sc_core::sc_time delay = sc_time (10, SC_NS);
    //sc_time clkdly(0, SC_NS);
    trans.set_command(rw ? tlm::TLM_READ_COMMAND : tlm::TLM_WRITE_COMMAND);
    trans.set_address(address);
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    l_data = 15;
    //unsigned char tmp_data = & l_data;
    trans.set_data_ptr((unsigned char*)&l_data);
    trans.set_data_length(1);

    if(sc_core::sc_time_stamp() < start_time)
        wait(start_time - sc_core::sc_time_stamp());

    cout<<"inside  stub"<<endl;
    master_sram->b_transport(trans,delay);

if(trans.get_response_status() != tlm::TLM_OK_RESPONSE){
    cout << sc_core::sc_time_stamp() << " " << sc_object::name() 
         << " ERROR Response Status " << trans.get_response_status() << endl;
}

    rw = 1;

    trans.set_command(rw ? tlm::TLM_READ_COMMAND : tlm::TLM_WRITE_COMMAND);
    trans.set_address(address);
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

        master_sram->b_transport(trans,delay);

    if(trans.get_response_status() != tlm::TLM_OK_RESPONSE){
    cout << sc_core::sc_time_stamp() << " " << sc_object::name() 
         << " ERROR Response Status " << trans.get_response_status() << endl;
}

    //unsigned char tmp_data = & l_data;
    //trans.set_data_ptr((unsigned char*)&l_data);
    //trans.set_data_length(1);


}