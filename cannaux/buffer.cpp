//buffer.cpp

#include <systemc.h>

// les modules
SC_MODULE(module)
{
   sc_in <bool> buffer;
   sc_in <bool> signal;
   sc_out<bool> out;

   SC_CTOR(module):buffer("buffer"), signal("signal"), out("out")
   {
      SC_METHOD(method);
      sensitive << buffer << signal;
      dont_initialize();
   }

   void method()
   {
      out = !out;
   }
};

// Le test
int sc_main (int argc, char * argv[])
{
   sc_buffer<bool> buffer;
   sc_signal<bool> signal;
   sc_signal<bool> out;
   module myModule("myModule");

   myModule.buffer(buffer);
   myModule.signal(signal);
   myModule.out(out);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("buffer");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, buffer, "buffer");
   sc_trace(trace_f, signal, "signal");
   sc_trace(trace_f, out,    "out");

   buffer = false;
   signal = false;

   sc_start(10, SC_NS);

   buffer = buffer;
   sc_start(1, SC_NS);
   buffer = buffer;
   sc_start(1, SC_NS);
   buffer = !buffer;
   sc_start(1, SC_NS);
   buffer = !buffer;
   sc_start(1, SC_NS);

   signal = signal;
   sc_start(1, SC_NS);
   signal = signal;
   sc_start(1, SC_NS);
   signal = !signal;
   sc_start(1, SC_NS);
   signal = !signal;
   sc_start(1, SC_NS);

   sc_close_vcd_trace_file(trace_f);

   return 0;
}
