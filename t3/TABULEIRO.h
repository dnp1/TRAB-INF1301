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

typedef struct TAB_tpTabuleiro_* TAB_tppTabuleiro ;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Tipo da casa
*
*  $ED Descrição do tipo
*     Representa se a casa é inicio, fim, chão ou parede
*
***********************************************************************/

    typedef enum {
        
        TAB_TipoCasaInicio ,

        TAB_TipoCasaFim ,
        
        TAB_TipoCasaChao,
        
        TAB_TipoCasaParede
    
    } TAB_TipoCasa ;

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

        TAB_CondRetNaoEhCasa ,
        /* A casa explicitada nao pertence ao tabuleiro */

        TAB_CondRetMovimentoInvalido ,
        /* Movimento inválido */

        TAB_CondRetAlteracaoInvalida , 
        /* Alteração do valor ( vazio/parede/inicio/fim ) inválida */

        TAB_CondRetTabuleiroValido ,
        /* Tabuleiro respeita as assertivas */

        TAB_CondRetTabuleiroInvalido ,
        /* Tabuleiro viola as assertivas */

        TAB_CondRetSemSolucao
        /* Tabuleiro não tem solução */

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
*  $FC Função: GRA  &Destruir Tabuleiro
*
*  $ED Descrição da função
*     Destroi o tabuleiro
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     GRA_CondRetOK - criou o tabuleiro sem problemas
*     GRA_CondRetFaltouMemoria - faltou memoria ao criar o tabuleiro
*
***********************************************************************/

    TAB_tpCondRet TAB_DestruirTabuleiro ( TAB_tppTabuleiro pTab ) ;

/***********************************************************************
*
*  $FC Função: TAB &Pode ir pra cima
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento para o norte.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido; 
*     TAB_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_PodeIrPraCima ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB  &Pode ir pra esquerda
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido; 
*     TAB_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_PodeIrPraEsquerda ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB  &Pode ir pra baixo
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido; 
*     TAB_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_PodeIrPraBaixo ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB  &Pode ir pra direita
*
*  $ED Descrição da função
*     Valida a possibilidade de um movimento. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido; 
*     TAB_CondRetMovimentoInvalido - O movimento é inválido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_PodeIrPraDireita ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB &Andar pra cima
*
*  $ED Descrição da função
*     Muda o corrente para o vizinho ao norte dele.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_AndarPraCima ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB  &Andar pra esquerda
*
*  $ED Descrição da função
*     Muda o corrente para o vizinho ao oeste dele. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_AndarPraEsquerda ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB  &Andar pra baixo
*
*  $ED Descrição da função
*     Muda o corrente para o vizinho ao sul dele.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_AndarPraBaixo ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB  &Andar pra direita
*
*  $ED Descrição da função
*     Muda o corrente para o vizinho ao leste dele. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O movimento é válido;
*
***********************************************************************/

    TAB_tpCondRet TAB_AndarPraDireita ( TAB_tppTabuleiro pTab );

/***********************************************************************
*
*  $FC Função: TAB  &Alterar Casa
*
*  $ED Descrição da função
*     Altera o tipo da casa. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     x - x da casa a ser modificada
*     y - y da casa a ser modificada
*     tipo - novo tipo da casa
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_AlterarCasa ( TAB_tppTabuleiro pTab , int x , int y , TAB_TipoCasa tipo ) ;
    
/***********************************************************************
*
*  $FC Função: TAB  &Visualizar Tabuleiro
*
*  $ED Descrição da função
*     Visualiza tabuleiro. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     pMatriz - ponteiro para a matriz de caracteres
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_VisualizarTabuleiro ( TAB_tppTabuleiro pTab , char*** pMatriz ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Validar Tabuleiro
*
*  $ED Descrição da função
*     Valida o tabuleiro. 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_ValidarTabuleiro ( TAB_tppTabuleiro pTab ) ;
    
/***********************************************************************
*
*  $FC Função: TAB  &Salvar Tabuleiro
*
*  $ED Descrição da função
*     Salva o tabuleiro em um arquivo.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     saida - ponteiro para o arquivo aonde o tabuleiro vai ser salvo
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_SalvarTabuleiro ( TAB_tppTabuleiro pTab , FILE* saida ) ;
        
/***********************************************************************
*
*  $FC Função: TAB  &Carregar Tabuleiro
*
*  $ED Descrição da função
*     Carrega o tabuleiro de um arquivo.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     entrada - ponteiro para o arquivo de onde o tabuleiro vai ser lido
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*
***********************************************************************/

    TAB_tpCondRet TAB_CarregarTabuleiro ( TAB_tppTabuleiro pTab, FILE* entrada ) ;
        
/***********************************************************************
*
*  $FC Função: TAB  &Solucionar Tabuleiro
*
*  $ED Descrição da função
*     Soluciona o tabuleiro. A solução é retornada em uma string de caracteres.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     pSolucao - ponteiro para a cadeia de caracteres que representa a solução
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido;
*     TAB_CondRetSemSolucao - O tabuleiro não possui solução;
*
***********************************************************************/

    TAB_tpCondRet TAB_SolucionarTabuleiro ( TAB_tppTabuleiro pTab, char* pSolucao ) ;    

/***********************************************************************
*
*  $FC Função: TAB  &Posicao do Jogador
*
*  $ED Descrição da função
*     Da a posição (x,y) do jogador no tabuleiro.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     pX - ponteiro para inteiro que representa a coordenada X do jogador
*     pY - ponteiro para inteiro que representa a coordenada Y do jogador
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido;
*
***********************************************************************/

    TAB_tpCondRet TAB_PosicaoJogador ( TAB_tppTabuleiro pTab , int* x , int* y ) ;        

/***********************************************************************
*
*  $FC Função: TAB  &GetTipoCasa
*
*  $ED Descrição da função
*     Da o tipo da casa referente as coordenadas (x,y)
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     x - inteiro que representa a coordenada x
*     y - inteiro que representa a coordenada y
*     pTipo - ponteiro para o tipo da casa
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido;
*     TAB_CondRetNaoEhCasa - As coordenadas explicitadas não pertencem ao tabuleiro;
*
***********************************************************************/

    TAB_tpCondRet TAB_GetTipoCasa ( TAB_tppTabuleiro pTab, int x , int y , TAB_TipoCasa* pTipo ) ;

#endif
