#include <stdio.h>
#include <string.h>

#define MAX_SLOTS 10
#define MAX_NAME 32


// Estruturas

typedef struct {
    char name[MAX_NAME];
    int quantidade;
    int durabilidade;
    int empilhavel;
} Item;

typedef struct {
    Item slots[MAX_SLOTS];
} Inventario;


// Inicializar Inventário

void inicializarInventario(Inventario *inv) {
    for (int i = 0; i < MAX_SLOTS; i++) {
        inv->slots[i].name[0] = '\0';
        inv->slots[i].quantidade = 0;
        inv->slots[i].durabilidade = 0;
        inv->slots[i].empilhavel = 0;
    }
}


// Adicionar Item

int adicionarItem(Inventario *inv, const char *nome, int quantidade, int durabilidade, int empilhavel) {

    // 1 — tentar empilhar, se possível
    if (empilhavel) {
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (strcmp(inv->slots[i].name, nome) == 0) {
                inv->slots[i].quantidade += quantidade;
                return 1; // sucesso
            }
        }
    }

    // 2 — procurar slot vazio
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (inv->slots[i].name[0] == '\0') {
            strcpy(inv->slots[i].name, nome);
            inv->slots[i].quantidade = quantidade;
            inv->slots[i].durabilidade = durabilidade;
            inv->slots[i].empilhavel = empilhavel;
            return 1; // sucesso
        }
    }

    return 0; // inventário cheio
}

// Usar Item

int usarItem(Inventario *inv, const char *nome) {
    for (int i = 0; i < MAX_SLOTS; i++) {

        if (strcmp(inv->slots[i].name, nome) == 0) {

            printf("Você usou: %s\n", nome);

            // Reduz quantidade
            inv->slots[i].quantidade--;

            // Reduz durabilidade, se tiver
            if (inv->slots[i].durabilidade > 0) {
                inv->slots[i].durabilidade--;
            }

            // Se item acabou → limpar slot
            if (inv->slots[i].quantidade <= 0) {
                inv->slots[i].name[0] = '\0';
                inv->slots[i].quantidade = 0;
                inv->slots[i].durabilidade = 0;
                inv->slots[i].empilhavel = 0;
            }

            return 1; // sucesso
        }
    }

    return 0; // item não encontrado
}

// Mostrar Inventário

void mostrarInventario(Inventario *inv) {
    printf("\n===== INVENTÁRIO =====\n");

    int vazio = 1;

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (inv->slots[i].name[0] != '\0') {
            vazio = 0;
            printf("[%02d] %s x%d", i, inv->slots[i].name, inv->slots[i].quantidade);

            if (inv->slots[i].durabilidade > 0)
                printf(" (Durabilidade: %d)", inv->slots[i].durabilidade);

            printf("\n");
        }
    }

    if (vazio)
        printf("(Inventário vazio)\n");

    printf("=======================\n");
}

// Itens iniciais

void adicionarItensIniciais(Inventario *inv) {
    adicionarItem(inv, "Faca improvisada", 1, 10, 0);
    adicionarItem(inv, "Bandagem", 2, 0, 1);
    adicionarItem(inv, "Cantil vazio", 1, 0, 0);
    adicionarItem(inv, "Racao basica", 2, 0, 1);
}


int main() {
    Inventario inventario;

    inicializarInventario(&inventario);
    adicionarItensIniciais(&inventario);

    mostrarInventario(&inventario);

    printf("\nUsando Bandagem...\n");
    usarItem(&inventario, "Bandagem");

    mostrarInventario(&inventario);

    printf("\nColetando Madeira...\n");
    adicionarItem(&inventario, "Madeira", 3, 0, 1);

    mostrarInventario(&inventario);

    return 0;
}
