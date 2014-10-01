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
#include    "LISTA.h"


static const char RESET_GRAFO_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_GRAFO_CMD         [ ] = "=criargrafo"     ;
static const char DESTRUIR_GRAFO_CMD      [ ] = "=destruirgrafo"  ;
static const char INS_VERT_CMD            [ ] = "=insvert"        ;
static const char EXC_VERT_CMD            [ ] = "=excvert"        ;
static const char INS_ARESTA_CMD          [ ] = "=insaresta"      ;
static const char EXC_ARESTA_CMD          [ ] = "=excaresta"      ;
static const char OBTER_VIZ_CMD           [ ] = "=obterviz"       ;
static const char OBTER_ORIG_CMD          [ ] = "=obterorig"      ;
static const char OBTER_VAL_CMD           [ ] = "=obterval"       ;
static const char ALT_VAL_CMD             [ ] = "=altval"         ;

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
*     =insvert                inxGrafo  v1  string..CondRetEsp
*     =excvert                inxGrafo  v1  CondRetEsp
*     =insaresta              inxGrafo  v1  v2  CondRetEsp
*     =excaresta              inxGrafo  v1  v2  CondRetEsp
*     =obterviz               inxGrafo  v1  CondRetEsp
*     =obterorig              inxGrafo  CondRetEsp
*     =obterval               inxGrafo  v1  CondRetPonteiro
*     =altval                 inxGrafo  v1  string  CondRetPonteiro
*
***********************************************************************/
#define TAMANHO 256

GRA_TppVertice vertices[TAMANHO]; 
int sujo = 1;

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
      if(sujo){
          memset(vertices,0,TAMANHO*sizeof(GRA_TppVertice));      
          sujo = 0;
      }
      GRA_tpCondRet CondRetObtida   = GRA_CondRetOK ;
      GRA_tpCondRet CondRetEsperada = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      GRA_tpCondRet CondRetTemp = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char stringDado[  DIM_VALOR ] ;
      char * pDado ;

      int  NumLidos      = -1 ;
      int  inxGrafo     = -1 ;

      int i ;
      int id, _id;

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
            NumLidos = LER_LerParametros( "iisi" , &inxGrafo , &id, stringDado, &CondRetEsperada ) ;
            if ( ( NumLidos != 4 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
            
            vertices[id] = (GRA_tppVertice *)malloc(sizeof(GRA_tppVertice)); 
            CondRetObtida = GRA_InserirVertice( vtRefGrafo[ inxGrafo ] , (vertices+id), stringDado);
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao inserir vértice." );
            
         } /* fim ativa: Testar GRA Inserir vértice */
         
         /* Testar GRA Excluir vértice */
         
         else if ( strcmp( ComandoTeste , EXC_VERT_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
             
            CondRetObtida = GRA_ExcluirVertice( vtRefGrafo[ inxGrafo ] , (vertices+id) );
            vertice[id] = 0;
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao excluir vértice." );
            
         } /* fim ativa: Testar GRA Excluir vértice */
                  
         /* Testar GRA Inserir aresta */
         
         else if ( strcmp( ComandoTeste , INS_ARESTA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iiii" , &inxGrafo , &id, &_id, &CondRetEsperada ) ;
            if ( ( NumLidos != 4 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
             
            CondRetObtida = GRA_InserirAresta( vtRefGrafo[ inxGrafo ] , (vertices+id), (vertices+_id) );
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao inserir aresta." );
            
         } /* fim ativa: Testar GRA Inserir Aresta */
         
         /* Testar GRA Excluir aresta */
         
         else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iiii" , &inxGrafo , &id, &_id, &CondRetEsperada ) ;
            if ( ( NumLidos != 4 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
             
            CondRetObtida = GRA_ExcluirAresta( vtRefGrafo[ inxGrafo ] , (vertices+id), (vertices+_id) );
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao excluir aresta." );
            
         } /* fim ativa: Testar GRA Excluir Aresta */
         
         /* Testar GRA Obter vizinhos */
         
         else if ( strcmp( ComandoTeste , OBTER_VIZ_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
            
            LIS_tppLista vizinhos = LIS_CriarLista(NULL); 
            
            CondRetObtida = GRA_ObterVizinhos( vtRefGrafo[ inxGrafo ] , (vertices+id), &vizinhos);
            LIS_DestruirLista(vizinhos);
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao obter vizinhos." );
            
         } /* fim ativa: Testar GRA Obter vizinhos */
         
         /* Testar GRA Obter origens */
         
         else if ( strcmp( ComandoTeste , OBTER_ORIG_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" , &inxGrafo , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
            
            LIS_tppLista origens = LIS_CriarLista(NULL); 
            
            CondRetObtida = GRA_ObterOrigens( vtRefGrafo[ inxGrafo ] , &origens);
            LIS_DestruirLista(origens);
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao obter origens." );
            
         } /* fim ativa: Testar GRA Obter origens */
         
         /* Testar GRA Obter valor */
         
         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
            
            CondRetObtida = GRA_ObterValor( vtRefGrafo[ inxGrafo ], (vertices+id), &stringDado);
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao obter valor." );
            
         } /* fim ativa: Testar GRA Obter valor */    
         
         /* Testar GRA Alterar valor */
         
         else if ( strcmp( ComandoTeste , ALT_VAL_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iisi" , &inxGrafo , &id, stringDado,  &CondRetEsperada ) ;
            if ( ( NumLidos != 4 ) || !VerificarInx( inxGrafo ) || !VerificarId(id))
            {
               return TST_CondRetParm ;
            } /* if */
     
            pDado = ( char * ) malloc( strlen( stringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , stringDado ) ;
            
            CondRetObtida = GRA_AlterarValor( vtRefGrafo[ inxGrafo ], (vertices+id), &pDado ) ;
            
            if ( CondRetObtida != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */
            
            CondRetTemp = GRA_ObterValor ( vtRefGrafo[ inxGrafo ], (vertices+id), stringDado ) ;
            
            if ( strcmp ( pDado, stringDado) != 0 )
            {
                free ( pDado ) ;
                
                return TST_CompararPonteiro ( pDado , stringDado , 
                                           "O valor obtido é diferente do alterado" ) ;
            } /* if */                               
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao alterar valor." );
            
         } /* fim ativa: Testar GRA Alterar valor */
         
/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA -Verificar índice de grafo
*
*  $FV Valor retornado
*     0 - inxGrafo não vale
*     1 - inxGrafo vale
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

/***********************************************************************
*
*  $FC Função: TGRA - Verificar Id
*
*  $FV Valor retornado
*     0 - vertice ja existe
*     1 - vertice nao existe
*
***********************************************************************/
    int VerificarId(int id){
        if (vertices[id] == 0 ) return 1;
        else return 0;
    }
/********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/
