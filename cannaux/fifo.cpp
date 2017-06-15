//fifo.cpp

#include <systemc.h>

SC_MODULE(producteur)
{
   sc_signal<bool> clk;
   sc_fifo_in<int> in;

   SC_CTOR(producteur):clk("clk"), in("in")
   {
      SC_THREAD(production);
      sensitive << clk.pos();
   }

   void production()
   {
      while(1)
      {
         wait();
      }
   }
}

SC_MODULE(consomateur)
{
   sc_signal<bool> clk;
   sc_fifo_out<int> out;

   SC_CTOR(consomateur):clk("clk"), out("out")
   {
      SC_THREAD(consomation);
      sensitive << clk.pos();
   }

   void consomation()
   {
      while(1)
      {
         wait();
      }
   }
}

int sc_main (int argc, char * argv[])
{
   sc_signal<bool> clk;
   sc_fifo<int> fifo(50);

   producteur  P("producteur");
   consomateur C("consomateur");

   P.in(fifo);
   P.clk(clk);
   C.out(fifo);
   C.clk(clk);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("buffer");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, clk, "clk");
   sc_trace(trace_f, fifo, "fifo");

   return 0;
}
