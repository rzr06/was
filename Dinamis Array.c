#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int jam, menit;
    float kecepatan, arah;
} DataAngin;


void menu();
void catatAngin(DataAngin **data, int *jumlah);
void lihatData(DataAngin *data, int jumlah);
void editData(DataAngin *data, int jumlah);
void rekamData(DataAngin *data, int jumlah);
void lihatRekaman();
int cariData(DataAngin *data, int jumlah, int jam, int menit);

int main() {
    DataAngin *data = NULL;
    int jumlah = 0, pilihan;

    while (1) {
        menu();
        scanf("%d", &pilihan);
        if (pilihan == 9) break;
        switch (pilihan) {
            case 1: catatAngin(&data, &jumlah); break;
            case 2: lihatData(data, jumlah); break;
            case 3: editData(data, jumlah); break;
            case 5: rekamData(data, jumlah); break;
            case 6: lihatRekaman(); break;
            default: printf("Pilihan tidak valid.\n");
        }
    }

    free(data);
    printf("Terimakasih. Program selesai.\n");
    return 0;
}

void menu() {
    printf("\nMenu Riset Cuaca\n");
    printf("[1] Catat arus angin\n[2] Lihat daftar arus angin\n");
    printf("[3] Edit data arus angin\n[5] Rekam data harian\n");
    printf("[6] Lihat keseluruhan rekaman\n[9] Keluar\nPilihan anda: ");
}

void catatAngin(DataAngin **data, int *jumlah) {
    char lanjut;
    do {
        *data = realloc(*data, (*jumlah + 1) * sizeof(DataAngin));
        printf("Masukan waktu pencatatan ([0-24] [0-59]): ");
        scanf("%d %d", &(*data)[*jumlah].jam, &(*data)[*jumlah].menit);
        printf("Masukan kecepatan angin (km/h): ");
        scanf("%f", &(*data)[*jumlah].kecepatan);
        printf("Masukan arah angin (0.0-359.0): ");
        scanf("%f", &(*data)[*jumlah].arah);
        (*jumlah)++;
        printf("Masih ada data? [Y/T]: ");
        scanf(" %c", &lanjut);
    } while (lanjut == 'Y' || lanjut == 'y');
}

void lihatData(DataAngin *data, int jumlah) {
    if (jumlah == 0) {
        printf("Tidak ada data yang dicatat.\n");
    } else {
        printf("\nWaktu\tKecepatan\tArah\n");
        for (int i = 0; i < jumlah; i++) {
            printf("%02d:%02d\t%.2f\t\t%.2f\n", data[i].jam, data[i].menit, data[i].kecepatan, data[i].arah);
        }
    }
}

void editData(DataAngin *data, int jumlah) {
    int jam, menit, idx;
    printf("Masukan waktu yang mau di edit ([0-24] [0-59]): ");
    scanf("%d %d", &jam, &menit);
    idx = cariData(data, jumlah, jam, menit);

    if (idx == -1) {
        printf("Waktu Inputan tidak ditemukan.\n");
    } else {
        printf("Waktu %02d:%02d\nKecepatan %.2f\nArah %.2f\n", jam, menit, data[idx].kecepatan, data[idx].arah);
        printf("Masukan revisi kecepatan angin (km/h): ");
        scanf("%f", &data[idx].kecepatan);
        printf("Masukan revisi arah angin (0.0-359.0): ");
        scanf("%f", &data[idx].arah);
        char yakin;
        printf("Yakin data sudah betul? [Y/T]: ");
        scanf(" %c", &yakin);
        if (yakin == 'Y' || yakin == 'y') {
            printf("Data telah diupdate.\n");
        } else {
            printf("Data tidak diubah.\n");
        }
    }
}

void rekamData(DataAngin *data, int jumlah) {
    FILE *file = fopen("ANGIN.DAT", "wb");
    if (!file) {
        printf("Gagal rekam.\n");
        return;
    }
    fwrite(data, sizeof(DataAngin), jumlah, file);
    fclose(file);
    printf("Data berhasil direkam ke ANGIN.DAT.\n");
}

void lihatRekaman() {
    FILE *file = fopen("ANGIN.DAT", "rb");
    if (!file) {
        printf("Gagal membaca file.\n");
        return;
    }
    DataAngin data;
    printf("\nWaktu\tKecepatan\tArah\n");
    while (fread(&data, sizeof(DataAngin), 1, file)) {
        printf("%02d:%02d\t%.2f\t\t%.2f\n", data.jam, data.menit, data.kecepatan, data.arah);
    }
    fclose(file);
}

int cariData(DataAngin *data, int jumlah, int jam, int menit) {
    for (int i = 0; i < jumlah; i++) {
        if (data[i].jam == jam && data[i].menit == menit) {
            return i;
        }
    }
    return -1;
}
