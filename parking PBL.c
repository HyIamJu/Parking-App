#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


int counter = 1;
int vipCounter = 8;
int counterExit = 0;
int income;


void login();

struct tiket{
	int noTicket;
	char typeVehicle [3];
	char platNum [10];
	time_t in;
	time_t out;
	int duration;
	int cost;
	bool mFine;
	bool vip;
	int change,cash;		 	
};
struct tiket vehicle [100];
void vipPrint();
int input();
int paymentExt();
void printTicket(int i);
void finalReport();
void credit ();
void dataCollect();


//main clear
int main(){
	login();
	int choice;
   
    do 
    {
    again:
    system("cls");
    printf("  ===================================================================\n");
	printf("  |                                                                 |\n");
	printf("  |                      PARKING APP	                            |\n");
	printf("  |               PT. SUKA SUKA SAYA (PERSERO)                      |\n");
	printf("  |                                                                 |\n");
	printf("  ===================================================================\n");
	printf("  |                                                                 |\n");
	printf("  |			MAIN MENU				    |\n");
	printf("  |                                                                 |\n");
	printf("  |	1. Incoming Vehicle	                       		    |\n");
	printf("  |	2. Vehicle Exit and Payment				    |\n");
	printf("  |	3. History of Incoming Vehicle Data 			    |\n");
	printf("  |	4. Report Remaining Slots and Income			    |\n");
	printf("  |	5. Project Credits					    |\n");
	printf("  |	6. Exit							    |\n");
	printf("  |                                                                 |\n");
	printf("  ===================================================================\n \n");
	printf("  Enter Your choice >");
	scanf("%i",&choice);
	switch(choice){
        case 1:
            system("cls");
            input();
            break;
            
        case 2:
            system("cls");
            paymentExt();
			break;
		
		case 3:
        	system("cls");
        	dataCollect();
            system("pause");
            break;
            
        case 4:
        	system("cls");
        	finalReport();
        	printf("\n \n");
        	system("pause");
			break;
        
        case 5:
        	system("cls");
        	credit ();
            system("pause");
            break;
             
        case 6:
        	system("cls");
        	char exitAns;
    		askExit:
	    	printf("Are you sure want to exit ? \n");
        	printf("(y/n)> ");
       		scanf("%s",&exitAns);
			if((exitAns == 'y')|| (exitAns == 'Y')){
				system("cls");
   				printf("Have a Nice Day :) \n");
    			sleep(4);
				exit(0);
			}
            else if ((exitAns == 'n')|| (exitAns == 'N')) {
            	goto again;
			} 
			else {
				printf(" \nWrong Input Please just input Y/N ! \n");
				sleep(2);
				goto askExit;
			
			} 
			break;
		
            
        default:
            printf("\a") ;
        }
    } while (1);
}

//login clear
void login(){ 
char username[5]= "admin" , pass[12]= "parkir";
   int status = 0, salah = 0;
   int i,j,a;

   while(status < 3){
   		printf("\t\t\t+--------------------------------+\n");
		printf("\t\t\t|         SELAMAT DATANG         |\n");
		printf("\t\t\t|  ----SUKASUKA MALL BATAM----   |\n");
		printf("\t\t\t+--------------------------------+\n\n");
		printf("\t\t\t+--------------------------------+\n");
		printf("\t\t\t|\t     LOGIN\t\t |\n");
		printf("\t\t\t+--------------------------------+\n");
      printf("\t\t\t  Username : ");
      scanf("%s",&username); 
      printf("\t\t\t  Password : ");
      scanf("%s",&pass); 
      
    printf("\n\t\t\t Loading"); 
    for(i=0; i<=2; i++){
    	sleep(1);
		printf(".");
	  }
	  
	  printf("\n\n\t\t\t Loading Complete");

      if(strcmp(username, "admin")==0 && strcmp (pass, "parkir")== 0){
         printf("\n\t\t\t Akses diterima. Selamat Datang\n");
         break;
      }else{
         printf("\n\t\t\t Username dan Password tidak match\n");
         salah++;
         sleep(1);
         system("cls");
         
         if(salah == 3){
            printf("\n\n\n\t\t\t Akses ditolak\n");
         }
      }
      status++;
   }

   sleep(1);
}

//input clear
int input(){
char answer,answerVIP;

inputLoop:
if (vipCounter<=8 && vipCounter > 0){
askInputVIP:
printf("VIP status ? (y/n) >" );
scanf(" %c",&answerVIP);
if ((answerVIP=='y') || (answerVIP=='Y') ){
		vipCounter--;
		vehicle[counter].vip=true;
		system("cls");
		vipPrint();
}
//else if ((strcmp(answerVIP,"n"))|| (strcmp(answerVIP,"N")) ){
	else if ((answerVIP=='N') || (answerVIP=='n') ) {
	vehicle[counter].vip=false;
	system("cls");
}
else  {
printf("Wrong input please just input y or n ! \n\n");
goto askInputVIP;
}
}

printf("Enter Vehicle type (A/B/C)	: ");
scanf(" %s",vehicle[counter].typeVehicle);

printf("Enter Vehicle plat number	: ");
scanf(" %s",vehicle[counter].platNum);

time(&vehicle[counter].in);
printf("Arival Time 			: %s \n",ctime(&vehicle[counter].in));

vehicle[counter].noTicket=counter;
printf("The vehicle has been successfully added with the ticket number %d \n",vehicle[counter].noTicket);
counter++;


printf("-------------------------------------------------------------------\n");

askInput:
printf("Want To Enter a Ticket again ? \n");
printf("(y/n) > ");
scanf(" %c",&answer);

//if ((strcmp(answer,"y")) || (strcmp(answer,"Y")) ){
if ((answer=='Y') || (answer=='y') ){
system("cls");	
goto inputLoop;
}
else if ((answer=='n') || (answer=='N') ){
	return(0);
}
else {
system("cls");
printf("Wrong input please just input y or n ! \n");
printf("\a") ;
sleep(1);

goto askInput;
}


}

int paymentExt(){
paymentLoop: ;
char printStruct;
char searchPlat[10];
char answerPrint;
char answerpayment;
int hour,minute,second;
int paymentHours;
bool platfound = false;
int totalPayment = 0;
int moneyCustomer = 0 ;
int vipCharge = 0;
int change = 0;
askSearchPlat:
printf("Enter plat number : ");
scanf(" %s",searchPlat);
int i;
for(i=0; i<counter; i++){
	if(strcmp(searchPlat,vehicle[i].platNum)==0 ){ 			//kalau ada di data
		system("cls");
		printf("The vehicle with license plate [BP %s] is recorded in the system \n",searchPlat);
		printf("---------------------------------------------------------------- \n");
		platfound = true;
		
		time(&vehicle[i].out);
		vehicle[i].duration= difftime(vehicle[i].out, vehicle[i].in);
		hour = vehicle[i].duration / 3600;
		minute = (vehicle[i].duration % 3600) / 60;
		second = vehicle[i].duration % 60;
		if (minute > 30){
			hour + 1;
		}	
				
		if((strcmp(vehicle[i].typeVehicle,"a")==0)|| (strcmp(vehicle[i].typeVehicle,"A")==0) ){
		paymentHours=hour*5000;
		}
		else if((strcmp(vehicle[i].typeVehicle,"b")==0)|| (strcmp(vehicle[i].typeVehicle,"B")==0) ){
		paymentHours=hour*10000;
		}
		else if((strcmp(vehicle[i].typeVehicle,"c")==0)|| (strcmp(vehicle[i].typeVehicle,"C")==0) ){
		paymentHours=hour*2000;
		}
	
	
	if(vehicle[i].vip == true){
			
		if((strcmp(vehicle[i].typeVehicle,"a")==0)|| (strcmp(vehicle[i].typeVehicle,"A")==0) ){
		paymentHours=hour*50000;
		}
		else if((strcmp(vehicle[i].typeVehicle,"b")==0)|| (strcmp(vehicle[i].typeVehicle,"B")==0) ){
		paymentHours=hour*50000;
		}
		else if((strcmp(vehicle[i].typeVehicle,"c")==0)|| (strcmp(vehicle[i].typeVehicle,"C")==0) ){
		paymentHours=hour*50000;
		}
		
		printf("Enter additional service fee 	: Rp.");
		scanf(" %d",&vipCharge);
		vipCounter++;
		}
		
		askTicket: ;
		char askTicket; 
		printf("Ticket availability?  ? (y/n) >");
		scanf(" %c",&askTicket);
		if ( (askTicket == 'y') || (askTicket == 'Y') ){
			vehicle[i].mFine=false;
			system("cls");	
			}
		else if ( (askTicket == 'n') || (askTicket == 'N') ){
		vehicle[i].mFine=true;
		}
		else {
		printf("\a") ;
		printf("Wrong input please just input y or n ! \n");
		sleep(2);
		system("cls");
		goto askTicket;
		}
		
		
		if(vehicle[i].mFine == true){
		totalPayment = paymentHours + vipCharge + 100000; 	//kalau tiket hilang true artinya betul kena denda
		}
		else{
		totalPayment = paymentHours + vipCharge; 			//kalau tiket ada
		}
		
		vehicle[i].cost = totalPayment;
		income +=totalPayment;
		printf("Total Payment is %d \n \n",totalPayment);
		printf("Enter the amount of customer money	: Rp.");
		scanf( " %d",&moneyCustomer);
		vehicle[i].cash = moneyCustomer;
		change = moneyCustomer - totalPayment ;
		vehicle[i].change = change;
		counterExit++;
		
		printf("Total change				: Rp. %d \n \n \n ",change);
	
		
		askPrint:
		printf("Print parking receipts ? (y/n) >");
		scanf(" %c",&answerPrint);
		
		if ((answerPrint=='y') || (answerPrint=='Y')){
		system("cls");
		 printTicket(i);
		}	
		
		else if ((answerPrint=='n' )|| (answerPrint=='N')){
		break;
		}
		else{
		printf("\a") ;
		printf("Wrong input please just input y or n ! \n");
		sleep(2);
		goto askPrint;
		}
		
			
	}
}
	if ( platfound != true ){
		system("cls");
		printf("Vehicle data with license plate [BP %s] not found \n",searchPlat);
		printf("-------------------------------------------------- \n");
		
		printf("Want Search again ? \n");
		printf("(y/n) > ");
		scanf(" %c",&answerpayment);

		if ((answerpayment == 'y') || (answerpayment == 'Y')){
		system("cls");
		goto paymentLoop;
		}
		else if ((answerpayment == 'n' )|| (answerpayment == 'N')) {return(0);}
		
		else {
		printf("\a") ;
		printf("Wrong input please just input y or n ! \n");
		sleep(2);
		system("cls");
		goto askSearchPlat;
		}
	}
	
	
	
		//semua proses clear skrng tanya ulang mau bayar lagi apa kaga
		askPaymenLoop:
		printf("Want to Search another vehicle again ? \n");
		printf("(y/n) > ");
		scanf(" %c",&answerpayment);

		if ((answerpayment == 'y' )|| (answerpayment == 'Y')){
		system("cls");
		goto paymentLoop;
		}
		else if ((answerpayment == 'n') || (answerpayment == 'N')) {return(0);}
		
		else {
		printf("\a") ;
		printf("Wrong input please just input y or n ! \n");
		system("pause");
		system("cls");
		goto askPaymenLoop;
		}
}

void printTicket(int i){
	int hour = vehicle[i].duration / 3600;
	int minute = (vehicle[i].duration % 3600) / 60;
	int second = vehicle[i].duration % 60;
	int denda = 0;
	char priceTerms [100];

	if(vehicle[i].mFine == true){ //kasih tau jumlah denda
		denda=100000;
		}
		
	if((strcmp(vehicle[i].typeVehicle,"a")==0)|| (strcmp(vehicle[i].typeVehicle,"A")==0) ){
	strcpy(priceTerms,"RP 5000/Jam");
	}
	else if((strcmp(vehicle[i].typeVehicle,"b")==0) || (strcmp(vehicle[i].typeVehicle,"B")==0) ){
	strcpy(priceTerms,"RP 10000/Jam");
	}
	else if((strcmp(vehicle[i].typeVehicle,"c")==0) || (strcmp(vehicle[i].typeVehicle,"C")==0) ){
	strcpy(priceTerms,"RP 2000/Jam");
	}

	if (vehicle[i].vip== true){
	strcpy(priceTerms,"RP 50000/Jam (VIP)");
	}
	
	printf("|		PT. SUKA-SUKA SAYA (Persero)			| \n");
	printf("|		----SUKASUKA MALL BATAM----			| \n");
	printf("================================================================== \n");
	
	printf("[BP %s] / TYPE %s \n",vehicle[i].platNum,vehicle[i].typeVehicle);
	printf("TICKET NO			: %d \n",vehicle[i].noTicket);
	printf("MASUK				: %s \n",ctime(&vehicle[i].in) );
	printf("KELUAR				: %s \n",ctime(&vehicle[i].out) );
	printf("DURASI				: %d Jam %d menit %d detik \n",hour,minute,second);
	printf("TARIF				: %s \n",priceTerms);
	printf("TARIF TOTAL			: RP %d \n",vehicle[i].cost);
	printf("DENDA				: RP %d \n",denda);
	printf("				------------------ + \n");
	printf("		TOTAL		: RP %d \n",vehicle[i].cost);
	printf("		TUNAI		: RP %d \n",vehicle[i].cash);
	printf("		KEMBALIAN	: RP %d \n \n",vehicle[i].change);
	
	printf("================================================================== \n \n");
	printf("		TERIMA KASIH ATAS KUNJUNGAN ANDA \n");
	printf("		--------SELAMAT JALAN----------- \n \n");
}

//vip print clear
void vipPrint(){
	char park[10];
	printf("+--------------------VIP PARKING SITE PLAN------------------------+\n");
	printf("===================================================================\n\n");
	
	printf("            _________  _________  _________  _________             \n");
	printf("    	   |         ||         ||         ||         |            \n");
	printf("           |         ||         ||         ||         |            \n");
	printf("           |    A1   ||    A2   ||    A3   ||    A4   |            \n");
	printf("|==========|         ||         ||         ||         |===========|\n");
    printf("                                                                   \n");
	printf("                                                                   \n");
	printf("-------------------------------------------------------------------\n");
	printf("                                                                   \n");
	printf("                                                                   \n");
	printf("|==========|         ||         ||         ||         |===========|\n");
	printf("           |    B1   ||    B2   ||   B3    ||   B4    |            \n");
	printf("           |         ||         ||         ||         |            \n");      
    printf("           |_________||_________||_________||_________|            \n\n"); 
    printf("===================================================================\n");
    printf("\n \n");
    printf("Parking slots available only %i \n", vipCounter+1);
    
    printf("The vehicle will be parked at	: ");
    scanf ("%s", park);

}


//final report clear
void finalReport(){
	int vehicleIn = counter-1-counterExit;
	int availbleSlot = 100 - vehicleIn;
	
	printf("  ===================================================================\n");

	printf("  |			Parkir Kendaraan			    | \n");
	printf("  ------------------------------------------------------------------- \n");
    printf("  1. Masuk		: %i		\n",counter-1);
	printf("  2. Keluar		: %i			\n",counterExit);
	printf("  3. Masih Didalam	: %i 	\n",vehicleIn);
	printf("  4. Sisa Slot		: %i dari 100	\n",availbleSlot);
	printf("  ------------------------------------------------------------------- \n");
	printf("  |			Total Pendapatan			    | \n");
	printf("  ------------------------------------------------------------------- \n");
	printf("  > Rp %i \n",income);

}

//credit clear
void credit (){

	printf("       ____________________________________________________ \n");
	printf("       |                 *DATA KELOMPOK*                  | \n");
	printf("       |--------------------------------------------------| \n");
	printf("       | PROJECT     | PARKING APP                        | \n ");
	printf("      |--------------------------------------------------| \n");
	printf("       | KELOMPOK    |   6                                | \n ");
	printf("      |--------------------------------------------------| \n");
	printf("       |             | 1. Devi Puspita pribadi_3312101001 |  \n");
	printf("       | NAMA_NIM    | 2. Junanda Ika Rizky_3312101001    |  \n");
	printf("       |             | 3. Ravena Auliya_3312101020        |  \n");
	printf("       |--------------------------------------------------|  \n");
	printf("       | Dosen Matkul| IBU MIRA CHANDRA KIRANA, S.T, M.T  | \n");      
    printf("       |__________________________________________________| \n\n\n\n");
    
}

//data collect
void dataCollect(){	
int i;

printf("\n \n");
	printf("  No | Plat Number | type of vehicle   | 	Arrived at \n");
	printf("-------------------------------------------------------------------------- \n");
for(i=0; i<counter; i++){
	if(i>=1){
		if(strlen(vehicle[i].platNum)==6 || strlen(vehicle[i].platNum)==7){
		printf("  %d \t%s  	   %s	 	%s",vehicle[i].noTicket, vehicle[i].platNum, vehicle[i].typeVehicle, ctime(&vehicle[i].in));
		}
		else if(strlen(vehicle[i].platNum)==5){
		printf("  %d \t%s   	   %s	 	%s",vehicle[i].noTicket, vehicle[i].platNum, vehicle[i].typeVehicle, ctime(&vehicle[i].in));
		}
		else if(strlen(vehicle[i].platNum)==4){
		printf("  %d \t%s    	   %s	 	%s",vehicle[i].noTicket, vehicle[i].platNum, vehicle[i].typeVehicle, ctime(&vehicle[i].in));
		}
		else if(strlen(vehicle[i].platNum)==3){
		printf("  %d \t%s     	   %s	 	%s",vehicle[i].noTicket, vehicle[i].platNum, vehicle[i].typeVehicle, ctime(&vehicle[i].in));
		}
		else if(strlen(vehicle[i].platNum)==2){
		printf("  %d \t%s       	   %s	 	%s",vehicle[i].noTicket, vehicle[i].platNum, vehicle[i].typeVehicle, ctime(&vehicle[i].in));
		}
		else if(strlen(vehicle[i].platNum)==1){
		printf("  %d \t%s         	   %s	 	%s",vehicle[i].noTicket, vehicle[i].platNum, vehicle[i].typeVehicle, ctime(&vehicle[i].in));
		}
		
	
	}
}
printf("\n-------------------------------------------------------------------------- \n");
}
























