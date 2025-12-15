#include <stdio.h>
#include <string.h> // strcpy ve strcmp fonksiyonları için
#include <math.h> // abs fonksiyonu için(mutlak değer)

typedef struct {
    int raw_adc_1;      // Ham ADC verisi (Kullanıcı girecek)
    int raw_adc_2;      // Ham ADC verisi (Kullanıcı girecek)
    int percent_1;      // Hesaplanmış %
    int percent_2;      // Hesaplanmış %
    int final_torque;   // Motora giden tork
    char status[20];    // "OK", "OutOfRange", "Implausible"
} PedalState;

int linear_map(int x, int in_min, int in_max, int out_min, int out_max);
void check_range(PedalState *ps);
void map_data(PedalState *ps);
void check_plausibility(PedalState *ps);

int main(){
    int max = 4095;
    // ilk başta bütün değerlere 0 ve statuse "OK"verdim
    PedalState ps = {0, 0, 0, 0, 0, "OK"}; 

    //Kullanıcıdan ADC değerlerini alır
    while (1) {
    printf("Enter first raw ADC value:\n");
    scanf("%d", &ps.raw_adc_1);

    if (ps.raw_adc_1 > max || ps.raw_adc_1 < 0) {
        printf("This value is not available. Please enter again.\n");
        continue;
    }
    printf("Enter second raw ADC value:\n");
    scanf("%d", &ps.raw_adc_2);

    if (ps.raw_adc_2 > max || ps.raw_adc_2 < 0) {
        printf("This value is not available. Please enter again.\n");
        continue;
    }
    break;
}
    // Güvenlik kontrollerini yapar
    check_range(&ps);
    map_data(&ps);
    check_plausibility(&ps);
    
    // Son duruma göre torku belirler
    if (strcmp(ps.status, "OK") != 0) { // Hata varsa torku 0 olarak alır
        ps.final_torque = 0;
        printf("! SYSTEM HALTED ! CRITICAL FAULT DETECTED. Status: %s. Torque locked to 0.\n", ps.status);
        while(1) { ; }
    } else {
        ps.final_torque = (ps.percent_1 + ps.percent_2) / 2; //Hata yoksa ortalama değeri alır
    }
    
    printf("Final Torque to Motor: %d\n", ps.final_torque);
    return 0;
}

// istenen aralık kontrollerini yapar
void check_range(PedalState *ps){ 
    if (strcmp(ps->status, "OK") != 0) return;
    
    if (ps->raw_adc_1 < 1000 || ps->raw_adc_1 > 4000){
        strcpy(ps->status, "OutOfRange");
        printf("CRITICAL ERROR: Out of Range! S1 Value: %d\n", ps->raw_adc_1);
        return; 
    }
    
    if (ps->raw_adc_2 < 500 || ps->raw_adc_2 > 2500){
        strcpy(ps->status, "OutOfRange");
        printf("CRITICAL ERROR: Out of Range! S2 Value: %d\n", ps->raw_adc_2);
        return; 
    }

    printf("Range Check Passed! Status: %s\n", ps->status);
}

// ADC verilerini yüzdeye çevirir
void map_data(PedalState *ps) {
    if (strcmp(ps->status, "OK") != 0) return; 

    ps->percent_1 = linear_map(ps->raw_adc_1, 1000, 4000, 0, 100);

    ps->percent_2 = linear_map(ps->raw_adc_2, 500, 2500, 0, 100);

    printf("Mapped Percentages: S1=%d%%, S2=%d%%\n", ps->percent_1, ps->percent_2);
}

// Aralarındaki farkı kontrol eder eğer 10%'dan büyükse hata verir
void check_plausibility(PedalState *ps) { 
    if (strcmp(ps->status, "OK") != 0) return;

    int diff = abs(ps->percent_1 - ps->percent_2);
    
    if (diff > 10) {
        strcpy(ps->status, "Implausible");
        printf("CRITICAL ERROR: Plausibility Check Failed! (Diff: %d%%)\n", diff);
        return;
    }

    printf("Plausibility Check Passed!\n");
}

// Map_data fonksiyonu için lineer dönüşüm fonksiyonu
int linear_map(int x, int in_min, int in_max, int out_min, int out_max) {
    long long numerator = (long long)(x - in_min) * (out_max - out_min);
    int denominator = in_max - in_min;

    if (denominator == 0) return out_min;
    
    if (x < in_min) return out_min;
    if (x > in_max) return out_max;

    return (int)(numerator / denominator) + out_min;
}