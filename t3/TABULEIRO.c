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
    TAB_tpCasa tipo;
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
    int* idCasa;
    int* idAresta;
} TAB_tpTabuleiro ;

/***** Protótipos das funções encapsuladas no módulo *****/

static int getCasaID ( TAB_tppTabuleiro pTab , int x , int y ) ;
static int getArestaHorizontalID ( TAB_tppTabuleiro pTab , int x , int y ) ;
static int getArestaVerticalID ( TAB_tppTabuleiro pTab , int x , int y ) ;
static int Norte ( TAB_tppTabuleiro pTab ) ;
static int Oeste ( TAB_tppTabuleiro pTab ) ;
static int Sul ( TAB_tppTabuleiro pTab ) ;
static int Leste ( TAB_tppTabuleiro pTab ) ;
static int MesmoTipo( void* a, void* b ) ;
static int MesmaPosicao( void* a, void* b ) ;
static int TemInicio( TAB_tppTabuleiro pTab );
static int TemFim( TAB_tppTabuleiro pTab ) ;
static int GetIdByXY ( TAB_tppTabuleiro pTab , int x , int y ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/

    TAB_tpCondRet TAB_CriarTabuleiro ( TAB_tppTabuleiro* pTab, int alt, int lar, char* nome ){
        GRA_tppGrafo grafo = NULL;
        Casa* parede;
        int maxCasas, maxArestas, x, y, id, i;

        maxCasas = alt*lar;
        maxArestas = 2*alt*lar-alt-lar;

        *pTab = (TAB_tppTabuleiro)malloc(sizeof(TAB_tpTabuleiro));
        if(*pTab == NULL)
            return TAB_CondRetFaltouMemoria ;

        grafo = GRA_CriarGrafo(free);
        if(grafo == NULL)
            return TAB_CondRetFaltouMemoria ;

        (*pTab)->idCasa = (int*)malloc(sizeof(int)*maxCasas);
        if((*pTab)->idCasa == NULL)
            return TAB_CondRetFaltouMemoria ;

        (*pTab)->idAresta = (int*)malloc(sizeof(int)*maxArestas);
        if((*pTab)->idAresta == NULL)
            return TAB_CondRetFaltouMemoria ;

        (*pTab)->altura = alt;
        (*pTab)->largura = lar;
        (*pTab)->nome = nome;
        (*pTab)->pGrafo = grafo;
    
        // Inicializa casas
        for(id = 0, y = 0 ; y < alt ; y++){
            for(x = 0 ; x < lar ; x++){
                parede = (Casa*)malloc(sizeof(Casa));
                if(parede == NULL)
                    return TAB_CondRetFaltouMemoria ;
                
                parede->tipo = TAB_tpCasaParede;
                parede->x = x;
                parede->y = y;

                (*pTab)->idCasa[id] = -1;
                GRA_InserirVertice((*pTab)->pGrafo,parede,id);
                id++;
            }
        }

        // Inicializa arestas
        for(i = 0 ; i < maxArestas ; i++){
            (*pTab)->idAresta[i] = -1;
        }

        return TAB_CondRetOK ;
    }

/***************************************************************************
*
*  Função: TAB  &Destruir Tabuleiro
*  ****/

    TAB_tpCondRet TAB_DestruirTabuleiro ( TAB_tppTabuleiro pTab ){
        GRA_DestruirGrafo( pTab->pGrafo );
        free(pTab->idCasa);
        free(pTab->idAresta);
        free(pTab);

        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Pode andar pra cima
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraCima(TAB_tppTabuleiro pTab ){
        int idCorrente = -1;
        GRA_ObterIDCorrente(pTab->pGrafo,&idCorrente);
        if(idCorrente == -1)
            return TAB_CondRetMovimentoInvalido;

        if(Norte(pTab)!=-1){
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetOK;
        }
        else{
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetMovimentoInvalido;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra esquerda
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraEsquerda(TAB_tppTabuleiro pTab){
        int idCorrente = -1;
        GRA_ObterIDCorrente(pTab->pGrafo,&idCorrente);
        if(idCorrente == -1)
            return TAB_CondRetMovimentoInvalido;

        if(Oeste(pTab)!=-1){
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetOK;
        }
        else{
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetMovimentoInvalido;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra baixo
*  ****/
    
    TAB_tpCondRet TAB_PodeAndarPraBaixo(TAB_tppTabuleiro pTab){
        int idCorrente = -1;
        GRA_ObterIDCorrente(pTab->pGrafo,&idCorrente);
        if(idCorrente == -1)
            return TAB_CondRetMovimentoInvalido;

        if(Sul(pTab)!=-1){
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetOK;
        }
        else{
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetMovimentoInvalido;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra direita
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraDireita(TAB_tppTabuleiro pTab){ 
        int idCorrente = -1;
        GRA_ObterIDCorrente(pTab->pGrafo,&idCorrente);
        if(idCorrente == -1)
            return TAB_CondRetMovimentoInvalido;

        if(Leste(pTab)!=-1){
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetOK;
        }
        else{
            GRA_MudarCorrente(pTab->pGrafo,idCorrente);
            return TAB_CondRetMovimentoInvalido;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra cima
*  ****/

    TAB_tpCondRet TAB_AndarPraCima(TAB_tppTabuleiro pTab, int colisao){
        Casa* corrente;

        if(colisao){
            GRA_MudarCorrente(pTab->pGrafo , Norte(pTab));
            return TAB_CondRetOK;
        }
        else{
            GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
            corrente->y -= 1;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra esquerda
*  ****/

    TAB_tpCondRet TAB_AndarPraEsquerda(TAB_tppTabuleiro pTab, int colisao){
        Casa* corrente;

        if(colisao){
            GRA_MudarCorrente(pTab->pGrafo , Oeste(pTab));
            return TAB_CondRetOK;
        }
        else{
            GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
            corrente->x -= 1;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra baixo
*  ****/
    
    TAB_tpCondRet TAB_AndarPraBaixo(TAB_tppTabuleiro pTab, int colisao){
        Casa* corrente;

        if(colisao){
            GRA_MudarCorrente(pTab->pGrafo , Sul(pTab));
            return TAB_CondRetOK;
        }
        else{
            GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
            corrente->y += 1;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra direita
*  ****/

    TAB_tpCondRet TAB_AndarPraDireita(TAB_tppTabuleiro pTab, int colisao){
        Casa* corrente;

        if(colisao){
            GRA_MudarCorrente(pTab->pGrafo , Leste(pTab));
            return TAB_CondRetOK;
        }
        else{
            GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
            corrente->x += 1;
        }
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

    TAB_tpCondRet TAB_GetTipoCasa(TAB_tppTabuleiro pTab , int x , int y , TAB_tpCasa* tipo){
        Casa* corrente;

        if(x < 0 || x > pTab->largura || y < 0 || y > pTab->altura )
            return TAB_CondRetNaoEhCasa;

        if(GRA_ObterValor(pTab->pGrafo, GetIdByXY(pTab,x,y), (void**)&corrente) == GRA_CondRetOK){
            *tipo = corrente->tipo;
            return TAB_CondRetOK;
        }
        else{
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
    
    TAB_tpCondRet TAB_PoeChao (TAB_tppTabuleiro pTab, int x, int y){
        Casa* casaXY;
        int idXY, idVertice, idAresta;
        
        idVertice = getCasaID (pTab,x,y);
        GRA_ObterValor(pTab->pGrafo,idVertice,(void**)&casaXY);

        if(casaXY->tipo == TAB_tpCasaParede){

            pTab->idCasa[idVertice] = 1;

            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x+1, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }
        }

        casaXY->tipo = TAB_tpCasaChao;

        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Poe Parede
*  ****/    
    
    TAB_tpCondRet TAB_PoeParede (TAB_tppTabuleiro pTab, int x , int y ){
        Casa* casaXY ,* parede;
        int idXY, idVertice, idAresta, idInicio;
        
        idVertice = getCasaID (pTab,x,y);
        GRA_ObterValor(pTab->pGrafo,idVertice,(void**)&casaXY);

        if(casaXY->tipo != TAB_tpCasaParede){
            
            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if(idAresta >= 0)
                    pTab->idAresta[idAresta] = -1;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if(idAresta >= 0)
                    pTab->idAresta[idAresta] = -1;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if(idAresta >= 0)
                    pTab->idAresta[idAresta] = -1;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x+1, y);
                if(idAresta >= 0)
                    pTab->idAresta[idAresta] = -1;
            }
            
            GRA_ExcluirVertice(pTab->pGrafo,idVertice);
            
            parede = (Casa*)malloc(sizeof(Casa));
            if(parede == NULL)
                return TAB_CondRetFaltouMemoria ;
                
            parede->tipo = TAB_tpCasaParede;
            parede->x = x;
            parede->y = y;

            pTab->idCasa[idVertice] = -1;
            GRA_InserirVertice(pTab->pGrafo,parede,idVertice);
        }
        else
            return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Poe Inicio
*  ****/    
    
    TAB_tpCondRet TAB_PoeInicio (TAB_tppTabuleiro pTab, int x, int y){
        Casa* casaXY ,* casaInicio;
        int idXY, idVertice, idAresta, idInicio;
        
        idInicio = -1; 
        idVertice = getCasaID (pTab,x,y);
        GRA_ObterValor(pTab->pGrafo,idVertice,(void**)&casaXY);

        if(casaXY->tipo == TAB_tpCasaParede){

            pTab->idCasa[idVertice] = 1;

            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x+1, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

        }

        //Busca e apaga outro inicio
        idInicio = TemInicio(pTab);
        if(idInicio != -1){
            GRA_ObterValor(pTab->pGrafo,idInicio,(void**)&casaInicio);
            casaInicio->tipo = TAB_tpCasaChao;
            GRA_MudarCorrente(pTab->pGrafo,idVertice);
        }

        GRA_ObterValor(pTab->pGrafo,idVertice,(void**)&casaXY);
        casaXY->tipo = TAB_tpCasaInicio;

        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Poe Fim
*  ****/    
    
    TAB_tpCondRet TAB_PoeFim (TAB_tppTabuleiro pTab, int x, int y){
        Casa* casaXY ,* casaFim;
        int idXY, idVertice, idAresta, idFim;
        
        idFim = -1;
        idVertice = getCasaID (pTab,x,y);
        GRA_ObterValor(pTab->pGrafo,idVertice,(void**)&casaXY);

        if(casaXY->tipo == TAB_tpCasaParede){

            pTab->idCasa[idVertice] = 1;

            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x+1, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = idAresta;
            }

        }

        //Busca e apaga outro fim
        idFim = TemFim(pTab);
        if(idFim != -1){
            GRA_ObterValor(pTab->pGrafo,idFim,(void**)&casaFim);
            casaFim->tipo = TAB_tpCasaChao;
            GRA_MudarCorrente(pTab->pGrafo,idVertice);
        }

        GRA_ObterValor(pTab->pGrafo,idVertice,(void**)&casaXY);
        casaXY->tipo = TAB_tpCasaFim;

        return TAB_CondRetOK;
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
    
    static int getCasaID ( TAB_tppTabuleiro pTab, int x, int y){
        return x+(y*pTab->altura);
    }
    
    static int getArestaHorizontalID ( TAB_tppTabuleiro pTab, int x, int y){
        return (x-1)+y*(pTab->altura - 1);
    }

    static int getArestaVerticalID ( TAB_tppTabuleiro pTab, int x, int y){
        return ((pTab->largura-1)*pTab->altura+((y-1)+x*(pTab->largura-1)));
    }

    static int Norte ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int* vizinhoIndex, norte = -1;
        LIS_tppLista vizinhos = NULL;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        if( vizinhos != NULL && LIS_NumeroDeElementos(vizinhos) > 0 ){
            LIS_IrInicioLista(vizinhos);
            do{
                vizinhoIndex = (int*)LIS_ObterValor(vizinhos);
                if(GRA_ObterValor(pTab->pGrafo,*vizinhoIndex,(void**)&vizinho) != GRA_CondRetOK)
                    continue;
                if(vizinho->y + 1 == corrente->y){
                    norte = *vizinhoIndex;
                    break;
                }   
            }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );
        }
        if(pTab->idCasa[norte] != -1)
            return norte;
        else
            return -1;
    }
    static int Oeste ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int* vizinhoIndex, oeste = -1;
        LIS_tppLista vizinhos;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        if( vizinhos != NULL && LIS_NumeroDeElementos(vizinhos) > 0 ){
        LIS_IrInicioLista(vizinhos);
            do{
                vizinhoIndex = (int*)LIS_ObterValor(vizinhos);
                GRA_ObterValor(pTab->pGrafo,*vizinhoIndex,(void**)&vizinho);
                if(vizinho->x + 1 == corrente->x){
                    oeste = *vizinhoIndex;
                    break;
                }   
            }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );
        }
        if(pTab->idCasa[oeste] != -1)
            return oeste;
        else
            return -1;
    }
    static int Sul ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int* vizinhoIndex, sul = -1;
        LIS_tppLista vizinhos;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        LIS_IrInicioLista(vizinhos);
        if( vizinhos != NULL && LIS_NumeroDeElementos(vizinhos) > 0 ){
            do{
                vizinhoIndex = (int*)LIS_ObterValor(vizinhos);
                GRA_ObterValor(pTab->pGrafo,*vizinhoIndex,(void**)&vizinho);
                if(vizinho->y - 1 == corrente->y){
                    sul = *vizinhoIndex;
                    break;
                }   
            }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );
        }
        if(pTab->idCasa[sul] != -1)
            return sul;
        else
            return -1;
    }
    static int Leste ( TAB_tppTabuleiro pTab ) {
        Casa* vizinho = NULL,* corrente;
        int* vizinhoIndex, leste = -1;
        LIS_tppLista vizinhos;

        GRA_ObterValorCorrente(pTab->pGrafo, (void**)&corrente);
        GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
        LIS_IrInicioLista(vizinhos);
        if( vizinhos != NULL && LIS_NumeroDeElementos(vizinhos) > 0 ){
            do{
                vizinhoIndex = (int*)LIS_ObterValor(vizinhos);
                GRA_ObterValor(pTab->pGrafo,*vizinhoIndex,(void**)&vizinho);
                if(vizinho->x - 1 == corrente->x){
                    leste = *vizinhoIndex;
                    break;
                }   
            }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK );
        }
        if(pTab->idCasa[leste] != -1)
            return leste;
        else
            return -1;
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
        parametro.tipo = TAB_tpCasaInicio;
        GRA_BuscarVertice(pTab->pGrafo, &id, MesmoTipo, (void*)&parametro);
        
        if(pTab->idCasa[id] != -1)
            return id;
        else
            return -1;
    }

    static int TemFim(TAB_tppTabuleiro pTab){
        Casa parametro;
        int id = -1;
        parametro.tipo = TAB_tpCasaFim;
        GRA_BuscarVertice(pTab->pGrafo, &id, MesmoTipo, (void*)&parametro);
        
        if(pTab->idCasa[id] != -1)
            return id;
        else
            return -1;
    }

    static int GetIdByXY(TAB_tppTabuleiro pTab, int x , int y ){
        Casa parametro;
        int id = -1;
        parametro.x = x;
        parametro.y = y;
        GRA_BuscarVertice(pTab->pGrafo, &id, MesmaPosicao, (void*)&parametro);
        
        if(pTab->idCasa[id] != -1)
            return id;
        else
            return -1;
    }