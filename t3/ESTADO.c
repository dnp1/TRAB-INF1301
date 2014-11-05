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
    int UltimoMenu;
} tpEstado;


EST_tppEstado CriaEstado(){
    
    EST_tppEstado e = malloc(sizeof(tpEstado));
    
    if(e==NULL) 
    {
        return NULL;
    }
    
    GRA_tppGrafo Menus = GRA_CriarGrafo(MEN_DestruirMenu);
    
    if(Menus==NULL)
    {
        free(e);
        return NULL;
    }
    e->Menus = Menus;
    e->UltimoMenu = 0;
    return e;
}

//EST_tpCondRet EST_MenuInicial(EST_tppEstado e){
int EST_MenuInicial(EST_tppEstado e){
    //algo proximo a isso, tem q tratar os condret
    return GRA_MudarCorrente(e->Menus,1);
}
int EST_MenuCorrente(EST_tppEstado e){
    return GRA_ObterIdCorrente(e->Menus);
}

int EST_MudaUltimoMenu(EST_tppEstado e,int n){
    e->UltimoMenu = n;
}
MEN_tppMenus EST_GetMenus(EST_tppEstado e){
    return e->Menus;
}
TAB_tppTabuleiro GetTabuleiro(EST_tppEstado e){
    return e->Tabuleiro;
}
