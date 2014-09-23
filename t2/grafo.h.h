grafo.h
typedef *Grafo tpGrafo;
typedef *Vertice tpVertice;

tpCondRet CriarGrafo(tpGrafo grafo);

tpCondRet ExcluirGrafo(tpGrafo grafo);

tpCondRet InserirVertice(tpGrafo grafo);

tpCondRet ExcluirVerticeCorrente(tpGrafo grafo);

tpCondRet InserirAresta(tpGrafo grafo,tpVertice v1, tpVertice v2);

tpCondRet ExcluirAresta(tpGrafo grafo,tpVertice v1, tpVertice v2);

tpCondRet ObterVizinhos(tpGrafo grafo, tpVertice v1, int * quantidade);

tpCondRet IrParaVizinho(tpGrafo grafo, tpVertice v1);

tpCondRet AcessarCorrente(tpGrafo grafo);