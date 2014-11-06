/***************************************************************************
*  $MCI Módulo de implementação: TEST Teste Tabuleiro para labirinto
*
*  Arquivo gerado:              TESTESTADO.c
*  Letras identificadoras:      TEST
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\ESTADO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: eav
*
*  $HA Histórico de evolução:
*     1       eav   5/nov/2014 início desenvolvimento
*
***************************************************************************/


#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "ESTADO.h"

    static const char RESET_ESTADO_CMD         [] = "=resetteste"         ;
    static const char CRIA_ESTADO_CMD          [] = "=criaestado"         ;
    static const char DESTRUIR_ESTADO_CMD      [] = "=destruirestado"     ;
    static const char GET_MENUS_CMD            [] = "=getmenus"           ;
    static const char SET_MENUS_CMD            [] = "=setmenus"           ;
    static const char GET_TABULEIRO_CMD        [] = "=gettabuleiro"       ;
    static const char SET_TABULEIRO_CMD        [] = "=settabuleiro"           ;

int estaInicializado = 0 ;

#define DIM_VT_ESTADOS   10
#define DIM_VALOR 4

EST_tppEstado vtRefEstados[ DIM_VT_ESTADOS ] ;


/***** Protótipos das funções encapuladas no módulo *****/
   
    static int VerificarInx( int inxEstado );

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar estado
*
*  $ED Descrição da função
*     Podem ser criadas até 10 estados, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de estados Provoca vazamento de memória
*     =criarestado            inxEstado  CondRetEsp
*     =destruirestado         inxEstado  CondRetEsp
*     =getmenus               inxEstado  CondRetEsp
*     =setmenus               inxEstado  CondRetEsp
*     =gettabuleiro           inxEstado  CondRetEsp
*     =settabuleiro           inxEstado  CondRetEsp       
*
*
***********************************************************************/


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
    {
        EST_tpCondRet CondRetObtida = EST_CondRetOK ;
        EST_tpCondRet CondRetEsperada = EST_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
        MEN_tppMenus menu;
        TAB_tppTabuleiro tabuleiro;
        int i;
        int inxEstado = -1;
        int NumLidos = -1;

        /* Tratar: inicializar contexto */
      
        if ( strcmp( ComandoTeste , RESET_ESTADO_CMD ) == 0 ){

        if ( estaInicializado ){
            for( i = 0 ; i < DIM_VT_ESTADOS ; i++ ){
                EST_DestruirEstado( ( vtRefEstados[ i ] )) ;
            }
        }

        for( i = 0 ; i < DIM_VT_ESTADOS ; i++ ){
            vtRefEstados[ i ] = 0 ;
        }

        estaInicializado = 1 ;

        } /* fim ativa: Tratar: inicializar contexto */
      
        /* Testar EST Criar estado */         
        else if ( strcmp( ComandoTeste , CRIA_ESTADO_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros("ii",&inxEstado,&CondRetEsperada);
            if((NumLidos != 2) || !VerificarInx(inxEstado))
            {
                return TST_CondRetParm;
            }
            printf("\n\ninx = %d\n\n",inxEstado);
            CondRetObtida = EST_CriaEstado( vtRefEstados[inxEstado] );
            return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao criar estado." );
        } /* fim ativa: Testar EST Criar estado */
            
        /* Testar EST Destruir estado */
        else if ( strcmp( ComandoTeste , DESTRUIR_ESTADO_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros("ii",&inxEstado,&CondRetEsperada);
            if((NumLidos != 2) || !VerificarInx(inxEstado))
            {
                return TST_CondRetParm;
            }

            CondRetObtida = EST_DestruirEstado( vtRefEstados[inxEstado] );
            return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao criar estado." );
        } /* fim ativa: Testar EST Destruir estado */
                    
        /* Testar EST Get Menus */
        else if ( strcmp( ComandoTeste , GET_MENUS_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros("ii",&inxEstado,&CondRetEsperada);
            if((NumLidos != 2) || !VerificarInx(inxEstado))
            {
                return TST_CondRetParm;
            }
            
            CondRetObtida = EST_GetMenus( vtRefEstados[inxEstado],&menu);
            return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao obter os menus." );
        } /* fim ativa: Testar EST Get Menus */
                    
        /* Testar EST Set Menus */
        else if ( strcmp( ComandoTeste , SET_MENUS_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros("ii",&inxEstado,&CondRetEsperada);
            if((NumLidos != 2) || !VerificarInx(inxEstado))
            {
                return TST_CondRetParm;
            }

            MEN_CriarMenus(&menu);


            CondRetObtida = EST_SetMenus( vtRefEstados[inxEstado],menu);
            return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao setar os menus." );
        } /* fim ativa: Testar EST Set Menus */
        
        /* Testar EST Get Tabuleiro */
        else if ( strcmp( ComandoTeste , GET_TABULEIRO_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros("ii",&inxEstado,&CondRetEsperada);
            if((NumLidos != 2) || !VerificarInx(inxEstado))
            {
                return TST_CondRetParm;
            }

            CondRetObtida = EST_GetTabuleiro( vtRefEstados[inxEstado],&tabuleiro);
            return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao obter o tabuleiro." );
        } /* fim ativa: Testar EST Get Tabuleiro */
                
        /* Testar EST Set Tabuleiro */
        else if ( strcmp( ComandoTeste , SET_TABULEIRO_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros("ii",&inxEstado,&CondRetEsperada);
            if((NumLidos != 2) || !VerificarInx(inxEstado))
            {
                return TST_CondRetParm;
            }

            TAB_CriarTabuleiro(&tabuleiro,DIM_VALOR,DIM_VALOR,"tabuleiro");

            CondRetObtida = EST_SetTabuleiro( vtRefEstados[inxEstado],tabuleiro);
            return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao obter o tabuleiro." );
        } /* fim ativa: Testar EST Set Tabuleiro */
        
        return TST_CondRetNaoConhec ;  
    }

   
   /*****  Código das funções encapsuladas no módulo  *****/
   
/***********************************************************************
*
*  $FC Função: TEST -Verificar índice de estado
*
*  $FV Valor retornado
*     0 - inxEstado não vale
*     1 - inxEstado vale
*
***********************************************************************/

   int VerificarInx( int inxEstado)
   {

      if ( ( inxEstado <   0 )
        || ( inxEstado >= DIM_VT_ESTADOS ))
      {
         return 0 ;
      } /* if */

      return 1 ;

   } /* Fim função: TEST -Verificar índice de estado */
