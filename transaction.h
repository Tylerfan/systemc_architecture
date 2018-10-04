#include <systemc.h>
#include "transactor_if.h"

class transaction :  public transactor_if, public sc_channel {
    public:
        sc_in<bool> clk;
        sc_out<sc_uint<6> >  addr;
        sc_inout_rv<8>  data;
        sc_out<bool> rw;
        sc_out<bool> en;
        
    transaction(sc_module_name module_name);

    virtual void write(sc_uint<6> addr,  sc_lv<8> data, bool rw, bool en,bool clk);  
    virtual void read(sc_uint<6> addr,  sc_lv<8> data, bool rw, bool en,bool clk); 

};