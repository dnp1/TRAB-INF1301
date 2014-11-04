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
        
        TAB_tpCasaInicio ,

        TAB_tpCasaFim ,
        
        TAB_tpCasaChao,
        
        TAB_tpCasaParede
    
    } TAB_tpCasa ;

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

    TAB_tpCondRet TAB_CriarTabuleiro ( TAB_tppTabuleiro* pTab , int altura , int largura , char* nome ) ;
    
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
*  $FC Função: TAB &Pode andar pra cima
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

    TAB_tpCondRet TAB_PodeAndarPraCima ( TAB_tppTabuleiro pTab , int colisao );

/***********************************************************************
*
*  $FC Função: TAB  &Pode andar pra esquerda
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

    TAB_tpCondRet TAB_PodeAndarPraEsquerda ( TAB_tppTabuleiro pTab , int colisao );

/***********************************************************************
*
*  $FC Função: TAB  &Pode andar pra baixo
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

    TAB_tpCondRet TAB_PodeAndarPraBaixo ( TAB_tppTabuleiro pTab , int colisao );

/***********************************************************************
*
*  $FC Função: TAB  &Pode andar pra direita
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

    TAB_tpCondRet TAB_PodeAndarPraDireita ( TAB_tppTabuleiro pTab , int colisao );

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

    TAB_tpCondRet TAB_AndarPraCima ( TAB_tppTabuleiro pTab  );

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

    TAB_tpCondRet TAB_AndarPraDireita ( TAB_tppTabuleiro pTab  );

/***********************************************************************
*
*  $FC Função: TAB  &Poe Chao
*
*  $ED Descrição da função
*     Altera o tipo da casa para chao
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*     TAB_CondRetFaltouMemoria - ;
*     TAB_CondRetAlteracaoInvalida - ;
*
***********************************************************************/

    TAB_tpCondRet TAB_PoeChao ( TAB_tppTabuleiro pTab ) ;
 
/***********************************************************************
*
*  $FC Função: TAB  &Poe Parede
*
*  $ED Descrição da função
*     Altera o tipo da casa para parede
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*     TAB_CondRetFaltouMemoria - ;
*     TAB_CondRetAlteracaoInvalida - ;
*
***********************************************************************/

    TAB_tpCondRet TAB_PoeParede ( TAB_tppTabuleiro pTab ) ;
 
/***********************************************************************
*
*  $FC Função: TAB  &Poe Inicio
*
*  $ED Descrição da função
*     Altera o tipo da casa para inicio
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*     TAB_CondRetFaltouMemoria - ;
*     TAB_CondRetAlteracaoInvalida - ;
*
***********************************************************************/

    TAB_tpCondRet TAB_PoeInicio ( TAB_tppTabuleiro pTab ) ;
 
/***********************************************************************
*
*  $FC Função: TAB  &Poe Fim
*
*  $ED Descrição da função
*     Altera o tipo da casa para fim
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido; 
*     TAB_CondRetFaltouMemoria - ;
*     TAB_CondRetAlteracaoInvalida - ;
*
***********************************************************************/

    TAB_tpCondRet TAB_PoeFim ( TAB_tppTabuleiro pTab ) ;
 
/***********************************************************************
*
*  $FC Função: TAB  &Get Tipo Casa
*
*  $ED Descrição da função
*     Da o tipo (chão, parede, inicio ou fim) da casa representada por (x,y). 
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     x - x da casa a ser modificada
*     y - y da casa a ser modificada
*     tipo - ponteiro para o tipo da casa
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido;
*     TAB_CondRetNaoEhCasa - O tabuleiro não possuia uma casa representada por (x,y)
*
***********************************************************************/   

    TAB_tpCondRet TAB_GetTipoCasa ( TAB_tppTabuleiro pTab, int x , int y , TAB_tpCasa* tipo ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Get Altura
*
*  $ED Descrição da função
*     Da a altura do tabuleiro.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     altura - ponteiro para a altura
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido;
*
***********************************************************************/   

    TAB_tpCondRet TAB_GetAltura ( TAB_tppTabuleiro pTab, int* altura ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Get Largura
*
*  $ED Descrição da função
*     Da a largura do tabuleiro.
*
*  $EP Parâmetros
*     pTab - ponteiro para o tabuleiro
*     largura - ponteiro para a largura
*
*  $FV Valor retornado
*     TAB_CondRetOK - O tabuleiro é válido;
*
***********************************************************************/   

    TAB_tpCondRet TAB_GetLargura ( TAB_tppTabuleiro pTab, int* largura ) ;

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

    TAB_tpCondRet TAB_SalvarTabuleiro ( TAB_tppTabuleiro pTab , char* saida ) ;
        
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

    TAB_tpCondRet TAB_CarregarTabuleiro ( TAB_tppTabuleiro pTab, char* entrada ) ;
        
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

#endif
