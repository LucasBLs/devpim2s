/**
 * @file main.c
 * @author Lucas Batista de Lemos (https://www.linkedin.com/in/lucasblemos/)
 * @brief 
 * @version 1.2
 * @date 11-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

/*01 - Estrutura do endereço*/
typedef struct
{
	char logradouro[52];
	char complemento[52];
	char bairro[52];
	char cidade[52];
	char estado[5];
	char cep[10];
	char alterar[5];
	char salvar[2];
} address;

/*02 - Estrutura da filial*/
typedef struct
{
	int codigo;
	char nome[52];
	char descricao[52];
	char cnpj[15];
	char alterar[5];
	char salvar[2];
	address endereco;
} branch, branch_aux, branch_upd, branch_del;

/*03 - Estrutura do usuário*/
typedef struct
{
	int codigo;
	char nome[52];
	char celular[13];
	char email[100];
	char cpf[12];
	char usuario[52];
	char senha[52];
	char senha2[60];
	char status[2];
	char alterar[5];
	char salvar[2];
	address endereco;
} user, user_aux, user_upd, user_del;

/*04 - Estrutura do paciente*/
typedef struct
{
	int codigo;
	char nome[52];
	char celular[13];
	char email[100];
	char cpf[12];
	char cpf_c[12];
	char alterar[5];
	char salvar[2];
	address endereco;
	branch filial;
} patient, patient_aux, patient_upd, patient_del;

/*05 - Estrutura do medico*/
typedef struct
{
	int codigo;
	char nome[52];
	char celular[13];
	char email[100];
	char cpf[12];
	char especialidade[52];
	char alterar[5];
	char salvar[2];
	branch filial;
	address endereco;
} doctor, doctor_aux, doctor_upd, doctor_del;

/*06 - Estrutura do agendamento*/
typedef struct
{
	int codigo;
	char descricao[52];
	patient paciente;
	doctor medico;
	branch filial;
	char data[10];
	char hora[6];
	char periodo[52];
	char status[2];
	char alterar[5];
	float precovalor;
	char salvar[2];
} scheduling, scheduling_aux, scheduling_upd, scheduling_del;

/*07 - Estrutura da avaliacao*/
typedef struct
{
	int codigo;
	char elogio[1500];
	char reclamacao[1500];
	int status;
	scheduling agendamento;
} evaluation, evaluation_aux;

FILE *puser, *ppatient, *pdoctor, *pfilial, *pendereco, *plogin, *pagendamento, *temporario, *relatorio, *pavaliacao;

/*FC MENU*/
int main(void);
int main_principal(void);
void main_cadastro(void);
void main_consulta(void);
void main_alterar(void);
void main_delete(void);
void main_relatorio(void);
void main_avaliacao(void);

/*FC MENU TELAS*/
void menu_principal(void);
void menu_cadastros(void);
void menu_consultas(void);
void menu_alterar(void);
void menu_delete(void);
void menu_relatorio(void);
void menu_avaliacao(void);

/*FC CADASTRO TELAS*/
void cad_usuario(void);
void cad_paciente(void);
void cad_medico(void);
void cad_filial(void);
void cad_agendamento(void);
void cad_elogio(void);
void cad_reclamacao(void);

/*FC CONSULTA TELAS*/
int con_usuario(void);
int con_paciente(void);
int con_filial(void);
int con_medico(void);
int con_agendamento(void);
int con_elogio(void);
int con_reclamacao(void);

/*FC ALTERAR TELAS*/
void alterar_usuario(void);
void alterar_paciente(void);
void alterar_medico(void);
void alterar_filial(void);
void alterar_agendamento(void);

/*FC DELETAR TELAS*/
void deletar_usuario(void);
void deletar_paciente(void);
void deletar_medico(void);
void deletar_filial(void);
void cancelar_agendamento(void);

/*FC RELATORIO TELAS*/
int relatorio_usuario(void);
int relatorio_paci_filial(void);
int relatorio_filialtotal(void);

/*FC ALEATORIAS*/
int verifica_useradm(void);
int tela_login(void);
void mostrarendereco(void);
void tratamento_desc50(char *tdesc50, int tdesc50_size);
void tratamento_desc1500(char *tdesc1500, int tdesc1500_size);
void tratamento_estado(char *testado, int testado_size);
void tratamento_cpf(char *tcpf, int tcpf_size);
void tratamento_data(char *tdata, int tdata_size);
void tratamento_tdta(char *tdta, int tdta_size);
void tratamento_dataqq(char *tdataqq, int tdataqq_size);
void tratamento_tdtaqq(char *tdtaqq, int tdtaqq_size);
void tratamento_hora(char *thora, int thora_size);
void tratamento_numero(char *tnum, int tnum_size);
void tratamento_numeroum(char *tnumum, int tnumum_size);
void tratamento_hm(char *thm, int thm_size);
void tratamento_cnpj(char *tcnpj, int tcnpj_size);
void tratamento_senha(char *tsenha, int tsenha_size);
void tratamento_celular(char *tcelular, int tcelular_size);
void tratamento_cep(char *tcep, int tcep_size);
void criptografa_senha(char *crip_msg, int senha_encript_size);
void incrementa_id_func(int *IDinc);
void incrementa_id_paci(int *IDinc_paci);
void incrementa_id_medi(int *IDinc_medi);
void incrementa_id_fili(int *IDinc_fili);
void incrementa_id_agen(int *IDinc_agen);
void incrementa_id_avale(int *IDinc_avale);
void incrementa_id_avalr(int *IDinc_avalr);

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
	char scan_main[2];
	memset(scan_main, 0, sizeof(scan_main));

	/*Chama o menu princial*/
	menu_principal();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	tratamento_numeroum(scan_main, 0);

	switch (scan_main[0])
	{
	case '1':
		main_cadastro();
		break;
	case '2':
		main_consulta();
		break;
	case '3':
		main_alterar();
		break;
	case '4':
		main_delete();
		break;
	case '5':
		main_relatorio();
		break;
	case '6':
		main_avaliacao();
		break;
	case '7':
		tela_login();
		break;
	case '8':
		exit(0);
		break;
	default:
		printf("\n\nMenu inexistente, tente novamente de 1 a 8.\n\n");
		system("pause");
		main_principal();
	}

	printf("\n\n");
	return 0;
}

void main_cadastro(void)
{
	/*---- ACESSO AOS MENU DE CADASTRO E CONSULTA ----*/
	char scan_cad[2];
	memset(scan_cad, 0, sizeof(scan_cad));

	/*Chama o menu de cadastros*/
	menu_cadastros();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	tratamento_numeroum(scan_cad, 0);

	switch (scan_cad[0])
	{
	case '1':
		cad_usuario();
		break;
	case '2':
		cad_paciente();
		break;
	case '3':
		cad_medico();
		break;
	case '4':
		cad_filial();
		break;
	case '5':
		cad_agendamento();
		break;
	case '6':
		main_principal();
		break;
	case '7':
		tela_login();
		break;
		exit(0);
	default:
		printf("\n\nMenu inexistente, tente de 1 a 7.\n\n");
		system("pause");
		main_cadastro();
	}

	printf("\n\n");
}

void main_consulta(void)
{
	/*---- ACESSO AOS MENU DE CADASTRO E CONSULTA ----*/
	char scan_con[2];
	memset(scan_con, 0, sizeof(scan_con));

	/*Chama o menu de consultas*/
	menu_consultas();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	tratamento_numeroum(scan_con, 0);

	switch (scan_con[0])
	{
	case '1':
		con_usuario();
		break;
	case '2':
		con_paciente();
		break;
	case '3':
		con_medico();
		break;
	case '4':
		con_filial();
		break;
	case '5':
		con_agendamento();
		break;
	case '6':
		main_principal();
		break;
	case '7':
		tela_login();
		break;
		exit(0);
	default:
		printf("\n\nMenu inexistente, tente de 1 a 7.\n\n");
		system("pause");
		main_consulta();
	}

	printf("\n\n");
	getchar();
}

void main_alterar(void)
{
	/*---- ACESSO AOS MENU DE CADASTRO E CONSULTA ----*/
	char scan_alt[2];
	memset(scan_alt, 0, sizeof(scan_alt));

	/*Chama o menu de alteração*/
	menu_alterar();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	tratamento_numeroum(scan_alt, 0);

	switch (scan_alt[0])
	{
	case '1':
		alterar_agendamento();
		break;
	case '2':
		alterar_usuario();
		break;
	case '3':
		alterar_paciente();
		break;
	case '4':
		alterar_medico();
		break;
	case '5':
		alterar_filial();
		break;
	case '6':
		main_principal();
		break;
	case '7':
		tela_login();
		break;
		exit(0);
	default:
		printf("\n\nMenu inexistente, tente de 1 a 7.\n\n");
		system("pause");
		main_alterar();
	}

	printf("\n\n");
	getchar();
}

void main_delete(void)
{
	/*---- ACESSO AOS MENU DE CADASTRO E CONSULTA ----*/
	char scan_del[2];
	memset(scan_del, 0, sizeof(scan_del));

	/*Chama o menu de delete*/
	menu_delete();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	tratamento_numeroum(scan_del, 0);

	switch (scan_del[0])
	{
	case '1':
		cancelar_agendamento();
		break;
	case '2':
		deletar_usuario();
		break;
	case '3':
		deletar_paciente();
		break;
	case '4':
		deletar_medico();
		break;
	case '5':
		deletar_filial();
		break;
	case '6':
		main_principal();
		break;
	case '7':
		tela_login();
		break;
		exit(0);
	default:
		printf("\n\nMenu inexistente, tente de 1 a 7.\n\n");
		system("pause");
		main_delete();
	}

	printf("\n\n");
	getchar();
}

void main_relatorio(void)
{
	/*---- ACESSO AOS MENU DE CADASTRO E CONSULTA ----*/
	char scan_rel[2];
	memset(scan_rel, 0, sizeof(scan_rel));

	/*Chama o menu de relatórios*/
	menu_relatorio();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	tratamento_numeroum(scan_rel, 0);

	switch (scan_rel[0])
	{
	case '1':
		relatorio_usuario();
		break;
	case '2':
		relatorio_paci_filial();
		break;
	case '3':
		relatorio_filialtotal();
		break;
	case '4':
		main_principal();
		break;
	case '5':
		tela_login();
		break;
		exit(0);
	default:
		printf("\n\nMenu inexistente, tente de 1 a 5.\n\n");
		system("pause");
		main_relatorio();
	}

	printf("\n\n");
	getchar();
}

void main_avaliacao(void)
{
	/*---- ACESSO AOS MENU DE CADASTRO E CONSULTA ----*/
	char scan_aval[2];
	memset(scan_aval, 0, sizeof(scan_aval));

	/*Chama o menu de relatórios*/
	menu_avaliacao();

	printf("\nSelecione uma opcao e pressione ENTER: ");
	tratamento_numeroum(scan_aval, 0);

	switch (scan_aval[0])
	{
	case '1':
		cad_elogio();
		break;
	case '2':
		cad_reclamacao();
		break;
	case '3':
		con_elogio();
		break;
	case '4':
		con_reclamacao();
		break;
	case '5':
		main_principal();
		break;
	case '6':
		tela_login();
		break;
		exit(0);
	default:
		printf("\n\nMenu inexistente, tente de 1 a 6.\n\n");
		system("pause");
		main_avaliacao();
	}

	printf("\n\n");
	getchar();
}

/*-----------------------------------------------------------------------*/

/*MENU TELAS*/
void menu_principal(void)
{
	setlocale(LC_ALL, ""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	      ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu principal                   |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Menu de cadastros                      |\n");
	printf("    |       [2] - Menu de consultas                      |\n");
	printf("    |       [3] - Menu de alteracao                      |\n");
	printf("    |       [4] - Menu de delete                         |\n");
	printf("    |       [5] - Menu de relatorios                     |\n");
	printf("    |       [6] - Menu de avaliacao                      |\n");
	printf("    |       [7] - Logout                                 |\n");
	printf("    |       [8] - Sair do Programa                       |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");
}

void menu_cadastros(void)
{
	setlocale(LC_ALL, ""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	      ========   CLIMANAGER   ========\n\n");

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
	setlocale(LC_ALL, ""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	      ========   CLIMANAGER   ========\n\n");

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

void menu_alterar(void)
{
	setlocale(LC_ALL, ""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	      ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu de alteracao                |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Alterar agendamento                    |\n");
	printf("    |       [2] - Alterar usuario                        |\n");
	printf("    |       [3] - Alterar paciente                       |\n");
	printf("    |       [4] - Alterar medico                         |\n");
	printf("    |       [5] - Alterar filial                         |\n");
	printf("    |       [6] - Voltar ao menu principal               |\n");
	printf("    |       [7] - Logout                                 |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");
}

void menu_delete(void)
{
	setlocale(LC_ALL, ""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	      ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu de delete	                 |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Cancelar agendamento                   |\n");
	printf("    |       [2] - Deletar usuario                        |\n");
	printf("    |       [3] - Deletar paciente                       |\n");
	printf("    |       [4] - Deletar medico                         |\n");
	printf("    |       [5] - Deletar filial                         |\n");
	printf("    |       [6] - Voltar ao menu principal               |\n");
	printf("    |       [7] - Logout                                 |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");
}

void menu_relatorio(void)
{
	setlocale(LC_ALL, ""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	      ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu de relatorios               |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Relatorio de usuarios                  |\n");
	printf("    |       [2] - Relatorio de pacientes por filial      |\n");
	printf("    |       [3] - Relatorio total faturado por unidade   |\n");
	printf("    |       [4] - Voltar ao menu principal               |\n");
	printf("    |       [5] - Logout                                 |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");
}

void menu_avaliacao(void)
{
	setlocale(LC_ALL, ""); //Para acentuação
	printf("\033[2J\033[1;1H");

	printf("	      ========   CLIMANAGER   ========\n\n");

	printf("    .____________________________________________________.\n");
	printf("    |                                                    |\n");
	printf("    |                   Menu de avaliacao                |\n");
	printf("    |____________________________________________________|\n");
	printf("    |                                                    |\n");
	printf("    |                                                    |\n");
	printf("    |       [1] - Criar um elogio                        |\n");
	printf("    |       [2] - Criar uma reclamacao                   |\n");
	printf("    |       [3] - Consultar elogios                      |\n");
	printf("    |       [4] - Consultar reclamacoes                  |\n");
	printf("    |       [5] - Voltar ao menu principal               |\n");
	printf("    |       [6] - Logout                                 |\n");
	printf("    |                                                    |\n");
	printf("    |____________________________________________________|\n");
}

/*-----------------------------------------------------------------------*/

/*CADASTRO TELAS*/
void cad_usuario(void)
{
	user cfuncionario = {'\0'};
	user_aux *cusuario_aux = calloc(1, sizeof(user_aux) * 1);

	int i, tam_msg;
	char crip_msg[52];

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE FUNCIONARIOS\n\n");

	incrementa_id_func(&cfuncionario.codigo);
	cfuncionario.codigo++;

	printf("Codigo de cadastro: %i\n", cfuncionario.codigo);

	while (strcmp(cfuncionario.nome, "admin") != 0)
	{
		printf("\nNome do funcionario: \n");
		tratamento_desc50(cfuncionario.nome, 50);
		fseek(stdin, 0, SEEK_END);

		if (strcmp(cfuncionario.nome, "admin") == 0)
		{
			printf("\n\nNao e possivel cadastrar o nome (admin), tente outro!\n\n");
			memset(cfuncionario.nome, 0, sizeof(cfuncionario.nome));
		}
		else
		{
			break;
		}
	}

	printf("\n\nCelular do funcionario: \n");
	tratamento_celular(cfuncionario.celular, 11);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nE-mail do funcionario: \n");
	tratamento_desc50(cfuncionario.email, 50);
	fseek(stdin, 0, SEEK_END);

	/*CARREGAR OS DADOS DOS FUNCIONARIOS*/
	while (strcmp(cusuario_aux->cpf, cfuncionario.cpf) == 0 || *cfuncionario.cpf == '\0')
	{
		puser = fopen("dados\\cad_funcionario.txt", "r");
		if (puser == NULL)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo de funcionarios ou ainda nao foi realizado nenhum cadastro!");

			char verificaarq[2];
			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				main_principal();
				break;
			case '2':
				exit(0);
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}

		while (strcmp(cusuario_aux->cpf, cfuncionario.cpf) == 0)
		{
			printf("\n\nCPF do funcionario: \n");
			tratamento_cpf(cfuncionario.cpf, 12);
			fseek(stdin, 0, SEEK_END);

			while (!feof(puser) && strcmp(cusuario_aux->cpf, cfuncionario.cpf) != 0)
			{
				fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cusuario_aux->codigo, cusuario_aux->nome, cusuario_aux->celular, cusuario_aux->email, cusuario_aux->cpf, cusuario_aux->usuario, cusuario_aux->senha, cusuario_aux->endereco.estado, cusuario_aux->endereco.cidade, cusuario_aux->endereco.bairro, cusuario_aux->endereco.logradouro, cusuario_aux->endereco.complemento, cusuario_aux->endereco.cep);
			}
			if (strcmp(cusuario_aux->cpf, cfuncionario.cpf) == 0)
			{
				printf("\n\nJa existe um cadastro com esse CPF!\n");
			}
			else
			{
				break;
			}
		}
	}
	fclose(puser);

	while (strcmp(cfuncionario.usuario, "admin") != 0)
	{
		printf("\n\nUsuario para funcionario: \n");
		tratamento_desc50(cfuncionario.usuario, 50);
		fseek(stdin, 0, SEEK_END);

		if (strcmp(cfuncionario.usuario, "admin") == 0)
		{
			printf("\n\nNao e possivel cadastrar o nome (admin), tente outro!\n\n");
			memset(cfuncionario.usuario, 0, sizeof(cfuncionario.usuario));
		}
		else if (strcmp(cfuncionario.usuario, cusuario_aux->usuario) == 0)
		{
			printf("\n\nEsse usuario ja esta cadastrado, tente outro!\n\n");
		}
		else
		{
			break;
		}
	}

	/* ---------- TRATAMENTO NO CAMPO SENHA ---------- */
	while (strcmp(cfuncionario.senha, cfuncionario.senha2) != 0 || strcmp(cfuncionario.senha, cfuncionario.senha2) == '\0')
	{
		printf("\n\nSenha do usuario: \n");
		tratamento_senha(cfuncionario.senha, 50);
		fseek(stdin, 0, SEEK_END);

		printf("\n\nDigite a senha novamente: \n");
		tratamento_senha(cfuncionario.senha2, 50);
		fseek(stdin, 0, SEEK_END);

		if (strcmp(cfuncionario.senha, cfuncionario.senha2) != 0)
		{
			memset(cfuncionario.senha, 0, sizeof(cfuncionario.senha));
			memset(cfuncionario.senha2, 0, sizeof(cfuncionario.senha2));
			printf("\nAs senhas nao conferem, adicione senhas iguais!\n");
		}
		else
		{
			printf("\n--------- Localizacao --------- \n");

			printf("\n\nEstado do Usuario(XX): \n");
			tratamento_estado(cfuncionario.endereco.estado, 2);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nCidade do Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.cidade, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nBairro do Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.bairro, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nLogradouro do Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.logradouro, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nComplemento do Usuario: \n");
			tratamento_desc50(cfuncionario.endereco.complemento, 50);
			fseek(stdin, 0, SEEK_END);

			printf("\n\nCEP do Usuario: \n");
			tratamento_cep(cfuncionario.endereco.cep, 8);
			fseek(stdin, 0, SEEK_END);
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

	fclose(puser);
	puser = fopen("dados\\cad_funcionario.txt", "a+");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de funcionarios ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cfuncionario.salvar, "1") != 0 || strcmp(cfuncionario.salvar, "2") != 0)
	{
		memset(cfuncionario.salvar, 0, sizeof(cfuncionario.salvar));

		printf("\n\nTecle [1] SALVAR esse cadastro ou [2] para CANCELAR este cadastro: ");
		tratamento_numeroum(cfuncionario.salvar, 0);
		fseek(stdin, 0, SEEK_END);

		switch (cfuncionario.salvar[0])
		{
		case '1':
			goto fim;
		case '2':
			main_cadastro();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
fim:
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

	printf("\n\nUsuario cadastrado com sucesso! Tecle ENTER para voltar ao menu.");
	getchar();
	main_cadastro();
}

void cad_paciente(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	system("mkdir dados");

	/*CRIAÇÃO DO ARQUIVO*/
	ppatient = fopen("dados\\cad_paciente.txt", "a+");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
	fclose(ppatient);

	patient cpaciente = {'\0'};
	branch *cfilial = calloc(1, sizeof(branch) * 1);
	patient_aux *cpaciente_aux = calloc(1, sizeof(patient_aux) * 1);

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

	/*CARREGAR OS DADOS DOS PACIENTES*/
	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cpaciente_aux->cpf, cpaciente.cpf) == 0 || *cpaciente.cpf == '\0')
	{
		while (strcmp(cpaciente_aux->cpf, cpaciente.cpf) == 0)
		{
			printf("\n\nCPF do paciente: \n");
			tratamento_cpf(cpaciente.cpf, 12);
			fseek(stdin, 0, SEEK_END);

			while (!feof(ppatient) && strcmp(cpaciente_aux->cpf, cpaciente.cpf) != 0)
			{
				fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente_aux->codigo, cpaciente_aux->nome, cpaciente_aux->celular, cpaciente_aux->email, cpaciente_aux->cpf, cpaciente_aux->filial.cnpj, cpaciente_aux->endereco.estado, cpaciente_aux->endereco.cidade, cpaciente_aux->endereco.bairro, cpaciente_aux->endereco.logradouro, cpaciente_aux->endereco.complemento, cpaciente_aux->endereco.cep);
			}
			if (strcmp(cpaciente_aux->cpf, cpaciente.cpf) == 0)
			{
				printf("\n\nCPF ja existe na base de dados!\n");
			}
			else
			{
				break;
			}
		}
	}

	fclose(ppatient);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DAS FILIAIS*/
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cfilial->cnpj, cpaciente.filial.cnpj) != 0 || *cpaciente.filial.cnpj == '\0')
	{
		memset(cpaciente.filial.cnpj, 0, sizeof(cpaciente.filial.cnpj));

		printf("\n\nCNPJ da filial: \n");
		tratamento_cnpj(cpaciente.filial.cnpj, 14);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pfilial) && strcmp(cfilial->cnpj, cpaciente.filial.cnpj) != 0)
		{
			fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
		}

		if (strcmp(cfilial->cnpj, cpaciente.filial.cnpj) != 0)
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

	printf("\n--------- Localizacao --------- \n");

	printf("\n\nEstado do paciente(XX): \n");
	tratamento_estado(cpaciente.endereco.estado, 2);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCidade do paciente: \n");
	tratamento_desc50(cpaciente.endereco.cidade, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nBairro do paciente: \n");
	tratamento_desc50(cpaciente.endereco.bairro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nLogradouro do paciente: \n");
	tratamento_desc50(cpaciente.endereco.logradouro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nComplemento do paciente: \n");
	tratamento_desc50(cpaciente.endereco.complemento, 50);

	printf("\n\nCEP do paciente: \n");
	tratamento_cep(cpaciente.endereco.cep, 8);
	fseek(stdin, 0, SEEK_END);

	ppatient = fopen("dados\\cad_paciente.txt", "a+");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cpaciente.salvar, "1") != 0 || strcmp(cpaciente.salvar, "2") != 0)
	{
		memset(cpaciente.salvar, 0, sizeof(cpaciente.salvar));

		printf("\n\nTecle [1] SALVAR esse cadastro ou [2] para CANCELAR este cadastro: ");
		tratamento_numeroum(cpaciente.salvar, 0);
		fseek(stdin, 0, SEEK_END);

		switch (cpaciente.salvar[0])
		{
		case '1':
			goto fim;
		case '2':
			main_cadastro();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
fim:

	/*Incrementar mais um valor no código usuário*/
	fprintf(ppatient, "%i\n", cpaciente.codigo);
	fprintf(ppatient, "%s\n", cpaciente.nome);
	fprintf(ppatient, "%s\n", cpaciente.celular);
	fprintf(ppatient, "%s\n", cpaciente.email);
	fprintf(ppatient, "%s\n", cpaciente.cpf);
	fprintf(ppatient, "%s\n", cfilial->cnpj);
	fprintf(ppatient, "%s\n", cpaciente.endereco.estado);
	fprintf(ppatient, "%s\n", cpaciente.endereco.cidade);
	fprintf(ppatient, "%s\n", cpaciente.endereco.bairro);
	fprintf(ppatient, "%s\n", cpaciente.endereco.logradouro);
	fprintf(ppatient, "%s\n", cpaciente.endereco.complemento);
	fprintf(ppatient, "%s\n", cpaciente.endereco.cep);
	fclose(ppatient);

	printf("\n\nPaciente cadastrado com sucesso! Tecle ENTER para voltar ao menu.");
	getchar();
	main_cadastro();
}

void cad_medico(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	/*Ponteiros do metodo*/
	system("mkdir dados");
	
	/*CRIAÇÃO DO ARQUIVO*/
	pdoctor = fopen("dados\\cad_medico.txt", "a+");
	if (pdoctor == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de medicos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
	fclose(pdoctor);

	doctor cmedico = {'\0'};
	branch *cfilial = calloc(1, sizeof(branch) * 1);

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

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DAS FILIAIS*/
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cfilial->cnpj, cmedico.filial.cnpj) != 0 || *cmedico.filial.cnpj == '\0')
	{
		memset(cmedico.filial.cnpj, 0, sizeof(cmedico.filial.cnpj));

		printf("\n\nFilial de atuacao do medico(CNPJ): \n");
		tratamento_cnpj(cmedico.filial.cnpj, 15);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pfilial) && strcmp(cfilial->cnpj, cmedico.filial.cnpj) != 0)
		{
			fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
		}

		if (strcmp(cfilial->cnpj, cmedico.filial.cnpj) != 0)
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

	printf("\n\n--------- Localizacao --------- \n");

	printf("\n\nEstado do medico(XX): \n");
	tratamento_estado(cmedico.endereco.estado, 2);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nCidade do medico: \n");
	tratamento_desc50(cmedico.endereco.cidade, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nBairro do medico: \n");
	tratamento_desc50(cmedico.endereco.bairro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nLogradouro do medico: \n");
	tratamento_desc50(cmedico.endereco.logradouro, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nComplemento do medico: \n");
	tratamento_desc50(cmedico.endereco.complemento, 50);

	printf("\n\nCEP do medico: \n");
	tratamento_cep(cmedico.endereco.cep, 8);
	fseek(stdin, 0, SEEK_END);

	pdoctor = fopen("dados\\cad_medico.txt", "a+");
	if (pdoctor == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de medicos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cmedico.salvar, "1") != 0 || strcmp(cmedico.salvar, "2") != 0)
	{
		memset(cmedico.salvar, 0, sizeof(cmedico.salvar));

		printf("\n\nTecle [1] SALVAR esse cadastro ou [2] para CANCELAR este cadastro: ");
		tratamento_numeroum(cmedico.salvar, 0);
		fseek(stdin, 0, SEEK_END);

		switch (cmedico.salvar[0])
		{
		case '1':
			goto fim;
		case '2':
			main_cadastro();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
fim:

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

	printf("\n\nMedico cadastrado com sucesso! Tecle ENTER para voltar ao menu.");
	getchar();
	main_cadastro();
}

void cad_filial(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	/*Ponteiros do metodo*/
	system("mkdir dados");

	/*CRIAÇÃO DO ARQUIVO*/
	pfilial = fopen("dados\\cad_filial.txt", "a+");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
	fclose(pfilial);

	branch cfilial = {'\0'};
	branch_aux *cfilial_aux = calloc(1, sizeof(branch_aux) * 1);

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE FILIAIS\n\n");

	incrementa_id_fili(&cfilial.codigo);
	cfilial.codigo++;

	printf("Codigo de cadastro: %i\n", cfilial.codigo);

	printf("\nNome da filial: \n");
	tratamento_desc50(cfilial.nome, 50);
	fseek(stdin, 0, SEEK_END);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DAS FILIAIS*/
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cfilial_aux->cnpj, cfilial.cnpj) == 0 || *cfilial.cnpj == '\0')
	{
		memset(cfilial.cnpj, 0, sizeof(cfilial.cnpj));

		printf("\n\nCNPJ da filial: \n");
		tratamento_cnpj(cfilial.cnpj, 15);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pfilial) && strcmp(cfilial_aux->cnpj, cfilial.cnpj) != 0)
		{
			fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial_aux->codigo, cfilial_aux->nome, cfilial_aux->cnpj, cfilial_aux->descricao, cfilial_aux->endereco.estado, cfilial_aux->endereco.cidade, cfilial_aux->endereco.bairro, cfilial_aux->endereco.logradouro, cfilial_aux->endereco.complemento, cfilial_aux->endereco.cep);
		}

		if (strcmp(cfilial_aux->cnpj, cfilial.cnpj) == 0)
		{
			printf("\n\nJa existe um CNPJ igual a esse cadastrado!\n");
		}
		else
		{
			break;
		}
	}

	fclose(pfilial);

	/*-----------------------------------------------------------------------*/

	printf("\n\nUma descricao sobre a filial: \n");
	tratamento_desc50(cfilial.descricao, 50);
	fseek(stdin, 0, SEEK_END);

	printf("\n\n--------- Localizacao --------- \n");

	printf("\n\nEstado da filial(XX): \n");
	tratamento_estado(cfilial.endereco.estado, 2);
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
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cfilial.salvar, "1") != 0 || strcmp(cfilial.salvar, "2") != 0)
	{
		memset(cfilial.salvar, 0, sizeof(cfilial.salvar));

		printf("\n\nTecle [1] SALVAR esse cadastro ou [2] para CANCELAR este cadastro: ");
		tratamento_numeroum(cfilial.salvar, 0);
		fseek(stdin, 0, SEEK_END);

		switch (cfilial.salvar[0])
		{
		case '1':
			goto fim;
		case '2':
			main_cadastro();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
fim:

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

	printf("\n\nFilial cadastrada com sucesso! Tecle ENTER para voltar ao menu.");
	getchar();
	main_cadastro();
}

void cad_agendamento(void)
{
	setlocale(LC_ALL, "Portuguese"); //Para acentuação

	/*Ponteiros do metodo*/
	system("mkdir dados");

	/*CRIAÇÃO DO ARQUIVO*/
	pagendamento = fopen("dados\\cad_agendamento.txt", "a+");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
	fclose(pagendamento);

	scheduling cagendamento = {'\0'};
	patient *cpaciente = calloc(1, sizeof(patient) * 1);
	doctor *cmedico = calloc(1, sizeof(doctor) * 1);
	branch *cfilial = calloc(1, sizeof(branch) * 1);
	scheduling_aux *agendamento_aux = calloc(1, sizeof(scheduling_aux) * 1);

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("CADASTRO DE AGENDAMENTOS\n\n");

	incrementa_id_agen(&cagendamento.codigo);
	cagendamento.codigo++;

	printf("Codigo de cadastro: %i\n", cagendamento.codigo);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DOS PACIENTES*/
	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
	
	while (strcmp(cpaciente->cpf, cagendamento.paciente.cpf) != 0 || *cagendamento.paciente.cpf == '\0')
	{
		printf("\nCPF do paciente: \n");
		tratamento_cpf(cagendamento.paciente.cpf, 12);
		fseek(stdin, 0, SEEK_END);

		while (!feof(ppatient) && strcmp(cpaciente->cpf, cagendamento.paciente.cpf) != 0)
		{
			fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->email, cpaciente->cpf, cpaciente->filial.cnpj, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep);
		}
		if (strcmp(cpaciente->cpf, cagendamento.paciente.cpf) != 0)
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
	pdoctor = fopen("dados\\cad_medico.txt", "r");
	if (pdoctor == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de medicas ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cmedico->cpf, cagendamento.medico.cpf) != 0 || *cagendamento.medico.cpf == '\0')
	{
		printf("\nCPF do do Medico: \n");
		tratamento_cpf(cagendamento.medico.cpf, 12);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pdoctor) && strcmp(cmedico->cpf, cagendamento.medico.cpf) != 0)
		{
			fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->email, cmedico->cpf, cmedico->especialidade, cmedico->filial.cnpj, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep);
		}
		if (strcmp(cmedico->cpf, cagendamento.medico.cpf) != 0)
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
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cfilial->cnpj, cagendamento.filial.cnpj) != 0 || *cagendamento.filial.cnpj == '\0')
	{
		memset(cagendamento.filial.cnpj, 0, sizeof(cagendamento.filial.cnpj));

		printf("\nCNPJ da filial: \n");
		tratamento_cnpj(cagendamento.filial.cnpj, 14);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pfilial) && strcmp(cfilial->cnpj, cagendamento.filial.cnpj) != 0)
		{
			fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
		}

		if (strcmp(cfilial->cnpj, cagendamento.filial.cnpj) != 0)
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
	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

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


		fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &agendamento_aux->codigo, agendamento_aux->paciente.cpf, agendamento_aux->paciente.nome, agendamento_aux->medico.cpf, agendamento_aux->medico.nome, agendamento_aux->filial.cnpj, agendamento_aux->filial.nome, agendamento_aux->data, agendamento_aux->hora, agendamento_aux->descricao);

		if (strcmp(agendamento_aux->medico.cpf, cagendamento.medico.cpf) == 0 && strcmp(agendamento_aux->hora, cagendamento.hora) == 0 && strcmp(agendamento_aux->data, cagendamento.data) == 0)
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
	printf("\n\nValor da consulta: \n");
	scanf("%f", &cagendamento.precovalor);
	fseek(stdin, 0, SEEK_END);

	printf("\nDescricao do agendamento: \n");
	tratamento_desc50(cagendamento.descricao, 50);
	fseek(stdin, 0, SEEK_END);

	pagendamento = fopen("dados\\cad_agendamento.txt", "a+");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while (strcmp(cagendamento.salvar, "1") != 0 || strcmp(cagendamento.salvar, "2") != 0)
	{
		memset(cagendamento.salvar, 0, sizeof(cagendamento.salvar));

		printf("\n\nTecle [1] SALVAR esse cadastro ou [2] para CANCELAR este cadastro: ");
		tratamento_numeroum(cagendamento.salvar, 0);
		fseek(stdin, 0, SEEK_END);

		switch (cagendamento.salvar[0])
		{
		case '1':
			goto fim;
		case '2':
			main_cadastro();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}
fim:

	fprintf(pagendamento, "%i\n", cagendamento.codigo);
	fprintf(pagendamento, "%s\n", cpaciente->cpf);
	fprintf(pagendamento, "%s\n", cpaciente->nome);
	fprintf(pagendamento, "%s\n", cmedico->cpf);
	fprintf(pagendamento, "%s\n", cmedico->nome);
	fprintf(pagendamento, "%s\n", cfilial->cnpj);
	fprintf(pagendamento, "%s\n", cfilial->nome);
	fprintf(pagendamento, "%s\n", cagendamento.data);
	fprintf(pagendamento, "%s\n", cagendamento.hora);
	fprintf(pagendamento, "%0.2f\n", cagendamento.precovalor);
	fprintf(pagendamento, "%s\n", cagendamento.descricao);
	fclose(pagendamento);

	printf("\n\nAgendamento realizado com sucesso! Tecle ENTER para voltar ao menu.");
	getchar();
	main_cadastro();
}

void cad_elogio(void)
{
	setlocale(LC_ALL, "Portuguese"); //habilita a acentuação para o português

	evaluation *cavaliacao = calloc(1, sizeof(evaluation) * 1);
	patient *cpaciente = calloc(1, sizeof(patient) * 1);
	scheduling *cagendamento = calloc(1, sizeof(scheduling) * 1);
	scheduling_aux *cagendamento_aux = calloc(1, sizeof(scheduling_aux) * 1);

	pavaliacao = fopen("dados\\cad_avaliacaoe.txt", "a+");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/elogios ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("ELOGIO DO ATENDIMENTO\n\n");

	incrementa_id_avale(&cavaliacao->codigo);
	cavaliacao->codigo++;

	printf("Codigo de cadastro: %i\n", cavaliacao->codigo);
	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DOS AGENDAMENTO*/
	while (strcmp(cpaciente->cpf, cagendamento->paciente.cpf) != 0 || *cagendamento->paciente.cpf == '\0')
	{
		pagendamento = fopen("dados\\cad_agendamento.txt", "r");
		if (pagendamento == NULL)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

			char verificaarq[2];
			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				main_principal();
				break;
			case '2':
				exit(0);
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}

		printf("\nCPF do paciente: \n");
		tratamento_cpf(cpaciente->cpf, 12);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pagendamento) && strcmp(cpaciente->cpf, cagendamento->paciente.cpf) != 0)
		{
			fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao);
		}
		if (strcmp(cpaciente->cpf, cagendamento->paciente.cpf) != 0)
		{
			printf("\n\nCPF Invalido!\n");
		}
		else
		{
			break;
		}
	}

	fclose(pagendamento);
	printf("\n\nNome do paciente: \n%s\n", cagendamento->paciente.nome);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DOS AGENDAMENTO*/
	while (strcmp(cagendamento_aux->data, cagendamento->data) != 0 || *cagendamento->data == '\0')
	{
		pagendamento = fopen("dados\\cad_agendamento.txt", "r");
		if (pagendamento == NULL)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

			char verificaarq[2];
			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				main_principal();
				break;
			case '2':
				exit(0);
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}

		printf("\nData do agendamento: \n");
		tratamento_tdta(cagendamento_aux->data, 8);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pagendamento) && strcmp(cagendamento_aux->data, cagendamento->data) != 0)
		{
			fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao);
		}
		if (strcmp(cagendamento_aux->data, cagendamento->data) != 0)
		{
			printf("\n\nData Invalido!\n");
		}
		else
		{
			break;
		}
	}

	fclose(pagendamento);

	/*-----------------------------------------------------------------------*/

	printf("\n\nDescricao da avaliacao: \n");
	tratamento_desc1500(cavaliacao->elogio, 1500);
	fseek(stdin, 0, SEEK_END);

	pavaliacao = fopen("dados\\cad_avaliacaoe.txt", "a+");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/elogio ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	fprintf(pavaliacao, "%i\n", cavaliacao->codigo);
	fprintf(pavaliacao, "%s\n", cagendamento->paciente.cpf);
	fprintf(pavaliacao, "%s\n", cagendamento->paciente.nome);
	fprintf(pavaliacao, "%s\n", cagendamento->data);
	fprintf(pavaliacao, "%s\n", cavaliacao->elogio);
	fclose(pavaliacao);

	printf("\n\nElogio cadastrada com sucesso! Tecle ENTER realizar um novo elogio.");
	getchar();
	cad_elogio();
}

void cad_reclamacao(void)
{
	setlocale(LC_ALL, "Portuguese"); //habilita a acentuação para o português

	evaluation *cavaliacao = calloc(1, sizeof(evaluation) * 1);
	patient *cpaciente = calloc(1, sizeof(patient) * 1);
	scheduling *cagendamento = calloc(1, sizeof(scheduling) * 1);
	scheduling_aux *cagendamento_aux = calloc(1, sizeof(scheduling_aux) * 1);

	pavaliacao = fopen("dados\\cad_avaliacaor.txt", "a+");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/reclamacao ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	/*Cadastro dos dados*/
	printf("\033[2J\033[1;1H");
	printf("RECLAMACAO DO ATENDIMENTO\n\n");

	incrementa_id_avalr(&cavaliacao->codigo);
	cavaliacao->codigo++;

	printf("Codigo de cadastro: %i\n", cavaliacao->codigo);
	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DOS AGENDAMENTO*/
	while (strcmp(cpaciente->cpf, cagendamento->paciente.cpf) != 0 || *cagendamento->paciente.cpf == '\0')
	{
		pagendamento = fopen("dados\\cad_agendamento.txt", "r");
		if (pagendamento == NULL)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

			char verificaarq[2];
			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				main_principal();
				break;
			case '2':
				exit(0);
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}

		printf("\nCPF do paciente: \n");
		tratamento_cpf(cpaciente->cpf, 12);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pagendamento) && strcmp(cpaciente->cpf, cagendamento->paciente.cpf) != 0)
		{
			fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao);
		}
		if (strcmp(cpaciente->cpf, cagendamento->paciente.cpf) != 0)
		{
			printf("\n\nCPF Invalido!\n");
		}
		else
		{
			break;
		}
	}

	fclose(pagendamento);
	printf("\n\nNome do paciente: \n%s\n", cagendamento->paciente.nome);

	/*-----------------------------------------------------------------------*/

	/*CARREGAR OS DADOS DOS AGENDAMENTO*/
	while (strcmp(cagendamento_aux->data, cagendamento->data) != 0 || *cagendamento->data == '\0')
	{
		pagendamento = fopen("dados\\cad_agendamento.txt", "r");
		if (pagendamento == NULL)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

			char verificaarq[2];
			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				main_principal();
				break;
			case '2':
				exit(0);
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}

		printf("\nData do agendamento: \n");
		tratamento_tdta(cagendamento_aux->data, 8);
		fseek(stdin, 0, SEEK_END);

		while (!feof(pagendamento) && strcmp(cagendamento_aux->data, cagendamento->data) != 0)
		{
			fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao);
		}
		if (strcmp(cagendamento_aux->data, cagendamento->data) != 0)
		{
			printf("\n\nData Invalido!\n");
		}
		else
		{
			break;
		}
	}

	fclose(pagendamento);

	/*-----------------------------------------------------------------------*/

	printf("\n\nDescricao da avaliacao: \n");
	tratamento_desc1500(cavaliacao->reclamacao, 1500);
	fseek(stdin, 0, SEEK_END);

	pavaliacao = fopen("dados\\cad_avaliacaor.txt", "a+");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/reclamacao ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	fprintf(pavaliacao, "%i\n", cavaliacao->codigo);
	fprintf(pavaliacao, "%s\n", cagendamento->paciente.cpf);
	fprintf(pavaliacao, "%s\n", cagendamento->paciente.nome);
	fprintf(pavaliacao, "%s\n", cagendamento->data);
	fprintf(pavaliacao, "%s\n", cavaliacao->reclamacao);
	fclose(pavaliacao);

	printf("\n\nReclamacao cadastrada com sucesso! Tecle ENTER realizar uma nova reclamacao.");
	getchar();
	cad_reclamacao();
}

/*-----------------------------------------------------------------------*/

/*CONSULTA TELAS*/
int con_usuario(void)
{
	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de funcionarios ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	user *cusuario = calloc(1, sizeof(user) * 1);
	char scan[14];

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE USUARIOS DO SISTEMA\n\n");

	printf("Favor digite o cpf desejado: ");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	while (!feof(puser) && strcmp(cusuario->cpf, scan) != 0)
	{
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->email, cusuario->cpf, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep);
	}

	fclose(puser);
	if (strcmp(cusuario->cpf, scan) == 0)
	{
		memset(cusuario->senha, 0, sizeof(cusuario->senha));

		printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nUsuario no sistema: %s\nSenha: %s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->celular + 2, cusuario->celular + 7, cusuario->email, cusuario->cpf, cusuario->cpf + 3, cusuario->cpf + 6, cusuario->cpf + 9, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep, cusuario->endereco.cep + 5);

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo usuario: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cusuario);
				con_usuario();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("\n\nCPF incorreto ou inexistente!\n");

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo usuario: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cusuario);
				con_usuario();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	getchar();
	return 0;
	main_consulta();
}

int con_paciente(void)
{
	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	patient *cpaciente = calloc(1, sizeof(patient) * 1);

	char scan[14];

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE PACIENTES\n\n");

	printf("Favor digite o CPF desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	while (!feof(ppatient) && strcmp(cpaciente->cpf, scan) != 0)
	{
		fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->email, cpaciente->cpf, cpaciente->filial.cnpj, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep);
	}

	fclose(ppatient);
	if (strcmp(cpaciente->cpf, scan) == 0)
	{
		printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nCNPJ da filial: %.2s.%.3s.%.3s/%.4s-%.2s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->celular + 2, cpaciente->celular + 7, cpaciente->email, cpaciente->cpf, cpaciente->cpf + 3, cpaciente->cpf + 6, cpaciente->cpf + 9, cpaciente->filial.cnpj, cpaciente->filial.cnpj + 2, cpaciente->filial.cnpj + 5, cpaciente->filial.cnpj + 8, cpaciente->filial.cnpj + 12, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep, cpaciente->endereco.cep + 5);

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo paciente: ");

			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cpaciente);
				con_paciente();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("\n\nCPF incorreto ou inexistente!\n");

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo paciente: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cpaciente);
				con_paciente();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	getchar();
	return 0;
	main_consulta();
}

int con_medico(void)
{
	pdoctor = fopen("dados\\cad_medico.txt", "r");
	if (pdoctor == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de medicos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	doctor *cmedico = calloc(1, sizeof(doctor) * 1);

	char scan[14];

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE MEDICOS\n\n");

	printf("Favor digite o CPF desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pdoctor) && strcmp(cmedico->cpf, scan) != 0)
	{
		fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->email, cmedico->cpf, cmedico->especialidade, cmedico->filial.cnpj, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep);
	}

	fclose(pdoctor);
	if (strcmp(cmedico->cpf, scan) == 0)
	{
		printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nEspecialidade: %s\nFilial de atuacao(CNPJ): %.2s.%.3s.%.3s/%.4s-%.2s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->celular + 2, cmedico->celular + 7, cmedico->email, cmedico->cpf, cmedico->cpf + 3, cmedico->cpf + 6, cmedico->cpf + 9, cmedico->especialidade, cmedico->filial.cnpj, cmedico->filial.cnpj + 2, cmedico->filial.cnpj + 5, cmedico->filial.cnpj + 8, cmedico->filial.cnpj + 12, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep, cmedico->endereco.cep + 5);

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo medico: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cmedico);
				con_medico();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("\n\nCNPJ incorreto ou inexistente!\n");

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo medico: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cmedico);
				con_medico();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	getchar();
	return 0;
	main_consulta();
}

int con_filial(void)
{
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	branch *cfilial = calloc(1, sizeof(branch) * 1);

	char scan[14];

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE FILIAIS\n\n");

	printf("Favor digite o CNPJ desejado:");
	tratamento_cnpj(scan, 15);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pfilial) && strcmp(cfilial->cnpj, scan) != 0)
	{
		fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
	}

	fclose(pfilial);

	if (strcmp(cfilial->cnpj, scan) == 0)
	{
		printf("\n\nCodigo: %i\nNome: %s\ncnpj: %.2s.%.3s.%.3s/%.4s-%.2s\nDescricao: %s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->cnpj + 2, cfilial->cnpj + 5, cfilial->cnpj + 8, cfilial->cnpj + 12, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep, cfilial->endereco.cep + 5);

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar uma nova filial: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cfilial);
				con_filial();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("\n\nCNPJ incorreto ou inexistente!\n");
		
		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar uma nova filial: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cfilial);
				con_filial();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	getchar();
	return 0;
	main_consulta();
}

int con_agendamento(void)
{
	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	scheduling *cagendamento = calloc(1, sizeof(scheduling) * 1);
	scheduling_aux *cagendamento_aux = calloc(1, sizeof(scheduling_aux) * 1);

	char scan[12];
	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE AGENDAMENTOS\n\n");

	printf("Favor digite o cpf desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nData do agendamento: ");
	tratamento_tdtaqq(cagendamento_aux->data, 8);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pagendamento) && (strcmp(cagendamento->paciente.cpf, scan) != 0))
	{
		fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao);
	}

	fclose(pagendamento);

	if ((strcmp(cagendamento->paciente.cpf, scan) == 0))
	{
		printf("\n\nCodigo: %i\nCPF do paciente: %.3s.%.3s.%.3s-%.2s\nNome do paciente: %s\nCPF do medico: %.3s.%.3s.%.3s-%.2s\nNome do medico: %s\nCNPJ da filial: %.2s.%.3s.%.3s/%.4s-%.2s\nNome da Filial: %s\nData do agendamento: %.2s/%.2s/%.4s\nHora do Agendamento: %.2s:%.2s\nValor da consulta: %0.2f\nDescricao: %s\n", cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.cpf + 3, cagendamento->paciente.cpf + 6, cagendamento->paciente.cpf + 9, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.cpf + 3, cagendamento->medico.cpf + 6, cagendamento->medico.cpf + 9, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.cnpj + 2, cagendamento->filial.cnpj + 5, cagendamento->filial.cnpj + 8, cagendamento->filial.cnpj + 12, cagendamento->filial.nome, cagendamento->data, cagendamento->data + 2, cagendamento->data + 4, cagendamento->hora, cagendamento->hora + 2, cagendamento->precovalor, cagendamento->descricao);

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar uma nova agendamento: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cagendamento);
				con_agendamento();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("\n\nCPF incorreto ou inexistente!\n");

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar uma nova agendamento: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_consulta();
				break;
			case '2':
				free(cagendamento);
				con_agendamento();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	getchar();
	return 0;
	main_consulta();
}

int con_elogio(void)
{
	pavaliacao = fopen("dados\\cad_avaliacaoe.txt", "r");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/elogio ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	evaluation *cavaliacao = calloc(1, sizeof(evaluation) * 1);
	evaluation_aux *cavaliacao_aux = calloc(1, sizeof(evaluation_aux) * 1);

	char scan[14];

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE ELOGIOS\n\n");

	printf("Favor digite o CPF desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nData do agendamento: ");
	tratamento_tdtaqq(cavaliacao_aux->agendamento.data, 8);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pavaliacao) && (strcmp(cavaliacao->agendamento.paciente.cpf, scan) != 0 && strcmp(cavaliacao_aux->agendamento.data, cavaliacao->agendamento.data) != 0))
	{
		fscanf(pavaliacao, "%d\n %[^\n] %[^\n] %[^\n] %[^\n]", &cavaliacao->codigo, cavaliacao->agendamento.paciente.cpf, cavaliacao->agendamento.paciente.nome, cavaliacao->agendamento.data, cavaliacao->elogio);
	}

	fclose(pavaliacao);

	if (strcmp(cavaliacao->agendamento.paciente.cpf, scan) == 0 && strcmp(cavaliacao_aux->agendamento.data, cavaliacao->agendamento.data) == 0)
	{
		printf("\n\nCodigo: %i\nCPF: %.3s.%.3s.%.3s-%.2s\nNome: %s\nData do agendamento: %.2s/%.2s/%.4s\nDescricao: %s\n", cavaliacao->codigo, cavaliacao->agendamento.paciente.cpf, cavaliacao->agendamento.paciente.cpf + 3, cavaliacao->agendamento.paciente.cpf + 6, cavaliacao->agendamento.paciente.cpf + 9, cavaliacao->agendamento.paciente.nome, cavaliacao->agendamento.data, cavaliacao->agendamento.data + 2, cavaliacao->agendamento.data + 4, cavaliacao->elogio);

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo elogio: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_avaliacao();
				break;
			case '2':
				free(cavaliacao);
				free(cavaliacao_aux);
				con_elogio();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("\n\nCPF ou Data incorreto ou inexistente!\n");

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo elogio: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_avaliacao();
				break;
			case '2':
				free(cavaliacao);
				free(cavaliacao_aux);
				con_elogio();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	getchar();
	return 0;
	main_avaliacao();
}

int con_reclamacao(void)
{
	pavaliacao = fopen("dados\\cad_avaliacaor.txt", "r");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/reclamacao ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	evaluation *cavaliacao = calloc(1, sizeof(evaluation) * 1);
	evaluation_aux *cavaliacao_aux = calloc(1, sizeof(evaluation_aux) * 1);

	char scan[14];

	printf("\033[2J\033[1;1H");
	printf("CONSULTA DE RECLAMACOES\n\n");

	printf("Favor digite o CPF desejado:");
	tratamento_cpf(scan, 12);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nData do agendamento: ");
	tratamento_tdtaqq(cavaliacao_aux->agendamento.data, 8);
	fseek(stdin, 0, SEEK_END);

	while (!feof(pavaliacao) && (strcmp(cavaliacao->agendamento.paciente.cpf, scan) != 0 && strcmp(cavaliacao_aux->agendamento.data, cavaliacao->agendamento.data) != 0))
	{
		fscanf(pavaliacao, "%d\n %[^\n] %[^\n] %[^\n] %[^\n]", &cavaliacao->codigo, cavaliacao->agendamento.paciente.cpf, cavaliacao->agendamento.paciente.nome, cavaliacao->agendamento.data, cavaliacao->reclamacao);
	}

	fclose(pavaliacao);

	if (strcmp(cavaliacao->agendamento.paciente.cpf, scan) == 0 && strcmp(cavaliacao_aux->agendamento.data, cavaliacao->agendamento.data) == 0)
	{
		printf("\n\nCodigo: %i\nCPF: %.3s.%.3s.%.3s-%.2s\nNome: %s\nData do agendamento: %.2s/%.2s/%.4s\nDescricao: %s\n", cavaliacao->codigo, cavaliacao->agendamento.paciente.cpf, cavaliacao->agendamento.paciente.cpf + 3, cavaliacao->agendamento.paciente.cpf + 6, cavaliacao->agendamento.paciente.cpf + 9, cavaliacao->agendamento.paciente.nome, cavaliacao->agendamento.data, cavaliacao->agendamento.data + 2, cavaliacao->agendamento.data + 4, cavaliacao->reclamacao);

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo reclamacao: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_avaliacao();
				break;
			case '2':
				free(cavaliacao);
				free(cavaliacao_aux);
				con_reclamacao();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("\n\nCPF ou Data incorreto ou inexistente!\n");

		char func_con[2];

		while((strcmp(func_con, "1") != 0) || (strcmp(func_con, "2") != 0))
		{	
			memset(func_con, 0, sizeof(func_con));

			printf("\n\nTecle [1] para voltar ou [2] consultar um novo reclamacao: ");
			tratamento_numeroum(func_con, 0);

			switch (func_con[0])
			{
			case '1':
				main_avaliacao();
				break;
			case '2':
				free(cavaliacao);
				free(cavaliacao_aux);
				con_reclamacao();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].\n\n");
				system("pause");
			}
		}
	}
	getchar();
	return 0;
	main_avaliacao();
}
/*-----------------------------------------------------------------------*/

/*ALTERAR TELAS*/
void alterar_usuario(void)
{
	int test;
	test = 0;

	user *cusuario = calloc(1, sizeof(user) * 1);
	user_upd *cusuario_upd = calloc(1, sizeof(user_upd) * 1);
	user_aux *cusuario_aux = calloc(1, sizeof(user_aux) * 1);

	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de funcionarios ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_user_upd.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de temporario de alteração do usuario, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("ALTERAR USUARIO CADASTRADO\n\n");

	printf("Para alterar um usuario, insira o CPF do usuario: ");
	tratamento_cpf(cusuario_aux->cpf, 11);

	while (fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->email, cusuario->cpf, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep) != EOF)
	{
		if (strcmp(cusuario->cpf, cusuario_aux->cpf) == 0)
		{
			retornaalteracao:
			test = 1;
			memset(cusuario->alterar, 0, sizeof(cusuario->alterar));

			printf("\n\n1.Nome\n2.Celular\n3.E-mail\n4.CPF\n5.Usuario\n6.Senha\n");
			mostrarendereco();
			tratamento_numero(cusuario->alterar, 2);

			/*NOME*/
			if (strcmp(cusuario->alterar, "1") == 0)
			{
				printf("\nNome do funcionario: \n");
				tratamento_desc50(cusuario_upd->nome, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario_upd->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
			}
			/*CELULAR*/
			else if (strcmp(cusuario->alterar, "2") == 0)
			{
				printf("\n\nCelular do funcionario: \n");
				tratamento_celular(cusuario_upd->celular, 11);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario_upd->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
			}
			/*E-MAIL*/
			else if (strcmp(cusuario->alterar, "3") == 0)
			{
				printf("\n\nE-mail do funcionario: \n");
				tratamento_desc50(cusuario_upd->email, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario_upd->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
			}
			/*CPF*/
			else if (strcmp(cusuario->alterar, "4") == 0)
			{
				printf("\n\nCPF do funcionario: \n");
				tratamento_cpf(cusuario_upd->cpf, 12);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario_upd->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
			}
			/*USUARIO*/
			else if (strcmp(cusuario->alterar, "5") == 0)
			{
				printf("\n\nUsuario para funcionario: \n");
				tratamento_desc50(cusuario_upd->usuario, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario_upd->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
			}
			/*SENHA*/
			else if (strcmp(cusuario->alterar, "6") == 0)
			{
				/* ---------- TRATAMENTO NO CAMPO SENHA ---------- */
				while (strcmp(cusuario_upd->senha, cusuario_upd->senha2) != 0 || strcmp(cusuario_upd->senha, cusuario_upd->senha2) == '\0')
				{
					printf("\n\nSenha do usuario: \n");
					tratamento_senha(cusuario_upd->senha, 50);
					fseek(stdin, 0, SEEK_END);

					printf("\n\nDigite a senha novamente: \n");
					tratamento_senha(cusuario_upd->senha2, 50);
					fseek(stdin, 0, SEEK_END);

					if (strcmp(cusuario_upd->senha, cusuario_upd->senha2) != 0)
					{
						memset(cusuario_upd->senha, 0, sizeof(cusuario_upd->senha));
						memset(cusuario_upd->senha2, 0, sizeof(cusuario_upd->senha2));
						printf("\nAs senhas nao conferem, adicione senhas iguais!\n");
					}
					else
					{
						int i = 0, tam_msg = 0;
						char crip_msg[52];
						/*GRAVAR OS DADOS NO ARQUIVO DE TEXTO*/
						tam_msg = strlen(cusuario_upd->senha);
						for (i = 0; i < tam_msg; i++)
						{
							crip_msg[i] = cusuario_upd->senha[i] + 5;
						}
						crip_msg[tam_msg] = '\0';

						fprintf(temporario, "%i\n", cusuario->codigo);
						fprintf(temporario, "%s\n", cusuario->nome);
						fprintf(temporario, "%s\n", cusuario->celular);
						fprintf(temporario, "%s\n", cusuario->email);
						fprintf(temporario, "%s\n", cusuario->cpf);
						fprintf(temporario, "%s\n", cusuario->usuario);
						fprintf(temporario, "%s\n", crip_msg);
						fprintf(temporario, "%s\n", cusuario->endereco.estado);
						fprintf(temporario, "%s\n", cusuario->endereco.cidade);
						fprintf(temporario, "%s\n", cusuario->endereco.bairro);
						fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
						fprintf(temporario, "%s\n", cusuario->endereco.complemento);
						fprintf(temporario, "%s\n", cusuario->endereco.cep);
						printf("\033[2J\033[1;1H");

						break;
					}
				}
			}
			/*ESTADO*/
			else if (strcmp(cusuario->alterar, "11") == 0)
			{
				printf("\n\nEstado do Usuario(XX): \n");
				tratamento_estado(cusuario_upd->endereco.estado, 2);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario_upd->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
				printf("\033[2J\033[1;1H");
			}
			/*CIDADE*/
			else if (strcmp(cusuario->alterar, "12") == 0)
			{
				printf("\n\nCidade do Usuario: \n");
				tratamento_desc50(cusuario_upd->endereco.cidade, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario_upd->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
				printf("\033[2J\033[1;1H");
			}
			/*BAIRRO*/
			else if (strcmp(cusuario->alterar, "13") == 0)
			{
				printf("\n\nBairro do Usuario: \n");
				tratamento_desc50(cusuario_upd->endereco.bairro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario_upd->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
				printf("\033[2J\033[1;1H");
			}
			/*LOGRADOURO*/
			else if (strcmp(cusuario->alterar, "14") == 0)
			{
				printf("\n\nLogradouro do Usuario: \n");
				tratamento_desc50(cusuario_upd->endereco.logradouro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario_upd->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
				printf("\033[2J\033[1;1H");
			}
			/*COMPLEMENTO*/
			else if (strcmp(cusuario->alterar, "15") == 0)
			{
				printf("\n\nComplemento do Usuario: \n");
				tratamento_desc50(cusuario_upd->endereco.complemento, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario_upd->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario->endereco.cep);
				printf("\033[2J\033[1;1H");
			}
			/*CEP*/
			else if (strcmp(cusuario->alterar, "16") == 0)
			{
				printf("\n\nCEP do Usuario: \n");
				tratamento_cep(cusuario_upd->endereco.cep, 8);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cusuario->codigo);
				fprintf(temporario, "%s\n", cusuario->nome);
				fprintf(temporario, "%s\n", cusuario->celular);
				fprintf(temporario, "%s\n", cusuario->email);
				fprintf(temporario, "%s\n", cusuario->cpf);
				fprintf(temporario, "%s\n", cusuario->usuario);
				fprintf(temporario, "%s\n", cusuario->senha);
				fprintf(temporario, "%s\n", cusuario->endereco.estado);
				fprintf(temporario, "%s\n", cusuario->endereco.cidade);
				fprintf(temporario, "%s\n", cusuario->endereco.bairro);
				fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
				fprintf(temporario, "%s\n", cusuario->endereco.complemento);
				fprintf(temporario, "%s\n", cusuario_upd->endereco.cep);
				printf("\033[2J\033[1;1H");
			}
			else
			{
				printf("\033[2J\033[1;1H");
				printf("\nATENCAO! Menu inexistente, tente um valor valido!");
				goto retornaalteracao;
			}
		}
		else
		{
			fprintf(temporario, "%i\n", cusuario->codigo);
			fprintf(temporario, "%s\n", cusuario->nome);
			fprintf(temporario, "%s\n", cusuario->celular);
			fprintf(temporario, "%s\n", cusuario->email);
			fprintf(temporario, "%s\n", cusuario->cpf);
			fprintf(temporario, "%s\n", cusuario->usuario);
			fprintf(temporario, "%s\n", cusuario->senha);
			fprintf(temporario, "%s\n", cusuario->endereco.estado);
			fprintf(temporario, "%s\n", cusuario->endereco.cidade);
			fprintf(temporario, "%s\n", cusuario->endereco.bairro);
			fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
			fprintf(temporario, "%s\n", cusuario->endereco.complemento);
			fprintf(temporario, "%s\n", cusuario->endereco.cep);
		}
	}

	fclose(temporario);
	fclose(puser);

	while ((strcmp(cusuario->salvar, "1") != 0 || strcmp(cusuario->salvar, "2") != 0) && test != 1)
	{
		printf("\n\n\nNao ha registros com esse CPF!\n\n");

		while((strcmp(cusuario->salvar, "1") != 0) || (strcmp(cusuario->salvar, "2") != 0))
		{
			memset(cusuario->salvar, 0, sizeof(cusuario->salvar));

			printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
			tratamento_numeroum(cusuario->salvar, 0);

			switch (cusuario->salvar[0])
			{
			case '1':
				alterar_usuario();
				break;
			case '2':
				main_alterar();
				break;
			default:
				printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
				system("pause");
			}
		}
	}

	while ((strcmp(cusuario->salvar, "1") != 0 || strcmp(cusuario->salvar, "2") != 0))
	{
		memset(cusuario->salvar, 0, sizeof(cusuario->salvar));

		printf("\n\nTecle [1] para confirmar a ALTERACAO desse usuario ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cusuario->salvar, 0);

		if (strcmp(cusuario->salvar, "2") == 0)
		{
			remove("dados\\temp_user_upd.txt");
			break;
		}

		switch (cusuario->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_alterar();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
			system("pause");
		}

		if((strcmp(cusuario->salvar, "1") == 0 || strcmp(cusuario->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_funcionario.txt");
			if (rem == 0)
			{
				rename("dados\\temp_user_upd.txt", "dados\\cad_funcionario.txt");
				printf("\nAlteracao realizada!\n\n");
				break;
			}
			else
			{
				remove("dados\\temp_user_upd.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}
	}

	system("pause");
	main_alterar();
}

void alterar_paciente(void)
{
	int test;
	test = 0;

	patient *cpaciente = calloc(1, sizeof(patient) * 1);
	patient_upd *cpaciente_upd = calloc(1, sizeof(patient_upd) * 1);
	patient_aux *cpaciente_aux = calloc(1, sizeof(patient_aux) * 1);
	branch *cfilial = calloc(1, sizeof(branch) * 1);

	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_paciente_upd.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de temporario de alteracao de pacientes, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("ALTERAR PACIENTE CADASTRADO\n\n");

	printf("Para alterar um paciente, insira o CPF do paciente: ");
	tratamento_cpf(cpaciente_aux->cpf, 11);

	while (fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->email, cpaciente->cpf, cpaciente->filial.cnpj, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep) != EOF)
	{
		if (strcmp(cpaciente->cpf, cpaciente_aux->cpf) == 0)
		{
			retornaalteracao:
			test = 1;
			memset(cpaciente->alterar, 0, sizeof(cpaciente->alterar));

			printf("\n\n1.Nome\n2.Celular\n3.E-mail\n4.CPF\n5.CNPJ da unidade\n");
			mostrarendereco();
			tratamento_numero(cpaciente->alterar, 2);

			/*NOME*/
			if (strcmp(cpaciente->alterar, "1") == 0)
			{
				printf("\nNome do paciente: \n");
				tratamento_desc50(cpaciente_upd->nome, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente_upd->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*CELULAR*/
			else if (strcmp(cpaciente->alterar, "2") == 0)
			{
				printf("\n\nCelular do paciente: \n");
				tratamento_celular(cpaciente_upd->celular, 11);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente_upd->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*E-MAIL*/
			else if (strcmp(cpaciente->alterar, "3") == 0)
			{
				printf("\n\nE-mail do paciente: \n");
				tratamento_desc50(cpaciente_upd->email, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente_upd->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*CPF*/
			else if (strcmp(cpaciente->alterar, "4") == 0)
			{
				printf("\n\nCPF do paciente: \n");
				tratamento_cpf(cpaciente_upd->cpf, 12);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente_upd->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*CNPJ*/
			else if (strcmp(cpaciente->alterar, "5") == 0)
			{
				/*-----------------------------------------------------------------------*/

				/*CARREGAR OS DADOS DAS FILIAIS*/
				while (strcmp(cfilial->cnpj, cpaciente_upd->filial.cnpj) != 0 || *cpaciente_upd->filial.cnpj == '\0')
				{
					pfilial = fopen("dados\\cad_filial.txt", "r");
					if (pfilial == NULL)
					{
						fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

						char verificaarq[2];
						memset(verificaarq, 0, sizeof(verificaarq));

						printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
						tratamento_numeroum(verificaarq, 0);

						switch (verificaarq[0])
						{
						case '1':
							main_principal();
							break;
						case '2':
							exit(0);
						default:
							printf("\nMenu inexistente, tente novamente [1] ou [2].");
							system("pause");
						}
					}

					memset(cpaciente_upd->filial.cnpj, 0, sizeof(cpaciente_upd->filial.cnpj));

					printf("\nCNPJ da filial: \n");
					tratamento_cnpj(cpaciente_upd->filial.cnpj, 14);
					fseek(stdin, 0, SEEK_END);

					while (!feof(pfilial) && strcmp(cfilial->cnpj, cpaciente_upd->filial.cnpj) != 0)
					{
						fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
					}

					if (strcmp(cfilial->cnpj, cpaciente_upd->filial.cnpj) != 0)
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

				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente_upd->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*ESTADO*/
			else if (strcmp(cpaciente->alterar, "11") == 0)
			{
				printf("\n\nEstado do Paciente(XX): \n");
				tratamento_estado(cpaciente_upd->endereco.estado, 2);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente_upd->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*CIDADE*/
			else if (strcmp(cpaciente->alterar, "12") == 0)
			{
				printf("\n\nCidade do Paciente: \n");
				tratamento_desc50(cpaciente_upd->endereco.cidade, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente_upd->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*BAIRRO*/
			else if (strcmp(cpaciente->alterar, "13") == 0)
			{
				printf("\n\nBairro do Paciente: \n");
				tratamento_desc50(cpaciente_upd->endereco.bairro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente_upd->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*LOGRADOURO*/
			else if (strcmp(cpaciente->alterar, "14") == 0)
			{
				printf("\n\nLogradouro do Paciente: \n");
				tratamento_desc50(cpaciente_upd->endereco.logradouro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente_upd->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*COMPLEMENTO*/
			else if (strcmp(cpaciente->alterar, "15") == 0)
			{
				printf("\n\nComplemento do Paciente: \n");
				tratamento_desc50(cpaciente_upd->endereco.complemento, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente_upd->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente->endereco.cep);
			}
			/*CEP*/
			else if (strcmp(cpaciente->alterar, "16") == 0)
			{
				printf("\n\nCEP do Paciente: \n");
				tratamento_cep(cpaciente_upd->endereco.cep, 8);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cpaciente->codigo);
				fprintf(temporario, "%s\n", cpaciente->nome);
				fprintf(temporario, "%s\n", cpaciente->celular);
				fprintf(temporario, "%s\n", cpaciente->email);
				fprintf(temporario, "%s\n", cpaciente->cpf);
				fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
				fprintf(temporario, "%s\n", cpaciente->endereco.estado);
				fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
				fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
				fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
				fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
				fprintf(temporario, "%s\n", cpaciente_upd->endereco.cep);
			}
			/*VALOR NAO CORRESPONDE AO MENU*/
			else
			{
				printf("\033[2J\033[1;1H");
				printf("\nATENCAO! Menu inexistente, tente um valor valido!");
				goto retornaalteracao;
			}
		}
		else
		{
			fprintf(temporario, "%i\n", cpaciente->codigo);
			fprintf(temporario, "%s\n", cpaciente->nome);
			fprintf(temporario, "%s\n", cpaciente->celular);
			fprintf(temporario, "%s\n", cpaciente->email);
			fprintf(temporario, "%s\n", cpaciente->cpf);
			fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
			fprintf(temporario, "%s\n", cpaciente->endereco.estado);
			fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
			fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
			fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
			fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
			fprintf(temporario, "%s\n", cpaciente->endereco.cep);
		}
	}

	fclose(ppatient);
	fclose(temporario);

	while ((strcmp(cpaciente->salvar, "1") != 0 || strcmp(cpaciente->salvar, "2") != 0) && test != 1)
	{
		printf("\n\n\nNao ha registros com esse CPF!\n\n");

		while((strcmp(cpaciente->salvar, "1") != 0) || (strcmp(cpaciente->salvar, "2") != 0))
		{
			printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
			tratamento_numeroum(cpaciente->salvar, 0);

			switch (cpaciente->salvar[0])
			{
			case '1':
				alterar_paciente();
				break;
			case '2':
				main_alterar();
				break;
			default:
				printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
				system("pause");
			}
		}
	}

	while ((strcmp(cpaciente->salvar, "1") != 0 || strcmp(cpaciente->salvar, "2") != 0))
	{
		memset(cpaciente->salvar, 0, sizeof(cpaciente->salvar));

		printf("\n\nTecle [1] para confirmar a ALTERACAO desse paciente ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cpaciente->salvar, 0);

		if (strcmp(cpaciente->salvar, "2") == 0)
		{
			remove("dados\\temp_paciente_upd.txt");
			break;
		}

		switch (cpaciente->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_alterar();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
			system("pause");
		}

		fclose(ppatient);
		fclose(temporario);

		if((strcmp(cpaciente->salvar, "1") == 0 || strcmp(cpaciente->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_paciente.txt");
			if (rem == 0)
			{
				rename("dados\\temp_paciente_upd.txt", "dados\\cad_paciente.txt");
				printf("\nAlteracao realizada!\n\n");
				break;
			}
			else
			{
				remove("dados\\temp_paciente_upd.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}	
	}
	system("pause");
	main_alterar();
}

void alterar_medico(void)
{
	int test;
	test = 0;

	doctor *cmedico = calloc(1, sizeof(doctor) * 1);
	doctor_upd *cmedico_upd = calloc(1, sizeof(doctor_upd) * 1);
	doctor_aux *cmedico_aux = calloc(1, sizeof(doctor_aux) * 1);
	branch *cfilial = calloc(1, sizeof(branch) * 1);

	pdoctor = fopen("dados\\cad_medico.txt", "r");
	if (pdoctor == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de medicos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_medico_upd.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de temporario de alteracao de medico, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("ALTERAR MEDICO CADASTRADO\n\n");

	printf("Para alterar um medico, insira o CPF do medico: ");
	tratamento_cpf(cmedico_aux->cpf, 11);

	while (fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->email, cmedico->cpf, cmedico->especialidade, cmedico->filial.cnpj, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep) != EOF)
	{
		if (strcmp(cmedico->cpf, cmedico_aux->cpf) == 0)
		{
			retornaalteracao:
			test = 1;
			memset(cmedico->alterar, 0, sizeof(cmedico->alterar));

			printf("\n\n1.Nome\n2.Celular\n3.E-mail\n4.CPF\n5.Especialidade\n6.Filial de atuacao\n");
			mostrarendereco();
			tratamento_numero(cmedico->alterar, 2);

			/*NOME*/
			if (strcmp(cmedico->alterar, "1") == 0)
			{
				printf("\nNome do medico: \n");
				tratamento_desc50(cmedico_upd->nome, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico_upd->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*CELULAR*/
			else if (strcmp(cmedico->alterar, "2") == 0)
			{
				printf("\n\nCelular do medico: \n");
				tratamento_celular(cmedico_upd->celular, 11);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico_upd->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*E-MAIL*/
			else if (strcmp(cmedico->alterar, "3") == 0)
			{
				printf("\n\nE-mail do medico: \n");
				tratamento_desc50(cmedico_upd->email, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico_upd->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*CPF*/
			else if (strcmp(cmedico->alterar, "4") == 0)
			{
				printf("\n\nCPF do medico: \n");
				tratamento_cpf(cmedico_upd->cpf, 12);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico_upd->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*ESPECIALIDADE*/
			else if (strcmp(cmedico->alterar, "5") == 0)
			{
				printf("\n\nEspecialidade do medico: \n");
				tratamento_desc50(cmedico_upd->especialidade, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico_upd->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*FILIAL DE ATUACAO*/
			else if (strcmp(cmedico->alterar, "6") == 0)
			{
				/*-----------------------------------------------------------------------*/

				/*CARREGAR OS DADOS DAS FILIAIS*/
				while (strcmp(cfilial->cnpj, cmedico_upd->filial.cnpj) != 0 || *cmedico_upd->filial.cnpj == '\0')
				{
					pfilial = fopen("dados\\cad_filial.txt", "r");
					if (pfilial == NULL)
					{
						fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

						char verificaarq[2];
						memset(verificaarq, 0, sizeof(verificaarq));

						printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
						tratamento_numeroum(verificaarq, 0);

						switch (verificaarq[0])
						{
						case '1':
							main_principal();
							break;
						case '2':
							exit(0);
						default:
							printf("\nMenu inexistente, tente novamente [1] ou [2].");
							system("pause");
						}
					}

					memset(cmedico_upd->filial.cnpj, 0, sizeof(cmedico_upd->filial.cnpj));

					printf("\nCNPJ da filial: \n");
					tratamento_cnpj(cmedico_upd->filial.cnpj, 14);
					fseek(stdin, 0, SEEK_END);

					while (!feof(pfilial) && strcmp(cfilial->cnpj, cmedico_upd->filial.cnpj) != 0)
					{
						fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
					}

					if (strcmp(cfilial->cnpj, cmedico_upd->filial.cnpj) != 0)
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

				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico_upd->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*ESTADO*/
			else if (strcmp(cmedico->alterar, "11") == 0)
			{
				printf("\n\nEstado do medico(XX): \n");
				tratamento_estado(cmedico_upd->endereco.estado, 2);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico_upd->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*CIDADE*/
			else if (strcmp(cmedico->alterar, "12") == 0)
			{
				printf("\n\nCidade do medico: \n");
				tratamento_desc50(cmedico_upd->endereco.cidade, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico_upd->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*BAIRRO*/
			else if (strcmp(cmedico->alterar, "13") == 0)
			{
				printf("\n\nBairro do medico: \n");
				tratamento_desc50(cmedico_upd->endereco.bairro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico_upd->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*LOGRADOURO*/
			else if (strcmp(cmedico->alterar, "14") == 0)
			{
				printf("\n\nLogradouro do medico: \n");
				tratamento_desc50(cmedico_upd->endereco.logradouro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico_upd->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*COMPLEMENTO*/
			else if (strcmp(cmedico->alterar, "15") == 0)
			{
				printf("\n\nComplemento do medico: \n");
				tratamento_desc50(cmedico_upd->endereco.complemento, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico_upd->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico->endereco.cep);
			}
			/*CEP*/
			else if (strcmp(cmedico->alterar, "16") == 0)
			{
				printf("\n\nCEP do medico: \n");
				tratamento_cep(cmedico_upd->endereco.cep, 8);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cmedico->codigo);
				fprintf(temporario, "%s\n", cmedico->nome);
				fprintf(temporario, "%s\n", cmedico->celular);
				fprintf(temporario, "%s\n", cmedico->email);
				fprintf(temporario, "%s\n", cmedico->cpf);
				fprintf(temporario, "%s\n", cmedico->especialidade);
				fprintf(temporario, "%s\n", cmedico->filial.cnpj);
				fprintf(temporario, "%s\n", cmedico->endereco.estado);
				fprintf(temporario, "%s\n", cmedico->endereco.cidade);
				fprintf(temporario, "%s\n", cmedico->endereco.bairro);
				fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
				fprintf(temporario, "%s\n", cmedico->endereco.complemento);
				fprintf(temporario, "%s\n", cmedico_upd->endereco.cep);
			}
			/*VALOR NAO CORRESPONDE AO MENU*/
			else
			{
				printf("\033[2J\033[1;1H");
				printf("\nATENCAO! Menu inexistente, tente um valor valido!");
				goto retornaalteracao;
			}
		}
		else
		{
			fprintf(temporario, "%i\n", cmedico->codigo);
			fprintf(temporario, "%s\n", cmedico->nome);
			fprintf(temporario, "%s\n", cmedico->celular);
			fprintf(temporario, "%s\n", cmedico->email);
			fprintf(temporario, "%s\n", cmedico->cpf);
			fprintf(temporario, "%s\n", cmedico->especialidade);
			fprintf(temporario, "%s\n", cmedico->filial.cnpj);
			fprintf(temporario, "%s\n", cmedico->endereco.estado);
			fprintf(temporario, "%s\n", cmedico->endereco.cidade);
			fprintf(temporario, "%s\n", cmedico->endereco.bairro);
			fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
			fprintf(temporario, "%s\n", cmedico->endereco.complemento);
			fprintf(temporario, "%s\n", cmedico->endereco.cep);
		}
	}

	fclose(pdoctor);
	fclose(temporario);

	while ((strcmp(cmedico->salvar, "1") != 0 || strcmp(cmedico->salvar, "2") != 0) && test != 1)
	{
		printf("\n\n\nNao ha registros com esse CPF!\n\n");

		while((strcmp(cmedico->salvar, "1") != 0) || (strcmp(cmedico->salvar, "2") != 0))
		{
			printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
			tratamento_numeroum(cmedico->salvar, 0);

			switch (cmedico->salvar[0])
			{
			case '1':
				alterar_medico();
				break;
			case '2':
				main_alterar();
				break;
			default:
				printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
				system("pause");
			}
		}
	}

	while ((strcmp(cmedico->salvar, "1") != 0 || strcmp(cmedico->salvar, "2") != 0))
	{
		memset(cmedico->salvar, 0, sizeof(cmedico->salvar));

		printf("\n\nTecle [1] para confirmar a ALTERACAO desse medico ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cmedico->salvar, 0);

		if (strcmp(cmedico->salvar, "2") == 0)
		{
			remove("dados\\temp_medico_upd.txt");
			break;
		}

		switch (cmedico->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_alterar();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
			system("pause");
		}

		if((strcmp(cmedico->salvar, "1") == 0 || strcmp(cmedico->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_medico.txt");
			if (rem == 0)
			{
				rename("dados\\temp_medico_upd.txt", "dados\\cad_medico.txt");
				printf("\nAlteracao realizada!\n\n");
				break;
			}
			else
			{
				remove("dados\\temp_medico_upd.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}
	}
	system("pause");
	main_alterar();
}

void alterar_filial(void)
{
	int test;
	test = 0;

	branch *cfilial = calloc(1, sizeof(branch) * 1);
	branch_upd *cfilial_upd = calloc(1, sizeof(branch_upd) * 1);
	branch_aux *cfilial_aux = calloc(1, sizeof(branch_aux) * 1);

	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_filial_upd.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de temporario de alteracao de filial, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("ALTERAR FILIAL CADASTRADA\n\n");

	printf("Para alterar um filial, insira o CNPJ do filial: ");
	tratamento_cnpj(cfilial_aux->cnpj, 15);

	while (fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep) != EOF)
	{
		if (strcmp(cfilial->cnpj, cfilial_aux->cnpj) == 0)
		{
			retornaalteracao:
			test = 1;
			memset(cfilial->alterar, 0, sizeof(cfilial->alterar));

			printf("\n\n1.Nome\n2.CNPJ\n3.Descricao\n");
			mostrarendereco();
			tratamento_numero(cfilial->alterar, 2);

			/*NOME*/
			if (strcmp(cfilial->alterar, "1") == 0)
			{
				printf("\nNome do filial: \n");
				tratamento_desc50(cfilial_upd->nome, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial_upd->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*CNPJ*/
			else if (strcmp(cfilial->alterar, "2") == 0)
			{
				printf("\n\nCNPJ do filial: \n");
				tratamento_cnpj(cfilial_upd->cnpj, 15);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial_upd->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*DESCRICAO*/
			else if (strcmp(cfilial->alterar, "3") == 0)
			{
				printf("\n\nDescricao do filial: \n");
				tratamento_desc50(cfilial_upd->descricao, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial_upd->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*ESTADO*/
			else if (strcmp(cfilial->alterar, "11") == 0)
			{
				printf("\n\nEstado do Filial(XX): \n");
				tratamento_estado(cfilial_upd->endereco.estado, 2);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial_upd->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*CIDADE*/
			else if (strcmp(cfilial->alterar, "12") == 0)
			{
				printf("\n\nCidade do Filial: \n");
				tratamento_desc50(cfilial_upd->endereco.cidade, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial_upd->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*BAIRRO*/
			else if (strcmp(cfilial->alterar, "13") == 0)
			{
				printf("\n\nBairro do Filial: \n");
				tratamento_desc50(cfilial_upd->endereco.bairro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial_upd->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*LOGRADOURO*/
			else if (strcmp(cfilial->alterar, "14") == 0)
			{
				printf("\n\nLogradouro do Filial: \n");
				tratamento_desc50(cfilial_upd->endereco.logradouro, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial_upd->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*COMPLEMENTO*/
			else if (strcmp(cfilial->alterar, "15") == 0)
			{
				printf("\n\nComplemento do Filial: \n");
				tratamento_desc50(cfilial_upd->endereco.complemento, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial_upd->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial->endereco.cep);
			}
			/*CEP*/
			else if (strcmp(cfilial->alterar, "16") == 0)
			{
				printf("\n\nCEP do Filial: \n");
				tratamento_cep(cfilial_upd->endereco.cep, 8);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cfilial->codigo);
				fprintf(temporario, "%s\n", cfilial->nome);
				fprintf(temporario, "%s\n", cfilial->cnpj);
				fprintf(temporario, "%s\n", cfilial->descricao);
				fprintf(temporario, "%s\n", cfilial->endereco.estado);
				fprintf(temporario, "%s\n", cfilial->endereco.cidade);
				fprintf(temporario, "%s\n", cfilial->endereco.bairro);
				fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
				fprintf(temporario, "%s\n", cfilial->endereco.complemento);
				fprintf(temporario, "%s\n", cfilial_upd->endereco.cep);
			}
			/*VALOR NAO CORRESPONDE AO MENU*/
			else
			{
				printf("\033[2J\033[1;1H");
				printf("\nATENCAO! Menu inexistente, tente um valor valido!");
				goto retornaalteracao;
			}
		}
		else
		{
			fprintf(temporario, "%i\n", cfilial->codigo);
			fprintf(temporario, "%s\n", cfilial->nome);
			fprintf(temporario, "%s\n", cfilial->cnpj);
			fprintf(temporario, "%s\n", cfilial->descricao);
			fprintf(temporario, "%s\n", cfilial->endereco.estado);
			fprintf(temporario, "%s\n", cfilial->endereco.cidade);
			fprintf(temporario, "%s\n", cfilial->endereco.bairro);
			fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
			fprintf(temporario, "%s\n", cfilial->endereco.complemento);
			fprintf(temporario, "%s\n", cfilial->endereco.cep);
		}
	}

	fclose(pfilial);
	fclose(temporario);

	while ((strcmp(cfilial->salvar, "1") != 0 || strcmp(cfilial->salvar, "2") != 0) && test != 1)
	{
		printf("\n\n\nNao ha registros com esse CNPJ!\n\n");

		while((strcmp(cfilial->salvar, "1") != 0) || (strcmp(cfilial->salvar, "2") != 0))
		{
			printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu cadastro: ");
			tratamento_numeroum(cfilial->salvar, 0);

			switch (cfilial->salvar[0])
			{
				case '1':
					alterar_filial();
					break;
				case '2':
					main_alterar();
					break;
				default:
					printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
					system("pause");
			}
		}
	}

	while ((strcmp(cfilial->salvar, "1") != 0 || strcmp(cfilial->salvar, "2") != 0))
	{
		memset(cfilial->salvar, 0, sizeof(cfilial->salvar));

		printf("\n\nTecle [1] para confirmar a ALTERACAO dessa filial ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cfilial->salvar, 0);

		if (strcmp(cfilial->salvar, "2") == 0)
		{
			remove("dados\\temp_filial_upd.txt");
			break;
		}

		switch (cfilial->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_alterar();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
			system("pause");
		}

		if((strcmp(cfilial->salvar, "1") == 0 || strcmp(cfilial->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_filial.txt");
			if (rem == 0)
			{
				rename("dados\\temp_filial_upd.txt", "dados\\cad_filial.txt");
				printf("\nAlteracao realizada!\n\n");
				break;
			}
			else
			{
				remove("dados\\temp_filial_upd.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}	
	}
	system("pause");
	main_alterar();
}

void alterar_agendamento(void)
{
	int test;
	test = 0;

	scheduling *cagendamento = calloc(1, sizeof(scheduling) * 1);
	scheduling_upd *cagendamento_upd = calloc(1, sizeof(scheduling_upd) * 1);
	scheduling_aux *cagendamento_aux = calloc(1, sizeof(scheduling_aux) * 1);
	branch *cfilial = calloc(1, sizeof(branch) * 1);

	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_agendamento_upd.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de temporario de alteracao de agendamentos, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("ALTERAR AGENDAMENTO CADASTRADO\n\n");

	printf("Insira o CPF do paciente: ");
	tratamento_cpf(cagendamento_aux->paciente.cpf, 11);
	fseek(stdin, 0, SEEK_END);

	printf("\n\nData do agendamento: ");
	tratamento_tdtaqq(cagendamento_aux->data, 8);
	fseek(stdin, 0, SEEK_END);

	while (fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao) != EOF)
	{
		if ((strcmp(cagendamento->paciente.cpf, cagendamento_aux->paciente.cpf) == 0) && (strcmp(cagendamento->data, cagendamento_aux->data) == 0))
		{
			retornaalteracao:
			test = 1;
			memset(cagendamento->alterar, 0, sizeof(cagendamento->alterar));

			printf("\n\n1.CPF do paciente\n2.CPF do medico\n3.Filial de consulta\n4.Data da consulta\n5.Hora da consulta\n6.Valor da consulta\n7.Descricao da consulta\n\nEscolha qual informacao voce deseja alterar e tecle ENTER: \n");
			tratamento_numero(cagendamento->alterar, 2);

			/*CPF DO PACIENTE*/
			if (strcmp(cagendamento->alterar, "1") == 0)
			{
				printf("\nCPF do paciente: \n");
				tratamento_cpf(cagendamento_upd->paciente.cpf, 12);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cagendamento->codigo);
				fprintf(temporario, "%s\n", cagendamento_upd->paciente.cpf);
				fprintf(temporario, "%s\n", cagendamento->paciente.nome);
				fprintf(temporario, "%s\n", cagendamento->medico.cpf);
				fprintf(temporario, "%s\n", cagendamento->medico.nome);
				fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
				fprintf(temporario, "%s\n", cagendamento->filial.nome);
				fprintf(temporario, "%s\n", cagendamento->data);
				fprintf(temporario, "%s\n", cagendamento->hora);
				fprintf(temporario, "%0.2f\n", cagendamento->precovalor);
				fprintf(temporario, "%s\n", cagendamento->descricao);
			}
			/*CPF DO MEDICO*/
			else if (strcmp(cagendamento->alterar, "2") == 0)
			{
				printf("\nCPF do do Medico: \n");
				tratamento_cpf(cagendamento_upd->medico.cpf, 12);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cagendamento->codigo);
				fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
				fprintf(temporario, "%s\n", cagendamento->paciente.nome);
				fprintf(temporario, "%s\n", cagendamento_upd->medico.cpf);
				fprintf(temporario, "%s\n", cagendamento->medico.nome);
				fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
				fprintf(temporario, "%s\n", cagendamento->filial.nome);
				fprintf(temporario, "%s\n", cagendamento->data);
				fprintf(temporario, "%s\n", cagendamento->hora);
				fprintf(temporario, "%0.2f\n", cagendamento->precovalor);
				fprintf(temporario, "%s\n", cagendamento->descricao);
			}
			/*CNPJ DA FILIAL*/
			else if (strcmp(cagendamento->alterar, "3") == 0)
			{

				/*-----------------------------------------------------------------------*/

				/*CARREGAR OS DADOS DAS FILIAIS*/
				while (strcmp(cfilial->cnpj, cagendamento_upd->filial.cnpj) != 0 || *cagendamento_upd->filial.cnpj == '\0')
				{
					pfilial = fopen("dados\\cad_filial.txt", "r");
					if (pfilial == NULL)
					{
						fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

						char verificaarq[2];
						memset(verificaarq, 0, sizeof(verificaarq));

						printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
						tratamento_numeroum(verificaarq, 0);

						switch (verificaarq[0])
						{
						case '1':
							main_principal();
							break;
						case '2':
							exit(0);
						default:
							printf("\nMenu inexistente, tente novamente [1] ou [2].");
							system("pause");
						}
					}

					memset(cagendamento_upd->filial.cnpj, 0, sizeof(cagendamento_upd->filial.cnpj));

					printf("\nCNPJ da filial: \n");
					tratamento_cnpj(cagendamento_upd->filial.cnpj, 14);
					fseek(stdin, 0, SEEK_END);

					while (!feof(pfilial) && strcmp(cfilial->cnpj, cagendamento_upd->filial.cnpj) != 0)
					{
						fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep);
					}

					if (strcmp(cfilial->cnpj, cagendamento_upd->filial.cnpj) != 0)
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

				fprintf(temporario, "%i\n", cagendamento->codigo);
				fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
				fprintf(temporario, "%s\n", cagendamento->paciente.nome);
				fprintf(temporario, "%s\n", cagendamento->medico.cpf);
				fprintf(temporario, "%s\n", cagendamento->medico.nome);
				fprintf(temporario, "%s\n", cagendamento_upd->filial.cnpj);
				fprintf(temporario, "%s\n", cagendamento->filial.nome);
				fprintf(temporario, "%s\n", cagendamento->data);
				fprintf(temporario, "%s\n", cagendamento->hora);
				fprintf(temporario, "%0.2f\n", cagendamento->precovalor);
				fprintf(temporario, "%s\n", cagendamento->descricao);
			}
			/*DATA*/
			else if (strcmp(cagendamento->alterar, "4") == 0)
			{
				printf("\nData do agendamento: \n");
				tratamento_tdta(cagendamento_upd->data, 8);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cagendamento->codigo);
				fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
				fprintf(temporario, "%s\n", cagendamento->paciente.nome);
				fprintf(temporario, "%s\n", cagendamento->medico.cpf);
				fprintf(temporario, "%s\n", cagendamento->medico.nome);
				fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
				fprintf(temporario, "%s\n", cagendamento->filial.nome);
				fprintf(temporario, "%s\n", cagendamento_upd->data);
				fprintf(temporario, "%s\n", cagendamento->hora);
				fprintf(temporario, "%0.2f\n", cagendamento->precovalor);
				fprintf(temporario, "%s\n", cagendamento->descricao);
			}
			/*HORA*/
			else if (strcmp(cagendamento->alterar, "5") == 0)
			{
				printf("\n\nHora do agendamento: \n");
				tratamento_hm(cagendamento_upd->hora, 4);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cagendamento->codigo);
				fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
				fprintf(temporario, "%s\n", cagendamento->paciente.nome);
				fprintf(temporario, "%s\n", cagendamento->medico.cpf);
				fprintf(temporario, "%s\n", cagendamento->medico.nome);
				fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
				fprintf(temporario, "%s\n", cagendamento->filial.nome);
				fprintf(temporario, "%s\n", cagendamento->data);
				fprintf(temporario, "%s\n", cagendamento_upd->hora);
				fprintf(temporario, "%0.2f\n", cagendamento->precovalor);
				fprintf(temporario, "%s\n", cagendamento->descricao);
			}
			/*PRECO*/
			else if (strcmp(cagendamento->alterar, "6") == 0)
			{
				printf("\n\nValor da consulta: \n");
				scanf("%f", &cagendamento_upd->precovalor);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cagendamento->codigo);
				fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
				fprintf(temporario, "%s\n", cagendamento->paciente.nome);
				fprintf(temporario, "%s\n", cagendamento->medico.cpf);
				fprintf(temporario, "%s\n", cagendamento->medico.nome);
				fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
				fprintf(temporario, "%s\n", cagendamento->filial.nome);
				fprintf(temporario, "%s\n", cagendamento->data);
				fprintf(temporario, "%s\n", cagendamento->hora);
				fprintf(temporario, "%0.2f\n", cagendamento_upd->precovalor);
				fprintf(temporario, "%s\n", cagendamento->descricao);
			}
			/*DESCRICAO*/
			else if (strcmp(cagendamento->alterar, "7") == 0)
			{
				printf("\nDescricao do agendamento: \n");
				tratamento_desc50(cagendamento_upd->descricao, 50);
				fseek(stdin, 0, SEEK_END);
				fprintf(temporario, "%i\n", cagendamento->codigo);
				fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
				fprintf(temporario, "%s\n", cagendamento->paciente.nome);
				fprintf(temporario, "%s\n", cagendamento->medico.cpf);
				fprintf(temporario, "%s\n", cagendamento->medico.nome);
				fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
				fprintf(temporario, "%s\n", cagendamento->filial.nome);
				fprintf(temporario, "%s\n", cagendamento->data);
				fprintf(temporario, "%s\n", cagendamento->hora);
				fprintf(temporario, "%0.2f\n", cagendamento->precovalor);
				fprintf(temporario, "%s\n", cagendamento_upd->descricao);
			}
			/*VALOR NAO CORRESPONDE AO MENU*/
			else
			{
				printf("\033[2J\033[1;1H");
				printf("\nATENCAO! Menu inexistente, tente um valor valido!");
				goto retornaalteracao;
			}
		}
		else
		{
			fprintf(temporario, "%i\n", cagendamento->codigo);
			fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
			fprintf(temporario, "%s\n", cagendamento->paciente.nome);
			fprintf(temporario, "%s\n", cagendamento->medico.cpf);
			fprintf(temporario, "%s\n", cagendamento->medico.nome);
			fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
			fprintf(temporario, "%s\n", cagendamento->filial.nome);
			fprintf(temporario, "%s\n", cagendamento->data);
			fprintf(temporario, "%s\n", cagendamento->hora);
			fprintf(temporario, "%0.2f\n", cagendamento->precovalor);
			fprintf(temporario, "%s\n", cagendamento->descricao);
		}
	}

	fclose(pagendamento);
	fclose(temporario);

	while ((strcmp(cagendamento->salvar, "1") != 0 || strcmp(cagendamento->salvar, "2") != 0) && test != 1)
	{
		printf("\n\n\nNao ha registros com esses dados cadastrados!\n\n");

		while((strcmp(cagendamento->salvar, "1") != 0) || (strcmp(cagendamento->salvar, "2") != 0))
		{
			printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
			tratamento_numeroum(cagendamento->salvar, 0);

			switch (cagendamento->salvar[0])
			{
			case '1':
				alterar_agendamento();
				break;
			case '2':
				main_alterar();
				break;
			default:
				printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
				system("pause");
			}
		}
	}

	while ((strcmp(cagendamento->salvar, "1") != 0 || strcmp(cagendamento->salvar, "2") != 0))
	{
		memset(cagendamento->salvar, 0, sizeof(cagendamento->salvar));
	
		printf("\n\nTecle [1] para confirmar a ALTERACAO desse agendamento ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cagendamento->salvar, 0);

		if (strcmp(cagendamento->salvar, "2") == 0)
		{
			remove("dados\\temp_agendamento_upd.txt");
			break;
		}

		switch (cagendamento->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_alterar();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\n\nMenu inexistente, tente novamente [1] ou [2].\n");
			system("pause");
		}

		if((strcmp(cagendamento->salvar, "1") == 0 || strcmp(cagendamento->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_agendamento.txt");
			if (rem == 0)
			{
				rename("dados\\temp_agendamento_upd.txt", "dados\\cad_agendamento.txt");
				printf("\nAlteracao realizada!\n\n");
				break;
			}
			else
			{
				remove("dados\\temp_agendamento_upd.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}
	}
	system("pause");
	main_alterar();
}

/*-----------------------------------------------------------------------*/

/*DELETE TELAS*/
void deletar_usuario(void)
{
	int test;
	test = 0;

	user *cusuario = calloc(1, sizeof(user) * 1);
	user_del *cusuario_del = calloc(1, sizeof(user_del) * 1);

	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de funcionarios ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_user_del.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao excluir arquivo de temporario  de funcionarios, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("DELETAR USUARIO CADASTRADO\n\n");

	printf("Para deletar um usuario, insira o CPF do usuario: ");
	tratamento_cpf(cusuario_del->cpf, 11);

	while (fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->email, cusuario->cpf, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep) != EOF)
	{
		if (strcmp(cusuario->cpf, cusuario_del->cpf) != 0)
		{
			fprintf(temporario, "%i\n", cusuario->codigo);
			fprintf(temporario, "%s\n", cusuario->nome);
			fprintf(temporario, "%s\n", cusuario->celular);
			fprintf(temporario, "%s\n", cusuario->email);
			fprintf(temporario, "%s\n", cusuario->cpf);
			fprintf(temporario, "%s\n", cusuario->usuario);
			fprintf(temporario, "%s\n", cusuario->senha);
			fprintf(temporario, "%s\n", cusuario->endereco.estado);
			fprintf(temporario, "%s\n", cusuario->endereco.cidade);
			fprintf(temporario, "%s\n", cusuario->endereco.bairro);
			fprintf(temporario, "%s\n", cusuario->endereco.logradouro);
			fprintf(temporario, "%s\n", cusuario->endereco.complemento);
			fprintf(temporario, "%s\n", cusuario->endereco.cep);
		}
		else
		{
			test++;
			memset(cusuario->senha, 0, sizeof(cusuario->senha));
			printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nUsuario no sistema: %s\nSenha: %s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->celular + 2, cusuario->celular + 7, cusuario->email, cusuario->cpf, cusuario->cpf + 3, cusuario->cpf + 6, cusuario->cpf + 9, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep, cusuario->endereco.cep + 5);
		}
	}

	fclose(puser);
	fclose(temporario);

	while ((strcmp(cusuario->salvar, "1") != 0 || strcmp(cusuario->salvar, "2") != 0) && test == 0)
	{
		printf("\n\n\nNao ha registros com esse CPF!\n\n");

		memset(cusuario->salvar, 0, sizeof(cusuario->salvar));

		printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cusuario->salvar, 0);

		switch (cusuario->salvar[0])
		{
		case '1':
			deletar_usuario();
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while ((strcmp(cusuario->salvar, "1") != 0 || strcmp(cusuario->salvar, "2") != 0))
	{
		memset(cusuario->salvar, 0, sizeof(cusuario->salvar));

		printf("\n\nTecle [1] para confirmar a EXCLUSAO desse usuario ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cusuario->salvar, 0);

		if (strcmp(cusuario->salvar, "2") == 0)
		{
			remove("dados\\temp_user_del.txt");
			break;
		}

		switch (cusuario->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}

		if((strcmp(cusuario->salvar, "1") == 0 || strcmp(cusuario->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_funcionario.txt");
			if (rem == 0)
			{
				rename("dados\\temp_user_del.txt", "dados\\cad_funcionario.txt");
				printf("\nO arquivo foi deletado com sucesso!\n");
				break;
			}
			else
			{
				remove("dados\\temp_user_del.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}
	}
	system("pause");
	main_delete();
}

void deletar_paciente(void)
{
	int test;
	test = 0;

	patient *cpaciente = calloc(1, sizeof(patient) * 1);
	patient_del *cpaciente_del = calloc(1, sizeof(patient_del) * 1);

	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_paciente_del.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao excluir arquivo de temporario de pacientes, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("DELETAR PACIENTE CADASTRADO\n\n");

	printf("Para deletar um registro, insira o CPF do paciente: ");
	tratamento_cpf(cpaciente_del->cpf, 11);

	while (fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->email, cpaciente->cpf, cpaciente->filial.cnpj, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep) != EOF)
	{
		if (strcmp(cpaciente->cpf, cpaciente_del->cpf) != 0)
		{
			fprintf(temporario, "%i\n", cpaciente->codigo);
			fprintf(temporario, "%s\n", cpaciente->nome);
			fprintf(temporario, "%s\n", cpaciente->celular);
			fprintf(temporario, "%s\n", cpaciente->email);
			fprintf(temporario, "%s\n", cpaciente->cpf);
			fprintf(temporario, "%s\n", cpaciente->filial.cnpj);
			fprintf(temporario, "%s\n", cpaciente->endereco.estado);
			fprintf(temporario, "%s\n", cpaciente->endereco.cidade);
			fprintf(temporario, "%s\n", cpaciente->endereco.bairro);
			fprintf(temporario, "%s\n", cpaciente->endereco.logradouro);
			fprintf(temporario, "%s\n", cpaciente->endereco.complemento);
			fprintf(temporario, "%s\n", cpaciente->endereco.cep);
		}
		else
		{
			test++;
			printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nCNPJ da filial: %.2s.%.3s.%.3s/%.4s-%.2s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->celular + 2, cpaciente->celular + 7, cpaciente->email, cpaciente->cpf, cpaciente->cpf + 3, cpaciente->cpf + 6, cpaciente->cpf + 9, cpaciente->filial.cnpj, cpaciente->filial.cnpj + 2, cpaciente->filial.cnpj + 5, cpaciente->filial.cnpj + 8, cpaciente->filial.cnpj + 12, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep, cpaciente->endereco.cep + 5);
		}
	}

	fclose(ppatient);
	fclose(temporario);

	while ((strcmp(cpaciente->salvar, "1") != 0 || strcmp(cpaciente->salvar, "2") != 0) && test == 0)
	{
		printf("\n\n\nNao ha registros com esse CPF!\n\n");

		memset(cpaciente->salvar, 0, sizeof(cpaciente->salvar));

		printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cpaciente->salvar, 0);

		switch (cpaciente->salvar[0])
		{
		case '1':
			deletar_paciente();
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while ((strcmp(cpaciente->salvar, "1") != 0 || strcmp(cpaciente->salvar, "2") != 0))
	{
		memset(cpaciente->salvar, 0, sizeof(cpaciente->salvar));

		printf("\n\nTecle [1] para confirmar a EXCLUSAO desse paciente ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cpaciente->salvar, 0);

		if (strcmp(cpaciente->salvar, "2") == 0)
		{
			remove("dados\\temp_paciente_del.txt");
			break;
		}

		switch (cpaciente->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}

		if((strcmp(cpaciente->salvar, "1") == 0 || strcmp(cpaciente->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_paciente.txt");
			if (rem == 0)
			{
				rename("dados\\temp_paciente_del.txt", "dados\\cad_paciente.txt");
				printf("\nO arquivo foi deletado com sucesso!\n");
				break;
			}
			else
			{
				remove("dados\\temp_paciente_del.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}		
	}
	system("pause");
	main_delete();
}

void deletar_medico(void)
{
	int test;
	test = 0;

	doctor *cmedico = calloc(1, sizeof(doctor) * 1);
	doctor_del *cmedico_del = calloc(1, sizeof(doctor_del) * 1);

	pdoctor = fopen("dados\\cad_medico.txt", "r");
	if (pdoctor == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de medicos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_medico_del.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao excluir arquivo de temporario de medicos, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("DELETAR MEDICO CADASTRADO\n\n");

	printf("Para deletar um registro, insira o CPF do medico: ");
	tratamento_cpf(cmedico_del->cpf, 11);

	while (fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->email, cmedico->cpf, cmedico->especialidade, cmedico->filial.cnpj, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep) != EOF)
	{
		if (strcmp(cmedico->cpf, cmedico_del->cpf) != 0)
		{
			fprintf(temporario, "%i\n", cmedico->codigo);
			fprintf(temporario, "%s\n", cmedico->nome);
			fprintf(temporario, "%s\n", cmedico->celular);
			fprintf(temporario, "%s\n", cmedico->email);
			fprintf(temporario, "%s\n", cmedico->cpf);
			fprintf(temporario, "%s\n", cmedico->especialidade);
			fprintf(temporario, "%s\n", cmedico->filial.cnpj);
			fprintf(temporario, "%s\n", cmedico->endereco.estado);
			fprintf(temporario, "%s\n", cmedico->endereco.cidade);
			fprintf(temporario, "%s\n", cmedico->endereco.bairro);
			fprintf(temporario, "%s\n", cmedico->endereco.logradouro);
			fprintf(temporario, "%s\n", cmedico->endereco.complemento);
			fprintf(temporario, "%s\n", cmedico->endereco.cep);
		}
		else
		{
			test++;
			printf("\n\nCodigo: %i\nNome: %s\nCelular: %.2s-%.5s-%.4s\nE-mail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nEspecialidade: %s\nFilial de atuacao(CNPJ): %.2s.%.3s.%.3s/%.4s-%.2s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cmedico->codigo, cmedico->nome, cmedico->celular, cmedico->celular + 2, cmedico->celular + 7, cmedico->email, cmedico->cpf, cmedico->cpf + 3, cmedico->cpf + 6, cmedico->cpf + 9, cmedico->especialidade, cmedico->filial.cnpj, cmedico->filial.cnpj + 2, cmedico->filial.cnpj + 5, cmedico->filial.cnpj + 8, cmedico->filial.cnpj + 12, cmedico->endereco.estado, cmedico->endereco.cidade, cmedico->endereco.bairro, cmedico->endereco.logradouro, cmedico->endereco.complemento, cmedico->endereco.cep, cmedico->endereco.cep + 5);
		}
	}

	fclose(pdoctor);
	fclose(temporario);

	while ((strcmp(cmedico->salvar, "1") != 0 || strcmp(cmedico->salvar, "2") != 0) && test == 0)
	{
		printf("\n\n\nNao ha registros com esse CPF!\n\n");

		memset(cmedico->salvar, 0, sizeof(cmedico->salvar));

		printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cmedico->salvar, 0);

		switch (cmedico->salvar[0])
		{
		case '1':
			deletar_medico();
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while ((strcmp(cmedico->salvar, "1") != 0 || strcmp(cmedico->salvar, "2") != 0))
	{
		memset(cmedico->salvar, 0, sizeof(cmedico->salvar));

		printf("\n\nTecle [1] para confirmar a EXCLUSAO desse medico ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cmedico->salvar, 0);

		if (strcmp(cmedico->salvar, "2") == 0)
		{
			remove("dados\\temp_medico_del.txt");
			break;
		}

		switch (cmedico->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}

		if((strcmp(cmedico->salvar, "1") == 0 || strcmp(cmedico->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_medico.txt");
			if (rem == 0)
			{
				printf("\nO arquivo foi deletado com sucesso!\n");
				rename("dados\\temp_medico_del.txt", "dados\\cad_medico.txt");
				break;
			}
			else
			{
				remove("dados\\temp_medico_del.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}
	}
	system("pause");
	main_delete();
}

void deletar_filial(void)
{
	int test;
	test = 0;

	branch *cfilial = calloc(1, sizeof(branch) * 1);
	branch_del *cfilial_del = calloc(1, sizeof(branch_del) * 1);

	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_filial_del.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao excluir arquivo de temporario de filial, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("DELETAR FILIAL CADASTRADA\n\n");

	printf("Para deletar um registro, insira o CNPJ da filial: ");
	tratamento_cnpj(cfilial_del->cnpj, 15);

	while (fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep) != EOF)
	{
		if (strcmp(cfilial->cnpj, cfilial_del->cnpj) != 0)
		{
			fprintf(temporario, "%i\n", cfilial->codigo);
			fprintf(temporario, "%s\n", cfilial->nome);
			fprintf(temporario, "%s\n", cfilial->cnpj);
			fprintf(temporario, "%s\n", cfilial->descricao);
			fprintf(temporario, "%s\n", cfilial->endereco.estado);
			fprintf(temporario, "%s\n", cfilial->endereco.cidade);
			fprintf(temporario, "%s\n", cfilial->endereco.bairro);
			fprintf(temporario, "%s\n", cfilial->endereco.logradouro);
			fprintf(temporario, "%s\n", cfilial->endereco.complemento);
			fprintf(temporario, "%s\n", cfilial->endereco.cep);
		}
		else
		{
			test++;
			printf("\n\nCodigo: %i\nNome: %s\ncnpj: %.2s.%.3s.%.3s/%.4s-%.2s\nDescrição: %s\nEstado: %s\nCidade: %s\nBairro: %s\nlogradouro: %s\nComplemento: %s\nCep: %.5s-%.3s\n", cfilial->codigo, cfilial->nome, cfilial->cnpj, cfilial->cnpj + 2, cfilial->cnpj + 5, cfilial->cnpj + 8, cfilial->cnpj + 12, cfilial->descricao, cfilial->endereco.estado, cfilial->endereco.cidade, cfilial->endereco.bairro, cfilial->endereco.logradouro, cfilial->endereco.complemento, cfilial->endereco.cep, cfilial->endereco.cep + 5);
		}
	}

	fclose(pfilial);
	fclose(temporario);

	while ((strcmp(cfilial->salvar, "1") != 0 || strcmp(cfilial->salvar, "2") != 0) && test == 0)
	{
		printf("\n\n\nNao ha registros com esse CNPJ!\n\n");

		memset(cfilial->salvar, 0, sizeof(cfilial->salvar));

		printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cfilial->salvar, 0);

		switch (cfilial->salvar[0])
		{
		case '1':
			deletar_filial();
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while ((strcmp(cfilial->salvar, "1") != 0 || strcmp(cfilial->salvar, "2") != 0))
	{
		memset(cfilial->salvar, 0, sizeof(cfilial->salvar));

		printf("\n\nTecle [1] para confirmar a EXCLUSAO desse filial ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cfilial->salvar, 0);

		if (strcmp(cfilial->salvar, "2") == 0)
		{
			remove("dados\\temp_filial_del.txt");
			break;
		}

		switch (cfilial->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}

		if((strcmp(cfilial->salvar, "1") == 0 || strcmp(cfilial->salvar, "2") == 0))
		{
			int rem = 0;
			rem = remove("dados\\cad_filial.txt");
			if (rem == 0)
			{
				printf("\nO arquivo foi deletado com sucesso!\n");
				rename("dados\\temp_filial_del.txt", "dados\\cad_filial.txt");	
				break;
			}
			else
			{
				remove("dados\\temp_filial_del.txt");
				perror("Nao foi possivel deletar o arquivo!");
				break;
			}
		}		
	}
	system("pause");
	main_delete();
}

void cancelar_agendamento(void)
{
	int test;
	test = 0;

	scheduling *cagendamento = calloc(1, sizeof(scheduling) * 1);
	scheduling_del *cagendamento_del = calloc(1, sizeof(scheduling_del) * 1);
	scheduling_aux *cagendamento_aux = calloc(1, sizeof(scheduling_aux) * 1);

	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	temporario = fopen("dados\\temp_agendamento_del.txt", "w");
	if (temporario == NULL)
	{
		fprintf(stderr, "\n\nErro ao excluir arquivo de temporario de agendamentos, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	printf("\033[2J\033[1;1H");
	printf("CANCELAR AGENDAMENTOS\n\n");

	printf("Insira o CPF do paciente: ");
	tratamento_cpf(cagendamento_del->paciente.cpf, 11);

	printf("\n\nData do agendamento: ");
	tratamento_tdtaqq(cagendamento_aux->data, 8);

	while (fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao) != EOF)
	{
		if ((strcmp(cagendamento->paciente.cpf, cagendamento_del->paciente.cpf) != 0 && strcmp(cagendamento->data, cagendamento_aux->data) != 0) || (strcmp(cagendamento->paciente.cpf, cagendamento_del->paciente.cpf) == 0 && strcmp(cagendamento->data, cagendamento_aux->data) != 0) || (strcmp(cagendamento->paciente.cpf, cagendamento_del->paciente.cpf) != 0 && strcmp(cagendamento->data, cagendamento_aux->data) == 0))
		{
			fprintf(temporario, "%i\n", cagendamento->codigo);
			fprintf(temporario, "%s\n", cagendamento->paciente.cpf);
			fprintf(temporario, "%s\n", cagendamento->paciente.nome);
			fprintf(temporario, "%s\n", cagendamento->medico.cpf);
			fprintf(temporario, "%s\n", cagendamento->medico.nome);
			fprintf(temporario, "%s\n", cagendamento->filial.cnpj);
			fprintf(temporario, "%s\n", cagendamento->filial.nome);
			fprintf(temporario, "%s\n", cagendamento->data);
			fprintf(temporario, "%s\n", cagendamento->hora);
			fprintf(temporario, "%f\n", cagendamento->precovalor);
			fprintf(temporario, "%s\n", cagendamento->descricao);
		}
		else if ((strcmp(cagendamento->paciente.cpf, cagendamento_del->paciente.cpf) == 0 && strcmp(cagendamento->data, cagendamento_aux->data) == 0))
		{
			test++;
			printf("\n\nCodigo: %i\nCPF do paciente: %.3s.%.3s.%.3s-%.2s\nNome do paciente: %s\nCPF do medico: %.3s.%.3s.%.3s-%.2s\nNome do medico: %s\nCNPJ da filial: %.2s.%.3s.%.3s/%.4s-%.2s\nNome da Filial: %s\nData do agendamento: %.2s/%.2s/%.4s\nHora do Agendamento: %.2s:%.2s\nValor da consulta: %0.2f\nDescricao: %s\n", cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.cpf + 3, cagendamento->paciente.cpf + 6, cagendamento->paciente.cpf + 9, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.cpf + 3, cagendamento->medico.cpf + 6, cagendamento->medico.cpf + 9, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.cnpj + 2, cagendamento->filial.cnpj + 5, cagendamento->filial.cnpj + 8, cagendamento->filial.cnpj + 12, cagendamento->filial.nome, cagendamento->data, cagendamento->data + 2, cagendamento->data + 4, cagendamento->hora, cagendamento->hora + 2, cagendamento->precovalor, cagendamento->descricao);
		}
	}

	fclose(pagendamento);
	fclose(temporario);

	while ((strcmp(cagendamento->salvar, "1") != 0 || strcmp(cagendamento->salvar, "2") != 0) && test == 0)
	{
		printf("\n\n\nNao ha registros com esse CPF!\n\n");

		memset(cagendamento->salvar, 0, sizeof(cagendamento->salvar));

		printf("\n\nTecle [1] para tentar novamente ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cagendamento->salvar, 0);

		switch (cagendamento->salvar[0])
		{
		case '1':
			cancelar_agendamento();
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	while ((strcmp(cagendamento->salvar, "1") != 0 || strcmp(cagendamento->salvar, "2") != 0))
	{
		memset(cagendamento->salvar, 0, sizeof(cagendamento->salvar));

		printf("\n\nTecle [1] para confirmar a EXCLUSAO desse agendamento ou [2] para VOLTAR ao menu anterior: ");
		tratamento_numeroum(cagendamento->salvar, 0);

		if (strcmp(cagendamento->salvar, "2") == 0)
		{
			remove("dados\\temp_agendamento_del.txt");
			break;
		}

		switch (cagendamento->salvar[0])
		{
		case '1':
			break;
		case '2':
			main_delete();
			break;
		default:
			printf("\033[2J\033[1;1H");
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}

		int rem = 0;
		rem = remove("dados\\cad_agendamento.txt");
		if (rem == 0)
		{
			printf("\nO arquivo foi deletado com sucesso!\n");
			rename("dados\\temp_agendamento_del.txt", "dados\\cad_agendamento.txt");
			break;
		}
		else
		{
			remove("dados\\temp_agendamento_del.txt");
			perror("Nao foi possivel deletar o arquivo!");
			break;
		}
	}
	system("pause");
	main_delete();
}

/*-----------------------------------------------------------------------*/

/*RELATÓRIOS*/
int relatorio_usuario(void)
{
	user *cusuario = calloc(1, sizeof(user) * 1);
	char scan[14];
	int l1 = 0;

	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de funcionarios ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	system("mkdir relatorios");

	relatorio = fopen("relatorios\\rel_funcionario.csv", "w");
	if (relatorio == NULL)
	{
		printf("\033[2J\033[1;1H");
		char verificaarq[2];
		while (strcmp(verificaarq, "1") != 0 || strcmp(verificaarq, "2") != 0)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo ou o arquivo ja pode estar aberto, feche o arquivo e tente novamente!");

			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				relatorio_usuario();
				break;
			case '2':
				main_relatorio();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}
	}

	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("RELATORIOS DE FUNCIONARIOS DO SISTEMA\n\n");

	printf("tecle [1] para gerar o relatorio de funcionarios ou [2] para voltar: ");
	tratamento_numero(scan, 2);
	fseek(stdin, 0, SEEK_END);

	if (strcmp(scan, "2") == 0)
	{
		fclose(puser);
		main_relatorio();
	}
	else if (strcmp(scan, "1") == 0)
	{
		goto gerarrelatorio;
	}
	else
	{
		printf("Opcao invalida, tente novamente!");
		fseek(stdin, 0, SEEK_END);
		relatorio_usuario();
	}

gerarrelatorio:

	while (!feof(puser))
	{

		if (l1 != 1)
		{
			fprintf(relatorio, "Codigo;Nome;Celular;E-mail;CPF;Usuario no sistema;Estado;Cidade;Bairro;logradouro;Complemento;Cep\n");
			l1 = 1;
		}
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->email, cusuario->cpf, cusuario->usuario, cusuario->senha, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep);

		if (feof(puser))
		{
			break;
		}

		if (strcmp(cusuario->usuario, "admin") != 0)
		{
			fprintf(relatorio, "\n%i;%s;%.2s-%.5s-%.4s;%s;%.3s.%.3s.%.3s-%.2s;%s;%s;%s;%s;%s;%s;%.5s-%.3s", cusuario->codigo, cusuario->nome, cusuario->celular, cusuario->celular + 2, cusuario->celular + 7, cusuario->email, cusuario->cpf, cusuario->cpf + 3, cusuario->cpf + 6, cusuario->cpf + 9, cusuario->usuario, cusuario->endereco.estado, cusuario->endereco.cidade, cusuario->endereco.bairro, cusuario->endereco.logradouro, cusuario->endereco.complemento, cusuario->endereco.cep, cusuario->endereco.cep + 5);
		}
	}
	fclose(puser);
	fclose(relatorio);

	printf("\n\nRelatorio gerado com sucesso!\n\n");

	char func_con[2];
	while (strcmp(func_con, "1") != 0 || strcmp(func_con, "2") != 0)
	{

		memset(func_con, 0, sizeof(func_con));

		printf("\n\nTecle [1] para voltar ou [2] gerar um novo relatorio: ");
		tratamento_numeroum(func_con, 0);

		switch (func_con[0])
		{
		case '1':
			main_relatorio();
			break;
		case '2':
			relatorio_usuario();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	getchar();
	return 0;
}

int relatorio_paci_filial(void)
{
	patient *cpaciente = calloc(1, sizeof(patient) * 1);
	char scan[14];
	int l1 = 0, l2 = 0;

	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	system("mkdir relatorios");

	relatorio = fopen("relatorios\\rel_paciente_filial.csv", "w");
	if (relatorio == NULL)
	{
		printf("\033[2J\033[1;1H");
		char verificaarq[2];
		while (strcmp(verificaarq, "1") != 0 || strcmp(verificaarq, "2") != 0)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo ou o arquivo ja pode estar aberto, feche o arquivo e tente novamente!");

			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				relatorio_paci_filial();
				break;
			case '2':
				main_relatorio();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}
	}

	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("RELATORIOS DE PACIENTES POR FILIAL\n\n");

	printf("Digite o CNPJ da filial relatorio de pacientes: ");
	tratamento_cnpj(scan, 15);
	fseek(stdin, 0, SEEK_END);

	while (!feof(ppatient))
	{

		if (l1 != 1)
		{
			fprintf(relatorio, "Codigo;Nome;Celular;E-mail;CPF;Unidade;Estado;Cidade;Bairro;logradouro;Complemento;Cep\n");
			l1 = 1;
		}

		fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->email, cpaciente->cpf, cpaciente->filial.cnpj, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep);

		if (feof(ppatient))
		{
			break;
		}

		if (strcmp(cpaciente->filial.cnpj, scan) == 0)
		{
			l2 = 1;
			fprintf(relatorio, "\n\n%i;%s;%.2s-%.5s-%.4s;%s;%.3s.%.3s.%.3s-%.2s;%.2s.%.3s.%.3s/%.4s-%.2s;%s;%s;%s;%s;%s;%.5s-%.3s", cpaciente->codigo, cpaciente->nome, cpaciente->celular, cpaciente->celular + 2, cpaciente->celular + 7, cpaciente->email, cpaciente->cpf, cpaciente->cpf + 3, cpaciente->cpf + 6, cpaciente->cpf + 9, cpaciente->filial.cnpj, cpaciente->filial.cnpj + 2, cpaciente->filial.cnpj + 5, cpaciente->filial.cnpj + 8, cpaciente->filial.cnpj + 12, cpaciente->endereco.estado, cpaciente->endereco.cidade, cpaciente->endereco.bairro, cpaciente->endereco.logradouro, cpaciente->endereco.complemento, cpaciente->endereco.cep, cpaciente->endereco.cep + 5);
		}
	}
	fclose(ppatient);
	fclose(relatorio);

	if (l2 == 1)
	{
		printf("\n\nRelatorio gerado com sucesso!\n\n");
	}
	else
	{
		printf("\n\n\nNao foram encontrados registros para esse CNPJ!\n\n");
	}

	char func_con[2];
	while (strcmp(func_con, "1") != 0 || strcmp(func_con, "2") != 0)
	{

		memset(func_con, 0, sizeof(func_con));

		printf("\n\nTecle [1] para voltar ou [2] gerar um novo relatorio: ");
		tratamento_numeroum(func_con, 0);

		switch (func_con[0])
		{
		case '1':
			main_relatorio();
			break;
		case '2':
			relatorio_paci_filial();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	getchar();
	return 0;
}

int relatorio_filialtotal(void)
{
	scheduling *cagendamento = calloc(1, sizeof(scheduling) * 1);
	char scan[14];
	int l1 = 0, l2 = 0;

	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	system("mkdir relatorios");

	relatorio = fopen("relatorios\\rel_agentotal.csv", "w");
	if (relatorio == NULL)
	{
		printf("\033[2J\033[1;1H");
		char verificaarq[2];
		while (strcmp(verificaarq, "1") != 0 || strcmp(verificaarq, "2") != 0)
		{
			fprintf(stderr, "\n\nErro ao abrir arquivo ou o arquivo ja pode estar aberto, feche o arquivo e tente novamente!");

			memset(verificaarq, 0, sizeof(verificaarq));

			printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
			tratamento_numeroum(verificaarq, 0);

			switch (verificaarq[0])
			{
			case '1':
				relatorio_paci_filial();
				break;
			case '2':
				main_relatorio();
				break;
			default:
				printf("\nMenu inexistente, tente novamente [1] ou [2].");
				system("pause");
			}
		}
	}

	memset(scan, 0, sizeof(scan));

	printf("\033[2J\033[1;1H");
	printf("RELATORIOS FATURAMENTO POR UNIDADE\n\n");

	printf("tecle [1] para gerar o relatorio ou [2] para voltar: ");
	tratamento_numero(scan, 2);
	fseek(stdin, 0, SEEK_END);

	if (strcmp(scan, "2") == 0)
	{
		fclose(puser);
		main_relatorio();
	}
	else if (strcmp(scan, "1") == 0)
	{
		goto gerarrelatorio;
	}
	else
	{
		printf("Opcao invalida, tente novamente!");
		fseek(stdin, 0, SEEK_END);
		relatorio_usuario();
	}

gerarrelatorio:

	while (!feof(pagendamento))
	{
		if (l1 != 1)
		{
			fprintf(relatorio, "Codigo;CNPJ da Unidade;Unidade;Data;Valor faturado;Total faturado\n");
			l1 = 1;
		}

		float somavalorrel = 0;
		while (!feof(pagendamento))
		{
			fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &cagendamento->codigo, cagendamento->paciente.cpf, cagendamento->paciente.nome, cagendamento->medico.cpf, cagendamento->medico.nome, cagendamento->filial.cnpj, cagendamento->filial.nome, cagendamento->data, cagendamento->hora, &cagendamento->precovalor, cagendamento->descricao);

			if (!feof(pagendamento))
			{
				somavalorrel = somavalorrel + cagendamento->precovalor;
			}
			if (!feof(pagendamento))
			{
				fprintf(relatorio, "\n%i;%.2s.%.3s.%.3s/%.4s-%.2s;%s;%.2s/%.2s/%.4s;%0.2f", cagendamento->codigo, cagendamento->filial.cnpj, cagendamento->filial.cnpj + 2, cagendamento->filial.cnpj + 5, cagendamento->filial.cnpj + 8, cagendamento->filial.cnpj + 12, cagendamento->filial.nome, cagendamento->data, cagendamento->data + 2, cagendamento->data + 4, cagendamento->precovalor);
			}
		}

		// if(feof(pagendamento))
		// {
		// 	break;
		// }

		if (strcmp(scan, "1") == 0)
		{
			//char valortotaltxt[1000];
			l2 = 1;
			fprintf(relatorio, "\n\n;;;;;%0.2f\n", somavalorrel);
		}
	}
	fclose(pagendamento);
	fclose(relatorio);

	if (l2 == 1)
	{
		printf("\n\nRelatorio gerado com sucesso!\n\n");
	}
	else
	{
		printf("\n\n\nNao foram encontrados registros para esse CNPJ!\n\n");
	}

	char func_con[2];
	while (strcmp(func_con, "1") != 0 || strcmp(func_con, "2") != 0)
	{

		memset(func_con, 0, sizeof(func_con));

		printf("\n\nTecle [1] para voltar ou [2] gerar um novo relatorio: ");
		tratamento_numeroum(func_con, 0);

		switch (func_con[0])
		{
		case '1':
			main_relatorio();
			break;
		case '2':
			relatorio_filialtotal();
			break;
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	getchar();
	return 0;
}

/*-----------------------------------------------------------------------*/

/*FUNÇÕES*/
int verifica_useradm(void)
{
	const char *buscar_adm = "admin";
	char senha_adm[52];
	char repete_senha_adm[52];

	system("mkdir dados");

	user *usuario = calloc(1, sizeof(user) * 1);

	puser = fopen("dados\\cad_funcionario.txt", "a+");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao excluir arquivo de funcionarios, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	//Comparar strings com strcmp
	while (!feof(puser) && strcmp(usuario->usuario, buscar_adm) != 0)
	{
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &usuario->codigo, usuario->nome, usuario->celular, usuario->email, usuario->cpf, usuario->usuario, usuario->senha, usuario->endereco.estado, usuario->endereco.cidade, usuario->endereco.bairro, usuario->endereco.logradouro, usuario->endereco.complemento, usuario->endereco.cep);
	}
	while (strcmp(usuario->usuario, buscar_adm) != 0)
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
		if (strcmp(senha_adm, repete_senha_adm) == 0)
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
		}
		else if (strcmp(senha_adm, repete_senha_adm) != 0)
		{
			memset(senha_adm, 0, sizeof(senha_adm));
			memset(repete_senha_adm, 0, sizeof(repete_senha_adm));
			printf("\n\nAs senhas nao conferem, adicione senhas iguais!\n\n");
			printf("\nTecle ENTER para tentar novamente!\n");
			getchar();
		}
	}
	fclose(puser);
	return 0;
}

int tela_login(void)
{
	int i, tam_msg;
	char scan[52], scan2[52], crip_msg[52];
	memset(scan, 0, sizeof(scan));
	memset(scan2, 0, sizeof(scan2));
	memset(crip_msg, 0, sizeof(crip_msg));
	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao excluir arquivo de funcionarios, pode ser permissao?");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	user *usuario = calloc(1, sizeof(user) * 1);

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
	while (!feof(puser))
	{
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &usuario->codigo, usuario->nome, usuario->celular, usuario->email, usuario->cpf, usuario->usuario, usuario->senha, usuario->endereco.estado, usuario->endereco.cidade, usuario->endereco.bairro, usuario->endereco.logradouro, usuario->endereco.complemento, usuario->endereco.cep);

		if (strcmp(usuario->usuario, scan) == 0)
		{
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
	if (strcmp(usuario->usuario, scan) == 0)
	{
		if (strcmp(usuario->senha, crip_msg) == 0)
		{
			printf("\n\nLOGADO");
			main_principal();
		}
		else
		{
			printf("\n\nUsuario ou senha invalido!\n\n");
			system("pause");
			tela_login();
		}
	}
	else if (strcmp(usuario->usuario, scan) != 0)
	{
		printf("\n\nUsuario ou senha invalido!\n\n");
		system("pause");
		tela_login();
	}
	printf("\n\n\n");
	return 0;
}

void mostrarendereco(void)
{
	printf("11.Endereco(Estado)\n12.Endereco(Cidade)\n13.Endereco(Bairro)\n14.Endereco(Logradouro)\n15.Endereco(Complemento)\n16.Endereco(CEP) \n\nEscolha qual informacao voce deseja alterar e tecle ENTER: \n");
}

void tratamento_desc50(char *tdesc50, int tdesc50_size)
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
		}
		else if (c == 8 && i)
		{
			tdesc50[i] = '\0';
			i--;
			printf("\b \b");
		}
	} while (c != 13 || i == 0);
	tdesc50[i] = '\0';
}

void tratamento_desc1500(char *tdesc1500, int tdesc1500_size)
{
	/*TRATAMENTO PARA NOME OU DESCRIÇÃO DE 1500 CARACTERES*/
	int i;
	char c;

	memset(tdesc1500, 0, tdesc1500_size);
	i = 0;
	c = '\0';

	do
	{
		c = getch();
		if (isprint(c) != 0)
		{
			if (i < 1498)
			{
				tdesc1500[i] = c;
				i++;
				printf("%c", c);
			}
		}
		else if (c == 8 && i)
		{
			tdesc1500[i] = '\0';
			i--;
			printf("\b \b");
		}
	} while (c != 13 || i == 0);
	tdesc1500[i] = '\0';
}

void tratamento_estado(char *testado, int testado_size)
{
	/*TRATAMENTO PARA O ESTADO*/
	int i;
	char c;

	memset(testado, 0, testado_size);
	i = 0;
	c = '\0';

	do
	{
		c = getch();
		if (isprint(c) != 0)
		{
			if (i < 2)
			{
				testado[i] = c;
				i++;
				printf("%c", c);
			}
		}
		else if (c == 8 && i)
		{
			testado[i] = '\0';
			i--;
			printf("\b \b");
		}
	} while (c != 13 || i == 0 || i < 2);
	testado[i] = '\0';
}

void tratamento_cpf(char *tcpf, int tcpf_size)
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
				}
				else if (i == 9)
				{
					printf("-");
				}
			}
		}
		else if (c == 8 && i)
		{
			if (i == 3 || i == 6 || i == 9)
			{
				printf("\b \b");
				tcpf[i] = '\0';
				i--;
				printf("\b \b");
			}
			else
			{
				tcpf[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	} while (c != 13 || i == 0 || i < 11);
	tcpf[i] = '\0';
}

void tratamento_data(char *tdata, int tdata_size)
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
		}
		else if (c == 8 && i)
		{
			if (i == 2 || i == 4)
			{
				printf("\b \b");
				tdata[i] = '\0';
				i--;
				printf("\b \b");
			}
			else
			{
				tdata[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	} while (c != 13 || i == 0 || i < 8);
	tdata[i] = '\0';
}

void tratamento_tdta(char *tdta, int tdta_size)
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

	do
	{
		d = 0, m = 0, a = 0;

		memset(tdta, 0, tdta_size);

		tratamento_data(tdta, 8);

		sscanf(tdta, "\n%2d %2d %4d", &d, &m, &a);

		if (((d < data_hora_atual->tm_mday || d > 31) && (m < data_hora_atual->tm_mon + 1 || m == data_hora_atual->tm_mon + 1 || m > 12) && (a <= data_hora_atual->tm_year + 1900)) || (a < data_hora_atual->tm_year + 1900) || (d > data_hora_atual->tm_mday && m > 12))
		{
			printf("\n\nData invalida, tente outra!\n");
			printf("\nData do agendamento: \n");
		}

	} while (((d < data_hora_atual->tm_mday || d > 31) && (m < data_hora_atual->tm_mon + 1 || m == data_hora_atual->tm_mon + 1 || m > 12) && (a <= data_hora_atual->tm_year + 1900)) || (a < data_hora_atual->tm_year + 1900) || (d > data_hora_atual->tm_mday && m > 12));
}

void tratamento_dataqq(char *tdataqq, int tdataqq_size)
{
	/*TRATAMENTO PARA A DATA*/

	int i;
	char c;

	memset(tdataqq, 0, tdataqq_size);
	i = 0;
	c = '\0';
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 8)
			{
				tdataqq[i] = c;
				i++;
				printf("%c", c);
				if (i == 2 || i == 4)
				{
					printf("/");
				}
			}
		}
		else if (c == 8 && i)
		{
			if (i == 2 || i == 4)
			{
				printf("\b \b");
				tdataqq[i] = '\0';
				i--;
				printf("\b \b");
			}
			else
			{
				tdataqq[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	} while (c != 13 || i == 0 || i < 8);
	tdataqq[i] = '\0';
}

void tratamento_tdtaqq(char *tdtaqq, int tdtaqq_size)
{
	int d, m, a;

	do
	{
		d = 0, m = 0, a = 0;

		memset(tdtaqq, 0, tdtaqq_size);

		tratamento_data(tdtaqq, 8);

		sscanf(tdtaqq, "\n%2d %2d %4d", &d, &m, &a);

		if ((d > 31) || ( m > 12) || (a < 2000))
		{
			printf("\n\nData invalida, tente outra!\n");
			printf("\nData do agendamento: \n");
		}

	} while ((d > 31) || ( m > 12) || (a < 2020));
}

void tratamento_hora(char *thora, int thora_size)
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
		}
		else if (c == 8 && i)
		{
			if (i == 2)
			{
				printf("\b \b");
				thora[i] = '\0';
				i--;
				printf("\b \b");
			}
			else
			{
				thora[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	} while (c != 13 || i == 0 || i < 4);
	thora[i] = '\0';
}

void tratamento_numero(char *tnum, int tnum_size)
{
	/*TRATAMENTO PARA NUMERO*/

	int i;
	char c;

	memset(tnum, 0, tnum_size);
	i = 0;
	c = '\0';
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 2)
			{
				tnum[i] = c;
				i++;
				printf("%c", c);
			}
		}
		else if (c == 8 && i)
		{		
			tnum[i] = '\0';
			i--;
			printf("\b \b");
		}
	} while (c != 13 || i == 0);
	tnum[i] = '\0';
}

void tratamento_numeroum(char *tnumum, int tnumum_size)
{
	/*TRATAMENTO PARA NUMERO*/

	int i;
	char c;

	memset(tnumum, 0, tnumum_size);
	i = 0;
	c = '\0';
	do
	{
		c = getch();
		if (isdigit(c) != 0)
		{
			if (i < 1)
			{
				tnumum[i] = c;
				i++;
				printf("%c", c);
			}
		}
		else if (c == 8 && i)
		{
			tnumum[i] = '\0';
			i--;
			printf("\b \b");
		}
	} while (c != 13 || i == 0);
	tnumum[i] = '\0';
}

void tratamento_hm(char *thm, int thm_size)
{
	int h, m;

	do
	{
		h = 0, m = 0;
		memset(thm, 0, thm_size);

		tratamento_hora(thm, 4);

		sscanf(thm, "\n%2d %2d", &h, &m);

		if (h > 23 || m > 59)
		{
			printf("\n\nFavor digite a hora entre 00 e 23 e os minutos entre 00 e 59!\n");
			printf("\nHora do agendamento: \n");
		}

	} while (h > 23 || m > 59);
}

void tratamento_cnpj(char *tcnpj, int tcnpj_size)
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
				}
				else if (i == 8)
				{
					printf("/");
				}
				else if (i == 12)
				{
					printf("-");
				}
			}
		}
		else if (c == 8 && i)
		{
			if (i == 2 || i == 5 || i == 8 || i == 12)
			{
				printf("\b \b");
				tcnpj[i] = '\0';
				i--;
				printf("\b \b");
			}
			else
			{
				tcnpj[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	} while (c != 13 || i == 0 || i < 14);
}

void tratamento_senha(char *tsenha, int tsenha_size)
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
			if (i < 48)
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

void tratamento_celular(char *tcelular, int tcelular_size)
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
				if (i == 2)
				{
					printf("-");
				}
				else if (i == 7)
				{
					printf("-");
				}
			}
		}
		else if (c == 8 && i)
		{
			if (i == 2 || i == 7)
			{
				printf("\b \b");
				tcelular[i] = '\0';
				i--;
				printf("\b \b");
			}
			else
			{
				tcelular[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	} while (c != 13 || i == 0 || i < 11);
}

void tratamento_cep(char *tcep, int tcep_size)
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
				if (i == 5)
				{
					printf("-");
				}
			}
		}
		else if (c == 8 && i)
		{
			if (i == 5)
			{
				printf("\b \b");
				tcep[i] = '\0';
				i--;
				printf("\b \b");
			}
			else
			{
				tcep[i] = '\0';
				i--;
				printf("\b \b");
			}
		}
	} while (c != 13 || i == 0 || i < 8);
}

void incrementa_id_func(int *IDinc_func)
{
	puser = fopen("dados\\cad_funcionario.txt", "r");
	if (puser == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de funcionarios ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	user *usuarioi = calloc(1, sizeof(user) * 1);

	while (!feof(puser))
	{
		fscanf(puser, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &usuarioi->codigo, usuarioi->nome, usuarioi->celular, usuarioi->email, usuarioi->cpf, usuarioi->usuario, usuarioi->senha, usuarioi->endereco.estado, usuarioi->endereco.cidade, usuarioi->endereco.bairro, usuarioi->endereco.logradouro, usuarioi->endereco.complemento, usuarioi->endereco.cep);
	}
	fclose(puser);
	*IDinc_func = usuarioi->codigo;
}

void incrementa_id_paci(int *IDinc_paci)
{
	ppatient = fopen("dados\\cad_paciente.txt", "r");
	if (ppatient == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de pacientes ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	patient *pacientei = calloc(1, sizeof(patient) * 1);

	while (!feof(ppatient))
	{
		fscanf(ppatient, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &pacientei->codigo, pacientei->nome, pacientei->celular, pacientei->email, pacientei->cpf, pacientei->filial.cnpj, pacientei->endereco.estado, pacientei->endereco.cidade, pacientei->endereco.bairro, pacientei->endereco.logradouro, pacientei->endereco.complemento, pacientei->endereco.cep);
	}
	fclose(ppatient);
	*IDinc_paci = pacientei->codigo;
}

void incrementa_id_medi(int *IDinc_medi)
{
	pdoctor = fopen("dados\\cad_medico.txt", "r");
	if (pdoctor == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de medicos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	doctor *medicoi = calloc(1, sizeof(doctor) * 1);

	while (!feof(pdoctor))
	{
		fscanf(pdoctor, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &medicoi->codigo, medicoi->nome, medicoi->celular, medicoi->email, medicoi->cpf, medicoi->especialidade, medicoi->filial.cnpj, medicoi->endereco.estado, medicoi->endereco.cidade, medicoi->endereco.bairro, medicoi->endereco.logradouro, medicoi->endereco.complemento, medicoi->endereco.cep);
	}
	fclose(pdoctor);
	*IDinc_medi = medicoi->codigo;
}

void incrementa_id_fili(int *IDinc_fili)
{
	pfilial = fopen("dados\\cad_filial.txt", "r");
	if (pfilial == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de filial ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	branch *filiali = calloc(1, sizeof(branch) * 1);

	while (!feof(pfilial))
	{
		fscanf(pfilial, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n]s", &filiali->codigo, filiali->nome, filiali->cnpj, filiali->descricao, filiali->endereco.estado, filiali->endereco.cidade, filiali->endereco.bairro, filiali->endereco.logradouro, filiali->endereco.complemento, filiali->endereco.cep);
	}
	fclose(pfilial);
	*IDinc_fili = filiali->codigo;
}

void incrementa_id_agen(int *IDinc_agen)
{
	pagendamento = fopen("dados\\cad_agendamento.txt", "r");
	if (pagendamento == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de agendamentos ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	scheduling *agendamentoi = calloc(1, sizeof(scheduling) * 1);

	while (!feof(pagendamento))
	{
		fscanf(pagendamento, "%d\n %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %f\n %[^\n]s", &agendamentoi->codigo, agendamentoi->paciente.cpf, agendamentoi->paciente.nome, agendamentoi->medico.cpf, agendamentoi->medico.nome, agendamentoi->filial.cnpj, agendamentoi->filial.nome, agendamentoi->data, agendamentoi->hora, &agendamentoi->precovalor, agendamentoi->descricao);
	}
	fclose(pagendamento);
	*IDinc_agen = agendamentoi->codigo;
}

void incrementa_id_avale(int *IDinc_avale)
{
	pavaliacao = fopen("dados\\cad_avaliacaoe.txt", "r");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/elogio ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	evaluation *avaliacaoi = calloc(1, sizeof(evaluation) * 1);

	while (!feof(pavaliacao))
	{
		fscanf(pavaliacao, "%d\n %[^\n] %[^\n] %[^\n] %[^\n]", &avaliacaoi->codigo, avaliacaoi->agendamento.paciente.cpf, avaliacaoi->agendamento.paciente.nome, avaliacaoi->agendamento.data, avaliacaoi->elogio);
	}
	fclose(pavaliacao);
	*IDinc_avale = avaliacaoi->codigo;
}

void incrementa_id_avalr(int *IDinc_avalr)
{
	pavaliacao = fopen("dados\\cad_avaliacaor.txt", "r");
	if (pavaliacao == NULL)
	{
		fprintf(stderr, "\n\nErro ao abrir arquivo de avaliacoes/reclamacao ou ainda nao foi realizado nenhum cadastro!");

		char verificaarq[2];
		memset(verificaarq, 0, sizeof(verificaarq));

		printf("\n\nTecle [1] para voltar ao menu principal ou [2] para sair do programa: ");
		tratamento_numeroum(verificaarq, 0);

		switch (verificaarq[0])
		{
		case '1':
			main_principal();
			break;
		case '2':
			exit(0);
		default:
			printf("\nMenu inexistente, tente novamente [1] ou [2].");
			system("pause");
		}
	}

	evaluation *avaliacaoi = calloc(1, sizeof(evaluation) * 1);

	while (!feof(pavaliacao))
	{
		fscanf(pavaliacao, "%d\n %[^\n] %[^\n] %[^\n] %[^\n]", &avaliacaoi->codigo, avaliacaoi->agendamento.paciente.cpf, avaliacaoi->agendamento.paciente.nome, avaliacaoi->agendamento.data, avaliacaoi->reclamacao);
	}
	fclose(pavaliacao);
	*IDinc_avalr = avaliacaoi->codigo;
}

void criptografa_senha(char *crip_msg, int senha_encript_size)
{
	int i, tam_msg = 0;
	char senha_cript[52], c;

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
			if (i < 50)
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
