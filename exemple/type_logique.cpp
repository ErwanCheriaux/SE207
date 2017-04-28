//type_logique.cpp

#include <systemc.h>

int sc_main (int argc, char * argv[])
{
   cout << "===Start type_logique===" << endl;
   
   /*
    * sc_logic a(x);
    * <=>
    * sc_logic a = sc_logic(x)
    */

   sc_logic a(3);
   sc_logic b(false);
   sc_logic c('1');
   sc_logic d('Z');
   sc_logic e;

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
   
   cout << "===Operateur binaire avec Bool===" << endl;
   e = a | false;
   cout << "e = a | false = " << e << endl;
   e = b | false;
   cout << "e = b | false = " << e << endl;
   e = c | false;
   cout << "e = c | false = " << e << endl;
   e = d | false;
   cout << "e = d | false = " << e << '\n' << endl;

   e = a & true;
   cout << "e = a & true = " << e << endl;
   e = b & true;
   cout << "e = b & true = " << e << endl;
   e = c & true;
   cout << "e = c & true = " << e << endl;
   e = d & true;
   cout << "e = d & true = " << e << '\n' << endl;

   e = a ^ true;
   cout << "e = a ^ true = " << e << endl;
   e = b ^ true;
   cout << "e = b ^ true = " << e << endl;
   e = c ^ true;
   cout << "e = c ^ true = " << e << endl;
   e = d ^ true;
   cout << "e = d ^ true = " << e << '\n' << endl;
   
   return 0;
}
