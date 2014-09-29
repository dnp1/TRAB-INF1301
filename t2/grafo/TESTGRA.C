/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste Grafo genérico
*
*  Arquivo gerado:              TESTGRA.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\GRAFO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: eav
*
*  $HA Histórico de evolução:
*     1       eav   27/set/2014 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "GRAFO.H"


static const char RESET_GRAFO_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_GRAFO_CMD         [ ] = "=criargrafo"     ;
static const char DESTRUIR_GRAFO_CMD      [ ] = "=destruirgrafo"  ;
static const char INS_VERT_CMD            [ ] = "=insvert"        ;
static const char INS_VALOR_CMD           [ ] = "=insvalor"       ;
static const char INS_ARESTA_CMD          [ ] = "=insaresta"      ;
static const char EXC_ARESTA_CMD          [ ] = "=excaresta"      ;
static const char OBTER_VIZ_CMD           [ ] = "=obterviz"       ;
static const char IR_PARA_VIZ_CMD         [ ] = "=irparaviz"      ;
static const char ACESS_VERT_CMD          [ ] = "=acessvert"      ;
static const char ACESS_CORR_CMD          [ ] = "=acesscorr"      ;
static const char EXC_VERT_CORR_CMD       [ ] = "=excvertcorr"    ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VALOR     100

GRA_tppGrafo   vtGrafos[ DIM_VT_GRAFO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar grafo
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de grafos. Provoca vazamento de memória
*     =criargrafo             inxGrafo
*     =destruirgrafo          inxGrafo
*     =insvert                inxGrafo    
*     =insvalor               inxGrafo
*     =insaresta              inxGrafo
*     =excaresta              inxGrafo
*     =obterviz               inxGrafo
*     =irparaviz              inxGrafo
*     =acessvert              inxGrafo
*     =acesscorr              inxGrafo
*     =excvertcorr            inxGrafo
*
***********************************************************************/
