/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clientes.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 21:19
 */

#include "estruturas.h"

CLIENTE * procurarCliente ( struct Clientes_helper * ListaClientes,  int aux_nif){
    CLIENTE *temp = ListaClientes->prim;
    while (temp != NULL) {
        if ( temp->nif == aux_nif ) {
            return temp;
        }
        temp = temp->prox;
    }
    return NULL;
}

int conta_val(CLIENTE * p){
    int total=0;
    printf("%d\n", total);
    if (p == NULL){
        printf("2\n");
        return total;
    }else{
        printf("1\n");
        total =  p->nr_alugueres;
        return total + conta_val(p->prox);
    }
}

bool criaLista(struct Clientes_helper * ListaClientes, CLIENTE clientes) {
    CLIENTE * temp = malloc(sizeof (CLIENTE));
    if (temp == NULL) {
        printf("[ERRO] Alocacao de memoria.\n");
        return false;
    }
    strcpy(temp->nome, clientes.nome);
    temp->nif = clientes.nif;
    temp->nr_alugueres = clientes.nr_alugueres;
    temp->aluga = NULL;
    temp->head = NULL;
    temp->banido = 0;

    temp->prox = NULL;

    ListaClientes->tamanho++;
    ListaClientes->prim = ListaClientes->atual = temp;
    return true;
}

bool AdicionaCliente(struct Clientes_helper * ListaClientes, CLIENTE clientes) {
    if (ListaClientes->prim == NULL) {
        return (criaLista(ListaClientes, clientes));
    } else {
        CLIENTE * temp = malloc(sizeof (CLIENTE));
        if (temp == NULL) {
            printf("[ERRO] Alocacao de memoria.\n");
            return false;
        }
        strcpy(temp->nome, clientes.nome);
        temp->nif = clientes.nif;
        temp->nr_alugueres = clientes.nr_alugueres;
        temp->aluga = NULL;
        temp->head = NULL;
        temp->prox = NULL;
        temp->banido = 0;

        ListaClientes->tamanho++;

        ListaClientes->atual->prox = temp;
        ListaClientes->atual = temp;

        return true;
    }
}

void AdicionaDadosCliente(struct Clientes_helper * ListaClientes){
    CLIENTE aux;
    printf("Indique o nome do cliente\n->");
    scanf("%s", aux.nome);
    do{
        printf("Indique o NIF do cliente\n->");
        scanf("%d", &aux.nif);
    }while (aux.nif < 99999999 || aux.nif > 1000000000);
    aux.nr_alugueres = 0;
    if (!AdicionaCliente(ListaClientes, aux)){
        printf("ERRO ao adicionar o cliente!");
    }
}

void listaCliente (CLIENTE * temp){
    int i;
    if (temp != NULL) {
        printf("%20s\t%d\n", temp->nome,temp->nif);
    } else {
        printf("Ponteiro CLIENTES NULL.\n");
    }
}

void listarTodosClientesAtivos(struct Clientes_helper * ListaClientes){
    CLIENTE *temp = ListaClientes->prim;
    while (temp != NULL) {
        if (temp->banido == 0){
            listaCliente(temp);
        }
    temp = temp->prox;
    }
}

void removerCliente (struct Clientes_helper * ListaClientes){
    CLIENTE * elimina = NULL;
    CLIENTE * anterior = NULL;
    elimina = ListaClientes->prim;
    int nif;
    printf("Indique o NIF do cliente:\n->");
    scanf("%d", &nif);
    while(elimina != NULL && elimina->nif != nif){
        anterior = elimina;
        elimina = elimina->prox;
    }
    if(elimina ==NULL){
        printf("ERRO Nenhum cliente tem esse NIF!\n");
    }
    else if(anterior == NULL){
        ListaClientes->prim = elimina->prox;
        printf("Cliente removido com sucesso!\n");
    }else{
        anterior->prox = elimina->prox;
        printf("Cliente removido com sucesso!\n");
    }
    free(elimina);
}

void mostraEstadoCliente (struct Clientes_helper * ListaCLientes, CLIENTE * temp){
    CLIENTE * aux = ListaCLientes->prim;
    int alugueres= 0, danificadas= 0;
    while (aux != NULL){
        if (aux->nif == temp->nif){
            while (aux->aluga != NULL){
                if (aux->aluga->estado == 0){
                    alugueres++;
                }
                if(aux->aluga->estado == 2){
                    danificadas++;
                }
                aux->aluga = aux->aluga->prox;
            }
        }
    aux->aluga = aux->head;
    aux = aux->prox;
    }
    printf("O Cliente fez %d alugueres ate ao momento!\n", temp->nr_alugueres);
    printf("O Cliente tem em sua posse %d guitarras!\n", alugueres);
    printf("O Cliente fez %d entregas com guitarra estragada!\n", danificadas);
}