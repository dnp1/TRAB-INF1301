lista.h
typedef *Lista tpLista;
typedef *Elemento tpElem;

tpCondRet CriarLista(tpLista lista);

tpCondRet ExcluirLista(tpLista lista);

tpCondRet InserirElementoEsquerda(tpLista lista, Elemento e);

tpCondRet ExcluirCorrente(tpLista lista);

tpCondRet IrParaPrimeiro(tpLista lista);

tpCondRet IrParaProximo(tpLista lista);

tpCondRet IrParaAnterior(tpLista lista);

tpCondRet AcessarCorrente(tpLista lista);

