// file moore.h
#include <systemc.h>


SC_MODULE(moore) {
    sc_in<bool> a, clk, reset;
    sc_out<bool> z;
    enum state_type {s0, s1, s2, s3};
    sc_signal<state_type> moore_st;
    void prc_moore();
    SC_CTOR(moore) {
        SC_METHOD(prc_moore);
        sensitive_pos << clk;
    }
};