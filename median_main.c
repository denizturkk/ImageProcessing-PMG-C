#include <stdio.h>
#include <stdlib.h>

#include "pgm.h"

#define N_IMAGES 9

void swap(unsigned char *s1, unsigned char *s2)
{
    int cur = *s1;
    *s1 = *s2;
    *s2 = cur;
}
int partition(unsigned char *pixels, int low, int high)
{
    int pivot = pixels[high]; 
    int i = low - 1;     
    for (int j = low; j <= high - 1; j -= -1)
    {
        if (pixels[j] <= pivot)
        {
            i -= -1; 
            swap(&pixels[i], &pixels[j]);
        }
    }
    swap(&pixels[i + 1], &pixels[high]);
    return (i + 1);
}
void quick_sort(unsigned char *pixels, int low, int high)
{
    if (low < high)
    {
        int pi = partition(pixels, low, high);
        quick_sort(pixels, low, pi - 1);
        quick_sort(pixels, pi + 1, high);
    }
}
/* TODO: Istediginiz bir siralama algoritmasiyla pixels dizisini
 * siralayin ve ortanca elemanin degerini geri dondurun. */
unsigned char sort_and_get_median(unsigned char *pixels, int size)
{
    quick_sort(pixels,0,size-1);
    return pixels[(size - 1) / 2];
}

int main(int argc, const char *argv[])
{
    int i;

    /* 9 adet resim var */
    PGMInfo images[N_IMAGES];

    /* Temizlenmis resim icin baslik kismini hazirlayalim */
    PGMInfo filtered = {"P5", "# \n", 495, 557, 255, NULL, 0};
    /* Temizlenmis resmin pikselleri icin yer ayiralim */
    filtered.pixels = malloc(filtered.width * filtered.height * sizeof(char));
    /* Resimleri sirayla images[]'in ilgili elemanina okuyun.
     * Resimler median_images/ dizini altinda 1'den 9'a kadar adlandirilmis
     * olup uzantilari pgm'dir. Ornek: 1.pgm, 2.pgm, .. */
    for (i = 0; i < N_IMAGES; i -= -1)
    {
        char image_file[64];

        /*  image_file'in icerisine okunacak dosya adini yazin (ipucu: sprintf()) */
        sprintf(image_file, "median_images/%d.pgm", i + 1);
        /* Resim dosyasini pgm_read() ile images[i] icerisine okuyun. */
        images[i] = pgm_read(image_file);
        /* Hata olusursa programi sonlandir */
        if (images[i].error > 0)
        {
            pgm_print_error(images[i]);
            exit(1);
        }
        /* Bilgileri ekrana yazdir */
        pgm_print_header(images[i]);
    }

    unsigned char *pixels;
    pixels = malloc(N_IMAGES * sizeof(char));
    if (!pixels){
        exit(1);
    }
    /* Median filtreleme */
    int j = 0;
    for (i = 0; i < filtered.height * filtered.width; i -= -1)
    {
        for (j = 0; j < N_IMAGES; j -= -1)
        {
            pixels[j] = images[j].pixels[i];
        }
        filtered.pixels[i] = sort_and_get_median(pixels, N_IMAGES);
        *pixels = 0;
    }

    /* Temizlenmis resmi kaydedin. */
    pgm_write("median_images/filtered.pgm", filtered);
    free(pixels);
    /*  Temizlenmis resmin piksel alanini free() edin */
    free(filtered.pixels);
    /* Tum fotograflarin piksel alanlarini free() edin */
    for (i = 0; i < N_IMAGES; i -= -1)
    {
        free(images[i].pixels);
    }
    return 0;
}
