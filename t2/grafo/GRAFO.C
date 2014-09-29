/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo genêrico
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\GRAFO.BSW
*
*  Projeto: INF 1301 / Labirinto
*  Gestor:  LSKDANEAV
*  Autores: eav
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		 1	   eav	 25/09/2014		//
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define GRAFO_OWN
#include "GRAFO.h"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de aresta
*
*
***********************************************************************/

   typedef struct tagElemAresta {

         struct tagElemVertice * pVertice;
               /* Ponteiro para o vértice correspondente */
               
   } GRA_tpAresta ;
   //GRA??

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de nó
*
*
***********************************************************************/

   typedef struct tagElemNode {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         LIS_tppLista * pAresta ;
               /* Ponteiro para a cabeça de aresta */

   } tpElemNode ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de vértice
*
*
***********************************************************************/

   typedef struct tagElemVertice {

         GRA_tpNode * pNode ;
               /* Ponteiro para a cabeça de nó */      
               
   } GRA_tpElemVertice ;

    
/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de componente
*
*
***********************************************************************/

   typedef struct tagElemComp {

         struct tagElemVertice * pVertice;
               /* Ponteiro para o vértice origem do componente */

   } tpElemComp ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de grafo
*
*
***********************************************************************/

   typedef struct GRA_tagGrafo {
         
         LIS_tppLista vertices;
         
         LIS_tppLista componentes;
         
         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } GRA_tpGrafo ;

/***** Protótipos das funções encapsuladas no módulo *****/
//as funcoes de exclusao de vertice e arestas sao chamadas internamente e externamente

//apaga aresta(u,v) e a aresta(v,u)
//essa tambem sera exportada
void ExcluirAresta(tpAresta a,tpVertice v){
{
    vai para o vertice apontado por a
        procura v na lista de vizinhos de u
            apaga a referencia para v
    free a
}
//apaga um vertice e suas referencias
//essa tambem eh exportada
void ExcluirVertice(tpVertice v){
    p cada aresta
        Excluir Aresta
    free cabeca lista de arestas
    chama a funcao de excluir valor do no(dada pelo cria grafo)
    free no
    free cabeca no
    free vertice
}


//funcao interna, a bfs eh para conseguirmos excluir todos sem ciclo.
void ExcluirComponente(tpComponente comp){
    BFS na origem do componente, para evitar ciclos. sempre que achar uma folha(folha = nao tem vizinhos nao marcados), apaga ela.
    elemento da bfs é um tpVertice, excluido com a esvaziar vertice
    free componente
}

//interna
void ExcluirGrafo(GRA_tppGrafo grafo){
    p cada componente
        ExcluirComponente(comp);
    
    free cabeca da lista de componentes
    free cabeca da lista de vertices
    limpa cabeca
    //da free na cabeca do grafo ou isso eh responsabilidade do cliente??
}

//interna, nao sei se eh necessaria, copiei o modelo da lista
void LimparCabeca(GRA_tppGrafo grafo){
    limpa os ponteiros
}
//interna
//responsavel por alocar memoria para a componente e aponta-la para o vetice dado
tpComp * CriarComponente(GRA_tppGrafo g, tpVertice * v){
    tpComp * comp = malloc (sizeof(tpComp))
    comp->vertice = v;
    return comp;
}

//interna
//cria um vertice e sua estrutura interna
tpVertice * CriarVertice(GRA_tppGrafo grafo){
    tpVertice * v = NULL;    
    v = (* tpVertice) malloc( sizeof(tpVertice) );
    if (v == NULL) 
        return NULL;
    LIS_tppLista l_aresta = LIS_CriarLista(ExcluirAresta);
    LIS_tppLista l_no = LIS_CriarLista(ExcluirNo);
    tpElemNode * no = malloc( sizeof(tpElemNode) );
    no->pAresta = l_aresta;
    no->pAnt = NULL;
    no->pProx = NULL;
    no->pValor = NULL; 
    LIS_InserirElementoAntes(l_no,no);
    v->pNode = l_no;
    return v
}

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: GRA  &Criar Grafo
*  ****/


   GRA_tppGrafo LIS_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      GRA_tpGrafo * pGrafo = NULL ;

      pGrafo = ( GRA_tpGrafo * ) malloc( sizeof( GRA_tpGrafo )) ;
      if ( pGrafo == NULL )
      {
         return NULL ;
      } /* if */
      LIS_tppLista l_vertice = LIS_CriarLista(ExcluirVertice);
      LIS_tppLista l_componente = LIS_CriarLista(ExcluirComp);
      LimparCabeca( pGrafo ) ;
      pGrafo->vertices = l_vertice;
      pGrafo->componentes = l_componente;
      pGrafo->ExcluirValor = ExcluirValor ;

      return pGrafo ;

   } /* Fim função: GRA  &Criar grafo */



/***************************************************************************
*
*  Função: GRA  &Destruir grafo
*  ****/

   tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo )
   {

      #ifdef _DEBUG
         assert( pGrafo != NULL ) ;
      #endif

      GRA_ExcluirGrafo( pGrafo ) ;
      
      free( pGrafo ) ;
      
      return GRA_CondRetOK;
   } /* Fim função: GRA  &Destruir grafo */


/***************************************************************************
*
*  Função: GRA  &Inserir vertice 
*  ****/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo , GRA_tppVertice * pVertice ) ;
   {

      tpVertice * pElem ;
      tpComponente * pComp ;

      #ifdef _DEBUG
         assert( pGrafo != NULL ) ;
      #endif

      /* Criar o Vertice antes */

         pElem = CriarVertice( pGrafo ) ;
         if ( pElem == NULL )
         {
            return GRA_CondRetFaltouMemoria ;
         } /* if */
         pComp = CriarComponente( pGrafo, pElem );
         if ( pComp == NULL )
         {
             return GRA_CondRetFaltouMemoria;
         }
         pVertice = pElem;
         return GRA_CondRetOK ;

   } /* Fim função: GRA  &Inserir vertice */

