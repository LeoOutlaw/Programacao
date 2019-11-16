/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 18:56
 */

#include "estruturas.h"


int main(int argc, char** argv) {
    int op, i, count=0;
    bool flag = true;
    struct Guitarras_helper ArrayGuitarras;         //Array das guitarras  
    struct Clientes_helper ListaClientes;           //Lista dos clientes
    struct ClienteBanido_helper ArrayBanido;        //Lista dos clientes banidos
    struct data hoje;                               //estrutura para data de hoje
    CLIENTE * temp;                                 //estrutura auxilar
    int aux_nif, aux;
    ArrayBanido.prim = ArrayBanido.banido = NULL;
    ArrayBanido.tamanho = 0;
    ListaClientes.tamanho = 0;
    ListaClientes.prim = ListaClientes.atual = NULL;
    if (iniciaVetorGuitarra(&ArrayGuitarras)){          // Le ficheiro guitarras
        if (!iniciaVetorCliente(&ListaClientes)){              // Le ficheiro clientes
            printf("[ERRO] Lista clientes nao foi carregada.\n");
            system("pause");
        }
        if(!lerClientebanido(&ArrayBanido, &ListaClientes)){    //Le ficheiro clientes banidos
            printf("[ERRO] Lista clientes banidos nao foi carregada.\n");
            system("pause");
        }
            indicarClientesBanidos(&ListaClientes, &ArrayBanido);       // Ver da lista de clientes quais estao banidos
           // printf("Indicar a data de hoje:\n");
           // indicaDataDeHoje(&hoje);
            CLIENTE * p = ListaClientes.prim;
           int total = conta_val(p);
           printf("%d\n", total);
           system("pause");
            do{
                op = menu();
                limparConsola();
                switch(op){
                    case 1:
                        printf("<------Adicionar Guitarra a Stock------>");
                        adicionaGuitarras(&ArrayGuitarras);
                        printf("Guitarra registada no stock com sucesso!\n");
                        system("pause");
                        break;
                    case 2:
                        printf("<------Mostrar historico de alugueres de uma guitarra------>\n");
                        printf("N - ID  Nome guitarra\n");
                        for ( i = 0; i < ArrayGuitarras.tamanho ; i++) {
                            printf("%d - %d %s\n", i + 1,ArrayGuitarras.guitarras[i].id, ArrayGuitarras.guitarras[i].nome);
                        }
                        mostrarHistoricoGuitarra(&ListaClientes);
                        system("pause");
                        break;
                    case 3:
                        printf("<------Listar todas as guitarras------>\n");
                        listarTodasGuitarras(&ArrayGuitarras);
                        printf("Lista das guitarras apresentada com sucesso!\n");
                        system("pause");
                        break;
                    case 4:
                        printf("<------Listar Todas as guitarras alugadas------>\n");
                        listarGuitarrasAlugadas(&ArrayGuitarras, &ListaClientes);
                        printf("Lista das guitarras alugadas apresentada com sucesso!\n");
                        system("pause");
                        break;
                    case 5:
                        printf("<------Adicionar Cliente------>\n");
                        AdicionaDadosCliente(&ListaClientes);
                        printf("Cliente adicionado com sucesso!\n");
                        system("pause");
                        break;
                    case 6:
                        printf("<------Remover Cliente------>\n");
                        removerCliente(&ListaClientes);
                        system("pause");
                        break;
                    case 7:
                        printf("<------Mostrar Estado do cliente------>\n");
                        printf("Indique o NIF do cliente que pretende mostrar!\n->");
                        scanf("%d", &aux_nif);
                        temp = procurarCliente(&ListaClientes, aux_nif);
                        if(temp != NULL){
                            mostraEstadoCliente(&ListaClientes, temp);
                        }else{
                            printf("Nenhum cliente tem esse NIF!\n");
                        }
                        system("pause");
                        break;
                    case 8:
                        printf("<------Listar Todos os Clientes Ativos------>\n");
                        listarTodosClientesAtivos(&ListaClientes);
                        printf("Lista de Clientes activos apresentada com sucesso!\n");
                        system("pause");
                        break;
                    case 9:
                        printf("<------Listar Clientes Banidos------->\n");
                        listarClientesBanidos(&ArrayBanido);
                        printf("Lista de Clientes banidos apresentada com sucesso!\n");
                        system("pause");
                        break;
                    case 10:
                        printf("<------Criar Aluguer------>\n");
                        printf("Indique o NIF do cliente que pretende alugar!\n->");
                        scanf("%d", &aux_nif);
                        temp = procurarCliente(&ListaClientes, aux_nif);
                        if(temp  != NULL){
                            printf("\t%s\n", temp->nome);
                            printf("Qual a guitarra que deseja alugar?\n");
                            for ( i = 0; i < ArrayGuitarras.tamanho ; i++) {
                               if (ArrayGuitarras.guitarras[i].estado == 0){
                                    printf(" %d - %s\n",ArrayGuitarras.guitarras[i].id, ArrayGuitarras.guitarras[i].nome);
                                    count++;
                                }
                            }
                            if (count == 0){
                                printf("Nao se encontram guitarras disponiveis para aluguer!\n");
                            }else{
                                do{
                                    flag = true;
                                    printf("->");
                                    scanf("%d", &aux);
                                    GUITARRA * emp = procurarGuitarraID(&ArrayGuitarras, aux);
                                    if (emp == NULL){
                                        printf("ID nao existe!\n");
                                        flag = false;
                                    }else{
                                        if(emp->estado != 0){
                                            printf("Esta guitarra nao se encontra disponivel!\n");
                                            flag = false;
                                        }
                                    }
                                }while(flag == false);
                            DadosParaAluguer(&ListaClientes, aux_nif , &ArrayGuitarras, aux, hoje);
                            }
                        }else {
                            printf("[ERRO] Cliente nao existe!\n");
                        }
                        system("pause");
                        break;
                    case 11:
                        printf("<------Concluir Aluguer------>\n");
                        printf("Indique o NIF do cliente que pretende concluir aluguer!\n->");
                        scanf("%d", &aux_nif);
                        temp = procurarCliente(&ListaClientes, aux_nif);
                        if(temp  != NULL){
                            if(!concluirAluguer(aux_nif, &ListaClientes, &ArrayGuitarras, hoje, &ArrayBanido)){
                                printf("Aluguer nao foi concluido!\n");
                            }else{
                                printf("Concluiu o aluguer com sucesso!\n");
                            }
                        }else {
                            printf("[ERRO] Cliente nao existe!\n");
                        }
                        system("pause");
                        break;
                    case 12:
                        printf("<------Listar Todos os alugueres------>\n");
                        listarTodosAlugueres(&ListaClientes, hoje);
                        printf("Lista de Alugueres apresentada com sucesso!\n");
                        system("pause");
                        break;
                }
            }while(op > 0 && op < 13);
            if(!gravarFicheiroClientesBanidos(&ArrayBanido)){
                printf("[ERRO] Array clientes banidos nao foi guardado.\n");
                system("pause");
            }
            if (!gravarFicheiroClientes(&ListaClientes)){
               printf("[ERRO] Lista de clientes nao foi guardado.\n");
              system("pause");
           }
            if (!gravarFicheiroGuitarras(&ArrayGuitarras)) {
                printf("[ERRO] Array guitarras nao foi guardado.\n");
                system("pause");
            }
        }else {
            system("pause");
        }
return 0;
}
