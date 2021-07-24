#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structs
typedef struct jogador
{
    int id;
    char nome[50];
    char posicao[4];
    int idade;
    int pontuacao_jogador;
    int total_kill;
    int total_assist;
    int total_morte;
} jogador_t;

typedef struct team
{
    char nome_team[50];
    char nome_tecnico[50];
} team_t;

typedef struct jogadores_partida
{
    int id_jogador;
    int num_assistencias;
    int num_kills;
    int num_deaths;
    int pontuacaofinal;
} jogador_partida_t;

typedef struct partida
{
    bool vitoria;
    int ponto_destaque;
    char posicao_destaque[4];
    char nome_destaque[50];

    // Dados do time
    int kills_time;
    int mortes_time;
    int torres_destruidas;

    // Dados do time adversário
    int kills_adversario;
    int mortes_adversario;
    int torres_destruidas_adv;

    // Dados dos jogadores 
    jogador_partida_t jogadores_por_partida[5];
} partida_t;

// Funções
bool verifica_opcao_menu(int opcao_menu);

// Case 1
int pede_nome_tecnico(char nome_team[50], char nome_tecnico[50]);
int pede_jogadores(char nome[50], char posicao[4], int *idade, int i);

// Case 2
int lista_time(int id, char nome[50], char posicao[4]);

// Case 3
int editar_jogador(int id, char nome[50], char posicao[4], int idade, int escolhido);

// Case 4
bool verifica_vitoria(char res);

// Case 5
int printa_dados_partida(int kills_time, int mortes_time, int torres_destruidas, int torres_destruidas_adv);
int printa_destaque(char posicao_destaque[4], char nome_destaque[50]);

// Case 6
int apresenta_informacao_jogador(int id, char nome[50], int idade, char posicao[4]);
int apresenta_estatisticas_jogador(int total_kill, int total_assist, int total_morte);

// Case 7
int printa_kill_assist(int soma_kills, int soma_assist);

// Case 8
bool menor_pontuacao(int pontuacao_jogador, int menorpt);

// Início
int main(void)
{
    // Criação de variáveis
    team_t team;
    jogador_t jogadores[5];
    jogador_partida_t jogadores_por_partida[5];
    partida_t partidas[100];

    int numero_de_partidas = 0, soma_kills = 0, soma_assist = 0, menorpt = 1000, maiorpt = 0, id_menor = 0, id_maior = 0;
    bool eh_maior = false, eh_menor = false;

    // Iniciar dados dos jogadores = 0
    int w = 0;
    for (w = 0; w < 5; w++)
    {
        jogadores[w].pontuacao_jogador = 0;
        jogadores[w].total_assist = 0;
        jogadores[w].total_kill = 0;
        jogadores[w].total_morte = 0;
    }

    // Menu
    int opcao_menu = 0;
    do
    {
        printf("\n\nMenu de opções:");
        printf("\n1) Cadastrar time");
        printf("\n2) Listar time");
        printf("\n3) Editar time");
        printf("\n4) Cadastrar partida");
        printf("\n5) Listar partidas");
        printf("\n6) Pesquisar jogador");
        printf("\n7) Mostrar número total de kills e assistências");
        printf("\n8) Mostrar jogador com menor pontuação");
        printf("\n9) Mostrar jogador com maior pontuação");
        printf("\n10) Sair\n\n");
        scanf("%d", &opcao_menu);

        // Verificar se opção é válida
        bool verificacao = false;
        verificacao = verifica_opcao_menu(opcao_menu);

        // Organização das funções do menu
        if (verificacao == true)
        {
            switch (opcao_menu)
            {
                case 1:
                    // Pedir nome do time e do técnico
                    pede_nome_tecnico(team.nome_team, team.nome_tecnico);

                    // Pedir nome e dados dos jogadores
                    int i = 0;
                    for (i = 0; i < 5; i++)
                    {
                        // Preenche automaticamente id
                        jogadores[i].id = i + 1;

                        // Outros dados
                        pede_jogadores(jogadores[i].nome, jogadores[i].posicao, &jogadores[i].idade, i);
                    }

                    break;

                case 2:
                    // Apresentar nomes
                    printf("Time: %s\n", team.nome_team);
                    setbuf(stdin, NULL);
                    printf("Técnico: %s\n\n", team.nome_tecnico);
                    setbuf(stdin, NULL);

                    // Listar jogadores
                    for (i = 0; i < 5; i++)
                    {
                        lista_time(jogadores[i].id, jogadores[i].nome, jogadores[i].posicao);
                        setbuf(stdin, NULL);
                        printf("\n");
                    }

                    break;

                case 3:
                    printf("ID do jogador: \n");

                    int escolhido = 0;
                    setbuf(stdin, NULL);
                    scanf("%d", &escolhido);

                    // Transformar o id escolhido em uma posição equivalente da string
                    int a = escolhido - 1;

                    if (escolhido <= 0 || escolhido > 5)
                    {
                        printf("Jogador inexistente ou ID inválido.");
                        break;
                    }

                    else
                    {
                        // Confirmar se deseja editar
                        printf("\n%d - %s - %s - %d\nDeseja editar? (S ou N)\n", jogadores[a].id, jogadores[a].nome, jogadores[a].posicao, jogadores[a].pontuacao_jogador);
                        char resposta;
                        setbuf(stdin, NULL);
                        scanf("%c", &resposta);
                        
                        if (resposta == 'S')
                        {
                            // Pedir dados
                            editar_jogador(jogadores[a].id, jogadores[a].nome, jogadores[a]. posicao, jogadores[a].idade, escolhido);
                            break;
                        }

                        else
                        {
                            // Caso não queira editar
                            printf("Não editado.");
                            break;
                        }                                               
                    }

                case 4:
                    numero_de_partidas++;

                    // Pedir kills
                    printf("\nKills do time: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &partidas[numero_de_partidas].kills_time);

                    while (partidas[numero_de_partidas].kills_time < 0)
                    {
                        printf("\nAlgo não está certo! Insira novamente.");
                        printf("\nKills do time: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].kills_time);
                    }

                    // Somar kills do time
                    soma_kills += partidas[numero_de_partidas].kills_time;

                    // Pedir mortes
                    printf("Mortes do time: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &partidas[numero_de_partidas].mortes_time);
                    
                    while (partidas[numero_de_partidas].mortes_time < 0)
                    {
                        printf("\nAlgo não está certo! Insira novamente.");
                        printf("\nMortes do time: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].mortes_time);
                    }

                    // Resultado
                    char res;
                    printf("\nFoi uma vitória?\nAtenção! Qualquer entrada diferente de s atribuirá derrota!\n");
                    setbuf(stdin, NULL);
                    scanf("%c", &res);
                    partidas[numero_de_partidas].vitoria = verifica_vitoria(res);

                    // Pedir torres
                    printf("Torres destruídas pelo time: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &partidas[numero_de_partidas].torres_destruidas);

                    while (partidas[numero_de_partidas].torres_destruidas > 11 || partidas[numero_de_partidas].torres_destruidas < 0)
                    {
                        printf("\nAlgo não está certo! Insira novamente.");
                        printf("\nTorres destruídas pelo time: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].torres_destruidas);
                    }
                    
                    // Dados do adversário
                    printf("\nKills adversárias: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &partidas[numero_de_partidas].kills_adversario);

                    while (partidas[numero_de_partidas].kills_adversario < 0)
                    {
                        printf("\nAlgo não está certo! Insira novamente.");
                        printf("\nKills adversárias: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].kills_adversario);
                    }
                    
                    printf("Mortes adversárias: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &partidas[numero_de_partidas].mortes_adversario);

                    while (partidas[numero_de_partidas].mortes_adversario < 0)
                    {
                        printf("\nAlgo não está certo! Insira novamente.");
                        printf("\nMortes adversárias: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].mortes_adversario);
                    }

                    printf("Torres destruídas pelo adversário: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &partidas[numero_de_partidas].torres_destruidas_adv);

                    while (partidas[numero_de_partidas].torres_destruidas_adv > 11 || partidas[numero_de_partidas].torres_destruidas_adv < 0)
                    {
                        printf("\nAlgo não está certo! Insira novamente.");
                        printf("\nTorres destruídas pelo adversário: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].torres_destruidas_adv);
                    }
                                 
                    // Preencher dado dos jogadores na partida
                    for (i = 0; i < 5; i++)
                    {
                        // Preencher automaticamente id
                        partidas[numero_de_partidas].jogadores_por_partida[i].id_jogador = i + 1;
                        printf("\nID: %d", partidas[numero_de_partidas].jogadores_por_partida[i].id_jogador);

                        // Dados individuais
                        printf("\nKills: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].jogadores_por_partida[i].num_kills);

                        while (partidas[numero_de_partidas].jogadores_por_partida[i].num_kills < 0)
                        {
                            printf("\nAlgo não está certo! Insira novamente.");
                            printf("\nKills: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &partidas[numero_de_partidas].jogadores_por_partida[i].num_kills);
                        }

                        printf("Assistências: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].jogadores_por_partida[i].num_assistencias);

                        while (partidas[numero_de_partidas].jogadores_por_partida[i].num_assistencias < 0)
                        {
                            printf("\nAlgo não está certo! Insira novamente.");
                            printf("\nAssistências: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &partidas[numero_de_partidas].jogadores_por_partida[i].num_assistencias);
                        }

                        printf("Mortes: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &partidas[numero_de_partidas].jogadores_por_partida[i].num_deaths);

                        while (partidas[numero_de_partidas].jogadores_por_partida[i].num_deaths < 0)
                        {
                            printf("\nAlgo não está certo! Insira novamente.");
                            printf("\nMortes: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &partidas[numero_de_partidas].jogadores_por_partida[i].num_deaths);
                        }

                        // Calcular pontuação final do jogador i
                        partidas[numero_de_partidas].jogadores_por_partida[i].pontuacaofinal = partidas[numero_de_partidas].jogadores_por_partida[i].num_assistencias + (3*partidas[numero_de_partidas].jogadores_por_partida[i].num_kills);

                        // Somar assistências totais do time
                        soma_assist += partidas[numero_de_partidas].jogadores_por_partida[i].num_assistencias;

                        // Acrescentar os dados inseridos ao total de kills, mortes, assist e pontuação final do jogador
                        jogadores[i].pontuacao_jogador += partidas[numero_de_partidas].jogadores_por_partida[i].pontuacaofinal;
                        jogadores[i].total_kill += partidas[numero_de_partidas].jogadores_por_partida[i].num_kills;
                        jogadores[i].total_assist += partidas[numero_de_partidas].jogadores_por_partida[i].num_assistencias;
                        jogadores[i].total_morte += partidas[numero_de_partidas].jogadores_por_partida[i].num_deaths;

                        printf("\n");

                        // Determinar o destaque da partida
                        if (partidas[numero_de_partidas].jogadores_por_partida[i].pontuacaofinal >= partidas[numero_de_partidas].ponto_destaque)
                        {
                            partidas[numero_de_partidas].ponto_destaque = partidas[numero_de_partidas].jogadores_por_partida[i].pontuacaofinal;

                            strcpy(partidas[numero_de_partidas].nome_destaque, jogadores[i].nome);
                            strcpy(partidas[numero_de_partidas].posicao_destaque, jogadores[i].posicao);
                        }
                    }
                    
                    break;

                case 5:
                    for (i = 1; i <= numero_de_partidas; i++)
                    {                        
                        printf("\n\nPartida %d: ", i);

                        if (partidas[i].vitoria == true)
                        {
                            printf("\nVitória!");                            
                        }
                        else if (partidas[i].vitoria == false)
                        {
                            printf("\nDerrota!");
                        }

                        printa_dados_partida(partidas[i].kills_time, partidas[i].mortes_time, partidas[i].torres_destruidas, partidas[i].torres_destruidas_adv);

                        printa_destaque(partidas[i].nome_destaque, partidas[i].posicao_destaque);
                    }

                    break;

                case 6:
                    printf("ID do jogador: \n");

                    int b = 0;
                    setbuf(stdin, NULL);
                    scanf("%d", &b);

                    // Transformar o id escolhido em uma posição equivalente da string
                    int escolha = b - 1;

                    if (b < 0 || b > 5)
                    {
                        printf("Jogador não existe.");
                        break;
                    }

                    else
                    {
                        apresenta_informacao_jogador(jogadores[escolha].id, jogadores[escolha].nome, jogadores[escolha].idade, jogadores[escolha].posicao);
                        apresenta_estatisticas_jogador(jogadores[escolha].total_kill, jogadores[escolha].total_assist, jogadores[escolha].total_morte);
                        break;
                    }
                    
                case 7:
                    printa_kill_assist(soma_kills, soma_assist);
                    break;

                case 8:
                    printf("\nJogador com menor pontuação:\n");

                    int y = 0;
                    for (y = 0; y < 5; y++)
                    {
                        bool eh_menor = menor_pontuacao(jogadores[y].pontuacao_jogador, menorpt);
                        if (eh_menor == true)
                        {
                            menorpt = jogadores[y].pontuacao_jogador;
                            id_menor = y+1;
                        }
                    }

                    printf("\nID: %d", jogadores[id_menor].id);
                    printf("\nNome: %s", jogadores[id_menor].nome);
                    printf("\nIdade: %d", jogadores[id_menor].idade);
                    printf("\nPosição: %s", jogadores[id_menor].posicao);
                    printf("\nKills totais: %d", jogadores[id_menor].total_kill);
                    printf("\nMortes totais: %d", jogadores[id_menor].total_morte);
                    printf("\nAssistências totais: %d", jogadores[id_menor].total_assist);
                    printf("\nPontuação total: %d", jogadores[id_menor].pontuacao_jogador);
                    
                    break;

                default:
                    break;
            }
        }
    }
    while (opcao_menu != 10);

    // Despedida </3
    printf("\nAté mais, invocador!");
    return 0;
}

// Funções
bool verifica_opcao_menu(int opcao_menu)
{
    if ((opcao_menu < 1) || (opcao_menu > 10))
    {
        printf("\n\nOpção inválida, tente novamente.\n");
        return false;
    }

    else
    {
        printf("\n\nOpção %d selecionada.\n", opcao_menu);
        return true;
    }
}

// Criar o time (case 1)
int pede_nome_tecnico(char nome_team[50], char nome_tecnico[50])
{
    printf("\nNome do time: ");
    scanf(" %[^\n]s", nome_team);

    printf("Nome do técnico: ");
    scanf(" %[^\n]s", nome_tecnico);

    return 0;
}
int pede_jogadores(char nome[50], char posicao[4], int *idade, int i)
{
    printf("\nJogador: %d", i+1);

    // Pede nome
    printf("\nNome: ");
    scanf(" %[^\n]s", nome);

    // Pede e verifica posição
    printf("Posição: ");
    scanf("%s", posicao);

    while (strcmp(posicao, "ADC") != 0 && strcmp(posicao, "SUP") != 0 && strcmp(posicao, "MID") != 0 && strcmp(posicao, "TOP") != 0 && strcmp(posicao, "JG") != 0) 
    {
        printf("\nPosição inválida.");
        printf("\nPosição: ");
        scanf("%s", posicao);
        setbuf(stdin, NULL);
    }

    // Pede e verifica idade
    printf("Idade: ");
    scanf("%d", idade);

    while ((*idade < 0) || (*idade > 150))
    {
        printf("\nIdade inválida.");
        printf("\nIdade: ");
        scanf("%d", idade);
        setbuf(stdin, NULL);
    }

    return 0;
}

// Listar o time (case 2)
int lista_time (int id, char nome[50], char posicao[4])
{
    printf("%d - %s - %s", id, nome, posicao);
    return 0;
}

// Edição de dados (case 3)
int editar_jogador(int id, char nome[50], char posicao[4], int idade, int escolhido)
{
    printf("\nInsira os novos dados.");
    
    int i = escolhido - 1;
    pede_jogadores(nome, posicao, &idade, i);

    return 0;   
}

// Vitória ou derrota (case 4)
bool verifica_vitoria(char res)
{  
    if (res == 's')
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Prints (case 5)
int printa_dados_partida(int kills_time, int mortes_time, int torres_destruidas, int torres_destruidas_adv)
{
    printf("\nKills do time: %d\nMortes do time: %d\nTorres destruídas pelo time: %d\nTorres destruídas pelo adversário: %d", kills_time, mortes_time, torres_destruidas, torres_destruidas_adv);
    return 0;
}
int printa_destaque(char posicao_destaque[4], char nome_destaque[50])
{
    printf("\nPosição destaque: %s - %s", posicao_destaque, nome_destaque);
    return 0;
}

// Print (case 6)
int apresenta_informacao_jogador(int id, char nome[50], int idade, char posicao[4])
{
    printf("\nID: %d \nNome: %s \nPosição: %s", id, nome, posicao);  
    return 0;
}
int apresenta_estatisticas_jogador(int total_kill, int total_assist, int total_morte)
{
    printf("\nKills: %d \nAssistências: %d \nMortes: %d\n", total_kill, total_assist, total_morte);
    return 0;
}

// Print (case 7)
int printa_kill_assist(int soma_kills, int soma_assist)
{
    int totalks = soma_kills + soma_assist;
    printf("\nKills do time: %d\nAssistências do time: %d\nTotal de kills e assistências: %d", soma_kills, soma_assist, totalks);

    return 0;
}

// Determinar jogador com menor pontuação (case 8)
bool menor_pontuacao(int pontuacao_jogador, int menorpt)
{
    if (pontuacao_jogador < menorpt)
    {
        return true;
    }
    else
    {
        return false;
    }
}