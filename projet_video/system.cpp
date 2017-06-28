/**********************************************************************
 * File : system.cpp
 * Date : 2008-2016
 * Author :  Alexis Polti/Tarik Graba
 *
 * This program is released under the GNU public license
 * Télécom ParisTECH
 *
 * Testbench pour video_in
 **********************************************************************/

#include <systemc.h>
#include <sstream>
#include "video_in.h"
#include "video_out.h"
#include "filter.h"

/***************************************************
 *	MAIN
 **************************************************/

int sc_main (int argc, char *argv[])
{
    int	ncycles;

    if (argc == 2) {
        std::stringstream arg1(argv[1]);
        arg1 >> ncycles;
    } else {
        cout
           << endl
           << "Le nombre de cycles de simulation doit être passé en argument (-1 pour une simulation illimitée)"
           << endl
           ;
        exit(1);
    }

    /******************************************************
     *      Déclaration des signaux
     *****************************************************/

    /* La période de l'horloge du signal vidéo */
    sc_time pix_period(74, SC_NS);

    sc_clock                        signal_clk("Clock", pix_period);
    sc_signal<bool>                 signal_resetn;

    sc_signal<bool>                 signal_href_1,  signal_href_2,  signal_href_3;
    sc_signal<bool>                 signal_vref_1,  signal_vref_2,  signal_vref_3;
    sc_signal<unsigned char>        signal_pixel_1, signal_pixel_2, signal_pixel_3;

    /********************************************************
     *	Instanciation des modules
     *******************************************************/

    VIDEO_IN  video_in  ("VIDEO_GEN");
    Zoom      zoom      ("zoom");
    Median    median    ("median");
    VIDEO_OUT video_out ("VIDEO_OUT");

    /*********************************************************
     *	Connexion des composants
     ********************************************************/

    video_in.clk       (signal_clk);
    video_in.reset_n   (signal_resetn);
    video_in.href      (signal_href_1);
    video_in.vref      (signal_vref_1);
    video_in.pixel_out (signal_pixel_1);

    zoom.clk           (signal_clk);
    zoom.reset_n       (signal_resetn);
    zoom.h_in          (signal_href_1);
    zoom.v_in          (signal_vref_1);
    zoom.p_in          (signal_pixel_1);
    zoom.h_out         (signal_href_2);
    zoom.v_out         (signal_vref_2);
    zoom.p_out         (signal_pixel_2);
                       
    median.clk         (signal_clk);
    median.reset_n     (signal_resetn);
    median.h_in        (signal_href_2);
    median.v_in        (signal_vref_2);
    median.p_in        (signal_pixel_2);
    median.h_out       (signal_href_3);
    median.v_out       (signal_vref_3);
    median.p_out       (signal_pixel_3);

    video_out.clk      (signal_clk);
    video_out.reset_n  (signal_resetn);
    video_out.href     (signal_href_3);
    video_out.vref     (signal_vref_3);
    video_out.pixel_in (signal_pixel_3);

    /*********************************************************
     *	Traces
     ********************************************************/

    /* fichier de traces */
    sc_trace_file * my_trace_file;
    my_trace_file = sc_create_vcd_trace_file ("simulation_trace");
    my_trace_file->set_time_unit(1,SC_NS);

#define TRACE(x) sc_trace(my_trace_file, x, #x)

    /* chronogrammes signaux CLK et NRESET */
    TRACE( signal_clk );
    TRACE( signal_resetn );

    /* chronogrammes video */
    TRACE( signal_href_1 );
    TRACE( signal_href_2 );
    TRACE( signal_href_3 );
    TRACE( signal_vref_1 );
    TRACE( signal_vref_2 );
    TRACE( signal_vref_3 );
    TRACE( signal_pixel_1 );
    TRACE( signal_pixel_2 );
    TRACE( signal_pixel_3 );

#undef TRACE

    /*********************************************************
     *	Simulation
     ********************************************************/

    /* Initialisation de la simulation */
    sc_start(SC_ZERO_TIME);
    signal_resetn = true;
    sc_start(10*signal_clk.period());

    /* Génération d'un reset */
    signal_resetn = false;
    sc_start(10*signal_clk.period());
    signal_resetn = true;

    /* Lancement de la simulation */
    if(ncycles >= 0) {
       cout << "Simulation lancée pour " << ncycles << " cycle de " << signal_clk.period() << endl;
       sc_start(ncycles * signal_clk.period());
    } else {
       cout << "Simulation lancée en continu (CTRL-C pour l'arrêter)" << endl;
       sc_start();
    }

    cout << "Fin de la simulation @ " << sc_time_stamp() << endl;

    /* Close trace file */
    sc_close_vcd_trace_file (my_trace_file);

    return EXIT_SUCCESS;
}
