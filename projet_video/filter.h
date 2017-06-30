#ifndef FILTER_H 
#define FILTER_H 

#include <systemc.h>
#include "image.h"

/************************************************
 *  définition du module MEDIAN
 ***********************************************/
SC_MODULE(Median) {

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
   SC_HAS_PROCESS(Median);

   Median(sc_module_name n, std::string filter_type) :sc_module(n)
   {
      cout << "Instanciation de " << name() <<" ..." ;

      SC_THREAD(getImage);
      sensitive << clk.pos();
      async_reset_signal_is(reset_n,false);
      dont_initialize();

      reset_done = false;

      if(filter_type == "sobel")
      {
         filter[0][0] = 1; filter[0][1] = 0; filter[0][2] =-1;
         filter[1][0] = 2; filter[1][1] = 0; filter[1][2] =-2;
         filter[2][0] = 1; filter[2][1] = 0; filter[2][2] =-1;
      }
      else if(filter_type == "moyenneur")
      {  
         filter[0][0] = 1; filter[0][1] = 1; filter[0][2] = 1;
         filter[1][0] = 1; filter[1][1] = 1; filter[1][2] = 1;
         filter[2][0] = 1; filter[2][1] = 1; filter[2][2] = 1;
      }
      else
      {
         filter[0][0] = 0; filter[0][1] = 0; filter[0][2] = 0;
         filter[1][0] = 0; filter[1][1] = 1; filter[1][2] = 0;
         filter[2][0] = 0; filter[2][1] = 0; filter[2][2] = 0;
      }

      buffer     = (unsigned char *)malloc(720*3*sizeof(unsigned char));

      cout << "... réussie" << endl;
   }

   /***************************************************
    *  méthodes et champs internes
    **************************************************/
   private:

   void getImage();
   void median();

   const std::string base_name; // nom de base des images d'entrée
   bool  reset_done;
   int   cpt;
   int   delay;

   int filter[3][3];

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
