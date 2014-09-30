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

	 typedef struct GRA_tpVertice_ {
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
        GRA_tpVertice* corrente;
	 } GRA_tpGrafo;

/***** Protótipos das funções encapsuladas no módulo *****/
//as funcoes de exclusao de vertice e arestas sao chamadas internamente e externamente

//apaga aresta(u,v) e a aresta(v,u)
//essa tambem sera exportada

static void RemoverAresta(GRA_tpVertice* u, GRA_tpVertice* v) {
	LIS_tppLista vizinhos;
	vizinhos = u->pNode->arestas;
	LIS_ProcurarValor(vizinhos, v);
	LIS_ExcluirElemento(vizinhos);
	
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

		no->arestas = NULL;
		no->pValor = NULL; //Really?
		v->pNode = no;

		return v;
}

static int BFS(GRA_tpVertice* v, GRA_tpVertice* u) {
	LIS_tppLista V = NULL; // LISTA VERTICE VISITADOS
	LIS_tppLista Q = NULL; //FILA
	LIS_tppLista arestas = NULL;
 	GRA_tpVertice* t = NULL;
 	GRA_tpVertice* s = NULL;
 	int achou = 0;

 	V = LIS_CriarLista(NULL); // dados são referenciados por outros, não devem ser apagados
	Q = LIS_CriarLista(NULL); // dados são referenciados por outros, não devem ser apagados

	LIS_InserirElementoApos(V, v);
	LIS_InserirElementoApos(Q, v); //Usado como uma Fila.

	while (LIS_NumeroDeElementos(Q) > 0) {

		LIS_IrInicioLista(Q);
		t = LIS_ObterValor(Q);
		LIS_ExcluirElemento(Q);

		if (t == u) {
			achou = 1; 
			break;
		}

		arestas = t->pNode->arestas;
		LIS_IrInicioLista(arestas);
		do {
			s = LIS_ObterValor(arestas);
			if (LIS_ProcurarValor(V, s) == LIS_CondRetNaoAchou) {
				LIS_InserirElementoApos(V, s);
				LIS_InserirElementoApos(Q, s);
			}
		} while(LIS_AvancarElementoCorrente(arestas, 1) != LIS_CondRetFimLista);
	}

	LIS_DestruirLista(V);
	LIS_DestruirLista(Q);

	return achou;
}

static void ExcluirAresta (GRA_tppGrafo grafo, GRA_tpVertice* v, GRA_tpVertice* u) {
	RemoverAresta(u, v);
	RemoverAresta(v, u);
	//BFS pra detectar se é necessário gerar nova componente.
	if (BFS(v,u) == 0) { //Estão em componentes distintas
		LIS_InserirElementoApos(grafo->componentes, u);
	}
}

static GRA_tpVertice* ObterOrigem (GRA_tppGrafo grafo, GRA_tpVertice* v) {
	GRA_tpVertice* u = NULL;
	LIS_tppLista origens = grafo->componentes;

	if (LIS_ProcurarValor(origens, v) == LIS_CondRetOK) {
		return v; //é a origem da própria componente
	}

	LIS_IrInicioLista(origens);

	do {
		u = LIS_ObterValor(origens);
		if (BFS(u,v) != 0) {
			return u;
		}
	} while(LIS_AvancarElementoCorrente(origens, 1) != LIS_CondRetFimLista);
	return NULL;//Deve ter algo errado;
}



/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: GRA  &Criar Grafo
*  ****/


	 GRA_tppGrafo GRA_CriarGrafo( void (*ExcluirValor) (void* pDado) )
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
				if (no->pValor != NULL) {
					g->ExcluirValor(no->pValor);
				}
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

		#ifdef _DEBUGa
			 assert( g != NULL ) ;
		#endif

		/* Criar o Vertice antes */

		GRA_tppVertice pElem = (GRA_tppVertice) CriarVertice( g ) ;
		
        if ( pElem == NULL )
			return GRA_CondRetFaltouMemoria ;

	 	if( LIS_InserirElementoApos (g->componentes, pElem) != LIS_CondRetOK)
			return GRA_CondRetFaltouMemoria ;
		 
		*pVertice = pElem;
        
        if (g->corrente == NULL) 
            g->corrente = pElem;

		return GRA_CondRetOK ;

	 } 
	 /* Fim função: GRA  &Inserir vertice */

//apaga um vertice e suas referencias
void GRA_RemoverVertice (GRA_tpGrafo* g, GRA_tpVertice* v) {
	GRA_tpVertice* vizinho = NULL;
	tpNode* no = NULL;

	if (g->vertices == NULL) {
		return;
	}
	if (LIS_ProcurarValor(g->vertices, v) != LIS_CondRetOK) { //Verifica se vertice pertence ao grafo, factualmente
		return;
	}
	
	no = LIS_ObterValor(g->vertices);
	g->ExcluirValor(no->pValor);

	LIS_IrInicioLista(no->arestas);

	do {
		vizinho = LIS_ObterValor(no->arestas);
		ExcluirAresta(g, v, vizinho); //Caro!
	} 
	while (LIS_AvancarElementoCorrente(no->arestas, 1) != LIS_CondRetFimLista);

	LIS_DestruirLista(no->arestas);
	free(no);

	LIS_ExcluirElemento(g->vertices);
}

GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, GRA_tppVertice pVertice1, GRA_tppVertice pVertice2 ) {
	GRA_tpVertice* origem1= NULL;
	GRA_tpVertice* origem2= NULL;
	/* Verifica se vertice pertence ao grafo; */
 	if (LIS_ProcurarValor(pGrafo->vertices, pVertice1) != LIS_CondRetOK) {
		return GRA_CondRetNaoEhVertice;
	}

	/* Verifica se vertice pertence ao grafo; */
	if (LIS_ProcurarValor(pGrafo->vertices, pVertice2) != LIS_CondRetOK) {
		return GRA_CondRetNaoEhVertice;
	}

	if (pVertice1 == pVertice2) {
		return GRA_CondRetEhVizinho;
	}

	if (LIS_ProcurarValor(pVertice1->pNode->arestas, pVertice2) != LIS_CondRetOK && 
		LIS_ProcurarValor(pVertice2->pNode->arestas, pVertice1) != LIS_CondRetOK ) {

		origem1 = ObterOrigem(pGrafo, pVertice1);
		origem2 = ObterOrigem(pGrafo, pVertice2);

		if (origem1 != origem2) { //Estavam em componentes distintas? Se sim, junta
			LIS_ProcurarValor(pGrafo->componentes, origem1);
			LIS_ExcluirElemento(pGrafo->componentes);
		}

		LIS_InserirElementoApos(pVertice1->pNode->arestas, pVertice2);
		LIS_InserirElementoApos(pVertice2->pNode->arestas, pVertice1);

		return GRA_CondRetOK;
	} 
	else {
		return GRA_CondRetEhVizinho;
	}
}

GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo , GRA_tppVertice pVertice1, GRA_tppVertice pVertice2 ) {

 	/* Verifica se vertice pertence ao grafo; */
 	if (LIS_ProcurarValor(pGrafo->vertices, pVertice1) != LIS_CondRetOK) {
		return GRA_CondRetNaoEhVertice;
	}

	/* Verifica se vertice pertence ao grafo; */
	if (LIS_ProcurarValor(pGrafo->vertices, pVertice2) != LIS_CondRetOK) {
		return GRA_CondRetNaoEhVertice;
	}

	ExcluirAresta(pGrafo, pVertice1, pVertice2);

	return GRA_CondRetOK;
}

GRA_tpCondRet GRA_AcessarCorrente ( GRA_tppGrafo pGrafo , void * pDado ) {
    if (pGrafo->corrente == NULL) 
        return GRA_CondRetGrafoVazio;
    pDado = pGrafo->corrente->pNode->pValor;
	return GRA_CondRetOK;
}

GRA_tpCondRet GRA_IrParaVizinho ( GRA_tppGrafo pGrafo, GRA_tppVertice pVertice ) {
   if (pVertice == NULL) 
       return GRA_CondRetNaoEhVertice; 
   if (LIS_ProcurarValor(pGrafo->corrente->pNode->arestas, pVertice) != LIS_CondRetOK)
       return GRA_CondRetNaoEhVertice; 
   pGrafo->corrente = pVertice;
   return GRA_CondRetOK;
}

