#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
/*
@brief s�ras�z olarak al�nan n elemanl� bir diziyi s�ralar

@param array : s�ralanmak istenen dizi
@param n : dizi boyutu

@return s�ralanan diziye point eden bir pointer dondurur.

*/
int* insertion_sort(int* array, int n) {//insertion sort algoritmas�n� merge sortta k dan kucuk boyutlu dizileri s�ralamak i�in kulland�m.
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
@brief k par�aya bolunmu� bir dizinin her bir k par�as�n� insertion sort ile s�ralayarak daha sonra her birini s�ral� �ekilde birle�tirir.
@param arr : k par�aya bolunen dizi.
@param midpoints : her bir k. par�an�n kac�nc� elemandan baslad�g�n� ve kac�nc� elemanda bittigini saklayan dizi.
@param left : dizinin en sol indisi
@param right : dizinin en sag indisi
@param k : k parcaya bolunme i�lemin i�in ilgili k degeri

*/
void mergeKway(int* arr, int* midpoints, int left, int right, int k) {
    int** arrays = (int**)calloc(k, sizeof(int*)); // k tane alt dizi par�as�n� burada saklad�m
    int* nextIndis = (int*)calloc(k, sizeof(int));// k tane alt diziyi �st dizide birle�tirirken her bir dizinin kac�nc� indisinde kald�g�m� bu dizi ile tuttum.
    int* dimension = (int*)calloc(k, sizeof(int)); // her bir alt dizinin boyutu.
    int i, j,start,end,n;// dongu degiskenleri
    int min, minIndis, mainIndis = left, completed = 0;
    for (i = 0; i < k; i++) {
        start = (i == 0) ? left : midpoints[i - 1] + 1;//her bir alt dizinin baskangic ve bitis noktas�n� burada belirledim.
        end = (i == k - 1) ? right : midpoints[i];
        n = end - start + 1;// her bir alt dizinin boyutunu dimension dizisine att�m
        dimension[i] = n;
        arrays[i] = (int*)calloc(n, sizeof(int));

        for (j = 0; j < n; j++) {
            arrays[i][j] = arr[start + j];// her bir alt diziyi ana diziden al�p buraya yerle�tirdim.
        }
        insertion_sort(arrays[i], n); //her bir alt diziyi kendi icinde insertion sort ile s�ralad�m
    }

    
    while (completed == 0) {//her bir alt dizi �st dizide birle�ene dek dondurdum.
        min = INT_MAX;
        for (i = 0; i < k; i++) {//her bir alt dizinin ilgili indisiini kar��la�t�rarak min eleman� buldum.
            if (nextIndis[i] < dimension[i]) {
                if (arrays[i][nextIndis[i]] < min) {
                    min = arrays[i][nextIndis[i]];
                    minIndis = i;
                }
            }
        }
        if (min != INT_MAX) {//eger hala yerle�ecek eleman varsa min deger bulunmus demektir.
            arr[mainIndis] = min;//ana diziye o degeri yazd�m.
            mainIndis++;
            nextIndis[minIndis]++;
        } else {//yerlesecek eleman kalmad�g�nda buradan donguyu sonland�r�r.
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
@brief s�ralanmak �zere al�nan bir diziyi recursive olarak her ad�mda k e�it par�aya b�ler. durma ko�ulu ise ilgili dizi boyutu < k.
@param array : s�ralanmak istenen dizi.
@param left : dizinin en sol indisi
@param right : dizinin en sag indisi
@param k : k parcaya bolunme i�lemin i�in ilgili k degeri

*/
void mergeSort(int* array, int left, int right, int k) {
    int i,start,end;
    if (right-left+1<=k) return;

    int segmentSize =(right-left+ 1)/ k; // k elemana boldugumde her bir alt parcan�n boyutu burada saklan�r
    int midPoints[k-1];//her bir alt parca�n baslang�c ve biti� noktalar� bu dizide tutulur

    for (i= 0;i< k-1;i++){
        midPoints[i] =left+(i+1)*segmentSize-1;//her bir alt parca�n baslang�c ve biti� noktalar� ilgili indise yerle�tirirlir.
    }

    for (i = 0; i < k; i++) {//dizi k kere mergesort ile b�l�n�r.
        start = (i==0)?left :midPoints[i- 1] +1;
        end = (i== k-1) ? right :midPoints[i];
        mergeSort(array, start, end, k);
    }

    mergeKway(array, midPoints, left, right, k);// daha bolunemeyecek kadar kucuk oldugunda merge fonksyionuna gider.
}
/*
@brief al�nan bir dizinin elemanlar�n� rastgele kar��t�ran fonksiyon
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
@brief istenen n ve k degerleri icin farkl� diziler �retip ilgili dizilerin s�ralanma s�resini ekrana bast�ran main fonksiyon.


*/

int main() {
	
	srand(time(0));
	int* arr; // mergesort i�in dizi a�t�m
	int* arrCheck ; // her k de�eri icin ayn� dizi kullan�lacag�ndan bu diziyi de her seferinde arr i kopyalamak i�in kulland�m
    int n ,i,j,k;//dongu ve boyut degiskenleri
    int random;
    int trash,index=0;//indisler
    double old_time;//zaman degiskenleri
    double time_taken;
    FILE* file = fopen("output.txt", "r");//buldugum sureleri 10 kez cal�st�r�p dosyaya yazmak icin dosya ac�yorum
  
    double times[100];//buldugum eski sureleri okuyup yeni s�reyle toplay�p geri dosyaya yaz�yorum.
    for(i=0;i<6;i++){// 6 farkl� n de�eri icin dongu
    n = 100*(pow(10,i));
    arr = (int*)malloc(n * sizeof(int));
    arrCheck = (int*)calloc(n , sizeof(int));
    
     for (j = 0; j < n;j++) {//diziyi 1 den n e kadar olusturup shuffle ediyorum
        arr[j] = j;
    }shuffle(arr, n);
 
     
    for(k=2;k<=10;k++){//her k degeri ile merge i�lemi i�in bu donguye giriyorum
    for (j = 0; j < n;j++) {
        arrCheck[j] = arr[j];// ana diziyi kopyal�yorum her k de�eri icin ayn� olmas� icin.
    }   
     
        clock_t start_time = clock();// zaman tutmak ad�na clock
    	mergeSort(arrCheck, 0, n - 1, k);
    	clock_t end_time = clock();
		  time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;//gecirilen zaman� hesaplar
		//dosyadan okuma yapmak istenirse bu yorum sat�r� kald�r�l�r.
		    /*old_time =0 ;
		
	        fscanf(file, "%d %d %lf\n", &trash, &trash, &old_time);//dosyadan ilgili k ve n degeri i�in �nceki s�re toplam�n� �eker
            times[index]= time_taken+old_time;//�u anki s�re ile �ncekileri toplar
   
            index++;*/
		printf("MergeSort  k=%d n = %d took %f seconds\n", k,n, time_taken);// ekrana ilgili k ve n de�erinin merge i�lemi i�in gecen s�reyi yazd�r�r
	}
    free(arr);
    free(arrCheck);
	}
	fclose(file);//okuma modunda act�g�m dosyay� kapat�yorum.
	file = fopen("output.txt", "w");//yazma modunda dosyay� tekrar ac�yorum.
  
   n = 10;
   for (i = 0; i < 54; i++) {//6 farkl� n , 9 farkl�  k de�eri icin 54 adet de�er yaz�lcak diziye.
   	if(i%9 == 0){
   		n=n*10;
	   }//e�er dosyaya yazma yapmak istenirse buray� yorum sat�r�ndan kald�r
       // fprintf(file, "%d %d %.6f\n", i%9+2, n, times[i]);//buldugumuz s�releri dosyaya geri yaz�yoruz.
    }
  fclose(file);
    return 0;
} 

