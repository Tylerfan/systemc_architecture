// file moore.cpp
#include "moore.h"

void moore::prc_moore() {
    if(reset)
        moore_st = s0;
    else
        switch(moore_st) {
            case s0: z=1; moore_st = a ? s0 : s2; break;
            case s1: z=0; moore_st = a ? s0 : s2; break;
            case s2: z=0; moore_st = a ? s2 : s3; break;
            case s3: z=1; moore_st = a ? s1 : s3; break;
        }
} 