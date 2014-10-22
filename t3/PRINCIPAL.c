//modulos
#include "GRAFO.c"
#include "TABULEIRO.c"
#include "LEITOR.c"

//organizacao
#include "ERRO.c"
#include "ESTADO.c"
#include "POPULA.c"
#include "APRESENTADOR.c"

int main(){
    tppEstado e = CriaEstado();
    PopulaMenus(e);
    //inicia a navegacao em 1
    GRA_MudarCorrente(e->Menus,1);
    //só sera 0 quando o ultimo corrente for 1 e o usuario digitar 0
    while(GRA_ObterIdCorrente(e->Menus)!=0){
        APR_ApresentaMenu(e->Menus);
        if(MenuAtual == EDITOR||JOGO)
            APR_ApresentaTabuleiro(e->Tabuleiro);
        Erro("Digite um comando:",LEI_LeCmd(e));
    }
    //clean(); //housekeeping
    return 0;
}


