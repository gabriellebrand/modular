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
#include   "PERFIL.H"

static int contadorID = 0;

/***********************************************************************
 *
 *  $TC Tipo de dados: MEN Mensagem
 *
 *
 ***********************************************************************/

typedef struct MEN_tagMensagem {

    PER_tppPerfil remetente;
        /* Ponteiro para o perfil remetente */
    
    PER_tppPerfil destinatario;
        /* Ponteiro para o perfil destinatario */
    
    char texto[250];
        /* Texto da mensagem */
    
    int id;
        /* Numero identificador da mensagem */

} MEN_tpMensagem ;

/***************************************************************************
 *
 *  Função: MEN &Criar Mensagem
 *****/

MEN_tppMensagem MEN_CriarMensagem(PER_tppPerfil remetente, PER_tppPerfil destinatario, char *texto) {

	MEN_tppMensagem mensagem;
	if (remente == NULL  || destinatario == NULL || texto == NULL || strlen(texto) == 0)
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

