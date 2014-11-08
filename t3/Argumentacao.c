//AE: Não há, é o início da execução e não recebemos parametros
int main(){
    int atual;
    EST_tppEstado e;
    EST_tpCondRet cr1;
    PRI_tpCondRet cr2;
    MEN_tppMenus menus;
    cr1 = EST_CriaEstado(&e);
    //AI1: Estado existe e valem suas assertivas estruturais e cr1 vale EST_CondRetOK se o estado foi criado corretamente
    Erro("Alocando Estado",cr1,EST);
    //AI2: Mensagem da situacao apresentada para o usuário
    if(cr1==EST_CondRetOK){
        cr2 = PopulaMenus(e);
        //AI3: Menus populados e valem as assertivas estruturais do menu e cr2 vale EST_CondRetOK se os Menus foram populados corretamente
        Erro("Populando Menus",cr2,PRI);
        //AI4: Mensagem da situacao apresentada para o usuário
    }
    //AI5: Caso o estado tenha sido alocado corretamente, os Menus foram populados e valem as assertivas estruturais do menu, usuario esta ciente da situacao. caso contrario, a memoria foi limpa. cr2 vale EST_CondRetOK se os Menus foram populados corretamente

    if(cr1 != EST_CondRetOK || cr2 != PRI_CondRetOK){
        return 0;
        //AI6: Programa terminado sem vazamento de memória
    }
    //AI7: Caso a criação do estado ou dos menus tenha falhado, o programa é terminado sem vazamento de memória. caso contrario, o programa continua.
    EST_GetMenus(e,&menus);
    //AI8: 'menus' aponta para o grafo de menus do estado, já populado
    MEN_MenuInicial(menus);
    //AI9: O Menu corrente é o inicial de id 1, que é diferente de JOGO e EDITOR
    MEN_MenuCorrente(menus,&atual);
    //AI10: 'atual' tem valor 1, o valor de inicio, visto que AI9 vale
    while(atual!=0){
        ApresentaMenu(e);
        //AI11: O menu corrente e suas opções são apresentadas para o usuário, assim como a existencia de um tabuleiro na memoria
        if(atual == EDITOR||atual == JOGO){
            ApresentaTabuleiro(e);
            //AI12: A situação do tabuleiro foi apresentada para o usuário
        }
        /*
        AI13: 
            Caso o menu corrente seja o do editor ou do jogo:
                A situação do tabuleiro foi apresentada para o usuário 
            Caso contrário:
                O tabuleiro não foi apresentado para o usuário
        */
        Erro("Comando:",LeCmd(e),PRI);
        //AI14: O comando que o usuário forneceu foi avaliado e o usuário recebeu uma resposta apropriada.
            //Se o comando for de voltar, o usuario sobe um nivel na arvore de menus. 
            //O pai da raiz tem id 0, simbolizando a opcao de sair do programa. 
        EST_GetMenus(e,&menus);
        //AI15: Assegura que continuamos apontando para o Menu do estado 
        MEN_MenuCorrente(menus,&atual);
        //AI16: atualiza o valor de 'atual' com o id do menu corrente
    }
    //AI17: O usuário, durante a execução do programa, optou por sair do programa, atual = 0
    EST_DestruirEstado(e);
    //AI18: A memória foi limpa
    return 0;
    //AS: Programa terminado sem vazamento de memória
}

/*
Sequencia:
    
    //AE: Não há, é o início da execução e não recebemos parametros
    //AI1: Estado existe e valem suas assertivas estruturais e cr1 vale EST_CondRetOK se o estado foi criado corretamente
    //AI2: Mensagem da situacao apresentada para o usuário
    //AI5: Caso o estado tenha sido alocado corretamente, os Menus foram populados e valem as assertivas estruturais do menu, usuario esta ciente da situacao. caso contrario, a memoria foi limpa. cr2 vale EST_CondRetOK se os Menus foram populados corretamente
    //AI7: Caso a criação do estado ou dos menus tenha falhado, o programa é terminado sem vazamento de memória. caso contrario, o programa continua.
    //AI8: 'menus' aponta para o grafo de menus do estado, já populado
    //AI9: O Menu corrente é o inicial de id 1, que é diferente de JOGO e EDITOR
    //AI10: 'atual' tem valor 1, o valor de inicio, visto que AI9 vale
    //A17: O usuário, durante a execução do programa, optou por sair do programa, atual = 0
    //AI18: A memória foi limpa
    //AS: Programa terminado sem vazamento de memória
*/
/*
Primeira seleção:
    
    //AE = A1: Mensagem da situacao apresentada para o usuário e cr1 vale EST_CondRetOK se o estado foi criado corretamente
    if(cr1==EST_CondRetOK){
        bloco A;
        //AI3: Menus populados e valem as assertivas estruturais do menu e cr2 vale EST_CondRetOK se os Menus foram populados corretamente
        //AI4: Mensagem da situacao apresentada para o usuário
    }
    //AS = AI5: Caso o estado tenha sido alocado corretamente, os Menus foram populados e valem as assertivas estruturais do menu, usuario esta ciente da situacao. caso contrario, a memoria foi limpa. cr2 vale EST_CondRetOK se os Menus foram populados corretamente
    
    1. AE e Cond = V + bloco A -> AS
        Pela AE uma mensagem da situação foi apresentada para o usuário e como condição é verdadeira, o estado foi criado corretamente.
        Portanto, o bloco A é executado e vale AI3 e AI4, valendo assim a AS.

    2. AE e Cond = F -> AS
        Pela AE uma mensagem da situação foi apresentada para o usuário e como condição é falsa, o estado não foi criado com exito.


*/
/*
Segunda seleção:

    //AE = AI1+AI5: Caso o estado tenha sido alocado corretamente, os Menus foram populados e valem as assertivas estruturais do menu, usuario esta ciente da situacao. cr2 vale EST_CondRetOK se os Menus foram populados corretamente. Mensagem da situacao apresentada para o usuário e cr1 vale EST_CondRetOK se o estado foi criado corretamente 
    if(cr1 != EST_CondRetOK || cr2 != PRI_CondRetOK){
        bloco A;
        //AI6: Programa terminado sem vazamento de memória
    }
    //AS = AI7: Caso a criação do estado ou dos menus tenha falhado, o programa é terminado sem vazamento de memória. caso contrario, o programa continua.
    
    1. AE e Cond = V + bloco A -> AS
        Pela AE cr1 e cr2 representam a situação da criação e população do estado e seusmenus. Como a condição é verdadeira, o Estado e os Menus não foram criados e populados e houve limpeza de memória.        
        Portanto, o bloco A é executado e vale AI6, valendo assim a AS.

    2. AE e Cond = F -> AS
        Pela AE uma mensagem da situação foi apresentada para o usuário e como condição é falsa, o Estado e os Menus foram populados corretamente, valendo assim a AS.
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


    //AE: atual é menu inicial = 1, que é diferente de jogo e editor
    while(atual!=0){
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
    //AS: O usuário, durante a execução do programa, optou por sair do programa, atual = 0

    //Ainv: O Estado e seus Menus existem e valem suas assertivas estruturais, se 'atual' for correspondente ao editor ou ao jogo, existe em estado um tabuleiro e suas assertivas estruturais valem. 'atual' sempre possui um id valido para os menus do estado (atual !=0). 
   
    1. AE -> Ainv
        Por AE, o Menu corrente é o menu inicial, o atual é válido, assim como estado e seus menus. O atual = 1, que não é o editor nem jogo, nem 0. Portanto vale Ainv.   

    2. AE e Cond = F -> AS
        Por AE, atual = 1. Mas como condição é falsa, atual = 0. Esse caso não existe. Se existisse, ignorando a saida para o usuario, o efeito é o mesmo que o usuário ter escolhido sair do programa como primeira opção. Portanto vale AS.
        

    3. AE e Cond = V + bloco A -> Ainv
        Por AE, o Menu corrente é o menu inicial, o atual é válido, assim como estado e seus menus. Como a condição é verdadeira, o comando fornecido pelo usuario foi avaliado. Como a condição é verdadeira, o usuario nao optou por sair do programa, o programa não acabou e existe um proximo menu a ser apresentado. Portanto vale Ainv.   
    
    4. Ainv e Cond = V + bloco A -> Ainv
        Para Ainv continuar valendo, bloco A avaliou o comando fornecido pelo usuário, e este foi diferente do correspondente ao termino do programa. 
        Como a condição é verdadeira, o bloco A avaliou o comando fornecido como não término, portanto, vale Ainv.
    
    5. Ainv e Cond = F -> AS
        Como a condição é falsa, o comando fornecido pelo usuário foi avaliado como o término do programa. atual é 0 e AS vale.     
    6. Término
        atual = 0
*/
