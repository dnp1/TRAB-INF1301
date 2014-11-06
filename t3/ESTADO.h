#if ! defined ( ESTADO_ )
#define ESTADO_

#if defined( ESTADO_OWN )
    #define ESTADO_EXT
#else
    #define ESTADO_EXT extern
#endif


#include "TIPOESTADO.h"
#include "MENU.h"
#include "TABULEIRO.h"

/***********************************************************************
*
*  $TC Tipo de dados: EST Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum{

    EST_CondRetFaltouMemoria,
    /* Concluiu corretamente */

    EST_CondRetOK
    /* Concluiu corretamente */

} EST_tpCondRet;

EST_tpCondRet EST_CriaEstado(EST_tppEstado e);
EST_tpCondRet EST_SetMenus(EST_tppEstado e, MEN_tppMenus men);
EST_tpCondRet EST_SetTabuleiro(EST_tppEstado e, TAB_tppTabuleiro tab);
EST_tpCondRet EST_GetMenus(EST_tppEstado e, MEN_tppMenus* men);
EST_tpCondRet EST_GetTabuleiro(EST_tppEstado e, TAB_tppTabuleiro* tab);
EST_tpCondRet EST_DestruirEstado(EST_tppEstado e);
#endif
