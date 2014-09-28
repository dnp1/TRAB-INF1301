//grafo nao direcionado, com pesos
typedef struct tpGrafo GRA_grafo;

typedef struct tpVertice GRA_vertice;

inserir aresta(GRA_grafo g,GRA_vertice u,GRA_vertice v,int(enum) p)
    se ja existir aresta entre u e v, erro de duplicata
    se u ou v nao existem, erro de inexistencia

        busca u em cada componente de g, (cc. erro de inexistencia)
            busca v na componente de u, se achar, adiciona v nos vizinhos de u (e vice versa)(cc. erro de duplicata)
                                        se nao, procura a componente de v, se achar v, exclui a componente de v, adiciona v nos vizinhos de u (e vice versa)(cc. erro de duplicata)
                                                                           se nao achar. erro de inexistencia  

inserir vertice(GRA_grafo g,GRA_vertice* v)
    se nao houver espaco, erro falta de espaco
 
        aloca espaço para v, retorna v(cc. erro falta de espaco)
        cria uma componente conexa apontando para v
        
excluir aresta(GRA_grafo g,GRA_vertice u,GRA_vertice v)
    se u ou v nao existem, erro de inexistencia
    se u nao esta nos vizinhos de v, erro de inexistencia
        
    se v nao esta nos vizinhos de u, erro de inexistencia
        busca u nos vizinhos de v, (cc. erro de inexistencia)
            busca v nos vizinhos de u, (cc. erro de inexistencia)
                exclui aresta de ambos lados
                se v nao esta na componente de u, cria componente conexa apontando para v.
                

