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

static const char RESET_TAB_CMD         [] = "=resetteste"      ;
static const char CRIAR_TAB_CMD         [] = "=criartab"        ;
static const char DESTRUIR_TAB_CMD      [] = "=destruirtab"     ;
static const char PODE_IR_CIMA_CMD      [] = "=podeircima"      ;
static const char PODE_IR_ESQUERDA_CMD  [] = "=podeiresquerda"  ;
static const char PODE_IR_BAIXO_CMD     [] = "=podeirdireita"   ;
static const char PODE_IR_DIREITA_CMD   [] = "=podeirbaixo"     ;
static const char ANDAR_CIMA_CMD        [] = "=andarcima"       ;
static const char ANDAR_ESQUERDA_CMD    [] = "=andaresquerda"   ;
static const char ANDAR_BAIXO_CMD       [] = "=andarbaixo"      ;
static const char ANDAR_DIREITA_CMD     [] = "=andardireita"    ;  
static const char POE_CHAO_CMD          [] = "=poechao"         ;  
static const char POE_PAREDE_CMD        [] = "=poeparede"       ;  
static const char POE_INICIO_CMD        [] = "=poeinicio"       ;  
static const char POE_FIM_CMD           [] = "=poefim"          ;
static const char GET_TIPO_CASA_CMD     [] = "=gettipocasa"     ;
static const char GET_ALTURA_CMD        [] = "=getaltura"       ;
static const char GET_LARGURA_CMD       [] = "=getlargura"      ;
static const char POSICAO_JOGADOR_CMD   [] = "=posicaojogador"  ;
static const char VALIDAR_TAB_CMD       [] = "=validartab"      ;
static const char SALVAR_TAB_CMD        [] = "=salvartab"       ;
static const char CARREGAR_TAB_CMD      [] = "=carregartab"     ;
static const char SOLUCIONAR_TAB_CMD    [] = "=solucionartab"   ;


/***** Protótipos das funções encapuladas no módulo *****/


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar tabuleiro
*
*  $ED Descrição da função
*     Podem ser criadas até 10 tabuleiros, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de grafos Provoca vazamento de memória
*     =criartab               inxTab   altura    largura   CondRetEsp
*     =destruirtab            inxTab   CondRetEsp
*     =podeircima"            inxTab   CondRetEsp
*     =podeiresquerda"        inxTab   CondRetEsp
*     =podeirdireita"         inxTab   CondRetEsp  
*     =podeirbaixo"           inxTab   CondRetEsp
*     =andarcima"             inxTab   CondRetEsp
*     =andaresquerda"         inxTab   CondRetEsp 
*     =andarbaixo"            inxTab   CondRetEsp
*     =andardireita"          inxTab   CondRetEsp
*     =poechao"               inxTab   CondRetEsp
*     =poeparede"             inxTab   CondRetEsp
*     =poeinicio"             inxTab   CondRetEsp
*     =poefim"                inxTab   CondRetEsp
*     =gettipocasa"           inxTab   x y   tipoEsp    CondRetEsp
*     =getaltura"             inxTab   alturaEsp        CondRetEsp       
*     =getlargura"            inxTab   alturaEsp        CondRetEsp
*     =posicaojogador"        inxTab   xEsp    yEsp     CondRetEsp
*     =validartab"            inxTab   condRetEsp
*     =salvartab"             inxTab   condRetEsp
*     =carregartab"           inxTab   condRetEsp
*     =solucionartab"         inxTab   condRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {   
      TAB_tpCondRet CondRetObtida   = TAB_CondRetOK ;
      TAB_tpCondRet CondRetEsperada = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      TAB_tpCondRet CondRetTemp = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
                                      
      /* Tratar: inicializar contexto */

      /* fim ativa: Tratar: inicializar contexto */
      
      /* Testar TAB Criar tabuleiro */
            
      else if ( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
      {
      
      } /* fim ativa: Testar TAB Criar tabuleiro */
            
      /* Testar TAB Destruir tabuleiro */
        
      else if ( strcmp( ComandoTeste , DESTRUIR_TAB_CMD ) == 0 )
      {
      
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
            
      else if ( strcmp( ComandoTeste , VALIDA_TAB_CMD ) == 0 )
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


/********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/
