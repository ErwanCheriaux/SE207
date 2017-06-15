//fifo_method.cpp

#include <systemc.h>
#include <cstdlib>
#include "pixel.h"

void next_cycle(sc_signal<bool> &signal_clk);

SC_MODULE(producteur)
{
   sc_in<bool> clk;
   sc_in<bool> rst;
   sc_fifo_out<pixel> out;

   //true  = production des 20 pixels
   //false = attente aléatoire
   bool etat;
   int  cpt;

   SC_CTOR(producteur):clk("clk"), rst("rst"), out("out")
   {
      SC_METHOD(production);
      sensitive << clk.pos();
      async_reset_signal_is(rst,true);
      dont_initialize();
   }

   void production()
   {
      if(rst)
      {
         etat = true;
         cpt  = 20;
      }
      else
      {
         if(etat)
         {
            out.write(pixel(rand(),rand(),rand()));
            if(cpt-- == 0)
            {
               cpt  = rand()%33;
               etat = !etat;
            }
         }
         else
         {
            if(cpt-- == 0)
            {
               cpt  = 20;
               etat = !etat;
            }
         }
      }
   }
};

SC_MODULE(consomateur)
{
   sc_in<bool> clk;
   sc_in<bool> rst;
   sc_fifo_in<pixel> in;

   int cpt;

   SC_CTOR(consomateur):clk("clk"), rst("rst"), in("in")
   {
      SC_METHOD(consomation);
      sensitive << clk.pos();
      async_reset_signal_is(rst,true);
      dont_initialize();
   }

   void consomation()
   {
      if(rst) cpt = 0;
      else    if(cpt-- == 0) cpt = in.read().sum()%2+2;
   }
};

int sc_main (int argc, char * argv[])
{
   sc_signal<bool> clk;
   sc_signal<bool> rst;
   sc_fifo<pixel> fifo(50);

   producteur  P("producteur");
   consomateur C("consomateur");

   P.out(fifo);
   P.clk(clk);
   P.clk(rst);
   C.in(fifo);
   C.clk(clk);
   C.clk(rst);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("fifo");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, clk,  "clk");
   sc_trace(trace_f, rst,  "rst");
   sc_trace(trace_f, fifo, "fifo");

   rst = true;
   sc_start(SC_ZERO_TIME);
   for(int i=0; i<5  ; i++) next_cycle(clk);
   rst = false;
   for(int i=0; i<500; i++) next_cycle(clk);

   return 0;
}

void next_cycle(sc_signal<bool> &signal_clk)
{
   signal_clk = false;
   sc_start(1, SC_NS);
   signal_clk = true;
   sc_start(1, SC_NS);
}
