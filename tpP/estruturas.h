/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estruturas.h
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 20:01
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 25


#ifdef __cplusplus
extern "C" {
#endif

struct data{
    int dia,mes,ano;
};

struct alugar{
    int id;
    int estado;
    struct data aluguer;
    struct data entrega;
    struct data prevista;           //guardar a data prevista de entrega para alugueres
    struct alugar * prox;
};

typedef struct Guitarras_F{
    int id;
    int preco_dia;
    int valor;
    int estado;
    char nome[MAX];
}GUITARRA;

typedef struct Clientes_F{
    int nif;
    int nr_alugueres;
    int banido;             // 0- nao banido 1-banido
    char nome[MAX];
    struct alugar * head;
    struct alugar * aluga;
    struct Clientes_F * prox;
}CLIENTE;

typedef struct Banido{
    int NIF;
    char nome[MAX];
    char razao [50];
    struct Banido * prox;
}BANIDO;

struct Clientes_helper{
    int tamanho;
    CLIENTE * atual;            //ponteiro para adicionar mais clientes (ultima posicao da lista)
    CLIENTE * prim;             //ponteiro para a primeira posicao da lista
};

struct Guitarras_helper{
    int tamanho;
    GUITARRA * guitarras;       //ponteiro para array
};

struct ClienteBanido_helper{
    int tamanho;
    BANIDO * banido;             //ponteiro para adicionar mais clientes banidos (ultima posicao da lista)
    BANIDO * prim;              //ponteiro para a primeira posicao da lista
};

int quantosDiasTemoMes(int mes);
struct data preencherDataprevista (  struct data  prevista);
void indicaDataDeHoje(struct data * hoje);
int converterDataInteiro(struct data converter);

int contaLinhas(char *nome);
bool iniciaVetorGuitarra(struct Guitarras_helper *ArrayGuitarras);
bool gravarFicheiroGuitarras(struct Guitarras_helper * bm);
bool iniciaVetorCliente(struct Clientes_helper * ListaClientes);
bool gravarFicheiroClientes( struct Clientes_helper * clientes);
bool lerClientebanido(struct ClienteBanido_helper * ArrayBanidos, struct Clientes_helper * ListaClientes);
bool gravarFicheiroClientesBanidos(struct ClienteBanido_helper * ArrayBanido);

CLIENTE * procurarCliente ( struct Clientes_helper * ListaClientes,  int aux_nif);
bool criaLista(struct Clientes_helper * ListaClientes, CLIENTE clientes);
bool AdicionaCliente(struct Clientes_helper * ListaClientes, CLIENTE clientes);
void AdicionaDadosCliente(struct Clientes_helper * ListaClientes);
void listaCliente (CLIENTE * temp);
void listarTodosClientesAtivos(struct Clientes_helper * ListaClientes);
void removerCliente (struct Clientes_helper * ListaClientes);
void mostraEstadoCliente (struct Clientes_helper * ListaCLientes, CLIENTE * temp);

GUITARRA * procurarGuitarraID ( struct Guitarras_helper * procura, int id);
GUITARRA * procurarGuitarraNome(struct Guitarras_helper * procura, char *nome);
void adicionaGuitarras (struct Guitarras_helper * ArrayGuitarras);
void listarGuitarra(GUITARRA * output);
void listarTodasGuitarras(struct Guitarras_helper * in);
void mostraGuitarrasAlugadas (struct Clientes_helper * ListaClientes, GUITARRA * guit );
void listarGuitarrasAlugadas(struct Guitarras_helper * ArrayGuitarras, struct Clientes_helper * ListaClientes);

bool criaAluguer( CLIENTE * cliente , struct alugar al);
bool AdicionaAluguer ( CLIENTE * clientes, struct alugar al);
void mostrarHistoricoGuitarra(struct Clientes_helper * ListaClientes);
void listarTodosAlugueres(struct Clientes_helper * ListaClientes, struct data hoje);
void DadosParaAluguer(struct Clientes_helper * ListaClientes, int nif, struct Guitarras_helper * ArrayGuitarras, int id, struct data hoje);
bool concluirAluguer(int nif, struct Clientes_helper * ListaClientes, struct Guitarras_helper * ArrayGuitarras, struct data hoje, struct ClienteBanido_helper * ArrayBanido);

void indicarClientesBanidos(struct Clientes_helper * ListaClientes, struct ClienteBanido_helper * ArrayBanido);
void listarClientesBanidos(struct ClienteBanido_helper * ArrayBanido);
bool criaListaBanido(struct ClienteBanido_helper * ArrayBanido, BANIDO aux);
bool clienteBanido ( struct ClienteBanido_helper * ArrayBanido, BANIDO aux);

void limparConsola();
int menu();
#ifdef __cplusplus
}
#endif

#endif /* ESTRUTURAS_H */

