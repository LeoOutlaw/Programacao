/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   interface.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 21:14
 */

#include "estruturas.h"

void limparConsola(){
    int i;
    for (i=0;i<45; i++){
        printf("\n");
    }
}

int menu(){
    int op;
    do{
        limparConsola();
        printf("->Menu Guitarras\n");
        printf("        (1)Adicionar guitarra a stock\n");
        printf("        (2)Mostrar historico de alugueres de uma guitarra\n");
        printf("        (3)Listar todas as guitarras\n");
        printf("        (4)Listar guitarras alugadas\n");
        printf("->Menu Clientes\n");
        printf("        (5)Adicionar um novo cliente\n");
        printf("        (6)Remover cliente\n");
        printf("        (7)Mostrar estado do cliente\n");
        printf("        (8)Listar todos os clientes ativos\n");
        printf("        (9)Listar clientes banidos\n");
        printf("->Menu Alugueres\n");
        printf("        (10)Criar aluguer\n");
        printf("        (11)Concluir aluguer\n");
        printf("        (12)Lista de alugueres\n");
        printf("->(0)Sair\n");
        printf("--->Selecione opcao: ");
        scanf("%d", &op);
    }while(op < 0 || op > 13);
    return op;
}
