#include "MENU.h"
#include "GRAFO.h"
#include <stdlib.h>


typedef struct Menus_{
    GRA_tppGrafo grafo;
    int UltimoMenu;
} tpMenus;
typedef struct Menu_{
    char* nome;
    int id;
    LIS_tppLista opcoes;        
    int pai;
} Menu;
typedef struct Opcao_{
    char cmd;
    char* nome;
    MEN_tpCondRet (*callback)(EST_tppEstado e,MEN_tppOpcao o);
} Opcao;

void MEN_DestruirMenu(MEN_tppMenu menu){
    LIS_DestruirLista(menu->opcoes);
    free(menu);
}
/*

   Por hipotese existe o grafo menus, id identifica, nome!=null

 */
//mudar pra usar grafo em vez de lista
void volta(EST_tppEstado e,MEN_tppOpcao o){
   MEN_tppMenus menus = EST_GetMenus(e);
   MEN_tppMenu atual;
   GRA_ObterCorrente(menus,atual);
   EST_MudaUltimoMenu(atual->id);
   GRA_IrVizinho(menus,atual->pai); 
}

MEN_tpCondRet MEN_CriarMenu(MEN_tppMenus menus, int id, char* nome,int idpai){
    MEN_tppMenu m = malloc(sizeof(Menu));
    if(m==NULL)
        return MEN_CondRetFaltouMemoria;
    m->opcoes = LIS_CriarLista(free);         
    if(m->opcoes==NULL){
        free(m);
        return MEN_CondRetFaltouMemoria;
    }
    m->nome = nome;
    m->id = id;
    MEN_tpCondRet cr = MEN_CriarOpcao(menus, m->id,'0', "Ir para o menu acima (encerrar o programa caso o menu atual seja o inicial(Inicio))",volta);
    if(cr!=MEN_CondRetOK)
    {
        LIS_ExcluirLista(m->opcoes);
        free(m);
    }
    //tratar cond ret
    GRA_InserirVertice(menus->grafo,m,m->id);
    return cr;
}

//mudar lis->gra
MEN_tpCondRet MEN_CriarOpcao(MEN_tppMenus menus, int idMenu,char cmd, char* nome,MEN_tpCondRet (*callback)(EST_tppEstado e,MEN_tppOpcao o)){
    MEN_tppOpcao o = malloc(sizeof(Opcao));
    if(o==NULL)
        return MEN_CondRetFaltouMemoria;
    //if(nome==NULL)
    //return erro;
    o->nome = nome;
    o->cmd = cmd;
    o->callback = callback;
    MEN_tppMenu m;
    GRA_ObterValor(menus,idMenu,m);
    LIS_InserirElementoApos(m->opcoes,o);
    return MEN_CondRetOK;
}
MEN_tpCondRet MEN_MudaMenu(MEN_tppMenus menus,int id){    	
    GRA_IrVizinho(menus,id);
}


MEN_tpCondRet MEN_Callback(MEN_tppOpcao o, EST_tppEstado e){
    return o->callback(e,o);
}

MEN_tpCondRet MEN_GetMenuOpcoes(MEN_tppMenu m,LIS_tppLista l){
    l = m->opcoes;
    return MEN_CondRetOK;
} 
MEN_tpCondRet MEN_GetMenuNome(MEN_tppMenu m, char* nome){
    nome = m->nome;
    return MEN_CondRetOK;

}
MEN_tpCondRet MEN_GetOpcaoCmd(MEN_tppOpcao o, char* cmd){
    cmd = o->cmd;
    return MEN_CondRetOK;

}
MEN_tpCondRet MEN_GetOpcaoNome(MEN_tppOpcao o, char* nome){
    nome = nome->nome;
    return MEN_CondRetOK;

}
MEN_tpCondRet MEN_CriarMenus(MEN_tppMenus* men){
    
    MEN_tppMenus m = malloc(sizeof(tpMenus));
    if(m == NULL)
        return MEN_CondRetFaltouMemoria;
    GRA_tppGrafo Menus = GRA_CriarGrafo(MEN_DestruirMenu);
    if(m == NULL){
        free(m);
        return MEN_CondRetFaltouMemoria;
    }
    m->grafo = Menus;
    m->UltimoMenu = 0;
    
    *men->grafo = (MEN_tppMenus)Menus;
    return MEN_CondRetOK;
}
MEN_tpCondRet MEN_MenuInicial(MEN_tppMenus men){
    //algo proximo a isso, tem q tratar os condret
    GRA_MudarCorrente(men->grafo,1);
    return MEN_CondRetOK;
}
MEN_tpCondRet MEN_MenuCorrente(MEN_tppMenus e, int* id){
    *id = GRA_ObterIdCorrente(men->grafo);
    return MEN_CondRetOK;
}
MEN_tpCondRet MEN_MudaUltimoMenu(MEN_tppMenus e,int n){
    men->UltimoMenu = n;
    return MEN_CondRetOK;
}
