#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMICS 100
#define MAX_NAME_LENGTH 100
#define MAX_KOMIKUS_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char komikus[MAX_KOMIKUS_LENGTH];
    int populer; 
    float rating;
    int tahun; 
} Comic;

Comic comics[MAX_COMICS];
int hitung = 0; 

void tambah_komik() {
    Comic komik_baru;
    FILE *file = fopen("komik.txt", "w");
    if (!file) {
        printf("file tidak dapat dibuka untuk membaca.\n");
        return;
    }

    while (fscanf(file, " %[^\n]\n%[^\n]\n%d\n%f\n%d", comics[hitung].name, comics[hitung].komikus, 
                  &comics[hitung].populer, &comics[hitung].rating, &comics[hitung].tahun) == 5) {
        hitung++;
    }
    fclose(file);

    printf("masukkan nama komik: ");
    getchar(); 
    fgets(komik_baru.name, MAX_NAME_LENGTH, stdin);
    komik_baru.name[strcspn(komik_baru.name, "\n")] = '\0';

    printf("masukkan nama komikus: ");
    fgets(komik_baru.komikus, MAX_KOMIKUS_LENGTH, stdin);
    komik_baru.komikus[strcspn(komik_baru.komikus, "\n")] = '\0';

    printf("masukkan popularitas (angka): ");
    while (scanf("%d", &komik_baru.populer) != 1) {
        printf("input invalid! masukkan angka: ");
        while (getchar() != '\n');
    }

    printf("masukkan rating (0-10): ");
    while (scanf("%f", &komik_baru.rating) != 1 || komik_baru.rating < 0 || komik_baru.rating > 10) {
        printf("input invalid! masukkan rating antara 0-10: ");
        while (getchar() != '\n');
    }

    printf("masukkan tahun: ");
    while (scanf("%d", &komik_baru.tahun) != 1) {
        printf("input invalid! masukkan angka: ");
        while (getchar() != '\n');
    }

    comics[hitung] = komik_baru;
    hitung++;

    file = fopen("komik.txt", "w");
    if (!file) {
        printf("file tidak dapat dibuka untuk menulis.\n");
        return;
    }

    for (int i = 0; i < hitung; i++) {
        fprintf(file, "%s\n%s\n%d\n%.2f\n%d\n", comics[i].name, comics[i ].komikus, comics[i].populer, 
                comics[i].rating, comics[i].tahun);
    }

    printf("komik berhasil ditambahkan.\n");
    fclose(file);
}

void tampilkan_komik() {
    hitung = 0;

    FILE *file = fopen("komik.txt", "r");
    if (!file) {
        printf("File tidak dapat dibuka untuk membaca.\n");
        return;
    }

    while (fscanf(file, " %[^\n]\n%[^\n]\n%d\n%f\n%d", comics[hitung].name, comics[hitung].komikus, 
                  &comics[hitung].populer, &comics[hitung].rating, &comics[hitung].tahun) == 5) {
        hitung++;
    }
    fclose(file);

    if (hitung == 0) {
        printf("Tidak ada komik untuk ditampilkan.\n");
        return;
    }

    int pilih;
    printf("\ntampilkan komik berdasarkan:\n");
    printf("1. nama komik\n");
    printf("2. nama komikus\n");
    printf("3. popularitas\n");
    printf("4. rating\n");
    printf("5. tahun\n"); 
    printf("pilih menu: ");
    scanf("%d", &pilih);

    switch (pilih) {
        case 1:
            for (int i = 0; i < hitung - 1; i++) {
                for (int j = i + 1; j < hitung; j++) {
                    if (strcmp(comics[i].name, comics[j].name) > 0) {
                        Comic temp = comics[i];
                        comics[i] = comics[j];
                        comics[j] = temp;
                    }
                }
            }
            printf("\ndaftar komik:\n");
            for (int i = 0; i < hitung; i++) {
                printf("nama: %s | komikus: %s | populer: %d | rating: %.2f | tahun: %d\n", 
                       comics[i].name, comics[i].komikus, comics[i].populer, comics[i].rating, comics[i].tahun);
            }
            break;
        case 2:
            for (int i = 0; i < hitung - 1; i++) {
                for (int j = i + 1; j < hitung; j++) {
                    if (strcmp(comics[i].komikus, comics[j].komikus) > 0) {
                        Comic temp = comics[i];
                        comics[i] = comics[j];
                        comics[j] = temp;
                    }
                }
            }
            printf("\ndaftar komik:\n");
            for (int i = 0; i < hitung; i++) {
                printf("komikus: %s | nama: %s | populer: %d | rating: %.2f | tahun: %d\n", 
                       comics[i].komikus, comics[i].name, comics[i].populer, comics[i].rating, comics[i].tahun);
            }
            break;
        case 3:
            for (int i = 0; i < hitung - 1; i++) {
                for (int j = i + 1; j < hitung; j++) {
                    if (comics[i].populer < comics[j].populer) {
                        Comic temp = comics[i];
                        comics[i] = comics[j];
                        comics[j] = temp;
                    }
                }
            }
            printf("\ndaftar komik:\n");
            for (int i = 0; i < hitung; i++) {
                printf("populer: %d | nama: %s | komikus: %s | rating: %.2f | tahun: %d\n", 
                       comics[i].populer, comics[i].name, comics[i].komikus, comics[i].rating, comics[i].tahun);
            }
            break;
        case 4:
            for (int i = 0; i < hitung - 1; i++) {
                for (int j = i + 1; j < hitung; j++) {
                    if (comics[i].rating < comics[j].rating) {
                        Comic temp = comics[i];
                        comics[i] = comics[j];
                        comics[j] = temp;
                    }
                }
            }
            printf("\ndaftar komik:\n");
            for (int i = 0; i < hitung; i++) {
                printf("rating: %.2f | nama: %s | komikus: %s | populer: %d | tahun: %d\n", 
                       comics[i].rating, comics[i].name, comics[i].komikus, comics[i].populer, comics[i].tahun);
            }
            break;
        case 5:
            for (int i = 0; i < hitung - 1; i++) {
                for (int j = i + 1; j < hitung; j++) {
                    if (comics[i].tahun > comics[j].tahun) {
                        Comic temp = comics[i];
                        comics[i] = comics[j];
                        comics[j] = temp;
                    }
                }
            }
            printf("\ndaftar komik:\n");
            for (int i = 0; i < hitung; i++) {
                printf("tahun: %d | nama: %s | komikus: %s | populer: %d | rating: %.2f\n", 
                       comics[i].tahun, comics[i].name, comics[i].komikus, comics[i].populer, comics[i].rating);
            }
            break;
        default:
            printf("pilihan tidak valid.\n");
            return;
    }
}

void cari_komik() {
    if (hitung == 0) {
        printf("tidak ada komik untuk dicari.\n");
        return;
    }

    int pilih;
    printf("cari komik berdasarkan:\n");
    printf("1. nama komik\n");
    printf("2. nama komikus\n");
    printf("3. popularitas\n");
    printf("4. rating\n");
    printf("5. tahun\n");
    printf("pilih menu: ");
    scanf("%d", &pilih);

    switch (pilih) {
        case 1: {
            char cari_nama[MAX_NAME_LENGTH];
            printf("masukkan nama komik yang ingin dicari: ");
            getchar(); 
            fgets(cari_nama, MAX_NAME_LENGTH, stdin);
            cari_nama[strcspn(cari_nama, "\n")] = '\0';

            int found = 0;
            for (int i = 0; i < hitung; i++) {
                if (strcasecmp(comics[i].name, cari_nama) == 0) {
                    printf("komik ditemukan: nama: %s | komikus: %s | populer: %d | rating: %.2f | tahun: %d\n", 
                           comics[i].name, comics[i].komikus, comics[i].populer, comics[i].rating, comics[i].tahun);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("komik dengan nama '%s' tidak ditemukan.\n", cari_nama);
            }
            break;
        }
        case 2: {
            char cari_komikus[MAX_KOMIKUS_LENGTH];
            printf("masukkan nama komikus yang ingin dicari: ");
            getchar();
            fgets(cari_komikus, MAX_KOMIKUS_LENGTH, stdin);
            cari_komikus[strcspn(cari_komikus, "\n")] = '\0';

            int found = 0;
            for (int i = 0; i < hitung; i++) {
                if (strcasecmp(comics[i].komikus, cari_komikus) == 0) {
                    printf("komik ditemukan: nama: %s | komikus: %s | populer: %d | rating: %.2f | tahun: %d\n", 
                           comics[i].name, comics[i].komikus, comics[i].populer, comics[i].rating, comics[i].tahun);
                    found = 1;
                }
            }
            if (!found) {
                printf("komikus '%s' tidak ditemukan.\n", cari_komikus);
            }
            break;
        }
        case 3: {
            int cari_populer;
            printf("masukkan popularitas yang ingin dicari: ");
            scanf("%d", &cari_populer);

            int found = 0;
            for (int i = 0; i < hitung; i++) {
                if (comics[i].populer == cari_populer) {
                    printf("komik ditemukan: nama: %s | komikus: %s | populer: %d | rating: %.2f | tahun: %d\n", 
                           comics[i].name, comics[i].komikus, comics[i].populer, comics[i].rating, comics[i].tahun);
                    found = 1;
                }
            }
            if (!found) {
                printf("tidak ada komik dengan popularitas %d.\n", cari_populer);
            }
            break;
        }
        case 4: {
            float cari_rating;
            printf("masukkan rating yang ingin dicari: ");
            scanf("%f", &cari_rating);

            int found = 0;
            for (int i = 0; i < hitung; i++) {
                if (comics[i].rating == cari_rating) {
                    printf("komik ditemukan: nama: %s | komikus: %s | populer: %d | rating: %.2f | tahun: %d\n", 
                           comics[i].name, comics[i].komikus, comics[i].populer, comics[i].rating, comics[i].tahun);
                    found = 1;
                }
            }
            if (!found) {
                 printf("tidak ada komik dengan rating %.2f.\n", cari_rating);
            }
            break;
        }
        case 5: {
            int cari_tahun;
            printf("masukkan tahun yang ingin dicari: ");
            scanf("%d", &cari_tahun);

            int found = 0;
            for (int i = 0; i < hitung; i++) {
                if (comics[i].tahun == cari_tahun) {
                    printf("komik ditemukan: nama: %s | komikus: %s | populer: %d | rating: %.2f | tahun: %d\n", 
                           comics[i].name, comics[i].komikus, comics[i].populer, comics[i].rating, comics[i].tahun);
                    found = 1;
                }
            }
            if (!found) {
                printf("tidak ada komik dengan tahun %d.\n", cari_tahun);
            }
            break;
        }
        default:
            printf("pilihan tidak valid.\n");
            return;
    }
}

int main() {
    int pilih;
    do {
        printf("\nmenu:\n");
        printf("1. tambah komik\n");
        printf("2. tampilkan komik\n");
        printf("3. cari komik\n");
        printf("4. keluar\n");
        printf("pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                tambah_komik();
                break;
            case 2:
                tampilkan_komik();
                break;
            case 3:
                cari_komik();
                break;
            case 4:
                printf("keluar program...\n");
                break;
            default:
                printf("pilihan tidak valid.\n");
        }
    } while (pilih != 4);
    return 0;
}