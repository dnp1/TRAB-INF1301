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
            não pode haver mais de 9 opcoes
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
void vaiMenu(int n){
    GRA_IrVizinho();
    //MenuAtual = n;
}



PRI_CondRet MEN_CriarMenu(tppGrafo menu, int id, char* nome){
    
};
PRI_CondRet MEN_CriarOpcao(tppGrafo menu, int idMenu,char cmd, char* nome,callback);


int main(){
    
    GRA_tppGrafo Menus;
    APR_Erro(MEN_CriarMenu(Menus,1,"inicio"));
      
    APR_Erro(MEN_CriarOpcao(Menus,1,'1',"Criar Mapa",vaiMenu(2)) ;
    APR_Erro(MEN_CriarOpcao(Menus,1,'2',"Jogar",vaiMenu(3));

    /*
    menu->nome = "inicio";
    menu->id = 1;
    menu->opcoes = CriarLista();
    opcao* a = malloc
    a->id = 1
    a->callback() = vaiMenu(2);//isso nao eh valido, mas eh essa ideia, com macros talvez role
    a->nome = "Criar mapa";
    opcao* b = malloc
    b->id = 2
    b->callback() = vaiMenu(3);//isso nao eh valido, mas eh essa ideia, com macros talvez role
    b->nome = "Jogar";
    Inserir(menu->opcoes,a);    
    Inserir(menu->opcoes,b);
    */ 
    //Inicializa os menus(exemplo)
    while(){//Se o corrente for ...
        LEI_Le();
        APR_ApresentaMenu(Menus);
        if(MenuAtual == EDITOR||JOGO)
            APR_ApresentaTabuleiro(Tabuleiro);
    }
    //clean(); //housekeeping
    return 0;
}


/*

este exemplo apresenta algo como
---------

Menu criado com sucesso!
Opcao criada com sucesso!
Opcao criada com sucesso!


###############
# labiririnto #
###############

inicio
------

Aperte 
0 para Voltar(se estiver em inicio, fecha o jogo)
1 para Criar Mapa
2 para Jogar 

#############################

*/

