/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   file_funcoes.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 21:16
 */

#include "estruturas.h"

int contaLinhas(char *nome) {
    FILE *f = fopen(nome, "r");
    int ch = 0, linhas = 0;
    if (f != NULL) {
        linhas++;
        while ((ch = fgetc(f)) != EOF) {
            if (ch == '\n')
                linhas++;
        }
        fclose(f);
        return linhas;
    } else {
        return 0;
    }
}

bool iniciaVetorGuitarra(struct Guitarras_helper *ArrayGuitarras){
    FILE *f = fopen("guitarras.txt", "r");
    int nr_linhas, i;

    if (f != NULL){

        nr_linhas = contaLinhas("guitarras.txt");
        if(nr_linhas > 0){
            ArrayGuitarras->guitarras = malloc(sizeof (GUITARRA) * nr_linhas);
            ArrayGuitarras->tamanho = nr_linhas;
            for (i=0; i<nr_linhas; i++){
                fscanf(f, "%d %d %d %d %[^\n]", &ArrayGuitarras->guitarras[i].id, &ArrayGuitarras->guitarras[i].preco_dia, &ArrayGuitarras->guitarras[i].valor, &ArrayGuitarras->guitarras[i].estado, &ArrayGuitarras->guitarras[i].nome);
            }
        }else{
            printf("[ERRO] Ficheiro guitarras nao contem informacao!\n");
        }
        fclose(f);
        return true;
    }else{
        printf("[ERRO] Ficheiro guitarras nao existe, logo o programa nao pode correr!\n");
        return false;
    }
}

bool gravarFicheiroGuitarras(struct Guitarras_helper * bm) {
    FILE *f = fopen("guitarras.txt", "w");
    int i;
    if (f != NULL) {
        for ( i = 0; i < bm->tamanho; i++) {
            fprintf(f, "%d %d %d %d %24s", bm->guitarras[i].id, bm->guitarras[i].preco_dia, bm->guitarras[i].valor, bm->guitarras[i].estado, bm->guitarras[i].nome);
            if (i != bm->tamanho - 1) {
                fprintf(f, "\n");
            }
        }
        fclose(f);
        return true;
    } else {
        return false;
    }
}

bool iniciaVetorCliente(struct Clientes_helper * ListaClientes){
    FILE * f = fopen("clientes.txt", "r");
    int i= 0,j , nr_al, linhas;
    CLIENTE aux;
    struct alugar aux2;
    char ch[2];
    char ch1;
    if(f != NULL){
        linhas = contaLinhas("clientes.txt");
        for(i =1; i < linhas; i++){
            fscanf(f, "%d %d", &aux.nif, &aux.nr_alugueres);
            fscanf(f, "%[^\n]", aux.nome);
            AdicionaCliente(ListaClientes, aux);
            nr_al = aux.nr_alugueres;
            if (nr_al != 0){
                if( nr_al > 0){
                    for (j = 0; j < nr_al; j++ ){
                        fscanf(f, "%d %d %d %d %d", &aux2.id, &aux2.estado
                                                            ,&aux2.aluguer.dia, &aux2.aluguer.mes
                                                            ,&aux2.aluguer.ano);
                        if ((ch1 = fgetc(f)) != '\n'){
                            fscanf(f, " %d %d %d", &aux2.entrega.dia, &aux2.entrega.mes, &aux2.entrega.ano);
                        }else {
                            aux2.entrega.dia = 00;
                            aux2.entrega.mes = 00;
                            aux2.entrega.ano = 00;
                        }
                        if ( feof(f)!= 0){
                            aux2.entrega.dia = 00;
                            aux2.entrega.mes = 00;
                            aux2.entrega.ano = 00;
                        }
                        aux2.prevista = preencherDataprevista(aux2.aluguer);
                        AdicionaAluguer(ListaClientes->atual, aux2);
                    }
                    i= i+nr_al+1;
                }else {
                    printf("ERRO Ficheiro de texto mal preenchido!");
                    return false;
                }
            }else {
                fscanf(f, "%[^\n]", ch);
                i+1;
            }
        }

        fclose(f);
        return true;
    }else{
        printf("[ERRO] Nao foi possivel abrir o ficheiro clientes.txt.\n");
        fclose(f);
        return false;
    }
}

bool gravarFicheiroClientes( struct Clientes_helper * clientes){
    FILE * f = fopen("clientes.txt", "w");
    int i;
    CLIENTE * aux;
    if (f != NULL){
        aux = clientes->prim;
        system("pause");
        while(aux != NULL){
            aux->aluga = aux->head;
            fprintf(f, "%d %d %s", aux->nif, aux->nr_alugueres, aux->nome);
            if(aux->aluga != NULL || aux->prox != NULL){
                    fprintf(f,"\n");
            }
            while (aux->aluga != NULL){
                fprintf(f, "%d %d %d %d %d", aux->aluga->id, aux->aluga->estado
                                                            , aux->aluga->aluguer.dia, aux->aluga->aluguer.mes, aux->aluga->aluguer.ano);
                if(aux->aluga->estado != 0){
                    fprintf(f,"\t%2.d %2.d %2.d", aux->aluga->entrega.dia, aux->aluga->entrega.mes, aux->aluga->entrega.ano);
                }else{
                    if(aux->aluga->prox != NULL){
                        fprintf(f,"\n");
                    }
                }
                if(aux->aluga->prox != NULL){
                    fprintf(f,"\n");
                }
                aux->aluga = aux->aluga->prox;
                }
            if(aux->prox != NULL){
                fprintf(f,"\n");
                if(aux->nr_alugueres != 0){
                    fprintf(f,"\n");
                }
            }
            aux = aux->prox;
            }
        fclose(f);
        return true;
    }else{
        fclose(f);
        return false;
    }

}

bool lerClientebanido(struct ClienteBanido_helper * ArrayBanidos, struct Clientes_helper * ListaClientes){
    FILE *f = fopen("banido.bin", "rb");
    if (f != NULL) {
        int quantos=0, aux_nif, i;
        CLIENTE * temp;
        BANIDO aux;
        fread(&quantos, sizeof (int), 1, f);
        for ( i = 0; i < quantos; i++) {
            fread(&aux.NIF, sizeof (int), 1, f);
            fread(&aux.nome, sizeof (char), MAX, f);
            fread(&aux.razao, sizeof(char), 50,f);
            temp = procurarCliente(ListaClientes, aux.NIF);
            if (temp == NULL) {
                printf("[ERRO] Cliente %s, nao encontrado.\n", aux.nome);
            } else {
                if(!clienteBanido(ArrayBanidos, aux)){
                    printf("ERRO a banir cliente!\n");
                }
            }
        }
        fclose(f);
        return true;
    } else {
        printf("[ERRO] Nao foi possivel abrir o ficheiro %s.\n", "banido.bin");
        return false;
    }
}

bool gravarFicheiroClientesBanidos(struct ClienteBanido_helper * ArrayBanido){
    FILE *f;
    int i;
    f = fopen("banido.bin", "wb");
    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return false;
    }
    if (ArrayBanido->tamanho != 0){
        fwrite(&ArrayBanido->tamanho, sizeof(int), 1, f);
     while (ArrayBanido->prim != NULL){
            fwrite(&ArrayBanido->prim->NIF, sizeof(int), 1, f);
            fwrite(&ArrayBanido->prim->nome, sizeof(char), MAX,f);
            fwrite(&ArrayBanido->prim->razao, sizeof(char), 50, f);
            ArrayBanido->prim = ArrayBanido->prim->prox;
        }
    }else {
        printf("[ERRO] Array vazio!\n");
    }
    fclose(f);
    return true;
}
