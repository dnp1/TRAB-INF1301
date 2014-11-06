#include "TABULEIRO.h"
#include "ESTADO.h"
#include "MENU.h"
#include "LISTA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 *   Tratamento de Erros
 */

typedef enum{
    PRI,
    TAB,
    EST,
    MEN
} tpmodulo;
typedef enum{
    PRI_CondRetOK,
    PRI_CondRetInvalido,
    PRI_CondRetSemOpcao         
} PRI_tpCondRet;

void Erro(char* comm, int CondRet,tpmodulo module);
/*
void TrataPRI(int CondRet){
    switch(CondRet){
        case FaltouMemoria:
            printf("Operacao mal sucedida. Faltou Memoria.");
            break;   
            printf("Comando invalido"); 
    }
}
*/
/*
    Tratamento de input
*/
/* 
mudar de lis->gra
*/
PRI_tpCondRet LeCmd(EST_tppEstado e){
    char c; 
    char cmd;
    int* id;
    LIS_tppLista opcoes;
    MEN_tppMenus ms;
    scanf(" %c ",&c);
    EST_GetMenus(e,&ms);
    MEN_MenuCorrente(ms,id);
    MEN_GetMenuOpcoes(ms,*id,opcoes);
    LIS_IrInicioLista(opcoes);
    do
    {
        MEN_tppOpcao opcao = LIS_ObterValor(opcoes);
        Erro("Comando selecionado\n",MEN_GetOpcaoCmd(opcao,&cmd),MEN);
        if(cmd == c){
            Erro("Executando opcao selecionada\n",MEN_Callback(opcao,e),MEN);
            return PRI_CondRetOK;
        }    
    }
    while(LIS_AvancarElementoCorrente(opcoes,1)==LIS_CondRetOK);
  
    return PRI_CondRetSemOpcao;         
}

/*
valida retorna apenas CondRetOK ou PRI_CondRetInvalido

*/

/*
trunca em 50
*/
PRI_tpCondRet LeString(char* dst, PRI_tpCondRet (*valida)(char* s)){
    char temp[50];
    scanf(" %s ",temp);
    PRI_tpCondRet cr = valida(temp);
    if(cr == PRI_CondRetOK){
        strcpy(dst,temp);
    }
    return cr;    
}
PRI_tpCondRet LeInt(int* dst, PRI_tpCondRet (*valida)(int t)){
    int temp;
    scanf(" %d ",&temp);
    PRI_tpCondRet cr = valida(temp);
    if(cr == PRI_CondRetOK){
        *dst = temp;
    }
    return cr;    
}
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
            case PRI:
                trataPRI(CondRet);
                break;
        }*/
    }
}

/* 
 *    Popula Menus 
 */

void vaiMenu1(EST_tppEstado e,MEN_tppOpcao opc){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,1); 
}
void vaiMenu2(EST_tppEstado e,MEN_tppOpcao opc){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,2); 
}
void vaiMenu3(EST_tppEstado e,MEN_tppOpcao opc){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,3); 
}
void vaiMenu4(EST_tppEstado e,MEN_tppOpcao opc){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,4); 
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
//    TAB_Deletar(EST_GetTabuleiro(e));
}
void salva(EST_tppEstado e,MEN_tppOpcao opc){
//    TAB_Salva(e);
}

/*
   Tres tipos de retorno: 
   no inicial, que termina o programa
   em um generico, volta para o menu acima
   os que exibem tabuleiro(jogo e editor), que precisam limpar o tabuleiro antes de voltar
    Mudar para nao usar GRAxxx

 */

PRI_tpCondRet validastring(char* s){
    if(strlen(s)<10 && !strcmp(s,""))
        return PRI_CondRetOK;
    else
        return PRI_CondRetInvalido;
}
PRI_tpCondRet validaint(int n){
    if(n>0 && n<11) 
        return PRI_CondRetOK;
    else 
        return PRI_CondRetInvalido;
}
//TODO:recomendacoes de ux do flavio

void novo_tab(EST_tppEstado e){
    char nome[10] = "";
    int alt = 0;
    int lar = 0;
    while(!strcmp(nome,""))
        Erro("Digite o nome (menos de 10 caracteres)",LeString(nome,validastring),PRI);
    while(alt == 0)
        Erro("Digite a altura (1..10)",LeInt(&alt,validaint),PRI);
    while(lar == 0)
        Erro("Digite a largura (1..10)",LeInt(&lar,validaint),PRI);
    TAB_tppTabuleiro a;
    EST_GetTabuleiro(e,&a);
    //Erro("Criando tabuleiro",TAB_CriaTab(a,nome, alt,lar),TAB);
    //Erro("Salvando tabuleiro",TAB_salvaTab(a),TAB);
}

void PopulaMenuInicio(EST_tppEstado e){
    int idMenu = 1;
    int idPai = 0;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando menu Inicio", MEN_CriarMenu(m,idMenu,"Inicio",idPai),MEN);

    Erro("criando opcao idMenu de Inicio", MEN_CriarOpcao(m,1,'1',"Editor",vaiMenu2),MEN) ;
    Erro("criando opcao 2 de Inicio", MEN_CriarOpcao(m,idMenu,'2',"Resolvedor",vaiMenu3),MEN);
    Erro("criando opcao 3 de Inicio", MEN_CriarOpcao(m,idMenu,'3',"Jogar",vaiMenu4),MEN);
}

void PopulaMenuEditor(EST_tppEstado e){
    int idMenu = 2;
    int idPai = 1;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando menu Editor", MEN_CriarMenu(m,idMenu,"Editor",idPai),MEN);

    Erro("criando opcao 1 de Editor", MEN_CriarOpcao(m,idMenu,'1',"Carregar",carrega),MEN) ;
    Erro("criando opcao idMenu de Editor", MEN_CriarOpcao(m,2,'2',"Novo",novo_tab),MEN);
    Erro("criando opcao 3 de Editor", MEN_CriarOpcao(m,idMenu,'3',"Deletar",deleta),MEN);
}
void PopulaMenuResolvedor(EST_tppEstado e){
    int idMenu = 3;
    int idPai = 1;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando menu Resolvedor", MEN_CriarMenu(m,idMenu,"Resolvedor",idPai),MEN);

    Erro("criando opcao 1 de Resolvedor", MEN_CriarOpcao(m,idMenu,'1',"Carregar",carrega),MEN) ;
}
void PopulaMenuJogar(EST_tppEstado e){
    int idMenu = 4;
    int idPai = 1;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando menu Jogar", MEN_CriarMenu(m,idMenu,"Jogar",idPai),MEN);

    Erro("criando opcao 1 de Jogar", MEN_CriarOpcao(m,idMenu,'1',"Carregar",carrega),MEN) ;
}
//housekeeping
//tpCondRet
PRI_tpCondRet PopulaMenus(EST_tppEstado e){
    MEN_tppMenus menus;
    MEN_CriarMenus(&menus);
    EST_SetMenus(e,menus);
    PopulaMenuInicio(e);
    PopulaMenuEditor(e);
    PopulaMenuResolvedor(e);
    PopulaMenuJogar(e);
    return PRI_CondRetOK;
}
/*
 *   Apresenta Dados para o usuario
 */

/*
   Apresenta o Menu corrente
 */
void ApresentaMenu(EST_tppEstado e){
    char cmd;
    int* id;
    char* nome;
    char* nomeopc;
    LIS_tppLista opc;
    MEN_tppMenus ms;
    EST_GetMenus(e,&ms);
    MEN_MenuCorrente(ms,id);
    MEN_GetMenuOpcoes(ms,*id,opc);
    MEN_GetMenuNome(ms,*id,nome);
    printf("\n#############\n#  Labirinto  #\n#############");
    printf("\n %s\n--------------",nome);
    printf("Digite:\n\n");
    LIS_IrInicioLista(opc);
    do
    {
        MEN_tppOpcao opcao = LIS_ObterValor(opc);
        if(opcao!=NULL){
            MEN_GetOpcaoCmd(opcao,&cmd);
            MEN_GetOpcaoNome(opcao,nomeopc);
            printf("\n %c para %s", cmd,nomeopc);
        }
    }
    while(LIS_AvancarElementoCorrente(opc,1)==LIS_CondRetOK);


}


void ApresentaTabuleiro(EST_tppEstado e){
	TAB_tppTabuleiro Tabuleiro; 
	int a,l,i,j,jx,jy;
    EST_GetTabuleiro(e,&Tabuleiro);
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

void ApresentaSolucao(EST_tppEstado e){
    int * solucao;
    int tam;
    int i;
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    TAB_SolucionarTabuleiro(t,&solucao,&tam);
    for(i=0;i<tam;i+=2){
        printf("Passo %d: (x,y) -> (%d,%d)\n",(i/2)+1,solucao[i],solucao[i+1]);    
    }
}

/*
 *   Função Principal
 */
#define JOGO 1
#define EDITOR 2
int main(){
    int atual;
    EST_tppEstado e;
    MEN_tppMenus menus;
    Erro("Alocando Estado",EST_CriaEstado(&e),EST);
    if(e!=NULL){
        PRI_tpCondRet cr = PopulaMenus(e);
        Erro("Populando Menus",cr,PRI);
        if(cr!=PRI_CondRetOK)
            return 0;
    }
    else{
        return 0;
    }
    
    EST_GetMenus(e,&menus);
    //inicia a navegacao em 1
    MEN_MenuInicial(menus);
    //só sera 0 quando o ultimo corrente for 1 e o usuario digitar 0
    
    MEN_MenuCorrente(menus,&atual);
    while(atual!=0){
        ApresentaMenu(e);
        if(atual == EDITOR||atual == JOGO)
            ApresentaTabuleiro(e);
        Erro("Digite um comando:",LeCmd(e),PRI);
        MEN_MenuCorrente(menus,&atual);
    }
    EST_DestruirEstado(e);
    return 0;
}


