//pixel.cpp

#include <systemc.h>

// un type utilisateur
struct pixel
{
   sc_uint<5> r;
   sc_uint<6> g;
   sc_uint<5> b;
   // un constructeur particulier avec des valeurs par défaut
   pixel(int _r=0, int _g=0, int _b=0): r(_r), g(_g), b(_b) { }

   bool operator == (const pixel &other)
   {
      return (r == other.r) && (g == other.g) && (b == other.b);
   }

   friend pixel operator + (const pixel &p1, const pixel &p2)
   {  
      unsigned int r_sat = p1.r.to_int() + p2.r.to_int();
      unsigned int g_sat = p1.g.to_int() + p2.g.to_int();
      unsigned int b_sat = p1.b.to_int() + p2.b.to_int();

      if(r_sat > 31) r_sat = 31;
      if(g_sat > 63) g_sat = 63;
      if(b_sat > 31) b_sat = 31;
   
      return pixel(r_sat, g_sat, b_sat);
   }

   // On doit pouvoir imprimer la valeur d'un objet de ce type
   // l'opérateur << est un opérateur de la classe std::ostream
   friend ostream& operator << (ostream& o, const pixel& P)
   {
      o << "{" << P.r << "," << P.g << "," << P.b << "}" ;
      return o;
   }
};

// surcharge de la fonction sc_trace pour le type utilisateur
void sc_trace( sc_trace_file* _f, const pixel& _foo, const std::string& _s ) {
   sc_trace( _f, _foo.r, _s + "_r" );
   sc_trace( _f, _foo.g, _s + "_g" );
   sc_trace( _f, _foo.b, _s + "_b" );
}

// les modules
SC_MODULE(somme)
{
   sc_in <pixel> p1;
   sc_in <pixel> p2;
   sc_out<pixel> p;

   SC_CTOR(somme)
   {
      SC_METHOD(sommeSature);
      sensitive << p1 << p2;
      dont_initialize();
   }

   void sommeSature()
   {
      p.write(p1.read() + p2.read());
   }
};

// Le test
int sc_main (int argc, char * argv[])
{
   sc_signal<pixel> P;

   // trace VCD
   sc_trace_file *trace_f;
   trace_f = sc_create_vcd_trace_file ("pixel");
   trace_f->set_time_unit(1,SC_NS);
   sc_trace(trace_f, P, "pixel");

   // affectation au signal
   for(int r=0; r<70; r++) {
      for(int g=0; g<70; g++) {
         for(int b=0; b<70; b++) {
            P = pixel(r,g,b);
            sc_start(1,SC_NS);
         }
      }
   }

   return 0;
}
