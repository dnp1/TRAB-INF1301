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
*  Função: GRA  &Obter Corrente
*  ****/    
    
    GRA_tpCondRet GRA_ObterCorrente( GRA_tppGrafo pGrafo , void** pDado ) {
        tpVertice * tpVertice = NULL;

        /* Verifica se vertice pertence ao grafo; */
        if ( pGrafo->corrente == -1 ) {
            return GRA_CondRetGrafoVazio;
        }
        tpVertice = get_by_id(pGrafo,pGrafo->corrente);
        *pDado = tpVertice->pNode->pValor;
        
        return GRA_CondRetOK;

    }
    /* Fim função: GRA  &Obter Corrente */   
    
/***************************************************************************
*
*  Função: GRA  &Criar Grafo
*  ****/


     GRA_tppGrafo GRA_CriarGrafo( void (*ExcluirValor) (void* pDado) )
     {

            GRA_tpGrafo * pGrafo = NULL ;
            LIS_tppLista l_vertice = NULL;
            LIS_tppLista l_componente = NULL;

            pGrafo = (GRA_tpGrafo*) calloc(1, sizeof(GRA_tpGrafo)) ;
            if (pGrafo == NULL) {
                 return NULL ;
            } /* if */
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
            
            LIS_DestruirLista(pGrafo->componentes); //Lista que não mexe com "ninguém"

            LIS_IrInicioLista(pGrafo->vertices);
            do {
                pVertice = (tpVertice *)LIS_ObterValor(pGrafo->vertices);
                if(pVertice == NULL) continue;

                if (pVertice->pNode->pValor != NULL && pGrafo->ExcluirValor != NULL) {
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
        int i;
        tpVertice * pElem = NULL ;
        tpVertice * v = NULL ;
        #ifdef _DEBUG
             assert( pGrafo != NULL ) ;
        #endif

        /* Criar o Vertice antes */
        
        pElem = CriarVertice( pGrafo, pValor, id ) ;
        
        if ( pElem == NULL ) {
            return GRA_CondRetFaltouMemoria ;
        }
        
        if( LIS_InserirElementoApos (pGrafo->vertices, pElem) != LIS_CondRetOK) {
            free(pElem);
            return GRA_CondRetFaltouMemoria ;   
        }
       
        if(pGrafo->corrente == -1) { 
            pGrafo->corrente = id;
        }
        LIS_NumeroDeElementos(pElem->pNode->arestas);
        return GRA_CondRetOK ;
     } 
     /* Fim função: GRA  &Inserir vertice */


/***************************************************************************
*
*  Função: GRA  &Excluir vertice 
*  ****/
     
    GRA_tpCondRet GRA_ExcluirVertice (GRA_tppGrafo pGrafo, int idVertice) {
        tpVertice * pVertice = get_by_id(pGrafo, idVertice);

        if (pVertice == NULL) {
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
        tpVertice* pVertice1 = get_by_id(pGrafo,idVertice1);
        tpVertice* pVertice2 = get_by_id(pGrafo,idVertice2);
        tpAresta* vizinho = NULL;   

        /* Verifica se vertice pertence ao grafo; */
        if (pVertice1 == NULL || pVertice2 == NULL) {
            return GRA_CondRetNaoEhVertice;
        }

        if (pVertice1 == pVertice2) {
            return GRA_CondRetEhVizinho;
        }
        if (!EhVizinho(pGrafo, pVertice1, pVertice2)  && 
            !EhVizinho(pGrafo, pVertice2, pVertice1) ) {
            tpAresta * aresta1 = NULL;
            tpAresta * aresta2 = NULL;

            origem1 = ObterOrigem(pGrafo, pVertice1);
            origem2 = ObterOrigem(pGrafo, pVertice2);

            aresta1 = ( tpAresta * ) calloc(1, sizeof( tpAresta )) ;
            if (aresta1 == NULL){
                return GRA_CondRetFaltouMemoria;
            }
            aresta2 = ( tpAresta * ) calloc(1, sizeof( tpAresta )) ;
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

                LIS_IrInicioLista(pGrafo->componentes);
                LIS_ProcurarValor(pGrafo->componentes, origem1);
                LIS_ExcluirElemento(pGrafo->componentes);
            }

            return GRA_CondRetOK;
        } 
        else {
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
        tpVertice * t = NULL;
        tpAresta * vizinho = NULL;
        int i;

        get_pair_by_id(pGrafo,idAresta, &pVertice1, &pVertice2);

        if (pVertice1 == NULL || pVertice2 == NULL) {
            return GRA_CondRetNaoEhVertice;
        }

        if(!EhVizinho(pGrafo,pVertice1,pVertice2)) return GRA_CondRetNaoEhVizinho;



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

        if (pVertice == NULL) 
            return GRA_CondRetNaoEhVertice; 

        Ret_vizinhos = LIS_CriarLista(free);
        if (Ret_vizinhos == NULL) {
            return GRA_CondRetFaltouMemoria;
        }

        vizinhos = pVertice->pNode->arestas;

        LIS_IrInicioLista(vizinhos);

        if(LIS_NumeroDeElementos(vizinhos) > 0){
            do {
                idVerticeVizinho = (int*) calloc(1, sizeof(int));
                aresta = (tpAresta *)LIS_ObterValor(vizinhos);           
                (*idVerticeVizinho) = aresta->pVizinho->id;
                if (LIS_InserirElementoApos( Ret_vizinhos, idVerticeVizinho) != LIS_CondRetOK ) {
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
       
        if (pGrafo->corrente == -1 ) 
            return GRA_CondRetGrafoVazio; 
        
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

        Ret_origens = LIS_CriarLista(NULL);  
        if (Ret_origens == NULL) {
            return GRA_CondRetFaltouMemoria;
        }
        
        origens = pGrafo->componentes;

        LIS_IrInicioLista(origens);
        do {
            tpVertice * no = (tpVertice *)LIS_ObterValor(origens);
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

        tpVertice * pVertice = get_by_id(pGrafo,idVertice);
        
        /* Verifica se vertice pertence ao grafo; */
        if (pVertice == NULL) {
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

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
            return GRA_CondRetGrafoVazio;
        }
        return GRA_ObterValor(pGrafo, pGrafo->corrente, pDado);

    }
    /* Fim função: GRA  &Obter Valor Corrente */

/***************************************************************************
*
*  Função: GRA  &Obter Valores
*  ****/  

    GRA_tpCondRet GRA_ObterValores( GRA_tppGrafo pGrafo, LIS_tppLista pValores ) {
        LIS_tppLista vertices;
        tpVertice* vertice;
        void* valor;
        vertices = pGrafo->vertices;
        LIS_IrInicioLista(vertices);
        do{
            valor = LIS_ObterValor(vertices);

            LIS_InserirElementoApos(pValores,valor);
            LIS_AvancarElementoCorrente(pValores,1);
        }while(LIS_AvancarElementoCorrente(vertices,1) == LIS_CondRetOK);
    }
    /* Fim função: GRA  &Obter Valores */


/***************************************************************************
*
*  Função: GRA  &Obter ID Corrente
*  ****/    
    
    GRA_tpCondRet GRA_ObterIDCorrente( GRA_tppGrafo pGrafo, int* id ) {

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
            *id = -1 ;
            return GRA_CondRetGrafoVazio;
        }
        else {
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

        tpVertice * pVertice = get_by_id(pGrafo,idVertice);
        /* Verifica se vertice pertence ao grafo; */
        if (pVertice == NULL) {
            return GRA_CondRetNaoEhVertice;
        }
        
        pVertice->pNode->pValor = pDado;
            
        return GRA_CondRetOK;

    }
    /* Fim função: GRA  &Alterar Valor */

/***************************************************************************
*
*  Função: GRA  &Alterar Valor Corrente
*  ****/    
    
    GRA_tpCondRet GRA_AlterarValorCorrente( GRA_tppGrafo pGrafo , void* pDado ) {

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
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
        
        tpAresta* vizinho = NULL;
        tpNode* no = NULL;
        GRA_tpCondRet r;
        tpVertice * pVertice = NULL;
        tpVertice * pVerticeCorrente = NULL;
        int achou = 0;
        
        if (pGrafo->corrente == -1) { //Checagem de grafo vazio
            return GRA_CondRetGrafoVazio ;
        }

        pVerticeCorrente = get_by_id( pGrafo, pGrafo->corrente );
        if(pVerticeCorrente == NULL) {
            return GRA_CondRetGrafoVazio ; //Questionável
        }
        
        pVertice = get_by_id(pGrafo,idVertice);
        if (pVertice == NULL) {
            return GRA_CondRetNaoEhVertice;
        }
        
        achou = EhVizinho( pGrafo, pVertice , pVerticeCorrente );
        
        if(achou) {
            return ExcluirVertice(pGrafo, pVertice);
        }
        else {     
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
        /* Verifica se o grafo não está vazio(possui corrente); */
        if (pGrafo->corrente == -1) {
            return GRA_CondRetGrafoVazio;
        }
        vizinho = get_by_id(pGrafo,id);
        if (vizinho == NULL) {
            return GRA_CondRetNaoEhVertice;
        }
        
        if (!EhVizinho(pGrafo,get_by_id(pGrafo,pGrafo->corrente),vizinho)) {
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
        tpVertice * vizinho = NULL;
        tpVertice * u;
        tpVertice * v;
        GRA_tpCondRet r;

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
            return GRA_CondRetGrafoVazio;
        }
       
        vizinho = get_by_id(pGrafo,idVertice);
        /*
        por hipotese nao precisamos checar isso
        if(vizinho != NULL)
            return GRA_CondRetEhVertice;
        
        if(EhVizinho(pGrafo,get_by_id(pGrafo,pGrafo->corrente),vizinho))
           return GRA_CondRetEhVizinho;  
        */
        r = GRA_InserirVertice(pGrafo, pValor, idVertice);
        if(r != GRA_CondRetOK) return r;
        return GRA_InserirAresta(pGrafo,idVertice,pGrafo->corrente,idAresta);

    }
    /* Fim função: GRA  &Ir Vizinho Corrente */

    

/***************************************************************************
*
*  Função: GRA  &Mudar Corrente
*  ****/    
    
    GRA_tpCondRet GRA_MudarCorrente( GRA_tppGrafo pGrafo , int id ) {
        tpVertice * vizinho = NULL;

        /* Verifica se vertice pertence ao grafo; */
        if (pGrafo->corrente == -1) {
            return GRA_CondRetGrafoVazio;
        }
        vizinho = get_by_id(pGrafo,id);
        if(vizinho == NULL)
            return GRA_CondRetNaoEhVertice;
        
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
       
        if (pGrafo->corrente == -1) {
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
        vet = calloc(LIS_NumeroDeElementos(lista) ,sizeof(int));
        LIS_IrInicioLista(lista);
        do {
            vet[*len] = getInt(LIS_ObterValor(lista));
            *len = (*len)+1;
        } while(LIS_AvancarElementoCorrente(lista, 1));
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
        vet = calloc(LIS_NumeroDeElementos(lista) ,sizeof(int));
        LIS_IrInicioLista(lista);
        do {
            vet[*len] = getInt(LIS_ObterValor(lista));
            *len = (*len)+1;
        } while(LIS_AvancarElementoCorrente(lista, 1));
    }


/***************************************************************************
*
*  Estrutura auxiliar: indiceDistancia;
*  ****/    

    typedef path {
        int id;
        int distancia;
    } Dist;

/***************************************************************************
*
*  Função: GRA  &newDist
*  ****/    


    static Dist* newDist(int id, int dist) {
        Dist* d = malloc(1, sizeof(Dist));
        d->id = id;
        d->dist = dist;
        return d;
    }

/***************************************************************************
*
*  Função: GRA  &newDist
*  ****/    


    static Dist* getDist(Dist** dists, int id) {
        int i;
        for (i=0;dists[i];i++) {
            if (d[i]->id ==id) {
                return d[i];
            }
        }
        return NULL;
    }

/***************************************************************************
*
*  Função: GRA  &Buscar caminho 
*  ****/    
    
    GRA_tpCondRet GRA_BuscarCaminho( GRA_tppGrafo pGrafo , int idVerticeOrigem, int idVerticeDestino, LIS_tppLista * pLista ) {
        LIS_tppLista caminho = NULL;
        tpVertice * v = NULL;
        tpVertice * u = NULL;               
        int *V = NULL; // Vetor de vertices vizitados
        int lenV = 0;
        LIS_tppLista Q = NULL; //FILA
        LIS_tppLista arestas = NULL;
        LIS_tppLista retorno = NULL;
        int t = NULL;
        int* vizinhos;
        int len = 0;
        tpVertice* s = NULL;
        tpAresta * atemp = NULL;
        tpAresta * a = NULL;
        tpVertice * origem1 = NULL;
        tpVertice * origem2 = NULL;
        int* idAux = NULL;
        int achou = 0;
        int achou_V = 0;
        int ok = 0;
        int i,j,in;
        int alt = 0;
        int lenD;
        Dist** dists = NULL;
        dists = calloc(LIS_NumeroDeElementos(pGrafo->vertices)+1, sizeof(*IndiceDistancia));
        Dist* dist = NULL; //aux;
        dists[0] = newDist(idVerticeOrigem, 0);
        lenD = 1;

        v = get_by_id(pGrafo, idVerticeOrigem);
        u = get_by_id(pGrafo, idVerticeDestino);
        if(v == NULL || u == NULL) {
            return GRA_CondRetNaoEhVertice; 
        }



        origem1 = ObterOrigem(pGrafo, v);
        origem2 = ObterOrigem(pGrafo, u);
        if (origem1 != origem2) {
            return GRA_CondRetNaoEhConexo;
        }//Else: É conexo, devia retornar Ok.
        

        for (;;) {
            retorno = LIS_CriarLista(free);
            if (retorno == NULL) { break; }
            else if (v == u) {
                if( LIS_InserirElementoApos(retorno, newInt(idVerticeOrigem)) == LIS_CondRetOK) {
                    *pLista = retorno;
                    return GRA_CondRetOK;
                } else {
                    break;
                }
            }
            caminho = LIS_CriarLista(free);
            if (caminho == NULL) { break; }

            V = calloc(LIS_NumeroDeElementos(pGrafo->vertices),sizeof(int));
            if (V == NULL) { break; }

            Q = LIS_CriarLista(free);
            if (Q == NULL) { break; }

            
            V[0] = v;
            lenV = 1;
            if (LIS_InserirElementoApos(Q, newInt(v)) != LIS_CondRetOK) { break;} //enque

            atemp = (tpAresta *) malloc(sizeof(tpAresta)); 
            if (atemp == NULL) { break; }

            ok = 1;
            break;
        }
        if (!ok) {
            LIS_DestruirLista(caminho);
            LIS_DestruirLista(retorno);
            free(V);
            LIS_DestruirLista(Q);
            return GRA_CondRetFaltouMemoria;
        }

        while (LIS_NumeroDeElementos(Q) > 0) {
            //dequeue
            LIS_IrInicioLista(Q);
            t = getInt(LIS_ObterValor(Q));
            LIS_ExcluirElemento(Q);

            //Iterar sobre vizinhos
            GRA_ObterVizinhos(pGrafo, t, &arestas);
            vizinhos = converteListaParaVetorDeInteiros(arestas, &len);
            LIS_DestruirLista(arestas);

            alt = getDist(dists, t)->dist + 1;
            for (i=0; i < len; i++) {
                in = 0;
                for (j=0; j < lenV; j++) {
                    if(V[j] == arestas[i] {
                        in = 1;
                    }
                }
                if (!in) {
                    dist = getDist(dists, arestas[i]);
                    if (dist == NULL) { //infinity
                        dists[lenD] = newDist(arestas[i], alt);
                        lenD++;
                    } else if (alt < dist->dist) {
                        dist->dist = alt;
                    }
                    
                    
                    LIS_InserirElementoAntes(Q, newInt(i));
                }
            }
            free(vizinhos);
        }

        //Limpando a memória        
        LIS_DestruirLista(caminho);    
        free(V);
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

        if(LIS_NumeroDeElementos(vertices) == 0){
            *idVertice = -1;
            return GRA_CondRetGrafoVazio;
        }

        LIS_IrInicioLista(vertices);
        do
        {
            vertice = (tpVertice*)LIS_ObterValor(vertices);
            
            if (predicado(vertice->pNode->pValor, parametro))
            {
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
    
    vizinhos = u->pNode->arestas;
    if(vizinhos == NULL) return vizinho; 
    LIS_IrInicioLista( vizinhos );
    do {
        viz = (tpAresta *)LIS_ObterValor(vizinhos);
        if(viz == NULL) break;
        if ( viz->pVizinho == v ) vizinho = 1 ;  
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
        if (pGrafo->vertices == NULL) {    
            return NULL;
        }
        LIS_IrInicioLista(pGrafo->vertices);
        do {
            vertice = (tpVertice*)LIS_ObterValor( pGrafo->vertices ) ;
            if(vertice == NULL)
                return NULL;
            
            if(vertice->id == idVertice) return vertice;    
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

    LIS_IrInicioLista( pGrafo->vertices );

    // Para cada vértice
    do{
        vertice = (tpVertice*)LIS_ObterValor( pGrafo->vertices ) ;
        if(vertice == NULL) break;
        LIS_IrInicioLista( vertice->pNode->arestas ) ;
        // Procura em todos os seus vizinhos
        do{
            aresta = (tpAresta*)LIS_ObterValor( vertice->pNode->arestas ) ;
            
            if(aresta == NULL){
                continue;
            }
         
            if ( aresta->id == idAresta ){
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
        if (vizinhos == NULL) return NULL;
        

        LIS_IrInicioLista(vizinhos);
        do { 
            aresta = (tpAresta*)LIS_ObterValor(vizinhos); 
            if (aresta->pVizinho == v) {
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
            tpVertice* t = NULL;

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

        vizinhos = u->pNode->arestas;
        aresta_v = get_edge_by_vertex(vizinhos, v); 

        LIS_IrInicioLista(vizinhos);
        if (aresta_v != NULL && (LIS_ProcurarValor(vizinhos, aresta_v ) == LIS_CondRetOK)) {
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
        tpVertice * pVerticeVizinho = NULL;
        int i = 0;
        
        no = pVertice->pNode;
        LIS_IrInicioLista(pGrafo->componentes);
        LIS_ProcurarValor(pGrafo->componentes, pVertice);
        LIS_ExcluirElemento(pGrafo->componentes);

        if (LIS_NumeroDeElementos(no->arestas) > 0) {

            vizinhos = (tpAresta**)calloc(LIS_NumeroDeElementos(no->arestas), sizeof(tpAresta*));

            LIS_IrInicioLista(no->arestas);
            do {
                vizinhos[i] = (tpAresta *)LIS_ObterValor(no->arestas);
                i++;
            } while ( LIS_AvancarElementoCorrente(no->arestas,1) == LIS_CondRetOK);
            
            for (i; i; i--) {
                ExcluirAresta(pGrafo, pVertice, vizinhos[i-1]->pVizinho); 
            }
            
            if (pGrafo->ExcluirValor != NULL && no->pValor != NULL) {
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
        RemoverAresta(v, u);//mexe só em v, ou deveria       
        RemoverAresta(u, v);

        //BFS pra detectar se é necessário gerar nova componente.
        if (BFS(v,u) != 1) { //Estão em componentes distintas
            if (LIS_InserirElementoApos(grafo->componentes, u) != LIS_CondRetOK) {
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
        tpAresta* a = NULL;
        int achou = 0;
        int achou_V = 0;

        V = LIS_CriarLista(NULL); // dados são referenciados por outros, não devem ser apagados
        Q = LIS_CriarLista(NULL); // dados são referenciados por outros, não devem ser apagados

        LIS_InserirElementoApos(V, v);
        LIS_InserirElementoApos(Q, v); //Usado como uma Fila.
        while (LIS_NumeroDeElementos(Q) > 0) {
            LIS_IrInicioLista(Q);
            t = (tpVertice *)LIS_ObterValor(Q);
            LIS_ExcluirElemento(Q);
            if (t == u) {
                achou = 1; 
                break;
            }
            arestas = t->pNode->arestas;
            LIS_IrInicioLista(arestas);
            do {
                a = (tpAresta *)LIS_ObterValor(arestas);
                if(a == NULL) continue;
                s = a->pVizinho;
                
                LIS_IrInicioLista(V);
                achou_V = 0;
                do {
                    tpVertice * re = (tpVertice *)LIS_ObterValor(V);
                    if (re == NULL) {
                        continue;
                    }
                    if(re == s) achou_V = 1;
                } while(LIS_AvancarElementoCorrente(V, 1) == LIS_CondRetOK);
            
                if (!achou_V) {
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
        
        LIS_IrInicioLista(grafo->vertices);
        LIS_IrInicioLista(origens);
        if (LIS_ProcurarValor(origens, v) == LIS_CondRetOK) {
            return v; //é a origem da própria componente
        }
        if(LIS_NumeroDeElementos(origens) > 0) {
            us = (tpVertice**) calloc(LIS_NumeroDeElementos(origens), sizeof(tpVertice*));

            LIS_IrInicioLista(origens);
            do {
                u = (tpVertice *)LIS_ObterValor(origens);
                if(u == NULL) break;
                us[i] = u;
                i++;
            } while(LIS_AvancarElementoCorrente(origens, 1) == LIS_CondRetOK);


            for ( i;i; i--) {
                if (BFS(us[i-1],v) == 1) {
                    u =  us[i-1];
                }
            }
            free(us);
        }

        return u;
    }

/********** Fim do módulo de implementação: GRA  Grafo **********/

