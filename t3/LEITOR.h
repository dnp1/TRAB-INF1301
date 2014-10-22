/* 
mudar de lis->gra
*/
LEI_CondRet LEI_LeCmd(tppEstado e){
    char c; 
    scanf(" %c ",&c);
    MEN_tppMenu m = GRA_ObterCorrente(e->Menu);
    LIS_IrInicio(menu->opcoes);
    do
    {
        MEN_tppOpcao opcao = LIS_ObterValor(menu->opcoes);
        if(opc->cmd == c){
            opc->callback();
            return LEI_CondRetOK;
        }    
    }
    while(LIS_IrProxElemento(menu->opcoes)==LIS_CondRetOK);
  
    return LEI_CondRetSemOpcao;         
}

/*
valida retorna apenas LEI_CondRetOK ou LEI_CondRetInvalido

*/

/*
trunca em 50
*/
LEI_CondRet LEI_LeString(char* dst, valida){
    char temp[50];
    scanf(" %s ",temp);
    LEI_CondRet cr = valida(temp);
    if(cr == LEI_CondRetOK){
        strcpy(dst,temp);
    }
    return cr;    
}
LEI_CondREt LEI_LeInt(int* dst, valida){
    int temp;
    scanf(" %d ",&temp);
    LEI_CondRet cr = valida(temp);
    if(cr == LEI_CondRetOK){
        *dst = temp;
    }
    return cr;    
}
