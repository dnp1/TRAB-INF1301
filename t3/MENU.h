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
/* Tipo referência para um Menu */
typedef struct Menu_ * MEN_tppMenu;
/* Tipo referência para uma Opção de um Menu */
typedef struct Opcao_ * MEN_tppOpcao; 

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

    MEN_CondRetFaltouMemoria,
    /* Concluiu corretamente */

    MEN_CondRetOK
    /* Concluiu corretamente */

} MEN_tpCondRet;


/***********************************************************************
*
*  $FC Função: MEN  &Criar Menus
*
*  $ED Descrição da função
*     Cria um grafo de Menus para aplicações, implementado com um grafo genérico.
*     Os Menus são implementados com um grafo de tipo homogêneo 
*     genérico não direcionado sem peso nas arestas. 
*     Por convenção, o menu inicial tem id 1;
*  $EP Parâmetros
*
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
***********************************************************************/
MEN_tpCondRet MEN_CriarMenus(MEN_tppMenus* m);
MEN_tpCondRet MEN_DestruirMenus(MEN_tppMenus* m);
MEN_tpCondRet MEN_DestruirMenu(MEN_tppMenu menu);
MEN_tpCondRet MEN_CriarMenu(MEN_tppMenus menus, int id, char* nome,int idPai);
MEN_tpCondRet MEN_CriarOpcao(MEN_tppMenus menus, int idMenu,char cmd, char* nome,void (*callback)(EST_tppEstado e,MEN_tppOpcao o));


MEN_tpCondRet MEN_GetMenuOpcoes(MEN_tppMenu m,LIS_tppLista l); 
MEN_tpCondRet MEN_GetMenuNome(MEN_tppMenu m, char* nome);
MEN_tpCondRet MEN_GetOpcaoCmd(MEN_tppOpcao o, char cmd);
MEN_tpCondRet MEN_GetOpcaoNome(MEN_tppOpcao o, char* nome);
MEN_tpCondRet MEN_Callback(MEN_tppOpcao o, EST_tppEstado e);
MEN_tpCondRet MEN_MudaMenu(MEN_tppMenus m, int id);
MEN_tpCondRet MEN_MenuInicial(MEN_tppMenus men);
MEN_tpCondRet MEN_MenuCorrente(MEN_tppMenus e, int* id);
MEN_tpCondRet MEN_MudaUltimoMenu(MEN_tppMenus e,int n);
#endif
