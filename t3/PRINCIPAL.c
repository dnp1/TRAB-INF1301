#include "GRAFO.h"
#include "TABULEIRO.h"
#include "LEITOR.h"
#include "ESTADO.h"

/*
 *   Tratamento de Erros
 */
enum modulos{
    PRI,
    LEI,
    TAB
}
void TrataPRI(int CondRet){
    switch(CondRet){
        case PRI_FaltouMemoria:
            printf("Operacao mal sucedida. Faltou Memoria.");
            break;   
            printf("Comando invalido"); 
    }
}
void Erro(char* comm, int CondRet,int module){
    printf("%s",comm);
    if(CondRet == 0)//OK
    {
        printf("OK");
    }
    else
    {    
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
    }
}

/* 
 *    Popula Menus 
 */

void vaiMenu1(tppEstado e,MEN_tppOpcoes opc){ 
    UltimoMenu = 1; 
    GRA_IrVizinho(e->Menus,1); 
}
void vaiMenu2(tppEstado e,MEN_tppOpcoes opc){ 
    UltimoMenu = 2; 
    GRA_IrVizinho(e->Menus,2); 
}
void vaiMenu3(tppEstado e,MEN_tppOpcoes opc){ 
    UltimoMenu = 3; 
    GRA_IrVizinho(e->Menus,3); 
}
void vaiMenu4(tppEstado e,MEN_tppOpcoes opc){ 
    UltimoMenu = 4; 
    GRA_IrVizinho(e->Menus,4); 
}
void carregar(tppEstado e,MEN_tppOpcoes opc){

    TAB le o dir
        p cada arquivo,i 
        char nome[10];
    TAB le o nome

        Erro("Lendo diretorio...", MEN_CriarOpcao(e->Menus,idCarrega,to_char(i),nome,carrega)) ;
    vaiMenuidCarrega(e);

}
void carrega(tppEstado e,MEN_tppOpcao opc){
    e->Tabuleiro = TAB_CriarTabuleiro(); 
    if(e != NULL)
        TAB_carrega(opc->nome);    
}
void deleta(tppEstado e,MEN_tppOpcao opc){

    TAB_Deletar(e->Tabuleiro);
}
void salva(tppEstado e,MEN_tppOpcao opc){
    TAB_Salva()
}
/*
   Tres tipos de retorno: 
   no inicial, que termina o programa
   em um generico, volta para o menu acima
   os que exibem tabuleiro(jogo e editor), que precisam limpar o tabuleiro antes de voltar
 */
void voltainicio(tppEstado e,MEN_tppOpcoes opc){
    e->UltimoMenu = 0;  
    GRA_IrVizinhoCorrente(e->Menu,e->UltimoMenu);
}
void volta(tppEstado e,MEN_tppOpcoes opc){
    int atual = GRA_ObterIdCorrente(e->Menu);
    GRA_IrVizinhoCorrente(e->Menu,e->UltimoMenu);
    e->UltimoMenu = atual;
}
void volta_tab(tppEstado e,MEN_tppOpcoes opc){
    GRA_ExcluirGrafo(e->Tabuleiro);
    volta(e);
}
LEI_tpCondRet validastring(char* s){
    if(strlen(s)<10 && !strcmp(s,""))
        return LEI_CondRetOk;
    else
        return LEI_CondRetInvalido;
}
LEI_tpCondRet validaint(int n){
    if(n>0 && n<11) 
        return LEI_CondRetOk;
    else 
        return LEI_CondRetInvalido;
}
void novo_tab(){
    char* nome[10] = "";
    int alt = 0;
    int lar = 0;
    while(!strcmp(nome,""))
        Erro("Digite o nome (menos de 10 caracteres)",LEI_LeString(nome,validastring));
    while(alt == 0)
        Erro("Digite a altura (1..10)",LEI_LeInt(&alt,validaint));
    while(lar == 0)
        Erro("Digite a largura (1..10)",LEI_LeInt(&lar,validaint));
    tpptab a;
    Erro("Criando tabuleiro",TAB_CriaTab(a,nome, alt,lar));
    Erro("Salvando tabuleiro",TAB_salvaTab(a));
}
void PopulaMenu1(tppEstado e){
    Erro("criando menu inicio", MEN_CriarMenu(e->Menus,1,"inicio",voltainicio));

    Erro("criando opcao 1 de inicio", MEN_CriarOpcao(e->Menus,1,'1',"Criar Mapa",vaiMenu2)) ;
    Erro("criando opcao 2 de inicio", MEN_CriarOpcao(e->Menus,1,'2',"Jogar",vaiMenu3));
}

void PopulaMenus(tppEstado e){
    PopulaMenu1(e);
    //PopulaMenu2(e);

}
/*
 *   Apresenta Dados para o usuario
 */

/*
   Apresenta o Menu corrente
 */
void APR_ApresentaMenu(tppGrafo Menus){
    MEN_tppMenu menu = GRA_ObterCorrente(Menus);
    printf("\n#############\n#  Labirinto  #\n#############");
    printf("\n %s\n--------------",menu->nome);
    printf("Digite:\n\n");
    LIS_IrInicio(menu->opcoes);
    do
    {
        MEN_tppOpcao opcao = LIS_ObterValor(menu->opcoes);
        if(opcao!=NULL)
            printf("\n %c para %s", opcao->cmd,opcao->nome);
    }
    while(LIS_IrProxElemento(menu->opcoes)==LIS_CondRetOK);

}


void ApresentaTabuleiro(tppGrafo Tabuleiro){

}

void ApresentaSolucao(LIS_tppLista solucao){}

/*
 *   Função Principal
 */
int main(){
    tppEstado e = CriaEstado();
    if(e!=NULL)
        PopulaMenus(e);
    //inicia a navegacao em 1
    EST_MenuInicial(e);
    //só sera 0 quando o ultimo corrente for 1 e o usuario digitar 0
    while(EST_MenuCorrente()!=0){
        ApresentaMenu(e->Menus);
        int atual = EST_MenuCorrente();
        if(atual == EDITOR||atual == JOGO)
            ApresentaTabuleiro(e->Tabuleiro);
        Erro("Digite um comando:",LEI_LeCmd(e));
    }
    //clean(); //housekeeping
    return 0;
}


