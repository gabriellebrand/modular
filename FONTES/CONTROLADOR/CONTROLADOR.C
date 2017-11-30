/**************************************************************************
*  $MCI Módulo de implementação: CON controlador
*
*  Arquivo gerado:              CONTROLADOR.c
*  Letras identificadoras:      CON
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
#include "PERFIL.H"
#include "grafo.h"

#define CONTROLADOR_OWN
#include "CONTROLADOR.H"
#undef CONTROLADOR_OWN


/*******   Protótipo das Funções Encapsuladas no Módulo *********************/



/************** Dados encapsulados no modulo   *********************************************************/

static GRA_tppGrafo Grafo = NULL; /* Ponteiro para o Grafo utilizado na rede de relacionamentos*/


/*******  Código das Funções Exportadas pelo Módulo ***********************/


/***********************************************************************
*
*  $FC Função: CON  &Criar Perfil
*
***********************************************************************/

CON_tpCondRet CON_CriarPerfil(char *pNome, char *pEmail, char *pCidade, char genero, char *pDataNasc) {

	PER_tppPerfil perfil = NULL;
	PER_tpCondRet retornoPerfil;
	GRA_tpCondRet retornoGrafo;
	char gen = 'O';

	/* Verifica se dados recebidos são válidos*/
	if ( pNome==NULL || pEmail==NULL || pCidade==NULL || pDataNasc==NULL)
		return CON_CondRetStringVazia;

	if (strlen(pNome)>100 || strlen(pEmail)>100 || strlen(pCidade)>100 || strlen(pDataNasc)>100 ) 
		return CON_CondRetLimiteString;

	if (genero!='M' && genero!='F' && genero!='O')
		return CON_CondRetErroFormato;

	/* Caso o Grafo ainda não exista, cria um Grafo*/
	if(Grafo==NULL)
		Grafo = GRA_CriarGrafo (PER_DestruirPerfil, PER_CompararPerfil);

	if (CON_BuscarPerfil(pEmail, &perfil) == CON_CondRetOK)
		return CON_PerfilJaExiste;

		/* Cria um ponteiro para o perfil*/
	perfil = PER_CriarPerfil (pNome, pEmail, pCidade, genero, pDataNasc);

	if (perfil==NULL)
		return CON_CondRetErroCadastro;

	/*Adiciona o Perfil como um vertice do grafo*/
	retornoGrafo = GRA_CriarVertice (Grafo, perfil, (void *)pEmail);

	if (retornoGrafo != GRA_CondRetOK)
		return CON_CondRetErroCadastro;

	/*Mostra as informações do perfil cadastrado na tela*/
	gen = PER_ObterGenero(perfil);
	INT_MostrarPerfil(PER_ObterEmail(perfil), PER_ObterNome(perfil), PER_ObterCidade(perfil), &gen, PER_ObterNascimento(perfil)); 

	return CON_CondRetOK;

}  /* Fim função: CON  &Criar Perfil */

/***********************************************************************
*
*  $FC Função: CON  &Buscar Perfil
*
***********************************************************************/

CON_tpCondRet CON_BuscarPerfil(char *email, PER_tppPerfil *pPerfil) {

	GRA_tpCondRet ret;

	if (email == NULL)
		return CON_CondRetValorNulo;
	if (strlen(email) == 0)
		return CON_CondRetStringVazia;

	ret = GRA_IrVertice(Grafo, (void*)email);

	if (ret != GRA_CondRetOK) 
		return CON_CondRetRedeVazia;
	
	if (ret == GRA_CondRetVerticeNaoExiste)
		return CON_CondRetNaoAchou;

	*pPerfil = (PER_tppPerfil) GRA_ObterValor(Grafo);

	if (pPerfil == NULL)
		return CON_CondRetValorNulo;

	return CON_CondRetOK;
	
}/* Fim função: CON  &Buscar Perfil */

/***********************************************************************
*
*  $FC Função: CON  &Mostrar Perfil
*
***********************************************************************/

CON_tpCondRet CON_MostrarPerfil (char *email) {

	PER_tppPerfil pPerfil = NULL;
	CON_tpCondRet ret;
	PER_tpCondRet pRet;
	char gen = 'O';

	/* Busca o perfil*/
	ret = CON_BuscarPerfil (email, &pPerfil);

	if (ret!=CON_CondRetOK)
		return ret;

	gen = PER_ObterGenero(pPerfil);

	/* Mostra o perfil, caso encontrado*/
	INT_MostrarPerfil(PER_ObterEmail(pPerfil), PER_ObterNome(pPerfil), PER_ObterCidade(pPerfil), &gen, PER_ObterNascimento(pPerfil)); 

	return CON_CondRetOK;
	
} /* Fim função: CON  &Mostrar Perfil */


/***********************************************************************
*
*  $FC Função: CON  &Excluir Perfil
*
***********************************************************************/
CON_tpCondRet CON_ExcluirPerfil (char *pEmail) {

	PER_tppPerfil pPerfil = NULL;
	CON_tpCondRet retCON;
	GRA_tpCondRet retGrafo;

	/*Buscar perfil*/
	retCON = CON_BuscarPerfil (pEmail, &pPerfil);

	if (retCON!= CON_CondRetOK)
		return retCON;

	/*Remove perfil do grafo*/
		/*Vai até o vertice*/
	retGrafo = GRA_IrVertice (Grafo, (void *)pEmail);

	switch (retGrafo) {
	case GRA_CondRetGrafoNaoExiste:
		return CON_CondRetRedeVazia;
	case GRA_CondRetGrafoVazio:
		return CON_CondRetRedeVazia;
	case GRA_CondRetVerticeNaoExiste:
		return CON_CondRetNaoAchou;
	}
		/*Remove vertice*/
	retGrafo = GRA_ExcluirVertCorr(Grafo);

	switch (retGrafo) {
	case GRA_CondRetOK:
		return CON_CondRetOK;
	default:
		return CON_CondRetRedeVazia;
	}

}	 /* Fim função: CON  &Excluir Perfil */


/***********************************************************************
*
*  $FC Função: CON  &Criar Amizade
*
***********************************************************************/
CON_tpCondRet CON_CriarAmizade(char *email1, char *email2) {
	GRA_tpCondRet ret;

	if ((email1 == NULL) || (email2 == NULL))
		return CON_CondRetValorNulo;
	if ((strlen(email1) == 0) || (strlen(email2) == 0))
		return CON_CondRetStringVazia;

	ret = GRA_CriarAresta(Grafo,(void*)email1, (void*)email2);

	switch (ret) {
	case GRA_CondRetVerticeNaoExiste:
		return CON_CondRetNaoAchou;
	case GRA_CondRetFaltouMemoria:
		//TODO: não sei o que precisa ser feito
		//tentar de novo? reportar que faltou memoria?
		return CON_CondRetFaltouMemoria;
	case GRA_CondRetArestaJaExiste:
		return CON_CondRetAmizadeJaExiste;
	case GRA_CondRetArestaIlegal:
		return CON_CondRetAmizadeInvalida;
	case GRA_CondRetOK:
		return CON_CondRetOK;
	default:
		return CON_CondRetRedeVazia;
	}
		
} /* Fim função: CON  &Criar Amizade */

/***********************************************************************
*
*  $FC Função: CON  &Excluir Amizade
*
***********************************************************************/

CON_tpCondRet CON_ExcluirAmizade (char *email1, char *email2) {

	GRA_tpCondRet retGrafo;

	/*Testa se valores sao validos*/
	if ( email1 == NULL || email2 == NULL)
		return CON_CondRetStringVazia;

	/*Chama função de excluir aresta*/
	retGrafo = GRA_ExcluirAresta (Grafo, (void *)email1, (void *)email2);

	/*Testa retorno*/
	if ((retGrafo == GRA_CondRetGrafoNaoExiste) || (retGrafo == GRA_CondRetGrafoVazio))
		return CON_CondRetRedeVazia;

	if (retGrafo == GRA_CondRetVerticeNaoExiste)
		return CON_CondRetNaoAchou;

	if (retGrafo == GRA_CondRetArestaNaoExiste)
		return CON_CondRetAmizadeInvalida;

	return CON_CondRetOK;
}/* Fim função: CON  &Excluir Amizade */

/***********************************************************************
*
*  $FC Função: CON  &Buscar Amizades
*
***********************************************************************/
CON_tpCondRet CON_BuscarAmizades(char *email) { /*Talvez seja melhor mudar o nome dessa funcao pra ListarAmizades */
	GRA_tpCondRet ret;
	int i = 0;
	//void * val = NULL;
	PER_tppPerfil perAmigo;

	do {
		//1. buscar o vertice relativo ao email passado
		ret = GRA_IrVertice (Grafo, email);

		if (ret == GRA_CondRetVerticeNaoExiste)
			return CON_PerfilNaoExiste;
		if (ret != GRA_CondRetOK)
			return CON_CondRetRedeVazia;
		
		//2. ir para o vizinho
		ret = GRA_AvancarVizinho (Grafo, i);

		if (ret == GRA_CondRetOK) {
			perAmigo = (PER_tppPerfil) GRA_ObterValor(Grafo);
			//4. chamar aqui a funcao que imprime os valores do perfil
			INT_MostrarPerfil(PER_ObterEmail(perAmigo), PER_ObterNome(perAmigo), NULL, NULL, NULL);
			//PER_MostrarPerfil(perAmigo);
			i++;
		}

	} while (ret == GRA_CondRetOK);

	switch (ret) {
	case GRA_CondRetNaoPossuiAresta:
		return CON_CondRetNaoAchou;
	case GRA_CondRetFimArestas:
		return CON_CondRetOK;
	case GRA_CondRetValorNulo:
		return CON_CondRetValorNulo;
	default:
		return CON_CondRetRedeVazia;
	}
	
} /* Fim função: CON  &Buscar Amizades */


/***********************************************************************
*		
*  $FC Função: CON  &Enviar Mensagem
*
***********************************************************************/
CON_tpCondRet CON_EnviarMensagem(char *email1, char *email2, char *texto) {
	GRA_tpCondRet ret;
	PER_tpCondRet pRet;
	CON_tpCondRet cRet;
	PER_tppPerfil remetente, destinatario;
	//1. verificar se os dois perfis sao amigos
	if ((cRet = CON_BuscarPerfil(email1, &remetente)) != CON_CondRetOK) {
		return cRet;
	}

	ret = GRA_IrVizinho(Grafo, email2);

	if ((ret == GRA_CondRetGrafoNaoExiste)||(ret == GRA_CondRetGrafoVazio))
		return CON_CondRetRedeVazia;
	if ((ret == GRA_CondRetArestaNaoExiste)||(ret == GRA_CondRetNaoPossuiAresta))
		return CON_CondRetAmizadeNaoExiste;
	if (ret == GRA_CondRetValorNulo)
		return CON_CondRetValorNulo;
	//if ret == GRA_CondRetOK ---> continua

	//2. acessar as referencias para o perfil1 e perfil 2
	destinatario = (PER_tppPerfil) GRA_ObterValor(Grafo);

	if (remetente == NULL || destinatario == NULL)
		return CON_CondRetValorNulo;

	//3. chamar a funcao enviar mensagem do modulo perfil
	pRet = PER_EnviarMensagem(remetente, texto, destinatario);

	switch (pRet) {
	case PER_CondRetPonteiroNulo:
		return CON_CondRetValorNulo;
	case PER_CondRetFaltouMemoria:
		return CON_CondRetFaltouMemoria; //nao sei se precisa fazer uma nova tentativa nesse caso.
	default:
		return CON_CondRetOK;
	}
}

CON_tpCondRet CON_CarregarHistorico(char *pEmail1, char *pEmail2) {
	int i = 0, idMsg1=0, idMsg2=0;
	char textoMsg1[TAM_MSG], textoMsg2[TAM_MSG], *nome1, *nome2;
	CON_tpCondRet ret;
	PER_tppPerfil perfil1, perfil2;

	/*
		Se idMsg == 0, entao está liberado procurar uma nova mensagem da lista
		Se idMsg > 0, entao a mensagem ainda nao foi impressa na tela, nao pode ser descartada (nao pode procurar a proxima da lista)
		Se idMsg < 0, entao todas as mensagens da lista ja foram encontradas, nao precisa procurar uma nova
	*/

	//busca perfil 1
	if ((ret = CON_BuscarPerfil(pEmail1, &perfil1)) != CON_CondRetOK)
		return ret;

	nome1 = PER_ObterNome(perfil1);

	//busca perfil 2 (necessario verificar se ele existe)
	if ((ret = CON_BuscarPerfil(pEmail2, &perfil2)) != CON_CondRetOK)
		return ret;

	nome2 = PER_ObterNome(perfil2);

	//acho que nao eh necessário verificar se os dois sao amigos, pois excluir amizade nao implica em excluir msgs trocadas

	while ((idMsg1 >= 0) || (idMsg2 >= 0)) {

		//busca uma mensagem enviada para o perfil2 na lista de mensagens enviadas pelo perfil1
		if (idMsg1 == 0) { //mensagem anterior já foi impressa, pode procurar a proxima
			if (PER_BuscarMsgEnviada(perfil1, pEmail2, i, textoMsg1, &idMsg1) != PER_CondRetOK) {
				//nao encontrou mais nenhuma mensagem ou entao deu algum erro
				idMsg1 = -1;
			}
		}

		//busca uma mensagem enviada pelo perfil2 na lista de mensagens recebidas pelo perfil1
		if (idMsg2 == 0) { //mensagem anterior já foi impressa, pode procurar a proxima
			if (PER_BuscarMsgRecebida(perfil1, pEmail2, i, textoMsg2, &idMsg2) != PER_CondRetOK) {
				//nao encontrou mais nenhuma mensagem ou entao deu algum erro
				idMsg2 = -1;
			}
		}

		//neste ponto nenhum dos idMsg's pode ter valor 0 (ou é < 0 ou é > 0)

		i++; //necessario para que nao volte para o inicio da lista de mensagens

		if (idMsg1 < 0) { // chegou ao fim da lista de msgs enviadas -> só resta imprimir as mensagens recebidas
			if (idMsg2 > 0) {
				//mensagem 2 ainda nao foi impressa -> chama funcao q imprime a mensagem (interface)
				INT_MostrarMensagem(textoMsg2, nome2);
				idMsg2 = 0; // marca mensagem 2 como impressa -> pode buscar a proxima
			}
		}

		else if (idMsg2 < 0) { // chegou ao fim da lista de msgs recebidas -> só resta imprimir as mensagens enviadas
			if (idMsg1 > 0) {
				//mensagem 1 ainda nao foi impressa -> chama funcao q imprime a mensagem (interface)
				INT_MostrarMensagem(textoMsg1, nome1);
				idMsg1 = 0; // marca mensagem 1 como impressa -> pode buscar a proxima
			}
		}

		else if ((idMsg1 > 0) && (idMsg2 > 0)) { //as duas mensagens estao aguardando impressao
			if (idMsg1 < idMsg2) {
				//chama funcao q imprime a mensagem 1 (interface)
				INT_MostrarMensagem(textoMsg1, nome1);
				idMsg1 = 0; // marca mensagem 1 como impressa -> pode buscar a proxima
			} else {
				//chama funcao q imprime a mensagem 2 (interface)
				INT_MostrarMensagem(textoMsg2, nome2);
				idMsg2 = 0; // marca mensagem 2 como impressa -> pode buscar a proxima
			}
		}
	}

	return CON_CondRetOK; //imprimiu todas as mensagens
}
