#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

/*01 - Estrutura do endereço*/
typedef struct address
{
	char logradouro[50];
	char complemento[50];
	char bairro[50];
	char cidade[50];
	char estado[50];
	char cep[9];
}address;

/*02 - Estrutura da filial*/
typedef struct branch
{
	int codigo;
	char nome[50];
	char descricao[50];
	char cnpj[15];
	address endereco;
}branch;

/*03 - Estrutura do usuário*/
typedef struct user
{
	int codigo;
	char nome[50];
	char celular[12];
	char email[100];
	char cpf[12];
	char usuario[50];
	char senha[50];
	char senha2[60];
	char status[2];
	address endereco;
}user;

/*03.1 - Estrutura do usuário*/
typedef struct user_aux
{
	int codigo;
	char nome[50];
	char celular[12];
	char email[100];
	char cpf[12];
	char usuario[50];
	char senha[50];
	char senha2[60];
	char status[2];
	address endereco;
}user_aux;

/*04 - Estrutura do paciente*/
typedef struct patient
{
	int codigo;
	char nome[50];
	char celular[12];
	char email[100];
	char cpf[12];
	char cpf_c[12];
	address endereco;
}patient;

/*05 - Estrutura do medico*/
typedef struct doctor
{
	int codigo;
	char nome[50];
	char celular[12];
	char email[100];
	char cpf[12];
	char especialidade[50];
	branch filial;
	address endereco;
}doctor;

/*06 - Estrutura do agendamento*/
typedef struct scheduling
{
	int codigo;
	char descricao[50];
	patient paciente;
	doctor medico;
	branch filial;
	char data[9];
	char hora[5];
	char periodo[50];	
	char status[2];
	int precovalor;
}scheduling;

/*06.1 - Estrutura do agendamento auxiliar*/
typedef struct scheduling_aux
{
	int codigo;
	char descricao[50];
	patient paciente;
	doctor medico;
	branch filial;
	char data[9];
	char hora[5];
	char periodo[50];	
	char status[2];
	int precovalor;
}scheduling_aux;

FILE * puser, * ppatient, * pdoctor, * pfilial, * pendereco, * plogin, * pagendamento;

/*MT MENU*/
int  main					(void);
int  main_principal			(void);
void main_cadastro			(void);
void main_consulta			(void);

/*MT MENU TELAS*/
void menu_principal			(void);
void menu_cadastros			(void);
void menu_consultas			(void);

/*MT CADASTRO TELAS*/
void cad_usuario			(void);
void cad_paciente			(void);
void cad_medico				(void);
void cad_filial				(void);
void cad_agendamento		(void);

/*MT CONSULTA TELAS*/
int con_usuario				(void);
int con_paciente			(void);
int con_filial				(void);
int con_medico				(void);
int con_agendamento			(void);

/*MT FUNÇÕES*/
int verifica_useradm		(void);
int tela_login				(void);
void tratamento_preco		(int* tpreco);
void tratamento_desc50		(char* tdesc50, int tdesc50_size);
void tratamento_cpf			(char* tcpf, int tcpf_size);
void tratamento_data		(char* tdata, int tdata_size);
void tratamento_tdta		(char* tdta, int tdta_size);
void tratamento_hora		(char* thora, int thora_size);
void tratamento_hm			(char* thm, int thm_size);
void tratamento_cnpj		(char* tcnpj, int tcnpj_size);
void tratamento_senha		(char* tsenha, int tsenha_size);
void tratamento_celular		(char* tcelular, int tcelular_size);
void tratamento_cep			(char* tcep, int tcep_size);
void criptografa_senha		(char *crip_msg, int senha_encript_size);
void incrementa_id_func		(int *IDinc);
void incrementa_id_paci		(int *IDinc_paci);
void incrementa_id_medi		(int *IDinc_medi);
void incrementa_id_fili		(int *IDinc_fili);
void incrementa_id_agen		(int *IDinc_agen);

/*-----------------------------------------------------------------------*/

/*MENU PRINCIPAL*/
int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	verifica_useradm();
	tela_login();
	main_principal();
	return 0;
}

int main_principal(void)
{
	/*---- ACESSO AOS MENU DE CADASTRO E CONSULTA ----*/
	int scan_main;

	/*Chama o menu princial*/
	menu_principal();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	scanf("%i", &scan_main);

	switch (scan_main)
		{
		case 1 : main_cadastro();		break;
		case 2 : main_consulta();		break;
		case 3 : tela_login(); 			break;
		case 4 : exit(0);
			break;
		default : printf("\nMenu inexistente, tente novamente de 1 a 3.");  
		}

	printf("\n\n");	
	getchar();
	main();
	return 0;
}

void main_cadastro(void)
{
	int scan_cad;
	scan_cad = 0;
	menu_cadastros();
	
	printf("\nSelecione uma opcao e pressione ENTER: ");
	scanf("%i", &scan_cad);

	switch (scan_cad)
	{
		case 1 : cad_usuario();		    break;
	    case 2 : cad_paciente();		break;
	    case 3 : cad_medico(); 		    break;
		case 4 : cad_filial(); 		    break;
		case 5 : cad_agendamento(); 	break;
		case 6 : main_principal();		break;
		case 7 : tela_login(); 			break;
		exit(0);
    default : printf("Menu inexistente, tente de 1 a 7.");
	}
	printf("\n\n");
	getchar();
}

void main_consulta(void)
{
	int scan_con;

	menu_consultas();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	scanf("%i", &scan_con);

	switch (scan_con)
	{
		case 1 : con_usuario();			break;
		case 2 : con_paciente();		break;
		case 3 : con_medico(); 			break;
		case 4 : con_filial(); 			break;
		case 5 : con_agendamento(); 	break;
		case 6 : main_principal();		break;
		case 7 : tela_login(); 			break;
			exit(0);
    	default : printf("Menu inexistente, tente de 1 a 7.");
	}

	printf("\n\n");
	getchar();
}

/*-----------------------------------------------------------------------*/

/*MENU TELAS*/
void menu_principal(void)
{
	setlocale(LC_ALL,""); //Para acentuação
  	printf("\033[2J\033[1;1H");

	printf("	           ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu principal                   |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Menu de cadastros                      |\n");
	printf("    |       [2] - Menu de consultas                      |\n");
	printf("    |       [3] - Logout                                 |\n");
	printf("    |       [4] - Sair do Programa                       |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");
}

void menu_cadastros(void)
{
	setlocale(LC_ALL,""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	           ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu de cadastros                |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Cadastros usuarios                     |\n");
	printf("    |       [2] - Cadastrar pacientes                    |\n");
	printf("    |       [3] - Cadastrar medicos                      |\n");
	printf("    |       [4] - Cadastrar filial                       |\n");
	printf("    |       [5] - Cadastrar agendamentos                 |\n");
	printf("    |       [6] - Voltar ao menu principal               |\n");
	printf("    |       [7] - Logout                                 |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");
  
}

void menu_consultas(void)
{
	setlocale(LC_ALL,""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	           ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu de consultas                |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Consultar usuarios                     |\n");
	printf("    |       [2] - Consultar pacientes                    |\n");
	printf("    |       [3] - Consultar medicos                      |\n");
	printf("    |       [4] - Consultar filial                       |\n");
	printf("    |       [5] - Consultar agendamentos                 |\n");
	printf("    |       [6] - Voltar ao menu principal               |\n");
	printf("    |       [7] - Logout                                 |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");

}

/*-----------------------------------------------------------------------*/

/*CADASTRO TELAS*/
void cad_usuario(void)
{
	user cfuncionario = {'\0'};
	//user_aux* cusuario_aux = calloc(1, sizeof(user_aux)* 1);

	int i, tam_msg;
	char crip_msg[50];
	
	puser = fopen("dados\\cad_funcionario.txt", "a+");
	if (puser == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE FUNCIONARIOS\n\n");

	incrementa_id_func(&cfuncionario.codigo);
	cfuncionario.codigo++;
	
	printf("Codigo de cadastro: %i\n", cfuncionario.codigo);

	printf("\nNome do funcionario: \n");
	tratamento_desc50(cfuncionario.nome, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCelular do funcionario: \n");
	tratamento_celular(cfuncionario.celular, 11);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nE-mail do funcionario: \n");
	tratamento_desc50(cfuncionario.email, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCPF do funcionario: \n");
	tratamento_cpf(cfuncionario.cpf, 12);
	fseek(stdin, 0, SEEK_END);
	
	/* 	QUANTO A ALTERACAO DE ARQUIVO ESTIVER PRONTA, USAR ESTE CARA PARA VERIFICAR SE O CPF JÁ EXISTE
	while (strcmp(cusuario_aux->cpf, cfuncionario.cpf) != 0 || *cfuncionario.cpf == '\0')
	{	
		puser = fopen("dados\\cad_funcionario.txt", "r");
		if (puser == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

		printf("\n\nCPF do funcionario: \n");
		tratamento_cpf(cfuncionario.cpf, 12);
		fseek(stdin, 0, SEEK_END);

		while (!feof(puser) && strcmp(cusuario_aux->cpf, cfuncionario.cpf) != 0)
		{
			fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cusuario_aux->codigo, cusuario_aux->nome, cusuario_aux->celular, cusuario_aux->email, cusuario_aux->cpf, cusuario_aux->usuario, cusuario_aux->senha, cusuario_aux->endereco.estado, cusuario_aux->endereco.cidade, cusuario_aux->endereco.bairro, cusuario_aux->endereco.logradouro, cusuario_aux->endereco.complemento, cusuario_aux->endereco.cep);
		}
		if(strcmp(cusuario_aux->cpf, cfuncionario.cpf) == 0)
		{
			printf("\n\nJá existe um cadastro com esse CPF!\n");		
		}
		else
		{
			break;
		}	
	}
	*/

	printf("\n\nUsuario para funcionario: \n");
	tratamento_desc50(cfuncionario.usuario, 50);
	fseek(stdin, 0, SEEK_END);

	/* ---------- TRATAMENTO NO CAMPO SENHA ---------- */	
	while(strcmp(cfuncionario.senha, cfuncionario.senha2) != 0 || strcmp(cfuncionario.senha, cfuncionario.senha2) == '\0')
	{		
		printf("\n\nSenha do usuario: \n");
		tratamento_senha(cfuncionario.senha, 50);
		fseek(stdin, 0, SEEK_END);	

		printf("\n\nDigite a senha novamente: \n");		
		tratamento_senha(cfuncionario.senha2, 50);
		fseek(stdin, 0, SEEK_END);

		if(strcmp(cfuncionario.senha, cfuncionario.senha2) != 0)
		{				
			memset(cfuncionario.senha, 0, sizeof(cfuncionario.senha));
			memset(cfuncionario.senha2, 0, sizeof(cfuncionario.senha2));
			printf("\nAs senhas nao conferem, adicione senhas iguais!\n");
		}else
		{
			printf("\n--------- Localizacao --------- \n");
			
			printf("\n\nEstado da Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.estado, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nCidade da Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.cidade, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nBairro da Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.bairro, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nLogradouro da Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.logradouro, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nComplemento da Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.complemento, 50);

			printf("\n\nCEP da Usuario: \n");
			tratamento_cep(cfuncionario.endereco.cep, 8);
			fseek(stdin, 0, SEEK_END);

			printf("\nUsuario cadastrado com sucessso!");
			break;
		}	
	}

	/*GRAVAR OS DADOS NO ARQUIVO DE TEXTO*/
	tam_msg = strlen(cfuncionario.senha);
	for (i = 0; i < tam_msg; i++)
	{
		crip_msg[i] = cfuncionario.senha[i] + 5;
	}
	crip_msg[tam_msg] = '\0';

	puser = fopen("dados\\cad_funcionario.txt", "a+");
	if (puser == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	fprintf(puser, "%i\n", cfuncionario.codigo);
	fprintf(puser, "%s\n", cfuncionario.nome);
	fprintf(puser, "%s\n", cfuncionario.celular);
	fprintf(puser, "%s\n", cfuncionario.email);
	fprintf(puser, "%s\n", cfuncionario.cpf);
	fprintf(puser, "%s\n", cfuncionario.usuario);
	fprintf(puser, "%s\n", crip_msg);
	fprintf(puser, "%s\n", cfuncionario.endereco.estado);
	fprintf(puser, "%s\n", cfuncionario.endereco.cidade);
	fprintf(puser, "%s\n", cfuncionario.endereco.bairro);
	fprintf(puser, "%s\n", cfuncionario.endereco.logradouro);
	fprintf(puser, "%s\n", cfuncionario.endereco.complemento);
	fprintf(puser, "%s\n", cfuncionario.endereco.cep);
	fclose(puser);

	getchar();
	main_cadastro();
}

void cad_paciente(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	system("mkdir dados");
	ppatient = fopen("dados\\cad_paciente.txt", "a+");
	if (ppatient == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}
	
	patient cpaciente = {'\0'};

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE PACIENTES\n\n");

	incrementa_id_paci(&cpaciente.codigo);
	cpaciente.codigo++;

	printf("Codigo de cadastro: %i\n", cpaciente.codigo);

	printf("\nNome do paciente: \n");
	tratamento_desc50(cpaciente.nome, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nTelefone do paciente: \n");
	tratamento_celular(cpaciente.celular, 11);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nE-mail do paciente: \n");
	tratamento_desc50(cpaciente.email, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCPF do paciente: \n");
	tratamento_cpf(cpaciente.cpf, 12);
	fseek(stdin, 0, SEEK_END);

	printf("\n--------- Localizacao --------- \n");
			
	printf("\n\nEstado da paciente: \n");
	tratamento_desc50(cpaciente.endereco.estado, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCidade da paciente: \n");
	tratamento_desc50(cpaciente.endereco.cidade, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nBairro da paciente: \n");
	tratamento_desc50(cpaciente.endereco.bairro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nLogradouro da paciente: \n");
	tratamento_desc50(cpaciente.endereco.logradouro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nComplemento da paciente: \n");
	tratamento_desc50(cpaciente.endereco.complemento, 50);

	printf("\n\nCEP da paciente: \n");
	tratamento_cep(cpaciente.endereco.cep, 8);
	fseek(stdin, 0, SEEK_END);

	ppatient = fopen("dados\\cad_paciente.txt", "a+");
	if (ppatient == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	/*Incrementar mais um valor no código usuário*/
	fprintf(ppatient, "%i\n", cpaciente.codigo);
	fprintf(ppatient, "%s\n", cpaciente.nome);
	fprintf(ppatient, "%s\n", cpaciente.celular);
	fprintf(ppatient, "%s\n", cpaciente.email);
	fprintf(ppatient, "%s\n", cpaciente.cpf);
	fprintf(ppatient, "%s\n", cpaciente.endereco.estado);
	fprintf(ppatient, "%s\n", cpaciente.endereco.cidade);
	fprintf(ppatient, "%s\n", cpaciente.endereco.bairro);
	fprintf(ppatient, "%s\n", cpaciente.endereco.logradouro);
	fprintf(ppatient, "%s\n", cpaciente.endereco.complemento);
	fprintf(ppatient, "%s\n", cpaciente.endereco.cep);
	fclose(ppatient);

	printf("\n\nPaciente cadastrado com sucessso!");
	getchar();
	main_cadastro();
}

void cad_medico(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	/*Ponteiros do metodo*/
	system("mkdir dados");
	pdoctor = fopen("dados\\cad_medico.txt", "a+");
	if (pdoctor == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	doctor cmedico = {'\0'};

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE MEDICOS\n\n");

	incrementa_id_medi(&cmedico.codigo);
	cmedico.codigo++;

	printf("Codigo de cadastro: %i\n", cmedico.codigo);

	printf("\nNome do medico: \n");
	tratamento_desc50(cmedico.nome, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCelular do medico: \n");
	tratamento_celular(cmedico.celular, 11);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nE-mail do medico: \n");
	tratamento_desc50(cmedico.email, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCPF do medico: \n");
	tratamento_cpf(cmedico.cpf, 12);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nEspecialidade do medico: \n");
	tratamento_desc50(cmedico.especialidade, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nFilial de atuacao do medico(CNPJ): \n");
	tratamento_cnpj(cmedico.filial.cnpj, 15);
	fseek(stdin, 0, SEEK_END);

	printf("\n\n--------- Localizacao --------- \n");
			
	printf("\n\nEstado da medico: \n");
	tratamento_desc50(cmedico.endereco.estado, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCidade da medico: \n");
	tratamento_desc50(cmedico.endereco.cidade, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nBairro da medico: \n");
	tratamento_desc50(cmedico.endereco.bairro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nLogradouro da medico: \n");
	tratamento_desc50(cmedico.endereco.logradouro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nComplemento da medico: \n");
	tratamento_desc50(cmedico.endereco.complemento, 50);

	printf("\n\nCEP da medico: \n");
	tratamento_cep(cmedico.endereco.cep, 8);
	fseek(stdin, 0, SEEK_END);

	pdoctor = fopen("dados\\cad_medico.txt", "a+");
	if (pdoctor == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}
	
	fprintf(pdoctor, "%i\n", cmedico.codigo);
	fprintf(pdoctor, "%s\n", cmedico.nome);
	fprintf(pdoctor, "%s\n", cmedico.celular);
	fprintf(pdoctor, "%s\n", cmedico.email);
	fprintf(pdoctor, "%s\n", cmedico.cpf);
	fprintf(pdoctor, "%s\n", cmedico.especialidade);
	fprintf(pdoctor, "%s\n", cmedico.filial.cnpj);
	fprintf(pdoctor, "%s\n", cmedico.endereco.estado);
	fprintf(pdoctor, "%s\n", cmedico.endereco.cidade);
	fprintf(pdoctor, "%s\n", cmedico.endereco.bairro);
	fprintf(pdoctor, "%s\n", cmedico.endereco.logradouro);
	fprintf(pdoctor, "%s\n", cmedico.endereco.complemento);
	fprintf(pdoctor, "%s\n", cmedico.endereco.cep);
	fclose(pdoctor);

	printf("\n\nMedico cadastrado com sucessso!");
	getchar();
	main_cadastro();
}

void cad_filial(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	/*Ponteiros do metodo*/
	system("mkdir dados");
	pfilial = fopen("dados\\cad_filial.txt", "a+");
	if (pfilial == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	branch cfilial = {'\0'};

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE FILIAIS\n\n");

	incrementa_id_fili(&cfilial.codigo);
	cfilial.codigo++;

	printf("Codigo de cadastro: %i\n", cfilial.codigo);

	printf("\nNome da filial: \n");
	tratamento_desc50(cfilial.nome, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCNPJ da filial: \n");
	tratamento_cnpj(cfilial.cnpj, 15);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nUma descricao sobre a filial: \n");
	tratamento_desc50(cfilial.descricao, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\n--------- Localizacao --------- \n");
			
	printf("\n\nEstado da filial: \n");
	tratamento_desc50(cfilial.endereco.estado, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCidade da filial: \n");
	tratamento_desc50(cfilial.endereco.cidade, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nBairro da filial: \n");
	tratamento_desc50(cfilial.endereco.bairro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nLogradouro da filial: \n");
	tratamento_desc50(cfilial.endereco.logradouro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nComplemento da filial: \n");
	tratamento_desc50(cfilial.endereco.complemento, 50);

	printf("\n\nCEP da filial: \n");
	tratamento_cep(cfilial.endereco.cep, 8);
	fseek(stdin, 0, SEEK_END);

	pfilial = fopen("dados\\cad_filial.txt", "a+");
	if (pfilial == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	fprintf(pfilial, "%i\n", cfilial.codigo);
	fprintf(pfilial, "%s\n", cfilial.nome);
	fprintf(pfilial, "%s\n", cfilial.cnpj);
	fprintf(pfilial, "%s\n", cfilial.descricao);
	fprintf(pfilial, "%s\n", cfilial.endereco.estado);
	fprintf(pfilial, "%s\n", cfilial.endereco.cidade);
	fprintf(pfilial, "%s\n", cfilial.endereco.bairro);
	fprintf(pfilial, "%s\n", cfilial.endereco.logradouro);
	fprintf(pfilial, "%s\n", cfilial.endereco.complemento);
	fprintf(pfilial, "%s\n", cfilial.endereco.cep);
	fclose(pfilial);

	printf("\n\nFilial cadastrada com sucessso!");
	getchar();
	main_cadastro();
}

void cad_agendamento(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	/*Ponteiros do metodo*/
	system("mkdir dados");
	pagendamento = fopen("dados\\cad_agendamento.txt", "a+");
	if (pagendamento == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	scheduling cagendamento = {'\0'};
	patient* cpaciente = calloc(1, sizeof(patient)* 1);
	doctor* cmedico = calloc(1, sizeof(doctor)* 1);
	branch* cfilial = calloc(1, sizeof(branch)* 1);
	scheduling_aux* agendamento_aux = calloc(1, sizeof(scheduling_aux)* 1);

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE AGENDAMENTOS\n\n");

	incrementa_id_agen(&cagendamento.codigo);
	cagendamento.codigo++;

	printf("Codigo de cadastro: %i\n", cagendamento.codigo);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DOS PACIENTES*/
	while (strcmp(cpaciente->cpf, cagendamento.paciente.cpf) != 0 || *cagendamento.paciente.cpf == '\0')
	{	
		ppatient = fopen("dados\\cad_paciente.txt", "r");
		if (ppatient == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

		printf("\nCPF do paciente: \n");
		tratamento_cpf(cagendamento.paciente.cpf, 12);
		fseek(stdin, 0, SEEK_END);

		while (!feof(ppatient) && strcmp(cpaciente->cpf, cagendamento.paciente.cpf) != 0) {
			fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->email, cpaciente->cpf, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep);
		}
			if(strcmp(cmedico->cpf, cagendamento.medico.cpf) != 0)
		{
			printf("\n\nCPF Invalido!\n");
			
		}
		else
		{
			break;
		}	
	}

	fclose(ppatient);
	printf("\n\nNome do paciente: \n%s\n", cpaciente->nome);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DOS MEDICOS*/
	while (strcmp(cmedico->cpf, cagendamento.medico.cpf) != 0 || *cagendamento.medico.cpf == '\0')
	{
		pdoctor = fopen("dados\\cad_medico.txt", "r");
		if (pdoctor == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

		printf("\nCPF do do Medico: \n");
		tratamento_cpf(cagendamento.medico.cpf, 12);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pdoctor) && strcmp(cmedico->cpf, cagendamento.medico.cpf) != 0) {
			fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->email, cmedico->cpf, cmedico->especialidade, cmedico->filial.cnpj, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep);
		}
		if(strcmp(cmedico->cpf, cagendamento.medico.cpf) != 0)
		{
			printf("\n\nCPF Invalido!\n");
			
		}
		else
		{
			break;
		}	
	}

	fclose(pdoctor);
	printf("\n\nNome do medico: \n%s\n", cmedico->nome);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DAS FILIAIS*/
	while (strcmp(cfilial->cnpj, cagendamento.filial.cnpj) != 0 || *cagendamento.filial.cnpj == '\0')
	{
		pfilial = fopen("dados\\cad_filial.txt", "r");
		if (pfilial == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

		memset(cagendamento.filial.cnpj, 0, sizeof(cagendamento.filial.cnpj));

		printf("\nCNPJ da filial: \n");
		tratamento_cnpj(cagendamento.filial.cnpj, 14);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pfilial) && strcmp(cfilial->cnpj, cagendamento.filial.cnpj) != 0) {
			fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
		}

		if(strcmp(cfilial->cnpj, cagendamento.filial.cnpj) != 0)
		{
			printf("\n\nCNPJ Invalido!\n");
			
		}
		else
		{
			break;
		}				
	}

	fclose(pfilial);
	printf("\n\nNome da Filial: \n%s\n", cfilial->nome);
	
	/*-----------------------------------------------------------------------*/
	
	/*CARREGAR OS DADOS DOS AGENDAMENTOS*/
	while ((strcmp(agendamento_aux->medico.cpf, cagendamento.medico.cpf) == 0 && strcmp(agendamento_aux->hora, cagendamento.hora) == 0 && strcmp(agendamento_aux->data, cagendamento.data) == 0) || (*cagendamento.data == '\0' || *cagendamento.hora == '\0'))
	{
		memset(cagendamento.data, 0, sizeof(cagendamento.data));
		memset(cagendamento.hora, 0, sizeof(cagendamento.hora));

		printf("\nData do agendamento: \n");
		tratamento_tdta(cagendamento.data, 8);
		fseek(stdin, 0, SEEK_END);

		printf("\n\nHora do agendamento: \n");
		tratamento_hm(cagendamento.hora, 4);
		fseek(stdin, 0, SEEK_END);

		pagendamento = fopen("dados\\cad_agendamento.txt", "r");
		if (pagendamento == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

		while (!feof(pagendamento) && strcmp(agendamento_aux->hora, cagendamento.hora) != 0 && strcmp(agendamento_aux->data, cagendamento.data) != 0)
		{
			fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &agendamento_aux->codigo, agendamento_aux->paciente.cpf, agendamento_aux->paciente.nome, agendamento_aux->medico.cpf, agendamento_aux->medico.nome, agendamento_aux->filial.cnpj, agendamento_aux->filial.nome, agendamento_aux->data, agendamento_aux->hora, agendamento_aux->descricao);
		}
		if(strcmp(agendamento_aux->medico.cpf, cagendamento.medico.cpf) == 0 && strcmp(agendamento_aux->hora, cagendamento.hora) == 0 && strcmp(agendamento_aux->data, cagendamento.data) == 0)
		{
			printf("\n\nJa existe um agendamento com esse medico para esse horario, tente outro horario!\n");
			
		}
		else
		{
			break;
		}	
	}
	fclose(pagendamento);

	/*-----------------------------------------------------------------------*/

	// printf("\n\nValor da consulta: \n");
	// scanf("%i", &cagendamento.precovalor);
	// fseek(stdin, 0, SEEK_END);

	printf("\n\nDescricao do agendamento: \n");
	tratamento_desc50(cagendamento.descricao, 50);
	fseek(stdin, 0, SEEK_END);

	pagendamento = fopen("dados\\cad_agendamento.txt", "a+");
	if (pagendamento == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo, ele foi criado?");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	fprintf(pagendamento, "%i\n", cagendamento.codigo);
	fprintf(pagendamento, "%s\n", cpaciente->cpf);
	fprintf(pagendamento, "%s\n", cpaciente->nome);
	fprintf(pagendamento, "%s\n", cmedico->cpf);
	fprintf(pagendamento, "%s\n", cmedico->nome);
	fprintf(pagendamento, "%s\n", cfilial->cnpj);
	fprintf(pagendamento, "%s\n", cfilial->nome);
	fprintf(pagendamento, "%s\n", cagendamento.data);
	fprintf(pagendamento, "%s\n", cagendamento.hora);
	fprintf(pagendamento, "%s\n", cagendamento.descricao);
	fclose(pagendamento);

	printf("\n\nAgendamento realizado com sucessso!");
	getchar();
	free(cfilial);
	free(cmedico);
	free(cpaciente);
	main_cadastro();
}

/*-----------------------------------------------------------------------*/

/*CONSULTA TELAS*/
int con_usuario(void)
{
	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	user* cusuario = calloc(1, sizeof(user)* 1);
	char scan[14];
	int func_con;

	func_con = 0;
	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE USUARIOS DO SISTEMA\n\n");

	printf("Favor digite o cpf desejado: ");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	while (!feof(puser) && strcmp(cusuario->cpf, scan) != 0) {
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->email, cusuario->cpf, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep);
	}

	fclose(puser);
	if (strcmp(cusuario->cpf, scan) == 0) {
		memset(cusuario->senha, 0, sizeof(cusuario->senha));
		
		printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nUsuario no sistema: %s\nSenha: %s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->celular+2, cusuario->celular+7, cusuario->email, cusuario->cpf, cusuario->cpf+3, cusuario->cpf+6, cusuario->cpf+9, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep, cusuario->endereco.cep+5);

		printf("\n\nTecle [1] para voltar ou [2] consultar um novo usuario: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 	break;
			case 2 : con_usuario(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(puser);
		}
	}
	else {
		printf("\n\nCPF incorreto ou inexistente!\n");

		printf("\n\nTecle [1] para voltar ou [2] consultar um novo usuario: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); break;
			case 2 : con_usuario(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(puser);
		}
	}

	getchar();
	return 0;
	free(puser);
}

int con_paciente(void)
{
	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}
	
	patient* cpaciente = calloc(1, sizeof(patient)* 1);

	char scan[14];
	int func_con;

	func_con = 0;
	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE PACIENTES\n\n");

	printf("Favor digite o CPF desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	while (!feof(ppatient) && strcmp(cpaciente->cpf, scan) != 0) {
		fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->email, cpaciente->cpf, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep);
	}

	fclose(ppatient);
	if (strcmp(cpaciente->cpf, scan) == 0) {
		printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->celular+2, cpaciente->celular+7, cpaciente->email, cpaciente->cpf, cpaciente->cpf+3, cpaciente->cpf+6, cpaciente->cpf+9, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep, cpaciente->endereco.cep+5);
		
		printf("\n\nTecle [1] para voltar ou [2] consultar um novo paciente: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 	break;
			case 2 : con_paciente(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(ppatient);
		}
	}
	else {
		printf("\n\nCNPJ incorreto ou inexistente!\n");

		printf("\n\nTecle [1] para voltar ou [2] consultar um novo paciente: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 	break;
			case 2 : con_paciente(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(ppatient);
		}
	}
	getchar();
	return 0;
	free(cpaciente);
	main_consulta();
}

int con_medico(void)
{
	pdoctor = fopen("dados\\cad_medico.txt", "r");
	if (pdoctor == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	doctor* cmedico = calloc(1, sizeof(doctor)* 1);

	char scan[14];
	int func_con;

	func_con = 0;
	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE MEDICOS\n\n");

	printf("Favor digite o CPF desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pdoctor) && strcmp(cmedico->cpf, scan) != 0) {
		fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->email, cmedico->cpf, cmedico->especialidade, cmedico->filial.cnpj, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep);
	}

	fclose(pdoctor);
	if (strcmp(cmedico->cpf, scan) == 0) {
		printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nEspecialidade: %s\nFilial de atuacao(CNPJ): %.2s.%.3s.%.3s/%.4s-%.2s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->celular+2, cmedico->celular+7, cmedico->email, cmedico->cpf, cmedico->cpf+3, cmedico->cpf+6, cmedico->cpf+9, cmedico->especialidade, cmedico->filial.cnpj, cmedico->filial.cnpj+2, cmedico->filial.cnpj+5, cmedico->filial.cnpj+8, cmedico->filial.cnpj+12, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep, cmedico->endereco.cep+5);
		
		printf("\n\nTecle [1] para voltar ou [2] consultar um novo medico: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 	break;
			case 2 : con_medico(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(pdoctor);
		}
	}
	else {
		printf("\n\nCNPJ incorreto ou inexistente!\n");

		printf("\n\nTecle [1] para voltar ou [2] consultar um novo medico: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 	break;
			case 2 : con_medico(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(pdoctor);
		}
	}
	getchar();
	return 0;
	free(cmedico);
	main_consulta();
}

int con_filial(void)
{
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	branch* cfilial = calloc(1, sizeof(branch)* 1);

	char scan[14];
	int func_con;

	func_con = 0;
	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE FILIAIS\n\n");

	printf("Favor digite o CNPJ desejado:");
	tratamento_cnpj(scan, 15);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pfilial) && strcmp(cfilial->cnpj, scan) != 0) {
		fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
	}

	fclose(pfilial);
	if (strcmp(cfilial->cnpj, scan) == 0) {
		printf("\n\nCodigo: %i\nNome: %s\ncnpj: %.2s.%.3s.%.3s/%.4s-%.2s\nDescrição: %s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->cnpj+2, cfilial->cnpj+5, cfilial->cnpj+8, cfilial->cnpj+12, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep, cfilial->endereco.cep+5);
		
		printf("\n\nTecle [1] para voltar ou [2] consultar uma nova filial: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 	break;
			case 2 : con_filial(); 		break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(cfilial);
		}
	}
	else {
		printf("\n\nCNPJ incorreto ou inexistente!\n");

		printf("\n\nTecle [1] para voltar ou [2] consultar uma nova filial: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 	break;
			case 2 : con_filial(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(cfilial);
		}
	}
	getchar();
	return 0;
	free(cfilial);
	main_consulta();
}

int con_agendamento(void)
{
	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	scheduling* cagendamento = calloc(1, sizeof(scheduling)* 1);

	char scan[14];
	int func_con;

	func_con = 0;
	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE FILIAIS\n\n");

	printf("Favor digite o cpf desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pagendamento) && strcmp(cagendamento->paciente.cpf, scan) != 0) {
		fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, cagendamento->descricao);
	}

	fclose(pagendamento);
	if (strcmp(cagendamento->paciente.cpf, scan) == 0) {
		printf("\n\nCodigo: %i\nCPF do paciente: %.3s.%.3s.%.3s-%.2s\nNome do paciente: %s\nCPF do medico: %.3s.%.3s.%.3s-%.2s\nNome do medico: %s\nCNPJ da filial: %.2s.%.3s.%.3s/%.4s-%.2s\nNome da Filial: %s\nData do agendamento: %.2s/%.2s/%.4s\nHora do Agendamento: %.2s:%.2s\nDescricao: %s\n", cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.cpf+3, cagendamento->paciente.cpf+6, cagendamento->paciente.cpf+9, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.cpf+3, cagendamento->medico.cpf+6, cagendamento->medico.cpf+9, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.cnpj+2, cagendamento->filial.cnpj+5, cagendamento->filial.cnpj+8, cagendamento->filial.cnpj+12, cagendamento->filial.nome, cagendamento->data, cagendamento->data+2, cagendamento->data+4, cagendamento->hora, cagendamento->hora+2, cagendamento->descricao);
		
		printf("\n\nTecle [1] para voltar ou [2] consultar um novo agendamento: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 		break;
			case 2 : con_agendamento(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(cagendamento);
		}
	}
	else {
		printf("\n\nCPF incorreto ou inexistente!\n");

		printf("\n\nTecle [1] para voltar ou [2] consultar um novo agendamento: ");
		scanf("%i", &func_con);

		switch (func_con)
		{
			case 1 : main_consulta(); 		break;
			case 2 : con_agendamento(); 	break;		
			default: printf("\nMenu inexistente, tente novamente [1] ou [2].");
			free(cagendamento);
		}
	}
	getchar();
	return 0;
	free(cagendamento);
	main_consulta();

}

/*-----------------------------------------------------------------------*/

/*FUNÇÕES*/
int verifica_useradm(void)
{
	const char * buscar_adm = "admin";
	char senha_adm[50];
	char repete_senha_adm[50];

	system("mkdir dados");
	
	user* usuario = calloc(1, sizeof(user)* 1);

	puser = fopen("dados\\cad_funcionario.txt", "a+");
	if(puser == NULL) 
	{
		fprintf(stderr, "Erro ao criar o arquivo cad_funcionario.txt, pode ser permisao?\n");
		return 1;
	}
		
	//Comparar strings com strcmp
	while (!feof(puser) && strcmp(usuario->usuario, buscar_adm) != 0)
	{	
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &usuario->codigo, usuario->nome, usuario->celular, usuario->email, usuario->cpf, usuario->usuario, usuario->senha, usuario->endereco.estado, usuario->endereco.cidade, usuario->endereco.bairro, usuario->endereco.logradouro, usuario->endereco.complemento, usuario->endereco.cep);
	}	
	while(strcmp(usuario->usuario, buscar_adm) != 0)
	{		
		memset(senha_adm, 0, sizeof(senha_adm));
		memset(repete_senha_adm, 0, sizeof(repete_senha_adm));
		/*Cadastro dos dados*/
		printf("\033[2J\033[1;1H");
		printf("\n============ CADASTRO DO USUARIO ADMINISTRADOR ============\n\n");
		printf("Atencao, para o primeiro acesso, cadastre um usuario adminsitrador para acessar o sistema!\n\n");
		printf("Usuario: admin\n");
		printf("Digite a senha: ");
		criptografa_senha(senha_adm, 50);
		printf("\nConfirme a senha: ");
		criptografa_senha(repete_senha_adm, 50);

		//Comparar strings com strcmp
		if(strcmp(senha_adm, repete_senha_adm) == 0)
		{
			fprintf(puser, "1\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "admin\n");
			fprintf(puser, "%s\n", senha_adm);
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fprintf(puser, "00000000000\n");
			fclose(puser);

			printf("\n\nUsuario administrador cadastrado com sucesso! Tecle ENTER para ir ao painel de login.");
			getchar();
			break;
		}else if(strcmp(senha_adm, repete_senha_adm) != 0)
		{				
			memset(senha_adm, 0, sizeof(senha_adm));
			memset(repete_senha_adm, 0, sizeof(repete_senha_adm));
			printf("\n\nAs senhas nao conferem, adicione senhas iguais!\n\n");
			printf("\nTecle ENTER para tentar novamente!\n");
			getchar();

		}	
	}
	return 0;
	free(usuario);
}

int tela_login(void)
{
	int i, tam_msg;
	char scan[50], scan2[50], crip_msg[50];
	memset(scan, 0, sizeof(scan));
	memset(scan2, 0, sizeof(scan2));
	memset(crip_msg, 0, sizeof(crip_msg));
	puser = fopen("dados\\cad_funcionario.txt", "r");

	user* usuario = calloc(1, sizeof(user)* 1);

  	/*PAINEL DE LOGIN*/
	printf("\033[2J\033[1;1H");
	printf("\n============ PAINEL DE LOGIN ============\n\n");
	printf("\nFavor digitar o seu usuario e senha!\n");
	printf("\nLOGIN: ");
	scanf("%s", scan);
	printf("\nSENHA: ");


  	//Adiciona * nos valores digitados na senha.
	tratamento_senha(scan2, 50);

  	//Busca o cadastro no arquivo
  	while (!feof(puser)) {
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &usuario->codigo, usuario->nome, usuario->celular, usuario->email, usuario->cpf, usuario->usuario, usuario->senha, usuario->endereco.estado, usuario->endereco.cidade, usuario->endereco.bairro, usuario->endereco.logradouro, usuario->endereco.complemento, usuario->endereco.cep);

		if (strcmp(usuario->usuario, scan) == 0) {
			break;
		}
	}

  	//Criptografa a senha digitada pelo usuário
  	tam_msg = strlen(scan2);
	for (i = 0; i < tam_msg; i++)
	{
		crip_msg[i] = scan2[i] + 5;
	}
	crip_msg[tam_msg] = '\0';

  	fclose(puser);

  	//Faz a comparação da senha digitada e criptografada do usuário com a que existe no cadastro
  	if (strcmp(usuario->usuario, scan) == 0) {
		if (strcmp(usuario->senha, crip_msg) == 0)
		{
			printf("\n\nLOGADO");
		}
		else {
			printf("\n\nUsuario ou senha invalido!\n\n");
			getchar();
			tela_login();
		}
	}
	else if(strcmp(usuario->usuario, scan) != 0)
	{
		printf("\n\nUsuário ou senha invalido!\n\n");
		tela_login();
	}
    printf("\n\n\n");
    return 0;
}

void tratamento_desc50(char* tdesc50, int tdesc50_size)
{
	/*TRATAMENTO PARA NOME OU DESCRIÇÃO DE 50 CARACTERES*/
    int i;
    char c;

	memset(tdesc50, 0, tdesc50_size);
    i = 0;
    c = '\0';

	do
	{
		c = getch();
		if (isprint(c) != 0)
		{
			if (i < 50)
			{
				tdesc50[i] = c;
				i++;
				printf("%c", c);				
			}
		}else if (c == 8 && i)
		{
			tdesc50[i] = '\0';
			i--;
			printf("\b \b");
		}
	}while(c != 13 || i == 0);
}

void tratamento_cpf(char* tcpf, int tcpf_size)
{
	/*TRATAMENTO PARA O CPF*/

 	int i;
    char c;

	memset(tcpf, 0, tcpf_size);
	i = 0;
	c = '\0';
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 11)
			{
				tcpf[i] = c;
				i++;
				printf("%c", c);
				if (i == 3 || i == 6)
				{
					printf(".");
				}else if(i == 9)
				{
					printf ("-");
				}
			}
		}else if(c == 8 && i)
		{
			if (i == 3 || i == 6 || i == 9)
			{
				printf("\b \b");
				tcpf[i] = '\0';
				i--;
				printf("\b \b");				
			}
			else {
				tcpf[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	}while(c != 13 || i == 0 || i < 11);
	tcpf[i] = '\0';
}

void tratamento_data(char* tdata, int tdata_size)
{
	/*TRATAMENTO PARA A DATA*/

 	int i;
    char c;

	memset(tdata, 0, tdata_size);
	i = 0;
	c = '\0';
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 8)
			{
				tdata[i] = c;
				i++;
				printf("%c", c);
				if (i == 2 || i == 4)
				{
					printf("/");
				}
			}
		}else if(c == 8 && i)
		{
			if (i == 2 || i == 4)
			{
				printf("\b \b");
				tdata[i] = '\0';
				i--;
				printf("\b \b");				
			}
			else {
				tdata[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	}while(c != 13 || i == 0 || i < 8);
	tdata[i] = '\0';
}

void tratamento_tdta(char* tdta, int tdta_size)
{
	int d, m, a;

	//ponteiro para struct que armazena data e hora  
	struct tm *data_hora_atual; 

	//variável do tipo time_t para armazenar o tempo em segundos  
  	time_t segundos;

	//obtendo o tempo em segundos  
  	time(&segundos);

	//para converter de segundos para o tempo local  
  	//utilizamos a função localtime  
  	data_hora_atual = localtime(&segundos); 

	do{
		d = 0, m = 0 , a = 0;
		
		memset(tdta, 0, tdta_size);

		tratamento_data(tdta, 8);

		sscanf(tdta, "\n%2d %2d %4d", &d, &m, &a);

		if (((d < data_hora_atual->tm_mday || d > 31 || d != data_hora_atual->tm_mday) && (m < data_hora_atual->tm_mon+1 || m > 12)) || (a < data_hora_atual->tm_year+1900)) 
		{
			printf("\n\nData invalida, tente outra!\n");
			printf("\nData do agendamento: \n");
		}
	
	}while (((d < data_hora_atual->tm_mday || d > 31 || d != data_hora_atual->tm_mday) && (m < data_hora_atual->tm_mon+1 || m > 12)) || (a < data_hora_atual->tm_year+1900));
}

void tratamento_hora(char* thora, int thora_size)
{
	/*TRATAMENTO PARA A HORA*/

 	int i;
    char c;

	memset(thora, 0, thora_size);
	i = 0;
	c = '\0';
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 4)
			{
				thora[i] = c;
				i++;
				printf("%c", c);
				if (i == 2)
				{
					printf(":");
				}
			}
		}else if(c == 8 && i)
		{
			if (i == 2)
			{
				printf("\b \b");
				thora[i] = '\0';
				i--;
				printf("\b \b");				
			}
			else {
				thora[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	}while(c != 13 || i == 0 || i < 4);
	thora[i] = '\0';
}

void tratamento_preco(int* tpreco)
{
	/*TRATAMENTO PARA A HORA*/

 	int i;
    char c;

	//memset(tpreco, 0, sizeof(tpreco));
	i = 0;
	c = 0;
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			tpreco[i] = c;
			i++; 
			printf("%c", c);
			if (i == 1 || i == 4 || i == 7)
			{
				printf(".");
			}

		}else if(c == 8 && i)
		{
			if (i == 1 || i == 4 || i == 7)
			{
				printf("\b \b");
				tpreco[i] = '\0';
				i--;
				printf("\b \b");				
			}else
			{			
			tpreco[i] = '\0';
			i--;
			printf("\b \b");
			}
		}
	}while(c != 13 || i == 0);
}

void tratamento_hm(char* thm, int thm_size)
{
	int h, m;

	do{
		h = 0, m = 0;
		memset(thm, 0, thm_size);

		tratamento_hora(thm, 4);

		sscanf(thm, "\n%2d %2d", &h, &m);

		if ( h > 23 || m > 59 ) 
		{
			printf("\n\nFavor digite a hora entre 00 e 23 e os minutos entre 00 e 59!\n");
			printf("\nHora do agendamento: \n");
		}
	
	}while (h > 23 || m > 59);
}

void tratamento_cnpj(char* tcnpj, int tcnpj_size)
{
	int i;
    char c;

	memset(tcnpj, 0, tcnpj_size);
	i = 0;
	c = '\0';
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 14)
			{
				tcnpj[i] = c;
				i++;
				printf("%c", c);
				if (i == 2 || i == 5)
				{
					printf(".");
				}else if(i == 8)
				{
					printf ("/");
				}else if(i == 12)
				{
					printf ("-");
				}
			}
		}else if(c == 8 && i)
		{
			if (i == 2 || i == 5 || i == 8 || i == 12)
			{
				printf("\b \b");
				tcnpj[i] = '\0';
				i--;
				printf("\b \b");				
			}
			else {
				tcnpj[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	}while(c != 13 || i == 0 || i < 14);
}

void tratamento_senha(char* tsenha, int tsenha_size)
{
	/*TRATAMENTO PARA A SENHA*/
	int i;
	char c;

	memset(tsenha, 0, tsenha_size);
	c = '\n';
	i = 0; 
	//Adiciona * nos valores digitados na senha.
	do 
	{			
		c = _getch();
		
		if (isprint(c))
		{
			if(i < 50)
			{
				tsenha[i++] = c;
				printf("%c", '*');
			}
		}
		else if (c == 8 && i)
		{
			tsenha[i--] = '\0';
			printf("%s", "\b \b");
		}

	} while (c != 13 || i == 0);
}

void tratamento_celular(char* tcelular, int tcelular_size)
{
	/*TRATAMENTO PARA O CELULAR*/
    int i;
    char c;

	memset(tcelular, 0, tcelular_size);
    i = 0;
    c = '\0';

	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 11)
			{
				tcelular[i] = c;
				i++;
				printf("%c", c);
				if(i == 2)
				{
					printf("-");
				}else if(i == 7)
				{
					printf("-");
				}
			}
		}else if(c == 8 && i)
		{
			if (i == 2 || i == 7)
			{
				printf("\b \b");
				tcelular[i] = '\0';
				i--;
				printf("\b \b");				
			}
			else {
				tcelular[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	}while(c != 13 || i == 0 || i < 11);
}

void tratamento_cep(char* tcep, int tcep_size)
{
	/*TRATAMENTO PARA O CEP*/
    int i;
    char c;

	memset(tcep, 0, tcep_size);
    i = 0;
    c = '\0';

	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 8)
			{
				tcep[i] = c;
				i++;
				printf("%c", c);
				if(i == 5)
				{
					printf("-");
				}
			}
		}else if(c == 8 && i)
		{
			if (i == 5)
			{
				printf("\b \b");
				tcep[i] = '\0';
				i--;
				printf("\b \b");				
			}
			else {
				tcep[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	}while(c != 13 || i == 0 || i < 8);
}

void incrementa_id_func(int *IDinc_func)
{
	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	user* usuarioi = calloc(1, sizeof(user)* 1);
	
	while (!feof(puser))
	{
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &usuarioi->codigo, usuarioi->nome, usuarioi->celular, usuarioi->email, usuarioi->cpf, usuarioi->usuario, usuarioi->senha, usuarioi->endereco.estado, usuarioi->endereco.cidade, usuarioi->endereco.bairro, usuarioi->endereco.logradouro, usuarioi->endereco.complemento, usuarioi->endereco.cep);
	}

	*IDinc_func = usuarioi->codigo;
}

void incrementa_id_paci(int *IDinc_paci)
{
	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	patient* pacientei = calloc(1, sizeof(patient)* 1);

	while (!feof(ppatient))
	{
		fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &pacientei->codigo, pacientei->nome, pacientei->celular, pacientei->email, pacientei->cpf, pacientei->endereco.estado, pacientei->endereco.cidade, pacientei->endereco.bairro, pacientei->endereco.logradouro, pacientei->endereco.complemento, pacientei->endereco.cep);
	}

	*IDinc_paci = pacientei->codigo;
}

void incrementa_id_medi(int *IDinc_medi)
{
	pdoctor = fopen("dados\\cad_medico.txt", "r");
	if (pdoctor == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	doctor* medicoi = calloc(1, sizeof(doctor)* 1);

	while (!feof(pdoctor))
	{
		fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &medicoi->codigo, medicoi->nome, medicoi->celular, medicoi->email, medicoi->cpf, medicoi->especialidade, medicoi->filial.cnpj, medicoi->endereco.estado, medicoi->endereco.cidade, medicoi->endereco.bairro, medicoi->endereco.logradouro, medicoi->endereco.complemento, medicoi->endereco.cep);
	}

	*IDinc_medi = medicoi->codigo;
}

void incrementa_id_fili(int *IDinc_fili)
{
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	branch* filiali = calloc(1, sizeof(branch)* 1);

	while (!feof(pfilial))
	{
		fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &filiali->codigo, filiali->nome, filiali->cnpj, filiali->descricao, filiali->endereco.estado, filiali->endereco.cidade, filiali->endereco.bairro, filiali->endereco.logradouro, filiali->endereco.complemento, filiali->endereco.cep);
	}
	
	*IDinc_fili = filiali->codigo;
}

void incrementa_id_agen(int *IDinc_agen)
{
	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL) {
		fprintf(stderr, "\n\nErro ao abrir arquivo ou ainda nao foi realizado nenhum cadastro!");
		
		int verificaarq;
		verificaarq = 0;
		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		scanf("%i", &verificaarq);

		switch (verificaarq)
		{
			case 1 : main_principal();	break;	
			case 2 : exit(0);		
			default:printf("\nMenu inexistente, tente novamente [1] ou [2].");
		}
	}

	scheduling* agendamentoi = calloc(1, sizeof(scheduling)* 1);

	while (!feof(pagendamento))
	{
		fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &agendamentoi->codigo, agendamentoi->paciente.cpf, agendamentoi->paciente.nome, agendamentoi->medico.cpf, agendamentoi->medico.nome, agendamentoi->filial.cnpj, agendamentoi->filial.nome, agendamentoi->data, agendamentoi->hora, agendamentoi->descricao);
	}
	
	*IDinc_agen = agendamentoi->codigo;
}

void criptografa_senha(char *crip_msg, int senha_encript_size)
{
	int i, tam_msg = 0;
	char senha_cript[50], c;

	memset(senha_cript, 0, sizeof(senha_cript));
	memset(crip_msg, 0, senha_encript_size);
	c = '\n';
	i = 0; 
	tam_msg = 0;
	//Adiciona * nos valores digitados na senha.
	do 
	{			
		c = _getch();
		
		if (isprint(c))
		{
			if(i < 50)
			{
				senha_cript[i++] = c;
				printf("%c", '*');
			}
		}
		else if (c == 8 && i)
		{
			senha_cript[i--] = '\0';
			printf("%s", "\b \b");
		}

	} while (c != 13 || i == 0);

	/*GRAVAR OS DADOS NO ARQUIVO DE TEXTO*/
	tam_msg = strlen(senha_cript);
	for (i = 0; i < tam_msg; i++)
	{
		crip_msg[i] = senha_cript[i] + 5;
	}
	crip_msg[tam_msg] = '\0';
}
