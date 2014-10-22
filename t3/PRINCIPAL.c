
#define vaimenu(_x) void vaiMenu##_x(tppEstado e){ \
                        UltimoMenu = _x; \
                        GRA_IrVizinho(e->Menus,_x); \
                    }
vaimenu(1)
vaimenu(2)
vaimenu(3)
vaimenu(4)

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
void carrega(){
    e->Tabuleiro = TAB_CriarTabuleiro();
    
}
void volta_tab(tppEstado e){
    GRA_ExcluirGrafo(e->Tabuleiro);
    GRA_IrVizinhoCorrente(e->Menu,e->UltimoMenu);
}
void volta(tppEstado e){
    GRA_IrVizinhoCorrente(e->Menu,e->UltimoMenu);
}
void novo_tab(){
    char* nome;
    int alt,lar;
    Erro("Digite o nome",LEI_LeString(nome));
    Erro("Digite a altura (1..10)",LEI_LeInt(&alt,1,10));
    Erro("Digite a largura (1.10)",LEI_LeInt(&lar,1,10));
    tpptab a;
    Erro("Criando tabuleiro",TAB_CriaTab(a,nome, alt,lar));
    Erro("Salvando tabuleiro",TAB_salvaTab(a));
}

enum modules{
    PRI,
    LEI,
    TAB
}
void TrataPRI(int CondRet){
    switch(CondRet){
        case PRI_CondRetOK: 
            printf("Sucesso");
        break;
        case PRI_FaltouMemoria:
            printf("Operacao mal sucedida. Faltou Memoria.");
        break;   
        printf("Comando invalido"); 
    }
}
void Erro(char* comm, int CondRet,int module){
    printf("%s",comm);
    switch (module){
        case PRI:
            trataPRI(CondRet);
            break;
        case TAB:
            trataTAB(CondRet);
            break;
        case LEI:
            trataLEI(CondRet);
            break;
}
int main(){
    tppEstado e = CriaEstado();
    
    Erro("criando menu inicio", MEN_CriarMenu(e->Menus,1,"inicio",volta));
      
    Erro("criando opcao 1 de inicio", MEN_CriarOpcao(e->Menus,1,'1',"Criar Mapa",vaiMenu2) ;
    Erro("criando opcao 2 de inicio", MEN_CriarOpcao(e->Menus,1,'2',"Jogar",vaiMenu3);
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


