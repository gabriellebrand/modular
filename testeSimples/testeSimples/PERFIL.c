﻿/***************************************************************************
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
    
    int idade;
        /* Idade do perfil */

} PER_tpPerfil ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: PER &Criar Perfil
 *****/

PER_tppPerfil PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, char genero, int idade ) {
    
	PER_tppPerfil pPerfil = ( PER_tppPerfil ) malloc( sizeof( PER_tpPerfil ));
	if( pPerfil == NULL ) {
		return pPerfil ;
	} /* if */
    
	if (PER_AlterarNome(pPerfil, pNome) != PER_CondRetOK){
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarCidade(pPerfil, pCidade) != PER_CondRetOK){
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarGenero(pPerfil, genero) != PER_CondRetOK){
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarIdade(pPerfil, idade) != PER_CondRetOK){
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}
	if (PER_AlterarEmail(pPerfil, pEmail) != PER_CondRetOK){
		PER_DestruirPerfil(pPerfil);
		return NULL;
	}

	return pPerfil ;
    
} /* Fim função: PER  &Criar Perfil */


/***************************************************************************
 *
 *  Função: PER &Destruir Perfil
 *****/

void PER_DestruirPerfil(void * pPerfil) {

    if(pPerfil != NULL) {
        free(pPerfil);
    } /* if */

} /* Fim função: PER  &Destruir Perfil */


/***************************************************************************
 *
 *  Função: PER Compara Perfil
 *****/

int PER_compararPerfil(void * pValor1, void * pValor2) {
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

char * PER_RecuperarEmail(PER_tppPerfil pPerfil) {
	if (pPerfil == NULL) return NULL;
	return pPerfil->email;
}

/***************************************************************************
 *
 *  Função: PER Alterar Nome
 *****/

PER_tpCondRet PER_AlterarNome(PER_tppPerfil pPerfil, char *pNome) {
	
	if (pNome == NULL) return PER_CondRetPonteiroNulo;
	if(strlen(pNome) == 0) return PER_CondRetStringVazia; //será que é necessário?
	//todo: verificar se precisa tratar caso em que o tamanho da string é maior que 100

	strcpy(pPerfil->nome, pNome);
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Alterar Cidade
 *****/

PER_tpCondRet PER_AlterarCidade(PER_tppPerfil pPerfil, char *pCidade) {
	
	if (pCidade == NULL) return PER_CondRetPonteiroNulo;
	if(strlen(pCidade) == 0) return PER_CondRetStringVazia;
	//todo: verificar se precisa tratar caso em que o tamanho da string é maior que 100

	strcpy(pPerfil->cidade, pCidade);
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Alterar Idade
 *****/

PER_tpCondRet PER_AlterarIdade(PER_tppPerfil pPerfil, int idade) {

	if (idade <= 0) return PER_CondRetValorInvalido;
	pPerfil->idade = idade;
	return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Alterar Genero
 *****/

PER_tpCondRet PER_AlterarGenero(PER_tppPerfil pPerfil, char genero) {

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

PER_tpCondRet PER_AlterarEmail(PER_tppPerfil pPerfil, char* pEmail) {

	if (pEmail == NULL) return PER_CondRetPonteiroNulo;
	if(strlen(pEmail) == 0) return PER_CondRetStringVazia;

	strcpy(pPerfil->email, pEmail);
	return PER_CondRetOK;
}



/********** Fim do módulo de implementação: PER  Perfil  **********/