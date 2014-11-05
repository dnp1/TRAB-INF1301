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
#include "TIPOESTADO.h"
typedef enum{
    MEN_CondRetFaltouMemoria,
    MEN_CondRetOK
}MEN_tpCondRet;
typedef GRA_tppGrafo MEN_tppMenus;
typedef struct Menu_ * MEN_tppMenu;
typedef struct Opcao_ * MEN_tppOpcao; 

void MEN_DestruirMenu(MEN_tppMenu menu);

MEN_tpCondRet MEN_CriarMenu(MEN_tppMenus menus, int id, char* nome,int idPai);
MEN_tpCondRet MEN_CriarOpcao(MEN_tppMenus menus, int idMenu,char cmd, char* nome,void (*callback)(EST_tppEstado e,MEN_tppOpcao o));


MEN_tpCondRet MEN_GetMenuOpcoes(MEN_tppMenu m,LIS_tppLista l); 
MEN_tpCondRet MEN_GetMenuNome(MEN_tppMenu m, char* nome);
MEN_tpCondRet MEN_GetOpcaoCmd(MEN_tppOpcao o, char cmd);
MEN_tpCondRet MEN_GetOpcaoNome(MEN_tppOpcao o, char* nome);
MEN_tpCondRet MEN_Callback(MEN_tppOpcao o, EST_tppEstado e);
MEN_tpCondRet MEN_MudaMenu(MEN_tppMenus m, int id);
#endif
