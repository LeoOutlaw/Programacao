/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Guitarras.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 21:20
 */

#include "estruturas.h"

GUITARRA * procurarGuitarraID ( struct Guitarras_helper * procura, int id){
    int i;
    for (i =0 ; i<procura->tamanho; i++){
        if (procura->guitarras[i].id == id){
            return &procura->guitarras[i];
        }
    }
    return NULL;
}

GUITARRA * procurarGuitarraNome(struct Guitarras_helper * procura, char *nome) {
    int i;
    for ( i = 0; i < procura->tamanho; i++) {
        if (!strcmp(procura->guitarras[i].nome, nome)) {
            return &procura->guitarras[i];
        }
    }
    return NULL;
}

void adicionaGuitarras (struct Guitarras_helper * ArrayGuitarras){
    int id, flag=0, op, i=1 ;
    char nome[MAX];
    printf("\nIndique quantas guitarras deseja adicionar: ");
    scanf("%d",&op);
    do{
        printf("\n->Informacoes sobre a %d guitarra", i);
        ArrayGuitarras->tamanho++;
        ArrayGuitarras->guitarras = realloc(ArrayGuitarras->guitarras, sizeof (GUITARRA) * ArrayGuitarras->tamanho);
        do{
            printf("\nIndique o ID da guitarra: ");
            scanf("%d", &id);
            if ( procurarGuitarraID(ArrayGuitarras, id) != NULL){
            printf("\n[ERRO] Este ID ja pertence a outra guitarra!\n");
            }else {
                flag=1;
                ArrayGuitarras->guitarras[ArrayGuitarras->tamanho -1].id = id;
            }
        }while (flag == 0);
        do{
            printf("Indique o preco de aluguer ao dia: ");
            scanf("%d", &ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].preco_dia);
            if(ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].preco_dia <= 0){
                printf("[ERRO]Preco de aluguer tem de ser maior que zero!");
            }
        }while(ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].preco_dia <= 0);
        do{
            printf("Indique o valor da guitarra: ");
            scanf("%d", &ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].valor);
            if (ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].preco_dia >= ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].valor){
                printf("[ERRO]Preco da guitarra tem de ser maior que o preco de alugar por dia!\n");
            }
        }while (ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].preco_dia >= ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].valor);
        ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].estado = 0;
        do{
            printf("Indique o nome da guitarra: ");
            scanf("%24s", &nome);
            if(procurarGuitarraNome(ArrayGuitarras, nome) != NULL){
                printf("\n[ERRO]Este nome ja existe!\n");
            }else{
                flag = 0;
                strcpy(ArrayGuitarras->guitarras[ArrayGuitarras->tamanho - 1].nome , nome);
            }
        }while (flag == 1);
        i++;
    }while ( i != op+1 );
}

void listarGuitarra(GUITARRA * output){
    if(output != NULL){
        printf("%d\t%d\t%d\t%d\t%24s\n",output->id, output->preco_dia, output->valor, output->estado, output->nome);
    }else{
        printf("[ERRO]Nao existem guitarras!\n");
    }
}

void listarTodasGuitarras(struct Guitarras_helper * in){
    int i;
    for (i=0; i< in->tamanho; i++){
        listarGuitarra(&in->guitarras[i]);
    }
}

void mostraGuitarrasAlugadas (struct Clientes_helper * ListaClientes, GUITARRA * guit ){
    CLIENTE * aux = ListaClientes->prim;
    while(aux != NULL){
        while (aux->aluga != NULL){
            if (aux->aluga->id == guit->id && aux->aluga->estado == 0){
                printf("%d %10s\t\t%4.d\t %4.d\t%20s\t%d\n ", guit->id, guit->nome,guit->preco_dia
                                                            , guit->valor, aux->nome, aux->nif);
            }
            aux->aluga = aux->aluga->prox;
        }
    aux->aluga = aux->head;
    aux = aux->prox;
    }
}

void listarGuitarrasAlugadas(struct Guitarras_helper * ArrayGuitarras, struct Clientes_helper * ListaClientes){
    int i,flag=0;
    for(i=0; i< ArrayGuitarras->tamanho; i++){
        if(ArrayGuitarras->guitarras[i].estado == 1){
            mostraGuitarrasAlugadas (ListaClientes, &ArrayGuitarras->guitarras[i]);
            flag++;
        }
    }
    if(flag == 0){
        printf("Nao existem guitarras alugadas!\n");
    }
}

