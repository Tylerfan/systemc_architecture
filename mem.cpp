#include  "mem.h"
using namespace std;



mem::mem( sc_core::sc_module_name module_name)
: sc_module (module_name)
{
    slave.register_b_transport(this, &mem::custom_b_transport);
}

void mem::custom_b_transport(){
    sc_lv<WORD_SIZE> allzs(SC_LOGIC_Z);
    sc_lv<WORD_SIZE> allxs(SC_LOGIC_X);

    if(en) {
        if(rw) { //read en
            if(addr.read() < MEM_SIZE){
                data = ram[addr.read()];
                cout<<"data read is" << data;
            }
            else{
                data = allxs;
                #ifndef SYNTHESIS
                    cout<<"address"<<addr<<"is out of range"<<endl;
                #endif
            }
        }


        else{
            if(addr.read() < MEM_SIZE){
                ram[addr.read()] = data;
                cout<< "write data" << data << "at address" << addr;
            }
            #ifndef SYNTHESIS
                else
                    cout <<"address"<<addr<<"is out of range"<<endl;
            #endif
        }
    }
        else
            data = allzs;

}