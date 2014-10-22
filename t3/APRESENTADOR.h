


/*
Apresenta o Menu corrente
*/
void APR_ApresentaMenu(tppGrafo Menus){
    MEN_tppMenu menu = GRA_ObterCorrente(Menus);
    printf("\n#############\n#  Labirinto  #\n#############");
    printf("\n %s\n--------------",menu->nome);
    printf("Digite:\n\n");
    LIS_IrInicio(menu->opcoes);
    do
    {
        MEN_tppOpcao opcao = LIS_ObterValor(menu->opcoes);
        if(opcao!=NULL)
            printf("\n %c para %s", opcao->cmd,opcao->nome);
    }
    while(LIS_IrProxElemento(menu->opcoes)==LIS_CondRetOK);
    
}


void APR_ApresentaTabuleiro(tppGrafo Tabuleiro){

}

void APR_ApresentaSolucao(LIS_tppLista solucao){}
