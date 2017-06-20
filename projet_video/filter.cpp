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
      delay = 0;
      pixel_new = 0;
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
      wait();
      if(!reset_done)
         cerr << "module: " << name() << " démarré sans reset!" << endl;
      if(h_in)
      {
         // on attend le prochain coup d'horloge
         pixel_in[cpt_pixel_h*720+cpt_pixel_w] = p_in;
         pixel_new++;
         delay++;

         // On a fini une image, on passe à la suivante
         if(cpt_pixel_w++ > 720)
         {
            cpt_pixel_w = 0;
            if(cpt_pixel_h++ > 576)
            {
               cpt_pixel_h = 0;
               debugImageIN();
            }
         }
      }

      //application du filtre
      if(delay >= 721) median_filter();
      else
      {
         h_out = false;
         v_out = false;
      }
   }
}

/**************************
 *      FILTRE MEDIAN
 **************************/
void Filter::median_filter()
{
   //cpt_median
   if(cpt_median_w++ > 720)
   {
      cpt_median_w = 0;
      if(cpt_median_h++ > 576)
      {
         cpt_median_h = 0;
         debugImageOUT();
      }
   }

   //h_out et v_out
   h_out = (cpt_median_h<576) && (cpt_median_w<720);
   v_out = (cpt_median_h<3);

   if(cpt_median_h*720+cpt_median_w < 720*576-2) h_out = true;
   else                                          h_out = false;

   int tmp = 0;
   for(int i=0; i<3; i++)
   {
      for(int j=0; j<3; j++)
      {
         tmp += pixel_in[cpt_pixel_h*720+cpt_pixel_w];
         //cotés
         if(cpt_pixel_w > 0)   tmp += pixel_in[cpt_pixel_h*720+cpt_pixel_w-1];
         if(cpt_pixel_w < 576) tmp += pixel_in[cpt_pixel_h*720+cpt_pixel_w+1];
         if(cpt_pixel_h > 0)   tmp += pixel_in[(cpt_pixel_h-1)*720+cpt_pixel_w];
         if(cpt_pixel_h < 720) tmp += pixel_in[(cpt_pixel_h+1)*720+cpt_pixel_w];
         //diago
         if(cpt_pixel_w > 0   and cpt_pixel_h > 0)   tmp += pixel_in[(cpt_pixel_h-1)*720+cpt_pixel_w-1];
         if(cpt_pixel_w < 576 and cpt_pixel_h > 0)   tmp += pixel_in[(cpt_pixel_h-1)*720+cpt_pixel_w+1];
         if(cpt_pixel_w > 0   and cpt_pixel_h < 720) tmp += pixel_in[(cpt_pixel_h+1)*720+cpt_pixel_w-1];
         if(cpt_pixel_w < 576 and cpt_pixel_h < 720) tmp += pixel_in[(cpt_pixel_h+1)*720+cpt_pixel_w+1];
      }
   }

   p_out = pixel_out[cpt_median_h*720+cpt_median_w] = (unsigned char)tmp/9;
   
   if(delay <= 720*576+721) delay = 0;
   pixel_new--;
}

/**************************
 *        DEBUG
 **************************/
void Filter::debugImageIN()
{
   Image image;
   image.pixel  = pixel_in;
   image.width  = 720;
   image.height = 576;

   std::ostringstream name_s;

   // Calcul du nom de la prochaine image.
   name_s << "debug_in.png";

   // Lecture proprement dite de l'image PNG a l'aide de la libpng
   std::cout << " DEBUG : Ecriture de l'image " << name_s.str() << endl;
   image_write(&image, name_s.str().c_str());
}

void Filter::debugImageOUT()
{
   Image image;
   image.pixel  = pixel_out;
   image.width  = 720;
   image.height = 576;

   std::ostringstream name_s;

   // Calcul du nom de la prochaine image.
   name_s << "debug_out.png";

   // Lecture proprement dite de l'image PNG a l'aide de la libpng
   std::cout << " DEBUG : Ecriture de l'image " << name_s.str() << endl;
   image_write(&image, name_s.str().c_str());
}
