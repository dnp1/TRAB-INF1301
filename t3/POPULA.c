

#define vaimenu(_x) void vaiMenu##_x(tppEstado e){ \
                        UltimoMenu = _x; \
                        GRA_IrVizinho(e->Menus,_x); \
                    }
vaimenu(1)
vaimenu(2)
vaimenu(3)
vaimenu(4)


void carrega(){
    e->Tabuleiro = TAB_CriarTabuleiro();
    
}
void volta_tab(tppEstado e){
    GRA_ExcluirGrafo(e->Tabuleiro);
    GRA_IrVizinhoCorrente(e->Menu,e->UltimoMenu);
}
void volta(tppEstado e){
    GRA_IrVizinhoCorrente(e->Menu,e->UltimoMenu);
}
LEI_tpCondRet validastring(char* s){
    if(strlen(s)<10 && !strcmp(s,""))
        return LEI_CondRetOk;
    else
        return LEI_CondRetInvalido;
}
LEI_tpCondRet validaint(int n){
    if(n>0 && n<11) 
        return LEI_CondRetOk;
    else 
        return LEI_CondRetInvalido;
}
void novo_tab(){
    char* nome[10] = "";
    int alt = 0;
    int lar = 0;
    while(!strcmp(nome,""))
        Erro("Digite o nome (menos de 10 caracteres)",LEI_LeString(nome,validastring));
    while(alt == 0)
        Erro("Digite a altura (1..10)",LEI_LeInt(&alt,validaint));
    while(lar == 0)
        Erro("Digite a largura (1.10)",LEI_LeInt(&lar,validaint));
    tpptab a;
    Erro("Criando tabuleiro",TAB_CriaTab(a,nome, alt,lar));
    Erro("Salvando tabuleiro",TAB_salvaTab(a));
}
void PopulaMenu1(tppEstado e){
    Erro("criando menu inicio", MEN_CriarMenu(e->Menus,1,"inicio",volta));
      
    Erro("criando opcao 1 de inicio", MEN_CriarOpcao(e->Menus,1,'1',"Criar Mapa",vaiMenu2) ;
    Erro("criando opcao 2 de inicio", MEN_CriarOpcao(e->Menus,1,'2',"Jogar",vaiMenu3);
}
void PopulaMenus(tppEstado e){
    PopulaMenu1(e);
    //PopulaMenu2(e);
   
}
