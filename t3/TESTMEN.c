/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste Menu para labirinto
*
*  Arquivo gerado:              TESTMENU.c
*  Letras identificadoras:      TMEN
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\MENU.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: dan
*
*  $HA Histórico de evolução:
*     1       dan   5/out/2014 início desenvolvimento
*
***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include    "TST_ESPC.H"
#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "MENU.h"
#include    "LISTA.h"

static const char RESET_MEN_CMD         [] = "=resetteste"     ;
static const char CRIAR_MENS_CMD        [] = "=criarmens"      ;
static const char CRIAR_MEN_CMD         [] = "=criarmen"       ;
static const char CRIAR_OPC_CMD         [] = "=criaropc"       ;
static const char DESTRUIR_MEN_CMD      [] = "=destruirmen"    ;
static const char DESTRUIR_MENS_CMD     [] = "=destruirmens"   ;
static const char DESTRUIR_OPC_CMD      [] = "=destruiropc"    ;
static const char GET_MENUOPCS_CMD      [] = "=getmenuopcs"        ;
static const char GET_MENUNOME_CMD      [] = "=getmenunome"        ;
static const char GET_OPCNOME_CMD       [] = "=getopcnome"     ;
static const char CALLBACK_CMD          [] = "=call"           ;
static const char MUDAMEN_CMD           [] = "=mudamenu"       ;
static const char INICIAL_CMD           [] = "=inicial"        ;
static const char CORRENTE_CMD          [] = "=corrente"       ;


#define DIM_VT_MENUS   10
#define STR_LEN  255

MEN_tppMenus vtRefMenus[DIM_VT_MENUS] ;
LIS_tppLista stringsUsadas = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

    static int VerificarInx( int inxMenu );
    static char* newString(char str[STR_LEN]);
    MEN_tpCondRet CallBackTeste(EST_tppEstado e);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar menu
*
*  $ED Descrição da função
*
*     Comandos disponíveis:
*
*     =resetteste    inxMenu    CondRetEsp   
*     =criarmens     inxMenu    CondRetEsp
*     =criarmen      inxMenu    idMenu         nome    idPai   CondRetEsp
*     =criaropc      inxMenu    idMenu        cmd   nome CondRetEsp        
*     =destruirmens  inxMenu    CondRetEsp    
*     =destruirmen   inxMenu    idMenu        CondRetEsp  
*     =destruiropc   inxMenu    idMenu        cmd     CondRetEsp
*     =getmenuopcs   inxMenu    idMenu        CondRetEsp
*     =getmenunome   inxMenu    idMenu        CondRetEsp
*     =getopcnome    inxMenu    idMenu        cmd     CondRetEsp
*     =call          inxMenu    idMenu        cmd     CondRetEsp
*     =mudamenu      inxMenu    idMenu        CondRetEsp
*     =inicial       inxMenu    CondRetEsp    
*     =corrente      inxMenu    CondRetEsp
*
***********************************************************************/
   

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {  
      MEN_tpCondRet CondRetObtida = MEN_CondRetOK ;
      MEN_tpCondRet CondRetEsperada = MEN_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      MEN_tpCondRet CondRetTemp = MEN_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      char* opcoes = NULL;
      static int estaInicializado = 0 ;
      int i = 0;
      int ok = 0;
      int NumLidos = -1 ;
      int inxMenu = -1 ;
      int idMenu = -1;
      int idMenuEsperado = -1;
      int idPai = -1;
      char cmd = -1;
      char c = -1;
      int tam = 0;
      char nome[STR_LEN];
      char* nomeRef = NULL;

      /* Tratar: inicializar contexto */
      
      if (strcmp(ComandoTeste , RESET_MEN_CMD) == 0){

        if (estaInicializado){
            for(i = 0 ; i < DIM_VT_MENUS ; i++){ //Destroi todos menus
                MEN_DestruirMenus(vtRefMenus[i]) ;
            }
            LIS_DestruirLista(stringsUsadas);
        }
        for(i = 0 ; i < DIM_VT_MENUS ; i++) {
            vtRefMenus[ i ] = 0 ;
        }
        stringsUsadas = LIS_CriarLista(free);
        estaInicializado = 1 ;

      } /* fim ativa: Tratar: inicializar contexto */      


      /* Testar MEN Criar Menus */
         else if (strcmp(ComandoTeste , CRIAR_MENS_CMD) == 0) { 

            NumLidos = LER_LerParametros("ii", &inxMenu, &CondRetEsperada);
            if(NumLidos != 2 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_CriarMenus(vtRefMenus + inxMenu);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao criar um TAD 'Menus'.");

         } /* fim ativa: Testar MEN Criar TAD 'Menus' */


      /* Testar MEN Destruir menus */
         else if (strcmp(ComandoTeste , DESTRUIR_MENS_CMD) == 0) { 
            NumLidos = LER_LerParametros("ii", &inxMenu, &CondRetEsperada);
            if(NumLidos != 2 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_DestruirMenus(vtRefMenus[inxMenu]);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao destruir um TAD 'Menus'.");
         } /* fim ativa: Testar MEN Destruir TAD 'Menus' */


      /* Testar MEN_Criar menu */
         else if (strcmp(ComandoTeste , CRIAR_MEN_CMD) == 0) { 
            NumLidos = LER_LerParametros("iisii", &inxMenu, &idMenu, nome, &idPai, &CondRetEsperada);
            if(NumLidos != 5 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_CriarMenu(vtRefMenus[inxMenu], idMenu, newString(nome), idPai);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao criar menu.");
         } /* fim ativa: Testar MEN Criar menu */


      /* Testar MEN_Destruir menu */
         else if (strcmp(ComandoTeste , DESTRUIR_MEN_CMD) == 0) {
            NumLidos = LER_LerParametros("iii", &inxMenu, &idMenu, &CondRetEsperada);
            if(NumLidos != 3 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_DestruirMenu(vtRefMenus[inxMenu], idMenu);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao destruir menu.");
         } /* fim ativa: Testar MEN Destruir menu */


      /* Testar MEN_Criar Opção */
         else if (strcmp(ComandoTeste , CRIAR_OPC_CMD) == 0) {
            NumLidos = LER_LerParametros("iicsi", &inxMenu, &idMenu, &cmd, nome, &CondRetEsperada);
            if(NumLidos != 5 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_CriarOpcao(vtRefMenus[inxMenu], idMenu, cmd, newString(nome), CallBackTeste);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao criar opção.");
         } /* fim ativa: Testar MEN Criar Opc */


      /* Testar MEN_Destruir Opção */
         else if (strcmp(ComandoTeste , DESTRUIR_OPC_CMD) == 0) {
            NumLidos = LER_LerParametros("iici", &inxMenu, &idMenu, &cmd, &CondRetEsperada);
            if(NumLidos != 4 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_DestruirOpcao(vtRefMenus[inxMenu], idMenu, cmd);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao destruir opção.");
         } /* fim ativa: Testar MEN Destruir Opc */


      /* Testar MEN_Get Menu Opcoes */
         else if (strcmp(ComandoTeste , GET_MENUOPCS_CMD) == 0) {
            NumLidos = LER_LerParametros("iii", &inxMenu, &idMenu, &CondRetEsperada);
            if(NumLidos != 3 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_GetMenuOpcoes(vtRefMenus[inxMenu], idMenu, &opcoes, &tam);
            free(opcoes); //mantendo a memória limpa
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao obter opções.");
         } /* fim ativa: Testar MEN_Get Menu Opcoes */


      /* Testar MEN_Get Menu Nome */
         else if (strcmp(ComandoTeste , GET_MENUNOME_CMD) == 0) {
            NumLidos = LER_LerParametros("iisi", &inxMenu, &idMenu, nome, &CondRetEsperada);
            if(NumLidos != 4 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_GetMenuNome(vtRefMenus[inxMenu], idMenu, &nomeRef);

            if(CondRetEsperada != CondRetObtida) {
               return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado na obter nome do menu.");
            }
            return TST_CompararString(nome, nomeRef, "Valor obtido não é o esperado na obter nome do menu.");
         } /* fim ativa: Testar MEN_Get Menu Nome */


      /* Testar MEN Menu Inicial*/
         else if (strcmp(ComandoTeste , INICIAL_CMD) == 0) {
            NumLidos = LER_LerParametros("ii", &inxMenu, &CondRetEsperada);
            if(NumLidos != 2 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_MenuInicial(vtRefMenus[inxMenu]);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao obter menu inicial.");
         } /* fim ativa: Testar MEN_Get Menu Inicial */


      /* Testar MEN Muda Menu*/
         else if (strcmp(ComandoTeste , MUDAMEN_CMD) == 0) {
            NumLidos = LER_LerParametros("iii", &inxMenu, &idMenu, &CondRetEsperada);
            if(NumLidos != 3 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_MudaMenu(vtRefMenus[inxMenu], idMenu);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao Mudar menu corrente.");
         } /* fim ativa: Testar MEN_Get Muda Menu*/


      /* Testar MEN Menu Corrente*/
         else if (strcmp(ComandoTeste , CORRENTE_CMD) == 0) {
            NumLidos = LER_LerParametros("iiii", &inxMenu, &idMenuEsperado, &CondRetEsperada);
            if (NumLidos != 4 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_MenuCorrente(vtRefMenus[inxMenu], &idMenu);
            if (CondRetEsperada == MEN_CondRetOK && CondRetObtida == CondRetEsperada) {
               return TST_CompararInt(idMenuEsperado , idMenu , "Id do Menu Corrente esperado diferente do Obtido");
            }
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Retorno errado ao obter menu corrente.");
         } /* fim ativa: Testar MEN_Get Muda Menu*/

      

      /* Testar MEN Get Opcao Nome */
         else if (strcmp(ComandoTeste , GET_OPCNOME_CMD) == 0) {
            NumLidos = LER_LerParametros("iiisi", &inxMenu, &idMenu, &cmd, nome, &CondRetEsperada);
            if (NumLidos != 5 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }

            CondRetObtida = MEN_GetMenuOpcoes(vtRefMenus[inxMenu], idMenu, &opcoes, &tam);
            if( CondRetObtida != MEN_CondRetOK) {
               free(opcoes);
               return TST_CompararInt(MEN_CondRetOK , CondRetObtida , "Não fomos capaz de encontrar este comando");
            }
            for (ok=0, i=0; i < tam; i++) {
               if (opcoes[i] == cmd) {
                  ok = 1;
                  break;
               }
            }
            free(opcoes);
            if (!ok) {
               return TST_CompararChar(MEN_CondRetOK , -1 , "Não fomos capaz de encontrar este comando"); //Não sei que condRet por aqui;
            }
            CondRetObtida = MEN_GetOpcaoNome(vtRefMenus[inxMenu], idMenu, cmd, &nomeRef);
            if (CondRetEsperada == MEN_CondRetOK && CondRetObtida==CondRetEsperada)   {
               return TST_CompararString(nome, nomeRef, "Valor de nome encontrado diferente do esperado"); //Não sei que condRet por aqui;
            }
            return TST_CompararInt(CondRetEsperada, CondRetObtida, "Condição de retorno obtida diferente da esperada");
         } /* fim ativa: Testar MEN Get Opcao Nome*/


         /* Testar MEN CallBack*/
         else if (strcmp(ComandoTeste , CALLBACK_CMD) == 0) {
            NumLidos = LER_LerParametros("iiii", &inxMenu, &idMenu, &cmd, &CondRetEsperada);
            if (NumLidos != 4 || !VerificarInx(inxMenu)) {
               return TST_CondRetParm;
            }
            CondRetObtida = MEN_Callback(vtRefMenus[inxMenu], idMenu, cmd, NULL);
            return TST_CompararInt(CondRetEsperada , CondRetObtida , "Id do Menu Corrente esperado diferente do Obtido");
         } /* fim ativa: Testar MEN Callback*/

      return TST_CondRetNaoConhec ;  
   }
   
   /*****  Código das funções encapsuladas no módulo  *****/
   

/***********************************************************************
*
*  $FC Função: TMEN -Verificar índice de menu
*
*  $FV Valor retornado
*     0 - inxMenu não vale
*     1 - inxMenu vale
*
***********************************************************************/

   int VerificarInx(int inxMenu) {

      if ((inxMenu <   0)
        || (inxMenu >= DIM_VT_MENUS)) {
         return 0 ;
      } /* if */

      return 1 ;

   } /* Fim função: TMEN -Verificar índice de menu */

/***********************************************************************
*
*  $FC Função: TMEN -Cria uma string na heap baseado em outra string, registra numa lista pra destruição à posteriori
*
*  $FV Valor retornado
*     ponteiro pra nova string
*
***********************************************************************/

   static char* newString(char str[STR_LEN]) {
      int len = strlen(str)+1;
      char *s = calloc(len, sizeof(char));
      memcpy (s, str, len);
      LIS_InserirElementoApos(stringsUsadas, s);
      return s;
   } /* Fim função: TMEN -Verificar índice de menu */

/***********************************************************************
*
*  $FC Função: TMEN -Verificar índice de menu
*
*  $FV Valor retornado
*     0 - inxMenu não vale
*     1 - inxMenu vale
*
***********************************************************************/

   MEN_tpCondRet CallBackTeste(EST_tppEstado e) {
      MEN_CondRetOK;
   }


/********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/


//********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/
#undef STR_LEN
#undef DIM_VT_MENUS