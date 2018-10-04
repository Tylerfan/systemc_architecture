#include "systemc.h"
#include "top.h"

void next_cycle(sc_signal<bool> &signal_clk);

int sc_main(int arg, char* argv[]){
    int i;

   	sc_time clkprd(10, SC_NS);
	sc_time clkdly(0, SC_NS);
	sc_clock clk("clk", clkprd, 0.5, clkdly, true);
    top top("top");
    top.clk(clk);
/*
    top.dram.data(data_in);
    top.dram.addr(addr);
    top.dram.rw(read);
    top.dram.en(en);
    top.dram.clk(clock);
*/       
    //sc_trace(my_trace_file,data_out,"data_out");

     sc_trace_file *my_trace_file;
    my_trace_file = sc_create_vcd_trace_file("sram_trace");
    sc_trace(my_trace_file,clk,"clk");
    sc_trace(my_trace_file,top.cpu.address,"addr");
    sc_trace(my_trace_file,top.cpu.en,"en");
    sc_trace(my_trace_file,top.cpu.rw,"rw");
    sc_trace(my_trace_file,top.cpu.l_data,"data_in");



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