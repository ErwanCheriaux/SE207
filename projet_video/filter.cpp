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
      if(h_in)
      {
         // on attend le prochain coup d'horloge
         pixel_in[cpt_pixel_h*720+cpt_pixel_w] = p_in;

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
   //cpt_median
   if(cpt_pixel_h == 0) cpt_median_h = 576-1;
   else                 cpt_median_h = cpt_pixel_h-1;

   if(cpt_pixel_w == 0) cpt_median_w = 720-1;
   else                 cpt_median_w = cpt_pixel_w-1;

   //h_out et v_out
   if(cpt_median_h == 0) v_out = true;
   else                  v_out = false;

   if(cpt_median_h*720+cpt_median_w < 720*576-2) h_out = true;
   else                                          h_out = false;

   pixel_out = 0;
   for(int i=0; i<3; i++)
   {
      for(int j=0; j<3; j++)
      {
         pixel_out += pixel_in[cpt_pixel_h*720+cpt_pixel_w];
         //cotés
         if(cpt_pixel_w > 0)   pixel_out += pixel_in[cpt_pixel_h*720+cpt_pixel_w-1];
         if(cpt_pixel_w < 576) pixel_out += pixel_in[cpt_pixel_h*720+cpt_pixel_w+1];
         if(cpt_pixel_h > 0)   pixel_out += pixel_in[(cpt_pixel_h-1)*720+cpt_pixel_w];
         if(cpt_pixel_h < 720) pixel_out += pixel_in[(cpt_pixel_h+1)*720+cpt_pixel_w];
         //diago
         if(cpt_pixel_w > 0   and cpt_pixel_h > 0)   pixel_out += pixel_in[(cpt_pixel_h-1)*720+cpt_pixel_w-1];
         if(cpt_pixel_w < 576 and cpt_pixel_h > 0)   pixel_out += pixel_in[(cpt_pixel_h-1)*720+cpt_pixel_w+1];
         if(cpt_pixel_w > 0   and cpt_pixel_h < 720) pixel_out += pixel_in[(cpt_pixel_h+1)*720+cpt_pixel_w-1];
         if(cpt_pixel_w < 576 and cpt_pixel_h < 720) pixel_out += pixel_in[(cpt_pixel_h+1)*720+cpt_pixel_w+1];
      }
   }

   p_out = (unsigned char)pixel_out/9;
}
