/***************************************************************************
 *  $MCI Módulo de implementaçăo: MEN  Mensagem
 *
 *  Arquivo gerado:              MENSAGEM.c
 *  Letras identificadoras:      MEN
 *
 *  Nome da base de software:    Arcabouço para a automaçăo de testes de programas redigidos em C
 *
 *  Projeto:    Trabalho 2 - Programaçăo Modular
 *  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellingotn Bezerra
 *
 *  $HA Histórico de evoluçăo:
 *     Versăo      Autor         Data                Observaçőes
 *     1.0          GB        15/11/2017       Criação do módulo
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define MENSAGEM_OWN
#include "MENSAGEM.H"
#undef MENSAGEM_OWN

#define TAM_MSG 251
static int contadorID = 1;

/***********************************************************************
 *
 *  $TC Tipo de dados: MEN Mensagem
 *
 *
 ***********************************************************************/

typedef struct MEN_tagMensagem {

    void * remetente;
        /* Ponteiro para o remetente */
    
    void * destinatario;
        /* Ponteiro para o destinatario */
    
    char texto[TAM_MSG];
        /* Texto da mensagem */
    
    int id;
        /* Numero identificador da mensagem */

} MEN_tpMensagem ;

/***************************************************************************
 *
 *  Função: MEN &Criar Mensagem
 *****/

MEN_tppMensagem MEN_CriarMensagem(void * remetente, void * destinatario, char *texto) {

	MEN_tppMensagem mensagem;
	if (remetente == NULL  || destinatario == NULL || texto == NULL || strlen(texto) == 0)
		return NULL;

	mensagem = (MEN_tpMensagem*)malloc(sizeof(MEN_tpMensagem));
	if (mensagem == NULL) 
		return NULL;

	mensagem->remetente = remetente;
	mensagem->destinatario = destinatario;
	strcpy(mensagem->texto, texto);
	mensagem->id = contadorID;

	contadorID++;

	return mensagem;
}

/***************************************************************************
 *
 *  Função: MEN &Obter texto da mensagem
 *****/

char * MEN_ObterTexto(MEN_tppMensagem mensagem) {
	if (mensagem == NULL) return NULL;

	return mensagem->texto;
}

/***************************************************************************
 *
 *  Função: MEN &Obter numero identificador da mensagem
 *****/

int MEN_ObterID(MEN_tppMensagem mensagem) {
	if (mensagem == NULL) return -1;

	return mensagem->id;
}

/***************************************************************************
 *
 *  Função: MEN &Obter remetente
 *****/
void * MEN_ObterRemetente(MEN_tppMensagem mensagem) {
 	if (mensagem == NULL)
 		return NULL;

 	return mensagem->remetente;
 }

 /***************************************************************************
 *
 *  Função: MEN &Obter destinatario
 *****/
void * MEN_ObterDestinatario(MEN_tppMensagem mensagem) {
 	if (mensagem == NULL)
 		return NULL;

 	return mensagem->destinatario;
 }


/***************************************************************************
 *
 *  Função: MEN &Comparar mensagens
 *****/
int MEN_CompararMensagem(void * pValor1, void * pValor2) {
	MEN_tppMensagem msg1, msg2;
	
	if ((pValor1 == NULL) || (pValor2 == NULL)) {
		return -2;
	}

	msg1 = (MEN_tppMensagem) pValor1;
	msg2 = (MEN_tppMensagem) pValor2;

	if (msg1->id == msg2->id)
		return 0;
	if (msg1->id > msg2->id)
		return 1;

	return -1;
}

/***************************************************************************
 *
 *  Função: MEN &Desativar o campo de perfil remetente
 *			Essa funcao deve ser chamada quando o perfil remetente será excluído
 *****/
MEN_tpCondRet MEN_DesativarRemetente(MEN_tppMensagem mensagem) {
	if (mensagem == NULL)
		return MEN_CondRetValorNulo;

	//faz o remetente apontar para NULL, pois ele será excluído
	mensagem->remetente = NULL;

	// se o destinatario for NULL, entao ambos perfis da mensagem foram excluidos -> mensagem pode ser excluída
	if(mensagem->destinatario == NULL)
		free(mensagem);

	return MEN_CondRetOK;
}

/***************************************************************************
 *
 *  Função: MEN &Desativar o campo de perfil remetente
 *			Essa funcao deve ser chamada quando o perfil destinatário será excluído
 *****/
MEN_tpCondRet MEN_DesativarDestinatario(MEN_tppMensagem mensagem) {
	if (mensagem == NULL)
		return MEN_CondRetValorNulo;

	//faz o destinatário apontar para NULL, pois ele será excluído
	mensagem->destinatario = NULL;

	// se o remetente for NULL, entao ambos perfis da mensagem foram excluidos -> mensagem pode ser excluída
	if(mensagem->remetente == NULL)
		free(mensagem);

	return MEN_CondRetOK;
}