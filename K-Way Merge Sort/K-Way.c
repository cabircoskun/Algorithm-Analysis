#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
/*
@brief sýrasýz olarak alýnan n elemanlý bir diziyi sýralar

@param array : sýralanmak istenen dizi
@param n : dizi boyutu

@return sýralanan diziye point eden bir pointer dondurur.

*/
int* insertion_sort(int* array, int n) {//insertion sort algoritmasýný merge sortta k dan kucuk boyutlu dizileri sýralamak için kullandým.
    int i, j, tmp;
    for (i =0;i<n -1;i++) {
        if (array[i+ 1] < array[i]) {
            j = i;
            while(j>=0 && array[j+1] <array[j]) {
                tmp= array[j];
                array[j] = array[j+1];
                array[j+1]= tmp;
                j--;
            }
        }
    }
    return array;
}
/*
@brief k parçaya bolunmuþ bir dizinin her bir k parçasýný insertion sort ile sýralayarak daha sonra her birini sýralý þekilde birleþtirir.
@param arr : k parçaya bolunen dizi.
@param midpoints : her bir k. parçanýn kacýncý elemandan basladýgýný ve kacýncý elemanda bittigini saklayan dizi.
@param left : dizinin en sol indisi
@param right : dizinin en sag indisi
@param k : k parcaya bolunme iþlemin için ilgili k degeri

*/
void mergeKway(int* arr, int* midpoints, int left, int right, int k) {
    int** arrays = (int**)calloc(k, sizeof(int*)); // k tane alt dizi parçasýný burada sakladým
    int* nextIndis = (int*)calloc(k, sizeof(int));// k tane alt diziyi üst dizide birleþtirirken her bir dizinin kacýncý indisinde kaldýgýmý bu dizi ile tuttum.
    int* dimension = (int*)calloc(k, sizeof(int)); // her bir alt dizinin boyutu.
    int i, j,start,end,n;// dongu degiskenleri
    int min, minIndis, mainIndis = left, completed = 0;
    for (i = 0; i < k; i++) {
        start = (i == 0) ? left : midpoints[i - 1] + 1;//her bir alt dizinin baskangic ve bitis noktasýný burada belirledim.
        end = (i == k - 1) ? right : midpoints[i];
        n = end - start + 1;// her bir alt dizinin boyutunu dimension dizisine attým
        dimension[i] = n;
        arrays[i] = (int*)calloc(n, sizeof(int));

        for (j = 0; j < n; j++) {
            arrays[i][j] = arr[start + j];// her bir alt diziyi ana diziden alýp buraya yerleþtirdim.
        }
        insertion_sort(arrays[i], n); //her bir alt diziyi kendi icinde insertion sort ile sýraladým
    }

    
    while (completed == 0) {//her bir alt dizi üst dizide birleþene dek dondurdum.
        min = INT_MAX;
        for (i = 0; i < k; i++) {//her bir alt dizinin ilgili indisiini karþýlaþtýrarak min elemaný buldum.
            if (nextIndis[i] < dimension[i]) {
                if (arrays[i][nextIndis[i]] < min) {
                    min = arrays[i][nextIndis[i]];
                    minIndis = i;
                }
            }
        }
        if (min != INT_MAX) {//eger hala yerleþecek eleman varsa min deger bulunmus demektir.
            arr[mainIndis] = min;//ana diziye o degeri yazdým.
            mainIndis++;
            nextIndis[minIndis]++;
        } else {//yerlesecek eleman kalmadýgýnda buradan donguyu sonlandýrýr.
            completed = 1;
        }
    }

    for (i = 0; i < k; i++) {
        free(arrays[i]);
    }
    free(arrays);
    free(nextIndis);
    free(dimension);
}
/*
@brief sýralanmak üzere alýnan bir diziyi recursive olarak her adýmda k eþit parçaya böler. durma koþulu ise ilgili dizi boyutu < k.
@param array : sýralanmak istenen dizi.
@param left : dizinin en sol indisi
@param right : dizinin en sag indisi
@param k : k parcaya bolunme iþlemin için ilgili k degeri

*/
void mergeSort(int* array, int left, int right, int k) {
    int i,start,end;
    if (right-left+1<=k) return;

    int segmentSize =(right-left+ 1)/ k; // k elemana boldugumde her bir alt parcanýn boyutu burada saklanýr
    int midPoints[k-1];//her bir alt parcaýn baslangýc ve bitiþ noktalarý bu dizide tutulur

    for (i= 0;i< k-1;i++){
        midPoints[i] =left+(i+1)*segmentSize-1;//her bir alt parcaýn baslangýc ve bitiþ noktalarý ilgili indise yerleþtirirlir.
    }

    for (i = 0; i < k; i++) {//dizi k kere mergesort ile bölünür.
        start = (i==0)?left :midPoints[i- 1] +1;
        end = (i== k-1) ? right :midPoints[i];
        mergeSort(array, start, end, k);
    }

    mergeKway(array, midPoints, left, right, k);// daha bolunemeyecek kadar kucuk oldugunda merge fonksyionuna gider.
}
/*
@brief alýnan bir dizinin elemanlarýný rastgele karýþtýran fonksiyon
@param arr : shuffle edilmek istenen dizi
@param n : dizi boyutu

*/
void shuffle(int* arr, int n) {
	
    int i,j ;
    int temp;
	for (i =n-1; i >0;i--) {
        j= rand()%(i+1);
        temp =arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
}


/*
@brief istenen n ve k degerleri icin farklý diziler üretip ilgili dizilerin sýralanma süresini ekrana bastýran main fonksiyon.


*/

int main() {
	
	srand(time(0));
	int* arr; // mergesort için dizi açtým
	int* arrCheck ; // her k deðeri icin ayný dizi kullanýlacagýndan bu diziyi de her seferinde arr i kopyalamak için kullandým
    int n ,i,j,k;//dongu ve boyut degiskenleri
    int random;
    int trash,index=0;//indisler
    double old_time;//zaman degiskenleri
    double time_taken;
    FILE* file = fopen("output.txt", "r");//buldugum sureleri 10 kez calýstýrýp dosyaya yazmak icin dosya acýyorum
  
    double times[100];//buldugum eski sureleri okuyup yeni süreyle toplayýp geri dosyaya yazýyorum.
    for(i=0;i<6;i++){// 6 farklý n deðeri icin dongu
    n = 100*(pow(10,i));
    arr = (int*)malloc(n * sizeof(int));
    arrCheck = (int*)calloc(n , sizeof(int));
    
     for (j = 0; j < n;j++) {//diziyi 1 den n e kadar olusturup shuffle ediyorum
        arr[j] = j;
    }shuffle(arr, n);
 
     
    for(k=2;k<=10;k++){//her k degeri ile merge iþlemi için bu donguye giriyorum
    for (j = 0; j < n;j++) {
        arrCheck[j] = arr[j];// ana diziyi kopyalýyorum her k deðeri icin ayný olmasý icin.
    }   
     
        clock_t start_time = clock();// zaman tutmak adýna clock
    	mergeSort(arrCheck, 0, n - 1, k);
    	clock_t end_time = clock();
		  time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;//gecirilen zamaný hesaplar
		//dosyadan okuma yapmak istenirse bu yorum satýrý kaldýrýlýr.
		    /*old_time =0 ;
		
	        fscanf(file, "%d %d %lf\n", &trash, &trash, &old_time);//dosyadan ilgili k ve n degeri için önceki süre toplamýný çeker
            times[index]= time_taken+old_time;//þu anki süre ile öncekileri toplar
   
            index++;*/
		printf("MergeSort  k=%d n = %d took %f seconds\n", k,n, time_taken);// ekrana ilgili k ve n deðerinin merge iþlemi için gecen süreyi yazdýrýr
	}
    free(arr);
    free(arrCheck);
	}
	fclose(file);//okuma modunda actýgým dosyayý kapatýyorum.
	file = fopen("output.txt", "w");//yazma modunda dosyayý tekrar acýyorum.
  
   n = 10;
   for (i = 0; i < 54; i++) {//6 farklý n , 9 farklý  k deðeri icin 54 adet deðer yazýlcak diziye.
   	if(i%9 == 0){
   		n=n*10;
	   }//eðer dosyaya yazma yapmak istenirse burayý yorum satýrýndan kaldýr
       // fprintf(file, "%d %d %.6f\n", i%9+2, n, times[i]);//buldugumuz süreleri dosyaya geri yazýyoruz.
    }
  fclose(file);
    return 0;
} 

