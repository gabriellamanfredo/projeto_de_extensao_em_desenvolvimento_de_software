#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 50
#define MAX_PRODUTOS 100
#define MAX_PEDIDOS 50
#define MAX_ITENS 200

// ---------- STRUCTS ----------
typedef struct {
    int id;
    char nome[50];
    char cpf[15];
    char email[50];
    char telefone[20];
    int ativo;
} Cliente;

typedef struct {
    int id;
    char nome[50];
    char autor[50];
    int ano;
    float preco;
    int quantidade;
    int ativo;
} Produto;

typedef struct {
    int id;
    int id_cliente;
    char data[11]; // formato: dd/mm/aaaa
    float valor_total;
    int ativo;
} Pedido;

typedef struct {
    int id;
    int id_produto;
    int id_pedido;
    int quantidade;
    float preco_unitario;
    int ativo; // para possibilitar controle futuro (ex.: marcar item como removido)
} ItemPedido;

// ---------- PROTÓTIPOS ----------
void cadastrarCliente(Cliente clientes[], int *total);
void listarClientes(Cliente clientes[], int total);
void cadastrarProduto(Produto produtos[], int *total);
void listarProdutos(Produto produtos[], int total);
void cadastrarPedido(Pedido pedidos[], ItemPedido itens[], int *totalPedidos, int *totalItens,
                     Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos);
void listarPedidos(Pedido pedidos[], ItemPedido itens[], int total, Cliente clientes[], int totalClientes, ItemPedido itensAll[], Produto produtos[], int totalProdutos);
void apagarPedido(Pedido pedidos[], ItemPedido itens[], int totalPedidos, int totalItens,
                  Produto produtos[], int totalProdutos);

// ---------- MAIN ----------
int main() {
    Cliente clientes[MAX_CLIENTES];
    Produto produtos[MAX_PRODUTOS];
    Pedido pedidos[MAX_PEDIDOS];
    ItemPedido itens[MAX_ITENS];

    int totalClientes = 0, totalProdutos = 0, totalPedidos = 0, totalItens = 0;
    int opcao;

    do {
        printf("\n=== LIVRARIA AQUARELA ===\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Cadastrar produto\n");
        printf("4. Listar produtos\n");
        printf("5. Cadastrar pedido\n");
        printf("6. Listar pedidos\n");
        printf("7. Apagar pedido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            // Limpeza de input em caso de entrada inválida
            while (getchar() != '\n');
            opcao = -1;
        }
        getchar(); // limpa o '\n' restante

        switch (opcao) {
            case 1:
                cadastrarCliente(clientes, &totalClientes);
                break;
            case 2:
                listarClientes(clientes, totalClientes);
                break;
            case 3:
                cadastrarProduto(produtos, &totalProdutos);
                break;
            case 4:
                listarProdutos(produtos, totalProdutos);
                break;
            case 5:
                cadastrarPedido(pedidos, itens, &totalPedidos, &totalItens, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 6:
                listarPedidos(pedidos, itens, totalPedidos, clientes, totalClientes, itens, produtos, totalProdutos);
                break;
            case 7:
                apagarPedido(pedidos, itens, totalPedidos, totalItens, produtos, totalProdutos);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ---------- CLIENTES ----------
void cadastrarCliente(Cliente clientes[], int *total) {
    if (*total >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    Cliente c;
    c.id = *total + 1;
    printf("\n--- Cadastro de Cliente ---\n");
    printf("Nome: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';
    printf("CPF: ");
    fgets(c.cpf, sizeof(c.cpf), stdin);
    c.cpf[strcspn(c.cpf, "\n")] = '\0';
    printf("E-mail: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = '\0';
    printf("Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';
    c.ativo = 1;

    clientes[*total] = c;
    (*total)++;
    printf("Cliente cadastrado com sucesso! (ID: %d)\n", c.id);
}

void listarClientes(Cliente clientes[], int total) {
    printf("\n--- Lista de Clientes ---\n");
    if (total == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        if (clientes[i].ativo) {
            printf("ID: %d | Nome: %s | CPF: %s | Email: %s | Telefone: %s\n",
                   clientes[i].id, clientes[i].nome, clientes[i].cpf,
                   clientes[i].email, clientes[i].telefone);
        }
    }
}

// ---------- PRODUTOS ----------
void cadastrarProduto(Produto produtos[], int *total) {
    if (*total >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    Produto p;
    p.id = *total + 1;
    printf("\n--- Cadastro de Produto ---\n");
    printf("Nome do livro: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';
    printf("Autor: ");
    fgets(p.autor, sizeof(p.autor), stdin);
    p.autor[strcspn(p.autor, "\n")] = '\0';
    printf("Ano: ");
    if (scanf("%d", &p.ano) != 1) { while (getchar() != '\n'); p.ano = 0; }
    printf("Preco: ");
    if (scanf("%f", &p.preco) != 1) { while (getchar() != '\n'); p.preco = 0.0f; }
    printf("Quantidade em estoque: ");
    if (scanf("%d", &p.quantidade) != 1) { while (getchar() != '\n'); p.quantidade = 0; }
    getchar();
    p.ativo = 1;

    produtos[*total] = p;
    (*total)++;
    printf("Produto cadastrado com sucesso! (ID: %d)\n", p.id);
}

void listarProdutos(Produto produtos[], int total) {
    printf("\n--- Lista de Produtos ---\n");
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        if (produtos[i].ativo) {
            printf("ID: %d | Livro: %s | Autor: %s | Ano: %d | Preco: R$ %.2f | Estoque: %d\n",
                   produtos[i].id, produtos[i].nome, produtos[i].autor,
                   produtos[i].ano, produtos[i].preco, produtos[i].quantidade);
        }
    }
}

// ---------- PEDIDOS ----------
void cadastrarPedido(Pedido pedidos[], ItemPedido itens[], int *totalPedidos, int *totalItens,
                     Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos) {

    if (*totalPedidos >= MAX_PEDIDOS) {
        printf("Limite de pedidos atingido!\n");
        return;
    }
    if (totalClientes == 0) {
        printf("Necessario ter clientes cadastrados antes de criar um pedido!\n");
        return;
    }
    if (totalProdutos == 0) {
        printf("Necessario ter produtos cadastrados antes de criar um pedido!\n");
        return;
    }

    Pedido ped;
    ped.id = *totalPedidos + 1;
    ped.ativo = 1;
    ped.valor_total = 0.0f;

    printf("\n--- Cadastro de Pedido ---\n");
    printf("Digite o ID do cliente: ");
    if (scanf("%d", &ped.id_cliente) != 1) { while (getchar() != '\n'); printf("Entrada invalida.\n"); return; }
    getchar();

    // valida cliente
    int clienteValido = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id == ped.id_cliente && clientes[i].ativo) {
            clienteValido = 1;
            break;
        }
    }
    if (!clienteValido) {
        printf("Cliente nao encontrado ou inativo.\n");
        return;
    }

    printf("Data do pedido (dd/mm/aaaa): ");
    fgets(ped.data, sizeof(ped.data), stdin);
    ped.data[strcspn(ped.data, "\n")] = '\0';

    int continuar = 1;
    while (continuar) {
        if (*totalItens >= MAX_ITENS) {
            printf("Limite de itens atingido! Nao e possivel adicionar mais itens.\n");
            break;
        }

        ItemPedido item;
        item.id = *totalItens + 1;
        item.id_pedido = ped.id;
        item.ativo = 1;

        printf("\nID do produto: ");
        if (scanf("%d", &item.id_produto) != 1) { while (getchar() != '\n'); printf("Entrada invalida.\n"); break; }
        printf("Quantidade: ");
        if (scanf("%d", &item.quantidade) != 1) { while (getchar() != '\n'); printf("Entrada invalida.\n"); break; }

        // procurar produto e validar estoque
        int encontrado = 0;
        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].id == item.id_produto && produtos[i].ativo) {
                encontrado = 1;
                if (produtos[i].quantidade < item.quantidade) {
                    printf("Estoque insuficiente. Disponivel: %d\n", produtos[i].quantidade);
                } else {
                    item.preco_unitario = produtos[i].preco;
                    // atualiza estoque
                    produtos[i].quantidade -= item.quantidade;
                    // adiciona item ao vetor
                    itens[*totalItens] = item;
                    (*totalItens)++;
                    // acumula valor
                    ped.valor_total += item.preco_unitario * item.quantidade;
                    printf("Item adicionado. Subtotal do pedido: R$ %.2f\n", ped.valor_total);
                }
                break;
            }
        }

        if (!encontrado) {
            printf("Produto nao encontrado!\n");
        }

        printf("Adicionar outro item? (1=Sim / 0=Nao): ");
        if (scanf("%d", &continuar) != 1) { while (getchar() != '\n'); continuar = 0; }
        getchar();
    }

    pedidos[*totalPedidos] = ped;
    (*totalPedidos)++;

    printf("Pedido cadastrado com sucesso! ID Pedido: %d | Valor total: R$ %.2f\n", ped.id, ped.valor_total);
}

void listarPedidos(Pedido pedidos[], ItemPedido itens[], int total, Cliente clientes[], int totalClientes, ItemPedido itensAll[], Produto produtos[], int totalProdutos) {
    printf("\n--- Lista de Pedidos ---\n");
    if (total == 0) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        if (!pedidos[i].ativo) continue;

        // nome do cliente
        char nomeCliente[50] = "Desconhecido";
        for (int j = 0; j < totalClientes; j++) {
            if (clientes[j].id == pedidos[i].id_cliente) {
                strcpy(nomeCliente, clientes[j].nome);
                break;
            }
        }

        printf("\nID Pedido: %d | Cliente: %s | Data: %s | Total: R$ %.2f\n",
               pedidos[i].id, nomeCliente, pedidos[i].data, pedidos[i].valor_total);

        // listar itens do pedido
        printf("Itens:\n");
        int encontrouItem = 0;
        for (int k = 0; k < MAX_ITENS; k++) {
            // somente percorre os itens existentes; assume que itensAll contém totalItens registros válidos
            // portanto verificamos active flag e id_pedido
            if (itensAll[k].ativo && itensAll[k].id_pedido == pedidos[i].id) {
                encontrouItem = 1;
                // encontra nome do produto
                char nomeProduto[50] = "Desconhecido";
                for (int p = 0; p < totalProdutos; p++) {
                    if (produtos[p].id == itensAll[k].id_produto) {
                        strcpy(nomeProduto, produtos[p].nome);
                        break;
                    }
                }
                printf("  Item ID: %d | Produto ID: %d | Nome: %s | Qtd: %d | Preco unit: R$ %.2f | Subtotal: R$ %.2f\n",
                       itensAll[k].id, itensAll[k].id_produto, nomeProduto,
                       itensAll[k].quantidade, itensAll[k].preco_unitario,
                       itensAll[k].preco_unitario * itensAll[k].quantidade);
            }
        }
        if (!encontrouItem) {
            printf("  (Sem itens registrados ou itens removidos)\n");
        }
    }
}

// ---------- APAGAR PEDIDO ----------
void apagarPedido(Pedido pedidos[], ItemPedido itens[], int totalPedidos, int totalItens,
                  Produto produtos[], int totalProdutos) {

    int id;
    printf("\n--- Apagar Pedido ---\n");
    printf("Digite o ID do pedido que deseja apagar: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Entrada invalida.\n"); return; }
    getchar();

    // Procurar pedido
    int posPedido = -1;
    for (int i = 0; i < totalPedidos; i++) {
        if (pedidos[i].id == id && pedidos[i].ativo == 1) {
            posPedido = i;
            break;
        }
    }

    if (posPedido == -1) {
        printf("Pedido nao encontrado ou ja esta inativo!\n");
        return;
    }

    // Reverter o estoque antes de apagar
    for (int i = 0; i < totalItens; i++) {
        if (itens[i].id_pedido == id && itens[i].ativo) {
            // Localiza o produto associado ao item
            for (int p = 0; p < totalProdutos; p++) {
                if (produtos[p].id == itens[i].id_produto && produtos[p].ativo) {
                    produtos[p].quantidade += itens[i].quantidade; // devolve estoque
                    break;
                }
            }
            // opcional: marcar item como inativo (mantemos histórico)
            itens[i].ativo = 0;
        }
    }

    // Marca o pedido como apagado (inativo)
    pedidos[posPedido].ativo = 0;

    printf("Pedido apagado com sucesso! Estoque restaurado para os itens do pedido.\n");
}

