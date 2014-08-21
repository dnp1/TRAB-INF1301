Progresso
=========


### Queremos desenvolver o projeto em ambiente unix.

* Para isso, tivemos a ideia de usar o pacote de ferramentas _autotools_. Eles tem como pré-requisito um makefile.

* Este makefile será gerado através do comando 

> $ .../arcabouc/Fontes gcc * -MM 

* Este comando gera uma arvore de dependencias, no formato esperado pelo Makefile.

* Com isso geramos um configure a partir do _autoconf_. Daí podemos fazer:

>./configure

> ./make

> ./make install

##### As dificuldades encontradas baseam-se na Case-sensitiveness do ambiente, ao contrario do ambiente proposto, windows.

* Para resolver esta questão estamos desenvolvendo um script que muda,  apenas para a etapa de compilação os nomes dos includes nos arquivos, de modo que combinem com os nomes dos arquivos, que são de forma %w+.H, onde %w+ é sempre upper case.

##### O marcelo nos forneceu seu port para linux do arcabouco 

https://github.com/rbertoche/t2

* Temos que descobrir como usar

### Estratégia de trabalho modular sugerida

1. Arquitetura do Programa = Dependências conceituais/funcionais de modulos e interfaces

2. Determinação das funções presentes em cada interface

3. Determinação dos argumentos e o retorno das funções determinadas

4. Documentação das funções, pelo ponto de vista do uso, do programador cliente

5. Implementação das funções, com as assinaturas das funções internas e externas, separadas nessas duas classes, no topo do programa.
