#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pedal durumunda kullanacaðým ifadeleri tek bir yerde topladým
typedef struct {
    int raw_adc_1;      // Ham ADC verisi (Kullanýcý girecek)
    int raw_adc_2;      // Ham ADC verisi (Kullanýcý girecek)
    int percent_1;      // Hesaplanmýþ %
    int percent_2;      // Hesaplanmýþ %
    int final_torque;   // Motora giden tork
    char status[20];    // "OK", "OutOfRange", "Implausible"
} PedalState;

 // adc 1 için yüzde hesaplama fonksiyonu
int percentraw1(int raw) {
    int in_min = 1000;
    int in_max = 4000;
    int out_min = 0;
    int out_max = 100;

    return (raw - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
// adc 2 için yüzde hesaplama fonksiyonu
int percentraw2(int raw) { 
    int in_min = 500;
    int in_max = 2500;
    int out_min = 0;
    int out_max = 100;

    return(raw - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
// pedal iþlemi fonksiyonu
void pedalislem(PedalState* p) {
    p->percent_1 = percentraw1(p->raw_adc_1);
    p->percent_2 = percentraw2(p->raw_adc_2);

    int fark = abs(p->percent_1 - p->percent_2);
    if (fark > 10) {
        strcpy_s(p->status, "IMKANSIZ");
        p->final_torque = 0;
    }
    else {
        strcpy_s(p->status, "OK");
        p->final_torque = (p->percent_1 + p->percent_2) / 2;
    }
}
int main()
    {
        PedalState pedal;
        // Kullanýcýdan geçerli adc 1 deðeri alana kadar döngü döner
        while (1) { 

            printf("Raw adc 1 degerini giriniz: ");
            scanf_s("%d", &pedal.raw_adc_1);

            if (pedal.raw_adc_1 >= 1000 && pedal.raw_adc_1 <= 4000) {
                break;
            }
            printf("HATA FARKLI BIR SAYI GIRINIZ\n: ");
        }
        // Kullanýcýdan geçerli adc 2 deðeri alana kadar döngü döner
        while (1) { 

            printf("Raw adc 2 degerini giriniz: ");
            scanf_s("%d", &pedal.raw_adc_2);

            if (pedal.raw_adc_2 >= 500 && pedal.raw_adc_2 <= 2500) {
                break;
            }
            printf("HATA FARKLI BIR SAYI GIRINIZ\n: ");

        }

        // Pedal iþlemi fonksiyonunu çaðýrýr
        pedalislem(&pedal);

        printf("Percent 1 : %d\n", pedal.percent_1);
        printf("Percent 2 : %d\n", pedal.percent_2);
        printf("Durum : %s\n", pedal.status);
        printf("Final torque : %d\n", pedal.final_torque);

        return 0;
    }