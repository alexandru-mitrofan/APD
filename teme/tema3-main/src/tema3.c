#include "mpi.h"

#include <stdio.h>

#include <stdlib.h>

#define BIGSIZE 100000
#define SMALL 1000

int main(int argc, char * argv[]) {
    int numtasks, rank;
    int topo[4][100] = {0};
    int coord = -1;
    int nrOfSons = -1;
    int i, j;
    int totalWorkeri = 0;
    int v[BIGSIZE] = {0};
    int N;
    int rest;
    int workeriPerCluster[4] = {0};
    MPI_Init( & argc, & argv);
    MPI_Comm_size(MPI_COMM_WORLD, & numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, & rank);

    //citirea din fisier de fiecare coordonator
    if (rank == 0) {
        FILE * fin;
        fin = fopen("cluster0.txt", "r");
        fscanf(fin, "%d", & nrOfSons);
        for (i = 0; i < nrOfSons; i++) {
            int son;
            fscanf(fin, "%d", & son);
            topo[rank][i] = son;
        }

        fclose(fin);
    }

    if (rank == 1) {
        FILE * fin;
        fin = fopen("cluster1.txt", "r");
        fscanf(fin, "%d", & nrOfSons);
        for (i = 0; i < nrOfSons; i++) {
            int son;
            fscanf(fin, "%d", & son);
            topo[rank][i] = son;
        }

        fclose(fin);
    }

    if (rank == 2) {
        FILE * fin;
        fin = fopen("cluster2.txt", "r");
        fscanf(fin, "%d", & nrOfSons);
        for (i = 0; i < nrOfSons; i++) {
            int son;
            fscanf(fin, "%d", & son);
            topo[rank][i] = son;
        }

        fclose(fin);
    }

    if (rank == 3) {
        FILE * fin;
        fin = fopen("cluster3.txt", "r");
        fscanf(fin, "%d", & nrOfSons);
        for (i = 0; i < nrOfSons; i++) {
            int son;
            fscanf(fin, "%d", & son);
            topo[rank][i] = son;
        }

        fclose(fin);
    }
    // se trimite topologia 0-3-2-1-2-3-0
    if (rank == 0) {

        MPI_Send( & topo, 4 * 100, MPI_INT, 3, 0, MPI_COMM_WORLD);
        printf("M(%d,3)\n", rank);
    } else if (rank == 1) {
        int topo_helper[4][100];
        MPI_Recv( & topo_helper, 4 * 100, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < 4; i++) {
            if (i != rank) {
                for (int j = 0; j < 100; j++) {
                    if (topo[i][j] == 0) {
                        topo[i][j] = topo_helper[i][j];
                    }
                    if (topo_helper[i][j] == 0) break;
                }
            }
        }

        //printare pt coordonator 1
        printf("%d -> ", rank);
        for (int i = 0; i < 4; i++) {
            printf("%d:", i);
            for (int j = 0; j < 100; j++) {
                if (topo[i][j] != 0) {
                    if (topo[i][j + 1] != 0) {
                        printf("%d,", topo[i][j]);
                    } else {
                        printf("%d ", topo[i][j]);
                        break;
                    }
                }
            }
        }

        printf("\n");
        MPI_Send( & topo, 4 * 100, MPI_INT, 2, 0, MPI_COMM_WORLD);
        printf("M(%d,2)\n", rank);

    } else if (rank == 2) {
        int topo_helper[4][100];
        MPI_Recv( & topo_helper, 4 * 100, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < 4; i++) {
            if (i != rank) {
                for (int j = 0; j < 100; j++) {
                    if (topo[i][j] == 0) {
                        topo[i][j] = topo_helper[i][j];
                    }
                    if (topo_helper[i][j] == 0) break;
                }
            }
        }
        MPI_Send( & topo, 4 * 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("M(%d,1)\n", rank);
    } else if (rank == 3) {
        int topo_helper[4][100];
        MPI_Recv( & topo_helper, 4 * 100, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < 4; i++) {
            if (i != rank) {
                for (int j = 0; j < 100; j++) {
                    if (topo[i][j] == 0) {
                        topo[i][j] = topo_helper[i][j];
                    }
                    if (topo_helper[i][j] == 0) break;
                }
            }
        }
        MPI_Send( & topo, 4 * 100, MPI_INT, 2, 0, MPI_COMM_WORLD);
        printf("M(%d,2)\n", rank);

    }

    if (rank == 2) {
        int topo_helper[4][100];
        MPI_Recv( & topo_helper, 4 * 100, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < 4; i++) {
            if (i != rank) {
                for (int j = 0; j < 100; j++) {
                    if (topo[i][j] == 0) {
                        topo[i][j] = topo_helper[i][j];
                    }
                    if (topo_helper[i][j] == 0) break;
                }
            }
        }
        //printare pt coordonator 2
        printf("%d -> ", rank);
        for (int i = 0; i < 4; i++) {
            printf("%d:", i);
            for (int j = 0; j < 100; j++) {
                if (topo[i][j] != 0) {
                    if (topo[i][j + 1] != 0) {
                        printf("%d,", topo[i][j]);
                    } else {
                        printf("%d ", topo[i][j]);
                        break;
                    }
                }
            }
        }

        printf("\n");
        MPI_Send( & topo, 4 * 100, MPI_INT, 3, 0, MPI_COMM_WORLD);
        printf("M(%d,3)\n", rank);

    }
    if (rank == 3) {
        int topo_helper[4][100];
        MPI_Recv( & topo_helper, 4 * 100, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < 4; i++) {
            if (i != rank) {
                for (int j = 0; j < 100; j++) {
                    if (topo[i][j] == 0) {
                        topo[i][j] = topo_helper[i][j];
                    }
                    if (topo_helper[i][j] == 0) break;
                }
            }
        }
        //printare pt coordonator 3
        printf("%d -> ", rank);
        for (int i = 0; i < 4; i++) {
            printf("%d:", i);
            for (int j = 0; j < 100; j++) {
                if (topo[i][j] != 0) {
                    if (topo[i][j + 1] != 0) {
                        printf("%d,", topo[i][j]);
                    } else {
                        printf("%d ", topo[i][j]);
                        break;
                    }
                }
            }
        }

        printf("\n");
        MPI_Send( & topo, 4 * 100, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("M(%d,0)\n", rank);

    }
    if (rank == 0) {
        int topo_helper[4][100];
        MPI_Recv( & topo_helper, 4 * 100, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < 4; i++) {
            if (i != rank) {
                for (int j = 0; j < 100; j++) {
                    if (topo[i][j] == 0) {
                        topo[i][j] = topo_helper[i][j];
                    }
                    if (topo_helper[i][j] == 0) break;
                }
            }
        }
        //printare pt coordonator 0
        printf("%d -> ", rank);
        for (int i = 0; i < 4; i++) {
            printf("%d:", i);
            for (int j = 0; j < 100; j++) {
                if (topo[i][j] != 0) {
                    if (topo[i][j + 1] != 0) {
                        printf("%d,", topo[i][j]);
                    } else {
                        printf("%d ", topo[i][j]);
                        break;
                    }
                }
            }
        }

        printf("\n");

    }

    if (rank < 4) {

        // trimit mesaj la workeri sa afle coordonatoruul

        for (i = 0; i < nrOfSons; i++) {
            printf("M(%d,%d)\n", rank, topo[rank][i]);
            MPI_Send( & rank, 1, MPI_INT, topo[rank][i], 0, MPI_COMM_WORLD);
        }

    } else {
        //fiecare worker afla coordonatorul
        if (coord < 0) {
            MPI_Recv( & coord, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    // la workeri le este trimisa topologia finala
    if (rank < 4) {
        for (int i = 0; i < nrOfSons; i++) {
            MPI_Send( & topo, 4 * 100, MPI_INT, topo[rank][i], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, topo[rank][i]);
        }
    } else {

        int new_topo[4][100];
        MPI_Recv( & new_topo, 4 * 100, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 100; j++) {
                topo[i][j] = new_topo[i][j];
            }
        }

        //afisare pt workeri
        printf("%d -> ", rank);
        for (int i = 0; i < 4; i++) {
            printf("%d:", i);
            for (int j = 0; j < 100; j++) {
                if (topo[i][j] != 0) {
                    if (topo[i][j + 1] != 0) {
                        printf("%d,", topo[i][j]);
                    } else {
                        printf("%d ", topo[i][j]);
                        break;
                    }
                }
            }
        }
        printf("\n");
    }

    //aflam nr total de workeri si cati workeri are fiecare cluster

    for (i = 0; i < 4; i++) {
        j = 0;
        while (topo[i][j] != 0) {
            j++;
        }
        workeriPerCluster[i] = j;
        totalWorkeri += j;
    }
    // aici se trimite N

    if (rank == 0) {
        N = atoi(argv[1]);

        MPI_Send( & N, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv( & N, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    } else if (rank == 2) {
        MPI_Recv( & N, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send( & N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 3) {
        MPI_Recv( & N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send( & N, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        for (int i = 0; i < N; i++) v[i] = N - i - 1;
        MPI_Send( & v, BIGSIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv( & v, BIGSIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 2) {
        MPI_Recv( & v, BIGSIZE, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send( & v, BIGSIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 3) {
        MPI_Recv( & v, BIGSIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send( & v, BIGSIZE, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }

    //trimit la toti workerii bucata pe care trebuie sa o prelucreze
    if (rank == 0) {

        int distrib;
        distrib = N / totalWorkeri;
        for (int i = 0; i < workeriPerCluster[0]; i++) {

            int aux_vec[SMALL] = {
                0
            };
            for (int j = 0; j < distrib; j++) {
                aux_vec[j] = v[i * distrib + j];
            }

            MPI_Send( & aux_vec, SMALL, MPI_INT, topo[rank][i], 0, MPI_COMM_WORLD);
        }
    } else if (rank == 1) {
        int distrib;
        distrib = N / totalWorkeri;
        for (int i = 0; i < workeriPerCluster[1]; i++) {

            int aux_vec[SMALL] = {0};
            for (int j = 0; j < distrib; j++) {
                aux_vec[j] = v[i * distrib + j + workeriPerCluster[0] * distrib];
                printf(" %d ", aux_vec[j]);
            }
            MPI_Send( & aux_vec, SMALL, MPI_INT, topo[rank][i], 0, MPI_COMM_WORLD);
        }

    } else if (rank == 2) {
        int distrib;
        distrib = N / totalWorkeri;
        for (int i = 0; i < workeriPerCluster[2]; i++) {

            int aux_vec[SMALL] = {0};
            for (int j = 0; j < distrib; j++) {
                aux_vec[j] = v[i * distrib + j + (workeriPerCluster[0] + workeriPerCluster[1]) * distrib];
            }

            MPI_Send( & aux_vec, SMALL, MPI_INT, topo[rank][i], 0, MPI_COMM_WORLD);
        }

    } else if (rank == 3) {
        int distrib;
        distrib = N / totalWorkeri;
        rest = N % totalWorkeri;
        for (int i = 0; i < workeriPerCluster[3]; i++) {

            int aux_vec[SMALL] = {0};
            if (i == workeriPerCluster[3] - 1 && rest > 0) {
                for (int j = 0; j < distrib + rest; j++) {
                    aux_vec[j] = v[i * distrib + j + (workeriPerCluster[0] + workeriPerCluster[1] + workeriPerCluster[2]) * distrib];
                }
            } else {
                for (int j = 0; j < distrib; j++) {
                    aux_vec[j] = v[i * distrib + j + (workeriPerCluster[0] + workeriPerCluster[1] + workeriPerCluster[2]) * distrib];
                }
            }

            MPI_Send( & aux_vec, SMALL, MPI_INT, topo[rank][i], 0, MPI_COMM_WORLD);
        }
    }

    //workerii primesc secventa si o inmltesc cu 5
    if (rank > 3) {

        int vec[SMALL];
        MPI_Recv( & vec, SMALL, MPI_INT, coord, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < SMALL; i++) {
            if (vec[i] == 0) break;
            vec[i] *= 5;
        }
        MPI_Send( & vec, SMALL, MPI_INT, coord, 0, MPI_COMM_WORLD);

    }

    //pana aici e bine

    //coordonatorii iau vectorii inmultiti cu 5 de workeri
    if (rank < 4) {
        int new_v[BIGSIZE] = {
            0
        }, k = 0;

        for (int i = 0; i < workeriPerCluster[rank]; i++) {
            int v_recv[SMALL];
            MPI_Recv( & v_recv, SMALL, MPI_INT, topo[rank][i], 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < SMALL; j++) {

                if (v_recv[j] != 0) {
                    new_v[k] = v_recv[j];
                    k++;
                }
                if (j != 0 && v_recv[j] == 0) break;
            }
        }
        //aici trimitem sirul prelucrat de workeri,acum in posesia coordonatorilor de la 1-2-3-0
        if (rank == 1) {
            MPI_Send( & new_v, BIGSIZE, MPI_INT, 2, 0, MPI_COMM_WORLD);

        } else if (rank == 2) {
            int new_v1[BIGSIZE] = {0};
            int distrib;
            distrib = N / totalWorkeri;
            int good_out[BIGSIZE] = {0};
            MPI_Recv( & new_v1, BIGSIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int pctIncepere1 = workeriPerCluster[0] * distrib;
            int pctIncepere2 = (workeriPerCluster[0] + workeriPerCluster[1]) * distrib;
            int pctTerminare2 = (workeriPerCluster[0] + workeriPerCluster[1] + workeriPerCluster[2]) * distrib;
            int j = 0;
            for (i = pctIncepere1; i < pctIncepere2; i++) {
                good_out[i] = new_v1[j];
                j++;
            }
            j = 0;
            for (i = pctIncepere2; i < pctTerminare2; i++) {
                good_out[i] = new_v[j];
                j++;
            }

            MPI_Send( & good_out, BIGSIZE, MPI_INT, 3, 0, MPI_COMM_WORLD);
        } else if (rank == 3) {
            int distrib, rest;
            distrib = N / totalWorkeri;
            rest = N % totalWorkeri;

            int good_out[BIGSIZE];
            MPI_Recv( & good_out, BIGSIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int workeri012 = workeriPerCluster[0] + workeriPerCluster[1] + workeriPerCluster[2];
            int pctIncepere3 = workeri012 * distrib;
            int pctTerminare3 = (workeri012 + workeriPerCluster[3]) * distrib + rest;

            j = 0;
            for (i = pctIncepere3; i < pctTerminare3; i++) {
                good_out[i] = new_v[j];
                j++;
            }

            MPI_Send( & good_out, BIGSIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
        } else if (rank == 0) {
            int new_v12[BIGSIZE] = {0};
            int distrib;
            distrib = N / totalWorkeri;

            int good_out[BIGSIZE];
            MPI_Recv( & good_out, BIGSIZE, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int pctIncepere0 = 0;
            int pctTerminare1 = workeriPerCluster[0] * distrib;

            j = 0;
            for (i = pctIncepere0; i < pctTerminare1; i++) {
                good_out[i] = new_v[j];
                j++;
            }
            //am asamblat tot vectorul acum il afisam
            printf("Rezultat: ");
            for (i = 0; i < N; i++) {
                printf("%d ", good_out[i]);
            }
            printf("\n");

        }
    }

    MPI_Finalize();

}