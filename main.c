// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Configuracoes
#define STRING_LENGHT 100

// Estrutura do No
typedef struct Node {
    int code;                           
    char name[STRING_LENGHT];           
    char description[STRING_LENGHT];    
    int quantity;                       
    float price;                        
    int guarantee;                      // Opcional: garantia
    char supplier[STRING_LENGHT];       // Opcional: fornecedor
    struct Node* left;                  
    struct Node* right;                 
} Node;

/*
 * Função: createNode
 * Descrição: Cria um novo nó de produto com os dados informados.
 * Parâmetros:
 *     code - código único do produto.
 *     name - nome do produto.
 *     description - descrição do produto.
 *     quantity - quantidade em estoque.
 *     price - preço do produto.
 *     guarantee - garantia em meses.
 *     supplier - nome do fornecedor.
 * Retorna:
 *     Ponteiro para o novo nó criado.
 */
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

/*
 * Função: insert
 * Descrição: Insere um novo nó na árvore binária de busca, respeitando a ordenação por código.
 * Parâmetros:
 *     root - nó raiz da árvore.
 *     newNode - nó a ser inserido.
 * Retorna:
 *     Ponteiro para a nova raiz da árvore.
 */
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

/*
 * Função: consult
 * Descrição: Busca um produto pelo código informado.
 * Parâmetros:
 *     root - nó raiz da árvore.
 *     code - código do produto a ser consultado.
 * Retorna:
 *     Ponteiro para o nó encontrado ou NULL se não existir.
 */
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

/*
 * Função: smallestValue
 * Descrição: Encontra o nó com o menor valor de código.
 * Parâmetros:
 *     root - nó raiz.
 * Retorna:
 *     Ponteiro para o nó de menor código.
 */
Node* smallestValue(Node* root) {
    Node* current = root;

    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

/*
 * Função: removeNode
 * Descrição: Remove um nó da árvore binária mantendo a ordenação.
 * Parâmetros:
 *     root - nó raiz da árvore.
 *     code - código do produto a ser removido.
 * Retorna:
 *     Ponteiro para a nova raiz da árvore.
 */
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

/*
 * Funções: preOrder
 * Descrição: Realiza percurso na árvore (pré ordem).
 * Parâmetros:
 *     root - nó raiz.
 * Retorna:
 *     void
 */
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

/*
 * Funções: inOrder
 * Descrição: Realiza percurso na árvore (em ordem).
 * Parâmetros:
 *     root - nó raiz.
 * Retorna:
 *     void
 */
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

/*
 * Funções: afterOrder
 * Descrição: Realiza percurso na árvore (pós-ordem).
 * Parâmetros:
 *     root - nó raiz.
 * Retorna:
 *     void
 */
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

/*
 * Função: clearBuffer
 * Descrição: Limpa o buffer do teclado após uso do scanf.
 * Parâmetros:
 *     Nenhum
 * Retorna:
 *     void
 */
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Função: insertProduct
 * Descrição: Solicita dados do usuário e insere um novo produto na árvore.
 * Parâmetros:
 *     root - ponteiro duplo para o nó raiz.
 * Retorna:
 *     void
 */
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

/*
 * Função: consultProduct
 * Descrição: Consulta um produto na árvore pelo código.
 * Parâmetros:
 *     root - nó raiz da árvore.
 * Retorna:
 *     void
 */
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

/*
 * Função: removeProduct
 * Descrição: Remove um produto da árvore pelo código.
 * Parâmetros:
 *     root - ponteiro duplo para a raiz.
 * Retorna:
 *     void
 */
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

/*
 * Funções: listProductsInOrder
 * Descrição: Exibe um cabeçalho e chama a função inOrder para listar os produtos 
 * em ordem crescente de código.
 * Parâmetros:
 *     root - nó raiz.
 * Retorna:
 *     void
 */
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

/*
 * Funções: listProductsPreOrder
 * Descrição: Exibe um cabeçalho e chama a função preOrder para listar os produtos 
 * na ordem Raiz, Esquerda, Direita.
 * Parâmetros:
 *     root - nó raiz.
 * Retorna:
 *     void
 */
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

/*
 * Funções: listProductsAfterOrder
 * Descrição: Exibe um cabeçalho e chama a função afterOrder para listar os produtos 
 * na ordem Esquerda, Direita, Raiz.
 * Parâmetros:
 *     root - nó raiz.
 * Retorna:
 *     void
 */
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

/*
 * Função: searchByPartialDescription
 * Descrição: Percorre a árvore (em ordem) e imprime os produtos cuja descrição 
 * contém a substring de consulta informada. Utiliza a função 'strstr' para 
 * verificar a ocorrência da substring.
 * Parâmetros:
 *     root - nó raiz da subárvore atual.
 *     query - string parcial a ser buscada na descrição.
 *     foundCount - ponteiro para um contador de produtos encontrados.
 * Retorna:
 *     void
 */
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

/*
 * Função: searchByPriceRange
 * Descrição: Percorre a árvore (em ordem) e imprime os produtos cujo preço está 
 * dentro do intervalo [min, max] informado, incluindo os limites.
 * Parâmetros:
 *     root - nó raiz da subárvore atual.
 *     min - preço mínimo do intervalo.
 *     max - preço máximo do intervalo.
 *     foundCount - ponteiro para um contador de produtos encontrados.
 * Retorna:
 *     void
 */
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

/*
 * Função: consultProductsParcialDescription
 * Descrição: Gerencia a interface para a busca por descrição parcial. Solicita a 
 * descrição ao usuário e chama 'searchByPartialDescription' para realizar a busca.
 * Exibe o número de produtos encontrados ou uma mensagem de "não encontrado".
 * Parâmetros:
 *     root - nó raiz da árvore.
 * Retorna:
 *     void
 */
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

/*
 * Função: consultProductsPriceRange
 * Descrição: Gerencia a interface para a busca por faixa de preço. Solicita os 
 * preços mínimo e máximo, valida o intervalo e chama 'searchByPriceRange' para a busca.
 * Exibe os resultados ou uma mensagem de "não encontrado no intervalo".
 * Parâmetros:
 *     root - nó raiz da árvore.
 * Retorna:
 *     void
 */
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

/*
 * Função: countNodes
 * Descrição: Calcula recursivamente o número total de nós (produtos) na árvore 
 * binária. É a implementação da lógica de contagem.
 * Parâmetros:
 *     root - nó raiz da subárvore atual.
 * Retorna:
 *     O número total de nós na subárvore.
 */
int countNodes(Node* root) {
    if (root == NULL){
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

/*
 * Função: countProducts
 * Descrição: Função de interface. Chama a função recursiva 'countNodes' para obter 
 * o total de produtos cadastrados e exibe este número ao usuário de forma amigável.
 * Parâmetros:
 *     root - nó raiz da árvore.
 * Retorna:
 *     void
 */
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

/*
 * Função: menu
 * Descrição: Exibe o menu principal da aplicação (TechInfo), lendo a opção 
 * do usuário e direcionando para a função correspondente.
 * Parâmetros:
 *  root - ponteiro duplo para o nó raiz, permitindo a modificação da raiz.
 * Retorna:
 *  void
 */
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
                        "\n  > 4. Retornar ao menu"
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

/*
 * Função: main
 * Descrição: Ponto de entrada do programa. Inicializa a raiz da árvore binária 
 * de busca (BST) como NULL e chama a função menu.
 * Parâmetros:
 *  Nenhum
 * Retorna:
 *  0 
 */
int main(){
    Node* root = NULL;
    menu(&root);

    return 0;
}