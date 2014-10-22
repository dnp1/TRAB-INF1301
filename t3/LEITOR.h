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
LEI_CondRet LEI_LeString(char* dst){
    scanf(" %s ",dst);    
}
LEI_CondREt LEI_LeInt(int* dst, int min, int max){
    scanf(" %d ",dst);
    if(*dst < min||*dst > max) return LEI_CondRetForaLimite;
    else return LEI_CondRetOK;
}
