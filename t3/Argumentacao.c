
int main(){
    //AE: ??? 
    EST_tppEstado e = EST_CriaEstado();
    //AI1: Estado existe e valem suas assertivas estruturais
    Erro("Alocando Estado:",(e!=NULL?PRI_CondRetOK:PRI_CondRetFaltouMemoria),PRI);
    //AI2: Mensagem da situacao apresentada para o usuário
    if(e!=NULL){
        if(PopulaMenus(e)!=PRI_CondRetOK){
            return 0;
            //AI3: Programa terminado sem vazamento de memória
        }    
        //AI4: Menus populados e valem as assertivas estruturais do menu ou programa terminado, caso tenha faltado memória
    }
    else{
        return 0;
        //AI5: Programa terminado sem vazamento de memória
    }
    /*
    AI6: 
        Caso tenha memória:
            Estado existe e Menus populados e suas assertivas estruturais valem 
        Caso não tenha memória:    
            Programa terminado sem vazamento de memória 
    */
    EST_MenuInicial(e);
    //AI7: O Menu corrente é menu inicial, que é diferente de jogo e editor
    while(EST_MenuCorrente()!=0){
        ApresentaMenu(e);
        //AI8: O menu corrente e suas opções são apresentadas para o usuário
        int atual = EST_MenuCorrente();
        //AI9: atual tem o id do Menu corrente, se atual for correspondente ao editor ou ao jogo, existe um tabuleiro apontado pelo estado 
        if(atual == EDITOR||atual == JOGO){
            ApresentaTabuleiro(e);
            //AI10: A situação do tabuleiro foi apresentada para o usuário
        }
        /*
        AI11: 
            Caso o menu corrente seja o do editor ou do jogo:
                A situação do tabuleiro foi apresentada para o usuário 
            Caso contrário:
                O tabuleiro não foi apresentado para o usuário
        */
        Erro("Digite um comando:",LeCmd(e),PRI);
        //AI12: O comando que o usuário forneceu foi avaliado e o usuário recebeu uma resposta apropriada. Se o comando for de sair, o menu corrente do estado vira 0.
    }
    //AI13: O usuário optou por sair do programa
    EST_ExcluirEstado();
    //AI14: A memória foi limpa
    return 0;
    //AS: Programa terminado sem vazamento de memória
}

/*
Primeira seleção:

    //AE: Mensagem da situacao apresentada para o usuário
    if(e!=NULL){
        //bloco A
        //AI4: Menus populados e valem as assertivas estruturais do menu ou programa terminado, caso tenha faltado memória
    }
    else{
        //bloco B
        //AI5: Programa terminado sem vazamento de memória
    }
    
    AS: 
        Caso tenha memória:
            Estado existe e Menus populados e suas assertivas estruturais valem 
        Caso não tenha memória:    
            Programa terminado sem vazamento de memória 
    
    1. AE e Cond = V + bloco A -> AS
        Pela AE uma mensagem da situação foi apresentada para o usuário e como condição é verdadeira, o estado não é nulo.
        Portanto, o bloco A é executado e vale AI4, valendo assim a AS.

    2. AE e Cond = F + bloco B -> AS
        Pela AE uma mensagem da situação foi apresentada para o usuário e como condição é falsa, o estado é nulo.
        Portanto, o bloco B é executado e vale AI5, valendo assim a AS.


*/
/*
Segunda seleção:

    //AE: Mensagem da situacao apresentada para o usuário
        if(PopulaMenus(e)!=PRI_CondRetOK){
            //Bloco A
            //AI3: Programa terminado sem vazamento de memória
        }    
    //AS: Menus populados e valem as assertivas estruturais do menu ou programa terminado, caso tenha faltado memória
    
    1. AE e Cond = V + bloco A -> AS
        Pela AE uma mensagem da situação foi apresentada para o usuário e como condição é verdadeira, os Menus não foram populados e houve limpeza de memória        
        Portanto, o bloco A é executado e vale AI3, valendo assim a AS.

    2. AE e Cond = F -> AS
        Pela AE uma mensagem da situação foi apresentada para o usuário e como condição é falsa, os Menus foram populados corretamente, valendo assim a AS.
*/
/*
Terceira seleção:

        //AE: atual tem o id do Menu corrente, se atual for correspondente ao editor ou ao jogo, existe um tabuleiro apontado pelo estado 
        if(atual == EDITOR||atual == JOGO){
            //Bloco A;
            //AI10: A situação do tabuleiro foi apresentada para o usuário
        }
        AS: 
            Caso o menu corrente seja o do editor ou do jogo:
                A situação do tabuleiro foi apresentada para o usuário 
            Caso contrário:
                O tabuleiro não foi apresentado para o usuário
    
    1. AE e Cond = V + bloco A -> AS
        Pela AE a variável 'atual' possui o valor do id do Menu corrente e como condição é verdadeira, atual corresponde ao id do Menu do editor ou do jogo         
        Portanto, o bloco A é executado e vale AI10, valendo assim a AS.

    2. AE e Cond = F -> AS
        Pela AE a variável 'atual' possui o valor do id do Menu corrente e como condição é falsa, atual corresponde a algum id que não o do editor ou do jogo, valendo assim a AS.
*/
/*
Repetição:


    //AE: O Menu corrente é menu inicial, que é diferente de jogo e editor
    while(EST_MenuCorrente()!=0){
        Bloco A;
        //AI8: O menu corrente e suas opções são apresentadas para o usuário
        //AI9: atual tem o id do Menu corrente, se atual for correspondente ao editor ou ao jogo, existe um tabuleiro apontado pelo estado 
        AI11: 
            Caso o menu corrente seja o do editor ou do jogo:
                A situação do tabuleiro foi apresentada para o usuário 
            Caso contrário:
                O tabuleiro não foi apresentado para o usuário
       
        //AI12: O comando que o usuário forneceu foi avaliado e o usuário recebeu uma resposta apropriada. Se o comando for de sair, o menu corrente do estado vira 0.
    }
    //AS: O usuário optou por sair do programa

    //Ainv: O Estado e seus Menus existem e valem suas assertivas estruturais, se 'atual' for correspondente ao editor ou ao jogo, existe em estado um tabuleiro e suas assertivas estruturais valem. 'atual' sempre possui um id valido para os menus do estado. 
   
    1. AE -> Ainv
        Por AE, o Menu corrente é o menu inicial, o atual é válido, assim como estado e seus menus. O atual não é o editor nem jogo. Portanto vale Ainv.   
    2. AE e Cond = F -> AS
        Por AE, o Menu corrente e suas opções são apresentadas para o usuário. Como a condição é falsa, o comando de sair fornecido pelo usuário foi avaliado e o Menu corrente virou 0. Portanto vale AS. 

    3. AE e Cond = V + bloco A -> Ainv
        Por AE, o Menu corrente é o menu inicial, o atual é válido, assim como estado e seus menus. Como a condição é verdadeira, o programa não acabou e existe um proximo menu a ser apresentado. Portanto vale Ainv.   
    
    4. Ainv e Cond = V + bloco A -> Ainv
        Para Ainv continuar valendo, bloco A avaliou o comando fornecido pelo usuário, e este foi diferente do correspondente ao termino do programa. 
        Como a condição é verdadeira, o bloco A avaliou o comando fornecido como não término, portanto, vale Ainv.
    
    5. Ainv e Cond = F -> AS
        Como a condição é falsa, o comando fornecido pelo usuário foi avaliado como o término do programa. Portato o menu corrente vira 0 e AS vale.     
    6. Término
        ???
*/
