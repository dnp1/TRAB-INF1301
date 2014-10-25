#include "MENU.h"
#include "GRAFO.h"

typedef struct Menu_{
    char* nome;
    int id;
    GRA_tppGrafo opcoes;        
} Menu;
typedef struct Opcao_{
    char cmd;
    char* nome;
    callback;
} Opcao;

void MEN_DestruirMenu(MEN_tppMenu menu){
    LIS_DestruirLista(menu->opcoes);
    free(menu);
}
/*

Por hipotese existe o grafo menus, id identifica, nome!=null

*/
//mudar pra usar grafo em vez de lista
MEN_CondRet MEN_CriarMenu(tppGrafo menus, int id, char* nome,callback volta){
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
   GRA_InserirVertice(menus,m,m->id);
   //ifs e returns...
   return MEN_CriarOpcao(menus, m->id,'0', "Ir para o menu acima (encerrar o programa caso o menu atual seja o inicial(Inicio))",volta);
}

//mudar lis->gra
MEN_CondRet MEN_CriarOpcao(tppGrafo menus, int idMenu,char cmd, char* nome,callback){
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
    }
