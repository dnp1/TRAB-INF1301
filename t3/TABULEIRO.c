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
#include    <stdlib.h>
#include    <malloc.h>

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#include "LISTA.h"
#undef TABULEIRO_OWN

#define DIM_VALOR 256

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
static int GetIdByXY ( TAB_tppTabuleiro pTab , int x , int y , int colisao ) ;

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
        if(grafo == NULL){
			TAB_DestruirTabuleiro(*pTab);
			return TAB_CondRetFaltouMemoria ;
		}

        (*pTab)->idCasa = (int*)malloc(sizeof(int)*maxCasas);
        if((*pTab)->idCasa == NULL){
			TAB_DestruirTabuleiro(*pTab);
			GRA_DestruirGrafo(grafo);
			return TAB_CondRetFaltouMemoria ;
		}

        (*pTab)->idAresta = (int*)malloc(sizeof(int)*maxArestas);
        if((*pTab)->idAresta == NULL){
            TAB_DestruirTabuleiro(*pTab);
			GRA_DestruirGrafo(grafo);
			return TAB_CondRetFaltouMemoria ;
		}

        (*pTab)->altura = alt;
        (*pTab)->largura = lar;
        (*pTab)->nome = nome;
        (*pTab)->pGrafo = grafo;
    
        // Inicializa casas
        for(id = 0, y = 0 ; y < alt ; y++){
            for(x = 0 ; x < lar ; x++){
                parede = (Casa*)malloc(sizeof(Casa));
                if(parede == NULL){
					TAB_DestruirTabuleiro(*pTab);
					return TAB_CondRetFaltouMemoria ;
				}
                
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

        GRA_MudarCorrente((*pTab)->pGrafo,0);

        return TAB_CondRetOK ;
    }

/***************************************************************************
*
*  Função: TAB  &Destruir Tabuleiro
*  ****/

    TAB_tpCondRet TAB_DestruirTabuleiro ( TAB_tppTabuleiro pTab ){
    
        if(pTab != NULL){
            GRA_DestruirGrafo( pTab->pGrafo );
            free(pTab->idCasa);
            free(pTab->idAresta);
            free(pTab);

            return TAB_CondRetOK;
        }
        else
            return TAB_CondRetTabuleiroInvalido;
    }

/***************************************************************************
*
*  Função: TAB  &Pode andar pra cima
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraCima(TAB_tppTabuleiro pTab , int colisao ){
        Casa* corrente;
        if(GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente) != GRA_CondRetOK)
            return TAB_CondRetMovimentoInvalido;

        if(colisao){
            if(Norte(pTab)!=-1)
                return TAB_CondRetOK;
            else
                return TAB_CondRetMovimentoInvalido;
        }
        else{
            if(corrente->y-1 < 0)
                return TAB_CondRetMovimentoInvalido;
            else
                return TAB_CondRetOK;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra esquerda
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraEsquerda(TAB_tppTabuleiro pTab , int colisao){
        Casa* corrente;
        if(GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente) != GRA_CondRetOK)
            return TAB_CondRetMovimentoInvalido;

        if(colisao){
            if(Oeste(pTab)!=-1)
                return TAB_CondRetOK;
            else
                return TAB_CondRetMovimentoInvalido;
        }
        else{
            if(corrente->x-1 < 0)
                return TAB_CondRetMovimentoInvalido;
            else
                return TAB_CondRetOK;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra baixo
*  ****/
    
    TAB_tpCondRet TAB_PodeAndarPraBaixo(TAB_tppTabuleiro pTab , int colisao){
        Casa* corrente;
        if(GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente) != GRA_CondRetOK)
            return TAB_CondRetMovimentoInvalido;

        if(colisao){
            if(Sul(pTab)!=-1)
                return TAB_CondRetOK;
            else
                return TAB_CondRetMovimentoInvalido;
        }
        else{
			if(corrente->y+1 >= pTab->altura)
                return TAB_CondRetMovimentoInvalido;
            else
                return TAB_CondRetOK;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Pode andar pra direita
*  ****/

    TAB_tpCondRet TAB_PodeAndarPraDireita(TAB_tppTabuleiro pTab , int colisao){ 
        Casa* corrente;
        if(GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente) != GRA_CondRetOK)
            return TAB_CondRetMovimentoInvalido;

		if(colisao){
            if(Leste(pTab)!=-1)
                return TAB_CondRetOK;
            else
                return TAB_CondRetMovimentoInvalido;
        }
        else{
			if(corrente->x+1 >= pTab->largura)
                return TAB_CondRetMovimentoInvalido;
            else
                return TAB_CondRetOK;
        }
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra cima
*  ****/

    TAB_tpCondRet TAB_AndarPraCima(TAB_tppTabuleiro pTab){
        Casa* corrente;
        int idVizinho = -1;
        
        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        idVizinho = GetIdByXY(pTab,corrente->x, corrente->y - 1, 1);

        if(idVizinho != -1){
            GRA_MudarCorrente(pTab->pGrafo , idVizinho);
            return TAB_CondRetOK;
        }
        else
            return TAB_CondRetMovimentoInvalido;
 
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra esquerda
*  ****/

    TAB_tpCondRet TAB_AndarPraEsquerda(TAB_tppTabuleiro pTab){
        Casa* corrente;
        int idVizinho = -1;
        
        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        idVizinho = GetIdByXY(pTab,corrente->x - 1, corrente->y, 1);

        if(idVizinho != -1){
            GRA_MudarCorrente(pTab->pGrafo , idVizinho);
            return TAB_CondRetOK;
        }
        else
            return TAB_CondRetMovimentoInvalido;
 
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra baixo
*  ****/
    
    TAB_tpCondRet TAB_AndarPraBaixo(TAB_tppTabuleiro pTab){
        Casa* corrente;
        int idVizinho = -1;
        
        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        idVizinho = GetIdByXY(pTab,corrente->x, corrente->y + 1, 1);

        if(idVizinho != -1){
            GRA_MudarCorrente(pTab->pGrafo , idVizinho);
            return TAB_CondRetOK;
        }
        else
            return TAB_CondRetMovimentoInvalido;
 
    }
 
/***************************************************************************
*
*  Função: TAB  &Andar pra direita
*  ****/

    TAB_tpCondRet TAB_AndarPraDireita(TAB_tppTabuleiro pTab){
        Casa* corrente;
        int idVizinho = -1;
        
        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&corrente);
        idVizinho = GetIdByXY(pTab,corrente->x + 1, corrente->y, 1);

        if(idVizinho != -1){
            GRA_MudarCorrente(pTab->pGrafo , idVizinho);
            return TAB_CondRetOK;
        }
        else
            return TAB_CondRetMovimentoInvalido;
 
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
        Casa* casaXY;

        if(x < 0 || x > pTab->largura || y < 0 || y > pTab->altura )
            return TAB_CondRetNaoEhCasa;

        if(GRA_ObterValor(pTab->pGrafo, GetIdByXY(pTab,x,y,1), (void**)&casaXY) == GRA_CondRetOK){
            *tipo = casaXY->tipo;
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
*  Função: TAB  &Get nome
*  ****/
    
    TAB_tpCondRet TAB_GetNome (TAB_tppTabuleiro pTab, char** nome){
		*nome = pTab->nome;
        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Poe Chao
*  ****/    
    
    TAB_tpCondRet TAB_PoeChao (TAB_tppTabuleiro pTab){
        Casa* casaXY;
        int idXY, idVertice, idAresta, x , y;

        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&casaXY);

        x = casaXY->x;
        y = casaXY->y;

        idVertice = getCasaID (pTab,x,y);
        if(casaXY->tipo == TAB_tpCasaParede){

            pTab->idCasa[idVertice] = 1;

            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x+1, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }
        }

        casaXY->tipo = TAB_tpCasaChao;

        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Poe Parede
*  ****/    
    
    TAB_tpCondRet TAB_PoeParede (TAB_tppTabuleiro pTab){
        Casa* casaXY ,* parede;
        int idXY, idVertice, idAresta, idInicio, x , y;

        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&casaXY);

        x = casaXY->x;
        y = casaXY->y;

        idVertice = getCasaID (pTab,x,y);

        if(casaXY->tipo != TAB_tpCasaParede){
            
            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if(idAresta >= 0)
                    pTab->idAresta[idAresta] = -1;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if(idAresta >= 0)
                    pTab->idAresta[idAresta] = -1;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if(idAresta >= 0)
                    pTab->idAresta[idAresta] = -1;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y,0);
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
    
    TAB_tpCondRet TAB_PoeInicio (TAB_tppTabuleiro pTab){
        Casa* casaXY ,* casaInicio;
        int idXY, idVertice, idAresta, idInicio, x , y;

        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&casaXY);

        x = casaXY->x;
        y = casaXY->y;

        idInicio = -1;
        idVertice = getCasaID (pTab,x,y);

        if(casaXY->tipo == TAB_tpCasaParede){

            pTab->idCasa[idVertice] = 1;

            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x+1, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
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
    
    TAB_tpCondRet TAB_PoeFim (TAB_tppTabuleiro pTab){
        Casa* casaXY ,* casaFim;
        int idXY, idVertice, idAresta, idFim, x , y;
		
        GRA_ObterValorCorrente(pTab->pGrafo,(void**)&casaXY);

        x = casaXY->x;
        y = casaXY->y;

        idFim = -1;
        idVertice = getCasaID (pTab,x,y);
        
        if(casaXY->tipo == TAB_tpCasaParede){

            pTab->idCasa[idVertice] = 1;

            //Vizinho ao norte
            idXY = GetIdByXY(pTab,x,y-1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao oeste
            idXY = GetIdByXY(pTab,x-1,y,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao sul
            idXY = GetIdByXY(pTab,x,y+1,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaVerticalID(pTab, x, y+1);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
            }

            //Vizinho ao leste
            idXY = GetIdByXY(pTab,x+1,y,0);
            //Reposiciona o corrente
            GRA_MudarCorrente(pTab->pGrafo, idVertice);
            if(idXY != -1){
                idAresta = getArestaHorizontalID(pTab, x+1, y);
                if( GRA_InserirAresta(pTab->pGrafo,idVertice,idXY,idAresta) == GRA_CondRetFaltouMemoria )
                    return TAB_CondRetFaltouMemoria;

                pTab->idAresta[idAresta] = 1;
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
	
/***************************************************************************
*
*  Função: TAB  &Validar Tabuleiro
*  ****/  

    TAB_tpCondRet TAB_ValidarTabuleiro(TAB_tppTabuleiro pTab){
        int idInicio = - 1, idFim = -1;
        idInicio = TemInicio(pTab);
        idFim = TemFim(pTab);
        if(idInicio != -1 && idFim != -1){
            return TAB_CondRetOK;
        }
        else
            return TAB_CondRetTabuleiroInvalido;
    }
	
/***************************************************************************
*
*  Função: TAB  &Salvar tabuleiro
*  ****/  

    TAB_tpCondRet TAB_SalvarTabuleiro(TAB_tppTabuleiro pTab, char* path){
        int idVisitado, idCorrente, i;
        int* visitados,* idOrigem,* idProx,* vizinho;
		char* pathTemp;
        FILE* saida;
        Casa* casaVizinho,* casaCorrente;
        LIS_tppLista fila = NULL;
        LIS_tppLista origens = NULL;
        LIS_tppLista vizinhos = NULL;

		GRA_ObterIDCorrente(pTab->pGrafo,&idCorrente);

		pathTemp = (char*)malloc(sizeof(path));
		strcpy(pathTemp,path);
        saida = fopen(strcat(pathTemp,".txt"),"w");
        fprintf(saida,"%d\n%d\n%s",pTab->largura,pTab->altura,pTab->nome);

        // vetor de inteiros usado como flag
        visitados = (int*)malloc(sizeof(int)*pTab->altura*pTab->largura);
		if(visitados == NULL) return TAB_CondRetFaltouMemoria;

        for(i=0 ; i < pTab->altura*pTab->largura ; i++){
            visitados[i] = pTab->idCasa[i];
        }

        // dados são referenciados por outros, não devem ser apagados
        fila = LIS_CriarLista(NULL);
		if(fila == NULL){
			free(visitados);
			return TAB_CondRetFaltouMemoria;
		}

        origens = LIS_CriarLista(NULL);
		if(origens == NULL){
			free(visitados);
			LIS_DestruirLista(fila);
			return TAB_CondRetFaltouMemoria;
		}

        vizinhos = LIS_CriarLista(NULL);
		if(vizinhos == NULL){
			free(visitados);
			LIS_DestruirLista(fila);
			LIS_DestruirLista(origens);
			return TAB_CondRetFaltouMemoria;
		}

        GRA_ObterOrigens(pTab->pGrafo,&origens);
        LIS_IrInicioLista(origens);
        do{ // Para cada componente
            idOrigem = (int*)LIS_ObterValor(origens);
            GRA_MudarCorrente(pTab->pGrafo,*idOrigem);
            
            // Origem é uma parede ?
            GRA_ObterValorCorrente(pTab->pGrafo,(void**)&casaCorrente);
            if(casaCorrente->tipo == TAB_tpCasaParede) continue;

            // Escreve origem[i] no arquivo
            fprintf(saida,"\n%d %d %d",casaCorrente->x,casaCorrente->y,casaCorrente->tipo);

            // origem[i] ja foi visitada
            LIS_InserirElementoApos(fila,idOrigem);
            visitados[*idOrigem] = -2;

            do{// Ate a fila ficar vazia

               GRA_ObterVizinhosCorrente(pTab->pGrafo,&vizinhos);
               LIS_IrInicioLista(vizinhos);
                
				   if(LIS_NumeroDeElementos(vizinhos) > 0){
				   do{// preenche a fila com os vizinhos

					   vizinho = (int*)LIS_ObterValor(vizinhos);
					   // vizinho ja foi visitado ?
					   if(visitados[*vizinho] != -2){
						   GRA_ObterValor(pTab->pGrafo,*vizinho,(void**)&casaVizinho);
                       
						   // Escreve vizinho no arquivo
						   fprintf(saida,"\n%d %d %d",casaVizinho->x,casaVizinho->y,casaVizinho->tipo);

						   // vizinho foi visitado
						   LIS_InserirElementoApos(fila,vizinho);
						   visitados[*vizinho] = -2;
					   }
					   else continue;

				   }while(LIS_AvancarElementoCorrente(vizinhos,1) == LIS_CondRetOK);
			   }	
               // Retira o elemento da fila - vertice ja foi visitado
               LIS_IrInicioLista(fila);
               LIS_ExcluirElemento(fila);

               // Fila vazia ?
               if(LIS_NumeroDeElementos(fila) == 0) break;
               
               // Proximo vertice a ser visitado
               idProx = (int*)LIS_ObterValor(fila);
               GRA_MudarCorrente(pTab->pGrafo,*idProx);

           }while(LIS_NumeroDeElementos(fila) > 0);
        }while(LIS_AvancarElementoCorrente(origens,1) == LIS_CondRetOK);

        fclose(saida);
		GRA_MudarCorrente(pTab->pGrafo,idCorrente);
        return TAB_CondRetOK;
    }

/***************************************************************************
*
*  Função: TAB  &Carregar tabuleiro
*  ****/  

    TAB_tpCondRet TAB_CarregarTabuleiro(TAB_tppTabuleiro* pTab,char* path){
        FILE* entrada;
        TAB_tpCasa casa;
        Casa corrente;
        int altura, largura, x, y, idCorrente;
        char linha[DIM_VALOR];

        entrada = fopen(path,"r");
        if(entrada != NULL){

            fgets(linha,sizeof(linha),entrada);
            largura = atoi(linha);
            
            fgets(linha,sizeof(linha),entrada);
            altura = atoi(linha);

            fgets(linha,sizeof(linha),entrada);
            TAB_CriarTabuleiro(pTab,altura,largura,linha);
            
            do{
                fscanf(entrada,"%d %d %d",&x,&y,&casa);
                idCorrente = GetIdByXY((*pTab),x,y,1);
                GRA_MudarCorrente((*pTab)->pGrafo,idCorrente);

                if(casa == TAB_tpCasaChao){
                    TAB_PoeChao((*pTab));
                }
                else if(casa == TAB_tpCasaInicio){
                    TAB_PoeInicio((*pTab));
                }
                else if(casa == TAB_tpCasaFim){
                    TAB_PoeFim((*pTab));
                }
                else{
                    return TAB_CondRetTabuleiroInvalido;
                }
            }while(fgets(linha,sizeof(linha),entrada));
            return TAB_CondRetOK;
        }
        else
            return TAB_CondRetTabuleiroInvalido;
    }

/***************************************************************************
*
*  Função: TAB  &Solucionar tabuleiro
*  ****/  

    TAB_tpCondRet TAB_SolucionarTabuleiro(TAB_tppTabuleiro pTab, int** solucao, int* tam){
        int idInicio, idFim, idParede;
        int* idTemp;
        LIS_tppLista lstSolucao = NULL;
        Casa* parede,* corrente;

		*solucao = (int*)malloc(sizeof(int)*DIM_VALOR);
		if(solucao == NULL) return TAB_CondRetFaltouMemoria;

        parede = (Casa*)malloc(sizeof(Casa));
        if(parede == NULL){
			LIS_DestruirLista(lstSolucao);
			free(solucao);
			return TAB_CondRetFaltouMemoria;
		}
        parede->tipo = TAB_tpCasaParede;

        idInicio = TemInicio(pTab);
        idFim = TemFim(pTab);

        GRA_MudarCorrente(pTab->pGrafo,idInicio);

        GRA_BuscarCaminhoCorrente(pTab->pGrafo,idFim,&lstSolucao);
        
        if(lstSolucao == NULL || LIS_NumeroDeElementos(lstSolucao) == 0){
			free(*solucao);
			free(parede);
			return TAB_CondRetSemSolucao;
		}
        
        LIS_IrInicioLista(lstSolucao);
		*tam = 0;
        do{
            idTemp = (int*)LIS_ObterValor(lstSolucao);
			GRA_ObterValor(pTab->pGrafo,*idTemp,(void**)&corrente);
			
			(*solucao)[*tam] = corrente->x;
			(*solucao)[(*tam)+1] = corrente->y;
			*tam = *tam + 2;
        }while(LIS_AvancarElementoCorrente(lstSolucao,1) == LIS_CondRetOK);
    }
    
/***************************************************************************
*
*  Função: TAB  &Ir inicio
*  ****/  
    TAB_tpCondRet TAB_IrInicio ( TAB_tppTabuleiro pTab){
        GRA_MudarCorrente(pTab->pGrafo,TemInicio(pTab));
        return TAB_CondRetOK;
    }
                
/***************************************************************************
*
*  Função: TAB  &Lista tabuleiros
*  ****/  
    TAB_tpCondRet TAB_ListaTabuleiros ( char*** tabuleiros, int* tam ){
        struct _finddata_t txt_file;
        long hFile;

        /* Find first .txt file in current directory */
        if( (hFile = _findfirst( "*.txt", &txt_file )) == -1L )
           printf( "No *.txt files in current directory!\n" );
        else
        {
            printf( "Listing of .txt files\n\n" );
            printf( "\nFILE\n", ' ' );
            printf( " %25c \n", ' ' );

            printf( " %-12s\n", txt_file.name );

            /* Find the rest of the .txt files */
            while( _findnext( hFile, &txt_file ) == 0 )
            {
                printf( " %-12s \n", txt_file.name );
            }

           _findclose( hFile );
       }
    }
                   
/*****  Código das funções encapsuladas no módulo  *****/
    
    static int getCasaID ( TAB_tppTabuleiro pTab, int x, int y){
        return x+(y*pTab->largura);
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

    static int GetIdByXY(TAB_tppTabuleiro pTab, int x , int y , int colisao ){
        Casa parametro;
        int id = -1;
        parametro.x = x;
        parametro.y = y;
        GRA_BuscarVertice(pTab->pGrafo, &id, MesmaPosicao, (void*)&parametro);
        
        if(colisao)
            return id;
        else if(pTab->idCasa[id] != -1)
            return id;
        else
            return -1;
    }

/********** Fim do módulo de implementação: TAB Tabuleiro **********/
