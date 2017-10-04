/***************************************************************************
*  $MCI Módulo de implementação: PERFIL  Módulo Perfil
*
*  Arquivo gerado:              PERFIL.c
*  Letras identificadoras:      PERFIL
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: wbs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       wbs   02/out/2017 Início do desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PERFIL.h"

struct perfil {

	char nome[100];
	char email[20];
	char cidade[20];
	int idade;

};

Perfil* criaPerfil(char *nome, char *email, char *cidade, int idade) {
    
	Perfil *p;

	p = (Perfil*) malloc( sizeof(Perfil) );
	if( p == NULL ){
		printf("Espaco insuficiente");
		exit(1);
	}
	strcpy(p->nome, nome);
	strcpy(p->email, email);
	strcpy(p->cidade, cidade);
	p->idade = idade;

	return p;
}

void mostraPerfil(Perfil *p) {
	printf("nome: %s, email: %s, cidade: %s, idade: %d", p->nome, p->email, p->cidade, p->idade);

}

void destroiPerfil(Perfil *p) {
	free(p);

}
