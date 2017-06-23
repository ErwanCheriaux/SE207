#include <cstdio>
#include <sstream>
#include <iomanip>
#include "filter.h"

/***************************************************************************
 *      SC_THREAD principale
 ***************************************************************************/
void Filter::getImage()
{
   reset_done = false;
   if(reset_n == false)
   {
      delay = 720+1;
      cpt_pixel = 0;
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
         pixel_in[cpt_pixel] = p_in;
         if(cpt_pixel++ >= 720*3-1) cpt_pixel = 0;

         //filtrage
         if(!delay) median_filter();
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
void Filter::median_filter()
{
   int tmp = 0;
   int index = cpt_pixel%720;

   for(int i=0; i<3; i++)
      for(int j=0; j<3; j++)
         if(index-j >= 0)
            tmp += pixel_in[(index-j)+(720*i)];

   tmp = tmp/9;
   p_out = (unsigned char)tmp;
}
