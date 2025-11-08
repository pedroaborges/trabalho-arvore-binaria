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
	    return root;
    } else {
        if (newNode->code > root->code) {
		    root->right = insert(root->right, newNode);
	        return root;
	    } else {
            printf("\n<* Codigo existente! *>\n");
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
        }

        Node* temp = smallestValue(root->right); 
        root->code = temp->code;
        root->right = removeNode(root->right, temp->code);
    }

    return root;
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf(
            "\nCodigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->quantity, root->price, root->guarantee, root->supplier
        );

        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);

        printf(
            "\nCodigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->quantity, root->price, root->guarantee, root->supplier
        );

        inOrder(root->right);
    }

}

void afterOrder(Node* root) {
    if (root != NULL) {
        afterOrder(root->left);
        afterOrder(root->right);

        printf(
            "\nCodigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
            root->code, root->name, root->quantity, root->price, root->guarantee, root->supplier
        );
    }
}

// Menu Functions
Node* insertProduct(Node* root) {
    char name[STRING_LENGHT], description[STRING_LENGHT], supplier[STRING_LENGHT];
    int code, quantity, guarantee;
    float price; 

    printf(
        "\n+---------------------------+"
        "\n|      INSERIR PRODUTO      |"
        "\n+---------------------------+"
        "\n"
    );

    printf("\nCodigo >> ");
    scanf("%d", &code);

    printf("\nNome >> ");
    scanf(" %[^\n]", &name);

    printf("\nDescricao >> ");
    scanf(" %[^\n]", &description);

    printf("\nQuantidade >> ");
    scanf("%d", &quantity);

    printf("\nPreco >> ");
    scanf("%f", &price);

    printf("\nGarantia (meses) >> ");
    scanf("%d", &guarantee);

    printf("\nFornecedor >> ");
    scanf(" %[^\n]", &supplier);

    printf("\n<* Produto cadastrado! *>\n");

    Node* newNode = createNode(code, name, description, quantity, price, guarantee, supplier);
    root = insert(root, newNode);
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

    printf("\nCodigo >> ");
    scanf("%d", &code);

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
        "\nCodigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f",
        result->code, result->name, result->quantity, result->price
    );
}

void removeProduct(Node* root) {
    int code;

    printf(
        "\n+---------------------------+"
        "\n|      REMOVER PRODUTO      |"
        "\n+---------------------------+"
        "\n"
    );

    printf("\nCodigo >> ");
    scanf("%d", &code);

    Node* result = removeNode(root, code);

    if (result == NULL) {
        printf("\n<* Produto nao encontrado! *>\n");
        return;
    }

    printf(
        "\n<* Produto %s removido! *>\n",
        result->name
    );
}

void listProductsInOrder(Node* root) {
    printf(
        "\n+---------------------------+"
        "\n|     LISTAGEM EM ORDEM     |"
        "\n+---------------------------+"
        "\n"
    );

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

    preOrder(root);
    printf("\n");
}

void listProductsAterOrder(Node* root) {
    printf(
        "\n+---------------------------+"
        "\n|   LISTAGEM EM POS ORDEM   |"
        "\n+---------------------------+"
        "\n"
    );

    afterOrder(root);
    printf("\n");
}

void consultProductsParcialDescription(Node* root) {
    char description[STRING_LENGHT];
    int productsCount = 0;
    Node* current = root;

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
    scanf(" %[^\n]", &description);

    printf(
        "\n+---------------------------+"
        "\n|  PRODUTO(S) ENCONTRADO(S) |"
        "\n+---------------------------+"
        "\n"
    );

    while (current && current->left != NULL) {
        if (strstr(root->description, description) != NULL) {
            printf(
                "\nCodigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f\n",
                current->code, current->name, current->quantity, current->price
            );
            productsCount++;
        }

        current = current->left;
    }

    if (productsCount == 0) {
        printf("\n<* Nenhum produto cadastrado *>\n");
    }
}

void consultProductsPriceRange(Node* root) {
    Node* current = root;
    float min, max;

    printf(
        "\n+---------------------------+"
        "\n|     CONSULTAR PRODUTO     |"
        "\n+---------------------------+"
        "\n"
    );

    printf("\nPreco minimo >> ");
    scanf("%f", &min);

    printf("\nPreco maximo >> ");
    scanf("%f", &max);

    printf(
        "\n+---------------------------+"
        "\n| PRODUTO(S) ENCONTRADO(S)  |"
        "\n+---------------------------+"
        "\n"
    );

    if (root == NULL) {
        printf("\n<* Nenhum produto cadastrado! *>\n");
        return;
    }

    while (current && current->left != NULL) {
        if(current->price >= min && current->price <= max) {
            printf(
                "\nCodigo: %d | Nome: %s | Quantidade: %d | Preco: R$%.2f | Garantia: %d meses | Fornecedor: %s\n",
                root->code, root->name, root->quantity, root->price, root->guarantee, root->supplier
            );
        }

        current = current->left;
    }
}

void countProducts(Node* root) {
    int productsCount = 0;
    Node* current = root;

    printf(
        "\n+---------------------------+"
        "\n|    CONTADOR DE PRODUTOS   |"
        "\n+---------------------------+"
        "\n"
    );

    if (root == NULL) {
        printf("\n<* Nenhum produto cadastrado! *>\n");
        return;
    }

    while (current && current->left != NULL) {
        current = current->left;
        productsCount++;
    }

    printf(
        "\n<* %d produtos cadastrados! *>\n",
        productsCount
    );
}

// Menu
void menu(Node* root){
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
            "\n============================="
            "\nOpcao desejada >> "
        );
        scanf("%d", &option);

        switch (option) {
            case 1: {
                insertProduct(root);
                break;

            }
            case 2: {
                consultProduct(root);
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
                        "\n============================="
                        "\nOpcao desejada >> "
                    );
                    scanf("%d", &listOption);

                    switch(listOption) {
                        case 1: 
                            listProductsInOrder(root);
                            break;
                            
                        case 2: 
                            listProductsPreOrder(root); 
                            break;

                        case 3: 
                            listProductsAterOrder(root); 
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
                consultProductsParcialDescription(root);
                break;

            }
            case 6: {
                consultProductsPriceRange(root);
                break;

            }
            case 7: {
                countProducts(root);
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

void main(){
    Node* root = NULL;
    menu(root);
}