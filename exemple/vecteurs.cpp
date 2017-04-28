//vecteurs.cpp

#include <systemc.h>

int sc_main (int argc, char * argv[])
{
   cout << "===Start vecteurs===" << endl;
 
   sc_bv<8> a = false; 
   sc_bv<8> b = "10100101"; 

   sc_lv<8> c = true; 
   sc_lv<8> d = "11110000"; 

   cout << "===Initialisation===" << endl;
   cout << "a = " << a << endl;
   cout << "b = " << b << endl;
   cout << "c = " << c << endl;
   cout << "d = " << d << endl;

   return 0;
} 
