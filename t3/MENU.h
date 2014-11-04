#if ! defined ( MENU_ )
#define MENU_

#if defined( MENU_OWN )
    #define MENU_EXT
#else
    #define MENU_EXT extern
#endif
/*
   ids dos Menus devem ser unicos e maiores que 1.
   A navegação sempre começa no Menu de id 1, ao menos este deve existir.
   
*/
#include "GRAFO.h"
typedef enum{
    MEN_CondRetFaltouMemoria,
    MEN_CondRetOK
}MEN_tpCondRet;
typedef GRA_tppGrafo MEN_tppMenus;
typedef struct Menu_ * MEN_tppMenu;
typedef struct Opcao_ * MEN_tppOpcao; 
#include "ESTADO.h"

void MEN_DestruirMenu(MEN_tppMenu menu);

MEN_tpCondRet MEN_CriarMenu(MEN_tppMenus menus, int id, char* nome,int idPai);
MEN_tpCondRet MEN_CriarOpcao(MEN_tppMenus menus, int idMenu,char cmd, char* nome,void (*callback)(EST_tppEstado e,MEN_tppOpcao o));

LIS_tppLista MEN_GetMenuOpcoes(MEN_tppMenu m);
char* MEN_GetMenuNome(MEN_tppMenu m);

char MEN_GetOpcaoCmd(MEN_tppOpcao o);
char* MEN_GetOpcaoNome(MEN_tppOpcao o);
void MEN_Callback(MEN_tppOpcao o, EST_tppEstado e);
#endif
