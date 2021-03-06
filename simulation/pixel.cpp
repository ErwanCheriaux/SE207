//pixel.cpp

#include <systemc.h>

// un type utilisateur
struct pixel {
   sc_uint<5> r;
   sc_uint<6> g;
   sc_uint<5> b;
   // un constructeur particulier avec des valeurs par défaut
   pixel(int _r=0, int _g=0, int _b=0): r(_r), g(_g), b(_b) { }

   bool operator == (const pixel &other) {
      return (r == other.r) && (g == other.g) && (b == other.b);
   }
   // On doit pouvoir imprimer la valeur d'un objet de ce type
   // l'opérateur << est un opérateur de la classe std::ostream
   friend ostream& operator << ( ostream& o, const pixel& P ) {
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
