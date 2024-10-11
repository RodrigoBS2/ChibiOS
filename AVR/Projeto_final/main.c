
#include "AVRincludes.h"
#include "pin.h"
#include "signal.h"
#include "state.h"

/* Variáveis globais    */
    // Buffer - eventos
    volatile bool walker = false;
    volatile bool secondary = false;
    volatile bool amb_secondary = false;
    volatile bool amb_main = false;

    // Estado atual  
    volatile state_t current_state = main_st_main_green_t;

    // Temporizadores
    virtual_timer_t vt_main_green_t;

/* Callbacks - Temporizadores */

    void vt_main_green_t_cb(void *arg)
    {
        chSysLockFromISR();
        flag_tratar_evento = 1;
        evento = tempo_motor;
        chVTSetI(&vt_main_green_t, TIME_MS2I(MAIN_TIMEOUT), vt_main_green_t_cb, NULL);
        chSysUnlockFromISR();
    }

event_t get_event(){

}


int main(void) {
  
  halInit();    //  Inicialização do HAL
  chSysInit();  //  Inicialização do Kernel

  
  //Configuração inicial dos sinais de transito
  void config_signals();
  void Led_Green_Main(ON);
  
  // Eventos
  event_t ev;

  while (true) {
        ev = get_event();
        // Estados  (main_st_main_green_t, main_st_main_green)
        switch(current_state){
               case main_st_main_green_t:
                    switch(ev){
                        case Timeout:
                            if(amb_secondary){
                                Led_Green_Main(OFF);    
                                Led_Yellow_Main(ON);
                                /*  Ativar timer (2s)   */
                                amb_secondary = false;
                                current_state = ambsec_st_main_yellow;
                            }
                            else if(walker){
                                Led_Green_Main(OFF);    
                                Led_Yellow_Main(ON);
                                /*  Ativar timer (2s)   */
                                walker = false;
                                current_state = walk_st_main_yellow;
                            } 
                            else if(secondary){
                                Led_Green_Main(OFF);    
                                Led_Yellow_Main(ON);
                                /*  Ativar timer (2s)   */
                                secondary = false;
                                current_state = sec_st_main_yellow;
                            } 
                            else{
                              current_state = main_st_main_green;                              
                            } 
                        break;

                        default:
                        break;                      
                    }
                    
               break;
               
               case main_st_main_green:
                    switch(ev){
                        case Amb_Sec:
                            Led_Green_Main(OFF);    
                            Led_Yellow_Main(ON);
                            /*  Ativar timer (2s)   */    
                            current_state = ambsec_st_main_yellow;                                                     
                        break;
                        
                        case Sec:     
                            Led_Green_Main(OFF);    
                            Led_Yellow_Main(ON);      
                            /*  Ativar timer (2s)   */         
                            current_state = sec_st_main_yellow;                                         
                        break;
                
                        case Walk: 
                            Led_Green_Main(OFF);    
                            Led_Yellow_Main(ON);    
                            /*  Ativar timer (2s)   */
                            current_state = walk_st_main_yellow;                                                    
                        break;                
                    }                

               default:
               break;
        }
        
  }






}
