# 🌟 TechInfo: Sistema de Gerenciamento de Inventário (BST)

O **TechInfo** é um sistema de gerenciamento de estoque e catálogo de produtos desenvolvido em **Linguagem C**. Ele utiliza a estrutura de dados **Árvore Binária de Busca (BST)** para otimizar operações cruciais de inventário, como a inserção, consulta e remoção de produtos, usando o código único do item como chave de ordenação.

---

## 🌳 Estrutura de Dados e Eficiência

O projeto alcançou seus objetivos ao permitir a compreensão profunda e a aplicação prática das **Árvores Binárias de Busca (BST)**.

* **Eficiência Logarítmica:** A BST garante operações de **inserção, consulta e remoção** rápidas, com complexidade de $O(\log n)$ no caso médio.
* **Algoritmos Complexos:** Demonstra domínio sobre algoritmos que exigem alta complexidade, como a **remoção de nó** (`removeNode`), que gerencia três cenários para manter a integridade da árvore. 
* **Buscas Avançadas:** Implementou buscas por atributos não-chave (**descrição parcial** e **faixa de preço**), que exigem varredura e filtragem inteligentes dos nós.

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C
* **Compilador:** GCC (Recomendado)

---

## 💻 Manual do Usuário

Este manual detalha como compilar, executar e testar as funcionalidades principais do sistema TechInfo.

### 1. Compilação e Execução

Para compilar o projeto, salve o código em um arquivo `.c` (ex: `inventario.c`) e utilize o GCC:

1.  **Compilar:**
    ```bash
    gcc main.c -o techinfo
    ```
2.  **Executar:**
    ```bash
    ./techinfo
    ```

### 2. Menu Principal

O sistema TechInfo opera a partir de um menu interativo, utilizando o código do produto como chave primária.

| Opção | Ação |
| :--- | :--- |
| **1** | Inserir Produto |
| **2** | Consultar Produto (por código) |
| **3** | Remover Produto |
| **4** | Listar Produto (sub-menu) |
| **5** | Buscar por Descrição |
| **6** | Buscar por Preço |
| **7** | Contar Produtos |
| **8** | Sair |

### 3. Fluxo de Teste Sugerido

Para validar as funcionalidades, siga este fluxo de teste:

#### 3.1. Teste de Inserção (Opção 1) ➕

Insira pelo menos 3 produtos diferentes. **Exemplo:**

| Código | Nome | Quantidade | Preço | Descrição |
| :--- | :--- | :--- | :--- | :--- |
| **50** | Mouse Gamer | 10 | 120.50 | Periférico de alta precisão. |
| **25** | Teclado Mecânico | 5 | 350.00 | Periférico com switch azul. |
| **75** | Monitor Curvo | 2 | 1500.99 | Tela de 27 polegadas. |

* **Teste de Duplicata:** Tente inserir um produto com o código **50** novamente. O sistema deve retornar **`<* Codigo ja existente, tente novamente! *>`**.

#### 3.2. Teste de Listagem (Opção 4) 📜

1.  Selecione **Opção 4** (Listar produto) e, em seguida, **Opção 1** (Em ordem).
2.  **Resultado Esperado:** A listagem deve seguir a ordem crescente dos códigos (**25, 50, 75**), confirmando a ordenação da BST.

#### 3.3. Teste de Remoção (Opção 3) 🗑️

1.  Selecione **Opção 3** (Remover produto).
2.  Remova o código **50** (nó com dois filhos, testando o algoritmo mais complexo).
3.  **Resultado Esperado:** O sistema deve confirmar a remoção e, ao listar novamente (Opção 4), o código **50** não deve mais estar presente.

#### 3.4. Teste de Busca Avançada (Opção 5 e 6) 🔎

* **Descrição (Opção 5):** Busque pela palavra-chave `Periférico`. O sistema deve listar o Mouse e o Teclado.
* **Faixa de Preço (Opção 6):** Busque por Mínimo: `100.00` e Máximo: `400.00`. O sistema deve listar o Mouse e o Teclado.

---

## 🎓 Conclusão

O projeto foi um sucesso na aplicação prática de estruturas de dados avançadas. A inclusão de validação de entrada e funções de limpeza de buffer (`clearBuffer`) confere ao sistema maior robustez e estabilidade.
