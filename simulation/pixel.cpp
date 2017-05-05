#include <systemc.h>

// un type utilisateur
struct pixel {
   int r, g, b;
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
   cout << "--> @ " << sc_time_stamp() << " P = " << P << endl;

   // affectation au signal
   P = pixel(33,22,11);
   cout << "--> @ " << sc_time_stamp() << " P = " << P << endl;

   sc_start(1,SC_NS);
   cout << "--> @ " << sc_time_stamp() << " P = " << P << endl;

   return 0;
}
