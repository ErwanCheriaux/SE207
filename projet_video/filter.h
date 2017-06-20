#ifndef FILTER_H 
#define FILTER_H 

#include <systemc.h>
#include "image.h"

/***************************************
 *  définition du module
 **************************************/
SC_MODULE(Filter) {

   // IO PORTS
   sc_in<bool> clk;
   sc_in<bool> reset_n;

   sc_in<bool> h_in;
   sc_in<bool> v_in;
   sc_in<unsigned char> p_in;

   sc_out<bool> h_out;
   sc_out<bool> v_out;
   sc_out<unsigned char> p_out;

   /***************************************************
    *  constructeur
    **************************************************/
   SC_CTOR(Filter)
   {
      cout << "Instanciation de " << name() <<" ..." ;

      SC_THREAD(getImage);
      sensitive << clk.pos();
      async_reset_signal_is(reset_n,false);
      dont_initialize();

      reset_done = false;
      pixel_in   = (unsigned char *)malloc(720*576*sizeof(unsigned char));
      pixel_out  = (unsigned char *)malloc(720*576*sizeof(unsigned char));

      cout << "... réussie" << endl;
   }

   /***************************************************
    *  méthodes et champs internes
    **************************************************/
   private:

   void getImage();
   void median_filter();

   void debugImageIN();
   void debugImageOUT();

   const std::string base_name; // nom de base des images d'entrée
   bool  reset_done;
   int   cpt_pixel_w;
   int   cpt_pixel_h;
   int   cpt_median_w;
   int   cpt_median_h;
   unsigned char *pixel_in;
   unsigned char *pixel_out;
   int   delay;
   int   pixel_new;
};

#endif
