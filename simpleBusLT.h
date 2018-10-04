#ifndef __SIMPLEBUSLT_H__
#define __SIMPLEBUSLT_H__

//#include <systemc>
#include "tlm.h"

#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

using namespace std;

template <int NR_OF_INITIATORS, int NR_OF_TARGETS>
class SimpleBusLT : public sc_core::sc_module
{
public:
  typedef tlm::tlm_generic_payload                 transaction_type;
  typedef tlm::tlm_phase                           phase_type;
  typedef tlm::tlm_sync_enum                       sync_enum_type;
  typedef tlm_utils::simple_target_socket_tagged<SimpleBusLT,64,tlm::tlm_base_protocol_types>    target_socket_type;
  typedef tlm_utils::simple_initiator_socket_tagged<SimpleBusLT,64,tlm::tlm_base_protocol_types> initiator_socket_type;

public:
  target_socket_type target_socket[NR_OF_INITIATORS];
  initiator_socket_type initiator_socket[NR_OF_TARGETS];
  sc_dt::uint64  addr;    	  
  sc_dt::uint64  addr1;  
  int counter =2;
  bool time = true;	
  bool m_initialized[4];
  sc_dt::uint64 m_memory_size,m_last_addr[4];
	

public:
  SC_HAS_PROCESS(SimpleBusLT);
  SimpleBusLT(sc_core::sc_module_name name) :
    sc_core::sc_module(name)
  {
    for (unsigned int i = 0; i < NR_OF_INITIATORS; ++i) {
      target_socket[i].register_b_transport(this, &SimpleBusLT::initiatorBTransport, i);
      target_socket[i].register_transport_dbg(this, &SimpleBusLT::transportDebug, i);
      target_socket[i].register_get_direct_mem_ptr(this, &SimpleBusLT::getDMIPointer, i);
    }
    for (unsigned int i = 0; i < NR_OF_TARGETS; ++i) {
      initiator_socket[i].register_invalidate_direct_mem_ptr(this, &SimpleBusLT::invalidateDMIPointers, i);
    }	
  }

  //
  // Dummy decoder:
  // - address[31-28]: portId
  // - address[27-0]: masked address
  //

  unsigned int getPortId(const sc_dt::uint64& address)
  {
    return (unsigned int)address >> 28;
  }

  sc_dt::uint64 getAddressOffset(unsigned int portId)
  {
    return portId << 28;
  }

  sc_dt::uint64 getAddressMask(unsigned int portId)
  {
    return 0xfffffff;
  }

  unsigned int decode(const sc_dt::uint64& address)
  {
    // decode address:
    // - return initiator socket id

    return getPortId(address);
  }

  //
  // interface methods
  //

  //
  // LT protocol
  // - forward each call to the target/initiator
  //
  void initiatorBTransport(int SocketId,
                           transaction_type& trans,
                           sc_core::sc_time& t)
  {
    
    if(time){
    wait(1995,sc_core::SC_NS);	
	time = false;
	}
    initiator_socket_type* decodeSocket = &initiator_socket[0];
    //unsigned int portId = decode(trans.get_address());
    unsigned  int     length   = trans.get_data_length();
    unsigned char    *data     = trans.get_data_ptr();	
    sc_dt::uint64  address = trans.get_address();
    t = sc_core::SC_ZERO_TIME;
    sc_core::sc_time mem_delay(10,sc_core::SC_NS);	
    unsigned long last_burst_length,bank;
    tlm::tlm_command command   = trans.get_command();
    string cmd;

    switch (command) {
      case tlm::TLM_WRITE_COMMAND:
	{
	cmd = " WRITE";
	break;
	}
      case tlm::TLM_READ_COMMAND:
	cmd =" READ";
	break;
	}
     	  
      mem_delay = sc_core::sc_time(20*length,sc_core::SC_NS);
		
	      
     //assert(portId < NR_OF_TARGETS);
    trans.set_address(trans.get_address());
     //wait(10,sc_core::SC_NS);
    cout << sc_core::sc_time_stamp() << " " << sc_object::name()
         << cmd<<" addr=0x" << hex << address << " size=0x" << length << " data=0x";


int i = length-1;
while(i>=0)  {
	   cout.width(2);
           cout.fill('0');
           cout<<hex << (unsigned)data[i];
           i--;
}
cout<<endl;


if(address != 0x40000010 && address != 0x40000060 &&address != 0x40000090){
 (*decodeSocket)->b_transport(trans, t); 
wait(mem_delay);
}

else if(counter==2 && address==0x40000090){
counter--;

addr = 0x00000040;
addr1 = 0x00004000;
for(int j = 0; j<15;j++){
trans.set_address(addr);
trans.set_command(tlm::TLM_READ_COMMAND);
 (*decodeSocket)->b_transport(trans, t);
wait(10,sc_core::SC_NS);
addr +=0x04; 
trans.set_address(addr1);
addr1+=0x04;
trans.set_command(tlm::TLM_WRITE_COMMAND);
(*decodeSocket)->b_transport(trans, t);
wait(100,sc_core::SC_NS);



}
}


else if(counter ==1 && address==0x40000090){
addr = 0x00000010;
addr1 = 0x00001000;
counter--;
for(int k = 0; k<8;k++){
trans.set_address(addr);
addr +=0x04; 
trans.set_command(tlm::TLM_READ_COMMAND);
(*decodeSocket)->b_transport(trans, t);
wait(10,sc_core::SC_NS);
trans.set_address(addr1);
addr1+=0x04;
trans.set_command(tlm::TLM_WRITE_COMMAND);
(*decodeSocket)->b_transport(trans, t);
wait(100,sc_core::SC_NS);

}
}





 
}





  unsigned int transportDebug(int SocketId,
                              transaction_type& trans)
  {
    unsigned int portId = decode(trans.get_address());
    assert(portId < NR_OF_TARGETS);
    initiator_socket_type* decodeSocket = &initiator_socket[portId];
    trans.set_address( trans.get_address() & getAddressMask(portId) );
    
    return (*decodeSocket)->transport_dbg(trans);
  }

  bool limitRange(unsigned int portId, sc_dt::uint64& low, sc_dt::uint64& high)
  {
    sc_dt::uint64 addressOffset = getAddressOffset(portId);
    sc_dt::uint64 addressMask = getAddressMask(portId);

    if (low > addressMask) {
      // Range does not overlap with addressrange for this target
      return false;
    }

    low += addressOffset;
    if (high > addressMask) {
      high = addressOffset + addressMask;

    } else {
      high += addressOffset;
    }
    return true;
  }

  bool getDMIPointer(int SocketId,
                     transaction_type& trans,
                     tlm::tlm_dmi&  dmi_data)
  {
    sc_dt::uint64 address = trans.get_address();

    unsigned int portId = decode(address);
    assert(portId < NR_OF_TARGETS);
    initiator_socket_type* decodeSocket = &initiator_socket[portId];
    sc_dt::uint64 maskedAddress = address & getAddressMask(portId);

    trans.set_address(maskedAddress);

    bool result =
      (*decodeSocket)->get_direct_mem_ptr(trans, dmi_data);
    
    if (result)
    {
      // Range must contain address
      assert(dmi_data.get_start_address() <= maskedAddress);
      assert(dmi_data.get_end_address() >= maskedAddress);
    }
    
    // Should always succeed
	sc_dt::uint64 start, end;
	start = dmi_data.get_start_address();
	end = dmi_data.get_end_address();
	
	limitRange(portId, start, end);
	
	dmi_data.set_start_address(start);
	dmi_data.set_end_address(end);

    return result;
  }

  void invalidateDMIPointers(int port_id,
                             sc_dt::uint64 start_range,
                             sc_dt::uint64 end_range)
  {
    // FIXME: probably faster to always invalidate everything?

    if (!limitRange(port_id, start_range, end_range)) {
      // Range does not fall into address range of target
      return;
    }
    
    for (unsigned int i = 0; i < NR_OF_INITIATORS; ++i) {
      (target_socket[i])->invalidate_direct_mem_ptr(start_range, end_range);
    }
  }

};

#endif
