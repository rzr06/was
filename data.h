#ifndef DATA_H
#define DATA_H

#define MAX_DATA 100

typedef struct {
    char nama[50];
    int harga;
    char tanggal[11]; // Format: dd-mm-yy
} Makanan;

// Deklarasi fungsi
void importData(Makanan data[], int *jumlahData);
void exportData(Makanan data[], int jumlahData);

#endif
