//fixed.cpp

#define SC_INCLUDE_FX
#include <systemc.h>

// 1 bit pour la partie entière et 2 bits après la virgule

#define WL  3
#define IWL 1

int sc_main (int argc, char* argv[])
{
   double d1 = 0.1;
   double d2 = 0.9;
   double ds = d1 + d2;

   sc_fixed<WL,IWL> f1(d1);
   sc_fixed<WL,IWL> f2 = d2;
   sc_fixed<WL,IWL> fs = f1 + f2;

   double e = ds - double(fs);

   cout << "Double " << ds  << endl
        << "Fixed  " << fs  << endl
        << "Error  " << e   << endl;

   return 0;
}
