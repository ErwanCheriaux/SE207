//vecteurs.cpp

#include <systemc.h>

int sc_main (int argc, char * argv[])
{
   cout << "===Start vecteurs===" << endl;
 
   sc_bv<8> a = false; 
   sc_bv<8> b = "10100101"; 

   sc_lv<8> c = sc_lv<8>(true); 
   sc_lv<8> d = "1x1y010x"; 

   sc_bv<10> e;

   cout << "===Initialisation===" << endl;
   cout << "a = " << a << endl;
   cout << "b = " << b << endl;
   cout << "c = " << c << endl;
   cout << "d = " << d << endl;

   cout << "===Operateur binaire===" << endl;
   e = a | b;
   cout << "e = a | b = " << e << endl;
   e = b | b;
   cout << "e = b | b = " << e << endl;
   e = c | b;
   cout << "e = c | b = " << e << endl;
   e = d | b;
   cout << "e = d | b = " << e << '\n' << endl;

   e = a & c;
   cout << "e = a & c = " << e << endl;
   e = b & c;
   cout << "e = b & c = " << e << endl;
   e = c & c;
   cout << "e = c & c = " << e << endl;
   e = d & c;
   cout << "e = d & c = " << e << '\n' << endl;

   e = a ^ c;
   cout << "e = a ^ c = " << e << endl;
   e = b ^ c;
   cout << "e = b ^ c = " << e << endl;
   e = c ^ c;
   cout << "e = c ^ c = " << e << endl;
   e = d ^ c;
   cout << "e = d ^ c = " << e << '\n' << endl;
   
   e = ~a;
   cout << "e = ~a = " << e << endl;
   e = ~b;
   cout << "e = ~b = " << e << endl;
   e = ~c;
   cout << "e = ~c = " << e << endl;
   e = ~d;
   cout << "e = ~d = " << e << '\n' << endl;

   e = a<<3;
   cout << "e = a<<3 = " << e << endl;
   e = b<<3;
   cout << "e = b<<3 = " << e << endl;
   e = c>>3;
   cout << "e = c>>3 = " << e << endl;
   e = d>>3;
   cout << "e = d>>3 = " << e << '\n' << endl;

   int           f = a.to_int();
   unsigned      g = b.to_uint();
   long          h = c.to_long();
   unsigned long i = d.to_ulong();

   cout << "===Convertion===" << endl;
   cout << "f = a.to_int() "   << f << endl;
   cout << "g = b.to_uint() "  << g << endl;
   cout << "h = c.to_long() "  << h << endl;
   cout << "i = d.to_ulong() " << i << endl;
   return 0;
} 
