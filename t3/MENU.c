#include "MENU.h"
#include "ESTADO.h"
#include "GRAFO.h"
#include "LISTA.h"
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

static void ExcluirMenu(void* menu){
    LIS_tppLista l = ((MEN_tppMenu)menu)->opcoes;
    LIS_DestruirLista(l);
    free(menu);
}
MEN_tpCondRet MEN_DestruirOpcao(MEN_tppMenus m, int idMenu, char cmd){
   MEN_tppMenu menu;
   GRA_ObterValor(m->grafo,idMenu,(void**)&menu); 
   do{
        if(((MEN_tppOpcao)LIS_ObterValor(menu->opcoes))->cmd == cmd){
            LIS_ExcluirElemento(menu->opcoes); 
            return MEN_CondRetOK;
        }
   }
   while(LIS_AvancarElementoCorrente(menu->opcoes,1)==LIS_CondRetOK);
   return MEN_CondRetComandoInvalido;
}

MEN_tpCondRet MEN_DestruirMenu(MEN_tppMenus m, int id){
    GRA_ExcluirVertice(m->grafo, id);
}
MEN_tpCondRet MEN_DestruirMenus(MEN_tppMenus m){
    GRA_DestruirGrafo(m->grafo);
    free(m);
    return MEN_CondRetOK;
};
/*

   Por hipotese existe o grafo menus, id identifica, nome!=null

 */
//mudar pra usar grafo em vez de lista
void volta(EST_tppEstado e,MEN_tppOpcao o){
   MEN_tppMenus menus;
   MEN_tppMenu atual;

   EST_GetMenus(e,&menus);
   GRA_ObterValorCorrente(menus->grafo,(void**)&atual);
   MEN_MudaMenu(menus,atual->pai);
}

MEN_tpCondRet MEN_CriarMenu(MEN_tppMenus menus, int id, char* nome,int idpai){
    MEN_tpCondRet cr;
    MEN_tppMenu m = (MEN_tppMenu)malloc(sizeof(Menu));
    if(m==NULL)
        return MEN_CondRetFaltouMemoria;
    m->opcoes = LIS_CriarLista(free);         
    if(m->opcoes==NULL){
        free(m);
        return MEN_CondRetFaltouMemoria;
    }
    m->nome = nome;
    m->id = id;
    GRA_InserirVertice(menus->grafo,m,m->id);
    cr = MEN_CriarOpcao(menus, m->id,'0', "Ir para o menu acima (encerrar o programa caso o menu atual seja o inicial(Inicio))",volta);
    if(cr!=MEN_CondRetOK)
    {
        LIS_DestruirLista(m->opcoes);
        free(m);
    }
    //tratar cond ret
    return cr;
}

//mudar lis->gra
MEN_tpCondRet MEN_CriarOpcao(MEN_tppMenus menus, int idMenu,char cmd, char* nome,MEN_tpCondRet (*callback)(EST_tppEstado e,MEN_tppOpcao o)){
    MEN_tppMenu m;
    MEN_tppOpcao o = (MEN_tppOpcao)malloc(sizeof(Opcao));
    if(o==NULL)
        return MEN_CondRetFaltouMemoria;
    //if(nome==NULL)
    //return erro;
    o->nome = nome;
    o->cmd = cmd;
    o->callback = callback;

    GRA_ObterValor(menus->grafo,idMenu,(void**)&m);
    LIS_InserirElementoApos(m->opcoes,o);
    return MEN_CondRetOK;
}


MEN_tpCondRet MEN_Callback(MEN_tppOpcao o, EST_tppEstado e){
    return o->callback(e,o);
}

MEN_tpCondRet MEN_GetMenuOpcoes(MEN_tppMenus m,int id,LIS_tppLista* l){
    MEN_tppMenu menu;
    GRA_ObterValor(m->grafo,id,&menu);
    *l = menu->opcoes;
    return MEN_CondRetOK;
} 
MEN_tpCondRet MEN_GetMenuNome(MEN_tppMenus m, int id, char** nome){
    MEN_tppMenu menu;
    GRA_ObterValor(m->grafo,id,&menu);
    *nome = menu->nome;
    return MEN_CondRetOK;

}
MEN_tpCondRet MEN_GetOpcaoCmd(MEN_tppOpcao o, char* cmd){
    *cmd = o->cmd;
    return MEN_CondRetOK;

}
MEN_tpCondRet MEN_GetOpcaoNome(MEN_tppOpcao o, char** nome){
    *nome = o->nome;
    return MEN_CondRetOK;

}
MEN_tpCondRet MEN_CriarMenus(MEN_tppMenus* men){
    GRA_tppGrafo Menus;
    MEN_tppMenus m = (MEN_tppMenus)malloc(sizeof(tpMenus));
    if(m == NULL)
        return MEN_CondRetFaltouMemoria;
    Menus = GRA_CriarGrafo(ExcluirMenu);
    if(Menus == NULL){
        free(m);
        return MEN_CondRetFaltouMemoria;
    }
    
    m->grafo = Menus;
    GRA_MudarCorrente(m->grafo,1);
    m->UltimoMenu = 0;
    
    *men = m;
    return MEN_CondRetOK;
}
MEN_tpCondRet MEN_MenuInicial(MEN_tppMenus men){
    //algo proximo a isso, tem q tratar os condret
    GRA_MudarCorrente(men->grafo,1);
    return MEN_CondRetOK;
}
MEN_tpCondRet MEN_MenuCorrente(MEN_tppMenus men, int* id){
    //checacondret
    int temp;
    GRA_ObterIDCorrente(men->grafo,&temp);
    *id = temp;
    return MEN_CondRetOK;
}
MEN_tpCondRet MEN_MudaMenu(MEN_tppMenus menus,int id){
    GRA_ObterIDCorrente(menus->grafo,&(menus->UltimoMenu));
    //checa condret
    GRA_MudarCorrente(menus->grafo,id);
    return MEN_CondRetOK;
}
