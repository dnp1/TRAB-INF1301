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
        int id
        void callback*(void)
        
    Este módulo utiliza outros 3 módulos:
        LEI - LEITOR.h     
            função Le() 
                Le um caracter numerico(id da opção)  e executa a funcao associada ao mesmo em opção. 
            função Joga()
                
        APR - APRESENTADOR.h
            função ApresentaMenu()
                Apresenta uma tela contendo o nome do menu atual, suas opções com seus ids.
                Se estiver na tela de jogo ou edição de mapa, desenha o mapa.
            função ApresentaEditor()
                Apresenta uma tela com os comandos validos e o estado atual do mapa sendo editado.
            função ApresentaJogo()
                A diferença esta nos comandos validos, pois neste momento o jogador nao pode mudar a configuracao do mapa.
        TAB - TABULEIRO.h
            contem as funções de validação dos movimentos no tabuleiro, utilizado para construir as callbacks passadas ao leitor. Tambem possui as funcoes de salvar e carregar o tabuleiro.
            
*/          
void vaiMenu(int n){
    MenuAtual = n;
}
 static int MenuAtual;
int main(){
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
    //acho legal uma CriarMenu e uma CriarOpcao    
    /*
    Inicializa os menus(exemplo)
    MenuAtual = 1;
    //MenuAtual = 0 acaba o jogo.
    while(MenuAtual != 0){
        LEI_Le();
        if(MenuAtual == EDITOR)
            APR_ApresentaEditor();
        if(MenuAtual == JOGO)
            APR_ApresentaJogo();
        else
            APR_ApresentaMenu();
    }
    clean()
    */
    return 0;
}


/*

este exemplo apresenta algo como

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

