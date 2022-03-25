# Documentação

## Checklist

- [x] Funções
- [x] Definição de variáveis
- [ ] Operações
  - [ ] Atribuição
    - [ ] Atribuição simples
    - [ ] Soma
    - [ ] Subtração
    - [ ] Multiplicação
    - [ ] Divisão
    - [ ] Chamada de função
  - [ ] Acesso a arrays
    - [ ] Leitura
    - [ ] Escrita
  - [ ] Condicional if
  - [ ] Retorno

## Funções

### Definição
A definição de uma função em BPL é feita da seguinte maneira:

```
function fN pX1 pX2 pX3
    ...
end
```

* `fN` é o nome da função  
  * `N` é um inteiro positivo
* `pXN` são os parâmetros da função  
  * `X` representa o tipo do parâmetro
    * `i` indica que o parâmetro é um número inteiro (integer)
    * `a` indica que o parâmetro é um vetor de inteiros (array)
  * `N` representa a posição do parâmetro (primeiro, segundo, terceiro)
    * `N` pode ser um número de 1 a 3

### Implementação
Ao se definir uma função, o código em Assembly deve:

1. Criar um label correspondente
2. Gerar a pilha de execução da função
   * Montar a pilha conforme a definição de variáveis locais

Ao chegar no final da função (`end`), o código Assembly deve:

1. Desmontar a pilha de execução da função
2. Retornar



## Variáveis locais

### Definição
A declaração de variáveis locais de uma função deve ser feita dentro de um bloco `def-enddef`:

```
def
    ...
enddef
```

Este bloco é obrigatório em todas as funções. Caso uma função não precise de variáveis locais, o bloco `def-enddef` fica vazio.
* PS: O bloco `def-enddef` deve estar na linha abaixo do nome da função

Dentro do bloco `def-enddef`, cada linha representa a declaração de uma variável.

Há 2 formas de se declarar variáveis dentro de uma função:
* `var viN` declara uma variável do tipo inteiro
  * `var` é a palavra-chave para se declarar uma variável inteira
  * `viN` é o nome da variável
    * `N` é um número inteiro
* `vet vaN size ciM`
  * `vet` é a palavra-chave para se declarar um vetor de inteiros
  * `vaN` é o nome da variável
    * `N` é um número inteiro
  * `size` é uma palavra chave para indicar o tamanho do vetor
  * `ciM` é o tamanho do vetor
    * `ci` é um prefixo utilizado para declarar inteiros constantes
    * `M` é um inteiro positivo

Algumas considerações:
* Não haverá 2 variáveis diferentes com o mesmo índice (valor de `N`)
* Os índices `N` das variáveis começam em 1 e vão incrementando de 1 em 1 para cada variável declarada

### Implementação
Para cada definição de variável, o código Assembly deve:  

1. Aumentar o tamanho da pilha
   * Caso a variável seja do tipo inteiro, aumentar a pilha em 4 bytes.
   * Caso a variável seja do tipo vetor de inteiros, aumentar a pilha pelo tamanho correspondente (4 bytes * tamanho do vetor)

PS: No final de uma função, a pilha deve ser desfeita.

## Comandos
Dentro de uma função, após a definição de variáveis, cada linha irá representar um comando. Esta parte irá documentar os possíveis comandos que podem ser feitos e o comportamento esperado.

## Comando - Operações matemáticas

### Definição
Na linguagem BPL, é possível realizar 4 operações matemáticas:

* Soma: `+`
* Subtração: `-`
* Multiplicação: `*`
* Divisão: `/`

Todos esses operadores são operadores binários, ou seja, são necessárias 2 variáveis para realizar uma operação matemática. A sintaxe para se utilizar uma operação matemática é a seguinte:

`<variavel1> <operador> <variavel2>`

### Implementação
Como o operador de instruções matemáticas vem no meio da expressão, pode ser um pouco complicado saber quando você está realizando uma leitura vs uma operação. Por isso, foi adotado o seguinte procedimento:

1. Ao encontrar `variavel1`, guardar o seu valor em algum registrador
2. Verificar se após `variavel1` há uma quebra de linha ou um operador
   * Caso haja uma quebra de linha, vá para o último passo

3. Aplicar a operação matemática correta e guardar o seu resultado no registrador
   * PS: Buscar o valor de `variavel2` da memória
5. Utilizar o valor dentro do registrador.

## Comando - Atribuição

### Definição
Uma variável do tipo inteiro pode ser atribuida um valor utilizando o operador `=`.

A sintaxe para utilizar o comando de atribuição é a seguinte:
```<nome_variável> = <valor>```  
onde `nome_variável` é a varíavel com o valor a ser atribuido, enquanto `valor` pode ser uma constante, o resultado de uma expressão (`+`, `-`, `*`, `/`), ou o valor de retorno de uma função.

### Implementação
Caso numa leitura de linha, a primeira palavra não for uma palavra-chave (`if`, `set`, `get`), então é uma operação de atribuição. Assim, o seguinte procedimento deve ser feito:

1. Preparar um registrador para receber `valor`
2. Analisar o texto depois do `=` para descobrir o que deve ser feito:
   * Caso seja uma chamada de função, o valor de retorno estará no registrador
   * Caso seja uma constante, guarde o seu valor no registrador
   * Caso contrário, siga os passos definidos em: Comando - Expressões

3. Guardar o valor que está dentro do registrador na memória em seu local apropriado

## Comando - Acesso a vetores

Em relação a acesso a arrays, existem 2 tipos de operações que podem ser feitas:
* Ler um valor dentro do array
* Colocar um valor dentro do array

## Acesso a vetores - Leitura
### Definição
Para se retirar um valor dentro de um array, deve-se utilizar o seguinte comando:

`get nome index indice to destino`  
Onde:
* `nome`: É o nome do array a ser acessado
* `indice`: É o indice do array a ser acessado
  * Os índice são sempre números constantes (`ciN`)
  * A contagem de índices do array começa em 0
* `destino`: É o nome da variável onde será armazenado o valor lido.
  * O destino deve ser uma variável inteira local, ou um parâmetro inteiro (`viN` ou `piN`)
 
### Implementação
Ao ler o valor de um array, o código Assembly resultante deve:

1. Achar o endereço do array dentro da memória (variável local ou parâmetro) e guardar seu valor em um registrador
2. Calcular o offset da posição a ser lida dentro do array
3. Copiar o valor lido para o local destino.

## Acesso a vetores - Escrita
Para se escrever um valor dentro de um array, deve-se utilizar o seguinte comando:

`set nome index indice with valor`  
Onde:
* `nome`: É o nome do array a ser acessado
* `indice`: É o indice do array a ser acessado
  * Os índice são sempre números constantes (`ciN`)
  * A contagem de índices do array começa em 0
* `valor`: É o valor a ser armazenado dentro do array
  * Pode ser uma variável inteira, um parâmetro inteiro ou uma constante

### Implementação
1. Achar o endereço do array dentro da memória (variável local ou parâmetro)
2. Calcular a posição de memória do índice a ser escrito
3. Copiar o valor para o local correto dentro do array



## Comando - Condicional
### Definição
A condicional `if` verifica se o valor fornecido a ler é 0.  
Caso ele seja, ela pula para o final `endif`.  
Caso ele não seja, ela executa o comando dentro do if.

A condicional `if` tem a seguinte sintaxe dentro da BPL:  
```
if condição
comando
endif
```  
Onde:
* `condição`: É o valor a ser testado. Pode ser uma variável inteira, um parâmetro inteiro ou uma constante
* `comando`: É o comando a ser executado.
  * Há apenas 1 único comando dentro do `if`
  * O comando pode ser qualquer comando visto até agora.

### Implementação
Ao encontrar a condicional `if` dentro da BPL, o código Assembly correspondente deve:

1. Comparar o valor fornecido com 0
2. Tomar uma decisão baseado no resultado da comparação feita
   * Caso o valor fornecido seja 0, pular para o label do final do if
   * Caso o valor fornecido não seja 0, continuar a execução normalmente.
3. Gerar o código do comando correspondente
4. Gerar um label para pular o comando acima
   * `IMPORTANTE`: Cada label deve ser único


## Comando - Retorno 
### Definição
O comando de retorno deve ser obrigatoriamente o último comando da função.  
Toda função tem um comando de retorno no final.

O comando de retorno tem a seguinte sintaxe:  
`return valor`  
Onde:
*  `valor`: É o valor a ser retornado. Pode ser uma variável, um parâmetro ou uma constante.

### Implementação
Ao encontrar o comando de retorno, o código Assembly correspondente deve:

1. Guardar o valor dentro do registrador %eax
2. Desfazer a pilha
3. Retornar