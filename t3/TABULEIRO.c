struct Casa{
    int valor;//1 vazio, 2 parede, 3 inicio, 4 final
    int norte;//ids
    int leste;
    int sul;
    int oeste;
    int x;
    int y;
}
/*
Um tabuleiro é a conjunção de 
    Um grafo de Casas(valido)
    Uma string nome
    dois ints indicando altura e largura 
*/
typedef struct Tabuleiro_{
    tpGrafo pGrafo;
    char* nome;
    int altura;
    int largura;
} Tabuleiro;
typedef Tabuleiro * tpTabuleiro;

TAB_CondRet TAB_SalvaTabuleiro(tpTabuleiro pTab){
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
/*
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

TAB_CondRet TAB_CarregaTabuleiro(tpTabuleiro pTab){}

//Antes de salvar valida as regras do tabuleiro
//ve se existe inicial, final e se existe apenas 1 destes
TAB_CondRet TAB_ValidaTabuleiro(tpTabuleiro pTab){}

TAB_CondRet TAB_CriaTabuleiro(tpTabuleiro* pTab, char* nome,int lar, int alt){}
//valida se eh possivel se mover do corrente para o proximo
//ver se eh vizinho, se ta dentro do tabuleiro, se nao eh parede(se existe o vertice)
TAB_CondRet TAB_ValidaMovimento(tpTabuleiro pTab,int idProximo){}
//valida se eh possivel alteraro valor do corrente para valor
TAB_CondRet TAB_ValidaAlteracao(tpTabuleiro pTab,int valor){}


