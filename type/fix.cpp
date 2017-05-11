//fix.cpp

#define SC_INCLUDE_FX
#include <systemc.h>

double compare (double d1, double d2)
{
   double ds = d1 + d2;

   sc_fix f1(d1);
   sc_fix f2(d2);
   sc_fix fs = f1 + f2;

   return ds - fs;
}

int sc_main (int argc, char* argv[])
{
   double d1 = 0.1;
   double d2 = 0.9;

   // 1 bit pour la partie entière et 2 bits après la virgule
   sc_fxtype_params param1(3,1);

   // 1 bit pour la partie entière et 4 bits après la virgule
   sc_fxtype_params param2(5,1);

   // 1 bit pour la partie entière et 6 bits après la virgule
   sc_fxtype_params param3(7,1);

   sc_fxtype_context ctxt1(param1);
   cout << "Error  in context " << ctxt1.default_value()
        << " is " <<  compare(d1,d2) << endl;

   sc_fxtype_context ctxt2(param2);
   cout << "Error  in context " << ctxt1.default_value()
        << " is " <<  compare(d1,d2) << endl;

   sc_fxtype_context ctxt3(param3);
   cout << "Error  in context " << ctxt1.default_value()
        << " is " <<  compare(d1,d2) << endl;

   return 0;
}
