//buffer.cpp

#include <systemc.h>

// les modules
SC_MODULE(module)
{
   sc_in <bool> buffer;
   sc_in <bool> signal;

   SC_CTOR(module):buffer("buffer"), signal("signal")
   {
      SC_METHOD(method);
      sensitive << buffer << signal;
      dont_initialize();
   }

   void method()
   {
      cout << "...NOTIFICATION !" << endl;
   }
};

// Le test
int sc_main (int argc, char * argv[])
{
   sc_buffer<bool> buffer;
   sc_signal<bool> signal;
   module myModule("myModule");

   myModule.buffer(buffer);
   myModule.signal(signal);

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("buffer");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, buffer, "buffer");
   sc_trace(trace_f, signal, "signal");

   buffer = false;
   signal = false;

   sc_start(10, SC_NS);

   cout << "Buffer = Buffer..." << endl;
   buffer = buffer;
   sc_start(1, SC_NS);

   cout << "Buffer = NOT(Buffer)..." << endl;
   buffer = !buffer;
   sc_start(1, SC_NS);

   cout << "Signal = Signal..." << endl;
   signal = signal;
   sc_start(1, SC_NS);

   cout << "Signal = NOT(Signal)..." << endl;
   signal = !signal;
   sc_start(1, SC_NS);

   sc_close_vcd_trace_file(trace_f);

   return 0;
}
