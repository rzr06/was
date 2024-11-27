#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "import.h"
#include "export.h"


// Variabel global
Makanan data[MAX_DATA];
int jumlahData = 0;

// Deklarasi fungsi import dan export secara eksplisit
void importData(Makanan data[], int *jumlahData);
void exportData(Makanan data[], int jumlahData);

// Fungsi utama program
void inputData();
void browseData();
void berhentiProgram();

void menuUtama() {
    int pilihan;

    do {
         printf("\nMenu Masakan\n");
        printf("[\033[1;34m\033[1m1\033[0m] Input Data Baru\n" );
        printf("[\033[1;34m\033[1m2\033[0m] Import Data Baru\n" );
        printf("[\033[1;34m\033[1m3\033[0m] Browse Data\n" );
        printf("[\033[1;34m\033[1m4\033[0m] Export ke CSV\n");
        printf("[\033[1;34m\033[1m9\033[0m] Berhenti Program\n");
        printf("Pilihan anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputData();
                break;
            case 2:
                importData(data, &jumlahData); // Fungsi import
                break;
            case 3:
                browseData();
                break;
            case 4:
                exportData(data, jumlahData); // Fungsi export
                break;
            case 9:
                berhentiProgram();
                break;
            default:
                printf("\033[1;34mE001. Error Pilihan\033[0m\n");
                printf("Maaf, pilihan salah. Hanya boleh [1, 2, 3, 4, 9].\n");
        }
    } while (pilihan != 9);
}

void inputData() {
    char ulangi = 'Y';
    do {
        printf("\nMasukan Nama Masakan: ");
        scanf(" %[^\n]", data[jumlahData].nama);
        printf("Masukan Harga Jual: Rp. ");
        scanf("%d", &data[jumlahData].harga);
        printf("Masukan Tanggal Produksi (dd-mm-yy): ");
        scanf(" %10s", data[jumlahData].tanggal);

        if (strlen(data[jumlahData].tanggal) != 8 || data[jumlahData].tanggal[2] != '-' || data[jumlahData].tanggal[5] != '-') {
            printf("\033[1;34mE002. Error Tanggal Produksi\033[0m\n");
            printf("Format yang diperbolehkan adalah dd-mm-yy.\n");
            continue;
        }

        jumlahData++;
        printf("Masih ada data? [Y/T]: ");
        scanf(" %c", &ulangi);
    } while (ulangi == 'Y' || ulangi == 'y');
}

void browseData() {
    int index = 0;
    char pilihan;

    if (jumlahData == 0) {
        printf("Tidak ada data untuk ditampilkan.\n");
        return;
    }

    do {
        printf("\nData ke \033[1;34m%d\033[0m dari \033[1;34m%d\033[0m\n", index + 1, jumlahData);
        printf("Nama Masakan: %s\n", data[index].nama);
        printf("Harga: Rp. %d\n", data[index].harga);
        printf("Tanggal Produksi: %s\n", data[index].tanggal);
        printf("Pilihan [P/N/Q]: ");
        scanf(" %c", &pilihan);

        if (pilihan == 'P') {
            index = (index == 0) ? jumlahData - 1 : index - 1;
        } else if (pilihan == 'N') {
            index = (index == jumlahData - 1) ? 0 : index + 1;
        } else if (pilihan != 'Q') {
            printf("\033[1;34mE004. Error Pilihan\033[0m\n");
            printf("Pilihan hanya boleh P, N, atau Q.\n");
        }
    } while (pilihan != 'Q');
}

void berhentiProgram() {
    printf("\n\033[1;34mTerima kasih sudah menggunakan aplikasi keren ini.\033[0m\n");
    exit(0);
}

int main() {
    menuUtama();
    return 0;
}