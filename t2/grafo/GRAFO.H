/*
grafo.h
typedef *Grafo tpGrafo;
typedef *Vertice tpVertice;

tpCondRet CriarGrafo(tpGrafo grafo);

tpCondRet ExcluirGrafo(tpGrafo grafo);

tpCondRet InserirVertice(tpGrafo grafo);

tpCondRet ExcluirVerticeCorrente(tpGrafo grafo);

tpCondRet InserirAresta(tpGrafo grafo,tpVertice v1, tpVertice v2);

tpCondRet ExcluirAresta(tpGrafo grafo,tpVertice v1, tpVertice v2);

tpCondRet ObterVizinhos(tpGrafo grafo, tpVertice v1, int * quantidade);

tpCondRet IrParaVizinho(tpGrafo grafo, tpVertice v1);

tpCondRet AcessarCorrente(tpGrafo grafo);
*/
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

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma grafp */

typedef struct GRA_tagGrafo * GRA_tppGrafo ;
typedef struct GRA_tagVertice * GRA_tppVertice ;


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

         GRA_CondRetNaoEncotrou ,
               /* Não encontrou o vértice procurado */

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
*	  ?
*	  Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à Grafo.
*	  ?
*
*  $EP Parâmetros
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

   GRA_tppGrafo GRA_CriarGrafo() ;
   
/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecida.
*     O parâmetro ponteiro para o grafo não é modificado.
*     Se ocorrer algum erro durante a destruição, o grafo resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     GRA_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void GRA_DestruirGrafo( GRA_tppGrafo pGrafo ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o vertice
*     pVertice - ponteiro para o novo vertice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo ,
                                           GRA_tppVertice * pVertice        ) ;

   
/***********************************************************************
*
*  $FC Função: GRA  &Inserir Aresta
*
*  $ED Descrição da função
*     Insere uma aresta entre 2 vértices.
*     Se já existir uma aresta entre u e v, erro de duplicata.
*     Se u ou v não existirem, erro de inexistencia 
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo aonde deve ser inserida a aresta
*     pVertice1 - ponteiro para um dos vértices
*	  pVertice2 - ponteiro para o outro vértice
*
*
*  $FV Valor retornado
*     GRA_CondRetOK  - Ambos u e v existiam e não hávia aresta entre eles
*	  GRA_CondRetNaoEncontrou - u (ou v) não é um vértice do grafo
*     GRA_CondRetFaltouMemoria - Não foi possível alocar memória para a aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo ,
                                           GRA_tppVertice * pVertice1,
                                           		GRA_tppVertice * pVertice2	) ;



