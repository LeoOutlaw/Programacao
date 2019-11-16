/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Alugueres.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 21:23
 */

#include "estruturas.h"

bool criaAluguer( CLIENTE * cliente , struct alugar al){
    struct alugar * temp = malloc(sizeof (struct alugar));
    if (temp == NULL) {
        printf("[ERRO] Alocacao de memoria.\n");
        return false;
    }
    temp->id= al.id;
    temp->estado = al.estado;
    temp->aluguer= al.aluguer;
    temp->entrega= al.entrega;
    temp->prevista = al.prevista;
    temp->prox = NULL;

    cliente->aluga= cliente->head = temp;

}

bool AdicionaAluguer ( CLIENTE * clientes, struct alugar al){
    if (clientes->head == NULL) {
        return (criaAluguer(clientes, al));
    }else{
        struct alugar * temp = malloc(sizeof (struct alugar));
        if (temp == NULL) {
            printf("[ERRO] Alocacao de memoria.\n");
            return false;
        }
        temp->id= al.id;
        temp->estado = al.estado;
        temp->aluguer= al.aluguer;
        temp->entrega= al.entrega;
        temp->prevista = al.prevista;
        temp->prox = NULL;

        clientes->aluga->prox = temp;
        clientes->aluga = temp;
        return true;
    }
}

void mostrarHistoricoGuitarra(struct Clientes_helper * ListaClientes){
    CLIENTE * aux = ListaClientes->prim;
    int x,count=0;
    printf("Introduza o ID da guitarra!\n->");
    scanf("%d", &x);
    limparConsola();
    printf("ID\tData de aluguer\tData de entrega\n");
    while(aux != NULL){
        aux->aluga = aux->head;
        while (aux->aluga != NULL){
            if (aux->aluga->id == x){
                printf("%d\t%d %d %d\t%2.d %2.d %4.d\n", aux->aluga->id, aux->aluga->aluguer.dia, aux->aluga->aluguer.mes, aux->aluga->aluguer.ano, aux->aluga->entrega.dia, aux->aluga->entrega.mes, aux->aluga->entrega.ano);
                count++;
            }
            aux->aluga = aux->aluga->prox;
        }
    aux = aux->prox;
    }
    if(count == 0){
        printf("Nao foi encontrado nenhum aluguer desta guitarra!\n");
    }

}

void listarTodosAlugueres(struct Clientes_helper * ListaClientes, struct data hoje){
    CLIENTE * aux = ListaClientes->prim;
    int dia_atraso,data_hoje, data_prevista ,i;
    printf("NIF      \tID\tData aluguer    Data prevista\n");
    while(aux != NULL){
        while (aux->aluga != NULL){
            if (aux->aluga->estado == 0){
                if (hoje.ano > aux->aluga->prevista.ano){
                    data_hoje = converterDataInteiro(hoje)+ 365;
                }
                if (hoje.ano == aux->aluga->prevista.ano){
                    data_hoje = converterDataInteiro(hoje);
                }
                if (hoje.ano < aux->aluga->prevista.ano){
                    printf("ERRO Data de hoje foi mal introduzida!\n");
                    break;
                }
                data_prevista = converterDataInteiro(aux->aluga->prevista);
                if(data_prevista - data_hoje >= 0 ){
                    printf("%d\t%d\t%d %d %d\t%2.d %2.d %4.d  \n", aux->nif, aux->aluga->id, aux->aluga->aluguer.dia, aux->aluga->aluguer.mes, aux->aluga->aluguer.ano, aux->aluga->prevista.dia, aux->aluga->prevista.mes, aux->aluga->prevista.ano);
                    printf("Cliente nao se encontra atrasado na entrega!\n");
                }else{
                    dia_atraso = data_hoje - data_prevista ;
                    printf("%d\t%d\t%d %d %d\t%2.d %2.d %4.d  \n", aux->nif, aux->aluga->id, aux->aluga->aluguer.dia, aux->aluga->aluguer.mes, aux->aluga->aluguer.ano, aux->aluga->prevista.dia, aux->aluga->prevista.mes, aux->aluga->prevista.ano);
                    printf("Cliente encontra se %d dias atrasado na entrega!\n", dia_atraso);
                }
            }
            aux->aluga = aux->aluga->prox;
        }
    aux->aluga = aux->head;
    aux = aux->prox;
    }
}

void DadosParaAluguer(struct Clientes_helper * ListaClientes, int nif, struct Guitarras_helper * ArrayGuitarras, int id, struct data hoje){
    CLIENTE *temp = ListaClientes->prim;
    struct alugar al;
    bool flag = false;
    GUITARRA * guitarra = procurarGuitarraID(ArrayGuitarras, id);
    while(temp != NULL){
        if(temp->nif == nif){
            if(guitarra != NULL){
                temp->nr_alugueres = temp->nr_alugueres+1;
                al.id = id;
                al.estado = 0;
                al.aluguer = hoje;
                al.entrega.dia = 0;
                al.entrega.mes = 0;
                al.entrega.ano = 0;
                al.prevista = preencherDataprevista(hoje);
                if(AdicionaAluguer(temp, al) == flag){
                    printf("ERRO aluguer nao adicionado!\n");
                }else{
                     printf("\nO cliente tera de entregar ate %d/%d/%d e pagamento previsto de %d euros\n", al.prevista.dia, al.prevista.mes, al.prevista.ano, guitarra->preco_dia * 7);
                }
                guitarra->estado = 1;
            }else{
                printf("ID da guitarra nao existe!\n");
            }
        }
    temp = temp->prox;
    }
}

bool concluirAluguer(int nif, struct Clientes_helper * ListaClientes, struct Guitarras_helper * ArrayGuitarras, struct data hoje, struct ClienteBanido_helper * ArrayBanido){
    CLIENTE * aux = ListaClientes->prim;
    int flag, estado, data_hoje, dia_atraso, data_prevista, dia_sematraso , dia_aluguer , count=0;
    while (aux != NULL){
        while (aux->aluga != NULL){
            if(aux->nif == nif){
                if (aux->aluga->estado == 0){
                    GUITARRA * guitarras = procurarGuitarraID(ArrayGuitarras,aux->aluga->id);
                    printf("%s\t\t Guitarra alugada ID: %d\n" , aux->nome, aux->aluga->id);
                    printf("Deseja concluir o aluguer?(1-sim/2-nao)\n");
                    do{
                        printf("->");
                        scanf("%d", &flag);
                    }while ( flag != 1 && flag != 2);
                    if (flag == 1){
                        aux->aluga->estado = 1;
                        aux->aluga->entrega.dia = hoje.dia;
                        aux->aluga->entrega.mes = hoje.mes;
                        aux->aluga->entrega.ano = hoje.ano;
                        printf("Estado da guitarra(1-Bom estado/2-Estragada):");
                        do{
                            printf("\n->");
                            scanf("%d", &estado);
                        }while(estado != 1 && estado != 2);
                        if (estado == 1){
                            if (hoje.ano > aux->aluga->prevista.ano){
                                data_hoje = converterDataInteiro(hoje)+ 365;
                            }
                            if (hoje.ano == aux->aluga->prevista.ano){
                                data_hoje = converterDataInteiro(hoje);
                            }
                            if (hoje.ano < aux->aluga->prevista.ano){
                                printf("ERRO Data de hoje foi mal introduzida!\n");
                                break;
                            }
                            data_prevista = converterDataInteiro(aux->aluga->prevista);
                            if(data_prevista - data_hoje >= 0 ){
                                dia_aluguer = converterDataInteiro(aux->aluga->aluguer);
                                dia_sematraso = dia_aluguer - data_hoje;    // dias que levou ate entregar
                                printf("O cliente tera de pagar %d euros!\n", guitarras->preco_dia*dia_sematraso );
                            }else{
                                dia_aluguer = converterDataInteiro(aux->aluga->aluguer);
                                dia_sematraso =data_hoje -  dia_aluguer;  //dias que levou ate entregar
                                dia_atraso = data_hoje - data_prevista ;       // dias de atraso , para multa
                                printf("O cliente tera de pagar %d euros!\n", (guitarras->preco_dia * dia_aluguer + 10 * dia_atraso) );
                                if (dia_atraso > 20){
                                    BANIDO temp;
                                    strcpy(temp.razao, "Entrega mais de 20 dias atrasada!");
                                    temp.NIF = aux->nif;
                                    strcpy(temp.nome, aux->nome);
                                    clienteBanido(ArrayBanido, temp);
                                    printf("Cliente adicionado a lista de banidos!\n");
                                    aux->banido = 1;
                                }
                            }
                            guitarras->estado = 0;
                            count++;
                        }else {
                            printf("O cliente tera de pagar o custo da guitarra!\n");
                            printf("O cliente tera de pagar %d euros\n", guitarras->valor);
                            guitarras->estado =2;
                            aux->aluga->estado = 2;
                            BANIDO temp;
                            strcpy(temp.razao, "Entrega da guitarra estragada!");
                            temp.NIF = aux->nif;
                            strcpy(temp.nome, aux->nome);
                            clienteBanido(ArrayBanido, temp);
                            printf("Cliente adicionado a lista de banidos!\n");
                            aux->banido = 1;
                            count++;
                        }
                    }else{
                        printf("Cancelou a operacao!\n");
                    }
                }
            }
            aux->aluga = aux->aluga->prox;
        }
    aux->aluga = aux->head;
    aux = aux->prox;
    }
    if (count > 0){
        return true;
    }else{
        return false;
    }
    
}

