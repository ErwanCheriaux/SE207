//colors_methode.cpp

#include <systemc.h>
#include "pixel.h"

// les modules
SC_MODULE(colors)
{
   sc_in <bool>  clk;
   sc_in <bool>  rst;
   sc_out<pixel> p;

   int r, g, b;

   SC_CTOR(colors):clk("clk"), rst("rst"), p("p")
   {
      SC_METHOD(all_colors);
      sensitive << clk.pos();
      async_reset_signal_is(rst,true);
      dont_initialize();
   }

   void all_colors()
   {
      if(rst)
      {
         r=0;
         g=0;
         b=0;
      }
      else
      {
         if(r++ > 31)
         {
            r=0;
            if(g++ > 63)
            {
               g=0;
               if(b++ > 31) b=0;
            }
         }
      }

      p.write(pixel(r,g,b));
   }
};

void next_cycle(sc_signal<bool> &signal_clk)
{
   signal_clk = false;
   sc_start(1, SC_NS);
   signal_clk = true;
   sc_start(1, SC_NS);
}

// Le test
int sc_main (int argc, char * argv[])
{
   sc_signal<bool>  clk;
   sc_signal<bool>  rst;
   sc_signal<pixel> P_output;
   colors myColors("myColors");

   myColors.clk(clk);
   myColors.rst(rst);
   myColors.p(P_output);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("colors_methode");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, clk,      "Horloge");
   sc_trace(trace_f, rst,      "Reset");
   sc_trace(trace_f, P_output, "pixel_output");

   rst = true;
   sc_start(10,SC_NS);
   rst = false;

   for(int i=0; i<50; i++) next_cycle(clk);
   rst = true;
   
   for(int i=0; i<5; i++) next_cycle(clk);
   rst = false;
   
   for(int i=0; i<500000; i++) next_cycle(clk);

   sc_close_vcd_trace_file(trace_f);

   return 0;
}
