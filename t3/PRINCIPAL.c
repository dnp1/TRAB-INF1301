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
/*
    TAB le o dir
        p cada arquivo,i 
        char nome[10];
    TAB le o nome
*/
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
    Mudar para nao usar GRAxxx

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
void PopulaMenuInicio(tppEstado e){
    int idMenu = 1;
    Erro("criando menu Inicio", MEN_CriarMenu(e->Menus,idMenu,"Inicio",voltainicio));

    Erro("criando opcao idMenu de Inicio", MEN_CriarOpcao(e->Menus,1,'1',"Editor",vaiMenu2)) ;
    Erro("criando opcao 2 de Inicio", MEN_CriarOpcao(e->Menus,idMenu,'2',"Resolvedor",vaiMenu3));
    Erro("criando opcao 3 de Inicio", MEN_CriarOpcao(e->Menus,idMenu,'3',"Jogar",vaiMenu4));
}

void PopulaMenuEditor(tppEstado e){
    int idMenu = 2;
    Erro("criando menu Editor", MEN_CriarMenu(e->Menus,idMenu,"Editor",volta));

    Erro("criando opcao 1 de Editor", MEN_CriarOpcao(e->Menus,idMenu,'1',"Carregar",carrega)) ;
    Erro("criando opcao idMenu de Editor", MEN_CriarOpcao(e->Menus,2,'2',"Novo",novo_tab));
    Erro("criando opcao 3 de Editor", MEN_CriarOpcao(e->Menus,idMenu,'3',"Deletar",deleta));
}
void PopulaMenuResolvedor(tppEstado e){
    int idMenu = 3;
    Erro("criando menu Resolvedor", MEN_CriarMenu(e->Menus,idMenu,"Resolvedor",volta));

    Erro("criando opcao 1 de Resolvedor", MEN_CriarOpcao(e->Menus,idMenu,'1',"Carregar",carrega)) ;
}
void PopulaMenuJogar(tppEstado e){
    int idMenu = 4;
    Erro("criando menu Jogar", MEN_CriarMenu(e->Menus,idMenu,"Jogar",volta));

    Erro("criando opcao 1 de Jogar", MEN_CriarOpcao(e->Menus,idMenu,'1',"Carregar",carrega)) ;
}
void PopulaMenus(tppEstado e){
    PopulaMenuInicio(e);
    PopulaMenuEditor(e);
    PopulaMenuResolvedor(e);
    PopulaMenuJogar(e);
    
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


void ApresentaTabuleiro(TAB_tppTabuleiro Tabuleiro){
	int a,l,i,j,jx,jy;
	a = TAB_GetAltura(Tabuleiro);
	l = TAB_GetLargura(Tabuleiro);
	TAB_PosicaoJogador(Tabuleiro,&i,&j);
	for(i=0;i<a;i++){
	    for(j=0;j<l;j++){
               TAB_tpCasa casa;
	       TAB_GetTipoCasa(Tabuleiro,i,j,&casa);
               //posicao do jogador
               if(i==jx && j==jy){
                   printf("O");    
               }
               else{
		       if(casa==TAB_tpCasaInicio) printf("I"); 
		       else if(casa==TAB_tpCasaFim) printf("F"); 
		       else if(casa==TAB_tpCasaChao) printf(" "); 
		       else if(casa==TAB_tpCasaParede) printf("#"); 
               }
            }	
            printf("\n");
	}
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


