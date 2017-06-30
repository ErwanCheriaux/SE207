#ifndef FILTER_H 
#define FILTER_H 

#include <systemc.h>
#include "image.h"

/************************************************
 *  définition du module MOYENNEUR
 ***********************************************/
SC_MODULE(Moyenneur) {

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
   SC_CTOR(Moyenneur)
   {
      cout << "Instanciation de " << name() <<" ..." ;

      SC_THREAD(getImage);
      sensitive << clk.pos();
      async_reset_signal_is(reset_n,false);
      dont_initialize();

      reset_done = false;
      buffer     = (unsigned char *)malloc(720*3*sizeof(unsigned char));

      cout << "... réussie" << endl;
   }

   /***************************************************
    *  méthodes et champs internes
    **************************************************/
   private:

   void getImage();
   void moyenneur();

   const std::string base_name; // nom de base des images d'entrée
   bool  reset_done;
   int   cpt;
   int   delay;

   unsigned char *buffer;
};

/************************************************
 *  définition du module ZOOM
 ***********************************************/
SC_MODULE(Zoom) {

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
   SC_CTOR(Zoom)
   {
      cout << "Instanciation de " << name() <<" ..." ;

      SC_THREAD(getImage);
      sensitive << clk.pos();
      async_reset_signal_is(reset_n,false);
      dont_initialize();

      reset_done = false;
      buffer     = (unsigned char *)malloc(360*288*sizeof(unsigned char));

      cout << "... réussie" << endl;
   }

   /***************************************************
    *  méthodes et champs internes
    **************************************************/
   private:

   void getImage();
   void zoom();

   const std::string base_name; // nom de base des images d'entrée
   bool  reset_done;
   int   cpt;
   int   cpt_pixel;
   int   cpt_buffer;
   int   cpt_zoom;
   int   delay;

   unsigned char *buffer;
};

#endif
