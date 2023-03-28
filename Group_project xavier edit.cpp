#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<ctype.h> 
#include<time.h>

//function prototypes
void receipt(char [], struct customerinfo *customer, int);
void vehicles_available(struct customerinfo *customer, int);
void login();
struct	customerinfo
{
	char fname[15], lname[15], plate[7], pay_method[5], service[6][30], paid[3];
	float tip,total;
	int k, invoice;	
};

struct	washbay
{
	char fname[15], lname[15], plate[7], service[6][30];	
};
		
int main() //defining main fuction
{
	system("color f1");
	struct 	customerinfo customer[20];
	struct washbay wash[3];
    int i, j , k, m, n, o, p, x, rtip, service_count=0, plate_count=0, invoice=26598, count, menu, choice;
    float cost[6],wvtotal=0, ewtotal=0, poltotal=0, bufftotal=0, rooftotal=0, ditotal=0,grandtotal=0,tiptotal=0;
    char date[12], array[225];
    int repeat[20];
    
    choice=menu=count=i=j=k=rtip=m=n=o=p=0;
    // i-used to keep track of the nnumber of vehicles in the bay
	// j-used to operate the menu
	// k-used to keep track of the requested number of services
	// m-used to run loops  
	// n-number of customers processed  
	// 0-used to run inner loops
	// p-used with receipts
    
    srand(time(NULL)); //ensures numbers generated from rand function are truly randomized
    
    login(); //calling our login function to run the program
    
    //accepting and validating the date input from the user [dd/mm/yyyy]
    int mm=0,dd=0,yyyy=0;
    
	do
	{
		do
	    {
		   	printf("Please enter today's date [dd mm yyyy]: ");
	    	scanf("%d %d %d",&dd,&mm,&yyyy);
			
	    	if(dd>31||dd<01 ||mm<01||mm>12 ||yyyy<1000||yyyy>9999) 
	  			puts("Invalid! please try again\a");
	  		
	    	if(mm==02 && dd>29)
	    	{
				puts("Note that February has a maximum of 29 days");
			}	
	    	puts("");
		}
		while(mm==02 && dd>29);
	}
	while(dd>31||dd<01 ||mm<01||mm>12 ||yyyy<0001||yyyy>9999);
	
	sprintf(date,"%2d/%2d/%4d",dd,mm,yyyy);
	 
    //CUSTOMER DETAILS file pointer
	FILE *c_details; 
	if((c_details=fopen("CUSTOMER DETAILS.txt","w+"))==NULL) 
		printf("File could not be opened.\n");
	else
	{
		//displays headings	in the text document
		fprintf(c_details,"\t\t\tDETAILS FOR %s\n",date);
		while(j != 5)
		{
			//displaying menu to aid the user's selection processes
			system("cls");
			printf("\t\t\t\t    MENU\n");
		    printf("\t\t\t   ------------------------\n");
		 	printf(" _________________________________________________________________________________\n");
			printf("| 1. Accept Customer's Information & Payment (randomly tip 0.02 of cost)          |\n");
			printf("|---------------------------------------------------------------------------------|\n");
		 	printf("| 2. Wash Car                                                                     |\n");
			printf("|---------------------------------------------------------------------------------|\n");
		 	printf("| 3. Display Returning Customers                                                  |\n");
			printf("|---------------------------------------------------------------------------------|\n");
		 	printf("| 4. Display Day's Sales Report                                                   |\n");
			printf("|---------------------------------------------------------------------------------|\n");
		 	printf("| 5. Exit                                                                         |\n");
			printf("|---------------------------------------------------------------------------------|\n");
			printf("|_________________________________________________________________________________|\n");
			printf("\n\nEnter option =>"); 
			scanf("%d", &j);
			system("cls");
			switch(j)
			{
				case 1:
					if(i==20)
					{
						puts("MAXIMUM CAPACITY HAS BEEN REACHED");
						break;
					}
					customer[i].k=0;
					i++;
					//accepts customers information
					printf("\nPlease enter customer's first and last name: ");
					scanf("%s %s",customer[i].fname,customer[i].lname);
					strupr(customer[i].fname);	strupr(customer[i].lname);
											// Prevents entering the same vehicle twice 
					do
					{
						plate_count=0;
						printf("Enter customer's vehicle license plate number: ");
						scanf("%s",customer[i].plate);	strupr(customer[i].plate);
						
									
						for(m=1;m<=i;m++)
						{
							if(strcmp(customer[i].plate,customer[m].plate)==0)
							plate_count++;
						}
						if(plate_count>=2)
						{
							printf("You have already entered vehicle - %s\n\a",customer[i].plate);
							puts("You may input 'cancel' stop this entry");
						}
					}
					while(plate_count>=2 && strcmp(customer[i].plate,"CANCEL")!=0);
					
					if(strcmp(customer[i].plate,"CANCEL")==0)
					{
						i--;
						//break;
					}
								
									
					//service selection area
					puts("\tServices \t\t     Cost");
					puts("   -------------------- \t   ----------");
					puts("1. Wash and Vacuum                  $2500.00");
					puts("2. Engine Wash                      $2000.00");
					puts("3. Polishing                        $3500.00");
					puts("4. Buffing                          $5500.00");
					puts("5. Roof Cleaning                    $3200.00");
					puts("6. Detailing/Interior Shampooing    $7500.00\n\n");
					
					while(j!=-1 && k!=6)
					{
						do
						{
							do
							{
								fflush (stdin);
								printf("Enter the number for a service reqired [-1 to end selection]: ");
								scanf("%d",&j);
								fflush (stdin);
								if(j>6 || j<-1 || j==0)
									puts("Invalid option, please try again :/ \a");
							}
							while(j>6 || j<-1 || j==0); //ensures only acceptable responses are entered for j
								
								
							if(j>0 && j<7)
								customer[i].k++;
							k=customer[i].k;
							
									
							service_count=0;
							switch(j)
							{
								case -1:
									break;
								case 1:
									("%s",strcpy(customer[i].service[k],"Wash and Vacuum")); 
									cost[k]=2500;
									wvtotal=wvtotal + cost[k];
									break;
								case 2:
									("%s",strcpy(customer[i].service[k],"Engine Wash"));
									cost[k]=2000;
									ewtotal=ewtotal + cost[k];
									break;
								case 3:
									("%s",strcpy(customer[i].service[k],"Polishing"));
									cost[k]=3500;
									poltotal = poltotal+ cost[k];
									break;
								case 4:
									("%s",strcpy(customer[i].service[k],"Buffing"));
									cost[k]=5500;
									bufftotal=bufftotal + cost[k];
									break;
								case 5:
									("%s",strcpy(customer[i].service[k],"Roof Cleaning"));
									cost[k]=3200;
									rooftotal = rooftotal + cost[k];
									break;
								case 6:
									("%s",strcpy(customer[i].service[k],"Detailing/Interior Shampooing"));
									cost[k]=7500;
									ditotal = ditotal + cost[k];
									break;
							}//end of switch
										
							//checkincg the number of times a paricular service was selected for this customer
							if(k>1)
							{
								for(m=1;m<=k;m++)
								{
									if(strcmp(customer[i].service[k],customer[i].service[m])==0)
										service_count++;
								}
							}
								
							if(service_count>=2)
							{
								printf("You have already selected - %s\n\a",customer[i].service[k]);
								k--; //allows for the previous entry to be overwritten
							}
							else if(j!=-1)
								customer[i].total+=cost[k];
						}
						while(service_count>=2);  //ensures each servive is only entered once
									
					}//end of while
									
													
					printf("\nDo you wish to give a tip? - ");
					rtip=rand()%2;
					if(rtip==1)
					{
						puts("YES");
						customer[i].tip=0.02*customer[i].total;
						tiptotal+=customer[i].tip;
					}
					else
					{
						puts("NO");	
						customer[i].tip=0.00;
					}
								
								
					do
					{
						printf("Enter Payment method - 'cash' or 'card': "); 
						scanf("%s",customer[i].pay_method);	strupr(customer[i].pay_method);
						if(strcmp(customer[i].pay_method,"CASH")==0)
							customer[i].total+=0.00*customer[i].total;
						else
						{
							if(strcmp(customer[i].pay_method,"CARD")==0)
								customer[i].total+=0.03*customer[i].total;
							else
								puts("Invalid Entry, please try again\a");
						}
					}
					while(strcmp(customer[i].pay_method,"CASH")!=0 && strcmp(customer[i].pay_method,"CARD")!=0);
								
										
					customer[i].total+=customer[i].tip;
					p=i;
					grandtotal+=customer[i].total;
					customer[i].invoice=invoice++;
					receipt(date, customer, p); //calling the receipt function
					n++;	
					//prints to the file
					fprintf(c_details,"CUSTOMER %d\n",n);
					fprintf(c_details,"---------------------------------------------------------------------------\n");
					fprintf(c_details,"Name: %s %s\n",customer[i].fname,customer[i].lname);
					fprintf(c_details,"Vehicle plate: %s\n",customer[i].plate);
					fprintf(c_details,"Requested Services:\n");
					for(m=1;m<=k;m++)
					{
						fprintf(c_details,"               %d. %s - $%.2f\n",m,customer[i].service[m],cost[m]);
					}
					fprintf(c_details,"\nPayment method: %s\n",customer[i].pay_method);
					fprintf(c_details,"Tip amount: $%.2f\n",customer[i].tip);
					fprintf(c_details,"Total: amount: $%.2f\n\n\n",customer[i].total);	
					k=0;
					system("pause");
					break;
				case 2:
					//wash car
					if(i==0)
					{
						puts("There a currently no vehicles at the car wash");
						break;
					}
					if(count<3)
					{
						puts("\nEnter a number from the choices below:");
						puts(" 1. Add vehicle to wash bay");
						puts(" 2. Clear vehicle from the wash bay");
						puts(" 3. Remove a waiting customer");
						printf("\n\nChoice=>");
						scanf("%d",&menu);
						
						switch(menu)
						{
							case 1:
								if(count==3)
								{
									puts("3 cars are currently being serviced");
									break;
								}
									
									
								vehicles_available(customer,i); //fuction call to show the vehicles available
								
								printf("\nEnter the number corresponding to the desried vehicle: ");
								scanf("%d",&choice);
								m=choice;
								if(strcmp(customer[m].paid,"NO"))
								{
									p=m;
									receipt(date, customer, p); //calling the receipt function
								}											
									
								if(strcmp(customer[m].paid,"YES"))
								{
									puts("Vehicle is now being serivced");
									count++;
									//moving customer to the wash bay
									("%s",strcpy(wash[count].fname,customer[m].fname));
									("%s",strcpy(wash[count].lname,customer[m].lname));
									("%s",strcpy(wash[count].plate,customer[m].plate));
									for(o=1;o<=k;o++)
										("%s",strcpy(wash[count].service[0], customer[count].service[o]));
										
									//"deleting" moved customer from the waiting area - technically it'll still be around but not accounting for
									for(m; m<=i; m++)
									{
										("%s",strcpy(customer[m].fname,customer[m+1].fname));
										("%s",strcpy(customer[m].lname,customer[m+1].lname));
										("%s",strcpy(customer[m].plate,customer[m+1].plate));
										for(o=1;o<=k;o++)
										{
											("%s",strcpy(customer[m].service[o],customer[m+1].service[o]));
										}
										("%s",strcpy(customer[m].pay_method,customer[m+1].pay_method));
										customer[m].tip=customer[m+1].tip;
										customer[m].total=customer[m+1].total;
										customer[m].invoice=customer[m+1].invoice;
										("%s",strcpy(customer[m].paid,customer[m+1].paid));
										
									}
									i--;
								}
									
								m=0;
								break;
							case 2:
								break;
							default:
								break;
						}//end of switch
					}//end if
											
					system("pause");
					break;
				case 3:
					//displays returning customers
					for(m=0;m<n;i++)
					{
						//delete this
						fscanf(c_details, "%s %s", customer[m].fname,customer[m].lname);
						fflush (stdin);
						fscanf(c_details, "%s %s", customer[m+1].fname,customer[m+1].lname);
						fflush (stdin);
						if (strcmp(customer[m].fname,customer[m+1].fname)==0 && strcmp(customer[m].lname,customer[m+1].lname)==0)
						{
							printf ("%d %d is a repeat customer",customer[m].fname,customer[m].lname);
							repeat[m]++;
						}
						
					}
					system("pause");
					break;
				case 4:
					//displays day's sale report
					printf ("\t\t\t\t\t------------------------------------------------- \n");
	    			printf ("\n\t\t\t\t\t\t         TODAY'S SALES' \n");	
	 				printf ("\t\t\t\t\t-------------------------------------------------\n");	
	 				printf ("\t\t\t\t\tTotal number of custumers today:           %d,",n);
					printf ("\t\t\t\t\tTotal Wash and Vacuum sales:               $%.2f",wvtotal);
					printf ("\t\t\t\t\tTotal Engine Wash sales:                   $%.2f",ewtotal);
					printf ("\t\t\t\t\tTotal Polishing sales:                     $%.2f",poltotal);
					printf ("\t\t\t\t\tTotal Buffing sales:                       $%.2f",bufftotal);
					printf ("\t\t\t\t\tTotal Roof Cleaning sales:                 $%.2f",rooftotal);
					printf ("\t\t\t\t\tTotal Detailing/Interior Shampooing sales: $%.2f",ditotal);
					printf ("\ttt\t\t\tTotal revenue earned in tips today:        $%.2f",tiptotal);
					printf ("\ttt\t\t\tTotal revenue earned today:                $%.2f",grandtotal);
					printf ("\t\t\t\t\t-------------------------------------------------\n");
					system("pause");
					break;
				case 5:
					exit(0);//terminates the program
					break;
				default:
					printf("\n\nInvalid option => %d\n\n", j);
					system("pause");
					break;
			}//end of switch
		}//end of while
		fclose(c_details);//marks the end of the file pointer
	}//end if
					
	return 0;		
}//end of main

void login()
{
	char pass[12];
	int attempt=0;
	do
	{
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t  __________________________________");
		printf("\n\t\t\t\t\t |                                  |");
		printf("\n\t\t\t\t\t |Trish & Shaun's Auto Wash Services|");
		printf("\n\t\t\t\t\t |__________________________________|\n");	
	    printf("\t\t\t\t\t-------------------------------------- ");
	    printf("\n\t\t\t\t\t\t         LOGIN \n");	
	 	printf("\t\t\t\t\t--------------------------------------\n");	
	 	printf(" \t\t\t\t\tEnter password: ");
	 	scanf("%s",&pass);
	 	if (strcmp(pass,"HELLO")== 0) printf("WELCOME!! :)\n");
		else
		{
	      	attempt=attempt+1;
	      	if(attempt>2) exit(0);
			printf("INVALID PASSWORD, please try again :(\n\n\n");  
			system("pause");
	      	system("cls");
		}	 
 	}
 	while(strcmp(pass,"HELLO")!= 0);
}

void receipt(char date[], struct customerinfo customer[], int p) //defining receipt
{
	system("cls");
	int invoice=customer[p].invoice;
	int k=customer[p].k;
	printf("\n	       Trish & Shaun's Auto Wash Services - Customer Invoice       ");
	printf("\n	 __________________________________________________________________");
	printf("\n	| Invoice No. :------------------|        #CXSD%-20d|",invoice);
	printf("\n	| Processed Date :---------------|     #DM%-25s|",date);
	printf("\n	| Billed to :--------------------|%-15s %-15s  |",customer[p].fname,customer[p].lname);
	printf("\n	| Vehicle # :--------------------|   %-30s|",customer[p].plate);
	printf("\n	| Services  :--------------------| 1.%-30s|",customer[p].service[1]);
	for(int o=2;o<=k;o++)
		printf("\n	|                                | %d.%-30s|",o,customer[p].service[o]);
	printf("\n	| Tip Amount:--------------------|   $%-29.2f|",customer[p].tip);
	printf("\n	|--------------------------------|---------------------------------|"); 
	printf("\n	| Total Amount is :--------------|   $%-29.2f|",customer[p].total); 
	printf("\n	|------------------------------------------------------------------|");
	printf("\n	| This is a computer generated invoce and it does not              |");
	printf("\n	| require an authorised signture                                   |"); 
	printf("\n	|------------------------------------------------------------------|");
	printf("\n	|//////////////////////////////////////////////////////////////////|");
	printf("\n	|    THANK YOU FOR MAKING IT Trish & Shaun's Auto Wash Services.   |");
	printf("\n	|                 ENJOY YOUR SHINY CLEAN RIDE :D                   |");
	printf("\n	|//////////////////////////////////////////////////////////////////|");
	
	do
	{
		printf("\n\nWould you like to make payment now? ['yes' or 'no']: ");
		scanf("%s",customer[p].paid); 
		strupr(customer[p].paid);
		printf("medz: %s",customer[p].paid);
		if(strcmp(customer[p].paid,"NO")!=0 && strcmp(customer[p].paid,"YES")!=0 )
			puts("Only accepting 'yes' or 'no'");
	}
	while(strcmp(customer[p].paid,"NO")!=0 && strcmp(customer[p].paid,"YES")!=0 );
	
	if(strcmp(customer[p].paid,"NO")==0 )
		puts("Payment will be required before service is applied");
	else
	{
		FILE *print; 
		if((print=fopen("CUSTOMER RECEIPT.txt","w+"))==NULL) 
			printf("File could not be opened.\n");
		else
		{
			fprintf(print,"\n	       Trish & Shaun's Auto Wash Services - Customer Invoice       ");
			fprintf(print,"\n	 __________________________________________________________________");
			fprintf(print,"\n	| Invoice No. :------------------|       #CXSD%-20d|",invoice);
			fprintf(print,"\n	| Processed Date :---------------|     #DM%-25s|","");
			fprintf(print,"\n	| Billed to :--------------------|%-15s %-15s  |",customer[p].fname,customer[p].lname);
			fprintf(print,"\n	| Vehicle # :--------------------|   %-30s|",customer[p].plate);
			fprintf(print,"\n	| Services  :--------------------| 1.%-30s|",customer[p].service[1]);
			for(int o=2;o<=k;o++)
				fprintf(print,"\n	|                                | %d.%-30s|",o,customer[p].service[o]);
			fprintf(print,"\n	| Tip Amount:--------------------|  $%-30.2f|",customer[p].tip);
			fprintf(print,"\n	|--------------------------------|---------------------------------|"); 
			fprintf(print,"\n	| Total Amount is :--------------|  $%-30.2f|",customer[p].total); 
			fprintf(print,"\n	|------------------------------------------------------------------|");
			fprintf(print,"\n	| This is a computer generated invoce and it does not              |");
			fprintf(print,"\n	| require an authorised signture                                   |"); 
			fprintf(print,"\n	|------------------------------------------------------------------|");
			fprintf(print,"\n	|//////////////////////////////////////////////////////////////////|");
			fprintf(print,"\n	|    THANK YOU FOR MAKING IT Trish & Shaun's Auto Wash Services.   |");
			fprintf(print,"\n	|                 ENJOY YOUR SHINY CLEAN RIDE :D                   |");
			fprintf(print,"\n	|//////////////////////////////////////////////////////////////////|");
		
			fclose(print);//marks the end of the file pointer
			puts("Invoce is ready for printing ;)");
		}
	}
}//end of receipt 


void vehicles_available(struct customerinfo customer[], int i)//defintion of vehicles_available
{
	puts("\t\t\t\t\t== THESE ARE THE VEHICLES AVAILABLE ==");
    puts(" _________________________________________________________________________________________________________________________");
	printf("|no. |%-20s |%-20s |%-15s |%-14s |%-7s |%-30s|\n","First Name","Lastname", "plate number", "Pay Method", "Paid","Services");
	for(int m=1;m<=i;m++)
	{
		int k=customer[m].k;
		puts("|----|---------------------|---------------------|----------------|---------------|--------|------------------------------|");							
		printf("|%2d. |%-20s |%-20s |%-15s |%-14s |%-7s |%-30s|\n",m,customer[m].fname, customer[m].lname, customer[m].plate, customer[m].pay_method, customer[m].paid, customer[m].service[1]);
		for(int o=2;o<=k;o++)
			printf("|----|---------------------|---------------------|----------------|---------------|--------|%-30s|\n", customer[m].service[o]);
	}	
	puts("|____|_____________________|_____________________|________________|_______________|________|______________________________|");
}//end of vehicles_available
