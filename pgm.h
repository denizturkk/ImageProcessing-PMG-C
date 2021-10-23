#ifndef _PGM_H_
#define _PGM_H_

/* Hata kodlari */
#define PGM_ERROR_READ          1
#define PGM_ERROR_SIGNATURE     2
#define PGM_ERROR_MALLOC        3
#define LINE_MAX 60
/* Hata kodlarinin string karsiliklari */
static char *pgm_error_messages[] = {
    NULL,
    "PGM Error: Couldn't read file",
    "PGM Error: Signature mismatch. Should be P2 or P5.",
    "PGM Error: malloc() error.",
};

#define pgm_print_error(p) fprintf(stderr, "%s\n", pgm_error_messages[p.error]);

typedef struct {
    char signature[3];              // PGM imzasi
    char comment[LINE_MAX];         // opsiyonel yorum satiri
    int width;                      // resmin eni
    int height;                     // resmin boyu
    unsigned char max_pixel_value;  // bir pikselin max degeri
    unsigned char *pixels;          // pixel dizisi
    int error;                      // PGM hata kodu
} PGMInfo;

/* Fonksiyon bildirimleri */
void pgm_print_header(PGMInfo pgm_info);
PGMInfo pgm_read(const char *filename);
int pgm_write(const char *filename, PGMInfo pgm_info);

#endif

