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
 *     1.2      GB      15/nov/2017   Inclusão das funções de edição
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

/***** Protótipo de funcoes encapsuladas pelo módulo *****/
PER_tpCondRet PER_AlterarEmail(PER_tppPerfil pPerfil, char* email);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: PER &Criar Perfil
 *****/

PER_tppPerfil PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, char genero, char *pDataNasc ) {
    
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
  if (PER_AlterarDataNasc(pPerfil, pDataNasc)  != PER_CondRetOK) {
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
      IrInicioLista(perfil->msgEnviadas);
      do {
      //acessar a estrutura da mensagem e desativar o perfil remetente.
        mensagem = (MEN_tppMensagem) LIS_ObterValor(perfil->msgEnviadas);
        //se o ponteiro do destinatário também for NULL, a mensagem será excluída.
        MEN_DesativarRemetente(mensagem);
      } while (LIS_AvancarElementoCorrente(perfil->msgEnviadas,1) != LIS_CondRetFimLista);


      //percorrer a lista de mensagens recebidas
      IrInicioLista(perfil->msgRecebidas);
      do {
      //acessar a estrutura da mensagem e desativar o perfil remetente.
        mensagem = (MEN_tppMensagem) LIS_ObterValor(perfil->msgRecebidas);
        //se o ponteiro do remetente também for NULL, a mensagem será excluída.
        MEN_DesativarDestinatario(mensagem);
      } while (LIS_AvancarElementoCorrente(perfil->msgRecebidas,1) != LIS_CondRetFimLista);


    //excluir lista de enviadas
    LIS_DestruirLista(perfil->msgEnviadas);
    //excluir lista de recebidas
    LIS_DestruirLista(perfil->msgRecebidas);

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
    printf("\t  Data Nascimento: %s\n", pPerfil->dataNasc);

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

PER_tpCondRet PER_AlterarNome(PER_tppPerfil pPerfil, char * nome) {
  
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

PER_tpCondRet PER_AlterarCidade(PER_tppPerfil pPerfil, char * cidade) {
  
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
 *  OBS: Essa função não deve ser exportada
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
PER_tpCondRet PER_EnviarMensagem(PER_tppPerfil remetente, char *texto, PER_tppPerfil destinatario) {
  MEN_tppMensagem mensagem;

  mensagem = MEN_CriarMensagem((void*)remetente, (void*)destinatario, texto);

  if (mensagem == NULL)
    return PER_CondRetPonteiroNulo;

  if (LIS_InserirElementoApos(remetente->msgEnviadas, (void *)mensagem) == LIS_CondRetFaltouMemoria)
    return PER_CondRetFaltouMemoria;

  if (LIS_InserirElementoApos(destinatario->msgRecebidas, (void *)mensagem) == LIS_CondRetFaltouMemoria) {
    //necessário excluir o ultimo elemento inserido na lista de enviados do remetente
    LIS_ExcluirElemento(remetente->msgEnviadas);
    return PER_CondRetFaltouMemoria;
  }

  return PER_CondRetOK;
}

/***************************************************************************
 *
 *  Função: PER Verifica Mensagem Enviada
 *
 *  Função de apoio à PER_BuscarMsgEnviada
 *
 *  Retorno:
 *    PER_CondRetPonteiroNulo - erro na estrutura
 *    PER_CondRetOK - encontrou uma mensagem
 *    PER_CondRetNaoAchoou - nao encontrou mensagem
 ***************************************************************************/

PER_tpCondRet PER_VerificaMsgEnviada(PER_tppPerfil pPerfil, char *pEmail, char * textoMsg, int * idMsg) {
  MEN_tppMensagem msg;
  PER_tppPerfil destinatario;

  msg = (MEN_tppMensagem) LIS_ObterValor(pPerfil->msgEnviadas);
  if (msg == NULL)
    return PER_CondRetPonteiroNulo;

  destinatario = (PER_tppPerfil) MEN_ObterDestinatario(msg);
  if (destinatario == NULL)
    return PER_CondRetPonteiroNulo;

  if (PER_CompararPerfil(destinatario, (void *) pEmail) == 0) {
    //encontrou uma mensagem cujo destinatario possui o email requerido
    
    //copia o id da msg pro parametro idMsg para ser acessado pelo cliente
    *idMsg = MEN_ObterID(msg);
    //copia o texto da msg pro parametro do textoMsg
    textoMsg = MEN_ObterTexto(msg);

    return PER_CondRetOK;
  }

  return PER_CondRetNaoAchou;
}

/***************************************************************************
 *
 *  Função: PER Buscar Mensagem 
 *      Funciona como um "iterador". se parametro inicio == 0, entao vai pro inicio da lista.
 *****/
PER_tpCondRet PER_BuscarMsgEnviada(PER_tppPerfil pPerfil, char * pEmail, int inicio, char * textoMsg, int * idMsg) {
  PER_tpCondRet ret;

  if ((pPerfil == NULL) || (pEmail == NULL))
    PER_CondRetPonteiroNulo;

  if (inicio == 0) { //primeira iteracao
    IrInicioLista(pPerfil->msgEnviadas);

    ret = PER_VerificaMsgEnviada(pPerfil, pEmail,textoMsg, idMsg);

    switch (ret) {
    case PER_CondRetOK:
      return PER_CondRetOK; //encontrou a mensagem já no primeiro elemento
    case PER_CondRetPonteiroNulo:
      return PER_CondRetPonteiroNulo; //erro na estrutura -> mensagem acessada é nula ou destinatario é nulo
    }
    //se ret = CondRetNaoAchou -> entao continua buscando
  }

  //acessa elemento por elemento da lista de mensagens, buscando a mensagem cujo destinatário possui o email requerido
  while (LIS_AvancarElementoCorrente(pPerfil->msgEnviadas,1) == LIS_CondRetOK) {

    ret = PER_VerificaMsgEnviada(pPerfil, pEmail,textoMsg, idMsg);

    switch (ret) {
    case PER_CondRetOK:
      return PER_CondRetOK; //encontrou a mensagem entao retorna
    case PER_CondRetPonteiroNulo:
      return PER_CondRetPonteiroNulo; //erro na estrutura -> mensagem acessada é nula ou destinatario é nulo
    }
    //se ret = CondRetNaoAchou -> entao continua buscando
  }

  return PER_CondRetNaoAchou; //chegou ao fim das mensagens e nao encontrou mais nenhuma
}

/***************************************************************************
 *
 *  Função: PER Verifica Mensagem Recebida
 *
 *  Função de apoio à PER_BuscarMsgEnviada
 *
 *  Retorno:
 *    PER_CondRetPonteiroNulo - erro na estrutura
 *    PER_CondRetOK - encontrou uma mensagem
 *    PER_CondRetNaoAchoou - nao encontrou mensagem
 ***************************************************************************/

PER_tpCondRet PER_VerificaMsgRecebida(PER_tppPerfil pPerfil, char *pEmail, char * textoMsg, int * idMsg) {
  MEN_tppMensagem msg;
  PER_tppPerfil destinatario;

  msg = (MEN_tppMensagem) LIS_ObterValor(pPerfil->msgRecebidas);
  if (msg == NULL)
    return PER_CondRetPonteiroNulo;

  destinatario = (PER_tppPerfil) MEN_ObterDestinatario(msg);
  if (destinatario == NULL)
    return PER_CondRetPonteiroNulo;

  if (PER_CompararPerfil(destinatario, (void *) pEmail) == 0) {
    //encontrou uma mensagem cujo destinatario possui o email requerido
    
    //copia o id da msg pro parametro idMsg para ser acessado pelo cliente
    *idMsg = MEN_ObterID(msg);
    //copia o texto da msg pro parametro do textoMsg
    textoMsg = MEN_ObterTexto(msg);

    return PER_CondRetOK;
  }

  return PER_CondRetNaoAchou;
}

/***************************************************************************
 *
 *  Função: PER Buscar Mensagem 
 *      Funciona como um "iterador". se parametro inicio == 0, entao vai pro inicio da lista.
 *****/
PER_tpCondRet PER_BuscarMsgRecebida(PER_tppPerfil pPerfil, char * pEmail, int inicio, char * textoMsg, int * idMsg) {
  PER_tpCondRet ret;

  if ((pPerfil == NULL) || (pEmail == NULL))
    PER_CondRetPonteiroNulo;

  if (inicio == 0) { //primeira iteracao
    IrInicioLista(pPerfil->msgRecebidas);

    ret = PER_VerificaMsgRecebida(pPerfil, pEmail,textoMsg, idMsg);

    switch (ret) {
    case PER_CondRetOK:
      return PER_CondRetOK; //encontrou a mensagem já no primeiro elemento
    case PER_CondRetPonteiroNulo:
      return PER_CondRetPonteiroNulo; //erro na estrutura -> mensagem acessada é nula ou remetente é nulo
    }
    //se ret = CondRetNaoAchou -> entao continua buscando
  }

  //acessa elemento por elemento da lista de mensagens, buscando a mensagem cujo remetente possui o email requerido
  while (LIS_AvancarElementoCorrente(pPerfil->msgRecebidas,1) == LIS_CondRetOK) {

    ret = PER_VerificaMsgRecebida(pPerfil, pEmail,textoMsg, idMsg);
    
    switch (ret) {
    case PER_CondRetOK:
      return PER_CondRetOK; //encontrou a mensagem entao retorna
    case PER_CondRetPonteiroNulo:
      return PER_CondRetPonteiroNulo; //erro na estrutura -> mensagem acessada é nula ou destinatario é nulo
    }
    //se ret = CondRetNaoAchou -> entao continua buscando
  }

  return PER_CondRetNaoAchou; //chegou ao fim das mensagens e nao encontrou mais nenhuma
}

/********** Fim do módulo de implementação: PER  Perfil  **********/
