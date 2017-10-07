/***************************************************************************
 *  $MCI Módulo de implementaçăo: PER  Perfil
 *
 *  Arquivo gerado:              PERFIL.c
 *  Letras identificadoras:      PER
 *
 *  Nome da base de software:    Arcabouço para a automaçăo de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - Programaçăo Modular
 *  Autores: GB - Gabrielle Brandenburg
    GC - Gabriel Cantergiani
    WB - Wellingotn Bezerra
 *
 *  $HA Histórico de evoluçăo:
 *     Versăo      Autor            Data                Observaçőes
 *     1.0       GB,GC,WB        02/out/2017       Criação do módulo
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

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
        /* Nome do perfil
         */
    
    char email[20];
        /* Email do perfil
         */
    
    char cidade[20];
        /* Cidade do perfil
         */
    
    int idade;
        /* Idade do perfil
         */
    
    int id;
        /* Id do perfil
         */

} PER_tpPerfil ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: PER Criar Perfil
 *****/

Perfil* PER_CriarPerfil(char *nome, char *email, char *cidade, int idade)
{
    
	Perfil *p;

	p = (Perfil*) malloc( sizeof(Perfil) );
	if( p == NULL ){
		printf("Espaco insuficiente");
		exit(1);
	} /* if */
    
	strcpy(p->nome, nome);
	strcpy(p->email, email);
	strcpy(p->cidade, cidade);
	p->idade = idade;

	return p;
    
} /* Fim função: PER  Criar Perfil */


/***************************************************************************
 *
 *  Função: PER Mostrar Perfil
 *****/

void PER_MostrarPerfil(Perfil *p) {
	printf("nome: %s, email: %s, cidade: %s, idade: %d", p->nome, p->email, p->cidade, p->idade);

} /* Fim função: PER  Mostrar Perfil */

/***************************************************************************
 *
 *  Função: PER Destruir Perfil
 *****/

void PER_destroirPerfil(Perfil *p) {
	free(p);

} /* Fim função: PER  Destruir Perfil */

/********** Fim do módulo de implementação: PER  Perfil  **********/
