#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESZ 256

// Remove o '\n' do fim da linha
void remove_newline(char *ptr) {
  while (*ptr) {
    if (*ptr == '\n')
      *ptr = 0;
    else
      ptr++;
  }
}

int main() {
  char v1, tipo1, tipo2, tipo3;
  int r, nfunc;
  char line[LINESZ];
  int count = 0;

  // Lê uma linha por vez
  while (fgets(line, LINESZ, stdin) != NULL) {
    count++;
    remove_newline(line);
    // Verifica se line começa com 'def' (3 letras)
    if (strncmp(line, "def", 3) == 0) {
      printf("Linha %d: %s\n", count, line);
      printf("Inicio da definição\n");
      printf("\n");
      continue;
    }
    // Verifica se line começa com 'enddef' (6 letras)
    if (strncmp(line, "enddef", 6) == 0) {
      printf("Linha %d: %s\n", count, line);
      printf("Fim da definição\n");
      printf("\n");
      continue;
    }
    // Verifica se line começa com 'end' (3 letras)
    if (strncmp(line, "end", 3) == 0) {
      printf("Linha %d: %s\n", count, line);
      printf("Fim da função\n");
      printf("---\n");
      printf("\n");
      continue;
    }

    // Verifica se é 'function' e quantos elementos possui
    r = sscanf(line, "function f%d p%c1 p%c2 p%c3", &nfunc, &tipo1, &tipo2,
               &tipo3);

    if (r == 4) {
      printf("Linha %d: %s\n", count, line);
      printf("Função: '%d' ", nfunc);

      if (tipo1 == 'i') {
        printf("inteiro ");
      } else {
        printf("ponteiro\n");
      }
      printf("\n");

      if (tipo2 == 'i') {
        printf("inteiro  ");
      } else {
        printf("ponteiro\n");
      }

      if (tipo3 == 'i') {
        printf("inteiro ");
      } else {
        printf("ponteiro\n");
      }
      continue;
    }

    if (r == 3) {
      printf("Linha %d: %s\n", count, line);
      printf("Função: '%d' ", nfunc);

      if (tipo1 == 'i') {
        printf("inteiro ");
      } else {
        printf("ponteiro\n");
      }
      printf("\n");

      if (tipo2 == 'i') {
        printf("inteiro ");
      } else {
        printf("ponteiro\n");
      }
      continue;
    }
    if (r == 2) {
      printf("Linha %d: %s\n", count, line);
      printf("Função: '%d' ", nfunc);

      if (tipo1 == 'i') {
        printf("inteiro\n");
      } else {
        printf("ponteiro\n");
      }
      printf("\n");

      continue;
    }
    if (r == 1) {
      printf("Linha %d: %s\n", count, line);
      printf("Função: '%d' ", nfunc);
      printf("Sem parametros\n");
      printf("\n");
      continue;
    }
  }

  return 0;
}