#include <cstdio>
#include <sstream>
#include <iomanip>
#include "filter.h"

/***************************************************************************
 *      SC_THREAD principale
 ***************************************************************************/
void Median::getImage()
{
   reset_done = false;
   if(reset_n == false)
   {
      cpt   = 0;
      delay = 720+1;
      h_out = false;
      v_out = false;
      cout << "module: " << name() << "... reset!" << endl;
      reset_done = true;
   }
   // boucle infinie
   while(1)
   {
      wait();
      if(!reset_done)
         cerr << "module: " << name() << " démarré sans reset!" << endl;
      if(h_in)
      {
         // on attend le prochain coup d'horloge
         buffer[cpt] = p_in;
         if(cpt++ >= 720*3-1) cpt = 0;

         //filtrage
         if(!delay) median();
         else       delay--;
      }
      //h_out et v_out
      if(!delay)
      {
         h_out = h_in;
         v_out = h_out;
      }
   }
}

/**************************
 *      FILTRE MEDIAN
 **************************/
void Median::median()
{
   int tmp = 0;
   int index = cpt%720;

   for(int i=0; i<3; i++)
      for(int j=0; j<3; j++)
         if(index-j >= 0)
            tmp += buffer[(index-j)+(720*i)];

   tmp = tmp/9;
   p_out = (unsigned char)tmp;
}
