#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define startingBalance 5000 // Kullanicinin baslangictaki bakiyesi. ($)
#define numberOfCoins 5 // Programda kullanilan coin sayisi

// Bu programda kullanilan coin fiyatlari, gercek degerleri yansitmamaktadir. Fiyatlar rastgele olarak belirlenmis ve rastgele olarak degismektedir.


int program_mode = 1; // Bu degiskeni global yapmamizin sebebi fonksiyonlarin icinden bu degiskene ulasabilmemiz icin.

FILE *filep, *filep2, *filep3, *filep4;

/*

filep -> Coinlerin adlarinin bulundugu txt dosyasinin adresini gosterir.
filep2 -> Coinlerin fiyatlarinin bulundugu txt dosyasinin adresini gosterir.
filep3 -> Kullanicida bulunan coin miktarlarinin bulundugu txt dosyasinin adresini gosterir.
filep4 -> Kullanicinin bakiyesinin bulundugu txt dosyasinin adresini gosterir.

*/ 

struct Coin {
	
	char name[20];
	int cost;	
	
}coins[numberOfCoins];

struct User { //*
	
	float userBalance;
	float coinNumbers[numberOfCoins]; // Kullanicida bulunan coin miktarlarini tutan dizi.
	float profitRate; // Kullanicinin kâr oranini tutan degisken.
	
}user;

// Text dosyasindan coin isimlerini okuyup nesnelerimizin icerisine aktaran fonksiyon.
void readNames(struct Coin *coin) {
	
	int i;
	char temp[20];
	filep = fopen("coinNames.txt", "r");
	
	for(i = 0; i < numberOfCoins; i++) {
		
		fscanf(filep, "%s", &temp);
		strcpy(coin->name, temp);
		coin++;
	}
	
	fclose(filep);
}

// Coinlerin fiyatlarini baslangicta atayan fonksiyon.
void setCoinCost(struct Coin *coin) {
	
	int i, temp;
	filep2 = fopen("coinCosts.txt", "r");
	
	for(i = 0; i < numberOfCoins; i++) {
		
		fscanf(filep2, "%d", &coin->cost);
		coin++;
	}
	
	fclose(filep2);
}

// Kullanicidaki coin miktarlarini txt dosyasindan okuyan fonksiyon.
void readCoinNumbers(struct User *user) {
	
	filep3 = fopen("coinNumbers.txt", "r");
	int i;
	
	for(i = 0; i < numberOfCoins; i++) {
		
		fscanf(filep3, "%f", &user->coinNumbers[i]);
	}
	
	fclose(filep3);
}

// Program sonlandirilmadan once kullanicinin sahip oldugu coin sayilarini txt dosyasina yazdiran fonksiyon. Bu sayede kullanici programi tekrar actiginda kaldigi yerden devam edebilecek.
void updateCoinNumbers(struct User *user) {
	
	filep3 = fopen("coinNumbers.txt", "w");
	int i;
	
	for(i = 0; i < numberOfCoins; i++) {
		
		fprintf(filep3, "%f\n", user->coinNumbers[i]);
	}
	
	fclose(filep3);
}

// Program isleyisi suresince fiyatlar degisecegi icin fiyatlari guncelleyen fonksiyon olusturuldu.
void updateCoinCost(struct Coin *coin) {
	
	filep = fopen("coinCosts.txt", "w");
	
	int i;
	
	for(i = 0; i < numberOfCoins; i++) {
		
		fprintf(filep, "%d\n", coin->cost);
		coin++;
	}
	
	fclose(filep);
}

// Kullanicinin bakiyesini txt dosyasindan okuyan fonksiyon.
void readUserBalance(struct User *user) {
	
	filep4 = fopen("userBalance.txt", "r");
	
	fscanf(filep4, "%f", &user->userBalance);
	
	fclose(filep4);
}

// Program sonlandirilmadan once kullanicinin son bakiye miktarini txt dosyasina yazan fonksiyon.
void updateUserBalance(struct User *user) {
	
	filep4 = fopen("userBalance.txt", "w");
	
	fprintf(filep4, "%f", user->userBalance);
	
	fclose(filep4);
}

// Coinlerin isimlerini ve fiyatlarini okuyan fonksiyonlari cagirma.
void readDatas(struct Coin *coin, struct User *user) {
	
	readNames(coin);
	setCoinCost(coin);
	readCoinNumbers(user);
	readUserBalance(user);
}

// Menuyu gosteren fonksiyon.
void showMenu(struct Coin coins[], int size) {
	
	system("CLS");
	int i;
	printf("*************** Kripto Para Simulasyonuna Hos Geldiniz ! ***************\n\n");
	printf("Ayrintili bilgisini goruntulemek istediginiz parayi seciniz:\n");
	
	for(i = 0; i < size; i++) {
		
		printf("%d - %s\n", i + 1, coins[i].name);
		
	}
	printf("\nKazanc durumunuzu goruntulemek icin 'k' tusuna basiniz.\n");
	printf("\nProgrami sonlandirmak icin 'x' tusuna basiniz.");
	printf("\n\nBakiyeniz: %.2f$\n\n", user.userBalance);


}

// Kullanicinin istedigi coine para yatirmasini saglayan fonksiyon. *
void buy(int choice) {
	
	if(user.userBalance == 0) {
		
		printf("Coin alabilmek icin yeterince bakiyeniz bulunmamaktadir. Anasayfaya yonlendiriliyorsunuz ...");
		sleep(3);
		showMenu(coins, numberOfCoins);
		
	}
	
	else {
	
		// choice parametresi kullanicinin sectigi coinin kac numaralý coin oldugunu belirtir. Bu sayede coins dizisinde ve coinNumbers dizisinde o coinin indexine ulasabiliriz.
		float depositBalance, coinNumber;
		printf("Ne kadar para yatirmak istiyorsunuz ? (Bakiyeniz: %f$) : ", user.userBalance);
		scanf("%f", &depositBalance);
		
		while(depositBalance > user.userBalance) {
			
			printf("Girdiginiz miktar bakiyenizden fazla olamaz. (Bakiyeniz: %f || Girilen miktar: %f)\n\nLutfen para miktarini yeniden giriniz: ", user.userBalance, depositBalance);
			scanf("%f", &depositBalance);
		}
		
		coinNumber = depositBalance / coins[choice - 1].cost;
		user.userBalance -= depositBalance;
		user.coinNumbers[choice - 1] += coinNumber;
		printf("%f$ ile %f adet %s satin aldiniz.\n\n", depositBalance, coinNumber, coins[choice - 1].name);
		sleep(4);
	
	}
}

// Kullanicinin sahip oldugu coini istedigi miktarda satabilmesini saglayan fonksiyon. *
void sell(int choice) {
	
	
	if(user.coinNumbers[choice - 1] == 0) {
		
		printf("Bu coinden elinizde hic bulunmadigi icin satma islemini gerceklestiremezsiniz. Anasayfaya yonlendiriliyorsunuz...");
		sleep(3);
		showMenu(coins, numberOfCoins);
	}
	
	else {
	
		printf("\nBu coinden elinizde bulunan adet sayisi: %f", user.coinNumbers[choice - 1]);
		float num;
		printf("\nKac adet satmak istiyorsunuz ?\nAdet giriniz: ");
		scanf("%f", &num);
		
		while(num <= 0) {
			
			printf("Girdiginiz deger 0 veya 0'dan kucuk olamaz.");
			printf("\nSatmak istediginiz adet sayisini tekrar giriniz: ");
			scanf("%f", &num);
		}
		
		if(num > user.coinNumbers[choice - 1]) {
			
			num = user.coinNumbers[choice - 1]; // Eger kullanici elinde bulunan miktardan fazla satmaya calisirsa, elindeki miktarin tamamini satmis olacak.
			
			switch(choice) {
				
				case 1:
					printf("Elinizdeki butun Bitcoinleri sattiniz.\n");
					break;
				
				case 2:
					printf("Elinizdeki butun Ethereum coinleri sattiniz.\n");
					break;
				case 3:
					printf("Elinizdeki butun Dogecoinleri sattiniz.\n");
					break;
				
				case 4:
					printf("Elinizdeki butun Litecoinleri sattiniz.\n");
					break;
					
				case 5:
					printf("Elinizdeki butun Tether coinleri sattiniz.\n");
					break;
			}
		}
		
		user.userBalance += num * coins[choice - 1].cost;
		user.coinNumbers[choice - 1] -= num;
		printf("Satis islemi basariyla gerceklestirildi. Satilan adet: %f | Hesabiniza aktarilan para: %f", num, num * coins[choice - 1].cost);
		sleep(4);
	}
	
}

// Kullanicinin secim yapabilmesini saglayan fonksiyon.
void choiceInput() {
	
	
	char choice;
	
	printf("Seciminizi giriniz: ");
	
	// Kullanici ana menudeyken de coin fiyatlarini degistirmemizi saglayan while dongusu.
	while(!kbhit()) {
		
		changeCosts(coins, numberOfCoins);
		sleep(3);
	}
	
	scanf("\n");
	scanf("%c", &choice);
	
	
	check:
	if(choice == 'x') {
		
		printf("Program sonlandirildi.");
		program_mode = 0; // Bu sayede program while dongusu icerisinden cikar ve program sonlanir.
	}
	
	else if(choice == '1') {
		
		// atoi fonksiyonu stdlib kutuphanesinin icinde olan bir fonksiyondur. String degeri int degere cevirmeye yarar.
		// int degere cevirmemizin sebebi coins dizisinde secilen coinin indexine erisebilmek istememiz.
		system("CLS");
		choice = atoi(&choice); 
		printf("%d. COININ AYRINTILI BILGILERI GORUNTULENIYOR:\n", choice);
		sleep(1); // Programi 1 saniye bekletir.
	}
	
	else if(choice == '2') {
		
		system("CLS");
		choice = atoi(&choice);
		printf("%d. COININ AYRINTILI BILGILERI GORUNTULENIYOR:\n", choice);
		sleep(1);
	}
	
	else if(choice == '3') {
		
		system("CLS");
		choice = atoi(&choice);
		printf("%d. COININ AYRINTILI BILGILERI GORUNTULENIYOR:\n", choice);
		sleep(1);
	}
	
	else if(choice == '4') {
		
		system("CLS");
		choice = atoi(&choice);
		printf("%d. COININ AYRINTILI BILGILERI GORUNTULENIYOR:\n", choice);
		sleep(1);
	}
	
	else if(choice == '5') {
		
		system("CLS");
		choice = atoi(&choice);
		printf("%d. COININ AYRINTILI BILGILERI GORUNTULENIYOR:\n", choice);
		sleep(1);
	}
	
	else if(choice == 'k') {
		
		system("CLS");
		printf("********** KAZANC DURUMUNUZ GORUNTULENIYOR **********\n\n");
		sleep(1);
		calculateProfitRate();
	}
	
	else {
		
		printf("Gecersiz secim yaptiniz. Seciminizi tekrar giriniz: ");
		scanf("\n");
		scanf("%c", &choice);
		goto check; // Tekrardan secim girildikten sonra kontrol yapmak icin 104. satira yonlendiriyoruz programi. Bu sayede secim gecersiz oldugu surece kullanicinin secim yapmasi gerekecek.
	}
	
	if(choice != 'x' && choice != 'k')
		coinDetails(choice);
}

// Kullanicinin kâr oranýný hesaplayan fonksiyon. Kâr oranini hesaplar ve geri dondurur.
void calculateProfitRate() {
	
	int i;
	float sum = user.userBalance;
	float profitRate;
	
	for(i = 0; i < numberOfCoins; i++) {
		
		sum += user.coinNumbers[i] * coins[i].cost;
		
	}
	
	profitRate = ((sum - startingBalance) / startingBalance) * 100;
	
	printf("Kazanc oraniniz: %%%.2f\n\n", profitRate);
	
	sleep(2); // Programi 2 saniye bekletir.
}

// Coinlerin fiyatlarini prýgram süresince (1 - 1000) arasinda rastgele olarak degistiren fonksiyon.
void changeCosts(struct Coin coins[], int size) {
	
	srand(time(0));
	
	int i, value, plusOrMinus; // plusOrMinus degiskenine 0 ile 1 arasinda deger atanacak. Bu sayede %50 ihtimal ile fiyat azalacak, %50 ihtimal ile fiyat artacak.
	
	for(i = 0; i < size; i++) {
		
		value = 1 + rand() % 1001; 
		plusOrMinus = rand() % 2; 
		
		if(plusOrMinus == 1) coins[i].cost += value;
			
		else {
			
			if(coins[i].cost - value > 0) 
				coins[i].cost -= value;
			
		}
	}
}

// Coinlerin detayli bilgilerini gosteren ve coinlerle ilgili islem yapmamizi saglayan fonksiyon. *
void coinDetails(int choice) {
	
	char input;
	
	printf("--------------------------------------------\nAdi: %s\nFiyati: %d$\nElinizde bulunan miktar: %.2f adet\n\n",coins[choice - 1].name, coins[choice - 1].cost, user.coinNumbers[choice - 1]);
	printf("Yapmak istediginiz islemi seciniz:\n1- Alim\n2- Satim\n3- Geri\n4- Cikis\nSeciminizi giriniz: ");
	sleep(1);
	
	while(!kbhit()) {
		
		 // kbhit fonksiyonu conio.h kütüphanesinde bulunan bir fonksiyondur. Klavyeden herhangi bir tuþa basýldýðýnda true deðeri döndürür.
			
		system("cls");
		printf("--------------------------------------------\nAdi: %s\nFiyati: %d$\nElinizde bulunan miktar: %.2f adet\n\n",coins[choice - 1].name, coins[choice - 1].cost, user.coinNumbers[choice - 1]);
		printf("Yapmak istediginiz islemi seciniz:\n1- Alim\n2- Satim\n3- Geri\n4- Cikis\nSeciminizi giriniz: ");
		changeCosts(coins, numberOfCoins);
		sleep(3);
			
	}
	
	scanf("\n");
	scanf("%c", &input);
	
	check:
	if(input == '4') {
		
		printf("Program sonlandirildi.");
		program_mode = 0; // Programi sonlandirmak icin.
	}
	
	else if(input == '1') {
		
		buy(choice);
	}
	
	else if(input == '2') {
		
		sell(choice);
	}
	
	else if(input == '3') {
		
		printf("\n");
		showMenu(coins, numberOfCoins); // Kullanici geri gitmek istedigi icin ana menu ekranini yazdiran fonksiyonu tekrar cagiriyoruz.
		choiceInput(); // Kullanicinin secim yapmasini saglayan fonksiyonu cagiriyoruz.
	}
	
	else {
		
		printf("Gecersiz karakter girdiniz. Lutfen seciminizi tekrar giriniz: ");
		scanf("\n");
		scanf("%c", &input);
		goto check; // Kullanici gecersiz karakter girdikten sonra alinan inputu tekrardan kontrol asamasindan gecirmek icin programi 115. satira yonlendirdik.
	}
	
}

int main() {
	
	// Coin yapisindan obje tutan pointer olusturuldu.
	struct Coin *ptrArray = coins; // ptrArray pointerý Coin yapisina ait coins dizisinin baslangic adresini tutuyor.
	// User yapisindan obje tutan pointer olusturuldu ve user objesinin adresini gosterecek sekilde ayarlandi.
	struct User *usrPtr;
	usrPtr = &user;
	readDatas(ptrArray, usrPtr);
	
	while(program_mode) {
		
		showMenu(coins, numberOfCoins);
		choiceInput();
		
	}
	
	// Program sonlandirilmadan once programin son halindeki veriler tekrardan txt dosyalarina yazdirilir.
	// Bu sayede program kaldigi yerden devam etmis olur.
	
	updateCoinCost(ptrArray);
	updateCoinNumbers(usrPtr);
	updateUserBalance(usrPtr);
	
	return 0;
}
