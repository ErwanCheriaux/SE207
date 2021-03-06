#include <cstdio>
#include <sstream>
#include <iomanip>
#include "filter.h"

/***************************************************************************
 *      SC_THREAD principale MOYENNEUR
 ***************************************************************************/
void Moyenneur::getImage()
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
         if(!delay) moyenneur();
         else       delay--;
      }
      //h_out et v_out
      if(!delay)
      {
         h_out = h_in;
         v_out = v_in;
      }
   }
}

/**************************
 *      FILTRE MOYENNEUR
 **************************/
void Moyenneur::moyenneur()
{
   int p = 0;
   int tmp = 0;
   int center =-cpt/720 + 2;
   int index  = cpt%720;

   for(int i=0; i<3; i++){
      for(int j=0; j<3; j++){
         if(index-j >= 0){
            tmp += buffer[(720*i)+(index-j)] * filter[(i+center)%3][2-j];
            p   += abs(filter[(i+center)%3][2-j]);
         }
      }
   }

   if(p) tmp = tmp/p;
   p_out = (unsigned char)tmp;
}

/***************************************************************************
 *      SC_THREAD principale ZOOM
 ***************************************************************************/
void Zoom::getImage()
{
   reset_done = false;
   if(reset_n == false)
   {
      cpt        = 0;
      cpt_pixel  = 0;
      cpt_buffer = 0;
      cpt_zoom   = 0;
      delay = 720*576/2;
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
         if(cpt_pixel > 144*720 and cpt_pixel < 432*720)
            if(cpt_pixel%720 >= 180 and cpt_pixel%720 < 540)
               buffer[cpt_buffer++] = p_in;

         if(cpt_pixel++ >= 720*576-1)
         {
            cpt_pixel  = 0;
            cpt_buffer = 0;
         }

         //filtrage
         if(!delay) zoom();
         else       delay--;
      }

      //h_out et v_out
      if(!delay)
      {
         h_out = h_in;
         v_out = v_in;
      }
   }
}

/**************************
 *      FILTRE ZOOM
 **************************/
void Zoom::zoom()
{
   static int line       = 0;
   static int column     = 0;
   static int cpt_column = 0;

   p_out = buffer[cpt_zoom];

   cpt_zoom = (line/2) + (360*column);

   if(line++ > 360*2-2) line=0;

   if(cpt_column++ > 360*4 + 4)
   {
      column++;
      cpt_column = 0;
   }

   if(cpt_pixel == 720*576/2)
   {
      cpt_zoom   = 0;
      line       = 0;
      column     = 0;
      cpt_column = 0;
   }
}
