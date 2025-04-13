#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef struct {
    double x, y, z;
} DataPoint;


void sort(double arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


double medyanBul(double arr[], int n) {
    if (n % 2 == 0)
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    else
        return arr[n / 2];
}


double aritmatikOrtalama(double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

double tepeDegeri(double arr[], int n) {
    int maxCount = 0;
    double mode = arr[0];
    
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mode = arr[i];
        }
    }
    return mode;

}


double degisimAraligi(double arr[], int n) {
    double minDeger = arr[0]; 
    double maxDeger = arr[0]; 
    for (int i = 1; i < n; i++) { 
        if (arr[i] < minDeger) {
            minDeger = arr[i];
        }
        if (arr[i] > maxDeger) {
            maxDeger = arr[i];
        }
    }

    return maxDeger - minDeger;
}

double mutlakDeger(double n) {
    if (n < 0) {
        return -n;
    }
    return n;
}


double ortalamaMutlakSapma(double arr[], int n) {
    double toplam = 0.0, ortalama = 0.0;

    ortalama=aritmatikOrtalama(arr,n);
    toplam = 0.0;
    for (int i = 0; i < n; i++) {
        toplam += mutlakDeger(arr[i] - ortalama);
    }
    return toplam / n;
}


double varyansHesapla(double arr[],int n){
	double toplam=0.0 ,ortalama= aritmatikOrtalama(arr,n);
	for(int i=0;i<n;i++){
		toplam+=(arr[i]-ortalama)*(arr[i]-ortalama);
	}
	return toplam/n;
}

double karekok(double arr[],int x) {
	x=varyansHesapla(arr,x);
    double tahmin = x / 2.0;  
    double fark;
    
    
    do {
        double yeniTahmin = 0.5 * (tahmin + x / tahmin);  
        fark = yeniTahmin - tahmin;  
        if (fark < 0) fark = -fark; 
        tahmin = yeniTahmin;  
    } while (fark > 0.000001);  
    
    return tahmin;
}

double degisimKatsayisi(double arr[],int n){
	float standartSapma=karekok(arr,n);
	float ortalama=aritmatikOrtalama(arr,n);
	return standartSapma/ortalama;	
}

void findOutliers(DataPoint data[], int n) {
    double xValues[MAX_SIZE], yValues[MAX_SIZE], zValues[MAX_SIZE];

    for (int i = 0; i < n; i++) {
        xValues[i] = data[i].x;
        yValues[i] = data[i].y;
        zValues[i] = data[i].z;
    }

    sort(xValues, n);
    sort(yValues, n);
    sort(zValues, n);

    double Q1_X = medyanBul(xValues, n / 2);
    double Q3_X = medyanBul(xValues + (n + 1) / 2, n / 2);
    double IQR_X = Q3_X - Q1_X;

    double Q1_Y = medyanBul(yValues, n / 2);
    double Q3_Y = medyanBul(yValues + (n + 1) / 2, n / 2);
    double IQR_Y = Q3_Y - Q1_Y;

    double Q1_Z = medyanBul(zValues, n / 2);
    double Q3_Z = medyanBul(zValues + (n + 1) / 2, n / 2);
    double IQR_Z = Q3_Z - Q1_Z;

    double altSinirX = Q1_X - 1.5 * IQR_X;
    double ustSinirX = Q3_X + 1.5 * IQR_X;

    double altSinirY = Q1_Y - 1.5 * IQR_Y;
    double ustSinirY = Q3_Y + 1.5 * IQR_Y;

    double altSinirZ = Q1_Z - 1.5 * IQR_Z;
    double ustSinirZ = Q3_Z + 1.5 * IQR_Z;
  
    printf("Degiken 1 icin aykiri degerler: [");
    int first = 1;
    for (int i = 0; i < n; i++) {
        if (data[i].x < altSinirX || data[i].x > ustSinirX) {
            if (!first) printf(", ");
            printf("%.0f", data[i].x);
            first = 0;
        }
    }
    printf("]\n");

    printf("Degiken 2 icin aykiri degerler: [");
    first = 1;
    for (int i = 0; i < n; i++) {
        if (data[i].y < altSinirY || data[i].y > ustSinirY) {
            if (!first) printf(", ");
            printf("%.0f", data[i].y);
            first = 0;
        }
    }
    printf("]\n");

    printf("Degiken 3 icin aykiri degerler: [");
    first = 1;
    for (int i = 0; i < n; i++) {
        if (data[i].z <altSinirZ || data[i].z > ustSinirZ) {
            if (!first) printf(", ");
            printf("%.0f", data[i].z);
            first = 0;
        }
    }
    printf("]\n");
     int newCountX = 0,newCountY=0, newCountZ=0;
    double filteredX[MAX_SIZE], filteredY[MAX_SIZE], filteredZ[MAX_SIZE];
     
     
     for(int i=0;i<n;i++){
     	
     	if (data[i].x >= altSinirX && data[i].x <= ustSinirX) {
            filteredX[newCountX] = data[i].x;
            newCountX++;
        }

    
        if (data[i].y >= altSinirY && data[i].y <= ustSinirY) {
            filteredY[newCountY] = data[i].y;
            newCountY++;
        }


        if (data[i].z >= altSinirZ && data[i].z <= ustSinirZ) {
            filteredZ[newCountZ] = data[i].z;
            newCountZ++;
        
	 }
}
   
     printf("\n");

    printf("Aykiri degerler cikarildiktan sonra:\n");
    printf("\n");
    

    printf("Degisken 1 icin Aritmetik Ortalama: %.2f\n", aritmatikOrtalama(filteredX, newCountX));
    printf("Degisken 2 icin Aritmetik Ortalama: %.2f\n", aritmatikOrtalama(filteredY, newCountY));
    printf("Degisken 3 icin Aritmetik Ortalama: %.2f\n", aritmatikOrtalama(filteredZ, newCountZ));
    printf("\n");

    printf("Degisken 1 icin Ortanca: %.2f\n", medyanBul(filteredX, newCountX));
    printf("Degisken 2 icin Ortanca: %.2f\n", medyanBul(filteredY, newCountY));
    printf("Degisken 3 icin Ortanca: %.2f\n", medyanBul(filteredZ, newCountZ));
    printf("\n");
    

    printf("Degisken 1 icin Tepe Degeri: %.0f\n", tepeDegeri(filteredX, newCountX));
    printf("Degisken 2 icin Tepe Degeri: %.0f\n", tepeDegeri(filteredY, newCountY));
    printf("Degisken 3 icin Tepe Degeri: %.0f\n", tepeDegeri(filteredZ, newCountZ));
    printf("\n");
    
    printf("Degisken 1 icin degisim Degeri: %.0f\n", degisimAraligi(filteredX, newCountX));
    printf("Degisken 2 icin degisim Degeri: %.0f\n", degisimAraligi(filteredY, newCountY));
    printf("Degisken 3 icin degisim Degeri: %.0f\n", degisimAraligi(filteredZ, newCountZ));
    printf("\n");
    
    printf("Degisken 1 icin OMS Degeri: %.0f\n", ortalamaMutlakSapma(filteredX, newCountX));
    printf("Degisken 2 için OMS Degeri: %.0f\n", ortalamaMutlakSapma(filteredY, newCountY));   
    printf("Degisken 3 için OMS Degeri: %.0f\n", ortalamaMutlakSapma(filteredZ, newCountZ)); 
    printf("\n");
    
    printf("Degisken 1 icin varyans Degeri: %.0f\n", varyansHesapla(filteredX, newCountX));
    printf("Degisken 2 icin varyans Degeri: %.0f\n", varyansHesapla(filteredY, newCountY));
    printf("Degisken 3 icin varyans Degeri: %.0f\n", varyansHesapla(filteredZ, newCountZ));
    printf("\n");
    
    printf("Degisken 1 icin standart sapma  Degeri: %.0f\n",karekok(filteredX, newCountX));
    printf("Degisken 2 icin standart sapma  Degeri: %.0f\n",karekok(filteredY, newCountY));
    printf("Degisken 3 icin standart sapma  Degeri: %.0f\n",karekok(filteredZ, newCountZ));
    printf("\n");
    
    printf("Degisken 1 icin degisim Degeri: %.2f\n",degisimKatsayisi(filteredX, newCountX));
    printf("Degisken 2 icin degisim Degeri: %.2f\n",degisimKatsayisi(filteredY, newCountY));
    printf("Degisken 3 icin degisim Degeri: %.2f\n",degisimKatsayisi(filteredZ, newCountZ));
    printf("\n");
    
    
    printf("degisken 1 ceyrekler acikligi %.0f\n",IQR_X );
    printf("degisken 2 ceyrekler acikligi %.0f\n",IQR_Y );
    printf("degisken 3 ceyrekler acikligi %.0f\n",IQR_Z );
    printf("\n");
}

int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Dosya açýlamadý!\n");
        return 1;
    }

    DataPoint data[MAX_SIZE];
    int count = 0;

    
    while (fscanf(file, "%lf %lf %lf", &data[count].x, &data[count].y, &data[count].z) == 3) {
        count++;
        if (count >= MAX_SIZE) break;
    }
    fclose(file);

    if (count == 0) {
        printf("Dosyada veri bulunamadý.\n");
        return 1;
    }
    findOutliers(data, count);

    return 0;
}


