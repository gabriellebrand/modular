/***************************************************************************
*  $MCD Módulo de definição: PERFIL  Módulo Perfil
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PERFIL
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observaçõess
*     1       wbs   02/out/2017 Início do desenvolvimento
*
*  $ED Descrição do Módulo
*     
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct perfil Perfil;

Perfil* criaPerfil(char *nome, char *email, char *cidade, int idade);

void mostraPerfil(Perfil *p);

void destroiPerfil(Perfil *p);

