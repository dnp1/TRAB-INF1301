#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB Tabuleiro de labirinto
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Tabuleiro.BSW
*
*  Projeto: INF 1301 / Labirinto
*  Gestor:  LSKDANEAV
*  Autores: eav
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		 1	   eav	 20/10/2014		//
*
*  $ED Descrição do módulo
*
***************************************************************************/

#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

#include "GRAFO.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */

typedef struct TAB_tppTabuleiro_* TAB_tppTabuleiro ;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

    typedef enum {

        TAB_CondRetOK ,
        /* Concluiu corretamente */
				
        TAB_CondRetFaltouMemoria ,
        /* Faltou memória */

        TAB_CondRetMovimentoInvalido ,
        /* Movimento inválido */

        TAB_CondRetAlteracaoInvalida 
        /* Alteração do valor ( vazio/parede/inicio/fim ) inválida */

    } TAB_tpCondRet ;
    
/***********************************************************************
*
*  $FC Função: GRA  &Criar Tabuleiro
*
*  $ED Descrição da função
*     Cria um Tabuleiro para labirinto, implementado com um grafo genérico.
*     O Tabuleiro é implementado com um grafo de tipo homogêneo 
*     genérico não direcionado sem peso nas arestas. 
*
*  $EP Parâmetros
*     Altura - inteiro que representa o tamanho vertical do tabuleiro.
*     Largura - inteiro que representa o tamanho horizontal do tabuleiro.
*
*  $FV Valor retornado
*     GRA_CondRetOK - criou o tabuleiro sem problemas
*     GRA_CondRetFaltouMemoria - faltou memoria ao criar o tabuleiro
*
***********************************************************************/

    TAB_tpCondRet TAB_CriarTabuleiro ( TAB_tppTabuleiro pTab , int altura , int largura , char* nome ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Valida Movimento
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     GRA_CondRetOK - O movimento é válido; 
*     GRA_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_ValidaMovimentoNorte ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: GRA  &Valida Movimento
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     GRA_CondRetOK - O movimento é válido; 
*     GRA_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_ValidaMovimentoOeste ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: GRA  &Valida Movimento
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     GRA_CondRetOK - O movimento é válido; 
*     GRA_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_ValidaMovimentoSul ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: GRA  &Valida Movimento
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     GRA_CondRetOK - O movimento é válido; 
*     GRA_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_ValidaMovimentoLeste ( TAB_tppTabuleiro pTab );

#endif
