
/*
   ids dos Menus devem ser unicos e maiores que 1.
   A navegação sempre começa no Menu de id 1, ao menos este deve existir.
   
*/
typedef enum{
    MEN_CondRetFaltouMemoria,
    MEN_CondRetOK
}
typedef Menu* MEN_tppMenu;
typedef Opcao* MEN_tppOpcao; 

void MEN_DestruirMenu(MEN_tppMenu menu);

MEN_CondRet MEN_CriarMenu(tppGrafo menus, int id, char* nome);

MEN_CondRet MEN_CriarOpcao(tppGrafo menus, int idMenu,char cmd, char* nome,callback);


