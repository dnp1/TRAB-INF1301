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

#include    "GRAFO.h"


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

int estaInicializado = 0 ;

#define DIM_VT_GRAFOS   10
#define DIM_VALOR     1000

GRA_tppGrafo vtRefGrafos[ DIM_VT_GRAFO ] ;

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
*     =insvert                inxGrafo  v1  CondRetEsp
*     =insvalor               inxGrafo  v1  string  CondRetEsp
*     =insaresta              inxGrafo  v1  v2  CondRetEsp
*     =excaresta              inxGrafo  v1  v2  CondRetEsp
*     =obterviz               inxGrafo  v1  lista CondRetEsp
*     =irparaviz              inxGrafo  v1  CondRetEsp
*     =acessvert              inxGrafo  v1  string  CondRetPonteiro
*     =acesscorr              inxGrafo  string  CondRetPonteiro
*     =excvertcorr            inxGrafo  CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      GRA_tpCondRet CondRetObtido   = GRA_CondRetOK ;
      GRA_tpCondRet CondRetEsperada = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
      char StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int  NumLidos      = -1 ;
      int  inxGrafo     = -1 ;

      int i ;

      TST_tpCondRet Ret ;

      #ifdef _DEBUG
         int  IntEsperado   = -1 ;
      #endif

      /* Tratar: inicializar contexto */

         if ( strcmp( ComandoTeste , RESET_GRAFO_CMD ) == 0 )
         {

            if ( estaInicializado )
            {
               for( i = 0 ; i < DIM_VT_GRAFOS ; i++ )
               {
                  GRA_DestruirGrafo( & ( vtRefGrafo[ i ] )) ;
               } /* for */
            } /* if */

            for( i = 0 ; i < DIM_VT_GRAFOS ; i++ )
            {
               vtRefGrafo[ i ] = 0 ;
            } /* for */

            estaInicializado = 1 ;

         } /* fim ativa: Tratar: inicializar contexto */
      
        /* Testar GRA Criar grafo */

         else if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &inxGrafo ) ;
            if ( ( NumLidos != 1 )
              || !VerificarInx( inxGrafo ))
            {
               return TST_CondRetParm ;
            } /* if */

            vtRetGrafo[ inxGrafo ] = GRA_CriarGrafo( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtRefGrafo[ inxGrafo ] ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Criar grafo */
         
         /* Testar GRA Destruir grafo */

         else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &inxGrafo ) ;
            if ( ( NumLidos != 1 )
              || !VerificarInx( inxGrafo ))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_DestruirGrafo( &( vtRefGrafo[ inxGrafo ] )) ;
            vtRefGrafo[ inxGrafo ] = NULL;
            
            return TST_CondRetOk ;
            
         } /* fim ativa: Testar GRA Destruir grafo */
         
         /* Testar GRA Inserir Vértice */

         else if ( strcmp( ComandoTeste , INS_VERT_CMD ) == 0 )
         {
            GRA_tppVertice * pVertice = (GRA_tppVertice *)malloc(sizeof(GRA_tppVertice)); 
            
            NumLidos = LER_LerParametros( "ii" ,
                               &inxGrafo , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxGrafo ))
            {
               return TST_CondRetParm ;
            } /* if */
            
            CondRetObtido = GRA_InserirVertice( vtRefGrafo[ inxGrafo ] , &pVertice);
            
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );
            
         } /* fim ativa: Testar GRA Inserir valor */
         
         else if ( strcmp( ComandoTeste , INS_VALOR_CMD ) == 0 )
         {
            GRA_tppVertice * pVertice = (GRA_tppVertice *)malloc(sizeof(GRA_tppVertice)); 
            
            NumLidos = LER_LerParametros( "isi" ,
                               &inxGrafo , StringDado , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 )
              || !VerificarInx( inxGrafo ))
            {
               return TST_CondRetParm ;
            } /* if */
            
            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;            
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */
            
            strcpy( pDado , StringDado ) ;
            
            CondRetObtido = GRA_InserirValor( vtRefGrafo[ inxGrafo ] , pDado ,&pVertice);
            
            if ( CondRetObtido != GRA_CondRetOk ){
                free ( pDado ) ;
            }
            
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir valor." );
            
         } /* fim ativa: Testar GRA Inserir valor */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV -Verificar índice de árvore
*
*  $FV Valor retornado
*     0 - inxArvore não vale
*     0 - inxArvore vale
*
***********************************************************************/

   int VerificarInx( int inxGrafo )
   {

      if ( ( inxGrafo <   0 )
        || ( inxGrafo >= DIM_VT_GRAFOS ))
      {
         return 0 ;
      } /* if */

      return 1 ;

   } /* Fim função: TARV -Verificar índice de árvore */

/********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/
