//PGCD_method.cpp

#include <systemc.h>
#include <algorithm>

using namespace std;

void next_cycle(sc_signal<bool> &signal_clk);
void pulse(sc_signal<bool> &signal, sc_signal<bool> &clk);

// les modules
SC_MODULE(pgcd)
{
   sc_in<bool> clk;
   sc_in<bool> valid;
   sc_in<sc_uint<8>> A;
   sc_in<sc_uint<8>> B;

   sc_out<bool> ready;
   sc_out<sc_uint<8>> PGCD;

   bool calculMode = false;
   sc_uint<8> MAX, MIN;

   SC_CTOR(pgcd):clk("clk"), valid("valid"), A("A"), B("B"), ready("ready"), PGCD("PGCD")
   {
      SC_METHOD(calcule_pgcd);
      sensitive << clk.pos();
      dont_initialize();
   }

   void calcule_pgcd()
   {
      if(valid.read())
      {
         calculMode = true;
         ready      = false;
         MAX = max(A,B);
         MIN = min(A,B);
      }
      else if(calculMode and !ready and MIN>0)
      {
         MAX = MAX - MIN;
         sc_uint<8> tmp = max(MAX,MIN);
         MIN = min(MAX,MIN);
         MAX = tmp;
      }
      else if(calculMode and !ready and !(MIN>0))
      {
         calculMode = false;
         ready      = true;
         PGCD       = MAX;
      }
      else
      {
         ready = false;
      }
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
   trace_f = sc_create_vcd_trace_file("PGCD_method");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, clk, "clk");
   sc_trace(trace_f, valid, "valid");
   sc_trace(trace_f, A, "A");
   sc_trace(trace_f, B, "B");
   sc_trace(trace_f, ready, "ready");
   sc_trace(trace_f, PGCD, "PGCD");

   sc_start(SC_ZERO_TIME);
   next_cycle(clk);

   // affectation au signal
   A = 45;
   B = 95;
   pulse(valid, clk);
   while(!ready.read()) next_cycle(clk);
   while(ready.read())  next_cycle(clk);

   A = 100;
   B = 150;
   pulse(valid, clk);
   while(!ready.read()) next_cycle(clk);
   while(ready.read())  next_cycle(clk);

   //feinte
   A = 45;
   B = 9;
   for(int i=0; i<4; i++) next_cycle(clk);

   A = 222;
   B = 111;
   pulse(valid, clk);
   while(!ready.read()) next_cycle(clk);
   while(ready.read())  next_cycle(clk);

   A = 45;
   B = 9;
   pulse(valid, clk);
   while(!ready.read()) next_cycle(clk);
   while(ready.read())  next_cycle(clk);

   return 0;
}

void next_cycle(sc_signal<bool> &signal_clk)
{
   signal_clk = false;
   sc_start(1, SC_NS);
   signal_clk = true;
   sc_start(1, SC_NS);
}

void pulse(sc_signal<bool> &signal, sc_signal<bool> &clk)
{
   signal = true;
   next_cycle(clk);
   signal = false;
}
