#include "ESTADO.h"
#include <stdlib.h>
//struct para manter o estado do jogo. 
//Ela é passada por referência para para ser modificada e lida.
//Ela é UNICA.
typedef struct estado_{
    //o id do corrente de Menus eh o o id do menu atual
    MEN_tppMenus Menus;
    TAB_tppTabuleiro Tabuleiro;
    //id do ultimo menu, do menu pai/acima
    //variavel utilizada para implementar a opcao 0 dos menus
} tpEstado;


EST_tpCondRet EST_CriaEstado(EST_tppEstado* est){
    
    EST_tppEstado e = (EST_tppEstado)malloc(sizeof(tpEstado));
    
    if(e==NULL) 
    {
        return EST_CondRetFaltouMemoria;
    }
    if(MEN_CriarMenus(&(e->Menus))!=MEN_CondRetOK){
        free(e);
        return EST_CondRetFaltouMemoria;
    }; 
    *est = e;
    return EST_CondRetOK;
}

EST_tpCondRet EST_DestruirEstado(EST_tppEstado est){
    TAB_DestruirTabuleiro(est->Tabuleiro);
    MEN_DestruirMenus(est->Menus);
    free(est);

    return EST_CondRetOK;
}

EST_tpCondRet EST_SetMenus(EST_tppEstado e, MEN_tppMenus men){
    e->Menus = men;
    return EST_CondRetOK;
}
EST_tpCondRet EST_SetTabuleiro(EST_tppEstado e,TAB_tppTabuleiro tab){
    e->Tabuleiro = tab;
    return EST_CondRetOK;
}
EST_tpCondRet EST_GetMenus(EST_tppEstado e, MEN_tppMenus* men){
    *men =  e->Menus;
    return EST_CondRetOK;
}
EST_tpCondRet EST_GetTabuleiro(EST_tppEstado e,TAB_tppTabuleiro* tab){
    *tab =  e->Tabuleiro;
    return EST_CondRetOK;
}
