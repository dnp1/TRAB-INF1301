#if ! defined ( MENU_ )
#define MENU_

/***************************************************************************
*
*  $MCD Módulo de definição: MEN Menus
*
*  Arquivo gerado:              MENU.h
*  Letras identificadoras:      MEN
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Menu.BSW
*
*  Projeto: INF 1301 / Labirinto
*  Gestor:  LSKDANEAV
*  Autores: lsk
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		 1	   lsk	 20/10/2014		//
*
*  $ED Descrição do módulo
*       Cria um grafo de menus para serem utilizados com o modulo Estado. 
*       Apesar disso, isto é apenas uma sugestão, pois o módulo poderia ser genérico, bastando mudar o EST_tppEstado para void**.
*       Caso esteja usando em uma aplicação de jogo, é recomendável a não criação de um menu com id 0, pois convencionamos o mesmo como fim de jogo.
*       É implementado com um grafo não direcionado e Listas duplamente encadeadas.
*       É recomendado o seu uso como árvore, porém funciona com ciclos.
*       É obrigatória a criação do menu com id 1.
*       Os ids de menus devem ser únicos para um grafo.
*       Os cmds identificadores das opções devem ser únicas em cada menu.
*       (Podem haver dois comandos iguais em menus diferentes, em um mesmo grafo)
***************************************************************************/
#if defined( MENU_OWN )
    #define MENU_EXT
#else
    #define MENU_EXT extern
#endif
#include "GRAFO.h"
#include "TIPOESTADO.h"

/* Tipo referência para um grafo de Menus */
typedef struct Menus_ * MEN_tppMenus;

/***********************************************************************
*
*  $TC Tipo de dados: MEN Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum{

    MEN_CondRetOK,
    /* Concluiu corretamente */
    MEN_CondRetFaltouMemoria,
    /* Faltou Memoria */
    MEN_CondRetComandoInvalido
    /* O comando é invalido */


} MEN_tpCondRet;


/***********************************************************************
*
*  $FC Função: MEN  &Criar Menus
*
*  $ED Descrição da função
*     Cria um grafo de Menus para aplicações, implementado com um grafo genérico.
*     Os Menus são implementados com um grafo de tipo homogêneo 
*     genérico não direcionado sem peso nas arestas. 
*     O menu inicial tem id 1;
*     O menu representando fim de jogo tem id 0;
*  $EP Parâmetros
*     m - endereço de um ponteiro para um grafo de menus
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
* Assertiva de entrada: É recomendável m nulo, para evitar memory leak
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem, id do corrente de m = 0 
***********************************************************************/
MEN_tpCondRet MEN_CriarMenus(MEN_tppMenus* m);
/***********************************************************************
*
*  $FC Função: MEN  &Criar Menu
*
*  $ED Descrição da função
*     Cria um Menu e o insere em um grafo de Menus
*     O menu contém:
*       um id, que deve ser único.
*       um nome.
*       um id do menu pai, pois todo menu tem por padrão um comando de voltar para o menu acima.
*       uma lista de opcoes, que devem ser populadas por MEN_CriarOpcao
*  $EP Parâmetros
*       m - ponteiro para grafo de menus
*       id - identificador único
*       nome - string alocada externamente ou constante 
*       id - identificador do pai deste menu, usado pela opção voltar sempre presente.
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, id é unico
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem
***********************************************************************/
MEN_tpCondRet MEN_CriarMenu(MEN_tppMenus m, int id, char* nome,int idPai);
/***********************************************************************
*
*  $FC Função: MEN  &Destruir Menus
*
*  $ED Descrição da função
*     Destroi o grafo e a estrutura de m, liberando sua memoria.
*  $EP Parâmetros
*     m - MEN_tppMenus a ser destruido
*  $FV Valor retornado
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem
* Assertiva de saida:  m é nulo 
***********************************************************************/
MEN_tpCondRet MEN_DestruirMenus(MEN_tppMenus m);
/***********************************************************************
*
*  $FC Função: MEN  &Destruir Menu
*
*  $ED Descrição da função
*     Destroi o menu de id 'id' em m
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - identificador do menu em m, unico para m 
*
*  $FV Valor retornado
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, id é unico
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem
***********************************************************************/
MEN_tpCondRet MEN_DestruirMenu(MEN_tppMenus m, int id);
/***********************************************************************
*
*  $FC Função: MEN  &Destruir Opcao
*
*  $ED Descrição da função
*     Destroi a Opcao representando o cmd 'cmd', no menu de id 'id' em m. 
*     Não libera a memória do nome associado nome.
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - identificador do menu em m, unico para m 
*     cmd - identificador da opcao de id em m, unica para id 
*
*  $FV Valor retornado
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, id é unico para m, cmd é unico para (id,m)
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem
***********************************************************************/
MEN_tpCondRet MEN_DestruirOpcao(MEN_tppMenus m, int id, char cmd);
/***********************************************************************
*
*  $FC Função: MEN  &Criar Opcao
*
*  $ED Descrição da função
*     Destroi o menu de id 'id' em m
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - identificador do menu em m, unico para m 
*     cmd - identificador da opcao de id em m, unica para id 
*     nome - ponteiro para o nome da opcao, deve ser alocado e liberado externamente
*     callback - endereço para uma callback que sera chamada quando o usuario digitar cmd no menu de id id
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar a opcao
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, id é unico para m, cmd é unico para (id,m), callback != null
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem
***********************************************************************/
MEN_tpCondRet MEN_CriarOpcao(MEN_tppMenus menus, int idMenu,char cmd, char* nome,MEN_tpCondRet (*callback)(EST_tppEstado e));
/***********************************************************************
*
*  $FC Função: MEN  &Get Menu Opcoes
*
*  $ED Descrição da função
*     Destroi o menu de id 'id' em m
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - identificador do menu em m, unico para m 
*     l - vetor de caracteres representando os comandos identificadores das opcoes. l tem tamanho tam.
*     tam - endereço para int, onde sera armazenado o numero de opcoes no menu requisitado
*  $FV Valor retornado
*     MEN_CondRetFaltouMemoria - faltou memoria ao criar os Menus
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, id é unico para m, l = null para evitar memory leak
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem, tam>=0, num de elementos em l = tam
***********************************************************************/
MEN_tpCondRet MEN_GetMenuOpcoes(MEN_tppMenus m,int id,char** l,int* tam); 
/***********************************************************************
*
*  $FC Função: MEN  &Get Menu Nome
*
*  $ED Descrição da função
*     Destroi o menu de id 'id' em m
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - identificador do menu em m, unico para m 
*     nome - ponteiro para um vetor de caracteres(string). 
*  $FV Valor retornado
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, id é unico para m, nome=null para evitar memory leak
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem 
***********************************************************************/
MEN_tpCondRet MEN_GetMenuNome(MEN_tppMenus m,int id, char** nome);
/***********************************************************************
*
*  $FC Função: MEN  &Get Opcao Nome
*
*  $ED Descrição da função
*     Destroi o menu de id 'id' em m
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - identificador do menu em m, unico para m 
*     cmd - identificador da opcao de id em m, unica para id 
*     nome - ponteiro para um vetor de caracteres(string). 
*  $FV Valor retornado
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, id é unico para m, cmd é unico para (id,m), nome=null, para evitar memory leak
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem, id do corrente de m = id
***********************************************************************/
MEN_tpCondRet MEN_GetOpcaoNome(MEN_tppMenus m, int id, char cmd, char** nome);
/***********************************************************************
*
*  $FC Função: MEN  &Callback
*
*  $ED Descrição da função
*     Chama a Callback associada à opção correspondente à cmd, no menu de id id, em m.
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - identificador do menu em m, unico para m 
*     cmd - identificador da opcao de id em m, unica para id 
*     e - um ponteiro para o estado global. 
*         As funções de callback tem efeito pratico modificando esse estado.
*  $FV Valor retornado
*     O retorno da callback:
*       como a callback é definida externamente, a semântica dos retornos pode variar, mas como sugestão:
*       
*       MEN_CondRetFaltouMemoria - Faltou memoria para executar a operação
*       MEN_CondRetComandoInvalido - A operação foi mal sucedida
*
* Assertiva de entrada: m e não é nulo e as assertivas estruturais valem, id é unico para m, cmd é unico para (id,m). se e nao for nulo, suas assertivas estruturais valem.
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem, id do corrente de m = id
***********************************************************************/
MEN_tpCondRet MEN_Callback(MEN_tppMenus m, int id, char cmd, EST_tppEstado e);
/***********************************************************************
*
*  $FC Função: MEN  &Menu Inicial 
*
*  $ED Descrição da função
*   Muda o corrente de m para o menu inicial, por convenção =  1
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*
*  $FV Valor retornado
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, foi criado um menu com id = 1
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem, id do corrente de m = 1
***********************************************************************/
MEN_tpCondRet MEN_MenuInicial(MEN_tppMenus m);
/***********************************************************************
*
*  $FC Função: MEN  &Menu Corrente
*
*  $ED Descrição da função
*     Retorna, por referência, o id do menu corrente 
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - o ponteiro para a area de memória aonde o id será armazenado
*  $FV Valor retornado
*
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem, *id = id do corrente de m 
*
***********************************************************************/
MEN_tpCondRet MEN_MenuCorrente(MEN_tppMenus m, int* id);
/***********************************************************************
*
*  $FC Função: MEN  &Muda Menu
*
*  $ED Descrição da função
*     Muda o menu corrente de m para o menu de id id
*
*  $EP Parâmetros
*     m - ponteiro para grafo de menus 
*     id - id do menu destino
*  $FV Valor retornado
*   
* Assertiva de entrada: m não é nulo e as assertivas estruturais valem, existe um menu com id id
* Assertiva de saida:  m não é nulo e as assertivas estruturais valem, id do corrente de m = id
*
***********************************************************************/
MEN_tpCondRet MEN_MudaMenu(MEN_tppMenus m,int id);
#endif
