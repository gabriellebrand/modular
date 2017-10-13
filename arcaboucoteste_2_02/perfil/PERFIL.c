/***************************************************************************
 *  $MCI Módulo de implementaçăo: PER  Perfil
 *
 *  Arquivo gerado:              PERFIL.c
 *  Letras identificadoras:      PER
 *
 *  Nome da base de software:    Arcabouço para a automaçăo de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - Programaçăo Modular
 *  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellingotn Bezerra
 *
 *  $HA Histórico de evoluçăo:
 *     Versăo      Autor            Data                Observaçőes
 *     1.0          WB        02/out/2017       Criação do módulo
 *
 ***************************************************************************/

#include   <stdio.h>
#include <stdlib.h>
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
    
    char email[20];
        /* Email do perfil */
    
    char cidade[20];
        /* Cidade do perfil */
    
    int idade;
        /* Idade do perfil */

} PER_tpPerfil ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: PER Criar Perfil
 *****/

PER_tpCondRet  PER_CriarPerfil( PER_tppPerfil* ppPerfil, char *pNome, char *pEmail, char *pCidade, int pIdade ) {
    
	PER_tpPerfil* pPerfil; 

	pPerfil = ( PER_tpPerfil * ) malloc( sizeof( PER_tpPerfil ));
	if( pPerfil == NULL )
    {
		return PER_CondRetFaltouMemoria ;
	} /* if */
    
	strcpy(pPerfil->nome, pNome);
	strcpy(pPerfil->email, pEmail);
	strcpy(pPerfil->cidade, pCidade);
	pPerfil->idade = pIdade;

    *ppPerfil = pPerfil;

	return PER_CondRetOK ;
    
} /* Fim função: PER  Criar Perfil */

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

//void PER_MostrarPerfil(PER_tppPerfil *pPerfil) {
	//printf("nome: %s, email: %s, cidade: %s, idade: %d", pPerfil->nome, pPerfil->email, pPerfil->cidade, pPerfil->idade);

//} /* Fim função: PER  Mostrar Perfil */

/***************************************************************************
 *
 *  Função: PER Destruir Perfil
 *****/

PER_tpCondRet PER_destroirPerfil(PER_tppPerfil *pPerfil) {

	if(pPerfil == NULL) {
        return PER_CondRetPonteiroNulo;
    }

    free(pPerfil);

    return PER_CondRetOK;

} /* Fim função: PER  Destruir Perfil */

/********** Fim do módulo de implementação: PER  Perfil  **********/
