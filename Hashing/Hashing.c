#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_LINE_SIZE 35 //maksimum satýr uzunlugu
#define MAX_VARIABLE_PER_LINE 30 // bir satirdaki maksimum degisken sayisi
#define MAX_VARIABLE 50 // maksimum tanýmlanan degisken sayýsý
#define MAX_USAGES  100 //maksimum degisken kullaným sayisi


typedef struct variable{//her bir degiskenin tipi ve ismi icin struct yapýsý.
	char* type ;
	char* name;
}variable;

/*
@brief : verilen bir satýrdaki degisken isimlerini arar ve döndürür
@param line : arama yapýlacak string
@param startAdr : aramaya baslanacak indis
@param size : döndürülerecek dizinin boyutu
@return bulunan tum degisken isimleri bir dizide döndürülür.
*/
char** findVariableName(char* line, int startAdr, int* size) {
    int k = startAdr; 
    char** variables = (char**)calloc(MAX_VARIABLE_PER_LINE, sizeof(char*));
    if (variables == NULL) {
        perror("Bellek tahsisi basarisiz");
        return NULL;
    }

    int num_of_variables = 0;

    //ssatýr boyunca gezin
    while (line[k] != '\0') {
        // `_` karakterini kontrol et
        if (line[k] == '_') {
            int startVar = k;
            //deðisken adininsonunu bul
            while ((line[k] >= 'a'&&line[k] <= 'z') ||
                   (line[k]>='A' && line[k] <= 'Z') ||
                   (line[k] == '_')||
                   (line[k] >='0' && line[k] <= '9')) {
                k++; // degisken ismi bitene kadar k yý arrttýr.
            }

            int varLength = k - startVar; //degiskenin boyutunu bul

            // Gecerli bir deðisken adi bulunduysa buraya gir.
            if (varLength > 0) {
                char* variableName = (char*)calloc(varLength + 1, sizeof(char));
                if (variableName == NULL) {
                    perror("Bellek tahsisi basarisiz");
                    return NULL;
                }
                strncpy(variableName, &line[startVar], varLength);
                variableName[varLength] = '\0'; 

                //printf("Degisken adi bulundu: %s\n", variableName);

                variables[num_of_variables] = variableName;
                num_of_variables++;

                // Fazla deðisken kontrolü
                if (num_of_variables >= MAX_VARIABLE_PER_LINE) {
                    printf("Maksimum degisken sayisina ulasildi\n");
                    k = strlen(line); 
                }
            }
        } else {
            
            k++;
        }
    }

    *size = num_of_variables; // Bulunan deðisken sayýsýný dondurmek icin.
    return variables;
}

/*
@brief : verilen bir satýrdaki ilgili patterni arayýp adresini doner
@param line : arama yapýlacak string
@param pattern : aranacak pattern
@return eger pattern varsa baslangic indisini, yoksa -1 doner.
*/
int findPattern(char*line,char*pattern){
	int lenPat = strlen(pattern);
	int lenStr = strlen(line);
	int i,j;
	for (i = 0;i<=lenStr -lenPat;i++) {
        j = 0;
        while((j<lenPat)&&(line[i+j]==pattern[j])){
        	j++;
		}
		if(j == lenPat){
			return i;
		}
	}

return -1;
}
/*
@brief : verilen bir satýrdaki degisken tanimlamalarini kontrol eder.
@param line : arama yapýlacak string
@param variables : bulunan degiskenler bu struct dizisine atýlýr.
@param size_of_variables : bulunan degiskenlerin sayisi.
@return o satýrda bulunan toplam degisken sayisini dondurur.
*/
int checkDeclarations(char* line,variable*variables,int* size_of_variables){
	int i = 0 ;
	int startAdr;
	char** variableNames;	
	variable temp_variable;
	int* size;
	*size = 0;
	int totalSize=0;
	
		startAdr = findPattern(line,"int"); // eger int tanimlamasi yakalanýrsa bu if ' e girer.
		if(startAdr != -1){
			variableNames = findVariableName(line,startAdr,size); // int degisken tipindeki degisken isimlerini arar.
			temp_variable.type = "int";
			for(i = 0;i < (*size);i++){  //bi onceki fonksiyon ile kac tane variable bulunduysa hepsini diziye atar.
				temp_variable.name =  variableNames[i];
				variables[*size_of_variables] = temp_variable;
				(*size_of_variables)++;
			}
		}
		totalSize= totalSize+(*size); // bu satýrda bulunan degisken sayisini toplar.
		*size = 0;
		//char ve float tipleri icin de yukarýdaki if blogunda yapýlan islerin aynilari yapilir.
		startAdr = findPattern(line,"char");
		if(startAdr != -1){
				variableNames = findVariableName(line,startAdr,size);
				temp_variable.type = "char";
			for(i = 0;i < (*size);i++){
				temp_variable.name =  variableNames[i];
				variables[*size_of_variables] = temp_variable;
					(*size_of_variables)++;
			}
		}
		
		totalSize= totalSize+(*size);
		*size = 0;	
		startAdr = findPattern(line,"float");
		if(startAdr != -1){
				variableNames = findVariableName(line,startAdr,size);
				temp_variable.type = "float";
			for(i = 0;i < (*size);i++){
				temp_variable.name =  variableNames[i];
				variables[*size_of_variables] = temp_variable;
					(*size_of_variables)++;
			}
		}
		
			totalSize= totalSize+(*size);
			return totalSize;
}
/*
@brief : verilen bir satýrdaki degisken kullanimlarini kontrol eder.
@param line : arama yapýlacak string
@param names : bulunan degisken isimleri bu dizi ile dondurulur
@param names_size : bulunan degiskenlerin sayisi.

*/
void checkUsages(char*line,char** names,int *names_size){
	if (findPattern(line, "int") != -1) return;
    if (findPattern(line, "char") != -1) return;
    if (findPattern(line, "float") != -1) return;
    //eger o satirda tanimlama yapilmiyosa buraya gelip devam eder.
	char**namesPerLine ;
	int size = 0 ;	
	namesPerLine = findVariableName(line,0,&size); // o satirdaki degiskenleri bulup dizi dondurur
	int i ;
	for(i = 0;i<size;i++){
		names[*names_size+i] = namesPerLine[i]; // butun degiskenleri names dizisine eklenir.
	}
	*names_size = *names_size + size;
}
/*
@brief : verilen bir dosyadan okuma yapar. dosyadaki degisken tanimlamarini,degisken kullanýmlarýný ve her ikisinin de sayilarini bulup döndürür.
@param file : ilgili dosya
@param number_of_variables : tanimlanan degisken sayisi.
@param usages : kullanýlan degiskenlerin tutuldugu dizi.
@param number_of_usages : usages dizisinin boyutu
@return tanýmlanan degiskenlerin isim ve tiplerinin tutuldugu bir struct dizisi dondurur.
*/
variable* readFromFile(FILE*file,int*number_of_variables,char**usages,int*number_of_usages){
	int totalVariables = 0;
	char*line = (char*)calloc(MAX_LINE_SIZE,sizeof(char));
	variable*variables = (variable*)calloc(MAX_VARIABLE,sizeof(variable));//variables dizisinde kodda declare edilen degiskenler ve tipleri var
	char**names = (char**)calloc(MAX_USAGES,sizeof(char*));// names dizisinde kodda kullanýlan degisken isimleri var
	int size_of_variables = 0;
	int names_size = 0;
	int i;
	fgets(line,MAX_LINE_SIZE,file);
	while(fgets(line,MAX_LINE_SIZE,file) != NULL){ 
		printf("%s",line);
		totalVariables += checkDeclarations(line,variables,&size_of_variables); //declarations control
		checkUsages(line,names,&names_size);  //usages kontrol
	}
	*number_of_usages = names_size;
 	for(i = 0;i<names_size;i++){
 		usages[i] = names[i]; // usages dizisini disari dondermek icin burada names dizisi kopyalaniyor.
	 }
	*number_of_variables = size_of_variables;

	return variables;
}

/*
@brief : verilen bir sayinin asalligini kontrol eder.
@param reference : kontrol edilecek sayi
@return asal olup olmadigi bilgisi doner (0-1)
*/
int checkPrime(int reference){
	int i =2;
	while(i<=(reference/2)){
		if((reference%i) ==0){
			return 0;
		}else{
			i++;
		}
	}
	
	return 1;
}
/*
@brief : verilen bir sayinin 2 katindan buyuk ilk asal sayiyi bulup dondurur
@param reference : kontrol edilecek sayi
@return ilgili sayi.
*/
int findPrimeNumber(int reference){
	reference = reference*2;
	int prime = 0;
	while(prime==0){
		if(checkPrime(reference)){
			prime =1;
		}else{
			reference++;
		}
	}
	return reference;
	
}
/*
@brief : verilen boyuta gore bir hashtable olusturup dondurur
@param size : hashtable boyutu.
@return hashtable dizisi
*/
variable* initializeHashTable(int size){
	variable* hashTable = (variable*)calloc(size,sizeof(variable));
	int i ;
	for(i = 0 ; i<size ; i++){
		hashTable[i].name = NULL;
	}
	return hashTable;
}
/*
@brief : verilen bir stringe horners method uygulanýr ve key degeri dondurulur.
@param name : ilgili string
@return key degeri dondurulur.
*/
int hornersMethod(char*name){
	int r = 31;
	int len = strlen(name);
	int key = 0;
	int i ;
	for(i = 0; i<len;i++){
		key += pow(r,len-(i+1))*name[i];
	}
	return key;
}
/*
@brief : hashlemek icin kullanýlan hash fonksiyonu
@param  key : yerlesecek sayi.
@param  i : hash2 icin indis
@param  tableSize : tablo boyutu
@return index degeri doner
*/
int hash(int key,int i, int tableSize){
	return (hash1(key,tableSize)+i*hash2(key,tableSize))%tableSize;
}
/*
@brief : hashlemek icin kullanýlan hash1 fonksiyonu
@param  key : yerlesecek sayi.
@param  tableSize : tablo boyutu
@return index degeri doner
*/
int hash1(int key,int tableSize){
	return key%tableSize;
}
/*
@brief : hashlemek icin kullanýlan hash2 fonksiyonu
@param  key : yerlesecek sayi.
@param  tableSize : tablo boyutu
@return index degeri doner
*/
int hash2(int key,int tableSize){
	return 1+key%(tableSize-3);//m2 = m-3
}
/*
@brief : verilen bir isim ve tipi hash dizisine yerlestirir
@param  name : degisken ismi.
@param  type : degisken tipi.
@param  tableSize : tablo boyutu.
@param  hashTable : tablo 
@param debug : hangi modda calistigi bilgisi (0-1)
@return insert islemi basariyla tamamlandiysa 1 doner.
*/
int insert(char*name,char*type,int tableSize,variable*hashTable,int debug){
	int key = hornersMethod(name);
	int i = 0;
	int index = hash(key,i,tableSize);
	if(debug){
		printf("Insertion for '%s' --> first index = %d ",name,index);
	}
	//printf("\n%d",index);
	//printf("\n%s",hashTable[index].name);
	while((i<tableSize)&&(hashTable[index].name!=NULL)&&strcmp(hashTable[index].name,name)){
		i++;
		index = hash(key,i,tableSize);
	}
	if(debug){
		if((hashTable[index].name!=NULL)){
			printf(" --> final index = -1\n");
		}else{
			printf(" --> final index = %d \n",index);
		}
	}
	if(i==tableSize){
		printf("Tablo dolu\n");//hic bir zaman gerceklesmemeli.
	}else if(hashTable[index].name==NULL){
		hashTable[index].name = name;
		hashTable[index].type=type;
		return 1 ; // success
	}else{
		printf("ERROR : %s is already declared.\n",name);
		
	  	return 0 ; //unsuccess
	}
}
/*
@brief : verilen bir isim hashTable dizisinde var mý diye kontrol eder.
@param  name : degisken ismi.
@param  hashTable : tablo
@param  tableSize : tablo boyutu.
@return var ise 1 yok ise 0 doner.
*/
int lookUp(char*name,variable*hashTable,int tableSize){
	int key = hornersMethod(name);
	int i = 0;
	int index = hash(key,i,tableSize);
	while((i<tableSize)&&(hashTable[index].name!=NULL)&&strcmp(hashTable[index].name,name)){
		i++;
		index = hash(key,i,tableSize);
	}
	if(i==tableSize){
		//printf("Tablo dolu\n");//hic bir zaman gerceklesmemeli.
	}else if(hashTable[index].name==NULL){
		//ilgili variable tabloda yok
		return 0 ;
	}else{
      //printf("Bu degisken  tabloda mevcut.\n");
	  	return 1 ; 
	}
}
/*
@brief : kullanýlan degiskenler tabloda var mý yok mu diye kontrol edip hata mesajý basar.
@param  tableSize : tablo boyutu.
@param  hashTable : tablo 
@param  usages : kullanýlan degiskenlerin isimlerinin dizisi
@param  number_of_usages : usages dizisi boyutu
@return insert islemi basariyla tamamlandiysa 1 doner.
*/
void checkLookUp(variable*hashTable,char**usages,int tableSize,int number_of_usages){
	int i ,exist;
	
	for(i = 0 ; i < number_of_usages;i++){
		exist = lookUp(usages[i],hashTable,tableSize);
		if(!exist){
			printf("ERROR : %s is not declared\n",usages[i]);
		}
	}
}
/*
@brief : tabloyu verilen dizilere gore doldurur
@param  tableSize : tablo boyutu.
@param  hashTable : tablo 
@param  variables : kullanýlan degiskenlerin  dizisi
@param  number_of_variables : variables dizisi boyutu
@param  debug : hangi modda calistigi bilgisi 0 - 1
*/
void completeTheTable(variable*variables,int tableSize,int number_of_variables,variable*hashTable,int debug){
	int i ;
	printf("\nInsertions and  ERRORS :\n");
	for(i = 0 ;i <number_of_variables;i++){
		insert(variables[i].name,variables[i].type,tableSize,hashTable,debug);
	}
}

//@brief tablo icerigini yazdirir.0
void printTableStatus(int number_of_variables,int tableSize,variable*hashTable){
	printf("\nTable Status : \n");
	int i ; 
	printf("Number of Declared Variables : %d\n",number_of_variables);
	printf("Size of HashTable : %d\n",tableSize);
	
	printf("\nHashTable:\n");
	for(i=0;i<tableSize;i++){
	 	printf("hashTable[%-2d].type = %-7s -- hashTable[%d].name =%-15s  \n",i,hashTable[i].type,i,hashTable[i].name);
	}
}
int main(){
	FILE*file;
	char*fileName =(char*)calloc(15,sizeof(char)) ;
	variable*variables; //kodda declare edilen degisken ve tiplerini tutan dizi
	char**usages=(char**)calloc(MAX_USAGES,sizeof(char*)); //kodda kullanýlan degiskenlerin isimleri.
	int i;
    int number_of_variables;//declare edilen degisken sayýsý
    int number_of_usages;	//kullanýlan degisken sayýsý
    int tableSize;
    int debug = 1;
	variable* hashTable;
	printf("Dosya ismi giriniz : ");
	scanf("%s",fileName);
	file = fopen(fileName,"r");
	if (file == NULL) {
        perror("Dosya acilamadi");
        return 1;
    }
    printf("Debug mod icin 1, Normal mod icin 0 giriniz.",debug);
    scanf("%d",&debug);
    	
	variables = readFromFile(file,&number_of_variables,usages,&number_of_usages);
    tableSize = findPrimeNumber(number_of_variables);
    hashTable = initializeHashTable(tableSize);
    completeTheTable(variables,tableSize,number_of_variables,hashTable,debug);
	//bu noktada  variables dizisinde declare edilen degiskenler ve tipleri var
    //			  usages dizisinde kullanýlan degisken isimleri var
    //            hashtable dizisinde hash fonksiyonlarý ile yerlestirilen degisken tipleri ve isimleri var.
	checkLookUp(hashTable,usages,tableSize,number_of_usages);
	if(debug){
		printTableStatus(number_of_variables,tableSize,hashTable);
	}
   
	return 0;
}
