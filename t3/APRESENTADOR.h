


/*
Apresenta o Menu corrente
*/
void APR_ApresentaMenu(tppGrafo Menus){
    MEN_tpMenu* menu = GRA_ObterCorrente(Menus);
    printf("\n#############\n#  Labirinto  #\n#############");
    printf("\n %s\n--------------",menu->nome);
    printf("Digite:\n\n");
    LIS_IrInicio(menu->opcoes);
    do
    {
        MEN_tpOpcao* opcao = LIS_ObterValor(menu->opcoes);
        if(opcao!=NULL)
            printf("\n %c para %s", opcao->cmd,opcao->nome);
    }
    while(LIS_IrProxElemento(menu->opcoes)==LIS_CondRetOK);
    
}
void Erro(int CondRet){
    switch(CondRet){
        case PRI_CondRetOK: 
            printf("Sucesso");
        break;
        case PRI_FaltouMemoria:
            printf("Operacao mal sucedida. Faltou Memoria.");
        break;    
    }
}

void APR_ApresentaTabuleiro(tppGrafo Tabuleiro){

}
