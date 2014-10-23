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

#define VAZIO 1
#define PAREDE 2
#define INICIO 3
#define FINAL 4

typedef struct Casa_{
    //1 vazio, 2 parede, 3 inicio, 4 final
    int valor;
    //ids
    int norte;
    int leste;
    int sul;
    int oeste;
    // (x,y) para referência gráfica
    int x;
    int y;
}Casa ;
/*
Um tabuleiro é a conjunção de 
    Um grafo de Casas(valido)
    Uma string nome
    dois ints indicando altura e largura 
*/

typedef struct TAB_tppTabuleiro_{
    GRA_tppGrafo pGrafo;  
    char* nome;
    int altura;
    int largura;
} TAB_tppTabuleiro ;

/***** Protótipos das funções encapsuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/

    TAB_tpCondRet TAB_CriarTabuleiro ( TAB_tppTabuleiro* pTab, int alt, int lar, char* nome ){
        GRA_tppGrafo grafo = NULL;
        pTab->altura = alt;
        pTab->largura = lar;
        pTab->nome = nome;

        grafo = GRA_CriarGrafo(free);
        if(grafo == NULL)
            return TAB_CondRetFaltouMemoria ;

        pTab->pGrafo = grafo;
    
        return TAB_CondRetOK ;
    }

/***************************************************************************
*
*  Função: TAB  &Valida Movimento
*  ****/

/*
valida se eh possivel se mover do corrente para o proximo
ver se eh vizinho, se ta dentro do tabuleiro, se nao eh parede(se existe o vertice)
*/ 
    TAB_tpCondRet TAB_ValidaMovimento(TAB_tppTabuleiro* pTab, int idProximo) {
        Casa* corrente;
        int idCorrente, idVizinho;
        LIS_tppLista vizinhos;

        GRA_ObterIDCorrente(pTab->pGrafo, &idCorrente);
        GRA_ObterVizinhos(pTab->pGrafo, idCorrente, &vizinhos);
        GRA_ObterValor(pTab->pGrafo, idCorrente , (void**)&corrente );

        if( idProximo == corrente->norte
            || idProximo == corrente->leste
            || idProximo == corrente->sul
            || idProximo == corrente->oeste ) 
        {
            return TAB_CondRetOK ;
        }
        return TAB_CondRetMovimentoInvalido ;
    }

/***************************************************************************
*
*  Função: TAB  &Valida Alteracao
*  ****/
    
    //valida se eh possivel alterar o valor do corrente para valor
    TAB_tpCondRet TAB_ValidaAlteracao(TAB_tppTabuleiro* pTab,int valor){
        
        if ( valor == 3 || valor == 4 ) {
            // todo busca
        }
        else return TAB_CondRetOK ;
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
        //se tiver valor == 1 ou 3 ou 4
        //so vamos salvar os caminhos livres
        //se nao tiver valor == 2
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



