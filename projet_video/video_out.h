#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include <systemc.h>
#include "image.h"

/***************************************
 *  définition du module
 **************************************/
SC_MODULE(VIDEO_OUT) {

   // IO PORTS
   sc_in<bool> clk;
   sc_in<bool> reset_n;

   sc_in<bool> href;
   sc_in<bool> vref;

   sc_in<unsigned char> pixel_in;

   /***************************************************
    *  constructeur
    **************************************************/
   SC_CTOR(VIDEO_OUT):base_name("wallace_out_")
   {
      cout << "Instanciation de " << name() <<" ..." ;

      SC_THREAD(read_port);
      sensitive << clk.pos();
      async_reset_signal_is(reset_n,false);
      dont_initialize();

      current_image_number = 0;
      reset_done  = false;
      image.pixel = (unsigned char *)malloc(720*576*sizeof(unsigned char));
      image.width  = 720;
      image.height = 576;

      cout << "... réussie" << endl;
   }

   /***************************************************
    *  méthodes et champs internes
    **************************************************/
   private:

   void read_port();
   void write_image();

   const std::string base_name;  // nom de base des images d'entrée
   int   current_image_number;   // numéro de l'image courante
   int   cpt_pixel;
   bool  reset_done;

   Image image;
};

#endif

