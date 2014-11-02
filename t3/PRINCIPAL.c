#include "TABULEIRO.h"
#include "LEITOR.h"
#include "ESTADO.h"
#include "MENU.h"
#include <stdio.h>
#include <stdlib.h>
/*
 *   Tratamento de Erros
 */

typedef enum{
    PRI,
    LEI,
    TAB,
    MEN
} tpmodulo;
void Erro(char* comm, int CondRet,tpmodulo module);
/*
void TrataPRI(int CondRet){
    switch(CondRet){
        case PRI_FaltouMemoria:
            printf("Operacao mal sucedida. Faltou Memoria.");
            break;   
            printf("Comando invalido"); 
    }
}
*/
void Erro(char* comm, int CondRet,tpmodulo module){
    printf("%s",comm);
    if(CondRet == 0)//OK
    {
        printf("OK");
    }
    else
    {    
	printf("falhou");     
/*   switch (module){
            case PRI:
                trataPRI(CondRet);
                break;
            case TAB:
                trataTAB(CondRet);
                break;
            case LEI:
                trataLEI(CondRet);
                break;
        }*/
    }
}

/* 
 *    Popula Menus 
 */

void vaiMenu1(EST_tppEstado e,MEN_tppOpcao opc){ 
    EST_MudaUltimoMenu(1); 
    MEN_MudaMenu(EST_GetMenus(e),1); 
}
void vaiMenu2(EST_tppEstado e,MEN_tppOpcao opc){ 
    EST_MudaUltimoMenu(2); 
    MEN_MudaMenu(EST_GetMenus(e),2); 
}
void vaiMenu3(EST_tppEstado e,MEN_tppOpcao opc){ 
    EST_MudaUltimoMenu(3); 
    MEN_MudaMenu(EST_GetMenus(e),3); 
}
void vaiMenu4(EST_tppEstado e,MEN_tppOpcao opc){ 
    EST_MudaUltimoMenu(4); 
    MEN_MudaMenu(EST_GetMenus(e),4); 
}
/*
void carregar(EST_tppEstado e,MEN_tppOpcao opc){

    TAB le o dir
        p cada arquivo,i 
        char nome[10];
    TAB le o nome
*
        Erro("Lendo diretorio...", MEN_CriarOpcao(EST_GetMenus(e),idCarrega,to_char(i),nome,carrega),MEN) ;
    vaiMenuidCarrega(e);

}
*/
void carrega(EST_tppEstado e,MEN_tppOpcao opc){
    //EST_AlterarTabuleiro(e,TAB_CriarTabuleiro()); 
    //if(e != NULL)
    //    TAB_carrega(MEN_GetNomeOpcao(opc));    
}
void deleta(EST_tppEstado e,MEN_tppOpcao opc){
    TAB_Deletar(EST_GetTabuleiro(e));
}
void salva(EST_tppEstado e,MEN_tppOpcao opc){
    TAB_Salva(e);
}

/*
   Tres tipos de retorno: 
   no inicial, que termina o programa
   em um generico, volta para o menu acima
   os que exibem tabuleiro(jogo e editor), que precisam limpar o tabuleiro antes de voltar
    Mudar para nao usar GRAxxx

 */

LEI_tpCondRet validastring(char* s){
    if(strlen(s)<10 && !strcmp(s,""))
        return LEI_CondRetOK;
    else
        return LEI_CondRetInvalido;
}
LEI_tpCondRet validaint(int n){
    if(n>0 && n<11) 
        return LEI_CondRetOK;
    else 
        return LEI_CondRetInvalido;
}
//TODO:recomendacoes de ux do flavio

void novo_tab(){
    char nome[10] = "";
    int alt = 0;
    int lar = 0;
    while(!strcmp(nome,""))
        Erro("Digite o nome (menos de 10 caracteres)",LEI_LeString(nome,validastring),LEI);
    while(alt == 0)
        Erro("Digite a altura (1..10)",LEI_LeInt(&alt,validaint),LEI);
    while(lar == 0)
        Erro("Digite a largura (1..10)",LEI_LeInt(&lar,validaint),LEI);
    TAB_tppTabuleiro a;
    Erro("Criando tabuleiro",TAB_CriaTab(a,nome, alt,lar),TAB);
    Erro("Salvando tabuleiro",TAB_salvaTab(a),TAB);
}

void PopulaMenuInicio(EST_tppEstado e){
    int idMenu = 1;
    int idPai = 0;
    Erro("criando menu Inicio", MEN_CriarMenu(EST_GetMenus(e),idMenu,"Inicio",idPai),MEN);

    Erro("criando opcao idMenu de Inicio", MEN_CriarOpcao(EST_GetMenus(e),1,'1',"Editor",vaiMenu2),MEN) ;
    Erro("criando opcao 2 de Inicio", MEN_CriarOpcao(EST_GetMenus(e),idMenu,'2',"Resolvedor",vaiMenu3),MEN);
    Erro("criando opcao 3 de Inicio", MEN_CriarOpcao(EST_GetMenus(e),idMenu,'3',"Jogar",vaiMenu4),MEN);
}

void PopulaMenuEditor(EST_tppEstado e){
    int idMenu = 2;
    int idPai = 1;
    Erro("criando menu Editor", MEN_CriarMenu(EST_GetMenus(e),idMenu,"Editor",idPai),MEN);

    Erro("criando opcao 1 de Editor", MEN_CriarOpcao(EST_GetMenus(e),idMenu,'1',"Carregar",carrega),MEN) ;
    Erro("criando opcao idMenu de Editor", MEN_CriarOpcao(EST_GetMenus(e),2,'2',"Novo",novo_tab),MEN);
    Erro("criando opcao 3 de Editor", MEN_CriarOpcao(EST_GetMenus(e),idMenu,'3',"Deletar",deleta),MEN);
}
void PopulaMenuResolvedor(EST_tppEstado e){
    int idMenu = 3;
    int idPai = 1;
    Erro("criando menu Resolvedor", MEN_CriarMenu(EST_GetMenus(e),idMenu,"Resolvedor",idPai),MEN);

    Erro("criando opcao 1 de Resolvedor", MEN_CriarOpcao(EST_GetMenus(e),idMenu,'1',"Carregar",carrega),MEN) ;
}
void PopulaMenuJogar(EST_tppEstado e){
    int idMenu = 4;
    int idPai = 1;
    Erro("criando menu Jogar", MEN_CriarMenu(EST_GetMenus(e),idMenu,"Jogar",idPai),MEN);

    Erro("criando opcao 1 de Jogar", MEN_CriarOpcao(EST_GetMenus(e),idMenu,'1',"Carregar",carrega),MEN) ;
}
void PopulaMenus(EST_tppEstado e){
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
void APR_ApresentaMenu(EST_tppEstado e){
    MEN_tppMenu Menus = EST_GetMenus(e);
    printf("\n#############\n#  Labirinto  #\n#############");
    printf("\n %s\n--------------",MEN_GetMenuNome(Menus));
    printf("Digite:\n\n");
    LIS_tppLista opc = MEN_GetMenuOpcoes(Menus);
    LIS_IrInicio(opc);
    do
    {
        MEN_tppOpcao opcao = LIS_ObterValor(opc);
        if(opcao!=NULL)
            printf("\n %c para %s",  MEN_GetOpcaoCmd(opcao),MEN_GetOpcaoNome(opcao));
    }
    while(LIS_IrProxElemento(opc)==LIS_CondRetOK);

}


void ApresentaTabuleiro(EST_tppEstado e){
	TAB_tppTabuleiro Tabuleiro = EST_GetTabuleiro(e);
	int a,l,i,j,jx,jy;
	TAB_GetAltura(Tabuleiro,&a);
	TAB_GetLargura(Tabuleiro,&l);
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
#define JOGO 1
#define EDITOR 2
int main(){
    EST_tppEstado e = EST_CriaEstado();
    if(e!=NULL)
        PopulaMenus(e);
    //inicia a navegacao em 1
    EST_MenuInicial(e);
    //só sera 0 quando o ultimo corrente for 1 e o usuario digitar 0
    while(EST_MenuCorrente()!=0){
        ApresentaMenu(e);
        int atual = EST_MenuCorrente();
        if(atual == EDITOR||atual == JOGO)
            ApresentaTabuleiro(e);
        Erro("Digite um comando:",LEI_LeCmd(e),LEI);
    }
    //clean(); //housekeeping
    return 0;
}


