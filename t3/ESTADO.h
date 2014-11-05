#if ! defined ( ESTADO_ )
#define ESTADO_

#if defined( ESTADO_OWN )
    #define ESTADO_EXT
#else
    #define ESTADO_EXT extern
#endif


#include "TIPOESTADO.h"
/*
#if ! defined ( TIPOESTADO_ )
#define TIPOESTADO_
typedef struct estado_ * EST_tppEstado;
#endif
*/
#include "MENU.h"
#include "TABULEIRO.h"

EST_tppEstado EST_CriaEstado();
int EST_MudaUltimoMenu(EST_tppEstado e, int n);
MEN_tppMenus EST_GetMenus(EST_tppEstado e);
TAB_tppTabuleiro EST_GetTabuleiro(EST_tppEstado e);
#endif
