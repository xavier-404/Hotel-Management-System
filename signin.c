#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 20
int signin();
int init();
int setup();
int menu();
int h_stat();
int h_custlist();
int h_cdetails(int n);
int checkout(int a);
int h_form();
int settings();
int initfileWrite(char userid[],char pass[],char n);
FILE* initfile;
char userId[16]="";
char userlevel=0;

struct {
	char name[NAME_SIZE];
	int currentcust;
	int peoplevisited;
	char manager[NAME_SIZE];
	int rooms;
}hotel={"",0,0,"",150};

struct customer{
	int id;
	char name[NAME_SIZE];
	int roomno;
	int groupmemno;
	char nationality[11];
	char emailid[NAME_SIZE];
	int arrivald[3];
	int arrivalt[2];
	float charge;
};
//main function
int main()
{
 init();
 menu();
 return 0;
}

int init(){
	int choice;
	FILE *initfile=fopen("init.data","rb");
	if(initfile==NULL){
	printf("1)Initialize software.\n2)exit.\n=");	
		scanf("%d",&choice);
		if(choice==1){
			setup();
		printf("\n================ENTER HOTEL DETAILS================\n");
			printf("Name of hotel:");
			scanf("%*c");
			scanf("%19[^\n]",hotel.name);
			printf("Hotel manager:");
			scanf("%*c");
			scanf("%19[^\n]",hotel.manager);
			printf("Enter total number of rooms:");
			scanf("%d",&hotel.rooms);
			FILE *hstat=fopen("hstat.data","wb");
			fwrite(&hotel,sizeof(hotel),1,hstat);
			fclose(hstat);
			FILE *cust=fopen("customers.data","wb");
			fclose(cust);
		}
		else{
			exit(0);
		}
	}
	else{
		fclose(initfile);
		signin();
		return 0;
	}
	init();
	return 0;
}

int setup(){
	char inpuser[16];
	char inppass[12];
printf("\n================CREATING ACCOUNT FOR OWNER================\n");
	printf("Enter new admin user ID:");
	scanf("%15s",inpuser);
	printf("Set a password:");
	scanf("%11s",inppass);
	initfileWrite(inpuser,inppass,8);
	printf("Account is created.\n");
	return 0;
}

int signin(){
	char reqId[16];
	char inpp[12];
	char tempuser[16];
	char temppass[12];
	int i=0;
	printf("\n==========================SIGN-IN=========================\n");
	printf("Enter user ID:");
	scanf("%15s",reqId);
	printf("Enter password:");
	scanf("%11s",inpp);
	FILE *initfile=fopen("init.data","rb");
while(1){
	fseek(initfile,29*i,0);
	fread(tempuser,1,16,initfile);
	if(feof(initfile)) break;
	if(!strcmp(reqId,tempuser)){
		fread(temppass,1,12,initfile);
		if(!strcmp(inpp,temppass)){
			printf("Access granted.\n");
			fread(&userlevel,1,1,initfile);
			strcpy(userId,reqId);
			fclose(initfile);
			return 0;
		}
	else break;
	}
	else{
		i++;
	}
}
printf("Incorrect email ID or password.");
exit(0);
return 0;
}

int initfileWrite(char userid[],char pass[],char n){
	FILE *initfile=fopen("init.data","ab");
	fwrite(userid,1,16,initfile);
	fwrite(pass,1,12,initfile);
	fwrite(&n,1,1,initfile);
	fclose(initfile);
	return 0;
}

int menu(){
int choice;	printf("\n=======================Dashboard=======================\n");
printf("USER ID:%s\n",userId);
	printf("1)Hotel status.\n2)Customers.\n3)Add customer.\n4)Exit.\n");
	if(userlevel==8)
		printf("5)Setting.\n=");
	else printf("=");
	scanf("%d",&choice);
	switch(choice){
		case 1:
		h_stat();
		break;
		case 2:
		h_custlist();
		break;
		case 3:
		h_form();
		break;
		case 4:
		exit(0);
		break;
		if(userlevel==8){
		case 5:
		settings();
		break;
		}
		default :
		exit(0);
		break;
	}
	menu();
	return 0;
}

int h_stat(){
	//name,current customers,customers till now,manager name;
	FILE *hstat=fopen("hstat.data","rb");
	fread(&hotel,sizeof(hotel),1,hstat);	printf("\n=======================HOTEL STATUS=======================\n");
	printf("Name of hotel:%s\n",hotel.name);
	printf("Name of manager:%s\n",hotel.manager);
	printf("Total number of rooms:%d\n",hotel.rooms);
	printf("Total number of families staying currently:%d\n",hotel.currentcust);
	printf("Number of people visited till now:%d\n",hotel.peoplevisited);
	fclose(hstat);
	return 0;
}
int h_custlist(){
	struct customer tempcust;
	FILE *cust=fopen("customers.data","rb");
	int i=0;
	int index;
	printf("INDEX\tCUSTOMER ID\tNAME\t\n");
	while(1){
	fread(&tempcust,sizeof(tempcust),1,cust);
	if(feof(cust)) break;
	printf("%d\t%d\t\t%s\t\t\n",i,tempcust.id,tempcust.name);
	i++;
	}
	
	fclose(cust);
	printf("End of customer list.\n");
	printf("1)View details.\n2)Dashboard.\n=");
	int choice4;
	scanf("%d",&choice4);
	switch(choice4){
		case 1:
		printf("Index of customer:");
		scanf("%d",&index);
		h_cdetails(index);
		break;
		case 2:
		
		break;
	}
	return 0;
}

int h_cdetails(int n){
int choice5;
struct customer tempcust;
FILE *cust=fopen("customers.data","rb");
fseek(cust,sizeof(tempcust) * n,0);
	fread(&tempcust,sizeof(tempcust),1,cust);
	if(feof(cust)){
		printf("ERROR:INVALID INDEX\n");
		return 1;
		}	
printf("\n===================CUSTOMER DETAILS===================\n");
	printf("CUSTOMER INDEX:%d\n",n);
	printf("CUSTOMER ID:%d\n",tempcust.id);
	printf("CUSTOMER NAME:%s\n",tempcust.name);
	printf("NATIONALITY:%s\n",tempcust.nationality);
	printf("EMAIL ID:%s\n",tempcust.emailid);
	printf("ROOM NO.:%d\n",tempcust.roomno);
	printf("NUMBER OF GROUP MEMBERS:%d\n",tempcust.groupmemno);
	printf("DATE OF ARRIVAL(DD MM YYYY):%2d/%2d/%4d\n",tempcust.arrivald[0],tempcust.arrivald[1],tempcust.arrivald[2]);
	printf("TIME OF ARRIVAL(HOUR MINUTES):%2d:%2d\n",tempcust.arrivalt[0],tempcust.arrivalt[1]);
	printf("1)Check out.\n2)Dashboard.\n=");
	fclose(cust);
		scanf("%d",&choice5);
		switch(choice5){
			case 1:
			checkout(n);
			break;
		}
	return 0;
}

int h_form(){
	char choice3;
	struct customer newcustomer;
	printf("====================NEW CUSTOMER DETAILS===================\n");
	printf("Customer Id:");
	scanf("%d",&newcustomer.id);
	printf("Name:");
	scanf("%*c");
	scanf("%19[^\n]",newcustomer.name);
	printf("Nationality:");
	scanf("%*c");
	scanf("%10[^\n]",newcustomer.nationality);
	printf("Email ID:");
	scanf("%*c");
	scanf("%19[^\n]",newcustomer.emailid);
	printf("Room No.:");
	scanf("%d",&newcustomer.roomno);
	printf("No of group members:");
	scanf("%d",&newcustomer.groupmemno);
	printf("Date of arrival(DD MM YYYY):");
	scanf("%d%d%d",&newcustomer.arrivald[0],&newcustomer.arrivald[1],&newcustomer.arrivald[2]);
	printf("Time of arrival(hour minute):");
	scanf("%d%d",&newcustomer.arrivalt[0],&newcustomer.arrivalt[1]);
	printf("Do you want to add this custumer(y/n):");
	do{
	scanf("%c",&choice3);
	}while(choice3=='\n');
	if(choice3=='y'){
		//Add customer to the list
		FILE *cust=fopen("customers.data","ab");
		fwrite(&newcustomer,sizeof(newcustomer),1,cust);
		fclose(cust);
		FILE *hstat=fopen("hstat.data","rb+");
		fread(&hotel,sizeof(hotel),1,hstat);
		hotel.currentcust++;
		hotel.peoplevisited+=1+newcustomer.groupmemno;
		rewind(hstat);
		fwrite(&hotel,sizeof(hotel),1,hstat);
		fclose(hstat);
		printf("Customer is added in the list.\n");
	}
	else{
		printf("Customer is cancelled.\n");
	}
	return 0;
}

int checkout(int a){
	struct customer tempcustomer;
	char choice6;
	float charge=0;
	int i=0;
	char title[NAME_SIZE]="Receipt";
	printf("Enter total charges:");
	scanf("%f",&charge);
	printf("Confirm check out(y/n):");
	do{
	scanf("%c",&choice6);
	}while(choice6=='\n');
	if(choice6=='y'){
		FILE *cust=fopen("customers.data","rb");
		FILE *receipt;
	FILE *cache=fopen("cache.data","wb");
		while (1){
			fread(&tempcustomer,sizeof(tempcustomer),1,cust);
			if(feof(cust)){
				break;
			}
			if(i!=a)
			fwrite(&tempcustomer,sizeof(tempcustomer),1,cache);
			else{
				tempcustomer.charge=charge;
int length = snprintf( NULL, 0, "%d", tempcustomer.id);
char* str = malloc( length + 1 );
snprintf( str, length + 1, "%d", tempcustomer.id );
				strcat(title,str);
				free(str);
				strcat(title,".txt");
				receipt=fopen(title,"w");
				fprintf(receipt,"==================RECEIPT==================\n");
				fprintf(receipt,"HOTEL NAME:%s\n",hotel.name);
				fprintf(receipt,"HOTEL MANAGER NAME:%s\n",hotel.manager);
				fprintf(receipt,"CUSTOMER ID:%d\n",tempcustomer.id);
	fprintf(receipt,"CUSTOMER NAME:%s\n",tempcustomer.name);
	fprintf(receipt,"NATIONALITY:%s\n",tempcustomer.nationality);
	fprintf(receipt,"EMAIL ID:%s\n",tempcustomer.emailid);
	fprintf(receipt,"ROOM NO.:%d\n",tempcustomer.roomno);
	fprintf(receipt,"NUMBER OF GROUP MEMBERS:%d\n",tempcustomer.groupmemno);
	fprintf(receipt,"DATE OF ARRIVAL(DD MM YYYY):%2d/%2d/%4d\n",tempcustomer.arrivald[0],tempcustomer.arrivald[1],tempcustomer.arrivald[2]);
	fprintf(receipt,"TIME OF ARRIVAL(HOUR MINUTES):%2d:%2d\n",tempcustomer.arrivalt[0],tempcustomer.arrivalt[1]);
	fprintf(receipt,"TOTAL CHARGES:%.2f",tempcustomer.charge);
	fclose(receipt);
			}
			i++;
		}
		fclose(cust);
		fclose(cache);
		remove("customers.data");
		rename("cache.data","customers.data");
		FILE *hstat=fopen("hstat.data","rb+");
		fread(&hotel,sizeof(hotel),1,hstat);
		hotel.currentcust--;
		rewind(hstat);
		fwrite(&hotel,sizeof(hotel),1,hstat);
		fclose(hstat);
	}
	
	return 0;
}
int settings(){
	int choice3;
	char choice4;
	int choice5;
	int i,a;
	char tempuser[16];
	char temppass[12];
	char templevel;
	int level;
	printf("\n===================SETTINGS===================\n");
	printf("1)View accounts.\n");
	printf("2)Delete all customers.\n");
	printf("3)Reset software.\n");
	printf("4)Dashboard.\n");
	printf("Choice:");
	scanf("%d",&choice3);
	switch(choice3){
		case 1:
		printf("INDEX\tUSER ID\tACCOUNT LEVEL\n");
		FILE *initfile=fopen("init.data","rb");
		for(i=0;1;i++){
			fread(tempuser,1,16,initfile);
			if(feof(initfile)) break;
			printf("%d\t",i);
			printf("%s\t",tempuser);
			fseek(initfile,12,1);
			fread(&templevel,1,1,initfile);
			printf("%u\n",templevel);
		}
		fclose(initfile);
		printf("End of the account list.\n");
		printf("1)Add account.\n");
		printf("2)Delete account.\n");
		printf("3)Dashboard.\n");
		scanf("%d",&choice5);
		if(choice5==1){
			printf("Enter new user ID:");
			scanf("%15s",tempuser);
			printf("Enter new password:");
			scanf("%11s",temppass);
			printf("Enter user level:");
			scanf("%d",&level);
			templevel=(char)level;
			printf("Confirm new account(y/n):");
		do{
			scanf("%c",&choice4);
		}while(choice4=='\n');
		if(choice4=='y'){
			initfileWrite(tempuser,temppass,templevel);
		}
		}
		else if(choice5==2){
			printf("Enter account index:");
			scanf("%d",&a);
			FILE *initfile=fopen("init.data","rb");
			fseek(initfile,29*a,0);
			fread(tempuser,1,16,initfile);
			if(feof(initfile)){
				printf("ERROR:INVALID INDEX\n");
				fclose(initfile);
				return 0;
			}
			fseek(initfile,12,1);
			fread(&templevel,1,1,initfile);
			if(templevel==8){
				printf("ERROR:CAN'T DELETE OWNER ACCOUNT.\n");
				fclose(initfile);
				return 0;
			}
			rewind(initfile);
			FILE *cache=fopen("cache.data","wb");
			for(i=0;1;i++){
				fread(tempuser,1,16,initfile);
				if(feof(initfile)) break;
				if(i!=a){
					fwrite(tempuser,1,16,cache);
					fread(temppass,1,12,initfile);
					fwrite(temppass,1,12,cache);
					fread(&templevel,1,1,initfile);
					fwrite(&templevel,1,1,cache);
				}
				else{
					fseek(initfile,13,1);
				}
			}
			fclose(initfile);
			fclose(cache);
			remove("init.data");
			rename("cache.data","init.data");
		}
		break;
		case 2:
		printf("Are you sure you want to delete all customers.(y/n):");
		do{
			scanf("%c",&choice4);
		}while(choice4=='\n');
		if(choice4=='y'){
		FILE *cust=fopen("customers.data","wb");
		fclose(cust);
		printf("Customer data is deleted.\n");
		}
		else{
			printf("Customer data is not deleted.\n");
		}
		break;
		case 3:
		printf("Are you sure you want to reset the software.(y/n):");
		do{
			scanf("%c",&choice4);
		}while(choice4=='\n');
		if(choice4=='y'){
		remove("init.data");
		remove("customers.data");
		remove("hstat.data");
		printf("Software reset has been occured.\n");
		printf("Restart the software.\n");
		exit(0);
		}
		else{
			printf("Software reset denied.\n");
		}
		break;
	}
	return 0;
}
