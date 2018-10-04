#include "systemc.h"
#include "top.h"

void next_cycle(sc_signal<bool> &signal_clk);

int sc_main(int arg, char* argv[]){
    int i;
    //sc_signal<bool>  clk;
    sc_signal<sc_uint<6> > addr;
    sc_signal_rv<8> data_in;
    //sc_signal_rv<8> data_out;
    sc_signal<bool> read;
    sc_signal<bool> en;

    sc_clock clock ("my_clock",10,0.5);


    top top("top");
    top.trans.data(data_in);
    top.trans.rw(read);
    top.trans.addr(addr);
    top.trans.en(en);
    top.trans.clk(clock);


    top.sram.data(data_in);
    top.sram.addr(addr);
    top.sram.rw(read);
    top.sram.en(en);
    top.sram.clk(clock);

/*
    top.dram.data(data_in);
    top.dram.addr(addr);
    top.dram.rw(read);
    top.dram.en(en);
    top.dram.clk(clock);
*/    
    sc_trace_file *my_trace_file;
    my_trace_file = sc_create_vcd_trace_file("sram_trace");
    sc_trace(my_trace_file,clock,"clk");
    sc_trace(my_trace_file,addr,"addr");
    sc_trace(my_trace_file,en,"en");
    sc_trace(my_trace_file,read,"rw");
    sc_trace(my_trace_file,data_in,"data_in");
    //sc_trace(my_trace_file,data_out,"data_out");

    sc_core::sc_start(5000,SC_NS);

     return EXIT_SUCCESS;
}

/*
void next_cycle(sc_signal<bool> &signal_clk){
    signal_clk = false;
    sc_start(5,SC_NS);
    signal_clk = true;
    sc_start(5,SC_NS);
}
*/