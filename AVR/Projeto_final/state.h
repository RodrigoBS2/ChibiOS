#ifndef STATE_H
#define STATE_H

typedef enum {

    // Estados. 
    /* 
        Obs: t = timeout, st = state (estado), sec = secundária, main = principal, walk = pedestre, ambmain = ambulância principal, ambsec = ambulância na 
           secundária
    */

    main_st_main_green_t, main_st_main_green,   // Principal
    
    sec_st_main_yellow, sec_st_sec_green, sec_st_sec_yellow,    // Secundária
    
    sec_ambmain_st_sec_yelow, sec_ambmain_st_main_green, sec_ambmain_st_main_yellow,   // Secundária / Ambulância na principal

    ambsec_st_main_yellow, ambsec_st_sec_green, ambsec_st_sec_yellow,   // Ambulância na secundária

    walk_st_main_yellow, walk_st_walk_green, walk_st_walk_yellow,   // Pedestre

    walk_ambmain_st_walk_yellow, walk_ambmain_st_main_green, walk_ambmain_st_main_yellow,   // Pedestre / Ambulância na principal
    
    walk_ambsec_st_walk_yellow, walk_ambsec_st_sec_green, walk_ambsec_st_sec_yellow;    // Pedestr / Ambulância na secundária


}state_t;

typedef enum{
    Timeout, Amb_Main, Amb_Sec, Walk, Sec;


}event_t;

#endif

