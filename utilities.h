/* 
 * -------------------------------------------------
 * ~ ARQUIVO DE CABEÇALHO DE UTILITÁRIOS
 * -------------------------------------------------
 * 
 *  Descrição: Arquivo de cabeçalho contendo funções auxiliares.
 *  Arquivo: utilities.h criado em 5 de Novembro de 2015, às 12:03.
 *  Professor: Luiz Fernando Bessa Seibel
 *  Instituição: Pontifícia Universidade Católica do Rio de Janeiro
 *  Disciplina: Sistemas de Computação (INF1019)
 *  Autoras: 
 * - - - - - - - - - - - - - - - - - - - - - - - - -
 *  -> Daniela Brazão Maksoud
 *  -> Curso: Ciência da Computação
 *  -> Matrícula: 1321873
 * - - - - - - - - - - - - - - - - - - - - - - - - -
 *  -> Thaíssa Falbo
 *  -> Curso: Engenharia da Computação
 *  -> Matrícula: 1421110
 * - - - - - - - - - - - - - - - - - - - - - - - - -
 * 
 *  Este arquivo é parte do programa principal do Simulador de Gerenciador 
 *  de Memória.
 *
 *  O Simulador de Gerenciador de Memória é um software livre; você 
 *  pode redistribuí-lo e/ou modificá-lo dentro dos termos da Licença 
 *  Pública Geral GNU como publicada pela Fundação do Software Livre 
 *  (FSF); na versão 3 da Licença.
 *
 *  Este programa é distribuído na esperança de que possa ser útil, 
 *  mas SEM NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO
 *  a qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
 *  Licença Pública Geral GNU para maiores detalhes.
 *
 *  Você deve ter recebido uma cópia da Licença Pública Geral GNU junto
 *  com este programa, Se não, veja <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef UTILITIES_H
#define	UTILITIES_H

#include "definitions.h" /* Arquivo de cabeçalho com definições (includes e defines) */

/* Função que exibe mensagem inicial do gerenciador de memória */

void cabecalho() {
    printf("\n-----------------------------------------------------------------------------------\n\n");
    printf("\tPONTIFÍCIA UNIVERSIDADE CATÓLICA DO RIO DE JANEIRO\n");
    printf("\tSegundo Trabalho de Sistemas de Computação\n");
    printf("\tAutores: Daniela Brazão e Thaíssa Falbo\n");
    printf("\tProfessor: Luiz Fernando Bessa Seibel\n");
    printf("\tDisciplina: Sistemas de Computação (INF1019)\n\n");
    printf("-----------------------------------------------------------------------------------\n\n");
    printf("\tSimulador de Gerenciador de Memória\n");
    printf("\tCopyright (C) 2015\n\tDaniela Brazão & Thaíssa Falbo\n\n");
    printf("-----------------------------------------------------------------------------------\n\n");
    printf("\tEste programa é um software livre; você pode redistribuí-lo e/ou \n");
    printf("\tmodificá-lo dentro dos termos da Licença Pública Geral GNU como \n");
    printf("\tpublicada pela Fundação do Software Livre (FSF); na versão 3 da \n");
    printf("\tLicença.\n\n");
    printf("\tEste programa é distribuído na esperança de que possa ser útil, \n");
    printf("\tmas SEM NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO \n");
    printf("\ta qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a Licença \n");
    printf("\tPública Geral GNU para maiores detalhes.\n\n");
    printf("\tVocê deve ter recebido uma cópia da Licença Pública Geral GNU junto \n");
    printf("\tcom este programa. Se não, veja <http://www.gnu.org/licenses/>.\n\n");
    printf("-----------------------------------------------------------------------------------\n\n");
}

/* Função que exibe mensagem de erro */

void showError(char str[TAM_STR + 1], int n) {
    printf("Erro %d: %s\n", n, str);
    exit(n);
}

/* Função que inicializa a memória com partições fixas */

void inicializar_memoria(mem *M) {

    int i;
    int v[5] = {8, 4, 2, 1, 1};

    M->tamanho = TAM_MEM;

    for (i = 0; i < 5; i++) {

        M->bloco[i].isAlocado = 0;
        M->bloco[i].tamanho = v[i];
    }

}

/* Função que aguarda o usuário digitar a tecla Enter para prosseguir */

void espera_enter() {

    int tecla = 0;

    printf("Pressione a tecla Enter para continuar...\n");
    tecla = getchar();

    while (tecla != 10) {
        printf("Pressione a tecla Enter para continuar...\n");
        tecla = getchar();
    }
}

/* Função que executa algoritmo de alocação de ajuste rápido */

void first_fit(processo *proc_v, mem *M, int qtd_proc, int tempo_total) {

    int i, j, k = 0, w, l, d, flag, z, tempo = 0;
    time_t dif = 0; /* Diferença entre os tempos final e inicial da execução do algoritmo */

    printf("-----------------------------------------------------------------------------------\n\n");
    printf("MAPA DE MEMÓRIA:\n\n");
    printf("-----------------------------------------------------------------------------------\n\n");
    sleep(2);

    /* Tempo total de todos os processos dividido pela fatia de tempo */
    if (tempo_total >= qtd_proc) {
        tempo = tempo_total / FATIA_TEMPO;
    }

    printf("Tempo total = %d\n\n", tempo);

    for (z = 0; z < tempo; z++) {
        /* Percorre todos os processos */
        for (i = 0; i < qtd_proc; i++) {
            printf("i = %d\n\n", i);
            flag = 0;

            /* Percorre todas as partições de memória */
            for (j = 0; j < QTD_BLOC; j++) {
                if (M->bloco[j].isAlocado == 0 && M->bloco[j].tamanho >= proc_v[i].tamanho) {

                    flag = 1;
                    M->bloco[j].isAlocado = proc_v[i].numero;

                    printf("-----------------------------------\n");

                    /* Imprime mapa de memória */
                    for (w = 0; w < QTD_BLOC; w++) {
                        printf("- Bloco #%d\n", w + 1);
                        printf("-----------------------------------\n");
                        sleep(2);

                        /* Bloco está alocado para um processo */
                        if (M->bloco[w].isAlocado > 0) {
                            printf("- Número do processo: %d\n", M->bloco[w].isAlocado);
                            fflush(stdout); // Flush do buffer.

                            for (l = 0; l < qtd_proc; l++) {
                                if (M->bloco[w].isAlocado == proc_v[l].numero) {
                                    printf("- Tamanho do processo: %dMb\n", proc_v[l].tamanho);
                                    printf("- Tempo restante do processo: %ds\n", proc_v[l].tempo_total);
                                }
                            }
                            printf("- Tamanho do bloco de memória: %dMb\n", M->bloco[w].tamanho);
                            printf("-----------------------------------\n");
                            sleep(2);
                        } else {
                            printf("- Bloco de memória vazio.\n");
                            printf("- Tamanho do bloco de memória: %dMb\n", M->bloco[w].tamanho);
                            printf("-----------------------------------\n");
                            sleep(2);
                        }
                    }

                    d = 0;

                    /* Percorre as informações sobre o processo */
                    for (k = 0; k < proc_v[i].qtd_info && dif < FATIA_TEMPO; k++) {

                        /* EXEC */
                        if ((strcmp(proc_v[i].infos[k].nome, "exec") == 0) && (dif < 10) && (proc_v[i].infos[k].tempo > 0)) {
                            if (d == 0 && proc_v[i].infos[k].tempo > 0) {
                                printf("\n-----------------------------------\n");
                                printf("PROCESSO #%d - RELÓGIO\n", proc_v[i].numero);
                                printf("-----------------------------------\n");
                                sleep(2);
                                printf("Comando: %s\n\n", proc_v[i].infos[k].nome);
                                sleep(2);
                                d = 1;
                            }
                            
                            time(&proc_v[i].inicio_execucao); /* Armazena o tempo de início da execução do algoritmo */

                            while (proc_v[i].infos[k].tempo > 0 && dif <= FATIA_TEMPO) {
                                sleep(1);
                                printf("Countdown: %ds\n", proc_v[i].infos[k].tempo);
                                proc_v[i].infos[k].tempo--;
                                proc_v[i].tempo_total--;
                                tempo_total--;
                                time(&proc_v[i].fim_execucao); /* Armazena o tempo de fim da execução do algoritmo */
                                dif = proc_v[i].fim_execucao - proc_v[i].inicio_execucao;
                            }
                            sleep(1);
                            printf("Countdown: %ds\n", proc_v[i].infos[k].tempo);
                            printf("-----------------------------------\n\n");

                            /* Imprime o mapa de memória */
                            for (w = 0; w < QTD_BLOC; w++) {
                                printf("-----------------------------------\n");
                                printf("- Bloco #%d\n", w + 1);
                                printf("-----------------------------------\n");
                                sleep(2);

                                /* Bloco está alocado para um processo */
                                if (M->bloco[w].isAlocado > 0) {
                                    printf("- Número do processo: %d\n", M->bloco[w].isAlocado);
                                    for (l = 0; l < qtd_proc; l++) {
                                        if (M->bloco[w].isAlocado == proc_v[l].numero) {
                                            printf("- Tamanho do processo: %dMb\n", proc_v[l].tamanho);
                                            printf("- Tempo restante do processo: %ds\n", proc_v[l].tempo_total);
                                        }
                                    }
                                    printf("- Tamanho do bloco de memória: %dMb\n", M->bloco[w].tamanho);
                                } else {
                                    printf("- Bloco de memória vazio.\n");
                                    fflush(stdout); // Flush do buffer.
                                    printf("- Tamanho do bloco de memória: %dMb\n", M->bloco[w].tamanho);
                                    fflush(stdout); // Flush do buffer.
                                }
                            }

                            printf("-----------------------------------\n\n");
                            sleep(2);

                            /* Libera bloco de memória caso tenha estourado o tempo máximo de execução de um processo ou todos os processos tenham terminado */
                            if ((dif == 10) || (tempo_total == 0)) {
                                M->bloco[j].isAlocado = 0;
                            }


                            /* Imprime o mapa de memória */
                            for (w = 0; w < QTD_BLOC; w++) {
                                printf("-----------------------------------\n");
                                printf("- Bloco #%d\n", w + 1);
                                printf("-----------------------------------\n");
                                sleep(2);

                                /* Bloco está alocado para um processo */
                                if (M->bloco[w].isAlocado > 0) {
                                    printf("- Número do processo: %d\n", M->bloco[w].isAlocado);
                                    for (l = 0; l < qtd_proc; l++) {
                                        if (M->bloco[w].isAlocado == proc_v[l].numero) {
                                            printf("- Tamanho do processo: %dMb\n", proc_v[l].tamanho);
                                            printf("- Tempo restante do processo: %ds\n", proc_v[l].tempo_total);
                                        }
                                    }
                                    printf("- Tamanho do bloco de memória: %dMb\n", M->bloco[w].tamanho);
                                } else {
                                    printf("- Bloco de memória vazio.\n");
                                    printf("- Tamanho do bloco de memória: %dMb\n", M->bloco[w].tamanho);
                                }
                            }

                            printf("-----------------------------------\n");
                            sleep(2);
                        } else {

                            /* IO 
                             * Esvazia o bloco de memória ocupado;
                             * Decrementa o tempo do IO.
                             */

                            M->bloco[j].isAlocado = 0;

                            while (proc_v[i].infos[k].tempo > 0) {
                                sleep(1);
                                proc_v[i].infos[k].tempo--;
                                proc_v[i].tempo_total--;
                                tempo_total--;
                                time(&proc_v[i].fim_execucao);
                                dif = proc_v[i].fim_execucao - proc_v[i].inicio_execucao;
                            }

                        }
                    }
                    printf("\n");
                }
                dif = 0; /* Reinicializa o valor do contador dif */
            }

            if (flag == 0) {
                printf("Bloco de memória compatível com o tamanho de %dMb do processo de número %d inexiste.\n\n", proc_v[i].tamanho, proc_v[i].numero);
            }
        }
    }

    if (tempo_total % 3 > 0) {
        // repete aquilo mais uma vez
    }
}

#endif	/* UTILITIES_H */