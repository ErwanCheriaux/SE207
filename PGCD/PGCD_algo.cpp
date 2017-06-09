//PGCD_algo.cpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdint>
#include <algorithm>

using namespace std;

unsigned int pgcd(unsigned int a, unsigned int b)
{
   unsigned int MAX = max(a,b);
   unsigned int MIN = min(a,b);

   while(MAX > 0 and MIN >0)
   {
      MAX = MAX - MIN;

      unsigned int tmp = max(MAX,MIN);

      MIN = min(MAX,MIN);
      MAX = tmp;
   }

   return MAX;
}

int main(void)
{
   cout << "pgcd entre 45 et 95   : " << pgcd(45, 95) << endl;
   cout << "pgcd entre 100 et 150 : " << pgcd(100, 150) << endl;
   cout << "pgcd entre 222 et 111 : " << pgcd(222, 111) << endl;
   cout << "pgcd entre 45 et 9    : " << pgcd(45, 9) << endl;
   return 0;
}
