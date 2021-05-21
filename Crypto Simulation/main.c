// Yazdigimiz fonksiyonlari iceren header dosyasinin projeye dahil edilmesi.
#include "functions.h"

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
