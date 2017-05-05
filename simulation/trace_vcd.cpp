//trace_vcd.cpp

#include <systemc.h>

int sc_main (int argc, char * argv[])
{
   if(argc != 2)
   {
      cout << "Mauvais nombre d'arguments : 2" << endl;
      return 1;
   }

   int N = atoi(argv[1]);

   if(N<0 or N>255)
   {
      cout << "L'argument doit être entre 0 et 255 !" << endl;
      return 1;
   }

   // Un pointeur sur l'objet qui permet de gérer les traces
   sc_trace_file *trace_f;

   // Cette fonction crée l'objet
   // L'argument est le nom du fichier qui sera créé.
   // L'extension .vcd est ajoutée automatiquement
   trace_f = sc_create_vcd_trace_file ("my_simu_trace");
   // On peut aussi préciser l'unité de temps dans le fichier vcd
   trace_f->set_time_unit(1,SC_NS);

   bool t;

   // Ajoute la variable t aux éléments à tracer
   // Les arguments de la fonction sont:
   //    - le pointeur vers le fichier de trace
   //    - la variable/objet à tracer
   //    - le nom dans dans le fichier généré
   sc_trace(trace_f, t, "t");

   // La simulation
   for(int i=0; i<N; i++)
   {
      sc_start(10,SC_NS);
      t = !t;
   }

   // Ferme le fichier de trace
   // ne peut êter fait qu'à la fin de la simulation
   sc_close_vcd_trace_file(trace_f);

   return 0;
}
