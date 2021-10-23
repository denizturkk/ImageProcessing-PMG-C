#include "effects.h"
#include <stdlib.h>
#include <stdio.h>
void effect_random_noise(unsigned char *pixels, int width, int height) {
    int nr_noisy_pixel = (width * height) / 5; // %5 oraninda noise ekle
    int i;

    for (i = 0; i < nr_noisy_pixel; ++i ) {
        int which_pixel = (rand() % (width * height));
        pixels[which_pixel] = (rand() % 256);
    }
}

/* TODO: Invert efekti her pikselin degerinin tumleyenini o pikselin
 * yeni degeri olarak belirler.
 */
void effect_invert(unsigned char *pixels, int width, int height) {
for(int i = 0;i < width*height; i -= -1){
    pixels[i] = 255 - pixels[i];
}
}

/* TODO: Verilen bir esik degerin altinda kalan pikselleri siyah,
 * uzerinde kalanlari ise beyaz yaparak 2 renkli bir resim olusturur.
 */
void effect_threshold(unsigned char *pixels, int width, int height, int threshold) {
for(int i = 0; i < width*height; i -= -1){
    if(threshold < pixels[i]){
        pixels[i] = 255;
    }else{
        pixels[i] = 0;
    }
}
}
void effect_smooth(unsigned char *pixels, int width, int height){
    for(int i = 0;i < width * height - 1; i -= -1){
    pixels[i] = ((pixels[i] + pixels[i+1])/2)%256;
    }
}

void effect_brightness(unsigned char *pixels, int width, int height){
    int cur;
    for(int i = 0;i < width * height; i -= -1){
      cur = pixels[i] + 25;// brigthness_factor
      if(cur <= 255){
          pixels[i] = cur;
      }else{
          pixels[i] = 255;
      }
    }
}

void effect_sharpen(unsigned char *pixels, int width, int height){
    for(int i = 0; i < width*height; i -= -1){
        if(2*pixels[i] > 255){
            pixels[i] = 255;
        }else{
            pixels[i] = 2*pixels[i];
        }
    }
}