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

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

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
static const char BUSCA_CAM_CMD           [ ] = "=buscacam"       ;
static const char INS_VIZ_CORR_CMD        [ ] = "=insvizcorr"     ;
static const char EXC_VIZ_CORR_CMD        [ ] = "=excvizcorr"     ;
static const char OBTER_VIZ_CORR_CMD      [ ] = "=obtervizcorr"   ;
static const char OBTER_VAL_CORR_CMD      [ ] = "=obtervalcorr"   ;
static const char ALT_VAL_CORR_CMD        [ ] = "=altvalcorr"     ;
static const char BUSCA_CAM_CORR_CMD      [ ] = "=buscacamcorr"       ;
static const char IR_VIZ_CORR_CMD         [ ] = "=irvizcorr"      ;
static const char MUDAR_CORR_CMD          [ ] = "=mudarcorr"      ;

int estaInicializado = 0 ;

#define DIM_VT_GRAFOS   10
#define DIM_VALOR     1000

GRA_tppGrafo vtRefGrafos[ DIM_VT_GRAFOS ] ;
char * stringDado = NULL ;
//-2 grafo nao existe -> -1 corrente = null -> 0+ id do corrente
int corrente[ DIM_VT_GRAFOS ];
/***********************************************************************
*
*  $TC Tipo de dados: TESTGRA Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno para as funções de obter valor. 
*     No script de teste é definido o pNULL = 1 e o pNaoNULL = 0.
*     Ápos a chamada das funções de obter valor, o retorno esperado é comparado com os dois enums abaixo,
*     de modo que o script possa interpretar de forma coesa.
*
***********************************************************************/

  typedef enum {

    TESTGRA_pNULL,
        /* ponteiro nulo*/
    TESTGRA_pNaoNULL,
        /* ponteiro !nulo*/

   } TESTGRA_tpCondRet ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

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
*           - anula o vetor de grafos Provoca vazamento de memória
*     =criargrafo             inxGrafo
*     =destruirgrafo          inxGrafo
*     =insvert                inxGrafo  string  v1  CondRetEsp
*     =excvert                inxGrafo  v1  CondRetEsp
*     =insaresta              inxGrafo  v1  v2  a1  CondRetEsp
*     =excaresta              inxGrafo  a1  CondRetEsp
*     =obterviz               inxGrafo  v1  CondRetEsp
*     =obterorig              inxGrafo  CondRetEsp
*     =obterval               inxGrafo  v1  CondRetPonteiro
*     =altval                 inxGrafo  v1  string  CondRetPonteiro
*     =buscacam               inxGrafo  v1  v2  CondRetEsp
*     =insvizcorr             inxGrafo  string v1 CondRetEsp
*     =excvizcorr             inxGrafo  v1  CondRetEsp
*     =obtervizcorr           inxGrafo  CondRetEsp
*     =obtervalcorr           inxGrafo  CondRetEsp
*     =altvalcorr             inxGrafo  string  CondRetEsp
*     =buscacamcorr           inxGrafo  v1  CondRetEsp
*     =irvizcorr              inxGrafo  v1  CondRetEsp
*     =mudarcorr              inxGrafo  v1  CondRetEsp
*
***********************************************************************/
#define TAMANHO 256

static int VerificarInx( int inxGrafo );
static int VerificarId (int id); 
int sujo = 1;

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {   
      GRA_tpCondRet CondRetObtida   = GRA_CondRetOK ;
      GRA_tpCondRet CondRetEsperada = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      GRA_tpCondRet CondRetTemp = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char stringTemp[  DIM_VALOR ] ;
      char * pDado ;

      int  NumLidos      = -1 ;
      int  inxGrafo     = -1 ;

      int i ;
      int id, _id , idAresta;
      int id2;
      if (sujo) {
         for(i=0;i<DIM_VT_GRAFOS;i++){
             corrente[i] = -2;
             vtRefGrafos[i] = NULL;
         }
         sujo = 0;
      }

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
                  if(vtRefGrafos[i] != NULL)
                      GRA_DestruirGrafo( vtRefGrafos[ i ] ) ;
               } /* for */
            } /* if */

            for( i = 0 ; i < DIM_VT_GRAFOS ; i++ )
            {
               vtRefGrafos[ i ] = NULL ;
               corrente[i] = -2;
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
          
            vtRefGrafos[ inxGrafo ] = GRA_CriarGrafo( free ) ;
            corrente[ inxGrafo ] = -1;
            return TST_CompararPonteiroNulo( 1 , vtRefGrafos[ inxGrafo ] ,
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

            GRA_DestruirGrafo( vtRefGrafos[ inxGrafo ] ) ;
            vtRefGrafos[ inxGrafo ] = NULL;
            corrente[ inxGrafo ] = -2;
            return TST_CondRetOK ;
            
         } /* fim ativa: Testar GRA Destruir grafo */
         
         /* Testar GRA Inserir Vértice */

         else if ( strcmp( ComandoTeste , INS_VERT_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "isii" , &inxGrafo , stringTemp , &id , &CondRetEsperada ) ;
            if ( ( NumLidos != 4 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */      

            stringDado = (char*)calloc(1, strlen(stringTemp)+1);

            if ( stringDado == NULL ) {
               return TST_CondRetMemoria ;
            } /* if */  

            strcpy(stringDado, stringTemp);

            CondRetObtida = GRA_InserirVertice( vtRefGrafos[ inxGrafo ] , stringDado , id ); 

            if (CondRetObtida != GRA_CondRetOK) {
                free(stringDado);
            }
            else if(corrente[ inxGrafo] == -1) {
                 corrente[inxGrafo] = id;
            }
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao inserir vértice." );
            
         } /* fim ativa: Testar GRA Inserir vértice */
         
         /* Testar GRA Excluir vértice */
         
         else if ( strcmp( ComandoTeste , EXC_VERT_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
            
            CondRetObtida = GRA_ExcluirVertice( vtRefGrafos[ inxGrafo ] , id );
            if(CondRetObtida == GRA_CondRetOK && id == corrente[inxGrafo]) corrente[inxGrafo] = -1;
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao excluir vértice." );
            
         } /* fim ativa: Testar GRA Excluir vértice */
                  
         /* Testar GRA Inserir aresta */
         
         else if ( strcmp( ComandoTeste , INS_ARESTA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iiiii" , &inxGrafo , &id, &_id, &idAresta, &CondRetEsperada ) ;
            if ( ( NumLidos != 5 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
             
            CondRetObtida = GRA_InserirAresta( vtRefGrafos[ inxGrafo ] , id , _id , idAresta);
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao inserir aresta." );
            
         } /* fim ativa: Testar GRA Inserir Aresta */
         
         /* Testar GRA Excluir aresta */
         
         else if ( strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &idAresta, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
             
            CondRetObtida = GRA_ExcluirAresta( vtRefGrafos[ inxGrafo ] , idAresta );
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao excluir aresta." );
            
         } /* fim ativa: Testar GRA Excluir Aresta */
         
         /* Testar GRA Obter vizinhos */
         
         else if ( strcmp( ComandoTeste , OBTER_VIZ_CMD ) == 0 )
         {
            LIS_tppLista vizinhos = NULL;
       
      NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
            
            CondRetObtida = GRA_ObterVizinhos( vtRefGrafos[ inxGrafo ] , id , &vizinhos );
            if(vizinhos != NULL){
                LIS_DestruirLista(vizinhos);
            }
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao obter vizinhos." );
            
         } /* fim ativa: Testar GRA Obter vizinhos */
         
         /* Testar GRA Obter origens */
         
         else if ( strcmp( ComandoTeste , OBTER_ORIG_CMD ) == 0 )
         {            
            LIS_tppLista origens = NULL;
            
            NumLidos = LER_LerParametros( "ii" , &inxGrafo , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = GRA_ObterOrigens( vtRefGrafos[ inxGrafo ] , &origens );
            if(origens!=NULL){
                 LIS_DestruirLista(origens);
            }
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao obter origens." );
            
         } /* fim ativa: Testar GRA Obter origens */
         
         /* Testar GRA Obter valor */
         
         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
            
            CondRetObtida = GRA_ObterValor( vtRefGrafos[ inxGrafo ], id , (void**)&pDado) ;

            if(CondRetObtida == GRA_CondRetOK) 
                return TST_CompararInt( CondRetEsperada , TESTGRA_pNaoNULL ,
                                        "Retorno errado ao obter valor." );

            else if(CondRetObtida == GRA_CondRetNaoEhVertice) 
                return TST_CompararInt( CondRetEsperada , TESTGRA_pNULL ,
                                        "Retorno errado ao obter valor." );

            else if(CondRetObtida == GRA_CondRetGrafoVazio) 
                return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                        "Retorno errado ao obter valor." );
            
         } /* fim ativa: Testar GRA Obter valor */    
         
         /* Testar GRA Alterar valor */
         
         else if ( strcmp( ComandoTeste , ALT_VAL_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iisi" , &inxGrafo , &id, stringTemp,  &CondRetEsperada ) ;
            if ( ( NumLidos != 4 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
            
            /* Como alterar valor não libera a memória do valor armazenado, 
            é preciso obter o valor e liberar a memoria antes de alterar */
            CondRetTemp = GRA_ObterValor ( vtRefGrafos[ inxGrafo ], id , (void**)&pDado ) ;
            if(CondRetTemp == GRA_CondRetOK) {
              free ( pDado ) ;
            }
     
            stringDado = (char* ) calloc(1, strlen(stringTemp) + 1) ;

            if (stringDado == NULL) {
               return TST_CondRetMemoria ;
            } /* if */  

            strcpy( stringDado , stringTemp ) ;
            
            CondRetObtida = GRA_AlterarValor( vtRefGrafos[ inxGrafo ], id , stringDado ) ;
            
            
            
            CondRetTemp = GRA_ObterValor ( vtRefGrafos[ inxGrafo ], id , (void**)&pDado ) ;
            
            if ( CondRetObtida == GRA_CondRetOK && (CondRetTemp != GRA_CondRetOK || strcmp ( pDado, stringDado) != 0 ))
            {
                return TST_CompararPonteiro ( pDado , stringDado , 
                                           "O valor obtido e diferente do alterado" ) ;
            } /* if */                               

            if (CondRetObtida != GRA_CondRetOK) {
               free(stringDado) ;
            } /* if */
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao alterar valor." );
            
         } /* fim ativa: Testar GRA Alterar valor */
                
         /* Testar GRA Buscar Caminho */
         
         else if ( strcmp( ComandoTeste , BUSCA_CAM_CMD ) == 0 )
         {            
            LIS_tppLista caminho;

            NumLidos = LER_LerParametros( "iiii" , &inxGrafo , &id , &_id , &CondRetEsperada ) ;
            if ( ( NumLidos != 4 ) || !VerificarInx( inxGrafo )  )
            {
               return TST_CondRetParm ;
            } /* if */

            
            CondRetObtida = GRA_BuscarCaminho( vtRefGrafos[ inxGrafo ] , id , _id , &caminho ) ;
            if(caminho!=NULL) {
                LIS_DestruirLista(caminho);
            }
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao buscar o caminho." );
            
         } /* fim ativa: Testar GRA Buscar Caminho */
         
         /* Testar GRA Inserir Vizinho Corrente */

         else if ( strcmp( ComandoTeste , INS_VIZ_CORR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "isiii" , &inxGrafo , stringTemp , &id , &id2,&CondRetEsperada ) ;
            if ( ( NumLidos != 5 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */ 

            stringDado = (char*)calloc(strlen(stringTemp) + 1, sizeof(char));

            strcpy(stringDado, stringTemp);          

            CondRetObtida = GRA_InserirVizinhoCorrente( vtRefGrafos[ inxGrafo ] , stringDado , id , id2) ;           
            if (CondRetObtida != GRA_CondRetOK) {
              free(stringDado);
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao inserir vizinho do corrente." );
            
         } /* fim ativa: Testar GRA Inserir Vizinho Corrente */        
         
         /* Testar GRA Excluir Vizinho Corrente */

         else if ( strcmp( ComandoTeste , EXC_VIZ_CORR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */           

            CondRetObtida = GRA_ExcluirVizinhoCorrente( vtRefGrafos[ inxGrafo ] , id ) ;           
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao excluir vizinho do corrente." );
            
         } /* fim ativa: Testar GRA Excluir Vizinho Corrente */        
                           
         /* Testar GRA Obter Vizinhos Corrente */
         
         else if ( strcmp( ComandoTeste , OBTER_VIZ_CORR_CMD ) == 0 )
         {            
            LIS_tppLista vizinhos = NULL;//Lista é criada dentro;

            NumLidos = LER_LerParametros( "ii" , &inxGrafo , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = GRA_ObterVizinhosCorrente( vtRefGrafos[ inxGrafo ] , &vizinhos );
            
            if (vizinhos != NULL) {
              LIS_DestruirLista(vizinhos);
            }
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao obter vizinhos do corrente." );
            
         } /* fim ativa: Testar GRA Obter Vizinhos Corrente*/                  
                 
         /* Testar GRA Obter Valor Corrente */
         
         else if ( strcmp( ComandoTeste , OBTER_VAL_CORR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" , &inxGrafo , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
            
            CondRetObtida = GRA_ObterValorCorrente( vtRefGrafos[ inxGrafo ] , (void**)&pDado) ;
            
            if(CondRetObtida == GRA_CondRetOK) 
                return TST_CompararInt( CondRetEsperada , TESTGRA_pNaoNULL ,
                                        "Retorno errado ao obter valor." );

            else if(CondRetObtida == GRA_CondRetNaoEhVertice) 
                return TST_CompararInt( CondRetEsperada , TESTGRA_pNULL ,
                                        "Retorno errado ao obter valor." );

            else if(CondRetObtida == GRA_CondRetGrafoVazio) 
                return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                        "Retorno errado ao obter valor." );
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao obter valor do corrente." );
            
         } /* fim ativa: Testar GRA Obter Valor Corrente */           
         
         /* Testar GRA Alterar Valor Corrente */
         
         else if ( strcmp( ComandoTeste , ALT_VAL_CORR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "isi" , &inxGrafo , stringTemp, &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */
            
            /* Como alterar valor não libera a memória do valor armazenado, 
            é preciso obter o valor e liberar a memoria antes de alterar */
            
            CondRetTemp = GRA_ObterValorCorrente ( vtRefGrafos[ inxGrafo ], (void**)&pDado ) ;

            if (CondRetTemp == GRA_CondRetGrafoVazio) {
              return TST_CompararInt( CondRetEsperada , CondRetTemp , "O grafo não possui vértice corrente, está vazio." );
            }

            free ( pDado ) ;
            
            stringDado = (char* ) calloc(strlen( stringTemp ) + 1, sizeof(char)) ;
            if ( stringDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */  


            strcpy( stringDado,stringTemp ) ;
            
            CondRetObtida = GRA_AlterarValorCorrente ( vtRefGrafos[ inxGrafo ] , stringDado ) ;
            
        
            
            CondRetTemp = GRA_ObterValorCorrente ( vtRefGrafos[ inxGrafo ] , (void**)&pDado ) ;
            
            if ( CondRetObtida == GRA_CondRetOK && (CondRetTemp != GRA_CondRetOK || strcmp ( pDado, stringDado) != 0 ))
            {
                return TST_CompararPonteiro ( pDado , stringDado , 
                                           "O valor obtido e diferente do alterado (do corrente)" ) ;
            } /* if */       

            if ( CondRetObtida != GRA_CondRetOK )
            {
               free( stringDado );
            } /* if */                        
            
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao alterar valor corrente." );
            
         } /* fim ativa: Testar GRA Alterar Valor Corrente */
                
         /* Testar GRA Buscar Caminho Corrente */
         
         else if ( strcmp( ComandoTeste , BUSCA_CAM_CORR_CMD ) == 0 )
         {            
            LIS_tppLista caminho;

            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo )  )
            {
               return TST_CondRetParm ;
            } /* if */

            
            CondRetObtida = GRA_BuscarCaminhoCorrente( vtRefGrafos[ inxGrafo ] , id , &caminho) ;
            if(caminho!=NULL){
                 LIS_DestruirLista(caminho);
            }
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao buscar o caminho desde o corrente." );
            
         } /* fim ativa: Testar GRA Buscar Caminho Corrente */
         
         /* Testar GRA Ir Vizinho Corrente */

         else if ( strcmp( ComandoTeste , IR_VIZ_CORR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */           

            CondRetObtida = GRA_IrVizinhoCorrente( vtRefGrafos[ inxGrafo ] , id ) ;           
            if(CondRetObtida == GRA_CondRetOK) corrente[ inxGrafo] = id; 
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao ir pro vizinho do corrente." );
            
         } /* fim ativa: Testar GRA Ir Vizinho Corrente */        
                                     
         /* Testar GRA Mudar Corrente */

         else if ( strcmp( ComandoTeste , MUDAR_CORR_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , &id , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 ) || !VerificarInx( inxGrafo ) )
            {
               return TST_CondRetParm ;
            } /* if */           

            CondRetObtida = GRA_MudarCorrente( vtRefGrafos[ inxGrafo ] , id ) ;           
            if(CondRetObtida == GRA_CondRetOK) corrente[ inxGrafo] = id; 
            return TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                    "Retorno errado ao mudar de vértice." );
            
         } /* fim ativa: Testar GRA Mudar Corrente */        
                  
                  
         return TST_CondRetNaoConhec ;
    }     
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
    int VerificarId(int id) {
        if (id = -1 ) return 0;
        else return 1;
    }


//DOCUMENTAR
static void DestruirValor( void * pValor ) {
   free(pValor);
}


/********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/
