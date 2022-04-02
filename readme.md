# Trabalho de Software Básico

## Compilação
Como há várias coisas diferentes que podemos compilar neste trabalho (O programa tradutor, o programa principal e o assembly), pode-se fazer uso do comando `make` para facilitar a sua vida.  
O comando `make` pode ser invocado pelo terminal com um parâmetro para determinar o que você quer compilar:
* `make tradutor` irá compilar apenas o programa tradutor de *BPL* para Assembly
* `make assembly` irá compilar os arquivos Assembly gerados pelo programa tradutor
* `make main` irá compilar o programa principal (que pode interagir com o assembly) e os arquivos Assembly que foram gerados pelo programa tradutor