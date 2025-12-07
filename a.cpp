#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int a;
    srand(time(NULL));
    int PCrastgeleSayi = (rand() % 10)+1;
   

    printf("1 ile 10 arasi bir sayi giriniz: ");
    scanf_s("%d", &a);

    if (a == PCrastgeleSayi) {
        printf("TEBRIKLER! Dogru tahmin ettiniz.");
    }
    else {
        printf("Maalesef yanlis sayiyi girdiniz.\n Dogru sayi %d ", PCrastgeleSayi);
    }

    return 0;
}
