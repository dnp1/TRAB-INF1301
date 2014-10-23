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
*     
*     O tabuleiro implementa um grafo de casas.
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
*     Caso a id passada seja igual a uma das ids correspondentes as direções (N,S,L,O) do vértice corrente,
*     o movimento é válido.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     idProximo - inteiro que representa o id do vértice de destino
*
*  $FV Valor retornado
*     GRA_CondRetOK - O movimento era válido; o vértice de destino é vizinho do corrente
*     GRA_CondRetMovimentoInvalido - O movimento era inválido; os vértices não são vizinhos ou o vértice de destino não existe;
*
***********************************************************************/

    TAB_tpCondRet TAB_ValidaMovimento ( TAB_tppTabuleiro pTab , int idProximo ) ;

#endif