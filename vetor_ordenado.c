#include <stdio.h>

#define MAX 50

// Busca binária: retorna o índice do elemento ou -1 se não encontrado
int buscaBinaria(int vetor[], int tamanho, int valor) {
    int inicio = 0, fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (vetor[meio] == valor)
            return meio;
        else if (vetor[meio] < valor)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

// Inserção ordenada: insere o valor na posição correta
// Retorna 1 se sucesso, 0 se vetor cheio
int insercaoOrdenada(int vetor[], int *tamanho, int capacidade, int valor) {
    if (*tamanho >= capacidade)
        return 0;

    int i = *tamanho - 1;

    // Desloca elementos maiores para a direita
    while (i >= 0 && vetor[i] > valor) {
        vetor[i + 1] = vetor[i];
        i--;
    }

    vetor[i + 1] = valor;
    (*tamanho)++;
    return 1;
}

// Remove um elemento pelo valor; desloca os elementos à direita para a esquerda
// Retorna 1 se removido, 0 se não encontrado
int removerElemento(int vetor[], int *tamanho, int valor) {
    int pos = buscaBinaria(vetor, *tamanho, valor);

    if (pos == -1)
        return 0;

    for (int i = pos; i < *tamanho - 1; i++)
        vetor[i] = vetor[i + 1];

    (*tamanho)--;
    return 1;
}

// Imprime todos os elementos do vetor
void imprimirVetor(int vetor[], int tamanho) {
    if (tamanho == 0) {
        printf("  [ vetor vazio ]\n");
        return;
    }

    printf("  [ ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", vetor[i]);
        if (i < tamanho - 1)
            printf(", ");
    }
    printf(" ]\n");
    printf("  Tamanho atual: %d elemento(s)\n", tamanho);
}

int main() {
    int vetor[MAX];
    int capacidade, tamanho = 0;
    int opcao, valor, qtd;

    // ── Passo 1: definir a capacidade do vetor ──────────────────────────────
    do {
        printf("Digite o tamanho do vetor (entre 3 e 50): ");
        scanf("%d", &capacidade);

        if (capacidade < 3 || capacidade > MAX)
            printf("  Tamanho invalido! Escolha entre 3 e 50.\n");

    } while (capacidade < 3 || capacidade > MAX);

    // ── Passo 2: preencher o vetor com inserção ordenada ────────────────────
    printf("\nDigite a quantidade de valores a inserir (maximo %d): ", capacidade);
    scanf("%d", &qtd);

    if (qtd < 0) qtd = 0;
    if (qtd > capacidade) qtd = capacidade;

    printf("Digite %d valor(es) inteiro(s):\n", qtd);
    for (int i = 0; i < qtd; i++) {
        printf("  Valor %d: ", i + 1);
        scanf("%d", &valor);
        insercaoOrdenada(vetor, &tamanho, capacidade, valor);
    }

    printf("\nVetor preenchido com sucesso!\n");
    imprimirVetor(vetor, tamanho);

    // ── Menu principal ──────────────────────────────────────────────────────
    do {
        printf("\n╔══════════════════════════════════════╗\n");
        printf("║            MENU DE OPCOES            ║\n");
        printf("╠══════════════════════════════════════╣\n");
        printf("║  1. Imprimir vetor                   ║\n");
        printf("║  2. Consultar elemento (busca bin.)  ║\n");
        printf("║  3. Remover elemento                 ║\n");
        printf("║  4. Inserir elemento                 ║\n");
        printf("║  0. Sair                             ║\n");
        printf("╚══════════════════════════════════════╝\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            // ── Opção 1: Imprimir ─────────────────────────────────────────
            case 1:
                printf("\nVetor atual:\n");
                imprimirVetor(vetor, tamanho);
                break;

            // ── Opção 2: Consultar ────────────────────────────────────────
            case 2:
                printf("\nDigite o valor a consultar: ");
                scanf("%d", &valor);

                int pos = buscaBinaria(vetor, tamanho, valor);
                if (pos == -1)
                    printf("  Elemento %d nao encontrado (posicao: -1).\n", valor);
                else
                    printf("  Elemento %d encontrado na posicao %d.\n", valor, pos);
                break;

            // ── Opção 3: Remover ──────────────────────────────────────────
            case 3:
                printf("\nDigite o valor a remover: ");
                scanf("%d", &valor);

                if (removerElemento(vetor, &tamanho, valor))
                    printf("  Elemento %d removido com sucesso.\n", valor);
                else
                    printf("  Elemento %d nao encontrado. Nenhuma alteracao.\n", valor);

                printf("  Vetor apos remocao:\n");
                imprimirVetor(vetor, tamanho);
                break;

            // ── Opção 4: Inserir ──────────────────────────────────────────
            case 4:
                if (tamanho >= capacidade) {
                    printf("\n  Vetor cheio (capacidade maxima: %d). "
                           "Nao e possivel inserir.\n", capacidade);
                    break;
                }

                printf("\nDigite o valor a inserir: ");
                scanf("%d", &valor);

                if (insercaoOrdenada(vetor, &tamanho, capacidade, valor))
                    printf("  Elemento %d inserido com sucesso.\n", valor);
                else
                    printf("  Falha ao inserir: vetor cheio.\n");

                printf("  Vetor apos insercao:\n");
                imprimirVetor(vetor, tamanho);
                break;

            // ── Sair ──────────────────────────────────────────────────────
            case 0:
                printf("\nEncerrando o programa. Ate logo!\n");
                break;

            default:
                printf("\n  Opcao invalida! Escolha entre 0 e 4.\n");
        }

    } while (opcao != 0);

    return 0;
}
