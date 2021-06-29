#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct infopaket{
	char namapengirim[100];
	char asal[100];
	char teleponPengirim[100];
	char namapenerima[100];
	char tujuan[100];
	char teleponPenerima[100];
	char status[50][100];
	int resi;
	float beratpaket;
	char waktu[50][100];
};

void loading(),Garis(int n),gotoxy(int, int);;
void menu(struct infopaket *packages,int*,int*);
void mainMenu();
void newPackage(struct infopaket *packages,int*,int*);
void displayPackages(struct infopaket *packages, int*,int*);
void validasiData();
void nonValidAction();
void statusUpdate(struct infopaket *packages, int*,int*);
void deleteData(struct infopaket *packages, int*,int*);
void pilihanDatabases();
void pilihanMelanjutkan();
void displaySearching();
void searchData(struct infopaket *packages, int*,int*);
void searchingNama(struct infopaket *packages, int*,int*);
void searchingAsal(struct infopaket *packages, int*,int*);
void searchingTujuan(struct infopaket *packages, int*,int*);
void searchingResi(struct infopaket *packages, int*,int*);
void detailedData(struct infopaket *packages, int*,int*);

/*initiate setCoord*/
COORD setCoord={};

int main(){
	struct infopaket *packages;
	int jumlahPaket = 0,*stat;
	
	//Buat space kosong mengisi packages
	packages = (struct infopaket*) malloc (100*sizeof(struct infopaket));
	//Buat space kosong untuk status
	stat = (int*) calloc (100,sizeof(int));
	if(stat == NULL){
		printf("Error!!! memory not allocated.");
		exit(0);
	}
	
	//menampilkan loading
	loading();
	
	//semua menu menu pada program ini
	menu(packages,&jumlahPaket,stat);
	
	//tampilan program selesai
	system("cls");
	printf("\n\t=========================================");
	printf("\n\tProgram Selesai, Terimakasih\n\n\tCreated by:\n\tThariq Hadyan 1906354311\n\tFerdinand Daniel Soebarkah 1906354476");
	printf("\n\t=========================================");
	free(stat);
	free(packages);
	return 0;
}

//Fungsi Goto
void gotoxy(int x , int y){
    setCoord.X=x;
    setCoord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), setCoord);
}

//Fungsi menampilkan loading awal
void loading(){
    int p,r,q;
    
    printf("\t---------------------------------------\n");
	printf("\t| ==== PROGRAM DATABASE JADI.ADA ==== |\n");
	printf("\t---------------------------------------\n");
    printf("\n\n\tLoading Database Please Wait\n");    
    /*printing loading bar*/
    gotoxy(8,6);
    for(r=1;r<=28;r++){
        for(q=0;q<=50000000;q++);
        printf("%c",221);
        if(p<1){
        	gotoxy(8,12);
    		printf("Tips: Program ini tidak menentukan harga, hanya database\n\tdikarenakan penentuan harga paket tergantung jarak,\n\tsehingga sulit agar mendapat jarak yang presisi");
    		p++;
    		gotoxy(9,6);
		}
    };
}

//Fungsi menampilkan semua menu pada program
void menu(struct infopaket *packages,int *jumlahPaket,int *stat){
	struct infopaket add;
	int i,j,k=0,l,len=0;
	char pos,temp;
	
	system("cls");
	printf("\t\t\t ==== PROGRAM DATABASE JADI.ADA ====  \n");
	
	FILE *database;
	FILE *tempfile;
	
	tempfile = fopen("tempfile.txt","w");
	database = fopen("database.txt", "r");
	if(database==NULL)
    {
        printf("\terror: can't read file\nBuatlah file database.txt dalam folder program untuk menambahkan dummy\n\n\tTekan enter untuk melanjutkan program tanpa data dari file database . . .\n");
        getch();
    }
   
	l = *jumlahPaket;
    
	while(fread(&add, sizeof(add), 1, database)==1){
		*(packages+l) = add;
		k=0;
		len=0;
		while(strlen(add.waktu[k]) != 0){
			len += strlen(add.waktu[k])/strlen(add.waktu[k]);
			k++;
		}
		*(stat+l)=len-1;
    	l++;
	}
	fclose(tempfile);
	fclose(database);
	
	*jumlahPaket = l;
	/*Display menu options*/  
	mainMenu();
	scanf("%c",&pos);
	    	        
    /*Posisi untuk membuka fungsi lainnya*/
    while(pos != 48){
    	if(pos == 49){
    		system("cls");
    		//mengisi paket baru
    		newPackage(packages,jumlahPaket,stat);
    		printf("\n\n\n\t");
    		system("cls");
		}else if(pos == 50){
			system("cls");
			//memperbarui status
			statusUpdate(packages, jumlahPaket,stat);
    		system("cls");
		}else if(pos == 51){
			system("cls");
			//menampilkan paket paket
			displayPackages(packages,jumlahPaket,stat);
		}else if(pos == 52){
			system("cls");
			printf("\n\t");
			Garis(62);
			printf("\n\t|                                                            |");
			printf("\n\t|                   Bantuan Perintah Utama                   |");
			printf("\n\t|                                                            |");
			printf("\n\t");
			Garis(62);
			printf("\n\t|Selamat Datang di program pengiriman paket JADI.ADA!        |");
			printf("\n\t|Program tidak menentukan harga paket,dikarenakan hanya      |");
			printf("\n\t|database saja!                                              |");
			printf("\n\t|                                                            |");
			printf("\n\t|Silahkan tekan 1 untuk menginput pengiriman baru            |");
			printf("\n\t|Anda akan memasukkan beberapa data, setelah itu anda        |");
			printf("\n\t|akan melihat data untuk validasi, bila data sudah benar     |");
			printf("\n\t|akan ke menu utama, jika belum anda akan diminta data       |");
			printf("\n\t|mana yang belum tervalidasi                                 |");
			printf("\n\t|                                                            |");
			printf("\n\t|Silahkan tekan 2 untuk memperbarui status/lokasi paket,     |");
			printf("\n\t|Setiap status/lokasi paket diperbarui, waktu paket akan     |");
			printf("\n\t|terbaru sendirinya. Apabila status sudah 'terkirim' atau    |");
			printf("\n\t|'Terkirim',status tidak akan bisa diubah lagi!              |");
			printf("\n\t|                                                            |");
			printf("\n\t|Silahkan tekan 3 untuk melihat database semua paket,        |");
			printf("\n\t|Database ini berisi semua data paket yang sudah             |");
			printf("\n\t|terkirim maupun belum dikirim                               |");
			printf("\n\t|Pengguna juga dapat melakukan searching, delete,            |");
			printf("\n\t|dan melihat detail perjalanan dari paket                    |");
			printf("\n\t|                                                            |");
			printf("\n\t");
			Garis(62);
			printf("\n\n\n\t");
    		system("pause");
    		system("cls");
		} else{
			system("cls");
			printf("\n\tError! Input salah\n");
		}
		printf("\t\t\t---------------------------------------\n");
		printf("\t\t\t| ==== PROGRAM DATABASE JADI.ADA ==== |\n");
		printf("\t\t\t---------------------------------------\n");
		mainMenu();
		scanf("%c",&temp);
		scanf("%c",&pos);
	}

}
//Fungsi untuk mendisplay menu
void mainMenu(){
	printf("\n\tPilihan Menu Awal");
	printf("\n\t-----------------------------------------");
   	printf("\n\t|TEKAN|     UNTUK                       |  ");
   	printf("\n\t-----------------------------------------");
   	printf("\n\t|  1  |Masukkan Paket baru              |  ");
   	printf("\n\t|  2  |Perbarui Status Paket            |  ");
   	printf("\n\t|  3  |Lihat/Delete Database            |  ");
   	printf("\n\t|  4  |Bantuan                          |  ");
  	printf("\n\t|  0  |EXIT                             |  ");
   	printf("\n\t-----------------------------------------\n\t=> ");
}
//Fungsi untuk menambahkan paket baru
void newPackage(struct infopaket *packages, int *jumlahPaket,int *stats){
	struct infopaket add;
	int i,j,k,count = 0,stat=0;
	char validation, change;
	char str[100]={0};
	
	//Membuat waktu secara real time
	time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
	char temp;
	i = *jumlahPaket;
	*(stats + i) = 0;
	k = *(stats+i);
	//Membuka file database
	FILE *database;
	FILE *tempfile;
	tempfile = fopen("tempfile.txt","w");
	database = fopen("database.txt","a");
	if(database == 0)database = fopen("database.txt","w");

	printf("\t\tMEMASUKKAN DATA BARU");
	printf("\n");
	Garis(120);
	
	//Menginput data penerima dan pengirim
	printf("\n\tMasukkan nama pengirim\t\t: ");
	scanf("%c",&temp);
	scanf("%[^\n]s",(packages+i)->namapengirim);
	
	printf("\tMasukkan alamat pengirim\t: ");
	scanf("%c",&temp);
	scanf("%[^\n]s",(packages+i)->asal);
	
	printf("\tNomor telepon pengirim\t\t: ");
	scanf("%c",&temp);
	gets(str);
	for(j=0;j<strlen(str);j++){
        if(str[j] >= 48 && str[j] <= 57){
            count++;
        }
    }
    while(count != strlen(str)){
    	printf("\n\t\tInput telepon harus nomor semua!\n");
    	printf("\tNomor telepon pengirim\t\t: ");
		scanf("%c",&temp);
		scanf("%s",str);
		count=0;
		stat=1;
		for(j=0;j<strlen(str);j++){
	        if(str[j] >= 48 && str[j] <= 57){
	            count++;
	        }
	    }
	}
	count = 0;
	strcpy((packages+i)->teleponPengirim,str);
	
	if(stat){
		printf("\tMasukkan nama penerima\t\t: ");
		scanf("%c",&temp);
		scanf("%[^\n]s",(packages+i)->namapenerima);
	}else{
		printf("\tMasukkan nama penerima\t\t: ");
		scanf("%[^\n]s",(packages+i)->namapenerima);
	}
	printf("\tMasukkan alamat penerima\t: ");
	scanf("%c",&temp);
	scanf("%[^\n]s",(packages+i)->tujuan);
	
	printf("\tNomor telepon penerima\t\t: ");
	scanf("%c",&temp);
	gets(str);
	for(j=0;j<strlen(str);j++){
        if(str[j] >= 48 && str[j] <= 57){
            count++;
        }
    }
    while(count != strlen(str)){
    	printf("\n\tInput telepon harus nomor semua!\n\n");
    	printf("\tNomor telepon penerima\t\t: ");
		scanf("%c",&temp);
		scanf("%s",str);
		count=0;
		for(j=0;j<strlen(str);j++){
	        if(str[j] >= 48 && str[j] <= 57){
	            count++;
	        }
	    }
	}
	count = 0;
	strcpy((packages+i)->teleponPenerima,str);
	
	strcpy((packages+i)->status[k],"Menunggu Kurir");
	
	(packages+i)->resi = 200+i;
	
	printf("\tBerat paket\t\t\t: ");
	scanf("%f",&(packages+i)->beratpaket);
	
	strcpy((packages+i)->waktu[k],time_str);
	
	//Menanyakan apakah data sudah valid atau belum
	do{
		printf("\n\t");
		Garis(110);
		printf("\n\t\t==VALIDASI PAKET==");
		printf("\n\t\t------------------");
		printf("\n\tWaktu dan Tanggal\t: %s",(packages+i)->waktu[k]);
		printf("\n\tNo.Resi\t\t\t: %d",(packages+i)->resi);
		printf("\n\tNama Pengirim\t\t: %s",(packages+i)->namapengirim);
		printf("\n\tAsal Paket\t\t: %s",(packages+i)->asal);
		printf("\n\tNo.Telp Pengirim\t: %s",(packages+i)->teleponPengirim);
		printf("\n\tNama Penerima\t\t: %s",(packages+i)->namapenerima);
		printf("\n\tTujuan Paket\t\t: %s",(packages+i)->tujuan);
		printf("\n\tNo.Telp Penerima\t: %s",(packages+i)->teleponPenerima);
		printf("\n\tBerat Paket\t\t: %.2f kg",(packages+i)->beratpaket);
		printf("\n\tStatus Paket\t\t: %s",(packages+i)->status[k]);
		printf("\n\t");
		Garis(110);
		validasiData();
		scanf("%c",&temp);
		scanf("%c",&validation);
		while(validation != 49 && validation != 48){
		   	printf("\n\tInput salah, hanya boleh 0 atau 1 => ");
		   	scanf("%c", &validation);
		}
		if(validation == 48){
			//Tampilan Data Apa yang akan diubah
			nonValidAction();
			scanf("%c",&temp);
			scanf("%c",&change);
			while(change != 49 && change != 50 && change != 51 && change != 52 && change != 53 && change != 54 && change != 55){
				printf("\n\tInput invalid! Masukkan kembali => ");
				scanf("%c",&temp);
				scanf("%c",&change);
			}
			if(change == 49){
				printf("\n\n\tMasukkan nama pengirim\t\t: ");
				scanf("%c",&temp);
				scanf("%[^\n]s",(packages+i)->namapengirim);
				printf("\tData baru nama pengirim\t: %s",(packages+i)->namapengirim);
			}else if(change == 50){
				printf("\n\n\tMasukkan alamat pengirim\t\t: ");
				scanf("%c",&temp);
				scanf("%[^\n]s",(packages+i)->asal);
				printf("\tData baru alamat pengirim\t: %s",(packages+i)->asal);
			}else if(change == 51){
				printf("\tNomor telepon pengirim\t\t: ");
				scanf("%c",&temp);
				gets(str);
				for(j=0;j<strlen(str);j++){
			        if(str[j] >= 48 && str[j] <= 57){
			            count++;
			        }
			    }
			    while(count != strlen(str)){
			    	printf("\n\t\tInput telepon harus nomor semua!\n");
			    	printf("\tNomor telepon pengirim\t\t: ");
					scanf("%c",&temp);
					scanf("%s",str);
					count=0;
					for(j=0;j<strlen(str);j++){
				        if(str[j] >= 48 && str[j] <= 57){
				            count++;
				        }
				    }
				}
				count = 0;
				strcpy((packages+i)->teleponPengirim,str);
				printf("\tData baru no.telp pengirim\t: %s",(packages+i)->teleponPengirim);
			}else if(change == 52){
				printf("\n\n\tMasukkan nama penerima\t\t: ");
				scanf("%c",&temp);
				scanf("%[^\n]s",(packages+i)->namapenerima);
				printf("\tData baru nama penerima\t: %s",(packages+i)->namapenerima);
			}else if(change == 53){
				printf("\n\n\tMasukkan alamat penerima\t: ");
				scanf("%c",&temp);
				scanf("%[^\n]s",(packages+i)->tujuan);
				printf("\tData baru alamat penerima: %s",(packages+i)->tujuan);
			}else if(change == 54){
				printf("\n\n\tNomor telepon penerima\t\t: ");
				scanf("%c",&temp);
				gets(str);
				for(j=0;j<strlen(str);j++){
			        if(str[j] >= 48 && str[j] <= 57){
			            count++;
			        }
			    }
			    while(count != strlen(str)){
			    	printf("\n\tInput telepon harus nomor semua!\n\n");
			    	printf("\tNomor telepon penerima\t\t: ");
					scanf("%c",&temp);
					scanf("%s",str);
					count=0;
					for(j=0;j<strlen(str);j++){
				        if(str[j] >= 48 && str[j] <= 57){
				            count++;
				        }
				    }
				}
				count = 0;
				strcpy((packages+i)->teleponPenerima,str);
				printf("\tData baru no.telp penerima\t: %s",(packages+i)->teleponPenerima);
			}else{
				printf("\n\n\tBerat paket\t\t\t: ");
				scanf("%f",&(packages+i)->beratpaket);
				printf("\tData baru berat paket\t: %.2f",(packages+i)->beratpaket);
			}
		}else break;
	}while(validation != 49);
	
	//Jumlah paket bertambah
	add = *(packages+i);
	i++;
	*jumlahPaket = i;
	fwrite(&add,sizeof(add),1,database);
	printf("\n");
	fclose(database);
	fclose(tempfile);
	Garis(120);
}

//Fungsi validasi data
void validasiData(){
	printf("\n\n\tApakah data yang masukkan sudah benar?");
	printf("\n\t----------------------------");
	printf("\n\t|TEKAN|     UNTUK          |  ");
	printf("\n\t----------------------------");
	printf("\n\t|  1  |SUDAH               |  ");
	printf("\n\t|  0  |BELUM               |  ");
	printf("\n\t----------------------------\n\t=> ");
}

void nonValidAction(){
	printf("\n\n\n\t====DATA YANG AKAN DIUBAH====");
	printf("\n\t------------------------------------");
	printf("\n\t|TEKAN|           UNTUK            |  ");
	printf("\n\t------------------------------------");
	printf("\n\t|  1  |Nama Pengirim               |  ");
	printf("\n\t|  2  |Alamat Pengirim             |  ");
	printf("\n\t|  3  |No.Telp Pengirim            |  ");
	printf("\n\t|  4  |Nama Penerima               |  ");
	printf("\n\t|  5  |Alamat Penerima             |  ");
	printf("\n\t|  6  |Telepon Penerima            |  ");
	printf("\n\t|  7  |Berat Paket                 |  ");
	printf("\n\t------------------------------------\n\t=> ");
}

//Fungsi display data
void displayPackages(struct infopaket *packages, int *jumlahPaket,int *stat){
	int i,k;
	char j,temp;
	while(j!=48){
		if(*jumlahPaket == 0){
			system("cls");
			printf("\t\tMENAMPILKAN PAKET");
			printf("\n\t");
			Garis(110);
			printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
			printf("\n\t");
			Garis(110);
			j=48;
		}else{
				system("cls");
				printf("\t\tMENAMPILKAN PAKET");
				printf("\n\t");
				Garis(110);
				//Menampilkan sebanyak jumlah paket
				for(i = 0; i < *jumlahPaket;i++){
					k = *(stat+i);
					printf("\n\tWaktu dan Tanggal\t: %s",(packages+i)->waktu[k]);
					printf("\n\tNo.Resi\t\t\t: %d",(packages+i)->resi);
					printf("\n\tNama Pengirim\t\t: %s",(packages+i)->namapengirim);
					printf("\n\tAsal Paket\t\t: %s",(packages+i)->asal);
					printf("\n\tNo.Telp Pengirim\t: %s",(packages+i)->teleponPengirim);
					printf("\n\tNama Penerima\t\t: %s",(packages+i)->namapenerima);
					printf("\n\tTujuan Paket\t\t: %s",(packages+i)->tujuan);
					printf("\n\tNo.Telp Penerima\t: %s",(packages+i)->teleponPenerima);
					printf("\n\tBerat Paket\t\t: %.2f kg",(packages+i)->beratpaket);
					printf("\n\tStatus Paket\t\t: %s",(packages+i)->status[k]);
					printf("\n\t");
					Garis(110);
				};
				pilihanDatabases();
				scanf("%c",&temp);
			   	scanf("%c",&j);
			   	
			   	if(j == 49){
			   		system("cls");
			   		//delete data
			   		deleteData(packages, jumlahPaket,stat);
				}else if(j == 50){
					system("cls");
					//cari data
					searchData(packages, jumlahPaket,stat);
				}else if(j==51){
					system("cls");
					//detailing data perjalanan
					detailedData(packages, jumlahPaket,stat);
				}else if(j==48){
					system("cls");
					break;
				}else{
					system("cls");
				}
			printf("\n");
		}
	}
}

//Fungsi update status
void statusUpdate(struct infopaket *packages, int *jumlahPaket,int *stat){
	struct infopaket up;
	int res,i,j,count=0;
	char x;
	char temp;
	//membuat waktu secara real time
	time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    
    printf("\t\tMEMPERBARUI STATUS PAKET");
    printf("\n\t");
    Garis(110);
    
    FILE *database;
    FILE *tempfile;
	
    if(*jumlahPaket == 0){
		printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
		printf("\n\t");
    	Garis(110);
    	printf("\n\n\n\t");
    	system("pause");
    	system("cls");
	}else{
	    do{
	    	system("cls");
	    	printf("\t\tMEMPERBARUI STATUS PAKET");
		    printf("\n\t");
		    Garis(110);
			printf("\n\tCari Paket yang akan diupdate statusnya dengan memasukkan nomor Resi \n\t(Ketik 0 apabila ingin mengagalkan): ");
			scanf("%d",&res);
			printf("\n\n\t====Info Paket====");
			for (i=0;i<*jumlahPaket;i++){
				//Menampilkan apabila nilai sama dengan nilai resi dari user
			   	if(res==(packages+i)->resi){
			   		j = *(stat+i);
			   		//Apabila status sudah "terkirim" sudah tidak bisa diupdate kembali
			   		if(!strcmp((packages+i)->status[j],"Terkirim") || !strcmp((packages+i)->status[j],"terkirim")){
			   			printf("\n\n\tStatus tidak bisa diubah karena status sudah terkirim!\n\n");
					}else{
						printf("\n\tWaktu, Tanggal (LastUpdate)\t: %s",(packages+i)->waktu[j]);
						printf("\n\tNama Pengirim\t\t\t: %s",(packages+i)->namapengirim);
						printf("\n\tAsal Paket\t\t\t: %s",(packages+i)->asal);
						printf("\n\tNo.Telp Pengirim\t\t: %s",(packages+i)->teleponPengirim);
						printf("\n\tNama Penerima\t\t\t: %s",(packages+i)->namapenerima);
						printf("\n\tTujuan Paket\t\t\t: %s",(packages+i)->tujuan);
						printf("\n\tNo.Telp Penerima\t\t: %s",(packages+i)->teleponPenerima);
						printf("\n\tStatus Paket (LastUpdate)\t: %s",(packages+i)->status[j]);
						printf("\n\tBerat Paket\t\t\t: %.2f kg",(packages+i)->beratpaket);
						printf("\n\tNo.Resi\t\t\t\t: %d",(packages+i)->resi);
						printf("\n\n");
						//Mengubah status
						j++;
						printf("\n\tUbah Status menjadi\t\t: ");
						scanf("%c",&temp);
						scanf("%[^\n]s",(packages+i)->status[j]);
						strcpy((packages+i)->waktu[j],time_str);
						*(stat+i) = j;
						//Update data di FILE
						database = fopen("database.txt", "r");
						tempfile = fopen("tempfile.txt", "w");
						while(fread(&up, sizeof(up), 1, database)){
							if(up.resi!=res){
								fwrite(&up, sizeof(up), 1, tempfile);
							}else{
								strcpy(up.status[j],(packages+i)->status[j]);
								strcpy(up.waktu[j],(packages+i)->waktu[j]);
								fwrite(&up,sizeof(up),1,tempfile);
							}
						}
						fclose(database);
						fclose(tempfile);
						database = fopen("database.txt","w");
						tempfile = fopen("tempfile.txt","r");
						while(fread(&up, sizeof(up),1,tempfile)){
							fwrite(&up,sizeof(up),1,database);
						}
						fclose(database);
						fclose(tempfile);
					}
					break;
				}else{
					count++;
				}
			}
			if(count == *jumlahPaket) printf("\n\n\n\tData tidak ditemukan!\n\n\n");
			count = 0;
			pilihanMelanjutkan();
			scanf("%c",&temp);
		   	scanf("%c",&x);
		   	while(x != 49 && x != 48){
		   		printf("\n\tInput salah, hanya boleh 0 atau 1 => ");
		   		scanf("%c",&temp);
		   		scanf("%c", &x);
			}
		}while(x != 48);
	}
}
//Fungsi display garis
void Garis(int n){
	int i;
	for(i=0;i<n;i++){
		printf("-");
	}
}

//Fungsi display pilihan untuk menghapus, mencari, memilah
void pilihanDatabases(){
	printf("\n\n\tTabel Perintah Database");
	printf("\n\t----------------------------------");
	printf("\n\t|TEKAN|     UNTUK                |  ");
	printf("\n\t----------------------------------");
	printf("\n\t|  1  |  Delete Data             |  ");
	printf("\n\t|  2  |  Search Data             |  ");
	printf("\n\t|  3  |  Detail Perjalanan Paket |  ");
	printf("\n\t|  0  |  Kembali                 |  ");
	printf("\n\t----------------------------------\n\t=> ");
}

//Fungsi untuk pilihan melanjutkan atau tidak
void pilihanMelanjutkan(){
	printf("\n\n\tIngin Melanjutkan Untuk Paket Lain?");
	printf("\n\t---------------------------------");
	printf("\n\t|TEKAN|     UNTUK               |  ");
	printf("\n\t---------------------------------");
	printf("\n\t|  1  |Melanjutkan              |  ");
	printf("\n\t|  0  |Kembali                  |  ");
	printf("\n\t---------------------------------\n\t=> ");
}

//Fungsi untuk delete data sesuai dengan no.resi yang diminta
void deleteData(struct infopaket *packages, int *jumlahPaket,int *stat){
	struct infopaket del;
	int res,i,j,k=0,getpos,status=0,count=0;
	char x,temp;
	
	FILE *database;
    FILE *tempfile;
	
	do{
		system("cls");
		printf("\tMENGHAPUS DATA DENGAN RESI");
		printf("\n\t");
		Garis(110);
		if(*jumlahPaket == 0){
			printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
			break;
		}else{
			printf("\n\tCari No. Resi untuk menghapus data (Ketik 0 apabila ingin mengagalkan): ");
			scanf("%d",&res);
			printf("\n\n\t====Info Paket====");
			for (i=0;i<*jumlahPaket;i++){
		   		if(res==(packages+i)->resi){
		   			getpos = i;
		   			status=1;
		   			break;
				}else{
					count++;
				}
			}
			database = fopen("database.txt", "r");
			tempfile = fopen("tempfile.txt", "w");
			if(count == *jumlahPaket) printf("\n\n\tResi Tidak Ditemukan\n\n\n");
			count=0;
			//delete data di FILE
			while(fread(&del,sizeof(del),1,database)){
				if(del.resi!=res){
					fwrite(&del,sizeof(del),1,tempfile);
				}
			}
			fclose(database);
			fclose(tempfile);
			database = fopen("database.txt","w");
			tempfile = fopen("tempfile.txt","r");
			while(fread(&del,sizeof(del),1,tempfile)) fwrite(&del,sizeof(del),1,database);
			fclose(database);
			fclose(tempfile);
			//Menghapus data sesuai resi yang tepat menggantikannya dengan data sequential berikutnya
			if(status==1){
				for(i=getpos;i<(*jumlahPaket);i++){
					j = *(stat+i);
					strcpy((packages+i)->namapengirim,(packages+(i+1))->namapengirim);
					strcpy((packages+i)->namapenerima,(packages+(i+1))->namapenerima);
		  			(packages+i)->resi=(packages+(i+1))->resi;
		  			strcpy((packages+i)->teleponPengirim,(packages+(i+1))->teleponPengirim);
		  			strcpy((packages+i)->teleponPenerima,(packages+(i+1))->teleponPenerima);
		  			(packages+i)->beratpaket=(packages+(i+1))->beratpaket;
		  			strcpy((packages+i)->asal,(packages+(i+1))->asal);
		  			strcpy((packages+i)->tujuan,(packages+(i+1))->tujuan);
		  			for(k=0;k<=j;k++){
		  				strcpy((packages+i)->waktu[k],(packages+(i+1))->waktu[k]);
		  				strcpy((packages+i)->status[k],(packages+(i+1))->status[k]);
					}
		  			*(stat+i)=*(stat+i+1);
				}
				*jumlahPaket -= 1;
				printf("\n\n\tDATA DENGAN RESI %d TELAH DIHAPUS!!\n\n\tPAKET SEKARANG BERJUMLAH %d\n\n",res,*jumlahPaket);
			}
			status=0;
		}
		pilihanMelanjutkan();
		scanf("%c",&temp);
	   	scanf("%c",&x);
	   	while(x != 49 && x != 48){
	   		printf("\n\tInput salah, hanya boleh 0 atau 1 => ");
	   		scanf("%c",&temp);
	   		scanf("%c", &x);
		}
	}while(x != 48);
}

//Fungsi untuk mencari data sesuai dengan no.resi yang diminta
void searchData(struct infopaket *packages, int *jumlahPaket,int *stat){
	int i,x;
	char pil,temp;
	displaySearching();
	scanf("%c",&temp);
	scanf("%c",&pil);
	do{
		if(pil==49){
			system("cls");
			//Mencari berdasarkan nama
			searchingNama(packages,jumlahPaket,stat);
		}else if(pil==50){
			system("cls");
			//Mencari berdasarkan asal atau alamat pengirim
			searchingAsal(packages,jumlahPaket,stat);
		}else if(pil==51){
			system("cls");
			//Mencari berdasarkan tujuan atau alamat penerima
			searchingTujuan(packages,jumlahPaket,stat);
		}else if(pil==52){
			system("cls");
			//Mencari berdasarkan resi
			searchingResi(packages,jumlahPaket,stat);
		}else if(pil==48){
			system("cls");
			break;
		}else{
			printf("Input Salah!!");
		}
		displaySearching();
		scanf("%c",&temp);
		scanf("%c",&pil);
	}while(pil != 48);
}

//Fungsi untuk display searching
void displaySearching(){
	printf("\n\n\tTabel Perintah Pencarian Oleh:");
	printf("\n\t------------------------------------");
   	printf("\n\t|TEKAN|     UNTUK                  |  ");
   	printf("\n\t------------------------------------");
   	printf("\n\t|  1  |  Searching Nama Penerima   |  ");
   	printf("\n\t|  2  |  Searching Asal            |  ");
   	printf("\n\t|  3  |  Searching Tujuan          |  ");
   	printf("\n\t|  4  |  Searching Resi            |  ");
   	printf("\n\t|  0  |  Kembali ke Menu           |  ");
   	printf("\n\t------------------------------------\n\t=> ");
}

void searchingNama(struct infopaket *packages, int *jumlahPaket,int *stat){
	int i,j,count=0;
	char nama[100];
	char temp;
	printf("\tMENCARI DATA SESUAI DENGAN NAMA PENERIMA");
	printf("\n\t");
	Garis(110);
	printf("\n\tMasukan Nama Penerima yang Anda Cari: ");
	scanf("%c",&temp);
	scanf("%[^\n]",&nama);
	
	printf("\n\t");
	Garis(110);
	if(*jumlahPaket == 0){
		printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
		printf("\n\t");
		Garis(110);
	}else{
		for (i=0;i<*jumlahPaket;i++){
	   		if(!strcmp((packages+i)->namapenerima,nama)){
	   			j = *(stat+i);
	   			printf("\n\tWaktu, Tanggal\t\t: %s",(packages+i)->waktu[j]);
				printf("\n\tNo.Resi\t\t\t: %d",(packages+i)->resi);
				printf("\n\tNama Pengirim\t\t: %s",(packages+i)->namapengirim);
				printf("\n\tAsal Paket\t\t: %s",(packages+i)->asal);
				printf("\n\tNo.Telp Pengirim\t: %s",(packages+i)->teleponPengirim);
				printf("\n\tNama Penerima\t\t: %s",(packages+i)->namapenerima);
				printf("\n\tTujuan Paket\t\t: %s",(packages+i)->tujuan);
				printf("\n\tNo.Telp Penerima\t: %s",(packages+i)->teleponPenerima);
				printf("\n\tBerat Paket\t\t: %.2f kg",(packages+i)->beratpaket);
				printf("\n\tStatus Paket\t\t: %s",(packages+i)->status[j]);
				printf("\n\t");
				Garis(110);
			}else{
				count++;
			}
		}
		if((count) == *jumlahPaket) printf("\n\n\n\tData tidak ditemukan!\n\n\n");
		count=0;
	}
}

void searchingAsal(struct infopaket *packages, int *jumlahPaket,int *stat){
	int i,j,count=0;
	char asal[100];
	char temp;
	printf("\tMENCARI DATA SESUAI DENGAN ALAMAT PENGIRIM");
	printf("\n\t");
	printf("\n\tMasukan Asal Paket Yang Anda Cari: ");
	scanf("%c",&temp);
	scanf("%[^\n]",&asal);
	
	printf("\n\t");
	Garis(110);
	if(*jumlahPaket == 0){
		printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
		printf("\n\t");
		Garis(110);
	}else{
		for (i=0;i<*jumlahPaket;i++){
	   		if(!strcmp((packages+i)->asal,asal)){
	   			j = *(stat+i);
	   			printf("\n\tWaktu, Tanggal\t\t: %s",(packages+i)->waktu[j]);
				printf("\n\tNo.Resi\t\t\t: %d",(packages+i)->resi);
				printf("\n\tNama Pengirim\t\t: %s",(packages+i)->namapengirim);
				printf("\n\tAsal Paket\t\t: %s",(packages+i)->asal);
				printf("\n\tNo.Telp Pengirim\t: %s",(packages+i)->teleponPengirim);
				printf("\n\tNama Penerima\t\t: %s",(packages+i)->namapenerima);
				printf("\n\tTujuan Paket\t\t: %s",(packages+i)->tujuan);
				printf("\n\tNo.Telp Penerima\t: %s",(packages+i)->teleponPenerima);
				printf("\n\tBerat Paket\t\t: %.2f kg",(packages+i)->beratpaket);
				printf("\n\tStatus Paket\t\t: %s",(packages+i)->status[j]);
				printf("\n\t");
				Garis(110);
			}else{
				count++;
			}
		}
		if((count) == *jumlahPaket) printf("\n\n\n\tData tidak ditemukan!\n\n\n");
		count=0;
	}
}

void searchingTujuan(struct infopaket *packages, int *jumlahPaket,int *stat){
	int i,j,count = 0;
	char tujuan[100];
	char temp;
	printf("\tMENCARI DATA SESUAI DENGAN ALAMAT PENERIMA");
	printf("\n\t");
	printf("\n\tMasukan Tujuan Paket Yang Anda Cari: ");
	scanf("%c",&temp);
	scanf("%[^\n]",&tujuan);
	
	printf("\n\t");
	Garis(110);
	if(*jumlahPaket == 0){
		printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
		printf("\n\t");
		Garis(110);
	}else{
		for (i=0;i<*jumlahPaket;i++){
	   		if(!strcmp((packages+i)->tujuan,tujuan)){
	   			j = *(stat+i);
	   			printf("\n\tWaktu, Tanggal\t\t: %s",(packages+i)->waktu[j]);
				printf("\n\tNo.Resi\t\t\t: %d",(packages+i)->resi);
				printf("\n\tNama Pengirim\t\t: %s",(packages+i)->namapengirim);
				printf("\n\tAsal Paket\t\t: %s",(packages+i)->asal);
				printf("\n\tNo.Telp Pengirim\t: %s",(packages+i)->teleponPengirim);
				printf("\n\tNama Penerima\t\t: %s",(packages+i)->namapenerima);
				printf("\n\tTujuan Paket\t\t: %s",(packages+i)->tujuan);
				printf("\n\tNo.Telp Penerima\t: %s",(packages+i)->teleponPenerima);
				printf("\n\tBerat Paket\t\t: %.2f kg",(packages+i)->beratpaket);
				printf("\n\tStatus Paket\t\t: %s",(packages+i)->status[j]);
				printf("\n\t");
				Garis(110);
			}else{
				count++;
			}
		}
		if((count) == *jumlahPaket) printf("\n\n\n\tData tidak ditemukan!\n\n\n");
		count=0;
	}
}

void searchingResi(struct infopaket *packages, int *jumlahPaket,int *stat){
	int i,j,count=0;
	int res;
	printf("\tMENCARI DATA SESUAI DENGAN NOMOR RESI");
	printf("\n\t");
	printf("\n\tMasukan Resi Paket Yang Anda Cari: ");
	scanf("%d",&res);
	
	printf("\n\t");
	Garis(110);
	if(*jumlahPaket == 0){
		printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
		printf("\n\t");
		Garis(110);
	}else{
		for (i=0;i<*jumlahPaket;i++){
	   		if(res==(packages+i)->resi){
	   			j=*(stat+i);
	   			printf("\n\tWaktu, Tanggal\t\t: %s",(packages+i)->waktu[j]);
				printf("\n\tNo.Resi\t\t\t: %d",(packages+i)->resi);
				printf("\n\tNama Pengirim\t\t: %s",(packages+i)->namapengirim);
				printf("\n\tAsal Paket\t\t: %s",(packages+i)->asal);
				printf("\n\tNo.Telp Pengirim\t: %s",(packages+i)->teleponPengirim);
				printf("\n\tNama Penerima\t\t: %s",(packages+i)->namapenerima);
				printf("\n\tTujuan Paket\t\t: %s",(packages+i)->tujuan);
				printf("\n\tNo.Telp Penerima\t: %s",(packages+i)->teleponPenerima);
				printf("\n\tBerat Paket\t\t: %.2f kg",(packages+i)->beratpaket);
				printf("\n\tStatus Paket\t\t: %s",(packages+i)->status[j]);
				printf("\n\t");
				Garis(110);
				break;
			}else{
				count++;
			}
		}
		if((count) == *jumlahPaket) printf("\n\n\n\tData tidak ditemukan!\n\n\n");
		count=0;
	}
}

void detailedData(struct infopaket *packages, int *jumlahPaket,int *stat){
	int i,j,k,l,m,n,o,count=0;
	int res;
	char temp,x;
	
	do{
		system("cls");
		printf("\tMENCARI DATA YANG AKAN DIRINCIKAN PERJALANANNYA DENGAN NO. RESI");
		printf("\n\t");
		printf("\n\tMasukan Resi Paket Yang Anda Cari (Ketik 0 apabila ingin mengagalkan): ");
		scanf("%d",&res);
		
		printf("\n\t");
		Garis(110);
		if(*jumlahPaket == 0){
			printf("\n\n\n\n\tTidak Ditemukan!, Belum terdapat data pada database\n\n\n");
			printf("\n\t");
			Garis(110);
		}else{
			for (i=0;i<*jumlahPaket;i++){
		   		if(res==(packages+i)->resi){
		   			j=*(stat+i);
					printf("\n\tNo.Resi\t\t\t: %d",(packages+i)->resi);
					printf("\n\tNama Pengirim\t\t: %s",(packages+i)->namapengirim);
					printf("\n\tAsal Paket\t\t: %s",(packages+i)->asal);
					printf("\n\tNo.Telp Pengirim\t: %s",(packages+i)->teleponPengirim);
					printf("\n\tNama Penerima\t\t: %s",(packages+i)->namapenerima);
					printf("\n\tTujuan Paket\t\t: %s",(packages+i)->tujuan);
					printf("\n\tNo.Telp Penerima\t: %s",(packages+i)->teleponPenerima);
					printf("\n\tBerat Paket\t\t: %.2f kg",(packages+i)->beratpaket);
					printf("\n\t");
					m = strlen((packages+i)->status[0]);
					for(l=1;l<=j;l++){
						if(strlen((packages+i)->status[l]) > m){
							m = strlen((packages+i)->status[l]);
						}
					}
					n = m+35;
					Garis(n);
					printf("\n\t|\tWaktu, Tanggal\t\t| Status Paket\t\t\t");
					printf("\n\t");
					Garis(n);
					for(k = 0; k<=j;k++){
						printf("\n\t|%s\t| %s",(packages+i)->waktu[k],(packages+i)->status[k]);
					}
					printf("\n\t");
					Garis(n);
					for(o = 0;o<=(j+4);o++){
						gotoxy(n+7,13+o);
						if(o == 0 || o == 2 || o == (j+4)){
							continue;
						}else{
							printf("|");
						}
					}
					gotoxy(8,14+o);
					printf("\n\t");
					Garis(110);
					break;
				}else{
					count++;
				}
			}
			if((count) == *jumlahPaket) printf("\n\n\n\tData tidak ditemukan!\n\n\n");
		}
		count=0;
		pilihanMelanjutkan();
		scanf("%c",&temp);
	   	scanf("%c",&x);
	   	while(x != 49 && x != 48){
	   		printf("\n\tInput salah, hanya boleh 0 atau 1 => ");
	   		scanf("%c",&temp);
	   		scanf("%c", &x);
		}
	}while(x != 48);
}
