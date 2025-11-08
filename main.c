#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Node Struct
typedef struct Node {
    int code;               // Search code (unique)
    char name[100];         // Product's name
    char description[100];  // Product's description
    int quantity;           // In stock quantity
    float price;            // Product's price
    int guarantee;          // Optional: product's guarantee in months
    char supplier[50];      // Optional: Supllier's name
    struct Node* left;      // Pointer to the left node
    struct Node* right;     // Pointer to the right node
} Node;

// Node Struct Implementation Functions
Node* createNode(int code, char name[], char description[], int quantity, float price, int guarantee,  char supplier[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->code = code;

    strcpy(newNode->name, name);
    strcpy(newNode->description, description);
    newNode->quantity = quantity;
    newNode->price = price;
    newNode->guarantee = guarantee;
    strcpy(newNode->supplier, supplier);
    
    newNode->left = newNode->right = NULL;

    return newNode;
}

Node* insert(Node* root, int code, char name[], char description[], int quantity, float price, int guarantee,  char supplier[]) {
    if (root == NULL) {
        return createNode(code, name, description, quantity, price, guarantee, supplier);
    }
        
    if (code < root->code) {
	    root->left = insert(root->left, code, name, description, quantity, price, guarantee, supplier);
	    return root;
    } else {
        if (code > root->code) {
		    root->right = insert(root->right, code, name, description, quantity, price, guarantee, supplier);
		    return root;
	    } else {
            return root;
        }
    }
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf("Codigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f\n",
               root->code, root->name, root->quantity, root->price);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Codigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f\n",
               root->code, root->name, root->quantity, root->price);
        inOrder(root->right);
    }

}

void posOrder(Node* root) {
    if (root != NULL) {
        posOrder(root->left);
        posOrder(root->right);
        printf("Codigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f\n",
               root->code, root->name, root->quantity, root->price);
    }
}


// funções do menu
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

void consultProductsParcialDescription() {
    printf("\ncomplement1\n");
}

void consultProductsPriceRange() {
    printf("\ncomplement2\n");
}

void countProducts() {
    printf("\ncomplement3\n");
}

// Menu
void menu(){
    int option;

    do {
        printf(
            "\n+---------------------------+"
            "\n|         TECHINFO          |"
            "\n+---------------------------+"
            "\n"
            "\n  > 1. Inserir produto"
            "\n  > 2. Consultar produto"
            "\n  > 3. Remover produto"
            "\n  > 4. Listar produto"
            "\n  > 5. Buscar por descricao"
            "\n  > 6. Buscar por preço"
            "\n  > 7. Contar produtos"
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
                consultProductsParcialDescription();
                break;

            }
            case 6: {
                consultProductsPriceRange();
                break;

            }
            case 7: {
                countProducts();
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

void main(){
    Node* root = NULL;
    menu();
}