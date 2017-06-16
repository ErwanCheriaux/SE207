#include <cstdio>
#include <sstream>
#include <iomanip>
#include "video_out.h"

/***************************************************************************
 *      SC_THREAD principale
 ***************************************************************************/
void VIDEO_OUT::read_port()
{
   reset_done = false;
   if(reset_n == false)
   {
      // Reset : on remet tous les paramètres à  zéro
      current_image_number = 0;
      cpt_pixel = 0;

      cout << "module: " << name() << "... reset!" << endl;
      reset_done = true;
   }
   // boucle infinie
   while(1)
   {
      if(!reset_done)
         cerr << "modul: " << name() << " démarré sans reset!" << endl;
      if(href and vref)
      {
         // on attend le prochain coup d'horloge
         wait();
         image.pixel[cpt_pixel] = pixel_in;

         if(++cpt_pixel > 720*576)
         {
            // On a fini une image, on passe à la suivante
            write_image();
            current_image_number++;
            cpt_pixel = 0;
         }
      }
   }
}

/***********************************************
 *  Ecriture des nouvelles images successives
 ***********************************************/

void VIDEO_OUT::write_image()
{
   std::ostringstream name_s;

   // Calcul du nom de la prochaine image.
   name_s << base_name << std::setfill('0') << std::setw(2) << current_image_number << ".png";

   // Lecture proprement dite de l'image PNG a l'aide de la libpng
   std::cout << name() << " Ecriture de l'image " << name_s.str() << endl;
   image_write(&image, name_s.str().c_str());
}
