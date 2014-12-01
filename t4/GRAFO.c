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
*        1     eav   25/09/2014     //
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>

#ifdef _DEBUG
    #include <assert.h>
    #include "CONTA.H"
    #include "CESPDIN.H"
    #define ID_VER_tppVertice 1
#endif

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

                void * pValor ;
                /* Ponteiro para o valor contido no elemento */

                LIS_tppLista arestas ;
                //Lista de tppVertice
                /* Ponteiro para lista de aresta */
     } tpNode ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de vértice
*
*
***********************************************************************/

     typedef struct tpVertice_ {
        tpNode * pNode ;
        int id;
#ifdef _DEBUG
        int tipo;
        GRA_tppGrafo pGrafo;
        int tam;
#endif
                             /* Ponteiro para a cabeça de nó */      
     } tpVertice ;

    
    

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento de Aresta
*
*
***********************************************************************/

     typedef struct tpAresta_ {

                tpVertice * pVizinho ;
                /* Ponteiro para o valor contido no elemento */
                int id;
     } tpAresta ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de grafo
*
*
***********************************************************************/

    typedef struct GRA_tagGrafo {
        LIS_tppLista vertices;
        
        int corrente;

        LIS_tppLista componentes;
     
        void ( * ExcluirValor ) ( void * pValor ) ;
#ifdef _DEBUG
        int numVertice;
        int tam;
#endif                
                
                 /* Ponteiro para a função de destruição do valor contido em um elemento */
     } GRA_tpGrafo;

/***** Protótipos das funções encapsuladas no módulo *****/

static void RemoverAresta(tpVertice* u, tpVertice* v);

static tpVertice* CriarVertice(GRA_tppGrafo grafo, void* pValor, int id);

static int BFS(tpVertice* v, tpVertice* u);

static GRA_tpCondRet ExcluirVertice (GRA_tppGrafo pGrafo, tpVertice* pVertice);

static GRA_tpCondRet ExcluirAresta (GRA_tppGrafo grafo, tpVertice* v, tpVertice* u);

static tpVertice * ObterOrigem (GRA_tppGrafo grafo, tpVertice* v);

static tpVertice * get_by_id(GRA_tppGrafo grafo,int idVertice);

static int EhVizinho(GRA_tppGrafo grafo,tpVertice * v, tpVertice * u);

static void get_pair_by_id(GRA_tppGrafo grafo, int idAresta, tpVertice ** u, tpVertice ** v);

static tpAresta* get_edge_by_vertex(LIS_tppLista  l, tpVertice * v);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA  &Criar Grafo
*  ****/

     GRA_tppGrafo GRA_CriarGrafo( void (*ExcluirValor) (void* pDado) )
     {

            GRA_tpGrafo * pGrafo = NULL ;
            LIS_tppLista l_vertice = NULL;
            LIS_tppLista l_componente = NULL;

            pGrafo = (GRA_tpGrafo*) malloc(sizeof(GRA_tpGrafo)) ;
            memset(pGrafo, 0, sizeof(GRA_tpGrafo));
            if (pGrafo == NULL) {
                 return NULL ;
            } /* if */
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_CriarGrafo" ) ;
            #endif

            l_vertice = LIS_CriarLista(free); //A Exclusão será manual, iterando sobre os elementos;
            if (l_vertice == NULL) {
                free(pGrafo);
                return NULL;
            }
            l_componente = LIS_CriarLista(NULL); //Controle interno e autocontido; Componentes não cuidam de dados do valor, só armazenam ponteiros.
            if (l_componente == NULL) {
                free(pGrafo);
                LIS_DestruirLista(l_vertice);
                return NULL;
            }
            
            pGrafo->vertices = l_vertice;
            pGrafo->componentes = l_componente;
            pGrafo->ExcluirValor = ExcluirValor ;
            pGrafo->corrente = -1;
#ifdef _DEBUG
            CED_MarcarEspacoAtivo(pGrafo);
            pGrafo->numVertice = 0;
            pGrafo->tam = 0;
#endif

            return pGrafo;
     } 
     /* Fim função: GRA  &Criar grafo */

/***************************************************************************
*
*  Função: GRA  &Destruir grafo
*  ****/

     GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo )
     {
            tpVertice* pVertice = NULL;
            #ifdef _DEBUG
                 assert( pGrafo != NULL ) ;
            #endif
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_DestruirGrafo" ) ;
            #endif
            
            LIS_DestruirLista(pGrafo->componentes); //Lista que não mexe com "ninguém"

            LIS_IrInicioLista(pGrafo->vertices);
            do {
                            
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_DestruirGrafo-while0" ) ;
                #endif

                pVertice = (tpVertice *)LIS_ObterValor(pGrafo->vertices);
                if(pVertice == NULL) continue;

                if (pVertice->pNode->pValor != NULL && pGrafo->ExcluirValor != NULL) {
                    
                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_DestruirGrafo-if0" ) ;
                    #endif

                    pGrafo->ExcluirValor(pVertice->pNode->pValor);
                }
                LIS_DestruirLista(pVertice->pNode->arestas);
                free(pVertice->pNode);
            } 
            while(LIS_AvancarElementoCorrente(pGrafo->vertices, 1) == LIS_CondRetOK);

            LIS_DestruirLista(pGrafo->vertices);
            
            free( pGrafo ) ;
            
            return GRA_CondRetOK;
     } 
     /* Fim função: GRA  &Destruir grafo */


/***************************************************************************
*
*  Função: GRA  &Inserir vertice 
*  ****/

     GRA_tpCondRet GRA_InserirVertice (GRA_tppGrafo pGrafo, void* pValor, int id)
     {
        tpVertice * pElem = NULL ;
        #ifdef _DEBUG
             assert( pGrafo != NULL ) ;
        #endif
                         
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_InserirVertice" ) ;
        #endif

        /* Criar o Vertice antes */
        
        pElem = CriarVertice( pGrafo, pValor, id ) ;

#ifdef _DEBUG
        pElem->pGrafo = pGrafo;
        pElem->tam = CED_ObterTamanhoValor(pValor);
        pElem->tipo = CED_ObterTipoEspaco(pValor);
#endif
        
        if ( pElem == NULL ) {
            return GRA_CondRetFaltouMemoria ;
        }
        
        if( LIS_InserirElementoApos (pGrafo->vertices, pElem) != LIS_CondRetOK) {
            free(pElem);
            return GRA_CondRetFaltouMemoria ;   
        }
       
        if(pGrafo->corrente == -1) { 

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_InserirVertice-if0" ) ;
            #endif

            pGrafo->corrente = id;
        }
        LIS_NumeroDeElementos(pElem->pNode->arestas);
#ifdef _DEBUG
        (pGrafo->numVertice)++;
        pGrafo->tam += pElem->tam;
#endif
        return GRA_CondRetOK ;
     } 
     /* Fim função: GRA  &Inserir vertice */


/***************************************************************************
*
*  Função: GRA  &Excluir vertice 
*  ****/
     
    GRA_tpCondRet GRA_ExcluirVertice (GRA_tppGrafo pGrafo, int idVertice) {
        tpVertice * pVertice;

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ExcluirVertice" ) ;
        #endif
       
        pVertice = get_by_id(pGrafo, idVertice);

        if (pVertice == NULL) {
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirVertice-if0" ) ;
            #endif
            return GRA_CondRetNaoEhVertice;
        }
        
        return ExcluirVertice (pGrafo, pVertice);
    } 
    /* Fim função: GRA  &Excluir vertice */
  
/***************************************************************************
*
*  Função: GRA  &Inserir Aresta
*  ****/
  
    GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, int idVertice1, int idVertice2 , int idAresta) {
        tpVertice* origem1 = NULL;
        tpVertice* origem2 = NULL;
        tpAresta * aresta1 = NULL;
        tpAresta * aresta2 = NULL;
        tpVertice* pVertice1 = get_by_id(pGrafo,idVertice1);
        tpVertice* pVertice2 = get_by_id(pGrafo,idVertice2);
        
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_InserirAresta" ) ;
        #endif

        /* Verifica se vertice pertence ao grafo; */
        if (pVertice1 == NULL || pVertice2 == NULL) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_InserirAresta-if0" ) ;
            #endif

            return GRA_CondRetNaoEhVertice;
        }

        if (pVertice1 == pVertice2) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_InserirAresta-if1" ) ;
            #endif

            return GRA_CondRetEhVizinho;
        }
        if (!EhVizinho(pGrafo, pVertice1, pVertice2)  && 
            !EhVizinho(pGrafo, pVertice2, pVertice1) ) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_InserirAresta-if3" ) ;
            #endif


            origem1 = ObterOrigem(pGrafo, pVertice1);
            origem2 = ObterOrigem(pGrafo, pVertice2);

            aresta1 = ( tpAresta * ) malloc(sizeof( tpAresta )) ;
            if (aresta1 == NULL){
                return GRA_CondRetFaltouMemoria;
            }
            aresta2 = ( tpAresta * ) malloc(sizeof( tpAresta )) ;
            if (aresta2 == NULL ) {
                free(aresta1);
                return GRA_CondRetFaltouMemoria;
            }
            aresta1->id = idAresta;
            aresta2->id = idAresta;
            aresta1->pVizinho = pVertice2;
            aresta2->pVizinho = pVertice1;
            LIS_InserirElementoApos(pVertice1->pNode->arestas, aresta1);
            LIS_InserirElementoApos(pVertice2->pNode->arestas, aresta2);     

            if (origem1 != origem2) { //Estavam em componentes distintas? Se sim, junta
                
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_InserirAresta-if4" ) ;
                #endif

                LIS_IrInicioLista(pGrafo->componentes);
                LIS_ProcurarValor(pGrafo->componentes, origem1);
                LIS_ExcluirElemento(pGrafo->componentes);
            }
#ifdef _DEBUG
            CED_MarcarEspacoAtivo(pAresta);
#endif

            return GRA_CondRetOK;
        } 
        else {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_InserirAresta-else0" ) ;
            #endif

            return GRA_CondRetEhVizinho;
        }
    }
    /* Fim função: GRA  &Inserir Aresta */
  
/***************************************************************************
*
*  Função: GRA  &Excluir Aresta
*  ****/
          
    GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo , int idAresta ) {
        tpVertice * pVertice1 = NULL; 
        tpVertice * pVertice2 = NULL;

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ExcluirAresta" ) ;
        #endif

        get_pair_by_id(pGrafo,idAresta, &pVertice1, &pVertice2);

        if (pVertice1 == NULL || pVertice2 == NULL) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirAresta-if0" ) ;
            #endif

            return GRA_CondRetNaoEhVertice;
        }

        if(!EhVizinho(pGrafo,pVertice1,pVertice2)){
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirAresta-if1" ) ;
            #endif

            return GRA_CondRetNaoEhVizinho;
        }

        return ExcluirAresta(pGrafo, pVertice1, pVertice2);

    }
    /* Fim função: GRA  &Excluir Aresta */

  
  
/***************************************************************************
*
*  Função: GRA  &Obter Vizinhos
*  ****/
     
    GRA_tpCondRet GRA_ObterVizinhos ( GRA_tppGrafo pGrafo, int idVertice, LIS_tppLista* pLista) {
        
        tpVertice * pVertice = get_by_id(pGrafo,idVertice);
        LIS_tppLista vizinhos = NULL;
        LIS_tppLista Ret_vizinhos = NULL;
        tpAresta* aresta = NULL;
        int* idVerticeVizinho = NULL;

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ObterVizinhos" ) ;
        #endif

        if (pVertice == NULL) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterVizinhos-if0" ) ;
            #endif

            return GRA_CondRetNaoEhVertice; 
        }

        Ret_vizinhos = LIS_CriarLista(free);
        if (Ret_vizinhos == NULL) {
            return GRA_CondRetFaltouMemoria;
        }

        vizinhos = pVertice->pNode->arestas;

        LIS_IrInicioLista(vizinhos);

        if (LIS_NumeroDeElementos(vizinhos) > 0) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterVizinhos-if1" ) ;
            #endif

            do {

                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_ObterVizinhos-while0" ) ;
                #endif

                idVerticeVizinho = (int*) malloc(sizeof(int));
                *idVerticeVizinho = 0;
                aresta = (tpAresta *)LIS_ObterValor(vizinhos);           
                (*idVerticeVizinho) = aresta->pVizinho->id;
                if (LIS_InserirElementoApos( Ret_vizinhos, idVerticeVizinho) != LIS_CondRetOK ) {
                    LIS_DestruirLista(Ret_vizinhos);
                    return GRA_CondRetFaltouMemoria;
                }
            }
            while(LIS_AvancarElementoCorrente(vizinhos, 1) == LIS_CondRetOK);
        }
        *pLista = Ret_vizinhos;

        return GRA_CondRetOK;
    }
    /* Fim função: GRA  &Obter Vizinhos */

/***************************************************************************
*
*  Função: GRA  &Obter Vizinhos Corrente
*  ****/
     
    GRA_tpCondRet GRA_ObterVizinhosCorrente ( GRA_tppGrafo pGrafo, LIS_tppLista * pLista) {
        
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ObterVizinhosCorrente" ) ;
        #endif

        if (pGrafo->corrente == -1 ) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterVizinhosCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio; 
        }
        return GRA_ObterVizinhos(pGrafo, pGrafo->corrente, pLista);
    }
    /* Fim função: GRA  &Obter Vizinhos Corrente*/

/***************************************************************************
*
*  Função: GRA  &Obter Origens
*  ****/
     
    GRA_tpCondRet GRA_ObterOrigens( GRA_tppGrafo pGrafo, LIS_tppLista * pLista) {
        LIS_tppLista Ret_origens = NULL;    
        LIS_tppLista origens = NULL ;
        tpVertice * no;

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ObterOrigens" ) ;
        #endif

        Ret_origens = LIS_CriarLista(NULL);  
        if (Ret_origens == NULL) {
            return GRA_CondRetFaltouMemoria;
        }
        
        origens = pGrafo->componentes;

        LIS_IrInicioLista(origens);
        do {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterOrigens-while0" ) ;
            #endif

            no = (tpVertice *)LIS_ObterValor(origens);
            if(no == NULL) break;
            if(LIS_InserirElementoApos(Ret_origens,&(no->id)) != LIS_CondRetOK)
                return GRA_CondRetFaltouMemoria;
        } 
        while(LIS_AvancarElementoCorrente(origens, 1) == LIS_CondRetOK);
        
        *pLista = Ret_origens;

        return GRA_CondRetOK;
    }
    /* Fim função: GRA  &Obter Origens */
 
    
/***************************************************************************
*
*  Função: GRA  &Obter Valor
*  ****/    
    
    GRA_tpCondRet GRA_ObterValor( GRA_tppGrafo pGrafo , int idVertice , void** pDado ) {
        tpVertice * pVertice;

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ObterValor" ) ;
        #endif

        pVertice = get_by_id(pGrafo,idVertice);
        
        /* Verifica se vertice pertence ao grafo; */
        if (pVertice == NULL) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterValor-if0" ) ;
            #endif

            return GRA_CondRetNaoEhVertice;
        }
        
        *pDado = pVertice->pNode->pValor;

        return GRA_CondRetOK;

    }
    /* Fim função: GRA  &Obter Valor */   


/***************************************************************************
*
*  Função: GRA  &Obter Valor Corrente
*  ****/    
    
    GRA_tpCondRet GRA_ObterValorCorrente( GRA_tppGrafo pGrafo, void** pDado ) {

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ObterValorCorrente" ) ;
        #endif

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterValorCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio;
        }
        return GRA_ObterValor(pGrafo, pGrafo->corrente, pDado);

    }
    /* Fim função: GRA  &Obter Valor Corrente */


/***************************************************************************
*
*  Função: GRA  &Obter ID Corrente
*  ****/ 
    
    GRA_tpCondRet GRA_ObterIDCorrente( GRA_tppGrafo pGrafo, int* id ) {

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ObterIDCorrente" ) ;
        #endif

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterIDCorrente-if0" ) ;
            #endif

            *id = -1 ;
            return GRA_CondRetGrafoVazio;
        }
        else {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ObterIDCorrente-else0" ) ;
            #endif

            *id = pGrafo->corrente;
            return GRA_CondRetOK;
        }
    }
    /* Fim função: GRA  &Obter ID Corrente */
    
    
/***************************************************************************
*
*  Função: GRA  &Alterar Valor
*  ****/    
    
    GRA_tpCondRet GRA_AlterarValor( GRA_tppGrafo pGrafo , int idVertice , void* pDado ) {
        tpVertice * pVertice;

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_AlterarValor" ) ;
        #endif

        pVertice = get_by_id(pGrafo,idVertice);
        /* Verifica se vertice pertence ao grafo; */
        if (pVertice == NULL) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_AlterarValor-if0" ) ;
            #endif

            return GRA_CondRetNaoEhVertice;
        }
#ifdef _DEBUG
        pGrafo->tam -= pVertice->tam;
        pVertice->tipo = CED_ObterTipoEspaco(pDado);
        pVertice->tam = CED_ObterTamanhoValor(pDado);
        pGrafo->tam += pVertice->tam;
#endif        
        pVertice->pNode->pValor = pDado;
            
        return GRA_CondRetOK;

    }
    /* Fim função: GRA  &Alterar Valor */

/***************************************************************************
*
*  Função: GRA  &Alterar Valor Corrente
*  ****/    
    
    GRA_tpCondRet GRA_AlterarValorCorrente( GRA_tppGrafo pGrafo , void* pDado ) {

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_AlterarValorCorrente" ) ;
        #endif

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_AlterarValorCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio;
        }
      
        return GRA_AlterarValor(pGrafo, pGrafo->corrente, pDado);
    }

    /* Fim função: GRA  &Alterar Valor Corrente*/


/***************************************************************************
*
*  Função: GRA  &Excluir Vizinho Corrente
*  ****/
     
    GRA_tpCondRet GRA_ExcluirVizinhoCorrente (GRA_tppGrafo pGrafo, int idVertice) {
        
        tpVertice * pVertice = NULL;
        tpVertice * pVerticeCorrente = NULL;
        int achou = 0;
 
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_ExcluirVizinhoCorrente" ) ;
        #endif

        if (pGrafo->corrente == -1) { //Checagem de grafo vazio
             
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirVizinhoCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio ;
        }

        pVerticeCorrente = get_by_id( pGrafo, pGrafo->corrente );
        if(pVerticeCorrente == NULL) {
             
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirVizinhoCorrente-if1" ) ;
            #endif

            return GRA_CondRetGrafoVazio ; //Questionável
        }
        
        pVertice = get_by_id(pGrafo,idVertice);
        if (pVertice == NULL) {
             
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirVizinhoCorrente-if2" ) ;
            #endif

            return GRA_CondRetNaoEhVertice;
        }
        
        achou = EhVizinho( pGrafo, pVertice , pVerticeCorrente );
        
        if(achou) {
             
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirVizinhoCorrente-if3" ) ;
            #endif

            return ExcluirVertice(pGrafo, pVertice);
        }
        else {    

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_ExcluirVizinhoCorrente-else0" ) ;
            #endif

            return GRA_CondRetNaoEhVizinho ;
        }
    } 
    /* Fim função: GRA  &Excluir vizinho corrente */


/***************************************************************************
*
*  Função: GRA  &Ir Vizinho Corrente
*  ****/    
    
    GRA_tpCondRet GRA_IrVizinhoCorrente( GRA_tppGrafo pGrafo , int id ) {
        tpVertice * vizinho = NULL;
 
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_IrVizinhoCorrente" ) ;
        #endif

        /* Verifica se o grafo não está vazio(possui corrente); */
        if (pGrafo->corrente == -1) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_IrVizinhoCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio;
        }
        vizinho = get_by_id(pGrafo,id);
        if (vizinho == NULL) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_IrVizinhoCorrente-if1" ) ;
            #endif

            return GRA_CondRetNaoEhVertice;
        }
        
        if (!EhVizinho(pGrafo,get_by_id(pGrafo,pGrafo->corrente),vizinho)) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_IrVizinhoCorrente-if2" ) ;
            #endif

            return GRA_CondRetNaoEhVizinho;  
        }

        pGrafo->corrente = id;
        return GRA_CondRetOK;

    }
    /* Fim função: GRA  &Ir Vizinho Corrente */




/***************************************************************************
*
*  Função: GRA  &Inserir Vizinho Corrente
*  ****/    
    
    GRA_tpCondRet GRA_InserirVizinhoCorrente( GRA_tppGrafo pGrafo , void* pValor, int idVertice, int idAresta ) {

        GRA_tpCondRet r;
 
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_InserirVizinhoCorrente" ) ;
        #endif

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
             
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_InserirVizinhoCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio;
        }

        r = GRA_InserirVertice(pGrafo, pValor, idVertice);
        if(r != GRA_CondRetOK){
          
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_InserirVizinhoCorrente-if1" ) ;
            #endif

            return r;
        }
        return GRA_InserirAresta(pGrafo,idVertice,pGrafo->corrente,idAresta);

    }
    /* Fim função: GRA  &Ir Vizinho Corrente */

    

/***************************************************************************
*
*  Função: GRA  &Mudar Corrente
*  ****/    
    
    GRA_tpCondRet GRA_MudarCorrente( GRA_tppGrafo pGrafo , int id ) {
        tpVertice * vizinho = NULL;
 
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_MudarCorrente" ) ;
        #endif

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
             
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_MudarCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio;
        }
        vizinho = get_by_id(pGrafo,id);
        if(vizinho == NULL){
         
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_MudarCorrente-if1" ) ;
            #endif

            return GRA_CondRetNaoEhVertice;
        }
        
        LIS_ProcurarValor(pGrafo->vertices,vizinho);

        pGrafo->corrente = id;
        return GRA_CondRetOK;

    }
    /* Fim função: GRA  &Mudar Corrente */


/***************************************************************************
*
*  Função: GRA  &Buscar caminho corrente
*  ****/    

      GRA_tpCondRet GRA_BuscarCaminhoCorrente( GRA_tppGrafo pGrafo , int idVerticeDestino, LIS_tppLista * pLista ) {

        /* Verifica se vertice pertence ao grafo; */
  
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminhoCorrente" ) ;
        #endif

        if (pGrafo->corrente == -1) {  

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminhoCorrente-if0" ) ;
            #endif

            return GRA_CondRetGrafoVazio;
        }
        
        return GRA_BuscarCaminho(pGrafo, pGrafo->corrente,idVerticeDestino,pLista);
    }
    /* Fim função: GRA  &Buscar caminho corrente */


/***************************************************************************
*
*  Função: GRA  &NewInt
*  ****/    

    static void* newInt(int id) {
        int* val = (int*)malloc(sizeof(int));
        *val = id;
        return (void*)val;
    }
/***************************************************************************
*
*  Função: GRA  &NewInt
*  ****/    


    static int getInt(void* pt) {
        return *((int*)pt);
    }

/***************************************************************************
*
*  Função: GRA  &converteListaParaVetorDeInteiros
*  ****/    

    static int* converteListaParaVetorDeInteiros(LIS_tppLista lista, int* len) {
        int* vet;
        *len = 0;
        if (lista == NULL || LIS_NumeroDeElementos(lista) == 0) {
            return NULL;
        }
        vet = (int*)malloc(LIS_NumeroDeElementos(lista)*sizeof(int));
        memset(vet, 0, LIS_NumeroDeElementos(lista)*sizeof(int));
        LIS_IrInicioLista(lista);
        do {
            vet[*len] = getInt(LIS_ObterValor(lista));
            *len = (*len)+1;
        } while(LIS_AvancarElementoCorrente(lista, 1) == LIS_CondRetOK);

        return vet;
    }

/***************************************************************************
*
*  Estrutura auxiliar: indiceDistancia;
*  ****/

    typedef struct _Dist Dist;
    struct _Dist {
        int id;
        int dist;
        Dist* prev;
    };

/***************************************************************************
*
*  Função: GRA  &newDist
*  ****/    

    static Dist* newDist(int id, int dist) {
        Dist* d = (Dist*)malloc(sizeof(Dist));
        d->id = id;
        d->dist = dist;
        d->prev = NULL;
        return d;
    }

/***************************************************************************
*
*  Função: GRA  &getDist
*  ****/   

    static Dist* getDist(Dist** dists, int id) {
        int i;
        for (i=0; dists[i]; i++) {
            if (dists[i]->id == id) {
                return dists[i];
            }
        }
        return NULL;
    }

/***************************************************************************
*
*  Função: GRA  &Buscar caminho 
*  ****/    
    
    GRA_tpCondRet GRA_BuscarCaminho( GRA_tppGrafo pGrafo , int idVerticeOrigem, int idVerticeDestino, LIS_tppLista * pLista ) {
        tpVertice * v = NULL;
        tpVertice * u = NULL;         
        tpVertice * origem1 = NULL;
        tpVertice * origem2 = NULL;
        int lenV = 0;
        LIS_tppLista Q = NULL; //FILA
        LIS_tppLista arestas = NULL;
        LIS_tppLista retorno = NULL;
        int t;
        int len = 0;
        int achou = 0;
        int ok = 0;
        int i,j,in;
        int lenD;
        int alt = 0;
        int* visitados = NULL; // Vetor de vertices visitados
        int* vizinhos = NULL;
        Dist** dists = NULL;
        Dist* dist = NULL; //aux;
        Dist* currDist = NULL;
 
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminho" ) ;
        #endif

        lenD = 1;

        *pLista = NULL; // Limpando o ponteiro

        v = get_by_id(pGrafo, idVerticeOrigem);
        u = get_by_id(pGrafo, idVerticeDestino);
        if(v == NULL || u == NULL) { 

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-if0" ) ;
            #endif

            return GRA_CondRetNaoEhVertice; 
        }

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminho-pr0" ) ;
        #endif

        origem1 = ObterOrigem(pGrafo, v);
        origem2 = ObterOrigem(pGrafo, u);
        if (origem1 != origem2) { 

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-if1" ) ;
            #endif

            return GRA_CondRetNaoEhConexo;
        }//Else: É conexo, devia retornar Ok.
        
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminho-pr1" ) ;
        #endif

        for (;;) {
            dists = (Dist**)malloc((LIS_NumeroDeElementos(pGrafo->vertices)+1)* sizeof(Dist*));
            memset(dists, 0, (LIS_NumeroDeElementos(pGrafo->vertices)+1)* sizeof(Dist*));
            if (dists == NULL) {
                break;
            }
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr2" ) ;
            #endif

            dists[0] = newDist(idVerticeOrigem, 0);

            retorno = LIS_CriarLista(free);
            if (retorno == NULL) {
                break;
            }
            else if (v == u) {
                
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarCaminho-else0" ) ;
                #endif

                if( LIS_InserirElementoApos(retorno, newInt(idVerticeOrigem)) == LIS_CondRetOK) {
                    
                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_BuscarCaminho-if2" ) ;
                    #endif

                    *pLista = retorno;
                    return GRA_CondRetOK;
                } else {
                    break;
                }
            }
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr3" ) ;
            #endif

            visitados = (int*) malloc((LIS_NumeroDeElementos(pGrafo->vertices)+1)*sizeof(int));
            memset(visitados, 0,(LIS_NumeroDeElementos(pGrafo->vertices)+1)*sizeof(int) );
            if (visitados == NULL) {
                break;
            }         

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr4" ) ;
            #endif

            Q = LIS_CriarLista(free);
            if (Q == NULL) {      
                break;
            }            

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr5" ) ;
            #endif

            visitados[0] = idVerticeOrigem;
            lenV = 1;
            if (LIS_InserirElementoApos(Q, newInt(idVerticeOrigem)) != LIS_CondRetOK) {
                break;
            } //enque

            #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarCaminho-pr6" ) ;
            #endif

            ok = 1;
            break;
        }

        #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr7" ) ;
        #endif

        if (!ok) {
            free(dists);
            LIS_DestruirLista(retorno);
            free(visitados);
            LIS_DestruirLista(Q);
            return GRA_CondRetFaltouMemoria;
        }
        
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminho-pr8" ) ;
        #endif

        while (LIS_NumeroDeElementos(Q) > 0) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-while0" ) ;
            #endif

            //dequeue
            LIS_IrInicioLista(Q);
            t = getInt(LIS_ObterValor(Q));
            LIS_ExcluirElemento(Q);

            //Iterar sobre vizinhos
            GRA_ObterVizinhos(pGrafo, t, &arestas);
            vizinhos = converteListaParaVetorDeInteiros(arestas, &len);
            LIS_DestruirLista(arestas);
            arestas = NULL;

            currDist = getDist(dists, t);
            if(!currDist) {
                return GRA_CondRetFaltouMemoria;
            }

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr9" ) ;
            #endif

            alt = currDist->dist + 1;
            for (i=0; i < len; i++) {

                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarCaminho-for0" ) ;
                #endif

                in = 0;
                for (j=0; j < lenV; j++) {

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_BuscarCaminho-for1" ) ;
                    #endif

                    if (visitados[j] == vizinhos[i]) {
                        
                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_BuscarCaminho-if3" ) ;
                        #endif

                        in = 1;
                    }
                }
                if (!in) {
                    
                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_BuscarCaminho-if4" ) ;
                    #endif

                    dist = getDist(dists, vizinhos[i]);
                    if (dist == NULL) { //infinity

                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_BuscarCaminho-if5" ) ;
                        #endif

                        dists[lenD] = newDist(vizinhos[i], alt);
                        dists[lenD]->prev = currDist;
                        dist = dists[lenD];
                        lenD++;
                    } else if (alt < dist->dist) {
                        
                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_BuscarCaminho-else2" ) ;
                        #endif

                        dist->dist = alt;
                        dist->prev = currDist;
                    }
                    if (idVerticeDestino == vizinhos[i]) {
                        
                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_BuscarCaminho-if6" ) ;
                        #endif

                        currDist = dist;
                        achou = 1;
                    }

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_BuscarCaminho-pr9" ) ;
                    #endif

                    visitados[lenV] = vizinhos[i];
                    lenV++;
                    LIS_InserirElementoAntes(Q, newInt(vizinhos[i]));
                }
                
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarCaminho-pr10" ) ;
                #endif
            }
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr11" ) ;
            #endif

            free(vizinhos);
            if (achou) {
                
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarCaminho-if7" ) ;
                #endif

                currDist = dist;
                break;
            }         

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr12" ) ;
            #endif

            if(lenV == LIS_NumeroDeElementos(pGrafo->vertices)) {
                
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarCaminho-if8" ) ;
                #endif

                break;
            }
                        
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr13" ) ;
            #endif
        }         

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminho-pr14" ) ;
        #endif
        
        if (achou) {

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-if9" ) ;
            #endif

            //printf("\n");
            // for(i=0; i < lenD; i++) {
            //     printf("endr: %p, id: %d, dist: %d, prev: %p \n", *(dists+i), dists[i]->id, dists[i]->dist, dists[i]->prev);
            // }
            while (currDist) {
                
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarCaminho-while1" ) ;
                #endif

                LIS_InserirElementoAntes(retorno, newInt(currDist->id));
                currDist  = currDist->prev;
            }
                        
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-pr15" ) ;
            #endif

        }
                    
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminho-pr16" ) ;
        #endif

        //Limpando a memória        
        for (i=0; i < lenD; i++) {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarCaminho-for2" ) ;
            #endif

            free(dists[i]);
        }
                    
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarCaminho-pr17" ) ;
        #endif

        free(dists);
        free(visitados);
        LIS_DestruirLista(Q);
        *pLista = retorno;
        return GRA_CondRetOK;
    }
    /* Fim função: GRA  &Buscar caminho */

    GRA_tpCondRet GRA_BuscarVertice( GRA_tppGrafo pGrafo , int* idVertice , int predicado(void* pDado, void* _parametro), void* parametro )
    {
        LIS_tppLista vertices;
        tpVertice* vertice;
        vertices = pGrafo->vertices;

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_BuscarVertice" ) ;
        #endif

        if(LIS_NumeroDeElementos(vertices) == 0){
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarVertice-if0" ) ;
            #endif

            *idVertice = -1;
            return GRA_CondRetGrafoVazio;
        }

        LIS_IrInicioLista(vertices);
        do
        {
            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_BuscarVertice-while0" ) ;
            #endif

            vertice = (tpVertice*)LIS_ObterValor(vertices);
            
            if (predicado(vertice->pNode->pValor, parametro))
            {
                
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_BuscarVertice-if1" ) ;
                #endif

                *idVertice = vertice->id;
                return GRA_CondRetOK;
            }
        }
        while (LIS_AvancarElementoCorrente(vertices, 1) == LIS_CondRetOK);

        return GRA_CondRetNaoEhVertice;
    }
   
    
/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: GRA -Eh Vizinho
*
*  $ED Descrição da função
*      Procura o vértice v na lista de vizinhos de u
*      Se v for vizinho de u, retorna 1.
*      Se não, retorna 0.
*
***********************************************************************/

static int EhVizinho( GRA_tppGrafo pGrafo, tpVertice * v, tpVertice * u ){
    LIS_tppLista vizinhos = NULL;
    tpAresta * viz = NULL;
    int vizinho = 0;
 
    #ifdef _DEBUG
        CNT_CONTAR( "EhVizinho" ) ;
    #endif

    vizinhos = u->pNode->arestas;
    if(vizinhos == NULL){
        
        #ifdef _DEBUG
            CNT_CONTAR( "EhVizinho-if0" ) ;
        #endif

        return vizinho; 
    }
    LIS_IrInicioLista( vizinhos );
    do {      

        #ifdef _DEBUG
            CNT_CONTAR( "EhVizinho-while0" ) ;
        #endif

        viz = (tpAresta *)LIS_ObterValor(vizinhos);
        if(viz == NULL){
                    
            #ifdef _DEBUG
                CNT_CONTAR( "EhVizinho-if1" ) ;
            #endif

            break;
        }
        else if ( viz->pVizinho == v ){
                 
            #ifdef _DEBUG
                CNT_CONTAR( "EhVizinho-else0" ) ;
            #endif

            vizinho = 1 ;  
        }
    } while( LIS_AvancarElementoCorrente( vizinhos , 1) == LIS_CondRetOK ) ;
    
    return vizinho;
}


/***********************************************************************
*
*  $FC Função: GRA -Get by ID
*
*  $ED Descrição da função
*      Dado um idVertice, retorna a refêrencia para o vértice correspondente.
*      Caso não exista um vértice com a id passada, retorna NULL.
*      Caso o grafo esteja vazio, retorna NULL.
*
***********************************************************************/

static tpVertice * get_by_id(GRA_tppGrafo pGrafo , int idVertice){

        tpVertice * vertice = NULL;

        #ifdef _DEBUG
            CNT_CONTAR( "get_by_id" ) ;
        #endif

        if (pGrafo->vertices == NULL) {

            #ifdef _DEBUG
                CNT_CONTAR( "get_by_id-if0" ) ;
            #endif

            return NULL;
        }
        LIS_IrInicioLista(pGrafo->vertices);
        do {

            #ifdef _DEBUG
                CNT_CONTAR( "get_by_id-while0" ) ;
            #endif

            vertice = (tpVertice*)LIS_ObterValor( pGrafo->vertices ) ;
            if(vertice == NULL){
     
                #ifdef _DEBUG
                    CNT_CONTAR( "get_by_id-if1" ) ;
                #endif     

                return NULL;
            }
            else if(vertice->id == idVertice){
      
                #ifdef _DEBUG
                    CNT_CONTAR( "get_by_id-else0" ) ;
                #endif       

                return vertice;
            }
        }
        while ( LIS_AvancarElementoCorrente( pGrafo->vertices , 1) == LIS_CondRetOK ) ;
        
        return NULL;       
}

/***********************************************************************
*
*  $FC Função: GRA -Get Pair by ID
*
*  $ED Descrição da função
*      Busca as arestas do grafo pela idAresta passada.
*      Se achar, bota as refêrencias do par de vértices em u e v.
*
***********************************************************************/


void get_pair_by_id(GRA_tppGrafo pGrafo, int idAresta, tpVertice ** u, tpVertice ** v){
    tpAresta * aresta = NULL;
    tpVertice * vertice = NULL;
     
    #ifdef _DEBUG
        CNT_CONTAR( "get_pair_by_id" ) ;
    #endif

    LIS_IrInicioLista( pGrafo->vertices );

    // Para cada vértice
    do{     

        #ifdef _DEBUG
            CNT_CONTAR( "get_pair_by_id-while0" ) ;
        #endif

        vertice = (tpVertice*)LIS_ObterValor( pGrafo->vertices ) ;
        if(vertice == NULL){
                 
            #ifdef _DEBUG
                CNT_CONTAR( "get_pair_by_id-if0" ) ;
            #endif

            break;
        }
        LIS_IrInicioLista( vertice->pNode->arestas ) ;
        // Procura em todos os seus vizinhos
        do{

            #ifdef _DEBUG
                CNT_CONTAR( "get_pair_by_id-while1" ) ;
            #endif

            aresta = (tpAresta*)LIS_ObterValor( vertice->pNode->arestas ) ;
            
            if(aresta == NULL){

                #ifdef _DEBUG
                    CNT_CONTAR( "get_pair_by_id-if1" ) ;
                #endif

                continue;
            }
         
            if ( aresta->id == idAresta ){

                #ifdef _DEBUG
                    CNT_CONTAR( "get_pair_by_id-if2" ) ;
                #endif

                *u = vertice ;
                *v = aresta->pVizinho ;
                break;
            }
        }while(LIS_AvancarElementoCorrente( vertice->pNode->arestas , 1) == LIS_CondRetOK );
    }while ( LIS_AvancarElementoCorrente( pGrafo->vertices , 1) == LIS_CondRetOK ) ;
}


/***********************************************************************
*
*  $FC Função: GRA -Get edge by Vertex
*
*  $ED Descrição da função
*      Sendo a lista passada a lista de vizinhos de u,
       busca nos vizinhos a aresta (u,v)
*      Se achar, retorna uma referência para a aresta (u,v).
*      Se não achar, retorna NULL.
*
***********************************************************************/

/*
sendo l a lista de vizinhos de u
e v sendo o vertice passado
retorna uma referencia para a aresta u,v

*/

tpAresta* get_edge_by_vertex(LIS_tppLista  vizinhos, tpVertice * v){
        tpAresta * aresta =  NULL;  
         
        #ifdef _DEBUG
            CNT_CONTAR( "get_edge_by_vertex" ) ;
        #endif

        if (vizinhos == NULL) return NULL;
        
        LIS_IrInicioLista(vizinhos);
        do {

            #ifdef _DEBUG
                CNT_CONTAR( "get_edge_by_vertex-while0" ) ;
            #endif

            aresta = (tpAresta*)LIS_ObterValor(vizinhos); 
            if (aresta->pVizinho == v) {

                #ifdef _DEBUG
                    CNT_CONTAR( "get_edge_by_vertex-if0" ) ;
                #endif

                return aresta ;
            }
        }
        while ( LIS_AvancarElementoCorrente( vizinhos , 1) == LIS_CondRetOK ) ;
        
        return NULL;   
}






/***********************************************************************
*
*  $FC Função: GRA -Criar Vértice
*
*  $ED Descrição da função
*
***********************************************************************/

    //cria um vertice e sua estrutura interna
    static tpVertice* CriarVertice(GRA_tppGrafo grafo, void* pValor, int id) {
            tpVertice* v = NULL;    
            tpNode* no = NULL;
            LIS_tppLista arestas = NULL;
             
            #ifdef _DEBUG
                CNT_CONTAR( "CriarVertice" ) ;
            #endif

            v = (tpVertice*) malloc( sizeof(tpVertice) );
            if (v == NULL) {
                return NULL;
            }

            no = (tpNode*) malloc( sizeof(tpNode) );
            if (no == NULL) {
                free(v);
                return NULL;
            }

            arestas = LIS_CriarLista(free);
            if(arestas == NULL) {
                free(v);
                free(no);
                return NULL;
            }
            no->arestas = arestas;
            no->pValor = pValor; 
            v->pNode = no;
            v->id = id;

            if( LIS_InserirElementoApos (grafo->componentes, v) != LIS_CondRetOK) {
                free(v);
                free(no);
                LIS_DestruirLista(arestas);
                return NULL ;
            }

            #ifdef _DEBUG
                CED_DefinirTipoEspaco( v, ID_VER_tppVertice );
                CED_MarcarEspacoAtivo(v);
            #endif

            return v;
    }

/***********************************************************************
*
*  $FC Função: GRA -Remover Aresta
*
*  $ED Descrição da função
*
***********************************************************************/



    static void RemoverAresta(tpVertice* u, tpVertice* v) {
        LIS_tppLista vizinhos = NULL;
        tpAresta * aresta_v = NULL;
         
        #ifdef _DEBUG
            CNT_CONTAR( "RemoverAresta" ) ;
        #endif

        vizinhos = u->pNode->arestas;
        aresta_v = get_edge_by_vertex(vizinhos, v); 

        LIS_IrInicioLista(vizinhos);
        if (aresta_v != NULL && (LIS_ProcurarValor(vizinhos, aresta_v ) == LIS_CondRetOK)) {         
            
            #ifdef _DEBUG
                CNT_CONTAR( "RemoverAresta-if0" ) ;
            #endif

            LIS_ExcluirElemento(vizinhos);
        }
    }

/***********************************************************************
*
*  $FC Função: GRA -Excluir Vertice
*
*  $ED Descrição da função
*
***********************************************************************/

    static GRA_tpCondRet ExcluirVertice (GRA_tppGrafo pGrafo, tpVertice* pVertice) {
        tpAresta** vizinhos = NULL;
        tpNode* no = NULL;
        int i = 0;
         
        #ifdef _DEBUG
            CNT_CONTAR( "ExcluirVertice" ) ;
        #endif
        
        no = pVertice->pNode;
        LIS_IrInicioLista(pGrafo->componentes);
        LIS_ProcurarValor(pGrafo->componentes, pVertice);
        LIS_ExcluirElemento(pGrafo->componentes);

        if (LIS_NumeroDeElementos(no->arestas) > 0) {       

            #ifdef _DEBUG
                CNT_CONTAR( "ExcluirVertice-if1" ) ;
            #endif

            vizinhos = (tpAresta**)malloc(LIS_NumeroDeElementos(no->arestas)* sizeof(tpAresta*));
            memset(vizinhos,  0, LIS_NumeroDeElementos(no->arestas)* sizeof(tpAresta*));

            LIS_IrInicioLista(no->arestas);
            do {    

                #ifdef _DEBUG
                    CNT_CONTAR( "ExcluirVertice-while0" ) ;
                #endif

                vizinhos[i] = (tpAresta *)LIS_ObterValor(no->arestas);
                i++;
            } while ( LIS_AvancarElementoCorrente(no->arestas,1) == LIS_CondRetOK);
            
            for (; i; i--) {         

                #ifdef _DEBUG
                    CNT_CONTAR( "ExcluirVertice-for0" ) ;
                #endif

                ExcluirAresta(pGrafo, pVertice, vizinhos[i-1]->pVizinho); 
            }
            
            if (pGrafo->ExcluirValor != NULL && no->pValor != NULL) {   

                #ifdef _DEBUG
                    CNT_CONTAR( "ExcluirVertice-if2" ) ;
                #endif

                pGrafo->ExcluirValor(no->pValor);
                no->pValor = NULL;
            }
            free(vizinhos);
        }

        LIS_DestruirLista(no->arestas);
        no->arestas = NULL;

        pVertice->pNode = NULL;
        free(no);
        LIS_IrInicioLista(pGrafo->vertices);
        LIS_ProcurarValor(pGrafo->vertices, pVertice);
        LIS_ExcluirElemento(pGrafo->vertices);
        return GRA_CondRetOK;
    }


/***********************************************************************
*
*  $FC Função: GRA -Excluir Aresta
*
*  $ED Descrição da função
*
***********************************************************************/

    static GRA_tpCondRet ExcluirAresta (GRA_tppGrafo grafo, tpVertice* v, tpVertice* u) {
         
        #ifdef _DEBUG
            CNT_CONTAR( "ExcluirAresta" ) ;
        #endif
        
        RemoverAresta(v, u);//mexe só em v, ou deveria       
        RemoverAresta(u, v);

        //BFS pra detectar se é necessário gerar nova componente.
        if (BFS(v,u) != 1) { //Estão em componentes distintas         

            #ifdef _DEBUG
                CNT_CONTAR( "ExcluirAresta-if0" ) ;
            #endif

            if (LIS_InserirElementoApos(grafo->componentes, u) != LIS_CondRetOK) {

                #ifdef _DEBUG
                    CNT_CONTAR( "ExcluirAresta-if1" ) ;
                #endif

                return GRA_CondRetFaltouMemoria;
            }
        }
        return GRA_CondRetOK;
    }   
    
/***********************************************************************
*
*  $FC Função: GRA -BFS
*
*  $ED Descrição da função
*
*   0 nao achou
*   1 achou
*  -1 erro
***********************************************************************/

    static int BFS(tpVertice* v, tpVertice* u) {
        LIS_tppLista V = NULL; // LISTA VERTICE VISITADOS
        LIS_tppLista Q = NULL; //FILA
        LIS_tppLista arestas = NULL;
        tpVertice* t = NULL;
        tpVertice* s = NULL;
        tpVertice * re = NULL;
        tpAresta* a = NULL;
        int achou = 0;
        int achou_V = 0;


        #ifdef _DEBUG
            CNT_CONTAR( "BFS" ) ;
        #endif

        V = LIS_CriarLista(NULL); // dados são referenciados por outros, não devem ser apagados
        Q = LIS_CriarLista(NULL); // dados são referenciados por outros, não devem ser apagados

        LIS_InserirElementoApos(V, v);
        LIS_InserirElementoApos(Q, v); //Usado como uma Fila.
        while (LIS_NumeroDeElementos(Q) > 0) {

            #ifdef _DEBUG
                CNT_CONTAR( "BFS-while0" ) ;
            #endif

            LIS_IrInicioLista(Q);
            t = (tpVertice *)LIS_ObterValor(Q);
            LIS_ExcluirElemento(Q);
            if (t == u) {

                #ifdef _DEBUG
                    CNT_CONTAR( "BFS-if0" ) ;
                #endif

                achou = 1; 
                break;
            }
            arestas = t->pNode->arestas;
            LIS_IrInicioLista(arestas);
            do {

                #ifdef _DEBUG
                    CNT_CONTAR( "BFS-while1" ) ;
                #endif

                a = (tpAresta *)LIS_ObterValor(arestas);
                if(a == NULL) continue;
                s = a->pVizinho;
                
                LIS_IrInicioLista(V);
                achou_V = 0;
                do {
                    
                    #ifdef _DEBUG
                        CNT_CONTAR( "BFS-while2" ) ;
                    #endif

                    re = (tpVertice *)LIS_ObterValor(V);
                    if (re == NULL) {

                        #ifdef _DEBUG
                            CNT_CONTAR( "BFS-if1" ) ;
                        #endif

                        continue;
                    }
                    if(re == s){
                     
                        #ifdef _DEBUG
                            CNT_CONTAR( "BFS-if2" ) ;
                        #endif

                        achou_V = 1;
                    }
                } while(LIS_AvancarElementoCorrente(V, 1) == LIS_CondRetOK);
            
                if (!achou_V) {

                    #ifdef _DEBUG
                        CNT_CONTAR( "BFS-if3" ) ;
                    #endif

                    if(LIS_InserirElementoApos(V, s)!= LIS_CondRetOK){ achou = -1;break;}
                    if(LIS_InserirElementoApos(Q, s)!= LIS_CondRetOK){ achou = -1;break;}
                }
            } while(LIS_AvancarElementoCorrente(arestas, 1) == LIS_CondRetOK);
        }

        LIS_DestruirLista(V);
        LIS_DestruirLista(Q);

        return achou;
    }

/***********************************************************************
*
*  $FC Função: GRA -Obter Origem
*
*  $ED Descrição da função
*
***********************************************************************/
        
    static tpVertice* ObterOrigem (GRA_tppGrafo grafo, tpVertice* v) {
        tpVertice** us = NULL; //Vetor com componentes a iterar;
        tpVertice* u = NULL;
        LIS_tppLista origens = grafo->componentes;
        int i = 0; 

        #ifdef _DEBUG
            CNT_CONTAR( "ObterOrigem" ) ;
        #endif
        
        LIS_IrInicioLista(grafo->vertices);
        LIS_IrInicioLista(origens);
        if (LIS_ProcurarValor(origens, v) == LIS_CondRetOK) {

            #ifdef _DEBUG
                CNT_CONTAR( "ObterOrigem-if0" ) ;
            #endif

            return v; //é a origem da própria componente
        }
        if(LIS_NumeroDeElementos(origens) > 0) {

            #ifdef _DEBUG
                CNT_CONTAR( "ObterOrigem-if1" ) ;
            #endif

            us = (tpVertice**) malloc(LIS_NumeroDeElementos(origens) * sizeof(tpVertice*));
            memset(us, 0, LIS_NumeroDeElementos(origens) * sizeof(tpVertice*));

            LIS_IrInicioLista(origens);
            do {

                #ifdef _DEBUG
                    CNT_CONTAR( "ObterOrigem-while0" ) ;
                #endif

                u = (tpVertice *)LIS_ObterValor(origens);
                if(u == NULL){
                
                    #ifdef _DEBUG
                        CNT_CONTAR( "ObterOrigem-if1" ) ;
                    #endif

                    break;
                }
                us[i] = u;
                i++;
            } while(LIS_AvancarElementoCorrente(origens, 1) == LIS_CondRetOK);


            for ( ;i; i--) {

                #ifdef _DEBUG
                    CNT_CONTAR( "ObterOrigem-for0" ) ;
                #endif

                if (BFS(us[i-1],v) == 1) {

                    #ifdef _DEBUG
                        CNT_CONTAR( "ObterOrigem-if2" ) ;
                    #endif

                    u =  us[i-1];
                }
            }
            free(us);
        }

        return u;
    }


#ifdef _DEBUG

GRA_tpCondRet GRA_Verifica(GRA_tppGrafo g,int* Numerros){
    int numerros;
    int vertices, arestas, origens, i, ehSucessor;
    tpVertice * v,* o1,* o2,* sucessor;
    tpAresta * a;
    LIS_tppLista listaV, listaA, listaO, caminho, vizinhosAux;
    LIS_tpCondRet cr;
     
    #ifdef _DEBUG
        CNT_CONTAR( "GRA_Verifica" ) ;
    #endif
    
    numerros = 0;
    ehSucessor = -1;

    // listas auxiliares / V -> vertices / A -> arestas / O -> origens
    listaV = LIS_CriarLista(NULL);
    listaA = LIS_CriarLista(NULL);
    listaO = LIS_CriarLista(NULL);
    caminho = LIS_CriarLista(NULL); 
    vizinhosAux = LIS_CriarLista(NULL);

    //#origens <= #vertices
    vertices = LIS_NumeroDeElementos(g->vertices);
    origens = LIS_NumeroDeElementos(g->componentes);
    if(origens <= vertices){
        
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_Verifica-if0" ) ;
        #endif

        numerros++;
    }     

    #ifdef _DEBUG
        CNT_CONTAR( "GRA_Verifica-pr0" ) ;
    #endif

    //#arestas <= #vertices ^ 2
    if(g->vertices != NULL && LIS_NumeroDeElementos(g->vertices) >= 1){        
        
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_Verifica-if1" ) ;
        #endif

        listaV = g->vertices;
        LIS_IrInicioLista(listaV);
        arestas = 0;
        if (LIS_NumeroDeElementos(listaV) > 0) {      

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_Verifica-if2" ) ;
            #endif

            do{        

                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_Verifica-while0" ) ;
                #endif

                v = (tpVertice*)LIS_ObterValor(listaV);
                if (v != NULL && v->pNode != NULL) {       

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_Verifica-if3" ) ;
                    #endif

                    arestas += LIS_NumeroDeElementos(v->pNode->arestas);
                }
                        
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_Verifica-pr1" ) ;
                #endif

            }while(LIS_AvancarElementoCorrente(listaV,1) == LIS_CondRetOK);
                
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_Verifica-pr2" ) ;
            #endif

            arestas = arestas/2;
            if (arestas <= vertices*vertices) {
                        
                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_Verifica-if4" ) ;
                #endif

                numerros++;
            }
                            
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_Verifica-pr3" ) ;
            #endif
            
            //todo vertice tem um node (todo vertice eh valido)
            //toda aresta liga dois vertices validos
            LIS_IrInicioLista(listaV);
            do {    

                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_Verifica-while1" ) ;
                #endif

                v = (tpVertice*)LIS_ObterValor(listaV);
                if (v->pNode == NULL) {        

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_Verifica-if5" ) ;
                    #endif

                    numerros++;
                    break; 
                }      

                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_Verifica-pr4" ) ;
                #endif

                listaA = v->pNode->arestas;
                LIS_IrInicioLista(listaA);
                do{

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_Verifica-while2" ) ;
                    #endif

                    a = (tpAresta*)LIS_ObterValor(listaA);
                    if(a != NULL) {

                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_Verifica-if6" ) ;
                        #endif

                        if (a->pVizinho == NULL) { // Aresta aponta pra vizinho inexistente

                            #ifdef _DEBUG
                                CNT_CONTAR( "GRA_Verifica-if7" ) ;
                            #endif

                            numerros++;
                        } 
                        
                        else if(CED_ObterTamanhoValor(a->pVizinho) == -1) {
                            
                            #ifdef _DEBUG
                                CNT_CONTAR( "GRA_Verifica-else0" ) ;
                            #endif

                            numerros++;
                        }
                        
                        else if (a->pVizinho->pNode == NULL) { //Vizinho apontado pela aresta está quebrado    
                            
                            #ifdef _DEBUG
                                CNT_CONTAR( "GRA_Verifica-else1" ) ;
                            #endif

                            numerros++;
                        }      

                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_Verifica-pr5" ) ;
                        #endif

                        // a->pVizinho é sucessor de v ? 
                        vizinhosAux = a->pVizinho->pNode->arestas;
                        LIS_IrInicioLista(vizinhosAux);
                        do{

                            #ifdef _DEBUG
                                CNT_CONTAR( "GRA_Verifica-while3" ) ;
                            #endif

                            sucessor = (tpVertice*)LIS_ObterValor(vizinhosAux);
                            if(sucessor->id == v->id) {
   
                                #ifdef _DEBUG
                                    CNT_CONTAR( "GRA_Verifica-if8" ) ;
                                #endif

                                ehSucessor = 1;
                            }
                            
                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_Verifica-pr6" ) ;
                        #endif

                        }while(LIS_AvancarElementoCorrente(vizinhosAux,1) == LIS_CondRetOK);

                        if(ehSucessor == -1){
                               
                            #ifdef _DEBUG
                                CNT_CONTAR( "GRA_Verifica-if9" ) ;
                            #endif

                            numerros++;
                        }

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_Verifica-pr7" ) ;
                    #endif

                    }

                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_Verifica-pr8" ) ;
                #endif

                } while(LIS_AvancarElementoCorrente(listaA,1) == LIS_CondRetOK);
                
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_Verifica-pr9" ) ;
            #endif

            } while(LIS_AvancarElementoCorrente(listaV,1) == LIS_CondRetOK);
                            
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_Verifica-pr10" ) ;
        #endif

        }
                                    
    #ifdef _DEBUG
        CNT_CONTAR( "GRA_Verifica-pr11" ) ;
    #endif

    }

    if(g->componentes != NULL && LIS_NumeroDeElementos(g->componentes) > 1){
        //nao existem duas origens iguais

        //copia origens para lista auxiliar
        LIS_IrInicioLista(g->componentes);
        do{

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_Verifica-while4" ) ;
            #endif

            o1 = (tpVertice*)LIS_ObterValor(g->componentes);
            LIS_InserirElementoApos(listaO,(void*)o1);
        }while(LIS_AvancarElementoCorrente(g->componentes,1) == LIS_CondRetOK);
                                    
        #ifdef _DEBUG
            CNT_CONTAR( "GRA_Verifica-pr12" ) ;
        #endif

        LIS_IrInicioLista(g->componentes);
        do{

            #ifdef _DEBUG
                CNT_CONTAR( "GRA_Verifica-while5" ) ;
            #endif

            o1 = (tpVertice*)LIS_ObterValor(g->componentes);
            
            LIS_IrInicioLista(listaO);
            // busca origem na lista auxiliar e remove
            LIS_ProcurarValor(listaO,(void*)o1);
            LIS_ExcluirElemento(listaO);

            // Se não há outra componente, acabamos aqui; Se não
            if (LIS_NumeroDeElementos(listaO) > 0) {

                #ifdef _DEBUG
                    CNT_CONTAR( "GRA_Verifica-if10" ) ;
                #endif

                LIS_IrInicioLista(listaO);
                do {

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_Verifica-while6" ) ;
                    #endif

                    o2 = (tpVertice*)LIS_ObterValor(listaO);
                    if(o1 != o2){

                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_Verifica-if11" ) ;
                        #endif

                        numerros++;
                    }

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_Verifica-pr13" ) ;
                    #endif
                    
                    //as componentes conexas realmente sao conexas(não existe um caminho de uma origem para outra qualquer)
                    if(GRA_BuscarCaminho(g,o1->id,o2->id,&caminho) == GRA_CondRetNaoEhConexo){
                        
                        #ifdef _DEBUG
                            CNT_CONTAR( "GRA_Verifica-if14" ) ;
                        #endif
                    
                        numerros++;
                    }         

                    #ifdef _DEBUG
                        CNT_CONTAR( "GRA_Verifica-pr14" ) ;
                    #endif

                } while(LIS_AvancarElementoCorrente(listaO,1) == LIS_CondRetOK);
                                                    
            #ifdef _DEBUG
                CNT_CONTAR( "GRA_Verifica-pr15" ) ;
            #endif

            }   

        #ifdef _DEBUG
            CNT_CONTAR( "GRA_Verifica-pr16" ) ;
        #endif

        }while(LIS_AvancarElementoCorrente(g->componentes,1) == LIS_CondRetOK);

    #ifdef _DEBUG
        CNT_CONTAR( "GRA_Verifica-pr17" ) ;
    #endif

    }

    #ifdef _DEBUG
        CNT_CONTAR( "GRA_Verifica-pr18" ) ;
    #endif

    *Numerros = numerros;
    return GRA_CondRetOK;
} 

GRA_tpCondRet GRA_Deturpa(GRA_tppGrafo g, int acao){
    tpVertice* v;
    tpAresta* a;
    if(g->corrente!=-1)
        v = get_by_id(g, g->corrente);
    
    if( acao == 1 ) { //elimina o elemento corrente da estrutura escolhida.
        ExcluirVertice(g,v);      
        g->corrente = -1;
    }
    if( acao == 2 ) { //atribui NULL ao ponteiro para um vértice sucessor.
        LIS_IrInicioLista(v->pNode->arestas);
        a = LIS_ObterValor(v->pNode->arestas);
        if(a != NULL) {
            a->pVizinho = NULL;
        }   
    }
    if( acao == 3 ) { //atribui NULL ao ponteiro para um vértice predecessor.
        LIS_IrInicioLista(v->pNode->arestas);
        a = LIS_ObterValor(v->pNode->arestas);
        if(a != NULL) {
            v = a->pVizinho;
            LIS_IrInicioLista(v->pNode->arestas);
            a = LIS_ObterValor(v->pNode->arestas);
            if(a != NULL) {
                a->pVizinho = NULL;
            }
        }   
    }
    if (acao == 4) { //atribui lixo ao ponteiro para a referência a um vértice sucessor
        LIS_IrInicioLista(v->pNode->arestas);
        a = LIS_ObterValor(v->pNode->arestas);
        if(a != NULL) {
            a->pVizinho = (tpVertice*)0x00000001;
        }   
        
    }
    if (acao == 5) { //atribui lixo ao ponteiro para a referência a um vértice predecessor.
        LIS_IrInicioLista(v->pNode->arestas);
        a = LIS_ObterValor(v->pNode->arestas);
        if(a != NULL) {
            v = a->pVizinho;
            LIS_IrInicioLista(v->pNode->arestas);
            a = LIS_ObterValor(v->pNode->arestas);
            if(a != NULL) {
                a->pVizinho = (tpVertice*)0x00000001;
            }
        }   
        
    }
    if( acao == 6 ) { //atribui NULL ao ponteiro para o conteúdo do vértice.
        v->pNode = NULL;
    }
    if( acao == 7 ) { //altera o tipo de estrutura apontado no vértice.
        v->pNode = (tpNode*)0x00000001;
    }
    if( acao == 8 ) { //destaca vértice do grafo sem liberá-lo com free 

        LIS_EsvaziarLista(v->pNode->arestas);
        CED_MarcarEspacoNaoAtivo(v);
    }
    if( acao == 9 ) { //atribui NULL ao ponteiro corrente
        v = NULL;
    }
    if( acao == 10 ) { //atribui NULL a um ponteiro de origem.
        v = ObterOrigem(g,v);
        v = NULL;
    }
    return GRA_CondRetOK;
}


#endif

/********** Fim do módulo de implementação: GRA  Grafo **********/

