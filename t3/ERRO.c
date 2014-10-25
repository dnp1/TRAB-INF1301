

enum modules{
    PRI,
    LEI,
    TAB
}
void TrataPRI(int CondRet){
    switch(CondRet){
        case PRI_FaltouMemoria:
            printf("Operacao mal sucedida. Faltou Memoria.");
        break;   
        printf("Comando invalido"); 
    }
}
void Erro(char* comm, int CondRet,int module){
    printf("%s",comm);
    if(CondRet == 0)//OK
    {
            printf("OK");
    }
    else
    {    
        switch (module){
            case PRI:
                trataPRI(CondRet);
                break;
            case TAB:
                trataTAB(CondRet);
                break;
            case LEI:
                trataLEI(CondRet);
                break;
        }
    }
}

