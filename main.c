#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <dirent.h>

int datahora();
void limpaBuffer();
void criptografarSenha();
void cadastrarUsuario();
void salvarUsuarios();
void entrarNoSistema();
void criarArquivo(const char *nomearquivo);
void listarArquivos();
void cadastrarEmpresa();
void salvarEmpresas();
void cadastrarFuncionario();
void salvarFuncionarios();
void cadastrarResiduo();
void salvarResiduos();
void cadResiduo();
void consEmpresa();
void consFuncionario();
void consResiduo();
void menu();
void menuLogin();

#define MAX_USUARIOS 100
#define MAX_EMPRESAS 1000
#define MAX_FUNCIONARIOS 100
#define MAX_RESIDUOS 100

struct Usuario {
    char usuarionome[50];
    char usuariosenha[50];
};

struct Empresa {
    char razaosocial[50];
    char nomefantasia[50];
    char cnpj[15];
    char email[50];
    char pessoacontato[50];
    int ddd;
    int telefone;
    int dia;
    int mes;
    int ano;
    char rua[50];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[50];
    char cep[11];
    char arquivoresiduo[30];
};

struct Funcionario {
    char nomefun[50];
    char email[50];
    char cpf[12];
    int dia;
    int mes;
    int ano;
    int ddd;
    int telefone;
    char rua[50];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[50];
    char cep[11]; 
};

struct Residuo {
    char nomeemp[50];
    char residuogasoso[20];
    char residuonaogasoso[20];
    float quantidadegasoso;
    float quantidadenaogasoso;
    float total;
    int dia;
    int mes;
    int ano;
};

struct Usuario Usuarios[MAX_USUARIOS];
int total_usuarios = 0;

struct Empresa empresas[MAX_EMPRESAS];
int total_empresas = 0;

struct Funcionario funcionarios[MAX_FUNCIONARIOS];
int total_funcionarios = 0;

struct Residuo residuos[MAX_RESIDUOS];
int total_residuos = 0;

// Funcao que retorna a data e hora
int datahora(){
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  return asctime(timeinfo);
}

// Funcao para limpar o buffer do teclado
void limpaBuffer() {
    // Tive que usar essa função para ler nomes compostos nos inputs
    int c;

    while ( (c = getchar()) != '\n' && c != EOF ) { }
}

// Função para criptografar a senha
void criptografarSenha(char *senha) {
    // Criptografia básica de substituição
    for (int i = 0; senha[i] != '\0'; ++i) {
        senha[i] += 3; // Faz o shift de 3 posições na tabela ASCII
    }
}

// Função para cadastrar um novo usuario
void cadastrarUsuario() {
    if (total_usuarios >= MAX_USUARIOS) {
        printf("Limite de usuários atingido.\n");
        return;
    }

    printf("Digite o nome de usuario: ");
    scanf("%s", Usuarios[total_usuarios].usuarionome);
    limpaBuffer();

    printf("Digite a senha: ");
    scanf("%s", Usuarios[total_usuarios].usuariosenha);
    limpaBuffer();

    criptografarSenha(Usuarios[total_usuarios].usuariosenha);

    total_usuarios++;
    salvarUsuarios();
}

// Função para salvar os usuários em um arquivo txt
void salvarUsuarios() {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < total_usuarios; ++i) {
        fprintf(arquivo, "%s %s\n", Usuarios[i].usuarionome, Usuarios[i].usuariosenha);
    }

    fclose(arquivo);
    printf("Usuarios salvos com sucesso.\n");
}

// Função para criar o arquivo de relatorio de residuos
void criarArquivo(const char *nomearquivo) {
    FILE *arquivo;
    arquivo = fopen(nomearquivo, "a");

    fclose(arquivo);
    printf("Arquivo criado com sucesso.\n");
}

// Função para listar os arquivos existentes
void listarArquivos() {
    DIR *dir;
    struct dirent *entrada;

    dir = opendir(".");

    if (dir == NULL) {
        printf("Erro ao abrir o diretorio %s\n", ".");
        return;
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            printf("%s/%s\n", ".", entrada->d_name);
        }
    }

    closedir(dir);
}

// Função para cadastrar uma nova empresa
void cadastrarEmpresa() {
    system("cls");
    if (total_empresas >= MAX_EMPRESAS) {
        printf("Limite de empresas atingido.\n");
        return;
    }

    struct Empresa novaEmpresa;

    limpaBuffer();

    printf("Digite a Razao Social: ");
    scanf("%[^\n]s", &novaEmpresa.razaosocial);
    limpaBuffer();

    printf("Digite o Nome Fantasia: ");
    scanf("%[^\n]s", &novaEmpresa.nomefantasia);
    limpaBuffer();

    printf("Digite o CNPJ: ");
    scanf("%s", novaEmpresa.cnpj);
    limpaBuffer();

    printf("Digite o Email: ");
    scanf("%s", novaEmpresa.email);
    limpaBuffer();

    printf("Digite a Pessoa para Contato: ");
    scanf("%[^\n]s", &novaEmpresa.pessoacontato);
    limpaBuffer();

    printf("Digite o DDD: ");
    scanf("%d", &novaEmpresa.ddd);
    limpaBuffer();

    printf("Digite o Telefone: ");
    scanf("%d", &novaEmpresa.telefone);
    limpaBuffer();

    printf("Digite a Rua: ");
    scanf("%[^\n]s", &novaEmpresa.rua);
    limpaBuffer();

    printf("Digite o Numero: ");
    scanf("%d", &novaEmpresa.numero);
    limpaBuffer();

    printf("Digite o Bairro: ");
    scanf("%[^\n]s", &novaEmpresa.bairro);
    limpaBuffer();

    printf("Digite a Cidade: ");
    scanf("%[^\n]s", &novaEmpresa.cidade);
    limpaBuffer();

    printf("Digite o Estado: ");
    scanf("%[^\n]s", &novaEmpresa.estado);
    limpaBuffer();

    printf("Digite o CEP: ");
    scanf("%[^\n]s", &novaEmpresa.cep);
    limpaBuffer();

    printf("Digite a Data de Abertura (dia mes ano): ");
    scanf("%d %d %d", &novaEmpresa.dia, &novaEmpresa.mes, &novaEmpresa.ano);
    limpaBuffer();

    printf("Digite o Nome do Arquivo para Relatorio dos Residuos: ");
    scanf("%[^\n]s", &novaEmpresa.arquivoresiduo);
    limpaBuffer();

    empresas[total_empresas] = novaEmpresa;
    total_empresas++;

    salvarEmpresas();
}

// Função para salvar uma novo empresa no arquito txt
void salvarEmpresas() {
    FILE *arquivo;
    arquivo = fopen("empresas.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < total_empresas; ++i) {
        fprintf(arquivo, "Cadastrado em: %s \nRazao Social: %s \nNome Fantasia: %s \nCNPJ: %s \nEmail: %s \nPessoa Contato: %s \nDDD: (%d) Telefone: %d \nData de Abertura: %d-%d-%d \nRua: %s, Numero: %d, Bairro: %s \nCidade: %s - Estado: %s - CEP: %s \nNome do Arquivo: %s\n\n",
                datahora(), empresas[i].razaosocial, empresas[i].nomefantasia, empresas[i].cnpj, empresas[i].email,
                empresas[i].pessoacontato, empresas[i].ddd, empresas[i].telefone, empresas[i].dia, empresas[i].mes, 
                empresas[i].ano, empresas[i].rua, empresas[i].numero, empresas[i].bairro, empresas[i].cidade, 
                empresas[i].estado, empresas[i].cep, empresas[i].arquivoresiduo);
    }

    fclose(arquivo);
    printf("Empresa salva com sucesso.\n");
    for (int i = 0; i < total_empresas; ++i) {
        criarArquivo(empresas[i].arquivoresiduo);
    }
    system("pause");
    menu();
}

// Função para cadastrar um novo funcionario
void cadastrarFuncionario() {
    system("cls");
    if (total_funcionarios >= MAX_FUNCIONARIOS) {
        printf("Limite de funcionarios atingido.\n");
        return;
    }

    struct Funcionario novoFuncionario;

    limpaBuffer();
    
    printf("Digite o Nome do Funcionario: ");
    scanf("%[^\n]s", &novoFuncionario.nomefun);
    limpaBuffer();

    printf("Digite o Email: ");
    scanf("%s", novoFuncionario.email);
    limpaBuffer();

    printf("Digite o CPF: ");
    scanf("%s", novoFuncionario.cpf);
    limpaBuffer();
    
    printf("Digite o DDD: ");
    scanf("%d", &novoFuncionario.ddd);
    limpaBuffer();

    printf("Digite o Telefone: ");
    scanf("%d", &novoFuncionario.telefone);
    limpaBuffer();

    printf("Digite a Data de Nascimento (dia mes ano): ");
    scanf("%d %d %d", &novoFuncionario.dia, &novoFuncionario.mes, &novoFuncionario.ano);
    limpaBuffer();

    printf("Digite a Rua: ");
    scanf("%[^\n]s", &novoFuncionario.rua);
    limpaBuffer();

    printf("Digite o Numero: ");
    scanf("%d", &novoFuncionario.numero);
    limpaBuffer();

    printf("Digite o Bairro: ");
    scanf("%[^\n]s", &novoFuncionario.bairro);
    limpaBuffer();

    printf("Digite a Cidade: ");
    scanf("%[^\n]s", &novoFuncionario.cidade);
    limpaBuffer();

    printf("Digite o Estado: ");
    scanf("%[^\n]s", &novoFuncionario.estado);
    limpaBuffer();

    printf("Digite o CEP: ");
    scanf("%s", novoFuncionario.cep);
    limpaBuffer();

    funcionarios[total_funcionarios] = novoFuncionario;
    total_funcionarios++;

    salvarFuncionarios();
}

// Função para salvar o cadastro de um novo funcionario no arquivo txt
void salvarFuncionarios() {
    FILE *arquivo;
    arquivo = fopen("funcionarios.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < total_funcionarios; ++i) {
        fprintf(arquivo, "Cadastrado em: %s \nNome: %s \nE-mail: %s \nCPF: %s \nDDD: (%d) Telefone: %d \nData Nascimento: %d-%d-%d \nRua: %s, Numero: %d, Bairro: %s \nCidade: %s - Estado: %s - CEP: %s \n\n",
                datahora(), funcionarios[i].nomefun, funcionarios[i].email, funcionarios[i].cpf, funcionarios[i].ddd,
                funcionarios[i].telefone, funcionarios[i].dia, funcionarios[i].mes, funcionarios[i].ano,
                funcionarios[i].rua, funcionarios[i].numero, funcionarios[i].bairro, funcionarios[i].cidade,
                funcionarios[i].estado, funcionarios[i].cep);
    }

    fclose(arquivo);
    printf("Funcionario salvo com sucesso.\n");
    system("pause");
    menu();
}

// Função para cadastrar os residuos
void cadastrarResiduo() {

    limpaBuffer();
    printf("******************************************************\n");
    printf("*               CADASTRO DE RESIDUOS                 *\n");
    printf("*             SGSA - SISTEMA DE GESTAO               *\n");
    printf("*              DE SOLUCOES AMBIENTAIS!               *\n");
    printf("******************************************************\n");

    if (total_residuos >= MAX_RESIDUOS) {
        printf("Limite de residuos atingido.\n");
        return;
    }

    struct Residuo novoResiduo;

    printf("Digite o Nome da Empresa: ");
    scanf("%[^\n]s", novoResiduo.nomeemp);
    limpaBuffer();

    printf("Digite o Tipo de Residuo Gasoso: ");
    scanf("%[^\n]s", novoResiduo.residuogasoso);
    limpaBuffer();

    printf("Digite a Quantidade de Residuo Gasoso: ");
    scanf("%f", &novoResiduo.quantidadegasoso);
    limpaBuffer();
    
    printf("Digite o Tipo de Outros Residuo: ");
    scanf("%[^\n]s", novoResiduo.residuonaogasoso);
    limpaBuffer();

    printf("Digite a Quantidade de Outros Residuo: ");
    scanf("%f", &novoResiduo.quantidadenaogasoso);
    limpaBuffer();

    printf("Digite o valor total: ");
    scanf("%f", &novoResiduo.total);
    limpaBuffer();

    printf("Digite a data de descarte (dia mes ano): ");
    scanf("%d %d %d", &novoResiduo.dia, &novoResiduo.mes, &novoResiduo.ano);
    limpaBuffer();

    residuos[total_residuos] = novoResiduo;
    total_residuos++;

    salvarResiduos();
}

// Função para salvar o cadastro de residuou no relatorio
void salvarResiduos() {
    char nomeArquivo[100];
    FILE *arquivo;

    printf("Digite o nome do arquivo que deseja abrir: ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < total_residuos; ++i) {
        fprintf(arquivo, "Cadastrado em: %s \nEmpresa: %s \nTipo de Residuo Gasoso: %s \nQuant. Residuo Gasoso: %.2f \nTipo de Residuo Nao Gasoso: %s \nQuantidade de Residuo Nao Gasoso: %.2f \nResiduo Total: %.2f \nData da Coleta: %d-%d-%d\n\n",
                datahora(), residuos[i].nomeemp, residuos[i].residuogasoso, residuos[i].quantidadegasoso, 
                residuos[i].residuonaogasoso, residuos[i].quantidadenaogasoso, residuos[i].total, 
                residuos[i].dia, residuos[i].mes, residuos[i].ano);
    }

    fclose(arquivo);
    printf("Residuos salvos com sucesso.\n");
    system("pause");
    menu();
}

// Função para consultar as empresas
void consEmpresa(){
    system("cls");
    fflush(stdin);
    printf("******************************************************\n");
    printf("*               PROGRAMA DE SOLUCOES                 *\n");
    printf("*                    AMBIENTAIS                      *\n");
    printf("*            CONSULTAR RELATORIOS EMPRESAS           *\n");
    printf("******************************************************\n");

    FILE *file;
    file = fopen("empresas.txt", "r");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
    }

    char texto [2000];

    while (fgets(texto,2000, file) != NULL){
        printf("%s", texto);
    }
    fclose(file);

    printf("\n");

    int opcao;

    printf("\nDeseja voltar ao menu anterior?\n");
    printf("\n[1] Sim. \n[2] Nao (sair do programa).\n");
    printf("\nOpcao Escolhida: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("\nRetornando ao menu anterior...\n");
            menu();
            break;
        case 2:
            printf("\nSaindo do programa...\n");
            exit(0);
            break;
        default:
            printf("\nOpcao invalida! Tente novamente, por favor.\n\n");
            system("pause");
            consEmpresa();
    }
}

// Função para consultar os funcionarios
void consFuncionario(){
    system("cls");
    fflush(stdin);
    printf("******************************************************\n");
    printf("*               PROGRAMA DE SOLUCOES                 *\n");
    printf("*                    AMBIENTAIS                      *\n");
    printf("*          CONSULTAR RELATORIOS FUNCIONARIOS         *\n");
    printf("******************************************************\n");


    FILE *file;
    file = fopen("funcionarios.txt", "r");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
    }

    char texto [2000];

    while (fgets(texto,2000, file) != NULL){
        printf("%s", texto);
    }
    fclose(file);

    printf("\n");

    int opcao;

    printf("\nDeseja voltar ao menu anterior?\n");
    printf("\n[1] Sim. \n[2] Nao (sair do programa).\n");
    printf("\nOpcao Escolhida: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("\nRetornando ao menu anterior...\n");
            menu();
            break;
        case 2:
            printf("\nSaindo do programa...\n");
            exit(0);
            break;
        default:
            printf("\nOpcao invalida! Tente novamente, por favor.\n\n");
            system("pause");
            consFuncionario();
    }

}

// Função para consultar os relatorios de residuos
void consResiduo(){
    system("cls");
    fflush(stdin);
    printf("******************************************************\n");
    printf("*               PROGRAMA DE SOLUCOES                 *\n");
    printf("*                    AMBIENTAIS                      *\n");
    printf("*           CONSULTAR RELATORIOS RESIDUOS            *\n");
    printf("******************************************************\n");

    listarArquivos();
    
    char nomeArquivo[100];
    FILE *arquivo;

    printf("Digite o nome do arquivo que deseja abrir: ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
    }

    char texto [2000];

    while (fgets(texto,2000, arquivo) != NULL){
        printf("%s", texto);
    }
    fclose(arquivo);

    printf("\n");

    int opcao;

    printf("\nDeseja voltar ao menu anterior?\n");
    printf("\n[1] Sim. \n[2] Nao (sair do programa).\n");
    printf("\nOpcao Escolhida: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("\nRetornando ao menu anterior...\n");
            menu();
            break;
        case 2:
            printf("\nSaindo do programa...\n");
            exit(0);
            break;
        default:
            printf("\nOpcao invalida! Tente novamente, por favor.");
            consResiduo();
    }

}

// Menu
void menu(){
    
	int opcao;

    printf("******************************************************\n");
    printf("*                    MENU - SGSA                     *\n");
    printf("*                 SISTEMA DE GESTAO                  *\n");
    printf("*               DE SOLUCOES AMBIENTAIS!              *\n");
    printf("******************************************************\n");

    printf("\nEscolha a opcao desejada: \n");
	printf("10 - Cadastros.\n");
	printf("  11 - Cadastrar empresas.\n");
	printf("  12 - Cadastrar funcionarios.\n");
	printf("  13 - Cadastrar residuos ambientais.\n");
	printf("20 Consultas. \n");
	printf("  21 - Consultar empresas.\n");
    printf("  22 - Consultar funcionarios.\n");
    printf("  23 - Consultar cadastros de residuos ambientais.\n");
	printf("30 - Logoff.\n");
	printf("\nOpcao Escolhida: ");
	scanf("%d", &opcao);

	switch(opcao){
		case 11:
            cadastrarEmpresa();
			break;
        case 12:
			cadastrarFuncionario();
			break;
        case 13:
            listarArquivos();
            system("pause");
            cadastrarResiduo();
            break;
		case 21:
			consEmpresa();
			break;
        case 22:
            consFuncionario();
            break;
        case 23:
            consResiduo();
            break;
		case 30:
			printf("\nRedirecionando para menu...\n");
			menuLogin();
		default:
			printf("\nOpcao invalida! Tente novamente.\n\n");
			system("pause");
			menu();
	}
}

// Função para verificar as credenciais e entrar no sistema
void entrarNoSistema() {
    char usuarionome[50];
    char usuariosenha[50];
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o nome de usuario: ");
    scanf("%s", usuarionome);
    limpaBuffer();
    printf("Digite a senha: ");
    scanf("%s", usuariosenha);
    limpaBuffer();

    criptografarSenha(usuariosenha);

    char file_usuarionome[50];
    char file_usuariosenha[50];
    int found = 0;

    while (fscanf(arquivo, "%s %s", file_usuarionome, file_usuariosenha) != EOF) {
        if (strcmp(usuarionome, file_usuarionome) == 0 && strcmp(usuariosenha, file_usuariosenha) == 0) {
            printf("Login bem-sucedido!\n");
            found = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!found) {
        printf("Usuario ou senha incorretos.\n");
    } else {
        menu();
    }
}

// Funcao para apresentar em tela o menu par acesso ao sistema ou criar usuario
void menuLogin() {
    system("cls");
    int opcao;

    do {
        printf("\n===================================== Menu =====================================\n");
        printf("1. Cadastrar novo usuario\n");
        printf("2. Entrar no sistema\n");
        printf("3. Fechar Sistema\n");
        printf("Escolha uma opcao: ");
        printf("\n=== 2024 - Desenvolvido por Rogerio Fabricio de Almeida Santos - PIM IV UNIP ===\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                entrarNoSistema();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 3);
    
    exit(0);
}

int main(){
    setlocale(LC_ALL,"Portuguese");
    menuLogin();
}