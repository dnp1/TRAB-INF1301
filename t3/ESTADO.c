/***************************************************************************
*  $MCI Módulo de implementação: EST  Tabuleiro de labirinto
*
*  Arquivo gerado:              ESTADO.c
*  Letras identificadoras:      EST
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\ESTADO.BSW
*
*  Projeto: INF 1301 / Labirinto
*  Gestor:  LSKDANEAV
*  Autores: lsk
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		 1	   lsk	 20/10/2014		//
*
***************************************************************************/
#include "TIPOESTADO.h"
#include "ESTADO.h"
#include <stdlib.h>
/***********************************************************************
*
*  $TC Tipo de dados: EST Estado
*
*
*  $ED Descrição do tipo
*       Agrupa em uma única entidade um par Menus, Tabuleiro, compondo um estado de um jogo.
*
***********************************************************************/
typedef struct estado_{
    MEN_tppMenus Menus;
    TAB_tppTabuleiro Tabuleiro;
} tpEstado;

/*****  Código das funções encapsuladas no módulo  *****/

/************** Código das funções exportadas no módulo  ***************/
/***********************************************************************
*
*  $FC Função: EST Criar Estado
*
***********************************************************************/
EST_tpCondRet EST_CriaEstado(EST_tppEstado* est){
    
    EST_tppEstado e = (EST_tppEstado)malloc(sizeof(tpEstado));
    
    if(e==NULL) 
    {
        return EST_CondRetFaltouMemoria;
    }
    if(MEN_CriarMenus(&(e->Menus))!=MEN_CondRetOK){
        free(e);
        return EST_CondRetFaltouMemoria;
    }; 
    e->Tabuleiro = NULL;
    e->Menus = NULL;
    *est = e;
    
    return EST_CondRetOK;
}

/***********************************************************************
*
*  $FC Função: EST Destruir Estado
*
***********************************************************************/
EST_tpCondRet EST_DestruirEstado(EST_tppEstado est){
    TAB_DestruirTabuleiro(est->Tabuleiro);
    MEN_DestruirMenus(est->Menus);
    free(est);

    return EST_CondRetOK;
}
/***********************************************************************
*
*  $FC Função: EST Alterar Menus
*
***********************************************************************/

EST_tpCondRet EST_SetMenus(EST_tppEstado e, MEN_tppMenus men){
    e->Menus = men;
    return EST_CondRetOK;
}
/***********************************************************************
*
*  $FC Função: EST Alterar Tabuleiro
*
***********************************************************************/
EST_tpCondRet EST_SetTabuleiro(EST_tppEstado e,TAB_tppTabuleiro tab){
    e->Tabuleiro = tab;
    return EST_CondRetOK;
}
/***********************************************************************
*
*  $FC Função: EST Obter Menus
*
***********************************************************************/
EST_tpCondRet EST_GetMenus(EST_tppEstado e, MEN_tppMenus* men){
    *men =  e->Menus;
    if(e->Menus == NULL) 
        return EST_CondRetFaltouMemoria;
    return EST_CondRetOK;
}
/***********************************************************************
*
*  $FC Função: EST Obter Tabuleiro
*
***********************************************************************/
EST_tpCondRet EST_GetTabuleiro(EST_tppEstado e,TAB_tppTabuleiro* tab){
    *tab =  e->Tabuleiro;
    if(e->Tabuleiro == NULL) 
        return EST_CondRetFaltouMemoria;
    return EST_CondRetOK;
}
/********** Fim do módulo de implementação: EST Estado **********/
