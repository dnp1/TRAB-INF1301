#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: GRA  Grafo genêrico
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Grafo.BSW
*
*  Projeto: INF 1301 / Labirinto
*  Gestor:  LSKDANEAV
*  Autores: eav
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		 1	   eav	 25/09/2014		//
*
*  $ED Descrição do módulo
*     Implementa um grafo genêrico usando uma interface de
*	  Grafos genéricas duplamente encadeadas.
*     O grafo possui uma cabeça encapsulando o seu estado.
*
***************************************************************************/

#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

#include "../lista/LISTA.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma grafo */

typedef struct GRA_tagGrafo* GRA_tppGrafo ;
typedef struct GRA_tpVertice_* GRA_tppVertice ;
typedef struct LIS_tagLista * LIS_tppLista ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

  typedef enum {

    GRA_CondRetOK ,
    /* Concluiu corretamente */

    GRA_CondRetGrafoVazio ,
    /* O grafo está vazio(não possui vertices) */

    GRA_CondRetNaoEhVertice ,
   /* Não encontrou o vértice procurado */

    GRA_CondRetEhVizinho ,
    /* Os vértices explicitados são vizinhos*/
		
    GRA_CondRetNaoEhVizinho ,
	  /* Os vértices explicitados não são vizinhos*/
				
	  GRA_CondRetFaltouMemoria
    /* Faltou memória ao tentar criar um elemento de Grafo */

   } GRA_tpCondRet ;

/***********************************************************************
*
*  $FC Função: GRA  &Criar Grafo
*
*  $ED Descrição da função
*     Cria uma Grafo genérico implementado com listas duplamente encadeadas, também genéricas.
*     
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à Grafo.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o Grafo.
*     Este ponteiro será utilizado pelas funções que manipulem este Grafo.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   GRA_tppGrafo GRA_CriarGrafo ( void ( * ExcluirValor ) ( void * pDado ) ) ;
   
/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecido.
*     O parâmetro ponteiro para o grafo não é modificado.
*     Se ocorrer algum erro durante a destruição, o grafo resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     GRA_CondRetOK - destruiu sem problemas
*
***********************************************************************/

   GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Inserir vértice
*
*  $ED Descrição da função
*     Insere um novo vértice no grafo.
*     Caso o grafo esteja vazio, insere o primeiro vértice do grafo.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o vertice
*     pVertice - ponteiro para o novo vertice
*     pValor - ponteiro para o valor armazenado no No
*  $FV Valor retornado
*     GRA_CondRetOK	- O vértice foi inserido com sucesso
*     GRA_CondRetFaltouMemoria - Não foi possível alocar memória para o vértice
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo , GRA_tppVertice* pVertice, void* pValor ) ;
   
/***********************************************************************
*
*  $FC Função: GRA  &Excluir vértice
*
*  $ED Descrição da função
*     Exclui um vértice no grafo, removendo todas suas arestas
*     Exclui grafo, caso ele seja não seja ou o corrente.
*     Se for o corrente, só pode ser excluido, se for 
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o vertice
*     pVertice - ponteiro para o novo vertice
*     pValor - ponteiro para o valor armazenado no No
*  $FV Valor retornado
*     GRA_CondRetOK - O vértice foi inserido com sucesso

*
***********************************************************************/


  GRA_tpCondRet GRA_ExcluirVertice (GRA_tppGrafo g, GRA_tppVertice v);
   
/***********************************************************************
*
*  $FC Função: GRA  &Inserir Aresta
*
*  $ED Descrição da função
*     Insere uma aresta entre 2 vértices.
*     Se já existir uma aresta entre pVertice1 e pVertice2, erro de duplicata
*     Se pVertice1 ou pVertice2 não existirem, erro de inexistencia 
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo aonde deve ser inserida a aresta
*     pVertice1 - ponteiro para um dos vértices
*   pVertice2 - ponteiro para o outro vértice
*
*
*  $FV Valor retornado
*     GRA_CondRetOK  - Ambos u e v existiam e não hávia aresta entre eles
*     GRA_CondRetEhVizinho - Já existe aresta entre u e v
*     GRA_CondRetNaoEhVertice - u (ou v) não é um vértice do grafo
*     GRA_CondRetFaltouMemoria - Não foi possível alocar memória para a aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo , GRA_tppVertice pVertice1, GRA_tppVertice pVertice2 ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Excluir Aresta
*
*  $ED Descrição da função
*     Exclui uma aresta entre 2 vértices.
*     Se não existir uma aresta entre pVertice1 e pVertice2, erro de inexistência
*     Se pVertice1 ou pVertice2 não existirem, erro de inexistencia 
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo aonde deve ser inserida a aresta
*     pVertice1 - ponteiro para um dos vértices
*     pVertice2 - ponteiro para o outro vértice
*
*
*  $FV Valor retornado
*     GRA_CondRetOK  - Ambos pVertice1 e pVertice2 existem e não há aresta entre eles
*     GRA_CondRetNaoEhVertice - pVertice1 (ou pVertice2) não é um vértice do grafo
*     GRA_CondRetNaoEhVizinho - Não existe aresta entre pVertice1 e pVertice2
*     GRA_CondRetFaltouMemoria - Não foi possível alocar memória para a aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo , GRA_tppVertice pVertice1, GRA_tppVertice pVertice2 ) ;

/***********************************************************************
*
*  $FC Função: GRA  &ObterVizinhos
*
*  $ED Descrição da função
*     Obtem os vizinhos do vértice corrente
*     Se pVertice não existir, erro de inexistencia
*   Se pVertice não possuir vizinhos, retorna uma lista vazia 
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo aonde deve ser inserida a aresta
*     pListaVertice - ponteiro para a lista de vértices a ser preenchida com os vizinhos de pVertice
*   quantidade - ponteiro para a quantidade de vizinhos achados
*
*  $FV Valor retornado
*     GRA_CondRetOK  - Retornou a lista
*     GRA_CondRetNaoEhVertice - pVertice não é um vértice do grafo
*     GRA_CondRetFaltouMemoria - Não foi possível alocar memória para a lista de vértices
*
***********************************************************************/

GRA_tpCondRet GRA_ObterVizinhos ( GRA_tppGrafo pGrafo, LIS_tppLista * pLista);
/***********************************************************************
*
*  $FC Função: GRA  &ObterVizinhos
*
*  $ED Descrição da função
*     Obtem os vizinhos do vértice corrente
*     Se pVertice não existir, erro de inexistencia
*   Se pVertice não possuir vizinhos, retorna uma lista vazia 
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo aonde deve ser inserida a aresta
*     pListaVertice - ponteiro para a lista de vértices a ser preenchida com os vizinhos de pVertice
*   quantidade - ponteiro para a quantidade de vizinhos achados
*
*  $FV Valor retornado
*     GRA_CondRetOK  - Retornou a lista
*     GRA_CondRetNaoEhVertice - pVertice não é um vértice do grafo
*     GRA_CondRetFaltouMemoria - Não foi possível alocar memória para a lista de vértices
*
***********************************************************************/



#endif




