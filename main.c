// Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Settings
#define STRING_LENGHT 100

// Node Struct
typedef struct Node {
    int code;                           // Search code (unique)
    char name[STRING_LENGHT];           // Product's name
    char description[STRING_LENGHT];    // Product's description
    int quantity;                       // In stock quantity
    float price;                        // Product's price
    int guarantee;                      // Optional: product's guarantee in months
    char supplier[STRING_LENGHT];       // Optional: Supllier's name
    struct Node* left;                  // Pointer to the left node
    struct Node* right;                 // Pointer to the right node
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

Node* insert(Node* root, Node* newNode) {
    if (root == NULL) {
        return newNode;
    }
        
    if (newNode->code < root->code) {
	    root->left = insert(root->left, newNode);
        printf("\n<* Produto cadastrado! *>\n");
	    return root;
    } else {
        if (newNode->code > root->code) {
		    root->right = insert(root->right, newNode);
            printf("\n<* Produto cadastrado! *>\n");
	        return root;
	    } else {
            printf("\n<* Codigo ja existente, tente novamente! *>\n");
            return root;
        }
    }
}

Node* consult(Node* root, int code) {
    if (root == NULL || root->code == code) {
        return root;
    }
    
    if (code < root->code) {
        return consult(root->left, code);
    } else {
        return consult(root->right, code);
    }
}

Node* smallestValue(Node* root) {
    Node* current = root;

    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

Node* removeNode(Node* root, int code) {
    if (root == NULL) {
        return root;
    }

    if (code < root->code) {
        root->left = removeNode(root->left, code);
    } else if (code > root->code) {
        root->right = removeNode(root->right, code);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);

            return NULL;
        } else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);

            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);

            return temp;
        } else {
            Node* temp = smallestValue(root->right);
            root->code = temp->code;
            strcpy(root->name, temp->name);
            strcpy(root->description, temp->description);
            root->quantity = temp->quantity;
            root->price = temp->price;
            root->guarantee = temp->guarantee;
            strcpy(root->supplier, temp->supplier);
            root->right = removeNode(root->right, temp->code);
        }

    }

    return root;
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf(
            "\nCodigo: %d | Nome: %s | Descricao: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->description, root->quantity, root->price, root->guarantee, root->supplier
        );

        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);

        printf(
            "\nCodigo: %d | Nome: %s | Descricao: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->description, root->quantity, root->price, root->guarantee, root->supplier
        );

        inOrder(root->right);
    }
}

void afterOrder(Node* root) {
    if (root != NULL) {
        afterOrder(root->left);
        afterOrder(root->right);

        printf(
            "\nCodigo: %d | Nome: %s | Descricao: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->description, root->quantity, root->price, root->guarantee, root->supplier
        );
    }
}

// Menu Functions
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insertProduct(Node** root) {
    char name[STRING_LENGHT], description[STRING_LENGHT], supplier[STRING_LENGHT];
    int code, quantity, guarantee;
    float price; 

    printf(
        "\n+---------------------------+"
        "\n|      INSERIR PRODUTO      |"
        "\n+---------------------------+"
        "\n"
    );


    while (1) {
        printf("\nCodigo >> ");
        if (scanf("%d", &code) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas números.\n");
            clearBuffer();
        }
    }

    printf("\nNome >> ");
    scanf(" %[^\n]", name);

    printf("\nDescricao >> ");
    scanf(" %[^\n]", description);

    while (1) {
        printf("\nQuantidade >> ");
        if (scanf("%d", &quantity) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros inteiros.\n");
            clearBuffer();
        }
    }

    while (1) {
        printf("\nPreco >> ");
        if (scanf("%f", &price) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros (use ponto para decimais, ex: 10.50).\n");
            clearBuffer();
        }
    }

    while (1) {
        printf("\nGarantia (meses) >> ");
        if (scanf("%d", &guarantee) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros inteiros.\n");
            clearBuffer();
        }
    }

    printf("\nFornecedor >> ");
    scanf(" %[^\n]", supplier);

    Node* newNode = createNode(code, name, description, quantity, price, guarantee, supplier);
    *root = insert(*root, newNode);


}

void consultProduct(Node* root) {
    int code;

    printf(
        "\n+---------------------------+"
        "\n|     CONSULTAR PRODUTO     |"
        "\n+---------------------------+"
        "\n"
    );

    if (root == NULL){
        printf("\n<* Nenhum produto cadastrado *>\n");
        return;
    }

    while (1) {
        printf("\nCodigo >> ");
        if (scanf("%d", &code) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros inteiros.\n");
            clearBuffer();
        }
    }

    Node* result = consult(root, code);

    if (result == NULL) {
        printf("\n<* Produto nao encontrado! *>\n");
        return;
    }

    printf(
        "\n+---------------------------+"
        "\n|   PRODUTOS ENCONTRADOS    |"
        "\n+---------------------------+"
        "\n"
    );

    printf(
        "\nCodigo: %d | Nome: %s | Descricao: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
        result->code, result->name, result->description, result->quantity, result->price, result->guarantee, result->supplier
    );
}

void removeProduct(Node** root) {
    int code;

    printf(
        "\n+---------------------------+"
        "\n|      REMOVER PRODUTO      |"
        "\n+---------------------------+"
        "\n"
    );

    if (*root == NULL) {
        printf("\n<* Nenhum produto cadastrado *>\n");
        return;
    }

    while (1) {
        printf("\nCodigo >> ");
        if (scanf("%d", &code) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros inteiros.\n");
            clearBuffer();
        }
    }

    Node* found = consult(*root, code);

    if (found == NULL) {
        printf("\n<* Produto nao encontrado! *>\n");
        return;
    }

    char nomeTemp[STRING_LENGHT];
    strcpy(nomeTemp, found->name); // guarda nome antes de remover
    *root = removeNode(*root, code);

    printf("\n<* Produto \"%s\" removido! *>\n", nomeTemp);

}

void listProductsInOrder(Node* root) {
    printf(
        "\n+---------------------------+"
        "\n|     LISTAGEM EM ORDEM     |"
        "\n+---------------------------+"
        "\n"
    );

    if(root == NULL){
        printf("\n<* Nenhum produto cadastrado *>\n");
        return;
    }

    inOrder(root);
    printf("\n");
}

void listProductsPreOrder(Node* root) {
    printf(
        "\n+---------------------------+"
        "\n|   LISTAGEM EM PRE ORDEM   |"
        "\n+---------------------------+"
        "\n"
    );

    if(root == NULL){
        printf("\n<* Nenhum produto cadastrado *>\n");
        return;
    }
    preOrder(root);
    printf("\n");
}

void listProductsAfterOrder(Node* root) {
    printf(
        "\n+---------------------------+"
        "\n|   LISTAGEM EM POS ORDEM   |"
        "\n+---------------------------+"
        "\n"
    );

    if(root == NULL){
        printf("\n<* Nenhum produto cadastrado *>\n");
        return;
    }

    afterOrder(root);
    printf("\n");
}

void searchByPartialDescription(Node* root, const char* query, int* foundCount) {
    if (root == NULL) return;
    searchByPartialDescription(root->left, query, foundCount);
    if (strstr(root->description, query) != NULL) {
        printf(
            "\nCodigo: %d | Nome: %s | Descricao: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->description, root->quantity, root->price, root->guarantee, root->supplier
        );
        (*foundCount)++;
    }
    searchByPartialDescription(root->right, query, foundCount);
}

void searchByPriceRange(Node* root, float min, float max, int* foundCount) {
    if (root == NULL) return;
    searchByPriceRange(root->left, min, max, foundCount);
    if (root->price >= min && root->price <= max) {
        printf(
            "\nCodigo: %d | Nome: %s | Descricao: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->description, root->quantity, root->price, root->guarantee, root->supplier
        );
        (*foundCount)++;
    } 
    searchByPriceRange(root->right, min, max, foundCount);
}

void consultProductsParcialDescription(Node* root) {
    char description[STRING_LENGHT];
    int productsCount = 0;

    printf(
        "\n+---------------------------+"
        "\n|     CONSULTAR PRODUTO     |"
        "\n+---------------------------+"
        "\n"
    );

    if (root == NULL){
        printf("\n<* Nenhum produto cadastrado *>\n");
        return;
    }

    printf("\nDescricao (parcial) >> ");
    scanf(" %[^\n]", description);

    printf(
        "\n+---------------------------+"
        "\n|  PRODUTO(S) ENCONTRADO(S) |"
        "\n+---------------------------+"
        "\n"
    );

    searchByPartialDescription(root, description, &productsCount);

    if (productsCount == 0) {
        printf("\n<* Nenhum produto encontrado *>\n");
    }

}

void consultProductsPriceRange(Node* root) {
    float min, max;
    int productsCount = 0;

    printf(
        "\n+---------------------------+"
        "\n|     CONSULTAR PRODUTO     |"
        "\n+---------------------------+"
        "\n"
    );

    if (root == NULL) {
        printf("\n<* Nenhum produto cadastrado! *>\n");
        return;
    }

    while (1) {
        printf("\nPreco minimo >> ");
        if (scanf("%f", &min) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros (use ponto para decimais, ex: 10.50).\n");
            clearBuffer();
        }
    }


    while (1) {
        printf("\nPreco maximo >> ");
        if (scanf("%f", &max) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros (use ponto para decimais, ex: 10.50).\n");
            clearBuffer();
        }
    }

    if (min > max) {
        printf("\n<* O preco minimo nao pode ser maior que o maximo! *>\n");
        return;
    }

    printf(
        "\n+---------------------------+"
        "\n| PRODUTO(S) ENCONTRADO(S)  |"
        "\n+---------------------------+"
        "\n"
    );

    searchByPriceRange(root, min, max, &productsCount);

    if (productsCount == 0) {
        printf("\n<* Nenhum produto encontrado no intervalo! *>\n");
        return;

}
}

int countNodes(Node* root) {
    if (root == NULL){
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

void countProducts(Node* root) {
    int productsCount = countNodes(root);

    printf(
        "\n+---------------------------+"
        "\n|    CONTADOR DE PRODUTOS   |"
        "\n+---------------------------+"
        "\n"
    );

    printf("\n<* %d produtos cadastrados! *>\n", productsCount);
}

// Menu
void menu(Node** root){
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
            "\n  > 6. Buscar por preco"
            "\n  > 7. Contar produtos"
            "\n  > 8. Sair"
            "\n=============================\n"
            //"\nOpcao desejada >> "
        );

        while (1) {
        printf("Opcao desejada >> ");
            if (scanf("%d", &option) == 1) {
            clearBuffer();
            break;
        } else {
            printf("Entrada invalida! Digite apenas numeros inteiros.\n");
            clearBuffer();
        }
    }

        switch (option) {
            case 1: {
                insertProduct(root);
                break;

            }
            case 2: {
                consultProduct(*root);
                break;

            }
            case 3: {
                removeProduct(root);
                break;

            }
            case 4: {
                int listOption;

                do {
                    printf(
                        "\n+---------------------------+"
                        "\n|   LISTAGEM DE PRODUTOS    |"
                        "\n+---------------------------+"
                        "\n"
                        "\n  > 1. Em ordem"
                        "\n  > 2. Pre ordem"
                        "\n  > 3. Pos ordem"
                        "\n  > 4. Sair"
                        "\n=============================\n"
                        //"\nOpcao desejada >> "
                    );
                    while (1) {
                        printf("Opcao desejada >> ");
                        if (scanf("%d", &listOption) == 1) {
                        clearBuffer();
                        break;
                    } else {
                        printf("Entrada invalida! Digite apenas numeros inteiros.\n");
                        clearBuffer();
                    }
                }

                    switch(listOption) {
                        case 1: 
                            listProductsInOrder(*root);
                            break;
                            
                        case 2: 
                            listProductsPreOrder(*root); 
                            break;

                        case 3: 
                            listProductsAfterOrder(*root); 
                            break;
                            
                        case 4: 
                            printf("\n<* Retornando ao menu... *>\n");
                            break;

                        default: 
                            printf("\n<* Opcao invalido! *>\n");
                    }

                } while(listOption != 4);

                break;
            }
            case 5: {
                consultProductsParcialDescription(*root);
                break;

            }
            case 6: {
                consultProductsPriceRange(*root);
                break;

            }
            case 7: {
                countProducts(*root);
                break;

            }
            case 8: {
                printf("\n<* Saindo... *>\n");
                break;

            }
            default:
                printf("\n<* Opcao invalido! *>\n");

                break;
        }
    } while (option != 8);
}

int main(){
    Node* root = NULL;
    menu(&root);

    return 0;
}