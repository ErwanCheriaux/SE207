//fifo.cpp

#include <systemc.h>
#include <cstdlib>

void next_cycle(sc_signal<bool> &signal_clk);

SC_MODULE(producteur)
{
   sc_in<bool> clk;
   sc_fifo_out<int> out;

   //true  = production des 20 pixels
   //false = attente aléatoire
   bool etat;
   int  cpt;

   SC_CTOR(producteur):clk("clk"), out("out")
   {
      SC_THREAD(production);
      sensitive << clk.pos();
   }

   void production()
   {
      etat = true;
      cpt  = 20;
      while(1)
      {
         wait();
         if(etat)
         {
            out.write(cpt);
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
   sc_fifo_in<int> in;

   int cpt;

   SC_CTOR(consomateur):clk("clk"), in("in")
   {
      SC_THREAD(consomation);
      sensitive << clk.pos();
   }

   void consomation()
   {
      cpt = 0;
      while(1)
      {
         wait();
         if(cpt-- == 0) cpt = in.read()%2+2;
      }
   }
};

int sc_main (int argc, char * argv[])
{
   sc_signal<bool> clk;
   sc_fifo<int> fifo(50);

   producteur  P("producteur");
   consomateur C("consomateur");

   P.out(fifo);
   P.clk(clk);
   C.in(fifo);
   C.clk(clk);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("fifo");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, clk, "clk");
   sc_trace(trace_f, fifo, "fifo");

   sc_start(SC_ZERO_TIME);
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
