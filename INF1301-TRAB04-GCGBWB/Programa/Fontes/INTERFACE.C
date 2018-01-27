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
#define BUF_SIZE 500

/********** Prototipo das funcoes encapsuladas pelo modulo **********/

void INT_CriarPerfil();
void INT_EnviarMensagem();
void INT_CriarAmizade();
void INT_BuscarPerfil();
void INT_ListarAmizades();
void INT_CarregarHistorico();
void INT_ExcluirPerfil();
void INT_ExcluirAmizade();
void INT_AlterarPerfil();

/******************************************************************/

void INT_MenuPrincipal() {
    int opcao = 0;
	char linha[BUF_SIZE];

    printf("\n::::::::::::::::::MENU PRINCIPAL::::::::::::::::::\n");
    printf("\n\t(1) Criar novo perfil \n\t(2) Criar uma nova amizade \n\t(3) Enviar uma mensagem \n\t(4) Carregar historico de mensagens \n\t(5) Buscar perfil \n\t(6) Listar amizades de perfil \n\t(7) Excluir Perfil \n\t(8) Excluir Amizade \n\t(9) Alterar Perfil \n\t(10) Sair\n");
    printf("\nDigite o numero da opcao desejada.\n");

    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &opcao);

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
			INT_CarregarHistorico();
			break;
        case 5:
			INT_BuscarPerfil();
			break;
        case 6:
			INT_ListarAmizades();
			break;
        case 7:
			INT_ExcluirPerfil();
			break;
        case 8:
			INT_ExcluirAmizade();
			break;
		case 9:
			INT_AlterarPerfil();
			break;
		case 10:
			exit(1);
        default:
        printf("\nOpcao invalida!\n");
    }

	fflush(stdin);
}

void INT_CriarPerfil() {
	char linha[BUF_SIZE];
	char nome[TAM_PERFIL], email[TAM_PERFIL], cidade[TAM_PERFIL], genero, dataNasc[11];
	CON_tpCondRet ret;
	printf("\n::::::::::::::::::CRIAR PERFIL::::::::::::::::::\n\nDigite todos os dados solicitados, respeitando o formato exigido.\nTodas as informacoes sao obrigatorias.\n");

	printf("\nNome:\n(max 100 caracteres)\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%[^\n]s", nome);
	
	printf("\nE-mail:\n(max 100 caracteres)\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email);
	
	printf("\nCidade:\n(max 100 caracteres)\n");
	fgets(linha, sizeof(cidade), stdin);
    sscanf(linha, "%[^\n]s", cidade);
	
	printf("\nGenero:\n(caractere 'F' - feminino ou 'M' - masculino ou 'O' - outro)\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%c", &genero);
	
	printf("\nData de nascimento:\n(no formato 'DD/MM/AAAA')\n");
	fgets(linha, sizeof(linha), stdin);
	
	if (strlen(linha) == 11)
		sscanf(linha, "%[^\n]s", dataNasc);
	else {
		printf("\n Data Invalida! %d \n", strlen(linha));
		return;
	}
	

	ret = CON_CriarPerfil(nome, email, cidade, genero, dataNasc);

	switch (ret) {
	case CON_CondRetOK:
		printf("\n\nPerfil criado com sucesso.\n");
		break;
	case CON_CondRetErroFormato:
		printf("\n!! Erro: formato do genero invalido. !!\n");
		break;
	case CON_CondRetLimiteString:
		printf("\n!! Erro: algum dado de entrada esta invalido. !!\n");
		break;
	case CON_PerfilJaExiste:
		printf("\n!! Erro: ja existe um perfil cadastrado com esse e-mail. !!\n");
		break;
	default:
		printf("\n!! Ocorreu um erro ao realizar o cadastro. !!\n");
	}
}

void INT_AlterarPerfil() {
	char linha[BUF_SIZE];
	char email[TAM_PERFIL], perfilDado[TAM_PERFIL], genero, dataNasc[11];
	CON_tpCondRet ret;
	int opcao;
	printf("\n::::::::::::::::::ALTERAR PERFIL::::::::::::::::::\n\n\tDigite o e-mail do perfil sera alterado.\n\n");

	printf("Email:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email);

    printf("\nEscolha uma das opcoes abaixo para alterar no perfil:\n\n\t(1) Nome\n\t(2) Cidade\n\t(3) Data de nascimento\n\t(4) Genero\n");

    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &opcao);

    switch (opcao){
    case 1:
    	printf("\nNovo nome:\n(max 100 caracteres)\n");
		fgets(linha, sizeof(linha), stdin);
    	sscanf(linha, "%[^\n]s", perfilDado);

    	ret = CON_AlterarPerfilNome(email, perfilDado);
    	break;
    case 2:
    	printf("\nNova cidade:\n(max 100 caracteres)\n");
		fgets(linha, sizeof(linha), stdin);
    	sscanf(linha, "%[^\n]s", perfilDado);

    	ret = CON_AlterarPerfilCidade(email, perfilDado);
    	break;
    case 3:
    	printf("\nNova data de nascimento:\n(no formato 'DD/MM/AAAA')\n");
		fgets(linha, sizeof(linha), stdin);
	
		if (strlen(linha) == 11)
			sscanf(linha, "%[^\n]s", dataNasc);
		else {
			printf("\n Data Invalida! %d \n", strlen(linha));
			return;
		}

		ret = CON_AlterarPerfilNasc(email, dataNasc);
		break;
    case 4:
    	printf("\nNovo genero:\n(caractere 'F' - feminino ou 'M' - masculino ou 'O' - outro)\n");
		fgets(linha, sizeof(linha), stdin);
    	sscanf(linha, "%c", &genero);

    	ret = CON_AlterarPerfilGenero(email, genero);
    	break;
    default:
    	printf("\nOpcao invalida!\n");
    	return;
    }


    if ((ret == CON_CondRetValorNulo) || (ret == CON_CondRetFaltouMemoria))
    	printf("\n!! Ocorreu um erro ao alterar o dado. !!\n");
    else if ((ret == CON_CondRetRedeVazia)||(ret == CON_CondRetNaoAchou))
    	printf("\nNao foi encontrado um perfil para esse email.\n");
    else if ((ret == CON_CondRetStringVazia)||(ret == CON_CondRetErroFormato))
    	printf("\n!!Dado invalido. !!\n");
    else
    	printf("\nDado alterado com sucesso.\n");

}

void INT_CriarAmizade() {
	CON_tpCondRet ret;
	char linha[BUF_SIZE];
	char email1[TAM_PERFIL], email2[TAM_PERFIL];
	printf("\n::::::::::::::::::CRIAR AMIZADE::::::::::::::::::\n\n\tDigite o e-mail dos dois perfis que serao conectados.\n\n");
	
	printf("E-mail 1:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email1);
	
	printf("E-mail 2:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email2);

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
		printf("\n!! Ocorreu um problema ao conectar os perfis. !!\n");
		break;
	case CON_CondRetOK:
		printf("\nPerfis conectados com sucesso.\n");
		break;
	default:
		printf("\n!! Algum dos perfis nao foi encontrado na rede.\n");
	}
}

void INT_EnviarMensagem() {
	char linha[BUF_SIZE];
	char mensagem[TAM_MSG], emailRem[TAM_PERFIL], emailDest[TAM_PERFIL];
	CON_tpCondRet ret;

	printf("\n::::::::::::::::::ENVIAR MENSAGEM::::::::::::::::::\n\n\tDigite o e-mail do remetente, o texto da mensagem e o e-mail do destinatario.\n\n");

	printf("E-mail do remetente:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", emailRem);

	printf("E-mail do destinatario:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", emailDest);
	
	printf("Texto da mensagem:\n");
	fgets(linha, sizeof(linha), stdin);
	printf("\n%d\n", strlen(linha));
    if (strlen(linha) > 1)
		sscanf(linha, "%[^\n]s", mensagem);
	else {
		printf("\n!! Erro: mensagem vazia !!\n");
		return;
	}


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
		printf("\n!! Erro: ueDados invalidos. !!\n");
		break;
	default:
		printf("\nAlgum (ou ambos) perfil nao foi encontrado na rede.\n");
	}

}

void INT_BuscarPerfil() {
	char linha[BUF_SIZE];
	char email[TAM_PERFIL];
	CON_tpCondRet ret;
	printf("\n::::::::::::::::::BUSCAR PERFIL::::::::::::::::::\n\n\tDigite o e-mail do perfil a ser buscado.\n\n");

	printf("Email:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email);

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

void INT_ListarAmizades() {
	char linha[BUF_SIZE];
	char email[TAM_PERFIL];
	CON_tpCondRet ret;

	printf("\n::::::::::::::::::LISTAR AMIZADES::::::::::::::::::\n\nDigite o email do perfil para listar todas as amizades.\n");
	
	printf("Email:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email);
	
	ret = CON_BuscarAmizades(email);

	switch (ret) {
	case CON_CondRetOK:
		break;
	case CON_CondRetNaoAchou:
		printf("\nNao foi encontrado nenhum amigo para esse e-mail.\n");
		break;
	case CON_CondRetValorNulo:
		printf("\n!! Erro: Ocorreu um problema ao buscar as amizades do perfil. !!\n");
		break;
	default:
		printf("\nNao foi encontrado um perfil com esse e-mail.\n");
	}

}

void INT_CarregarHistorico() {
	char linha[BUF_SIZE];
	char email1[TAM_PERFIL], email2[TAM_PERFIL];
	CON_tpCondRet ret;

	printf("\n::::::::::::::::::MOSTRAR CONVERSA::::::::::::::::::\n\nDigite o email dos perfis para carregar a conversa entre eles.\n");

	printf("E-mail 1:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email1);
	
	printf("E-mail 2:\n");
	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email2);
	
	ret = CON_CarregarHistorico(email1, email2);

	switch (ret) {
	case CON_CondRetRedeVazia:
		printf("\nOs perfis nao estao cadastrados no sistema. \n");
		break;
	case CON_CondRetNaoAchou:
		printf("\n Algum dos perfis nao foi encontrado na rede.\n");
		break;
	case CON_CondRetOK:
		printf("\n--Fim da conversa--\n");
		break;
	default:
		printf("\n!! Ocorreu um erro ao buscar algum dos perfis. !!\n");
	}
}

void INT_ExcluirPerfil() {
	char linha[BUF_SIZE];
	char email[TAM_PERFIL];
	CON_tpCondRet ret;

	printf("\n::::::::::::::::::EXCLUIR PERFIL::::::::::::::::::\n\nDigite o email do perfil que deseja excluir.\n");

	fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s", email);

	ret = CON_ExcluirPerfil (email);

	switch (ret) {
	case CON_CondRetStringVazia:
		printf("\n!! E-mail invalido. !!\n");
		break;
	case CON_CondRetValorNulo:
		printf("\n!! Ocorreu um erro ao buscar o perfil. !!\n");
		break;
	case CON_CondRetOK:
		printf("\nPerfil excluido com sucesso.\n");
		break;
	default:
		printf("\nNao foi encontrado um perfil com esse email.\n");
	}


}

void INT_ExcluirAmizade() {
	char email1[TAM_PERFIL], email2[TAM_PERFIL];
	CON_tpCondRet ret;

	printf("\n::::::::::::::::::EXCLUIR AMIZADE::::::::::::::::::\n\nDigite o email dos perfis para excluir a amizade entre eles.\n");

	printf("E-mail 1:\n");
	scanf(" %[^\n]", email1);
	
	printf("E-mail 2:\n");
	scanf(" %[^\n]", email2);

	ret = CON_ExcluirAmizade (email1, email2);

	switch (ret) {
	case CON_CondRetStringVazia:
		printf("\n!! Dados de entrada invalidos. !!\n");
		break;
	case CON_CondRetAmizadeInvalida:
		printf("\n!! Esses perfis nao sao amigos. !!\n");
		break;
	case CON_CondRetOK:
		printf("\nAmizade excluida com sucesso.\n");
		break;
	default:
		printf("\nUm (ou ambos) dos perfis nao existe.\n");
	}

}

void INT_MostrarMensagem(char *pTexto, char * pRemetente) {
	if (pTexto != NULL && pRemetente != NULL)
		printf("\n\t%s:  %s\n", pRemetente, pTexto);
	else
		printf("\n[Nao foi possivel imprimir a mensagem.]\n");
}

void INT_MostrarPerfil(char * email, char * nome, char * cidade, char *genero, char *dataNasc) {
	if (nome != NULL)
		printf("\n\tNome: %s", nome);
	if (email != NULL)
		printf("\n\tE-mail: %s", email);
	if (cidade != NULL)
		printf("\n\tCidade: %s", cidade);
	if (genero != NULL)
		printf("\n\tGenero: %c", *genero);
	if (dataNasc != NULL)
		printf("\n\tData de nascimento: %s", dataNasc);

}

// OBS: MAIN FOI COMENTADA PARA RODAR O SCRIPT DE TESTE DO CONTROLADOR!
/*
int main (void) {

	printf("\n::::::::::::::::::REDE DE RELACIONAMENTOS::::::::::::::::::\n\n");

	while(1)
		INT_MenuPrincipal();
    
    return 0;
}
*/
