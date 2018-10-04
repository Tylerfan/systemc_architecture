#include  "systemc.h"
#include "transaction.h"
using namespace std;


transaction::transaction(sc_module_name module_name): sc_channel(module_name)
    ,addr("addr")
    ,data("data")
    ,rw("rw")
    ,en("en")
    { 
    
    }

void transaction::write( sc_uint<6> addr, sc_lv<8> data, bool  rw, bool en,bool clk ) {
        this->en->write(en);
        this->rw->write(rw);
        this->addr->write(addr);
        this->data->write(data);
        wait(10, SC_NS);
        cout << "Write out " << this->data->read() << endl;
}


void transaction::read( sc_uint<6> addr, sc_lv<8> data, bool  rw, bool en,bool clk ) {
        this->en->write(en);
        this->rw->write(rw);
        this->addr->write(addr);
        data = this->data->read();
        wait(10, SC_NS);
        cout << "read out" << data << endl;
}