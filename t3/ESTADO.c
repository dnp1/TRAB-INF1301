
//struct para manter o estado do jogo. 
//Ela é passada para as callbacks para ser modificada e lida.
//Ela é UNICA.
typedef struct estado_{
    //o id do corrente de Menus eh o o id do menu atual
    GRA_tppGrafo Menus;
    GRA_tppGrafo tabuleiro;
    //id do ultimo menu, do menu pai/acima
    //variavel utilizada para implementar a opcao 0 dos menus
    int UltimoMenu;
} estado;
//tipo exportado
//usado por LEI 
typedef estado* tppEstado;


tppEstado CriaEstado(){
    malloc(sizeof(estado));
    GRA_tppGrafo Menus = GRA_CriarGrafo(MEN_DestruirMenu);
    //GRA_tppGrafo Tabuleiro = GRA_CriarGrafo(MEN_DestruirMenu);
    
    if(e == NULL||Menus==NULL){
        APR_Erro(CondRetFaltouMemoria);
        return 0;
    }
}
