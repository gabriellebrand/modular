/**************************************************************************
*  $MCI Módulo de implementação: INT Interface
*
*  Arquivo gerado:              INTERFACE.c
*  Letras identificadoras:      INT
*
*
*  Projeto:    Trabalho 2 - Programaçăo Modular
*  Autores:    GB - Gabrielle Brandenburg
*              GC - Gabriel Cantergiani
*              WB - Wellingotn Bezerra
*
*  $HA Histórico de evoluçăo:
*     Versăo      Autor         Data                Observaçőes
*     1.0          GC        18/11/2017       início do desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PERFIL.h"
#include "grafo.h"

#define INTERFACE_OWN
#include "INTERFACE.H"
#undef INTERFACE_OWN

#define TAM_PERFIL 101
#define TAM_MSG 251

/********** Prototipo das funcoes encapsuladas pelo modulo **********/

void INT_CriarPerfil();
void INT_EnviarMensagem();
void INT_CriarAmizade();
void INT_BuscarPerfil();

void INT_MenuPrincipal() {
    int opcao = 0;
    printf("\n*****MENU PRINCIPAL*****\n");
    printf("\n\t(1) Criar novo perfil \n\t(2) Criar uma nova amizade \n\t(3) Enviar uma mensagem \n\t(4) Carregar historico de mensagens \n\t(5) Buscar perfil \n\t(6) Listar amizades de perfil \n\t(7) Excluir Perfil \n\t(8) Excluir Amizade \n");
    printf("\nDigite o numero da opcao desejada.\n");

    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
			INT_CriarPerfil();
			break;
        case 2:
			INT_CriarAmizade();
			break;
        case 3:
			INT_EnviarMensagem();
			break;
        case 4:
			printf("\nOK! 4\n");
			break;
        case 5:
			INT_BuscarPerfil();
			break;
        case 6:
			printf("\nOK! 6\n");
			break;
        case 7:
			printf("\nOK! 7\n");
			break;
        case 8:
			printf("\nOK! 8\n");
			break;
        default:
        printf("\nOpcao invalida!\n");
    }
}

void INT_CriarPerfil() {
	char nome[TAM_PERFIL], email[TAM_PERFIL], cidade[TAM_PERFIL], genero, dataNasc[11];
	CON_tpCondRet ret;
	printf("\n*****CRIAR PERFIL*****\n\nDigite todos os dados solicitados, respeitando o formato exigido.\nTodas as informacoes sao obrigatorias.\n");

	printf("\nNome:\n(max 100 caracteres)\n");
	scanf(" %[^\n]", nome);
	
	printf("\nE-mail:\n(max 100 caracteres)\n");
	scanf(" %[^\n]", email);
	
	printf("\nCidade:\n(max 100 caracteres)\n");
	scanf(" %[^\n]%*c", cidade);
	
	printf("\nGenero:\n(caractere 'F' - feminino ou 'M' - masculino ou 'O' - outro)\n");
	scanf("%c", &genero);
	
	printf("\nData de nascimento:\n(no formato 'DD/MM/AAAA')\n");
	scanf(" %[^\n]", dataNasc);

	//printf("\nOs dados do perfil sao: \n%s %s %s %c %s\n", nome, email, cidade, genero, dataNasc);

	ret = CON_CriarPerfil(nome, email, cidade, genero, dataNasc);

	switch (ret) {
	case CON_CondRetOK:
		printf("\nPerfil criado com sucesso.\n");
		break;
	case CON_CondRetErroFormato:
		printf("\n!! Erro: formato do genero invalido. !!\n");
		break;
	case CON_CondRetLimiteString:
		printf("\n!! Erro: algum dado ultrapassou limite de caracteres. !!\n");
		break;
	case CON_PerfilJaExiste:
		printf("\n!! Erro: ja existe um perfil cadastrado com esse e-mail. !!\n");
		break;
	default:
		printf("\n!! Ocorreu um erro ao realizar o cadastro. !!\n");
	}
}

void INT_CriarAmizade() {
	CON_tpCondRet ret;
	char email1[TAM_PERFIL], email2[TAM_PERFIL];
	printf("\n*****CRIAR AMIZADE*****\n\n\tDigite o e-mail dos dois perfis que serao conectados.\n\n");
	
	printf("E-mail 1:\n");
	scanf(" %[^\n]", email1);
	
	printf("E-mail 2:\n");
	scanf(" %[^\n]", email2);

	ret = CON_CriarAmizade(email1, email2);

	switch (ret) {
	case CON_CondRetAmizadeJaExiste:
		printf("\n!! Amizade ja' existe entre os dois perfis.\n");
		break;
	case CON_CondRetAmizadeInvalida:
		printf("\n!! Erro: nao e' possivel conectar um perfil com ele mesmo. !!\n");
		break;
	case CON_CondRetStringVazia:
		printf("\n!! Erro: e-mails invalidos. !!\n");
		break;
	case CON_CondRetValorNulo:
		printf("\n!! Ocorreu um problema ao conectar os perfis :( Tente novamente.\n");
		break;
	case CON_CondRetOK:
		printf("\nPerfis conectados com sucesso.\n");
		break;
	default:
		printf("\n!! Algum dos perfis nao foi encontrado na rede.\n");
	}
}

void INT_EnviarMensagem() {
	char mensagem[TAM_MSG], emailRem[TAM_PERFIL], emailDest[TAM_PERFIL];
	CON_tpCondRet ret;

	printf("\n*****ENVIAR MENSAGEM*****\n\n\tDigite o e-mail do remetente, o texto da mensagem e o e-mail do destinatario.\n\n");

	printf("E-mail do remetente:\n");
	scanf(" %[^\n]", emailRem);
	
	printf("Texto da mensagem:\n");
	scanf(" %[^\n]", mensagem);

	printf("E-mail do destinatario:\n");
	scanf(" %[^\n]", emailDest);

	ret = CON_EnviarMensagem(emailRem, emailDest, mensagem);

	switch (ret) {
	case CON_CondRetOK:
		printf("\nMensagem enviada com sucesso.\n");
		break;
	case CON_CondRetAmizadeNaoExiste:
		printf("\n!! Erro: nao foi possivel enviar mensagem pois os perfis nao estao conectados. !!\n");
		break;
	case CON_CondRetFaltouMemoria:
		printf("\n!! Ocorreu um problema ao enviar a mensagem :( Tente novamente.\n");
		break;
	case CON_CondRetValorNulo:
		printf("\n!! Erro: Dados invalidos. !!\n");
		break;
	default:
		printf("\nAlgum (ou ambos) perfil nao foi encontrado na rede.\n");
	}

}

void INT_BuscarPerfil() {
	char email[TAM_PERFIL];
	CON_tpCondRet ret;
	printf("\n*****BUSCAR PERFIL*****\n\n\tDigite o e-mail do perfil a ser buscado.\n\n");

	printf("Email:\n");
	scanf(" %[^\n]", email);

	ret = CON_MostrarPerfil (email);
	
	switch (ret) {
	case CON_CondRetOK:
		//printf("\nMensagem enviada com sucesso.\n");
		break;
	case CON_CondRetStringVazia:
		printf("\n!! Erro: Dado vazio. !!\n");
		break;
	case CON_CondRetValorNulo:
		printf("\n!! Erro: Ocorreu um problema ao buscar o perfil. !!\n");
		break;
	default:
		printf("\nNao foi encontrado um perfil com esse e-mail.\n");
	}

}



int main (void) {

	printf("\n******** REDE DE RELACIONAMENTOS ********\n\n");

	while(1)
		INT_MenuPrincipal();
    
    return 0;
}