//entiers_taille_arbitraire.cpp

#include <systemc.h>

int sc_main (int argc, char * argv[])
{
   cout << "===Start vecteurs===" << endl;
 
   sc_int<8> a = 12;
   sc_int<8> b = sc_bv<8>(false);
   sc_int<8> c = sc_bv<8>("10100101"); 

   sc_uint<8> d = 42;
   sc_uint<8> e = sc_lv<8>(true); 
   sc_uint<8> f = sc_lv<8>("1x1y010x"); 

   sc_uint<10> g;

   cout << "===Initialisation===" << endl;
   cout << "a = " << a << endl;
   cout << "b = " << b << endl;
   cout << "c = " << c << endl;
   cout << "d = " << d << endl;
   cout << "e = " << e << endl;
   cout << "f = " << f << endl;

   cout << "===Operateur binaire===" << endl;
   g = a + b + c + d;
   cout << "g = a + b + c + d = "      << g << endl;
   g = (a + b) | (c - d);
   cout << "g = (a + b) | (c - d) = "  << g << endl;
   g = (a & b) >> (c - d);
   cout << "g = (a & b) >> (c - d) = " << g << endl;
   g = e * e - f / f;
   cout << "g = e * e - f / f = "      << g << endl;

   int           h = a.to_int();
   unsigned      i = b.to_uint();
   long          j = c.to_long();
   unsigned long k = d.to_ulong();

   cout << "===Convertion===" << endl;
   cout << "h = a.to_int() "   << h << endl;
   cout << "i = b.to_uint() "  << i << endl;
   cout << "j = c.to_long() "  << j << endl;
   cout << "k = d.to_ulong() " << k << endl;
   return 0;
} 
