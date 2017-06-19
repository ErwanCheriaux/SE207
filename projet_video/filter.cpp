#include <cstdio>
#include <sstream>
#include <iomanip>
#include "filter.h"

/***************************************************************************
 *      FILTRE MEDIAN
 ***************************************************************************/
void Filter::median_filter()
{
   reset_done = false;
   if(reset_n == false)
   {
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
   }
}
