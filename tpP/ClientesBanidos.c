/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientesBanidos.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 21:25
 */

#include "estruturas.h"

void indicarClientesBanidos(struct Clientes_helper * ListaClientes, struct ClienteBanido_helper * ArrayBanido){
    CLIENTE * aux = ListaClientes->prim;
    BANIDO * temp= ArrayBanido->prim;
    while (temp != NULL){
        while(aux != NULL){
            if(temp->NIF == aux->nif){
                aux->banido =1;
            }
            aux = aux->prox;
        }
        temp = temp->prox;
    }
}

void listarClientesBanidos(struct ClienteBanido_helper * ArrayBanido){
    BANIDO * temp = ArrayBanido->prim;
    if(temp == NULL){
        printf("Nao existem clientes banidos!\n");
    }
    while (temp != NULL){
        printf("%20s\t%d\t%s\n", temp->nome,temp->NIF, temp->razao);
        temp = temp->prox;
    }
}

bool criaListaBanido(struct ClienteBanido_helper * ArrayBanido, BANIDO aux){
    BANIDO * temp = malloc(sizeof (BANIDO));
    if (temp == NULL) {
        printf("[ERRO] Alocacao de memoria.\n");
        return false;
    }
    strcpy(temp->nome, aux.nome);
    temp->NIF = aux.NIF;
    strcpy(temp->razao, aux.razao);
    temp->prox = NULL;

    ArrayBanido->tamanho++;
    ArrayBanido->prim = ArrayBanido->banido = temp;
    return true;
}

bool clienteBanido ( struct ClienteBanido_helper * ArrayBanido, BANIDO aux){
    if (ArrayBanido->prim == NULL) {
        return (criaListaBanido(ArrayBanido, aux));
    } else {
        BANIDO * temp = malloc(sizeof (BANIDO));
        if (temp == NULL) { 
            printf("[ERRO] Alocacao de memoria.\n");
            return false;
        }
        strcpy(temp->nome, aux.nome);
        temp->NIF = aux.NIF;
        strcpy(temp->razao, aux.razao);
        temp->prox = NULL;

        ArrayBanido->tamanho++;
        ArrayBanido->banido->prox = temp;
        ArrayBanido->banido = temp;

        return true;
    }

}