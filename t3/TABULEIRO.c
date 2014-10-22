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
 *        1     eav   20/10/2014     //
 *
 ***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#undef TABULEIRO_OWN

struct Casa{
    int valor;//1 vazio, 2 inicio, 3 final
    int norte;//ids
    int leste;
    int sul;
    int oeste;
    int x;//index. 0 
    int y;//index. 0
    //(0,0) superior esquerdo
}
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

TAB_tpCondRet TAB_CriarTabuleiro ( int alt, int lar, char* nome ){
    TAB_tppTabuleiro * pTab = NULL;
    int altura, largura;
    char* nome;
    // leitura da altura, largura e nome 
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
//so vamos salvar os caminhos livres
print(idVertice x y num_vizinhos)
idVertice++
para cada vizinho 
print(idVertice idVizinho idAresta)//tomar cuidado para nao repetir aresta, ou mexer no grafo para suportar/esperar isso
idAresta++
exclui vertice
}

Exemplo:

I..##
.###.
##.##
##F##

======

134##
2###5
##6##
##7##


======
mapa1
10 10
1 7
1 0 0 2
1 2 1
1 3 2
2 0 1 0

3 1 0 1
3 4 3
4 2 0 0

5 4 1 0

6 2 2 1
6 7 4
7 2 3 0

   TAB_tpCondRet TAB_CarregaTabuleiro(TAB_tppTabuleiro pTab){}

   Antes de salvar valida as regras do tabuleiro
   ve se existe inicial, final e se existe apenas 1 destes
   TAB_tpCondRet TAB_ValidaTabuleiro(tpTabuleiro pTab){}


   valida se eh possivel se mover do corrente para o proximo
   ver se eh vizinho, se ta dentro do tabuleiro, se nao eh parede(se existe o vertice)
   TAB_tpCondRet TAB_ValidaMovimento(tpTabuleiro pTab,int idProximo){}

   valida se eh possivel alterar o valor do corrente para valor
   TAB_tpCondRet TAB_ValidaAlteracao(tpTabuleiro pTab,int valor){}

 */
