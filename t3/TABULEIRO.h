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
				
        TAB_CondRetFaltouMemoria
        /* Faltou memória */

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
*     Se executou corretamente retorna o ponteiro para o Tabuleiro.
*     Este ponteiro será utilizado pelas funções que manipulem este Tabuleiro.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

    TAB_tppTabuleiro TAB_CriarTabuleiro( int altura, int largura, char* nome ) ;

#endif