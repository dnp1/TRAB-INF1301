#if ! defined ( ESTADO_ )
#define ESTADO_

#if defined( ESTADO_OWN )
    #define ESTADO_EXT
#else
    #define ESTADO_EXT extern
#endif

typedef struct estado_ * EST_tppEstado;
#include "MENU.h"
#include "TABULEIRO.h"

EST_tppEstado CriaEstado();
int EST_MudaUltimoMenu(int n);
MEN_tppMenus EST_GetMenus(EST_tppEstado e);
TAB_tppTabuleiro GetTabuleiro(EST_tppEstado e);
#endif
