#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    int code; // chave de busca (tem que ser única)
    char name[100];         // nome produto, nao tem obrigatorio no trabalho mas faz sentido ter um nome
    char description[100];     //descrição do produto
    int quantity;          // quantidade em estoque
    float price;             // preço do produto
    int guarantee;      // campo opcional: garantia em meses
    char fornecedor[50];     // campo opcional: nome do fornecedor
    struct Node* esquerda;     // ponteiro para o nó à esquerda
    struct Node* direita;      // ponteiro para o nó à direita
} Node;

//fazer função pra criar novo no
//fazer funçoes da arvore binaria de busca para implementar nas funçoes abaixo

void insertProduct() {
    printf("\ninsertProduct\n");
}

void consultProduct() {
    printf("\nconsultProduct\n");
}

void removeProduct() {
    printf("\nremoveProduct\n");
}

void listarProdutos() {
    printf("\nlistarProdutos\n");
}

void listProductsInOrder() {
    printf("\nlistProductsInOrder\n");
}

void listProductsPreOrder() {
    printf("\nlistProductsPreOrder\n");
}

void listProductsAterOrder() {
    printf("\nlistProductsAterOrder\n");
}

void complement1() {
    printf("\ncomplement1\n");
}

void complement2() {
    printf("\ncomplement2\n");
}

void complement3() {
    printf("\ncomplement3\n");
}

void menu(){


    int option;

    do {
        printf(
            "\n+---------------------------+"
            "\n|         TECHINFO          |"
            "\n+---------------------------+"
            "\n"
            "\n  > 1. Inserir Produto"
            "\n  > 2. Consultar Produto"
            "\n  > 3. Remover Produto"
            "\n  > 4. Listar Produto"
            "\n  > 5. Complemento 1"
            "\n  > 6. Complemento 2"
            "\n  > 7. Complemento 3"
            "\n  > 8. Sair"
            "\n============================="
            "\nSelecione uma opcao >> "
        );
        scanf("%d", &option);

        switch (option) {
            case 1: {

                insertProduct();
                break;

            }
            case 2: {
                
                consultProduct();
                break;

            }
            case 3: {
                
                removeProduct();
                break;

            }
            case 4: {

                int listOption;
                do {
                    printf(
                        "\n+-------------------------------+"
                        "\n|     LISTAGEM DE PRODUTOS      |"
                        "\n+-------------------------------+"
                        "\n"
                        "\n1. Em-ordem (crescente por codigo)"
                        "\n2. Pre-ordem"
                        "\n3. Pos-ordem"
                        "\n4. Voltar"
                        "\n---------------------------------"
                        "\nEscolha uma opcao >> "
                    );
                    scanf("%d", &listOption);

                    switch(listOption) {
                        case 1: 

                            printf("Listando em-ordem...\n"); 
                            break;
                            
                        case 2: 

                            printf("Listando pre-ordem...\n"); 
                            break;

                        case 3: 

                            printf("Listando pos-ordem...\n"); 
                            break;
                            
                        case 4: 

                            printf("Voltando ao menu principal...\n"); 
                            break;

                        default: 
                            printf("Opcao invalida!\n");
                    }

                } while(listOption != 4);

                break;
            }
            case 5: {

                complement1();
                break;

            }
            case 6: {

                complement2();
                break;

            }
            case 7: {

                complement3();
                break;

            }
            case 8: {

                printf("\nEncerrando o sistema... Obrigado por usar o TECHINFO!\n");
                break;

            }

            default:
                printf("<* Setor invalido! *>\n");

                break;
        }
    } while (option != 8);
}

int main(){

    menu();

    return 0;
}
