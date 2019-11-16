/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   datas.c
 * Author: Leonardo
 *
 * Created on 16 de Junho de 2018, 20:05
 */

#include "estruturas.h"

int quantosDiasTemoMes(int mes){
    if(mes ==1 || mes ==3 || mes ==5 || mes ==7 || mes ==8 || mes ==10 || mes ==12){
        return 31;
    }
    if(mes == 4 || mes == 6 || mes == 9 || mes ==11){
        return 30;
    }
    if(mes == 2){
        return 28;
    }
}

struct data preencherDataprevista (  struct data  prevista){
    if (prevista.mes ==1 || prevista.mes ==3 || prevista.mes ==5 || prevista.mes ==7 || prevista.mes ==8 || prevista.mes ==10 || prevista.mes ==12 ){
        if(prevista.dia +7 > 31 ){
            prevista.dia=prevista.dia + 7;
            prevista.dia = prevista.dia - 31;
            if(prevista.mes == 12){
                prevista.mes = 1;
                prevista.ano = prevista.ano +1;
            }else{
                prevista.mes = prevista.mes +1;
            }
        }else{
            prevista.dia=prevista.dia + 7;
        }
    }
    if (prevista.mes == 4 || prevista.mes == 6 || prevista.mes == 9 || prevista.mes ==11){
         if(prevista.dia +7 > 30 ){
            prevista.dia +7;
            prevista.dia = prevista.dia - 30;
            prevista.mes = prevista.mes +1;
        }else{
            prevista.dia=prevista.dia + 7;
        }
    }
    if (prevista.mes == 2){
        if(prevista.dia + 7 > 28){
            prevista.dia=prevista.dia + 7;
            prevista.dia = prevista.dia - 28;
            prevista.mes = prevista.mes + 1;
        }else{
            prevista.dia=prevista.dia + 7;
        }
    }
    return prevista;
}

void indicaDataDeHoje(struct data * hoje){
    int flag;
    do{
        printf("Ano:->");
        scanf("%d", &hoje->ano);
        if (hoje->ano < 2000 || hoje->ano > 3000){
            printf("Ano nao aceite!\n");
        }
    }while (hoje->ano < 2000 || hoje->ano > 3000);
    do{
        printf("Mes:->");
        scanf("%d", &hoje->mes);
        if (hoje->mes < 1 || hoje->mes > 12){
            printf("Mes nao aceite(ano tem 12 meses)!\n");
        }
    }while (hoje->mes < 1 || hoje->mes > 12);
    do{
        flag = 0;
        printf("Dia:->");
        scanf("%d", &hoje->dia);
        if (hoje->mes == 1 || hoje->mes == 3 || hoje->mes == 5 || hoje->mes == 7 || hoje->mes == 8 || hoje->mes == 10 || hoje->mes == 12 ){
            if (hoje->dia < 1 || hoje->dia > 31){
                printf("Dia nao aceite(mes tem 31 dias)");
                flag = 1;
            }
        }
        if(hoje->mes == 4 || hoje->mes == 6 || hoje->mes == 9 || hoje->mes == 10){
            if (hoje->dia < 1 || hoje->dia >30){
                printf("Dia nao aceite(mes tem 30 dias)");
                flag = 1;
            }
        }
        if(hoje->mes == 2){
            if (hoje->dia < 1 || hoje->dia >28){
                printf("Dia nao aceite(mes tem 28 dias)");
                flag = 1;
            }
        }
    }while (flag == 1);
}

int converterDataInteiro(struct data converter){        //converter data em inteiro para cancular dias de atraso
    int inteiro = 0;
    int i;
    i = converter.mes- 1;
    while(i != 0){
        inteiro = inteiro + quantosDiasTemoMes (i);
        i--;
    }
    inteiro = inteiro + converter.dia;
    return inteiro;
}


