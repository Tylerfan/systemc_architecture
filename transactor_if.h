#pragma once

#include "systemc.h"

class transactor_if: virtual public sc_interface {
    public:
        virtual void write(sc_uint<6> address, sc_lv<8> data, bool en, bool rw ,bool clk) = 0;
        virtual void read(sc_uint<6> address, sc_lv<8> data, bool en, bool rw,bool clk ) = 0;
};