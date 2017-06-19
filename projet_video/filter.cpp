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
      cpt_pixel_w  = 0;
      cpt_pixel_h  = 0;
      h_out = false;
      v_out = false;
      cout << "module: " << name() << "... reset!" << endl;
      reset_done = true;
   }
   // boucle infinie
   while(1)
   {
      if(!reset_done)
         cerr << "module: " << name() << " démarré sans reset!" << endl;
      if(href)
      {
         // on attend le prochain coup d'horloge
         pixel[cpt_pixel_h*720+cpt_pixel_w] = p_in;

         // On a fini une image, on passe à la suivante
         if(cpt_pixel_w++ > 720)
         {
            cpt_pixel_w = 0;
            if(cpt_pixel_h++ > 576) cpt_pixel_h = 0;
         }
      }

      //application du filtre
      median_filter();
   }
}

/**************************
 *      FILTRE MEDIAN
 **************************/
void Filter::median_filter()
{
   if(cpt_pixel_h == 0) cpt_median_h = 576-1;
   else                 cpt_median_h = cpt_pixel_h-1;

   if(cpt_pixel_w == 0) cpt_median_w = 720-1;
   else                 cpt_median_w = cpt_pixel_w-1;

}
