/*  Modulo responsavel por realizar o fluxo do jogo.
    É neste módulo que se mantém e se modifica o estado do jogo.
    O fluxo do jogo se da nas seguintes etapas:
        1 - Leitura de Input
        2 - Mudança do estado
        3 - Apresentação do estado
    O estado é mantido em uma variável:
        int MenuAtual - o id do menu
    Há um mapa de menus construidos a partir da seguinte estrutura:
      Menu
        char* nome do menu
        int id
        LIS de opcoes 
            sempre existe a opcao de id 0, que volta ao menu anterior
      Opcao
        char* nome da opcao
        char id/cmd
        void callback*(void)
        
    Este módulo utiliza outros 3 módulos:
        LEI - LEITOR.h     
            função Le() 
                Le um caracter(id/cmd da opção)  e executa a funcao associada ao mesmo em opção. 
            função Joga()
                
        APR - APRESENTADOR.h
            função ApresentaMenu()
                Apresenta uma tela contendo o nome do menu atual, suas opções com seus ids.
                Se estiver na tela de jogo ou edição de mapa, desenha o mapa.
            função ApresentaTabuleiro()
                Imprime o tabuleiro
            função Erro(int CondRet)
                Imprime o erro(ou sucesso) para o usuario.
        TAB - TABULEIRO.h
            contem as funções de validação dos movimentos no tabuleiro, utilizado para construir as callbacks passadas ao leitor. Tambem possui as funcoes de salvar e carregar o tabuleiro.
            
*/          

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
void volta(tppEstado e){
    GRA_IrVizinhoCorrente(e->Menu,e->UltimoMenu);
}
int main(){
    tppEstado e = CriaEstado();
    
    APR_Erro(MEN_CriarMenu(e->Menus,1,"inicio",volta));
      
    APR_Erro(MEN_CriarOpcao(e->Menus,1,'1',"Criar Mapa",vaiMenu2) ;
    APR_Erro(MEN_CriarOpcao(e->Menus,1,'2',"Jogar",vaiMenu3);
    //inicia a navegacao em 1
    GRA_MudarCorrente(e->Menus,1);
    //só sera 0 quando o ultimo corrente for 1 e o usuario digitar 0
    while(GRA_ObterIdCorrente(e->Menus)!=0){
        APR_ApresentaMenu(e->Menus);
        if(MenuAtual == EDITOR||JOGO)
            APR_ApresentaTabuleiro(e->Tabuleiro);
        LEI_Le();
    }
    //clean(); //housekeeping
    return 0;
}


