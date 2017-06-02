//PGCD_thread.cpp

#include <systemc.h>

unsigned int pgcd_algo(unsigned int a, unsigned int b);
void next_cycle(sc_signal<bool> &signal_clk);

// les modules
SC_MODULE(pgcd)
{
   sc_in<bool> clk;
   sc_in<bool> valid;
   sc_in<sc_uint<8>> A;
   sc_in<sc_uint<8>> B;

   sc_out<bool> ready;
   sc_out<sc_uint<8>> PGCD;

   SC_CTOR(pgcd):clk("clk"), valid("valid"), A("A"), B("B"), ready("ready"), PGCD("PGCD")
   {
      SC_THREAD(calcule_pgcd);
      sensitive << clk.pos();
   }

   void calcule_pgcd()
   {
      PGCD.write(pgcd_algo(A,B));
   }
};

// Le test
int sc_main (int argc, char * argv[])
{
   sc_signal<bool> clk;
   sc_signal<bool> valid;
   sc_signal<sc_uint<8>> A;
   sc_signal<sc_uint<8>> B;
   sc_signal<bool> ready;
   sc_signal<sc_uint<8>> PGCD;

   pgcd myPGCD("myPGCD");

   myPGCD.clk(clk);
   myPGCD.valid(valid);
   myPGCD.A(A);
   myPGCD.B(B);
   myPGCD.ready(ready);
   myPGCD.PGCD(PGCD);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("PGCD_thread");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, clk, "clk");
   sc_trace(trace_f, valid, "valid");
   sc_trace(trace_f, A, "A");
   sc_trace(trace_f, B, "B");
   sc_trace(trace_f, ready, "ready");
   sc_trace(trace_f, PGCD, "PGCD");

   // affectation au signal
   A = 45;
   B = 95;
   for(int i=0; i<50; i++) next_cycle(clk);
   sc_start(1,SC_NS);
   return 0;
}

unsigned int pgcd_algo(unsigned int a, unsigned int b)
{
   unsigned int MAX = max(a,b);
   unsigned int MIN = min(a,b);

   while(MAX > 0 and MIN >0)
   {
      MAX = MAX - MIN;

      unsigned int tmp = max(MAX,MIN);

      MIN = min(MAX,MIN);
      MAX = tmp;
   }

   return MAX;
}

void next_cycle(sc_signal<bool> &signal_clk)
{
   signal_clk = false;
   sc_start(1, SC_NS);
   signal_clk = true;
   sc_start(1, SC_NS);
}
