#include <stdio.h>
#include <stdlib.h>

float max = 4095.0;
float min = 0.0;
float yuzde(float x);
float average(float x, float y);
float safetycontrol(float x, float y);
void deadzone();
void saturation();

int main(){

    float raw1,raw2;

    while (1) {
    printf("Enter the first value:\n");
    scanf("%f", &raw1);

    if (raw1 > max || raw1 < min) {
        printf("This value is not available. Please enter again.\n");
        continue;
    }
    printf("Enter the second value:\n");
    scanf("%f", &raw2);

    if (raw2 > max || raw2 < min) {
        printf("This value is not available. Please enter again.\n");
        continue;
    }
    break;
}
    printf("\nSafety Control:\n");
    safetycontrol(raw1, raw2);

    float avg = average(raw1, raw2);

    if (avg < 200){
        deadzone();
    }
    else if (avg > 3800){
        saturation();
    }
    else {
        float percent = yuzde(avg);
        printf("Percentage value: %.2f%%\n", percent);
    }
    return 0;
}

float yuzde(float x){
    return (((x-200)*100)/(3800-200));
}
float average(float x, float y){
    return (x+y)/2;
}
float safetycontrol(float x, float y){
    if (x-y > 300 || y-x > 300){
        printf("Error! System is not reliable.\n");
        exit(0);
    } else {
        printf("Safety control completed successfully.\n");
    }
}
void deadzone(){
    printf("Too low — interpreted as %%0\n");
}
void saturation(){
    printf("Too high — interpreted as %%100\n");
}
