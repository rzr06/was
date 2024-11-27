#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "import.h"

void importData(Makanan data[], int *jumlahData) {
    char path[100];
    FILE *file;

    printf("\nMasukan path dan nama file CSV: ");
    scanf(" %[^\n]", path);

    file = fopen(path, "r");
    if (!file) {
        printf("\033[1;34mE003. Error Import Data Baru\033[0m\n");
        printf("File tidak ditemukan atau path salah.\n");
        return;
    }

    while (fscanf(file, " %[^,],%d,%10s", data[*jumlahData].nama, &data[*jumlahData].harga, data[*jumlahData].tanggal) != EOF) {
        (*jumlahData)++;
    }

    fclose(file);
    printf("Data berhasil diimport.\n");
}
