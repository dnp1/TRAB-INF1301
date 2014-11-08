#if ! defined ( ESTADO_ )
#define ESTADO_

/***************************************************************************
*
*  $MCD Módulo de definição: EST Menus
*
*  Arquivo gerado:              MENU.h
*  Letras identificadoras:      EST
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Menu.BSW
*
*  Projeto: INF 1301 / Labirinto
*  Gestor:  LSKDANEAV
*  Autores: lsk
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		 1	   lsk	 20/10/2014		//
*
*  $ED Descrição do módulo
*       Cria um grafo de menus para serem utilizados com o modulo Estado. 
*       Apesar disso, isto é apenas uma sugestão, pois o módulo poderia ser genérico, bastando mudar o EST_tppEstado para void**.
*       Caso esteja usando em uma aplicação de jogo, é recomendável a não criação de um menu com id 0, pois convencionamos o mesmo como fim de jogo.
*       É implementado com um grafo não direcionado e Listas duplamente encadeadas.
*       É recomendado o seu uso como árvore, porém funciona com ciclos.
*       É obrigatória a criação do menu com id 1.
*       Os ids de menus devem ser únicos para um grafo.
*       Os cmds identificadores das opções devem ser únicas em cada menu.
*       (Podem haver dois comandos iguais em menus diferentes, em um mesmo grafo)
***************************************************************************/
#if defined( ESTADO_OWN )
    #define ESTADO_EXT
#else
    #define ESTADO_EXT extern
#endif


#include "TIPOESTADO.h"
#include "MENU.h"
#include "TABULEIRO.h"

/***********************************************************************
*
*  $TC Tipo de dados: EST Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum{

    EST_CondRetOK,
    /* Concluiu corretamente */

    EST_CondRetFaltouMemoria
    /* Concluiu corretamente */

} EST_tpCondRet;

/***********************************************************************
*
*  $FC Função: EST  &Criar EStado
*
*  $ED Descrição da função
*     Cria um Estado. Este contém um ponteiro para um tabuleiro e um para um grafo de menus.
*     É recomendável manter um estado único por jogo.
*  $EP Parâmetros
*     e - endereço de um ponteiro para um estado
*  $FV Valor retornado
*     EST_CondRetFaltouMemoria - faltou memoria ao criar o Estado
*
* Assertiva de entrada: É recomendável e nulo, para evitar memory leak
* Assertiva de saida:  e não é nulo e as assertivas estruturais valem 
***********************************************************************/
EST_tpCondRet EST_CriaEstado(EST_tppEstado* e);
/***********************************************************************
*
*  $FC Função: EST  &Alterar Menus
*
*  $ED Descrição da função
*     Substitui os Menus de e pelo ponteiro fornecido
*  $EP Parâmetros
*       e - ponteiro para estado
*       men - ponteiro para menus
*  $FV Valor retornado
*
* Assertiva de entrada: e e men não são nulos e suas assertivas estruturais valem
* Assertiva de saida:  e e men não são nulos e suas assertivas estruturais valem
***********************************************************************/
EST_tpCondRet EST_SetMenus(EST_tppEstado e, MEN_tppMenus men);
/***********************************************************************
*
*  $FC Função: EST  &Alterar Tabuleiro
*
*  $ED Descrição da função
*     Substitui o Tabuleiro de e pelo ponteiro fornecido
*  $EP Parâmetros
*       e - ponteiro para estado
*       tab - ponteiro para Tabuleiro
*  $FV Valor retornado
*
* Assertiva de entrada: e e tab não são nulos e suas assertivas estruturais valem
* Assertiva de saida:  e e tab não são nulos e suas assertivas estruturais valem
***********************************************************************/
EST_tpCondRet EST_SetTabuleiro(EST_tppEstado e, TAB_tppTabuleiro tab);
/***********************************************************************
*
*  $FC Função: EST  &Obter Menus
*
*  $ED Descrição da função
*     Substitui o ponteiro fornecido pelos Menus de e  
*  $EP Parâmetros
*       e - ponteiro para estado
*       men - endereço de ponteiro para menus
*  $FV Valor retornado
*       EST_CondRetFaltouMemoria - Menus de e é null (portanto men também, após a execução da função)
* Assertiva de entrada: e não é nulo e as assertivas estruturais valem, recomendavel men=null, para evitar memory leak
* Assertiva de saida:  e não é nulo e as assertivas estruturais valem
***********************************************************************/
EST_tpCondRet EST_GetMenus(EST_tppEstado e, MEN_tppMenus* men);
/***********************************************************************
*
*  $FC Função: EST  &Obter Tabuleiro
*
*  $ED Descrição da função
*     Substitui o ponteiro fornecido pelos Tabuleiro de e  
*  $EP Parâmetros
*       e - ponteiro para estado
*       tab - endereço de ponteiro para tabuleiro 
*  $FV Valor retornado
*       EST_CondRetFaltouMemoria - Tabuleiro de e é null (portanto tab também, após a execução da função)
* Assertiva de entrada: e não é nulo e as assertivas estruturais valem, recotabdavel men=null, para evitar memory leak
* Assertiva de saida:  e não é nulo e as assertivas estruturais valem
***********************************************************************/
EST_tpCondRet EST_GetTabuleiro(EST_tppEstado e, TAB_tppTabuleiro* tab);
/***********************************************************************
*
*  $FC Função: EST  &Destruir Estado
*
*  $ED Descrição da função
*       Destroi e e sua estrutura interna, liberando toda a memória contida neste estado
*  $EP Parâmetros
*       e - ponteiro para estado
*  $FV Valor retornado
*
* Assertiva de entrada: e não é nulo e as assertivas estruturais valem
* Assertiva de saida:  e é nulo
***********************************************************************/
EST_tpCondRet EST_DestruirEstado(EST_tppEstado e);
#endif
