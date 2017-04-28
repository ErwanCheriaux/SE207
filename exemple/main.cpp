//main.cpp

#include <systemc.h>

int sc_main (int argc, char * argv[])
{
   cout << "===Start example===" << endl;
   
   /*
    * sc_logic a(x);
    * <=>
    * sc_logic a = sc_logic(x)
    */

   sc_logic a(3);
   sc_logic b(false);
   sc_logic c('1');
   sc_logic d('Z');

   cout << "===Initialisation===" << endl;
   cout << "a = " << a << endl;
   cout << "b = " << b << endl;
   cout << "c = " << c << endl;
   cout << "d = " << d << endl;

   cout << "===Operateur binaire===" << endl;

   sc_logic e;

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
   
   

   return 0;
}
