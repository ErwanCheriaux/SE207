//somme_thread.cpp

#include <systemc.h>
#include "pixel.h"

// les modules
SC_MODULE(somme)
{
   sc_in <pixel> p1;
   sc_in <pixel> p2;
   sc_out<pixel> p;

   SC_CTOR(somme):p1("p1"), p2("p2"), p("p")
   {
      SC_THREAD(sommeSature);
   }

   void sommeSature()
   {
      while(1)
      {
         wait(100, SC_NS);
         p.write(p1.read() + p2.read());
      }
   }
};

// Le test
int sc_main (int argc, char * argv[])
{
   sc_signal<pixel> P_input;
   sc_signal<pixel> P_output;
   somme mySomme("mySomme");

   mySomme.p1(P_input);
   mySomme.p2(P_input);
   mySomme.p(P_output);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("somme_thread");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, P_input, "pixel_input1");
   sc_trace(trace_f, P_input, "pixel_input2");
   sc_trace(trace_f, P_output, "pixel_output");

   // affectation au signal
   for(int r=0; r<70; r++) {
      for(int g=0; g<70; g++) {
         for(int b=0; b<70; b++) {
            P_input = pixel(r,g,b);
            sc_start(1,SC_NS);
         }
      }
   }
   return 0;
}
