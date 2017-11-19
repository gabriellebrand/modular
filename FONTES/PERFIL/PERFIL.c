/***************************************************************************
 *  $MCI Módulo de implementaçăo: PER  Perfil
 *
 *  Arquivo gerado:              PERFIL.c
 *  Letras identificadoras:      PER
 *
 *  Nome da base de software:    Arcabouço para a automaçăo de testes de programas redigidos em C
 *
 *  Projeto:    Trabalho 2 - Programaçăo Modular
 *  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellingotn Bezerra
 *
 *  $HA Histórico de evoluçăo:
 *     Versăo      Autor            Data                Observaçőes
 *     1.0          WB        02/out/2017       Criação do módulo
 *     1.1          WB        14/out/2017       Alteração da função criarPerfil
 *	   1.2			GB 		  15/nov/2017		Inclusão das funções de edição
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define PERFIL_OWN
#include "PERFIL.h"
#undef PERFIL_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: PER Perfil
 *
 *
 ***********************************************************************/

typedef struct PER_tagPerfil {

    char nome[100];
        /* Nome do perfil */
    
    char email[100];
        /* Email do perfil */
    
    char cidade[100];
        /* Cidade do perfil */

    char genero;
    	/* Genero do perfil (M, F ou O) */
    
    char dataNasc[11];
        /* Data de nascimento do perfil XX/XX/XXXX */
    
    LIS_tppLista msgEnviadas;
    	/* Lista de mensagens enviadas pelo perfil */

    LIS_tppLista msgRecebidas;
    	/*Lista de mensagens recebidas pelo perfil */

} PER_tpPerfil ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: PER &Criar Perfil
 *****/

PER_tppPerfil PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, char genero, char dataNasc ) {
    
	LIS_tppLista msgEnv, msgRec;
	PER_tppPerfil pPerfil = ( PER_tppPerfil ) malloc( sizeof( PER_tpPerfil ));
	if( pPerfil == NULL ) {
		return NULL ;
	} /* if */
    
	if (PER_AlterarNome(pPerfil, pNome) != PER_CondRetOK) {
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarCidade(pPerfil, pCidade) != PER_CondRetOK) {
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarGenero(pPerfil, genero) != PER_CondRetOK) {
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarDataNasc(pPerfil, dataNasc)  != PER_CondRetOK) {
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarEmail(pPerfil, pEmail) != PER_CondRetOK) {
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}

	if ((msgEnv = LIS_CriarLista(NULL, MEN_CompararMensagem)) == NULL) {
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}

	if ((msgRec = LIS_CriarLista(NULL, MEN_CompararMensagem)) == NULL) {
		LIS_DestruirLista(msgRec);
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}

	pPerfil->msgRecebidas = msgRec;
	pPerfil->msgEnviadas = msgEnv;	

	return pPerfil;
    
} /* Fim função: PER  &Criar Perfil */

/***************************************************************************
 *
 *  Função: PER &Destruir Perfil
 *****/

void PER_DestruirPerfil(void * pPerfil) {

	PER_tppPerfil perfil;
	MEN_tppMensagem mensagem;
    
    if(pPerfil != NULL) {
    	//faz um typecast para PER_tppPerfil
    	perfil = (PER_tppPerfil) (pPerfil); 


		//percorrer a lista de mensagens enviadas
    	IrInicioLista(pPerfil->msgEnviadas);
    	do {
			//acessar a estrutura da mensagem e desativar o perfil remetente.
    		mensagem = (MEN_tppMensagem) LIS_ObterValor(pPerfil->msgEnviadas);
    		//se o ponteiro do destinatário também for NULL, a mensagem será excluída.
    		MEN_DesativarRemetente(mensagem);
    	} while (LIS_AvancarElementoCorrente(perfil->msgEnviadas,1) != LIS_CondRetFimLista);


    	//percorrer a lista de mensagens recebidas
    	IrInicioLista(pPerfil->msgRecebidas);
    	do {
			//acessar a estrutura da mensagem e desativar o perfil remetente.
    		mensagem = (MEN_tppMensagem) LIS_ObterValor(pPerfil->msgRecebidas);
    		//se o ponteiro do remetente também for NULL, a mensagem será excluída.
    		MEN_DesativarDestinatario(mensagem);
    	} while (LIS_AvancarElementoCorrente(perfil->msgRecebidas,1) != LIS_CondRetFimLista);


		//excluir lista de enviadas
		LIS_DestruirLista(pPerfil->msgEnviadas);
		//excluir lista de recebidas
		LIS_DestruirLista(pPerfil->msgRecebidas);

		//excluir perfil
        free(perfil);
    } /* if */

} /* Fim função: PER  &Destruir Perfil */


/***************************************************************************
 *
 *  Função: PER Compara Perfil
 *****/

int PER_CompararPerfil(void * pValor1, void * pValor2) {
    PER_tppPerfil pPerfil;
    char *email;
    pPerfil = (PER_tppPerfil) pValor1;
    email = (char*) pValor2;

    return strcmp(pPerfil->email, email);

} /* Fim função: PER  Comparar Perfil */  


/***************************************************************************
 *
 *  Função: PER Mostrar Perfil
 *****/

PER_tpCondRet PER_MostrarPerfil(PER_tppPerfil pPerfil) {

    if(pPerfil == NULL) {
        return PER_CondRetPonteiroNulo;
    } /* if */

    printf("\n\t  Nome: %s\n", pPerfil->nome );
    printf("\t  Email: %s\n", pPerfil->email);
    printf("\t  Cidade: %s\n", pPerfil->cidade);
    printf("\t  Idade: %d\n", pPerfil->idade);

    return PER_CondRetOK;

} /* Fim função: PER  Mostrar Perfil */

/***************************************************************************
 *
 *  Função: PER Recuperar Email
 *****/

char * PER_ObterEmail(PER_tppPerfil pPerfil) {
	if (pPerfil == NULL) return NULL;
	return pPerfil->email;
}

/***************************************************************************
 *
 *  Função: PER Alterar Nome
 *****/

PER_tpCondRet PER_AlterarNome(PER_tppPerfil pPerfil, char *nome) {
	
	if (nome == NULL || pPerfil == NULL) return PER_CondRetPonteiroNulo;
	if(strlen(nome) == 0) return PER_CondRetStringVazia; //será que é necessário?
	//todo: verificar se precisa tratar caso em que o tamanho da string é maior que 100

	strcpy(pPerfil->nome, nome);
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Alterar Cidade
 *****/

PER_tpCondRet PER_AlterarCidade(PER_tppPerfil pPerfil, char *cidade) {
	
	if (cidade == NULL || pPerfil == NULL) return PER_CondRetPonteiroNulo;
	if(strlen(cidade) == 0) return PER_CondRetStringVazia;
	//todo: verificar se precisa tratar caso em que o tamanho da string é maior que 100

	strcpy(pPerfil->cidade, cidade);
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Alterar Data de Nascimento
 *	
 *****/

PER_tpCondRet PER_AlterarDataNasc(PER_tppPerfil pPerfil, char * dataNasc) {
	if (dataNasc == NULL || pPerfil == NULL) return PER_CondRetPonteiroNulo;
	if(strlen(dataNasc) != 10 ) return PER_CondRetValorInvalido;
	//todo: verificar se precisa tratar caso em que o tamanho da string é maior que 100

	strcpy(pPerfil->dataNasc, dataNasc);
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Alterar Genero
 *****/

PER_tpCondRet PER_AlterarGenero(PER_tppPerfil pPerfil, char genero) {

	if (pPerfil == NULL) return PER_CondRetPonteiroNulo;

	if (genero != 'M' && genero != 'F' && genero != 'O')
		return PER_CondRetValorInvalido;

	pPerfil->genero = genero;
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Alterar Email
 *	OBS: Essa função não deve ser exportada
 *****/

PER_tpCondRet PER_AlterarEmail(PER_tppPerfil pPerfil, char* email) {

	if (email == NULL) return PER_CondRetPonteiroNulo;
	if(strlen(email) == 0) return PER_CondRetStringVazia;

	strcpy(pPerfil->email, email);
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Enviar Mensagem
 *****/
PER_tpCondRet PER_EnviarMensagem(PER_tppPerfil remetente, void * mensagem, PER_tppPerfil destinatario) {
	if (remetente == NULL || mensagem == NULL || destinatario == NULL)
		return PER_CondRetPonteiroNulo;

	if (LIS_InserirElementoApos(remetente->msgEnviadas, mensagem) == LIS_CondRetFaltouMemoria)
		return PER_CondRetFaltouMemoria;

	if (LIS_InserirElementoApos(destinatario->msgRecebidas, mensagem) == LIS_CondRetFaltouMemoria) {
		//necessário excluir o ultimo elemento inserido na lista de enviados do remetente
		LIS_ExcluirElemento(remetente->msgEnviadas);
		return PER_CondRetFaltouMemoria;
	}

	return PER_CondRetOK;
}





/********** Fim do módulo de implementação: PER  Perfil  **********/