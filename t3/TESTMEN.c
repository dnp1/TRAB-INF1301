/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste Tabuleiro para labirinto
*
*  Arquivo gerado:              TESTTAB.c
*  Letras identificadoras:      TTAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: eav
*
*  $HA Histórico de evolução:
*     1       eav   29/out/2014 início desenvolvimento
*
***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "TABULEIRO.h"
#include    "LISTA.h"

static const char RESET_MEN_CMD         [] = "=resetteste"      ;
static const char CRIAR_MENS_CMD        [] = "=criarmens"        ;
static const char CRIAR_MEN_CMD         [] = "=criarmen"        ;
static const char CRIAR_OPC_CMD         [] = "=criaropc"        ;
static const char DESTRUIR_MEN_CMD      [] = "=destruirmen"     ;
static const char DESTRUIR_MENS_CMD     [] = "=destruirmens"     ;
static const char GET_MENU_CMD          [] = "=getmenu"      ;
static const char GET_MENUOPC_CMD       [] = "=getopc"  ;
static const char GET_MENUNOME_CMD      [] = "=getnome"  ;
static const char GET_OPCCMD_CMD        [] = "=getcmd"   ;
static const char GET_OPCNOME_CMD       [] = "=getnomeopc"   ;
static const char CALLBACK_CMD          [] = "=call"   ;
static const char MUDAMEN_CMD           [] = "=mudamenu"   ;
static const char INICIAL_CMD           [] = "=inicial"   ;
static const char CORRENTE_CMD          [] = "=corrente"   ;
static const char MUDA_ULTIMO_CMD       [] = "=mudaultimo"   ;

int estaInicializado = 0 ;

#define DIM_VT_TABULEIROS   10

TAB_tppTabuleiro vtRefTabuleiros[ DIM_VT_TABULEIROS ] ;


/***** Protótipos das funções encapuladas no módulo *****/
   
    static MEN_tpCondRet F(EST_tppEstado e, Men_tppOpcao o);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar tabuleiro
*
*  $ED Descrição da função
*
*     Comandos disponíveis:
*
*     =resetteste      
*     =criarmens       
*     =criaropc        
*     =destruirmens     
*     =destruirmen     
*     =getmenu      
*     =getopc  
*     =getnome  
*     =getcmd   
*     =getnomeopc   
*     =call   
*     =mudamenu   
*     =inicial
*     =corrente
*     =mudaultimo   
*
***********************************************************************/

MEN_tpCondRet F(EST_tppEstado e, Men_tppOpcao o){
    return CondRetOK;
}

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {  
      TAB_tpCondRet CondRetObtida = TAB_CondRetOK ;
      TAB_tpCondRet CondRetEsperada = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      TAB_tpCondRet CondRetTemp = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      int i ;
      int NumLidos = -1 ;
      int inxTabuleiro = -1 ;

      /* Tratar: inicializar contexto */
      
      if ( strcmp( ComandoTeste , RESET_MEN_CMD ) == 0 ){

        if ( estaInicializado ){
            for( i = 0 ; i < DIM_VT_TABULEIROS ; i++ ){
                TAB_DestruirTabuleiro( ( vtRefTabuleiros[ i ] )) ;
            }
        }

        for( i = 0 ; i < DIM_VT_TABULEIROS ; i++ ){
            vtRefTabuleiros[ i ] = 0 ;
        }

      estaInicializado = 1 ;

      } /* fim ativa: Tratar: inicializar contexto */
      
      /* Testar TAB Criar tabuleiro */
            
      else if ( strcmp( ComandoTeste , CRIAR_MEN_CMD ) == 0 )
      {
          int altura, largura;
          char* nome;

          NumLidos = LER_LerParametros("iiisi",&inxTabuleiro,&altura,&largura,&nome,&CondRetEsperada);
          if((NumLidos != 5) || !VerificarInx(inxTabuleiro))
          {
              return TST_CondRetParm;
          }

          CondRetObtida = TAB_CriarTabuleiro( &vtRefTabuleiros[inxTabuleiro],altura,largura,nome);
          return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao criar tabuleiro." );
      } /* fim ativa: Testar TAB Criar tabuleiro */
            
      /* Testar TAB Destruir tabuleiro */
        
      else if ( strcmp( ComandoTeste , DESTRUIR_TAB_CMD ) == 0 )
      {
          NumLidos = LER_LerParametros("ii",&inxTabuleiro,&CondRetEsperada);
          if((NumLidos != 2) || !VerificarInx(inxTabuleiro))
          {
              return TST_CondRetParm;
          }

          CondRetObtida = TAB_DestruirTabuleiro( vtRefTabuleiros[inxTabuleiro]);
          return TST_CompararInt( CondRetEsperada , CondRetObtida , "Retorno errado ao destruir tabuleiro." );
      } /* fim ativa: Testar TAB Destruir tabuleiro */
      
      /* Testar TAB Pode ir cima */
            
      else if ( strcmp( ComandoTeste , PODE_IR_CIMA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Pode ir cima */

      /* Testar TAB Pode ir esquerda */
        
      else if ( strcmp( ComandoTeste , PODE_IR_ESQUERDA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Pode ir esquerda */
            
      /* Testar TAB Pode ir baixo */
            
      else if ( strcmp( ComandoTeste , PODE_IR_BAIXO_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Pode ir baixo */
            
      /* Testar TAB Pode ir direita */
            
      else if ( strcmp( ComandoTeste , PODE_IR_DIREITA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Pode ir direita */
      
      /* Testar TAB Andar pra cima */
            
      else if ( strcmp( ComandoTeste , ANDAR_CIMA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Andar pra cima */     
       
      /* Testar TAB Andar pra esquerda */
            
      else if ( strcmp( ComandoTeste , ANDAR_ESQUERDA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Andar pra esquerda */
            
      /* Testar TAB Andar pra baixo */
            
      else if ( strcmp( ComandoTeste , ANDAR_BAIXO_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Andar pra baixo */      
      
      /* Testar TAB Andar pra direita */
            
      else if ( strcmp( ComandoTeste , ANDAR_DIREITA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Andar pra direita */
      
      /* Testar TAB Poe chao */
            
      else if ( strcmp( ComandoTeste , POE_CHAO_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Poe chao */   
         
      /* Testar TAB Poe parede */
            
      else if ( strcmp( ComandoTeste , POE_PAREDE_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Poe parede */      
      
      /* Testar TAB Poe inicio */
        
      else if ( strcmp( ComandoTeste , POE_INICIO_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Poe inicio */      
      
      /* Testar TAB Poe fim */
        
      else if ( strcmp( ComandoTeste , POE_FIM_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Poe fim */      
      
      /* Testar TAB Get tipo casa */
            
      else if ( strcmp( ComandoTeste , GET_TIPO_CASA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Get tipo casa */      
      
      /* Testar TAB Get altura */
            
      else if ( strcmp( ComandoTeste , GET_ALTURA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Get altura */      
      
      /* Testar TAB Get largura */
            
      else if ( strcmp( ComandoTeste , GET_LARGURA_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Get largura */  
             
      /* Testar TAB Posicao do jogador */
            
      else if ( strcmp( ComandoTeste , POSICAO_JOGADOR_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Posicao do jogador */      
      
      /* Testar TAB Validar Tabuleiro */
            
      else if ( strcmp( ComandoTeste , VALIDAR_TAB_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Validar Tabuleiro */      
      
      /* Testar TAB Salvar Tabuleiro */
            
      else if ( strcmp( ComandoTeste , SALVAR_TAB_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Salvar Tabuleiro */      
      
      /* Testar TAB Carregar Tabuleiro */
            
      else if ( strcmp( ComandoTeste , CARREGAR_TAB_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Carregar Tabuleiro */      
      
      /* Testar TAB Solucionar Tabuleiro */
            
      else if ( strcmp( ComandoTeste , SOLUCIONAR_TAB_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Solucionar Tabuleiro */      
      
      return TST_CondRetNaoConhec ;  
   }
   
   /*****  Código das funções encapsuladas no módulo  *****/
   

/***********************************************************************
*
*  $FC Função: TTAB -Verificar índice de tabuleiro
*
*  $FV Valor retornado
*     0 - inxTabuleiro não vale
*     1 - inxTabuleiro vale
*
***********************************************************************/

   int VerificarInx( int inxTabuleiro )
   {

      if ( ( inxTabuleiro <   0 )
        || ( inxTabuleiro >= DIM_VT_TABULEIROS ))
      {
         return 0 ;
      } /* if */

      return 1 ;

   } /* Fim função: TTAB -Verificar índice de tabuleiro */

/********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/


//********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/
