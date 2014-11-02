#include "GRAFO.h"

/*
   ids dos Menus devem ser unicos e maiores que 1.
   A navegação sempre começa no Menu de id 1, ao menos este deve existir.
   
*/
typedef enum{
    MEN_CondRetFaltouMemoria,
    MEN_CondRetOK
}MEN_tpCondRet;
typedef struct Menu_ * MEN_tppMenu;
typedef struct Opcao_ * MEN_tppOpcao; 

void MEN_DestruirMenu(MEN_tppMenu menu);

MEN_tpCondRet MEN_CriarMenu(GRA_tppGrafo menus, int id, char* nome,int idPai);

MEN_tpCondRet MEN_CriarOpcao(GRA_tppGrafo menus, int idMenu,char cmd, char* nome,void (*callback)(EST_tppEstado,MEN_tppOpcao));


