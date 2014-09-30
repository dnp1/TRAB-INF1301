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
*  $TC Tipo de dados: GRA Elemento de nó
*
*
***********************************************************************/

	 typedef struct tpNode_ {

				 void* pValor ;
							 /* Ponteiro para o valor contido no elemento */

				 LIS_tppLista arestas ;
					/* Ponteiro para a cabeça de aresta */
	 } tpNode ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de vértice
*
*
***********************************************************************/

	 typedef struct tpVertice_ {
				 tpNode* pNode ;
							 /* Ponteiro para a cabeça de nó */      
	 } GRA_tpVertice ;

		
/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de componente
*
*
***********************************************************************/

	 typedef struct tagElemComp {

		 struct tagElemVertice* pVertice;
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

	 } GRA_tpGrafo;

/***** Protótipos das funções encapsuladas no módulo *****/
//as funcoes de exclusao de vertice e arestas sao chamadas internamente e externamente

//apaga aresta(u,v) e a aresta(v,u)
//essa tambem sera exportada
void GRA_RemoverAresta (GRA_tpVertice* u, GRA_tpVertice* v)
{
	 LIS_tppLista vizinhos;
	 GRA_tpVertice* vizinho;
	 
	 //Codigo duplicado, melhorar!!!
	 vizinhos = u->pNode->arestas;
	 LIS_IrInicioLista(vizinhos);
	 do {
			vizinho = LIS_ObterValor(vizinhos);
			if (vizinho == v) {
				 LIS_ExcluirElemento(vizinhos);
				 break;
			}
			
	 } while(LIS_AvancarElementoCorrente(vizinhos, 1) != LIS_CondRetFimLista);
	 
	 vizinhos = v->pNode->arestas;
	 LIS_IrInicioLista(vizinhos);
	 do {
			vizinho = LIS_ObterValor(vizinhos);
			if (vizinho == u) {
				 LIS_ExcluirElemento(vizinhos);
				 break;
			}
	 } while(LIS_AvancarElementoCorrente(vizinhos, 1) != LIS_CondRetFimLista);
	 
	 // FAZER BUSCA na componente e ve se grafos ainda fazem parte da mesma;
}


void ExcluirVertice(GRA_tpVertice* v) {
	GRA_tpVertice* vizinho;
	LIS_tppLista vizinhos;

	if(v == NULL) {
		return;
	}
	
	vizinhos = v->pNode->arestas;
	LIS_IrInicioLista(vizinhos);
	do {
		vizinho = LIS_ObterValor (vizinhos);
		GRA_RemoverAresta (v, vizinho);
	} while(LIS_AvancarElementoCorrente(vizinhos, 1) != LIS_CondRetFimLista);
	LIS_DestruirLista(vizinhos);

}

//apaga um vertice e suas referencias
//essa tambem eh exportada
void GRA_RemoverVertice (GRA_tpGrafo* g, GRA_tpVertice* v) {
	if (g->vertices == NULL) {
		return;
	}
	if (LIS_ProcurarValor(g->vertices, v) != LIS_CondRetOK) {
		return;
	}
	LIS_ExcluirElemento(g->vertices);
}


//funcao interna, a bfs eh para conseguirmos excluir todos sem ciclo.
void ExcluirPonteiro(void* comp) {
	free(comp);
}


//interna
//responsavel por alocar memoria para a componente e aponta-la para o vetice dado
// tpComp * CriarComponente(GRA_tppGrafo g, tpVertice * v){
// 		tpComp * comp = malloc (sizeof(tpComp))
// 		comp->vertice = v;
// 		return comp;
// }

//interna
//cria um vertice e sua estrutura interna
GRA_tpVertice* CriarVertice(GRA_tppGrafo grafo) {
		GRA_tpVertice* v = NULL;    
		tpNode* no = NULL;
		LIS_tppLista arestas = NULL;

		v = (GRA_tpVertice*) malloc( sizeof(GRA_tpVertice) );
		if (v == NULL) {
			return NULL;
		}

		no = (tpNode*) malloc( sizeof(tpNode) );
		if(no == NULL) {
			free(v);
			return NULL;
		}

		arestas = LIS_CriarLista(NULL);
		if(arestas == NULL) {
			free(v);
			free(no);
			return NULL;
		}

		no->arestas = arestas;
		no->pValor = NULL; //Really?
		v->pNode = no;

		return v;
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
			if (pGrafo == NULL) {
			
				 return NULL ;
			} /* if */
			LIS_tppLista l_vertice = LIS_CriarLista(free); //A Exclusão será manual, iterando sobre os elementos;
			LIS_tppLista l_componente = LIS_CriarLista(NULL); //Controle interno e autocontido; Componentes não cuidam de dados do valor, só armazenam ponteiros.
			
			pGrafo->vertices = l_vertice;
			pGrafo->componentes = l_componente;
			pGrafo->ExcluirValor = ExcluirValor ;

			return pGrafo ;

	 } /* Fim função: GRA  &Criar grafo */



/***************************************************************************
*
*  Função: GRA  &Destruir grafo
*  ****/

	 GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo g )
	 {
	 		tpNode* no;
			#ifdef _DEBUG
				 assert( pGrafo != NULL ) ;
			#endif

			LIS_DestruirLista(g->componentes);

			LIS_IrInicioLista(g->vertices);
			do {
				no = LIS_ObterValor(g->vertices);
				g->ExcluirValor(no->pValor);
				LIS_DestruirLista(no->arestas);
				free(no);
			} while(LIS_AvancarElementoCorrente(g->vertices, 1) != LIS_CondRetFimLista);

			LIS_DestruirLista(g->vertices);

			free( g ) ;
			
			return GRA_CondRetOK;
	 } /* Fim função: GRA  &Destruir grafo */


/***************************************************************************
*
*  Função: GRA  &Inserir vertice 
*  ****/

	 GRA_tpCondRet GRA_InserirVertice (GRA_tppGrafo g, GRA_tppVertice* pVertice )
	 {

		GRA_tppVertice pElem ;
		#ifdef _DEBUG
			 assert( g != NULL ) ;
		#endif

		/* Criar o Vertice antes */

		pElem = (GRA_tppVertice) CriarVertice( g ) ;
		if ( pElem == NULL )
		{
			return GRA_CondRetFaltouMemoria ;
		} /* if */

	 	LIS_InserirElementoApos (g->componentes, (void*)pElem);
		 
		(*pVertice) = pElem;

		return GRA_CondRetOK ;

	 } 
	 /* Fim função: GRA  &Inserir vertice */

