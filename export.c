#include <stdio.h>
#include "data.h"
#include "export.h"

void exportData(Makanan data[], int jumlahData) {
    char path[100];
    FILE *file;

    printf("\nMasukan Path dan nama file untuk export data: ");
    scanf(" %[^\n]", path);

    file = fopen(path, "w");
    if (!file) {
        printf("\033[1;34mE005. Error Export\033[0m\n");
        printf("Gagal export file. Periksa nama file dan path.\n");
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        fprintf(file, "%s,%d,%s\n", data[i].nama, data[i].harga, data[i].tanggal);
    }

    fclose(file);
    printf("Data berhasil diexport.\n");
}