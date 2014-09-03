/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTARV.C
*  Letras identificadoras:      TARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este mÇodulo contém as funções específicas para o teste do
*     módulo árvore. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     =criar        - chama a função ARV_CriarArvore( )
*     =insdir <Char>
*                   - chama a função ARV_InserirDireita( <Char> )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     "=insesq" <Char>
*                   - chama a função ARV_InserirEsquerda( <Char> )
*     "=irpai"      - chama a função ARV_IrPai( )
*     "=iresq"      - chama a função ARV_IrEsquerda( )
*     "=irdir"      - chama a função ARV_IrDireita( )
*     "=obter" <Char>
*                   - chama a função ARV_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a função ARV_DestruirArvore( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "ARVORE.H"
#include    "LISTA.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_ARV_CMD       "=criar"
#define     INS_DIR_CMD         "=insdir"
#define     INS_ESQ_CMD         "=insesq"
#define     IR_PAI_CMD          "=irpai"
#define     IR_ESQ_CMD          "=iresq"
#define     IR_DIR_CMD          "=irdir"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

#define NUM_ARVORES 12
#define TAM_STR_TESTE 255


// Inicia arvores locais como NULL
static ARV_tppArvore arvores[NUM_ARVORES] = {
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL // Deselegante mas prático.
};


// Função auxiliar que cria uma lista de caracteres a partir de um vetor de caracteres terminado com '\0'
   static void preencheListaComString(LIS_tppLista lista, char* str) {
      for (str; *str; str++) {
         LIS_InserirElementoApos(lista, *str);
         LIS_AvancarElementoCorrente(lista, 1);
      }
   }

   static TST_tpCondRet comparaListaComString(LIS_tppLista lista, char* str) {
      if(lista != NULL) {
         IrInicioLista(lista);

         for (str; *str; str++) {
            if (LIS_ObterValor(lista) != *str) {
               return TST_CondRetErro;
            }
            LIS_AvancarElementoCorrente(lista, 1);
         }
      }
      return (*str == '\0') ? TST_CondRetOK : TST_CondRetErro; //Se nulo, string acabou e é igual. Se não é diferente.
   }

   static TST_tpCondRet preencheStringComLista(LIS_tppLista lista, char* str) {
      if(lista == NULL) {
         str[0]='\0';
         return TST_CondRetOK;
      }
      IrInicioLista(lista);
      do {
         *str = LIS_ObterValor(lista);
         str++;
      }while (LIS_AvancarElementoCorrente(lista,1) != LIS_CondRetFimLista);
      *str = '\0';
      return TST_CondRetOK;
   }
   

// Seta arvore ok como nula

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
      char str[TAM_STR_TESTE]; //Vetor de Caracteres temporário utilizado para ler outros
      char str_[TAM_STR_TESTE]; //Vetor de Caracteres temporário utilizado para ler outros

      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;
      ARV_tpCondRet CondRetEsperada = ARV_CondRetFaltouMemoria ;

      int arvindex = -1;

      //char ValorEsperado = '?'  ;
      //char ValorObtido   = '!'  ;
      LIS_tppLista ListaObtida = NULL;
      LIS_tppLista ListaDada = NULL;
      //char ValorDado     = '\0' ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar ARV Criar árvore */

         if ( strcmp( ComandoTeste , CRIAR_ARV_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &arvindex, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_CriarArvore( (arvores+arvindex) ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar ARV Criar árvore */

      /* Testar ARV Adicionar filho à direita */

         else if ( strcmp( ComandoTeste , INS_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &arvindex, str , &CondRetEsperada ) ;
            
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            ListaDada = LIS_CriarLista( );
            preencheListaComString(ListaDada, str);
            

            CondRetObtido = ARV_InserirDireita( arvores[arvindex], ListaDada ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir àa direita." );

         } /* fim ativa: Testar ARV Adicionar filho à direita */

      /* Testar ARV Adicionar filho à esquerda */

         else if ( strcmp( ComandoTeste , INS_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &arvindex,  &str , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm;
            } /* if */

            ListaDada = LIS_CriarLista( );
            preencheListaComString(ListaDada, str);
            
            CondRetObtido = ARV_InserirEsquerda( arvores[arvindex], ListaDada ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir à esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho à esquerda */

      /* Testar ARV Ir para nó pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                              &arvindex, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( arvores[arvindex] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para nó pai */

      /* Testar ARV Ir para nó à esquerda */

         else if ( strcmp( ComandoTeste , IR_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                              &arvindex, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoEsquerda( arvores[arvindex] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para nó à esquerda */

      /* Testar ARV Ir para nó à direita */

         else if ( strcmp( ComandoTeste , IR_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                              &arvindex,  &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoDireita( arvores[arvindex] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para nó à direita */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                              &arvindex,
                              &str,
                              &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_ObterValorCorr( arvores[arvindex], &ListaObtida ) ;
            
            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK || CondRetObtido != ARV_CondRetOK ) // RET != 0
            {
               return Ret;
            } /* if */

			   Ret = comparaListaComString( ListaObtida , str );
            preencheStringComLista(ListaObtida, str_);

            return TST_CompararString( str , str_ ,
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir árvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" ,
                              &arvindex ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
               
            ARV_DestruirArvore( (arvores+arvindex) ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Destruir árvore */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TARV Efetuar operações de teste específicas para árvore */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

