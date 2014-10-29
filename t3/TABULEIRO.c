/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro de labirinto
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / Labirinto
*  Gestor:  LSKDANEAV
*  Autores: eav
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		 1	   eav	 20/10/2014		//
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#include "LISTA.h"
#undef TABULEIRO_OWN

typedef struct Casa_{
    TAB_Casa tipo;
    // (x,y) para referência gráfica
    int x, y;
}Casa ;
/*
Um tabuleiro é a conjunção de 
    Um grafo de Casas(valido)
    Uma string nome
    dois ints indicando altura e largura 
*/

typedef struct TAB_tpTabuleiro_{
    GRA_tppGrafo pGrafo;  
    char* nome;
    int altura;
    int largura;
} TAB_tpTabuleiro ;

/***** Protótipos das funções encapsuladas no módulo *****/

static int Norte ( TAB_tppTabuleiro pTab ) ;
static int Oeste ( TAB_tppTabuleiro pTab ) ;
static int Sul ( TAB_tppTabuleiro pTab ) ;
static int Leste ( TAB_tppTabuleiro pTab ) ;
static int MesmoTipo( void* a, void* b ) ;
static int MesmaPosicao( void* a, void* b ) ;
static int TemInicio( TAB_tppTabuleiro pTab );
static int TemFim( TAB_tppTabuleiro pTab );
static int GetIdByXY ( TAB_tppTabuleiro pTab , int x , int y ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/

    TAB_tpCondRet TAB_CriarTabuleiro ( TAB_tppTabuleiro pTab, int alt, int lar, char* nome ){
        GRA_tppGrafo grafo = NULL;

        grafo = GRA_CriarGrafo(free);
        if(grafo == NULL)
            return TAB_CondRetFaltouMemoria ;

        pTab->altura = alt;
        pTab->largura = lar;
        pTab->nome = nome;
        pTab->pGrafo = grafo;
    
        return TAB_CondRetOK ;
    }

/***************************************************************************
*
*  Função: TAB  &Destruir Tabuleiro
*  ****/

    TAB_tpCondRet TAB_DestruirTabuleiro ( TAB_tppTabuleiro pTab ){
        GRA_DestruirGrafo( pTab->pGrafo );

        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Pode andar pra cima
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraCima(TAB_tppTabuleiro pTab ){
        Casa* corrente;
        GRA_ObterValorCorrente(pTab->pGrafo , (void**)&corrente);
        if(Norte(pTab)!=-1)
            return TAB_CondRetOK;
        else return TAB_CondRetMovimentoInvalido;
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra esquerda
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraEsquerda(TAB_tppTabuleiro pTab){
        Casa* corrente;
        GRA_ObterValorCorrente(pTab->pGrafo , (void**)&corrente);
        if(Oeste(pTab)!=-1)
            return TAB_CondRetOK;
        else return TAB_CondRetMovimentoInvalido;
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra baixo
*  ****/
    
    TAB_tpCondRet TAB_PodeAndarPraBaixo(TAB_tppTabuleiro pTab){
        Casa* corrente;
        GRA_ObterValorCorrente(pTab->pGrafo , (void**)&corrente);
        if(Sul(pTab)!=-1)
            return TAB_CondRetOK;
        else return TAB_CondRetMovimentoInvalido;
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra direita
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraDireita(TAB_tppTabuleiro pTab){
        Casa* corrente;
        GRA_ObterValorCorrente(pTab->pGrafo , (void**)&corrente);
        if(Leste(pTab)!=-1)
            return TAB_CondRetOK;
        else return TAB_CondRetMovimentoInvalido;
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra cima
*  ****/

    TAB_tpCondRet TAB_AndarPraCima(TAB_tppTabuleiro pTab ){
        GRA_MudarCorrente(pTab->pGrafo , Norte(pTab));
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra esquerda
*  ****/

    TAB_tpCondRet TAB_AndarPraEsquerda(TAB_tppTabuleiro pTab){
        GRA_MudarCorrente(pTab->pGrafo , Oeste(pTab));
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra baixo
*  ****/
    
    TAB_tpCondRet TAB_AndarPraBaixo(TAB_tppTabuleiro pTab){
        GRA_MudarCorrente(pTab->pGrafo , Sul(pTab));
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra direita
*  ****/

    TAB_tpCondRet TAB_AndarPraDireita(TAB_tppTabuleiro pTab){
        GRA_MudarCorrente(pTab->pGrafo , Leste(pTab));
    }
  
/***************************************************************************
*
*  Função: TAB  &Posicao do Jogador
*  ****/

    TAB_tpCondRet TAB_PosicaoJogador(TAB_tppTabuleiro pTab , int* x , int* y ){
        Casa* corrente;
        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        *x = corrente->x;
        *y = corrente->y;
        return TAB_CondRetOK;
    }
   
/***************************************************************************
*
*  Função: TAB  &Get Tipo Casa
*  ****/

    TAB_tpCondRet TAB_GetTipoCasa(TAB_tppTabuleiro pTab , int x , int y , TAB_Casa* tipo){
        Casa* corrente;

        if(x < 0 || x > pTab->largura || y < 0 || y > pTab->altura )
            return TAB_CondRetNaoEhCasa;

        if(GRA_ObterValor(pTab->pGrafo, GetIdByXY(pTab,x,y), (void**)&corrente) == GRA_CondRetOK){
            *tipo = corrente->tipo;
            return TAB_CondRetOK;
        }
        else{
            *tipo = TAB_CasaParede;
            return TAB_CondRetNaoEhCasa;
        }
    }

/***************************************************************************
*
*  Função: TAB  &Get altura
*  ****/

    TAB_tpCondRet TAB_GetAltura (TAB_tppTabuleiro pTab, int* altura){
        *altura = pTab->altura;
        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Get largura
*  ****/
    
    TAB_tpCondRet TAB_GetLargura (TAB_tppTabuleiro pTab, int* largura){
        *largura = pTab->largura;
        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Poe Chao
*  ****/    
    
    TAB_tpCondRet TAB_PoeChao (TAB_tppTabuleiro pTab){
        Casa* corrente,* chao;

        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        
        chao = (Casa*)malloc(sizeof(TAB_Casa));
        if (chao == NULL)
            return TAB_CondRetFaltouMemoria;

        chao->tipo = TAB_CasaChao;
        chao->x = corrente->x;
        chao->y = corrente->y;

        if(corrente->tipo == TAB_CasaParede){
            //todo
            //criar vertice
            //procurar vizinhos e criar arestas se necessario
        }
        else if (corrente->tipo == TAB_CasaInicio || corrente->tipo == TAB_CasaFim){
            GRA_AlterarValorCorrente(pTab->pGrafo,chao);
            return TAB_CondRetOK;
        }
        else if (corrente->tipo == TAB_CasaChao) return TAB_CondRetOK;
        else{
            free(chao);
            return TAB_CondRetAlteracaoInvalida;
        }
    }

/***************************************************************************
*
*  Função: TAB  &Poe Parede
*  ****/    
    
    TAB_tpCondRet TAB_PoeParede (TAB_tppTabuleiro pTab){
        Casa* corrente;

        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);

        if (corrente->tipo == TAB_CasaInicio || corrente->tipo == TAB_CasaFim || corrente->tipo == TAB_CasaChao){
            //todo
            //procurar vizinhos e excluir arestas se necessario
            //excluir vértice
        }
        
        else if (corrente->tipo == TAB_CasaParede) return TAB_CondRetOK;

        else return TAB_CondRetAlteracaoInvalida;
    }

/***************************************************************************
*
*  Função: TAB  &Poe Inicio
*  ****/    
    
    TAB_tpCondRet TAB_PoeInicio (TAB_tppTabuleiro pTab){
        Casa* corrente,* inicio,* chao;
        int idInicio;

        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        
        inicio = (Casa*)malloc(sizeof(TAB_Casa));
        if (inicio == NULL)
            return TAB_CondRetFaltouMemoria;

        inicio->tipo = TAB_CasaInicio;
        inicio->x = corrente->x;
        inicio->y = corrente->y;

        chao = (Casa*)malloc(sizeof(TAB_Casa));
        if (chao == NULL)
            return TAB_CondRetFaltouMemoria;

        chao->tipo = TAB_CasaChao;
        chao->x = corrente->x;
        chao->y = corrente->y;

        if(corrente->tipo == TAB_CasaParede){
            //todo
            //criar vertice
            //procurar vizinhos e criar arestas se necessario
        }
        else if (corrente->tipo == TAB_CasaChao || corrente->tipo == TAB_CasaFim){
            idInicio = TemInicio(pTab);
            if(idInicio != -1){
                GRA_AlterarValor(pTab->pGrafo,idInicio,chao);
                GRA_AlterarValorCorrente(pTab->pGrafo,inicio);
                return TAB_CondRetOK;
            }
            else{
                GRA_AlterarValorCorrente(pTab->pGrafo,inicio);
                return TAB_CondRetOK;
            }
        }
        else if (corrente->tipo == TAB_CasaChao) return TAB_CondRetOK;
        else{
            free(chao);
            free(inicio);
            return TAB_CondRetAlteracaoInvalida;
        }
    }

/***************************************************************************
*
*  Função: TAB  &Poe Fim
*  ****/    
    
    TAB_tpCondRet TAB_PoeFim (TAB_tppTabuleiro pTab){
        Casa* corrente,* fim,* chao;
        int idFim;

        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        
        fim = (Casa*)malloc(sizeof(TAB_Casa));
        if (fim == NULL)
            return TAB_CondRetFaltouMemoria;

        fim->tipo = TAB_CasaFim;
        fim->x = corrente->x;
        fim->y = corrente->y;

        chao = (Casa*)malloc(sizeof(TAB_Casa));
        if (chao == NULL)
            return TAB_CondRetFaltouMemoria;

        chao->tipo = TAB_CasaChao;
        chao->x = corrente->x;
        chao->y = corrente->y;

        if(corrente->tipo == TAB_CasaParede){
            //todo
            //criar vertice
            //procurar vizinhos e criar arestas se necessario
        }
        else if (corrente->tipo == TAB_CasaChao || corrente->tipo == TAB_CasaFim){
            idFim = TemFim(pTab);
            if(idFim != -1){
                GRA_AlterarValor(pTab->pGrafo,idFim,chao);
                GRA_AlterarValorCorrente(pTab->pGrafo,fim);
                return TAB_CondRetOK;
            }
            else{
                GRA_AlterarValorCorrente(pTab->pGrafo,fim);
                return TAB_CondRetOK;
            }
        }
        else if (corrente->tipo == TAB_CasaChao) return TAB_CondRetOK;
        else{
            free(chao);
            free(fim);
            return TAB_CondRetAlteracaoInvalida;
        }
    }

/*
TAB_tpCondRet TAB_SalvaTabuleiro(TAB_tppTabuleiro pTab){
    idAresta = 0
    idVertice = 0
    print(nome)
    print(alt lar)
    id1 = buscainicio
    id2 = buscafim
    print(id1 id2)
    para cada vertice em pGrafo
        print(idVertice x y num_vizinhos)
        idVertice++
        para cada vizinho 
            print(idVertice idVizinho idAresta)//tomar cuidado para nao repetir aresta, ou mexer no grafo para suportar/esperar isso
            idAresta++
        exclui vertice
}

TRES OPCOES:
mudar para ter x y
======
mapa1
10 10
1 7
1 2
1 2 1
1 3 2
2 0

3 1
3 4 3
4 0

5 0

6 1
6 7 4
7 0

=====
mapa1
10 10
1 7
1 2
1 2 1
1 3 2
2 1
2 1 1
3 2
3 1 2
3 4 3
4 1
4 3 3
5 0

6 1
6 7 4
7 1
7 6 4

=====
mapa1
10 10
1 7
1 2
1 2 1
1 3 2
2 1
2 1 3
3 2
3 1 4
3 4 5
4 1
4 3 6
5 0 

6 1
6 7 7
7 1
7 6 8

*/
    /*
    TAB_tpCondRet TAB_CarregaTabuleiro(TAB_tppTabuleiro pTab){}

    
    TAB_tpCondRet TAB_ValidaTabuleiro(tpTabuleiro pTab){}
        Antes de salvar valida as regras do tabuleiro
        ve se existe inicial, final e se existe apenas 1 destes
    */

   
    
/*****  Código das funções encapsuladas no módulo  *****/

    
    static int Norte ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int vizinhoIndex, norte = -1;
        LIS_tppLista vizinhos;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        LIS_IrInicioLista(vizinhos);
        do{
            vizinhoIndex = (int)LIS_ObterValor(vizinhos);
            GRA_ObterValor(pTab->pGrafo,vizinhoIndex,(void**)&vizinho);
            if(vizinho->y - 1 == corrente->y){
                norte = vizinhoIndex;
                break;
            }   
        }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );

        return norte;
    }
    static int Oeste ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int vizinhoIndex, oeste = 0;
        LIS_tppLista vizinhos;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        LIS_IrInicioLista(vizinhos);
        do{
            vizinhoIndex = (int)LIS_ObterValor(vizinhos);
            GRA_ObterValor(pTab->pGrafo,vizinhoIndex,(void**)&vizinho);
            if(vizinho->x + 1 == corrente->x){
                oeste = vizinhoIndex;
                break;
            }   
        }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );

        return oeste;
    }
    static int Sul ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int vizinhoIndex, sul = 0;
        LIS_tppLista vizinhos;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        LIS_IrInicioLista(vizinhos);
        do{
            vizinhoIndex = (int)LIS_ObterValor(vizinhos);
            GRA_ObterValor(pTab->pGrafo,vizinhoIndex,(void**)&vizinho);
            if(vizinho->y - 1 == corrente->y){
                sul = vizinhoIndex;
                break;
            }   
        }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );

        return sul;
    }
    static int Leste ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int vizinhoIndex, leste = -1;
        LIS_tppLista vizinhos;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        LIS_IrInicioLista(vizinhos);
        do{
            vizinhoIndex = (int)LIS_ObterValor(vizinhos);
            GRA_ObterValor(pTab->pGrafo,vizinhoIndex,(void**)&vizinho);
            if(vizinho->x - 1 == corrente->x){
                leste = vizinhoIndex;
                break;
            }   
        }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );

        return leste;
    }

    static int MesmoTipo(void* a, void* b){
        Casa* _a = (Casa*)a,* _b = (Casa*)b;
        return (_a->tipo == _b->tipo);
    }

    static int MesmaPosicao(void* a, void* b){
        Casa* _a = (Casa*)a,* _b = (Casa*)b;
        return (_a->x == _b->x && _a->y == _b->y);
    }

    static int TemInicio(TAB_tppTabuleiro pTab){
        Casa parametro;
        int id = -1;
        parametro.tipo = TAB_CasaInicio;
        GRA_BuscarVertice(pTab->pGrafo, &id, MesmoTipo, (void*)&parametro);
        return id;
    }

    static int TemInicio(TAB_tppTabuleiro pTab){
        Casa parametro;
        int id = -1;
        parametro.tipo = TAB_CasaFim;
        GRA_BuscarVertice(pTab->pGrafo, &id, MesmoTipo, (void*)&parametro);
        return id;
    }

    static int GetIdByXY(TAB_tppTabuleiro pTab, int x , int y ){
        Casa parametro;
        int id = -1;
        parametro.x = x;
        parametro.y = y;
        GRA_BuscarVertice(pTab->pGrafo, &id, MesmaPosicao, (void*)&parametro);
        return id;
    }
