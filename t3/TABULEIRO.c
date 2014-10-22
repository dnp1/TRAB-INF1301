struct Casa{
    int valor;//1 vazio, 2 inicio, 3 final
    int norte;//ids
    int leste;
    int sul;
    int oeste;
    int x; //indexado em 0
    int y; //indexado em 0
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

TAB_CondRet TAB_CarregaTabuleiro(tpTabuleiro* pTab,char* nome){}

//Antes de salvar valida as regras do tabuleiro
//ve se existe inicial, final e se existe apenas 1 destes
TAB_CondRet TAB_ValidaTabuleiro(tpTabuleiro pTab){}

TAB_CondRet TAB_CriaTabuleiro(tpTabuleiro* pTab, char* nome,int lar, int alt){}
//valida se eh possivel se mover do corrente para o proximo
//ver se eh vizinho, se ta dentro do tabuleiro, se nao eh parede(se existe o vertice)
TAB_CondRet TAB_ValidaMovimento(tpTabuleiro pTab,int idProximo){}
//valida se eh possivel alteraro valor do corrente para valor
TAB_CondRet TAB_ValidaAlteracao(tpTabuleiro pTab,int valor){}


