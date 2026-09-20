#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int sum_array(int arr[],int size){
    int sum = 0;
    for(int i = 0; i<size; i++){
        sum += arr[i];
    }
    return sum;
}

long long factorial(int n){
    if(n < 0){
        return -1;
    }
    if(n == 0 || n == 1){
        return 1;
    }else{
    long long result =1;
    for(int i = 2; i<=n; i++){
        result *=i;
    }
    return result;
    }
}

long long fibonacci(int n){
    if(n < 0) return -1;
    if(n == 0) return 0;
    if(n == 1) return 1;
    long long a = 0, b = 1, c;
    for(int i=2; i<=n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

bool is_right_triangle(double a,double b,double c){
    if(a <= 0 || b <= 0 || c <= 0){
        return false;
    }
    double x = fmax(a, fmax(b, c));
    double y, z;
    if(x == a){
        y = b;
        z = c;
    } else if(x == b){
        y = a;
        z = c;
    } else {
        y = a;
        z = b;
    }
    return fabs(x*x - (y*y + z*z)) < 1e-9;
}

typedef struct {
    double x;
    double y;
    double w;
    double h;
} Rect;

bool rect_overleap(Rect r1,Rect r2){
    if(r1.x + r1.w < r2.x || r2.x + r2.w < r1.x|| r1.y + r1.h < r2.y || r2.y + r2.h < r1.y){
        return false;
    }
    return true;
}

double usd_to_cny(double usd,double rate){
    if(rate <= 0){
        return -1;
    }
    return usd * rate;
}

int main(void){
    int arr[] = {1,2,3,4,5};
    printf("Sum of array: %d\n", sum_array(arr, 5));
    
    int n = 5;
    printf("Factorial of %d: %lld\n", n, factorial(n));
    
    n = 10;
    printf("Fibonacci of %d: %lld\n", n, fibonacci(n));
    
    double a = 3.0, b = 4.0, c = 5.0;
    printf("Is right triangle: %s\n", is_right_triangle(a, b, c) ? "true" : "false");
    
    Rect r1 = {0.0, 0.0, 2.0, 2.0};
    Rect r2 = {1.0, 1.0, 2.0, 2.0};
    printf("Do rectangles overlap: %s\n", rect_overleap(r1, r2) ? "true" : "false");
    
    double usd = 100.0;
    double rate = 6.5;
    printf("%.2f USD to %.2f CNY (rate: %.2f)\n", usd, usd_to_cny(usd, rate), rate);
    
    return 0;
}