#include  "mem.h"
using namespace std;

mem::mem( sc_core::sc_module_name module_name)
: sc_module (module_name)
{
    slave.register_b_transport(this,&mem::custom_b_transport);
    sc_lv<8> ram[MEM_SIZE]; // 100 size of ram
    m_array = new unsigned char[size_t(100)];
}

void mem::custom_b_transport(tlm::tlm_generic_payload& trans,sc_time& delay){
    tlm::tlm_command cmd    = trans.get_command();

  
    //uint32_t    addr   = trans.get_address();
    unsigned char* data_ptr     =  trans.get_data_ptr();
    unsigned int   len  = trans.get_data_length();
    //unsigned int data_ptr =  trans.get_data_length();
    //unsigned int length  = trans.get_data_length();
   
    memcpy(&m_array[0],data_ptr,len);
    cout  <<"data is "<<hex<<int(m_array[0])<<endl;
    
  sc_core::sc_time mem_delay(10,sc_core::SC_NS);	

    if(cmd  == tlm::TLM_WRITE_COMMAND){
        en.write(1) ;
        rw.write(0);
        addr.write(trans.get_address());
    }

    else
    {
        en.write(true);
        rw.write(true);
        addr.write(trans.get_address());
        //cout<<"read"<<endl;
    }
        wait();
        cout<<sc_core::sc_time_stamp()<<" write en "<<en<<endl;
        cout<<sc_core::sc_time_stamp()<<" write rw "<<rw<<endl;
        cout<<sc_core::sc_time_stamp()<<" write addr  "<<addr<<endl;

    sc_lv<WORD_SIZE> allzs(SC_LOGIC_Z);
    sc_lv<WORD_SIZE> allxs(SC_LOGIC_X);

    if(en) {
        if(rw) { //read en
            if(addr.read() < MEM_SIZE){
                data = ram[addr.read()];
                memcpy(data_ptr,&m_array[0],len);
                cout<<"data read is" <<hex<< int(*data_ptr) <<endl;
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
                ram[addr.read()] = sc_lv<8>((*data_ptr));
                cout<< "write data " <<hex<< int(*data_ptr) << " at address" << addr<<endl;
                trans.set_response_status( tlm::TLM_OK_RESPONSE );
            }
            #ifndef SYNTHESIS
                else
                    cout <<"address"<<addr<<"is out of range"<<endl;
            #endif
        }
    }
        else {
            data = allzs;
            trans.set_response_status( tlm::TLM_COMMAND_ERROR_RESPONSE );
        }

    wait(10,SC_NS);

}