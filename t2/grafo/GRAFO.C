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

         struct tagElemAresta * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemAresta * pProx ;
               /* Ponteiro para o elemento sucessor */
         
         struct tagElemVertice * pVertice;
               /* Ponteiro para o vértice correspondente */

   } tpElemAresta ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de aresta
*
*
***********************************************************************/

   typedef struct GRA_tagAresta {

         // id ?
         
         tpElemGrafo * pOrigemAresta ;
               /* Ponteiro para a origem do nó */

         tpElemGrafo * pFimAresta ;
               /* Ponteiro para o final do nó */

         tpElemGrafo * pElemAresta ;
               /* Ponteiro para o elemento corrente do nó */

         int numElem ;
               /* Número de elementos do nó */
               
   } GRA_tpAresta ;
   

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de nó
*
*
***********************************************************************/

   typedef struct tagElemNode {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemNode * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemNode * pProx ;
               /* Ponteiro para o elemento sucessor */
               
         GRA_tpAresta * pAresta ;
               /* Ponteiro para a cabeça de aresta */

   } tpElemNode ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de nó
*
*
***********************************************************************/

   typedef struct GRA_tagNode {

         tpElemGrafo * pOrigemNode ;
               /* Ponteiro para a origem do nó */

         tpElemGrafo * pFimNode ;
               /* Ponteiro para o final do nó */

         tpElemGrafo * pElemNode ;
               /* Ponteiro para o elemento corrente do nó */

         int numElem ;
               /* Número de elementos do nó */
               
   } GRA_tpNode ;
   

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de vértice
*
*
***********************************************************************/

   typedef struct tagElemVertice {

         struct tagElemVertice * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemVertice * pProx ;
               /* Ponteiro para o elemento sucessor */
         
         GRA_tpNode * pNode ;
               /* Ponteiro para a cabeça de nó */      
               
   } tpElemVertice ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de vértice
*
*
***********************************************************************/

   typedef struct GRA_tagVertice {

         // id ?
         
         tpElemVertice * pOrigemVertice ;
               /* Ponteiro para a origem do vértice */

         tpElemVertice * pFimVertice ;
               /* Ponteiro para o final do vértice */

         tpElemVertice * pElemVertice ;
               /* Ponteiro para o elemento corrente do vértice */

         int numElem ;
               /* Número de elementos do vértice */
               
   } GRA_tpVertice ;
     
    
/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de componente
*
*
***********************************************************************/

   typedef struct tagElemComp {

         struct tagElemComp * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemComp * pProx ;
               /* Ponteiro para o elemento sucessor */
         
         struct tagElemVertice * pVertice;
               /* Ponteiro para o vértice origem do componente */

   } tpElemComp ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de componentes
*
*
***********************************************************************/

   typedef struct GRA_tagComp {

         // id ?
         
         tpElemComp * pOrigemComp ;
               /* Ponteiro para a origem do nó */

         tpElemComp * pFimComp ;
               /* Ponteiro para o final do nó */

         tpElemComp * pElemComp ;
               /* Ponteiro para o elemento corrente do nó */

         int numElem ;
               /* Número de elementos do nó */
               
   } GRA_tpComp ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de grafo
*
*
***********************************************************************/

   typedef struct GRA_tagGrafo {

         tpElemGrafo * pOrigemGrafo ;
               /* Ponteiro para a origem do grafo */

         tpElemGrafo * pFimGrafo ;
               /* Ponteiro para o final do grafo */

         tpElemGrafo * pElemGrafo ;
               /* Ponteiro para o elemento corrente do grafo */

         int numElem ;
               /* Número de elementos da grafo */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } GRA_tpGrafo ;

/***** Protótipos das funções encapsuladas no módulo *****/

