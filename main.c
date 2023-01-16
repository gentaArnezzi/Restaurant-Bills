//Bill Restaurant Program

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};


//functions to generate biils

void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
        printf("\t    Siu. Restaurant");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}


void generateBillBody(char item[30],int qty, float price){
    printf("%s\t\t",item);
        printf("%d\t\t",qty);
        printf("%.2f\t\t",qty * price);
        printf("\n");
}



void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;//netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}

int compare(const void *a, const void *b) {
        struct orders *order1 = (struct orders *)a;
        struct orders *order2 = (struct orders *)b;
        return strcmp(order1->date, order2->date);
}

int compareByName(const void *a, const void *b) {
    struct orders *orderA = (struct orders *)a;
    struct orders *orderB = (struct orders *)b;
    return strcmp(orderA->customer, orderB->customer);
}

int main(){
    
    int choiceMen;
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';
    char name[50];
    FILE *fp;
       //dashboard
    while(contFlag == 'y'){
    system("clear");
    float total = 0;
    int invoiceFound = 0;
    printf("\t============Siu RESTAURANT============");
    printf("\n\nPlease select your prefered operation");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Menu List");
    printf("\n5.Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt){
        case 1:
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        strcpy(ord.date,__DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;
        for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++){
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);

        if(saveBill == 'y'){
            fp = fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else
            printf("\nError saving");
            fclose(fp);
        }
        break;

        case 2:
         system("clear");
        fp = fopen("RestaurantBill.dat","r");
        int numOfOrders = 0;
        struct orders ordersList[100];

        // Membaca data dari file dan menyimpannya dalam array ordersList
        while(fread(&ordersList[numOfOrders], sizeof(struct orders), 1, fp)) {
            numOfOrders++;
        }
        fclose(fp);


        // Mengurutkan data menggunakan fungsi qsort
        qsort(ordersList, numOfOrders, sizeof(struct orders), compareByName);

        printf("\n  *****Your Previous Invoices*****\n");
        for (int i = 0; i < numOfOrders; i++) {
            struct orders order = ordersList[i];
            float tot = 0;
            generateBillHeader(order.customer, order.date);
            for (int j = 0; j < order.numOfItems; j++) {
                generateBillBody(order.itm[j].item, order.itm[j].qty, order.itm[j].price);
                tot += order.itm[j].qty * order.itm[j].price;
            }
            generateBillFooter(tot);
        }
        break;

        case 3:
        printf("Enter the name of the customer:\t");
        //fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t*****Invoice of %s*****",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
            invoiceFound = 1;
            }
        }
        if(!invoiceFound){
            printf("Sorry the invoice for %s doesnot exists",name);
        }
        fclose(fp);
        break;

        case 4:
            system("clear");
            printf("\t============Menu LIst============\n");
            printf("\n\n");
            printf("1. Makanan\n");
            printf("2. Minuman\n");
            printf("3. Desert\n");
            printf("\n");
            printf(">>");            
            scanf("%d", &choiceMen);
            if (choiceMen==1) {
                system("clear");
                printf("\t==============Makanan================\n");
                printf("\t1. Nasi Goreng %9s|%9s\n"," ","Rp15.000");
                printf("\t2. Mie Goreng %10s|%9s\n"," ","Rp10.000");
                printf("\t3. Sate %16s|%9s\n"," ","Rp20.000");
                printf("\t4. Ayam Bakar %10s|%9s\n"," ","Rp25.000");
                printf("\t5. Ikan Bakar %10s|%9s\n"," ","Rp30.000");
                printf("\t6. Nasi Campur %9s|%9s\n"," ","Rp18.000");
                printf("\t7. Cap Cay %13s|%9s\n"," ","Rp15.000");
                printf("\t8. Buntil %14s|%9s\n"," ","Rp10.000");
                printf("\t9. Gudeg %15s|%9s\n"," ","Rp12.000");
                printf("\t10. Soto %15s|%9s\n"," ","Rp15.000");
                
            }else if (choiceMen==2) {
                system("clear");
                printf("\t==============Minuman================\n");
                printf("\t1. Teh %16s|%9s\n"," ","Rp5.000");
                printf("\t2. Kopi %15s|%9s\n"," ","Rp8.000");
                printf("\t3. Jus %16s|%9s\n"," ","Rp10.000");
                printf("\t4. Susu %15s|%9s\n"," ","Rp7.000");
                printf("\t5. Es Teh %13s|%9s\n"," ","Rp5.000");
                printf("\t6. Es Jeruk %11s|%9s\n"," ","Rp7.000");
                printf("\t7. Es Campur %10s|%9s\n"," ","Rp10.000");
                printf("\t8. Es Teler %11s|%9s\n"," ","Rp12.000");
                printf("\t9. Wedang %13s|%9s\n"," ","Rp8.000");
                printf("\t10. Sirup %13s|%9s\n"," ","Rp6.000");
            }else if(choiceMen==3){
                system("clear");
                printf("\t==============Desert================\n");
                printf("\t1. Es Krim %12s|%9s\n"," ","Rp15.000");
                printf("\t2. Puding %13s|%9s\n"," ","Rp10.000");
                printf("\t3. Roti Sobek %9s|%9s\n"," ","Rp5.000");
                printf("\t4. Kue Bolu %11s|%9s\n"," ","Rp8.000");
                printf("\t5. Martabak %11s|%9s\n"," ","Rp20.000");
                printf("\t6. Cheese Cake %8s|%9s\n"," ","Rp25.000");
                printf("\t7. Brownies %11s|%9s\n"," ","Rp18.000");
                printf("\t8. Kue Lapis %10s|%9s\n"," ","Rp12.000");
                printf("\t9. Kue Sus %12s|%9s\n"," ","Rp10.000");
                printf("\t10. Kue Kering %8s|%9s\n"," ","Rp8.000");
            }
            
        break;
            
        case 5:
            printf("\n\t\t Bye Bye :)\n\n");
            exit(0);
            break;
        default:
        printf("Sorry invalid option");
        break;
    }
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");

    return 0;
}

