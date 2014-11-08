#if ! defined ( MENU_ )
#define MENU_

/***************************************************************************
*
*  $MCD Módulo de definição: MEN Menus
*
*  Arquivo gerado:              MENU.h
*  Letras identificadoras:      MEN
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
*
***************************************************************************/
#if defined( MENU_OWN )
    #define MENU_EXT
#else
    #define MENU_EXT extern
#endif
/*
   ids dos Menus devem ser unicos e maiores que 1.
   A navegação sempre começa no Menu de id 1, ao menos este deve existir.
   
*/
#include "GRAFO.h"
#include "TIPOESTADO.h"

/* Tipo referência para um grafo de Menus */
typedef struct Menus_ * MEN_tppMenus;

/***********************************************************************
*
*  $TC Tipo de dados: MEN Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum{

    MEN_CondRetOK,
    /* Concluiu corretamente */
    MEN_CondRetFaltouMemoria,
    /* Faltou Memoria */
    MEN_CondRetComandoInvalido
    /* O comando é invalido */


} MEN_tpCondRet;


/***********************************************************************
*
*  $FC Função: MEN  &Criar Menus
*
*  $ED Descrição da função
*     Cria um grafo de Menus para aplicações, implementado com um grafo genérico.
*     Os Menus são implementados com um grafo de tipo homogêneo 
*     genérico não direcionado sem peso nas arestas. 
*     O menu inicial tem id 1;
*     O menu representando fim de jogo tem id 0;
*  $EP Parâmetros
*
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
***********************************************************************/
MEN_tpCondRet MEN_CriarMenus(MEN_tppMenus* m);
/***********************************************************************
*
*  $FC Função: MEN  &Criar Menu
*
*  $ED Descrição da função
*     Cria um Menu e o insere em um grafo de Menus
*     O menu contém:
*       um id, que deve ser único.
*       um nome.
*       um id do menu pai, pois todo menu tem por padrão um comando de voltar para o menu acima.
*       uma lista de opcoes, que devem ser populadas por MEN_CriarOpcao
*  $EP Parâmetros
*       id - identificador único
*       nome - string alocada externamente ou constante 
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
***********************************************************************/
MEN_tpCondRet MEN_CriarMenu(MEN_tppMenus menus, int id, char* nome,int idPai);
/***********************************************************************
*
*  $FC Função: MEN  &Destruir Menus
*
*  $ED Descrição da função
*     Destroi o grafo e a estrutura de m, liberando sua memoria.
*  $EP Parâmetros
*     m - MEN_tppMenus a ser destruido
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
***********************************************************************/
MEN_tpCondRet MEN_DestruirMenus(MEN_tppMenus m);
/***********************************************************************
*
*  $FC Função: MEN  &Destruir Menu
*
*  $ED Descrição da função
*     Destroi o menu de id 'id' em m
*  $EP Parâmetros
*
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
***********************************************************************/
MEN_tpCondRet MEN_DestruirMenu(MEN_tppMenus m, int id);
/***********************************************************************
*
*  $FC Função: MEN  &Destruir Opcao
*
*  $ED Descrição da função
*     Destroi a Opcao representando o cmd 'cmd', no menu de id 'id' em m
*  $EP Parâmetros
*
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
***********************************************************************/
MEN_tpCondRet MEN_DestruirOpcao(MEN_tppMenus m, int idMenu, char cmd);
MEN_tpCondRet MEN_CriarOpcao(MEN_tppMenus menus, int idMenu,char cmd, char* nome,MEN_tpCondRet (*callback)(EST_tppEstado e));


MEN_tpCondRet MEN_GetMenuOpcoes(MEN_tppMenus m,int id,char* l,int* tam); 
MEN_tpCondRet MEN_GetMenuNome(MEN_tppMenus m,int id, char** nome);
MEN_tpCondRet MEN_GetOpcaoNome(MEN_tppMenus m, int id, char cmd, char** nome);
MEN_tpCondRet MEN_Callback(MEN_tppMenus m, int id, char cmd, EST_tppEstado e);
MEN_tpCondRet MEN_MudaMenu(MEN_tppMenus m, int id);
MEN_tpCondRet MEN_MenuInicial(MEN_tppMenus men);
MEN_tpCondRet MEN_MenuCorrente(MEN_tppMenus e, int* id);
MEN_tpCondRet MEN_MudaMenu(MEN_tppMenus e,int n);
#endif
