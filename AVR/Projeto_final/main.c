
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
        // Estados  
        switch(current_state){

               // Principal
               case main_st_main_green_t:
                    switch(ev){
                        // Evento
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

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        case Walk:
                            walker = true;
                        break;

                        case Sec:
                            secondary = true;
                        break;

                        default:
                        break;                      
                    }
                    
               break;
             
               case main_st_main_green:
                    // Evento
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

                        default:
                        break;                
                    }                
               break;
               
               // Secundária
               case sec_st_main_yellow:
                    // Evento
                    switch(ev){
                        case Timeout:    
                            Led_Yellow_Main(OFF);
                            Led_Red_Main(ON);  
                            Led_Green_Secondary(ON);  
                            /*  Ativar timer (3s)   */
                            current_state = sec_st_sec_green;                        
                        break;
                        
                        case Walk:
                            walker = true;
                        break;

                        default:
                        break;
                    }                    
               break;

               case sec_st_sec_green:
                    //  Evento
                    switch(ev){
                        case Timeout:
                            Led_Green_Secondary(OFF);
                            Led_Yellow_Secondary(ON);
                            /*  Ativar timer (2s)   */
                            current_state = sec_st_sec_yellow;
                        break;

                        case Amb_Main:
                            Led_Green_Secondary(OFF);
                            Led_Yellow_Secondary(ON);
                            /*  Ativar timer (2s)   */ 
                            current_state = sec_ambmain_st_sec_yelow;                           
                        break;

                        case Walk:
                            walker = true;
                        break;

                        default:
                        break;
                    }
               break;


               case sec_st_sec_yellow:
                    //  Evento
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Secondary(OFF);
                            Led_Yellow_Red(ON);
                            Led_Green_Main(ON);
                            /*  Ativar timer (10s)   */
                            current_state = main_st_main_green_t;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        case Walk:
                            walker = true;
                        break;

                        case Amb_Main:
                            amb_main = true;
                        break;



                        default:
                        break;
                    }
               break;
               
               // Secundário - Ambulância na principal
               case sec_ambmain_st_sec_yelow:
                    // Evento
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Secondary(OFF);
                            Led_Yellow_Red(ON);
                            Led_Green_Main(ON);
                            /*  Verificar push button da ambulância na principal (borda de descida)   */
                            current_state = sec_ambmain_st_main_green;
                        break;

                        case Walk:
                            walker = true;
                        break;
                    
                        default:
                        break;                            
                    }
               break;

               case sec_ambmain_st_main_green:
                    // Evento
                    switch(ev){
                        case Push_Button_Amb_Main:
                            Led_Green_Main(OFF);
                            Led_Yellow_Main(ON);
                            /*  Ativar timer (2s)  */
                            current_state = sec_ambmain_st_main_yellow;                                                                   
                        break;

                        case Walk:
                            walker = true;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        default:
                        break; 
                    }
               break;

               case sec_ambmain_st_main_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Main(OFF);
                            Led_Red_Main(ON);
                            Led_Green_Secondary(ON);
                            /*  Ativar timer (3s)*/
                            current_state = sec_st_sec_green;
                        break;

                        case Walk:
                            walker = true;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        default:
                        break; 
                    }
               break;

               // Ambulância na secundária
               case ambsec_st_main_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Main(OFF);
                            Led_Red_Main(ON);
                            Led_Green_Secondary(ON);
                            /*  Verificar push button da ambulância na secundária (borda de descida)   */
                            current_state = ambsec_st_sec_green;
                        break;
                        
                        case Walk:
                            walker = true;
                        break;

                        default:
                        break; 
                    }
               break;

               case ambsec_st_sec_green:
                    switch(ev){
                        case Push_Button_Amb_Sec:
                            Led_Green_Secondary(OFF);
                            Led_Yellow_Secondary(ON);
                            /*  Ativar timer 2s*/
                            current_state = ambsec_st_sec_yellow;
                        break;

                        case Walk:
                            walker = true;
                        break;

                        case Amb_Main:
                            amb_main = true;
                        break;

                        default:
                        break;
                    }
               break;

               case ambsec_st_sec_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Secondary(OFF);
                            Led_Red_Secondary(ON);
                            Led_Green_Main(ON);
                            current_state = main_st_main_green;
                        break;

                       case Walk:
                            walker = true;
                        break;

                        case Amb_Main:
                            amb_main = true;
                        break;

                        default:
                        break;
                    }
               break;

               // Pedestre
               case walk_st_main_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Main(OFF);
                            Led_Red_Main(ON);
                            Led_Green_Walker(ON);
                            /*  Ativar timer (3s)   */
                            current_state = walk_st_walk_green;
                        break;

                        case Sec:
                            secondary = true;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        default:
                        break;
                    }
               break;
                
               case walk_st_walk_green:
                    switch(ev){
                        case Timout:
                            Led_Green_Walker(OFF);
                            Led_Blink_Waker(ON);
                            /*  Ativar timer (2s)*/
                            current_state = walk_st_walk_yellow;
                        break;

                        case Amb_Main:
                            Led_Green_Walker(OFF);
                            Led_Blink_Waker(ON);
                            /*  Ativar timer (2s)*/
                            current_state = walk_ambmain_st_walk_yellow;                            
                        break;

                        case Amb_Sec
                            Led_Green_Walker(OFF);
                            Led_Blink_Waker(ON);
                            /*  Ativar timer (2s)*/
                            current_state = walk_ambsec_st_walk_yellow;   
                        break;

                        case Sec:
                            secondary = true;
                        break;

                        default:
                        break;                    
                    }
               break;

               case walk_st_walk_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Blink_Walker(OFF);
                            Led_Red_Walker(ON);
                            Led_Green_Main(ON);
                            /*  Ativar timer (10s)*/
                            current_state = main_st_main_green_t;
                        break;

                        case Sec:
                            secondary = true;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        case Amb_Main:
                            amb_main = true;
                        break;

                        default:
                        break;                    
                    }
               break;

               // Pedestre - Ambulância na principal
               case walk_ambmain_st_walk_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Blink_Walker(OFF);
                            Led_Red_Walker(ON);
                            Led_Green_Main(ON);
                            /*  Verificar push button da ambulância na principal (borda de descida)   */
                            current_state = walk_ambmain_st_main_green;
                        break;

                        case Sec:
                            secondary = true;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        default:
                        break;             
                    }
               break;

               case walk_ambmain_st_main_green:
                    switch(ev){
                        case Push_Button_Amb_Main:
                            Led_Green_Main(OFF);
                            Led_Yellow_Main(ON);
                            /*  Ativar timer (2s)   */
                            current_state = walk_ambmain_st_main_yellow;
                        break;

                        case Sec:
                            secondary = true;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        default:
                        break;                    
                    }
               break;

               case walk_ambmain_st_main_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Main(OFF);
                            Led_Red_Main(ON);
                            Led_Green_Walker(ON);
                            current_state = walk_st_walk_green;
                        break;

                        case Sec:
                            secondary = true;
                        break;

                        case Amb_Sec:
                            amb_secondary = true;
                        break;

                        default:
                        break;                    
                    }
               break;

               // Pedestre - Ambulância na secundária            
               case walk_ambsec_st_walk_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Blink_Walker(OFF)
                            Led_Green_Secondary(ON);
                            /*  Verificar push button da ambulância na secundária (borda de descida)   */
                            current_state = walk_ambsec_st_sec_green;
                        break;

                        case Amb_Main:
                            amb_main = true;
                        break;

                        default:
                        break;                    
                    }
               break;
          
               case walk_ambsec_st_sec_green:
                    switch(ev){
                        case Push_Button_Amb_Sec:
                            Led_Green_Secondary(OFF);
                            Led_Yellow_Secondary(ON);
                            /*  Ativar timeout de 2s  */
                            current_state = walk_ambsec_st_sec_yellow;
                        break;

                        case Amb_Main:
                            amb_main = true;
                        break;

                        default:
                        break;                    
                    }
               break;

               case walk_ambsec_st_sec_yellow:
                    switch(ev){
                        case Timeout:
                            Led_Yellow_Secondary(OFF);
                            Led_Red_Secondary(ON);
                            Led_Green_Walker(ON);
                            current_state = walk_st_walk_green;
                        break;

                        case Amb_Main:
                            amb_main = true;
                        break;

                        default:
                        break;                    
                    }
               break;

               default:
               break;
        }
        
  }






}
