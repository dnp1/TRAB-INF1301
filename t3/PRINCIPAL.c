#include "TABULEIRO.h"
#include "ESTADO.h"
#include "MENU.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    Tipos internos
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

/*
    Funcoes presentes
*/

static void Erro(char* comm, int CondRet,tpmodulo module);
static void ApresentaMenu(EST_tppEstado e);
static void ApresentaSolucao(EST_tppEstado e);
static void ApresentaTabuleiro(EST_tppEstado e);
/*
 *   Tratamento de Erros
 */


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
PRI_tpCondRet LeCmd(EST_tppEstado e){
    char c; 
    char cmd;
    int id;
    char* opcoes;
    int tam;
    int i;
    MEN_tppMenus ms;
    scanf(" %c",&c);
    EST_GetMenus(e,&ms);
    MEN_MenuCorrente(ms,&id);
    MEN_GetMenuOpcoes(ms,id,&opcoes,&tam);
    for(i=0;i,tam;i++){
        if(opcoes[i] == c){
            Erro("Executando opcao selecionada:",MEN_Callback(ms,id,c,e),MEN);
            return PRI_CondRetOK;
        }    
    
    }
    free(opcoes);
    return PRI_CondRetSemOpcao;         
}

void Msg(char* comm){
    printf("\n== %s\n",comm);
}
/*
valida retorna apenas CondRetOK ou PRI_CondRetInvalido

*/

/*
trunca em 50
*/
PRI_tpCondRet LeString(char** dst, PRI_tpCondRet (*valida)(char* s)){
    char temp[50];
    PRI_tpCondRet cr;
    scanf(" %s",temp);
    cr = valida(temp);
    if(cr == PRI_CondRetOK){
        strcpy(*dst,temp);
    }
    return cr;    
}
PRI_tpCondRet LeInt(int* dst, PRI_tpCondRet (*valida)(int t)){
    int temp;
    PRI_tpCondRet cr;
    scanf(" %d",&temp);
    cr = valida(temp);
    if(cr == PRI_CondRetOK){
        *dst = temp;
    }
    return cr;    
}
void Erro(char* comm, int CondRet,tpmodulo module){
    printf("\n%s ===> ",comm);
    if(CondRet == 0)//OK
    {
        printf("OK");
    }
    else
    {    
	printf("Falhou");     
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
	printf("");     
}
/* 
 *    Popula Menus 
 */

#define JOGO 6 
#define EDITOR 5 
void vaiMenu1(EST_tppEstado e){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,1); 
}
void vaiMenu2(EST_tppEstado e){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,2); 
}
void vaiMenu3(EST_tppEstado e){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,3); 
}
void vaiMenu4(EST_tppEstado e){ 
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,4); 
}
void joga(EST_tppEstado e){ 
    MEN_tppMenus m;
    TAB_tppTabuleiro t;
    EST_GetMenus(e,&m);
    if(EST_GetTabuleiro(e,&t)==EST_CondRetOK)
    {
        TAB_IrInicio(t);
        MEN_MudaMenu(m,JOGO);
    }
}
void edita(EST_tppEstado e){ 
    MEN_tppMenus m;
    TAB_tppTabuleiro t;
    EST_GetMenus(e,&m);
    EST_GetTabuleiro(e,&t);
     
    if(EST_GetTabuleiro(e,&t)==EST_CondRetOK)
    {
        MEN_MudaMenu(m,EDITOR);
    }
}
static void soluciona(EST_tppEstado e){ 
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(EST_GetTabuleiro(e,&t)==EST_CondRetOK)
    {
        ApresentaSolucao(e); 
    }
}
/*
void carregar(EST_tppEstado e){

    TAB le o dir
        p cada arquivo,i 
        char nome[10];
    TAB le o nome
*
        Erro("Lendo diretorio...", MEN_CriarOpcao(EST_GetMenus(e),idCarrega,to_char(i),nome,carrega),MEN) ;
    vaiMenuidCarrega(e);

}
*/
void carrega(EST_tppEstado e){
    //EST_AlterarTabuleiro(e,TAB_CriarTabuleiro()); 
    //if(e != NULL)
    //    TAB_carrega(MEN_GetNomeOpcao(opc));    
}
void deleta(EST_tppEstado e){
//    TAB_Deletar(EST_GetTabuleiro(e));
}
void salva(EST_tppEstado e){
    TAB_tppTabuleiro t;
    char* nome;
    EST_GetTabuleiro(e,&t);
    if(t!=NULL)
        Erro("Salvando tabuleiro",TAB_SalvarTabuleiro(t,nome),TAB);
    else 
       Msg("nao existe atual");
}
void andadireditor(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraDireita(t,0)==TAB_CondRetOK)
        TAB_AndarPraDireita(t);
}
void andaesqeditor(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraEsquerda(t,0)==TAB_CondRetOK)
        TAB_AndarPraEsquerda(t);
}
void andabaixoeditor(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraBaixo(t,0)==TAB_CondRetOK)
        TAB_AndarPraBaixo(t);
}
void andacimaeditor(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraCima(t,0)==TAB_CondRetOK)
        TAB_AndarPraCima(t);
}
/*
*   Checa Vitoria
*   verifica se o usuário, durante o jogo, solucionou o labirinto. Caso afirmativo,retorna para o menu acima. 
*/
void ChecaVitoria(EST_tppEstado e){  
    TAB_tppTabuleiro t;
    MEN_tppMenus m;
    int x,y;
    TAB_tpCasa casa;
    EST_GetTabuleiro(e,&t);
    EST_GetMenus(e,&m);
	TAB_PosicaoJogador(t,&x,&y);
	TAB_GetTipoCasa(t,x,y,&casa);
    if(casa == TAB_tpCasaFim){ 
        Msg("Voce ganhou!!!");
        MEN_MudaMenu(m,4);
        //4 é o pai de JOGO 
    }
}
void andadirjogador(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraDireita(t,1)==TAB_CondRetOK){
        TAB_AndarPraDireita(t);
        ChecaVitoria(e);
    }
}
void andaesqjogador(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraEsquerda(t,1)==TAB_CondRetOK){
        TAB_AndarPraEsquerda(t);
        ChecaVitoria(e);
    }
}
void andabaixojogador(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraBaixo(t,1)==TAB_CondRetOK){
        TAB_AndarPraBaixo(t);
        ChecaVitoria(e);
    }
}
void andacimajogador(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    if(TAB_PodeAndarPraCima(t,1)==TAB_CondRetOK){
        TAB_AndarPraCima(t);
        ChecaVitoria(e);
    }
}

void poefim(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    TAB_PoeFim(t);
}
void poeinicio(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    TAB_PoeInicio(t);
}
void poechao(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    TAB_PoeChao(t);
}

void poeparede(EST_tppEstado e){
    TAB_tppTabuleiro t;
    EST_GetTabuleiro(e,&t);
    TAB_PoeParede(t);
}
/*
   Tres tipos de retorno: 
   no inicial, que termina o programa
   em um generico, volta para o menu acima
   os que exibem tabuleiro(jogo e editor), que precisam limpar o tabuleiro antes de voltar
    Mudar para nao usar GRAxxx

 */

PRI_tpCondRet validastring(char* s){
    if(strlen(s)<10){
        if(strcmp(s,"")){
            return PRI_CondRetOK;
        }
        else{
            return PRI_CondRetInvalido;
        }
    }
    else{
        return PRI_CondRetInvalido;
    }
}
PRI_tpCondRet validaint(int n){
    if(n>=0 && n<11) 
        return PRI_CondRetOK;
    else 
        return PRI_CondRetInvalido;
}

void novo_tab(EST_tppEstado e){
    char* nome = malloc(sizeof(char)*10);
    MEN_tppMenus m;
    TAB_tppTabuleiro a;
    int alt = -1;
    int lar = -1;
    char* saida;
    while(alt == -1){
        Msg("Digite a altura (1..10) ou 0 para voltar");
        Erro("validando:",LeInt(&alt,validaint),PRI);
        if(alt == 0){
            Msg("cancelando operacao");
             return;
        }
    }
    while(lar == -1){
        Msg("Digite a largura (1..10) ou 0 para voltar");
        Erro("validando:",LeInt(&lar,validaint),PRI);
        if(lar == 0){
            Msg("cancelando operacao");
             return;
        }
    }
    while(!strcmp(nome,"")){
        Msg("Digite o nome (menos de 10 caracteres) ou 0 para voltar");
        Erro("validando:",LeString(&nome,validastring),PRI);
        if(!strcmp(nome,"0")){
            Msg("cancelando operacao");
             return;
        }
    }
    
    if(EST_GetTabuleiro(e,&a)==EST_CondRetOK)
        TAB_DestruirTabuleiro(a);
    Erro("Criando tabuleiro",TAB_CriarTabuleiro(&a,alt,lar,nome),TAB);
    EST_SetTabuleiro(e,a);
    //Erro("Salvando tabuleiro",TAB_SalvarTabuleiro(a,nome),TAB);
    
    EST_GetMenus(e,&m);
    MEN_MudaMenu(m,EDITOR); 
}

void PopulaMenuInicio(EST_tppEstado e){
    int idMenu = 1;
    int idPai = 0;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando menu Inicio", MEN_CriarMenu(m,idMenu,"Inicio",idPai),MEN);

    Erro("criando opcao 1 de Inicio", MEN_CriarOpcao(m,1,'1',"Editor",vaiMenu2),MEN) ;
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
    Erro("criando opcao 2 de Editor", MEN_CriarOpcao(m,2,'2',"Novo",novo_tab),MEN);
    Erro("criando opcao 3 de Editor", MEN_CriarOpcao(m,idMenu,'3',"Deletar",deleta),MEN);
    Erro("criando opcao 4 de Editor", MEN_CriarOpcao(m,idMenu,'4',"Editar atual",edita),MEN) ;
}
void PopulaMenuResolvedor(EST_tppEstado e){
    int idMenu = 3;
    int idPai = 1;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando menu Resolvedor", MEN_CriarMenu(m,idMenu,"Resolvedor",idPai),MEN);

    Erro("criando opcao 1 de Resolvedor", MEN_CriarOpcao(m,idMenu,'1',"Carregar",carrega),MEN);
    Erro("criando opcao 2 de Resolvedor", MEN_CriarOpcao(m,idMenu,'2',"Solucionar atual",soluciona),MEN) ;
}
void PopulaMenuJogar(EST_tppEstado e){
    int idMenu = 4;
    int idPai = 1;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando menu Jogar", MEN_CriarMenu(m,idMenu,"Jogar",idPai),MEN);

    Erro("criando opcao 1 de Jogar", MEN_CriarOpcao(m,idMenu,'1',"Jogar atual",joga),MEN) ;
    Erro("criando opcao 2 de Jogar", MEN_CriarOpcao(m,idMenu,'2',"Carregar",carrega),MEN) ;
}
void PopulaMenuEdicao(EST_tppEstado e){
    int idMenu = EDITOR;
    int idPai = 2;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando Editor", MEN_CriarMenu(m,idMenu,"Edicao",idPai),MEN);

    Erro("criando opcao 1 de Edicao", MEN_CriarOpcao(m,idMenu,'w',"andar para cima",andacimaeditor),MEN) ;
    Erro("criando opcao 2 de Edicao", MEN_CriarOpcao(m,idMenu,'s',"andar para baixo",andabaixoeditor),MEN) ;
    Erro("criando opcao 3 de Edicao", MEN_CriarOpcao(m,idMenu,'a',"andar para esquerda",andaesqeditor),MEN) ;
    Erro("criando opcao 4 de Edicao", MEN_CriarOpcao(m,idMenu,'d',"andar para direita",andadireditor),MEN) ;
    Erro("criando opcao 5 de Edicao", MEN_CriarOpcao(m,idMenu,'1',"por parede",poeparede),MEN) ;
    Erro("criando opcao 6 de Edicao", MEN_CriarOpcao(m,idMenu,'2',"por chao",poechao),MEN) ;
    Erro("criando opcao 7 de Edicao", MEN_CriarOpcao(m,idMenu,'3',"por inicio",poeinicio),MEN) ;
    Erro("criando opcao 8 de Edicao", MEN_CriarOpcao(m,idMenu,'4',"por fim",poefim),MEN) ;
    Erro("criando opcao 9 de Edicao", MEN_CriarOpcao(m,idMenu,'5',"salvar",salva),MEN) ;
    Erro("criando opcao 10 de Edicao", MEN_CriarOpcao(m,idMenu,'6',"jogar",joga),MEN) ;
}
void PopulaMenuJogo(EST_tppEstado e){
    int idMenu = JOGO;
    int idPai = 4;
    MEN_tppMenus m;
    EST_GetMenus(e,&m);
    Erro("criando Jogo", MEN_CriarMenu(m,idMenu,"Jogo",idPai),MEN);

    Erro("criando opcao 1 de Jogo", MEN_CriarOpcao(m,idMenu,'w',"andar para cima",andacimajogador),MEN) ;
    Erro("criando opcao 2 de Jogo", MEN_CriarOpcao(m,idMenu,'s',"andar para baixo",andabaixojogador),MEN) ;
    Erro("criando opcao 3 de Jogo", MEN_CriarOpcao(m,idMenu,'a',"andar para esquerda",andaesqjogador),MEN) ;
    Erro("criando opcao 4 de Jogo", MEN_CriarOpcao(m,idMenu,'d',"andar para direita",andadirjogador),MEN) ;
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
    PopulaMenuEdicao(e);
    PopulaMenuJogo(e);
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
    int id;
    char* nome;
    char* nomeopc;
    char* tab;
    TAB_tppTabuleiro t;
    char* opc;
    int tam;
    int i;
    MEN_tppMenus ms;
    EST_GetMenus(e,&ms);
    EST_GetTabuleiro(e,&t);    
	/*
	if(t!=NULL)
        TAB_GetNome(t,&tab);
    else
	*/
        tab = "Nao existe";
    MEN_MenuCorrente(ms,&id);
    MEN_GetMenuOpcoes(ms,id,&opc,&tam);
    MEN_GetMenuNome(ms,id,&nome);
    printf("\n###############\n#  Labirinto  #\n###############");
    printf("\nmenu: %s\nlabirinto atual: %s\n------------",nome,tab);
    printf("\nDigite:\n\n");
    for(i=0;i<tam;i++){
       MEN_GetOpcaoNome(ms,id,opc[i],&nomeopc);
       printf("\n %c para %s", opc[i],nomeopc);
    }
    free(opc);

    printf("\n--------------\n");

}


void ApresentaTabuleiro(EST_tppEstado e){
	TAB_tppTabuleiro Tabuleiro; 
	int a,l,i,j,jx,jy;
    TAB_tpCasa casa;
    EST_GetTabuleiro(e,&Tabuleiro);
	TAB_GetAltura(Tabuleiro,&a);
	TAB_GetLargura(Tabuleiro,&l);
	TAB_PosicaoJogador(Tabuleiro,&jx,&jy);
    for(i=0;i<a;i++){
	    for(j=0;j<l;j++){
	       TAB_GetTipoCasa(Tabuleiro,j,i,&casa);
               //posicao do jogador
               if(j==jx && i==jy){
                   printf("O");    
               }
               else{
		       //printf("%d",casa);
               
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
    free(solucao);
}
/*
 *   Função Principal
 */
int main(){
    int atual;
    EST_tppEstado e;
    EST_tpCondRet cr1;
    PRI_tpCondRet cr2;
    MEN_tppMenus menus;
    cr1 = EST_CriaEstado(&e);
    Erro("Alocando Estado",cr1,EST);
    if(cr1==EST_CondRetOK){
        cr2 = PopulaMenus(e);
        Erro("Populando Menus",cr2,PRI);
    }
    if(cr1 != EST_CondRetOK || cr2 != PRI_CondRetOK){
        return 0;
    }
    
    EST_GetMenus(e,&menus);
    //inicia a navegacao em 1
    MEN_MenuInicial(menus);
    //só sera 0 quando o ultimo corrente for 1 e o usuario digitar 0
    
    MEN_MenuCorrente(menus,&atual);
    while(atual!=0){
        ApresentaMenu(e);
        if(atual == EDITOR||atual == JOGO){
            ApresentaTabuleiro(e);
        }
        Erro("Comando:",LeCmd(e),PRI);
        EST_GetMenus(e,&menus);
        MEN_MenuCorrente(menus,&atual);
    }
    EST_DestruirEstado(e);
    return 0;
}


