
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "csv.h"





typedef struct Node {// Creates a Node

    long long ID;
    char meno[300];
    char mermod[300];
    char typmervel[300];
    double hodnota;
    char casmerania[300];
    long long datum;

    struct Node* next;//pointer to next Node(llist)
}NODE;


/*
 *
 * Function to create linked list
 *
 * */

void funkcia_n(NODE** head, int* na, int* zaznam, NODE* headd) {
    int i = 1;
    *na=i;
    FILE* fr;
    fr = fopen("dataloger_V2.txt", "r");//txt file where we have our data
    char garr[300];//storage where we store unnecessary garbage
    long long IDd;
    char menoo[300];
    char mermodd[300];
    char typmervell[300];
    double hodnotaa;
    char casmeraniaa[300];
    long long datumm;
    int k = 0;

    if (fr != NULL) {

        while (feof(fr) == 0) {//it will ittarete throught the whole txt file line after line
            fscanf(fr, "%s", &garr);// $$$

            NODE* novyprk = (NODE*)malloc(sizeof(NODE));// allocating memory for each list
            fscanf(fr, "%lld", &IDd);//Saves value to the IDd variable
            novyprk->ID = IDd;//puts the IDd value to the first linked list

            fscanf(fr, " %[^\n]s", &menoo);//used this form of formating so the code will take the space abr between names
            strcpy(novyprk->meno, menoo);// the same thing as with ID and IDd adding value to the linked list but becouse it is a String we need to use strcpy

            fscanf(fr, "%s", &mermodd);
            strcpy(novyprk->mermod, mermodd);
            fscanf(fr, "%s", &typmervell);
            strcpy(novyprk->typmervel, typmervell);
            fscanf(fr, "%lf", &hodnotaa);
            novyprk->hodnota = hodnotaa;
            fscanf(fr, "%s", &casmeraniaa);
            strcpy(novyprk->casmerania, casmeraniaa);
            fscanf(fr, "%lld", &datumm);
            novyprk->datum = datumm;


            novyprk->next = (*head);// here we "create" and send pointer n list
            (*head) = novyprk;// here we point the pointer of the list we created to the next list it is going backwords so we will need to reverse it later.
            k++;

        }
    }
    else {
        printf("zaznamy neboli nacitane");
    }
    //ve need to reverse the lsit


    struct Node* newhead = NULL;//head of the reversed list becouse it is saved backwords
    struct Node* tmp = NULL;

    while (*head) {
        tmp = *head; /*tmp is pointing to the first list in our backwords linked list ukayuje na prvy zaznam nasho terajsieho listu*/
        *head = (*head)->next;

        //this will add tmp to the new reversed list
        tmp->next = newhead;
        newhead = tmp;
    }

    *head = newhead;
    *zaznam = k;
    printf("Nacitalo sa %d zaznamov\n", *zaznam);



}

/*
 * This function is to print the Linked list in console
 *
 *
 * */

void funkcia_v(NODE* head, int* na, int* zaznam) {

    int cislo = 0;
    *zaznam = cislo;
    if (*na >= 1) {
        while (head != NULL) {
            cislo++;
            printf("%d:\n", cislo);
            printf("ID cislo mer. osoby: %lld\n", head->ID);
            printf("Meno osoby: %s\n", head->meno);
            printf("Mer. modul: %s\n", head->mermod);
            printf("Typ mer. veliciny: %s\n", head->typmervel);
            printf("Hodnota: %lf\n", head->hodnota);
            printf("Cas merania: %s\n", head->casmerania);
            printf("Datum: %lld\n", head->datum);

            printf("\n");
            head = head->next;


        }
        printf("\n");
    }
    else {
        printf("nobola spostena funkcia n\n");
    }
    *zaznam = cislo;

}




/*
 * To delete all the list with specific ID
 * */


void funkcia_z(NODE* head, NODE** headd, int* zaznam,int*na) {
    long long IDD;



    int po = 0;
    int k = *zaznam;
    if (*na == 1) {
        printf("Zadajte ID zaznamu na vymazanie\n");
        scanf("%lld", &IDD);
        //***********************************pisem toto ako madar vsetko to prezera celz linked list nie iba jedno ***************(ked bude preyentovat abz som to nepomotal)*************
        while (head != NULL) {
            if (IDD == head->ID) {
                printf("Zaznam pre ID: %lld pre modul %s bol vymayany.\n", head->ID, head->mermod);
            }
            head = head->next;
        }
        while (po <= *zaznam) {
            //use temp to free memory
            NODE* temp;
            // looking if id is in the first list if yes move head to next and free the list
            //if the list is at the start

            if ((*headd)->ID == IDD)
            {

                temp = *headd;    //save head to tmp to free memory
                *headd = (*headd)->next;
                k--;
                free(temp);
            }
            else//if the list is in middle
            {

                NODE* current = *headd;
                while (current->next != NULL)
                {
                    //delete current ->next node
                    if (current->next->ID == IDD)
                    {//node will be deleted from linked list

                        temp = current->next;

                        current->next = current->next->next;
                        //a vymaze sa
                        k--;
                        free(temp);
                        break;
                    }

                    else
                        current = current->next;
                }
            }

            po++;

        }
        *zaznam = k;
    }
    else {
        printf("nebola spustena funkcia n\n");
    }
}









void funkcia_u(struct Node** head, int* na,int * zaznam) {
    int k = *zaznam;
    int i = k * k;
    int a;
    if (*na != 1) {
        return;
    }
    struct Node* current = *head, * index = NULL;//index for latter use
    long long temp;

    if (head == NULL) {
        return;
    }
    else {
        for (a = 0; a >= i; a++) {
            while (current != NULL) {// spustime loop next node current v indexe

                index = current->next;

                //cheecking if the date values is current are bigger then index
                //if yes swap the possitions
                while (index != NULL) {
                    if (current->datum > index->datum) {
                        temp = current->datum;
                        current->datum = index->datum;
                        index->datum = temp;
                    }
                    index = index->next;
                }
                current = current->next;
            }
        }

    }



}

















/*
 *
 * when we want to add streight tp the linked list
 *
 * */
void funkcia_p(NODE** headd, NODE* head, int* na, int* zaznam) {

    char p[30];//gerbage collection
    int c, j = 0, i,l=0;
    long long IDd;
    char menoo[300];
    char mermodd[300];
    char typmervell[300];
    double hodnotaa;
    char casmeraniaa[300];
    long long datumm;
    NODE* tmp;
    if (*na == 1) {
        printf("zadajte poziciu\n");
        scanf("%s", &p);
        scanf("%d", &c);
        printf("zadajte udaje\n");
        scanf("%lld", &IDd);
        scanf(" %[^\n]s", &menoo);
        scanf("%s", &mermodd);
        scanf("%s", &typmervell);
        scanf("%lf", &hodnotaa);
        scanf("%s", &casmeraniaa);
        scanf("%lld", &datumm);

        if (c == 1) {
            //If we want to add to the top of thi linked list
            NODE* newnode = /*(NODE*)*/malloc(sizeof(NODE*));
            //we fill the list
            tmp = *headd;
            newnode->ID = IDd;
            strcpy(newnode->meno, menoo);
            strcpy(newnode->mermod, mermodd);
            strcpy(newnode->typmervel, typmervell);
            newnode->hodnota = hodnotaa;
            strcpy(newnode->casmerania, casmeraniaa);
            newnode->datum = datumm;

            *headd = newnode;
            //we relink the list
            newnode->next = tmp;
            l++;

            printf("podarilo sa pridat zaznam");
        }//when we want to add to the middle
        else if (c > 1 && c < *zaznam) {
            //fill the list
            NODE* temp;
            NODE* newnode = (NODE*)malloc(sizeof(NODE*));
            newnode->ID = IDd;
            strcpy(newnode->meno, menoo);
            strcpy(newnode->mermod, mermodd);
            strcpy(newnode->typmervel, typmervell);
            newnode->hodnota = hodnotaa;
            strcpy(newnode->casmerania, casmeraniaa);
            newnode->datum = datumm;
            newnode->next = NULL;

            temp = head;



            // we will go back to the pssition n -1 and so we can link the new list so it points to the n+1 list there are now 2 connecction to n+1 list
            //now we will conecct n-1 list to new list n and delete the link to n+1

            // to sa vraciam na poyiciu n-1
            for (i = 2; i <= c - 1; i++)
            {
                temp = temp->next;

                if (temp == NULL)
                    break;
            }

            if (temp != NULL)
            {
                // linkin to n+1
                newnode->next = temp->next;

                //n-1 to new link
                temp->next = newnode;
                l++;
                printf("zaznam bol pridany\n");
            }
            else
            {
                printf("nepodarilo sa pridat zaznam\n");
            }
        }
            // when we want to add to the end
        else if (c >= *zaznam) {
            NODE* last = *headd;
            NODE* temp;
            NODE* newnode = (NODE*)malloc(sizeof(NODE*));
            newnode->ID = IDd;
            strcpy(newnode->meno, menoo);
            strcpy(newnode->mermod, mermodd);
            strcpy(newnode->typmervel, typmervell);
            newnode->hodnota = hodnotaa;
            strcpy(newnode->casmerania, casmeraniaa);
            newnode->datum = datumm;
            //cuz it is the last in linked list it will point to null
            newnode->next = NULL;
            // go to the last list /node
            temp = head;
            while (temp != NULL && temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
            l++;
            printf("zaznam bol pridany\n");

        }


    }
    else {
        printf("nebolo spustena funkcia n");
    }
    i = 0;
    i = *zaznam + l;
    *zaznam = i;

}








/*
 *
 * When we want ot find by measurement mode
 *
 * */
void funkcia_h(NODE* head,int*na) {
    char md[300];
    int cislo = 0, c = 0;
    if (*na == 1) {
        printf("Zadaj meraci modul format: N11 Pismeno a 2 cisla");
        scanf("%s", &md);
        while (head != NULL) {//going thriugh the whole Linked list when we find the meas mode print the lsit
            if (md[0] == head->mermod[0] && md[1] == head->mermod[1] && md[2] == head->mermod[2]) {
                cislo++;
                printf("%d\n", cislo);
                printf("ID cislo mer. osoby: %lld\n", head->ID);
                printf("Meno osoby: %s\n", head->meno);
                printf("Mer. modul: %s\n", head->mermod);
                printf("Typ mer. veliciny: %s\n", head->typmervel);
                printf("Hodnota: %lf\n", head->hodnota);
                printf("Cas merania: %s\n", head->casmerania);
                printf("Datum: %lld\n", head->datum);
                printf("\n");
                c++;
            }
            head = head->next;
        }
        if (c == 0) {
            printf("Pre meraci modul %s niesu zaznamy\n", md);
        }
    }
    else {
        printf("nebola spustena funkcia n\n");
    }
}


/*
 *
 * swaping possitions in Linked lst
 *
 * */
 int funkcia_r(NODE*head,int * zaznam,int*na) {
    NODE* tmp=head;
    NODE* tmp1=head;
    NODE* prev1;
    NODE* prev2;
    NODE* temp;
    int pos1,pos2;
    char p;
    if (*na != 1) {
        printf("nebola spustena funkcia n\n");
        return 1;
    }
    scanf("%d", &pos1);

    scanf("%d", &pos2);
    int i;
    if (pos1 <= *zaznam && pos2 <= *zaznam) {
        // which pos is the biggest
        const int maxPos = (pos1 > pos2) ? pos1 : pos2;

        // getting info how many lists are ther
        const int totalNodes = *zaznam;

        // looking if the possitions are within the Linked list
        if ((pos1 <= 0 || pos1 > totalNodes) || (pos2 <= 0 || pos2 > totalNodes))
        {
            return -1;
        }

        // if positions are the same we dont need to change
        if (pos1 == pos2)
        {
            return 1;
        }


        // finding which list i need to swap
        i = 1;
        temp = head;
        prev1 = NULL;
        prev2 = NULL;

        //iterater throug linked list until Max pos
        while (temp != NULL && (i <= maxPos))
            //when loop  ends we have link we want ot swa[
        {
            if (i == pos1 - 1)
                prev1 = temp;
            if (i == pos1)
                tmp = temp;

            if (i == pos2 - 1)
                prev2 = temp;
            if (i == pos2)
                tmp1 = temp;
            //move to next list
            temp = temp->next;
            i++;
        }
        //checking if we have the links we want to swap
        //
        if (tmp != NULL && tmp1 != NULL)
        {//swaping next links by node1->.next=node2->next a reversed
            // linking previous to next
            if (prev1 != NULL)
                prev1->next = tmp1;

            // linking prweius (node2) s node1 (node 1 a node 2 su node2 a node4 pozicie)
            if (prev2 != NULL)
                prev2->next = tmp;

            temp = tmp->next;
            tmp->next = tmp1->next;
            tmp1->next = temp;

            //
            // we are changing the 1st List we need to change the head
            if (prev1 == NULL)
                head = tmp1;
            else if (prev2 == NULL)
                head = tmp;
        }
    }


}



/*
 *
 * After data anlys is complite print thit to the csv file
 *
 * */

void funkcia_e(NODE* head, int* na, int* zaznam){

    // opening the csv file in a mode a+ which allows us to print there
    //csv files are formatted  wiht , and \n
    //, is new row
    //\n is new collum

    FILE* fp = fopen("dataloger.csv","a+");
    // if we can open the fiwl
    if(!fp){
        printf("cant open file");
    }
    //for prinith the first row and fiiled it out with
    fprintf(fp,"ID,Meno,MerMod,TypMerVel,Hodnota,CasMerania,Datum\n");



    int index = 0;
     NODE* curr = head;
     while(curr!= NULL) {
//we print list to the file


         fprintf(fp,"%lld,%s,%s,%s,%lf,%s,%lld\n",curr->ID,curr->meno,curr->mermod,curr->typmervel,curr->hodnota,curr->casmerania,curr->datum);
//move to next list
         index++;
         curr=curr->next;


     }


    fclose(fp);


}













int main() {


    NODE* zaciatok = NULL;
    NODE* list = malloc(sizeof(NODE));
    NODE* head = NULL;
    NODE* tmp = NULL;

    char pr;
    int k = 1;
    int* na = 0, zaznam = 0;

    while (k == 1) {
        scanf("%c", &pr);


        switch (pr) {
            case 'n':
                if (na == 1) {
                    tmp = zaciatok;
                    while (zaciatok != NULL)
                    {
                        tmp = zaciatok;
                        zaciatok = zaciatok->next;
                        free(tmp);

                    }
                    zaciatok = NULL;
                }
                funkcia_n(&zaciatok, &na, &zaznam, zaciatok);

                break;
            case 'v':
                funkcia_v(zaciatok, &na, &zaznam);
                break;
            case 'z':
                funkcia_z(zaciatok, &zaciatok, &zaznam,&na);
                break;
            case 'u':
                funkcia_u(&zaznam,&na,&zaznam);
                break;
            case 'p':
                funkcia_p(&head, zaciatok,&na,&zaznam);
                break;
            case 'h':
                funkcia_h(zaciatok,&na);
                break;
            case 'r':
                funkcia_r(zaciatok,&zaznam,&na);
                break;

            case 'e':
                funkcia_e(zaciatok, &na, &zaznam);
                break;

            case 'k':
                tmp = zaciatok;
                while (zaciatok != NULL)
                {
                    tmp = zaciatok;
                    zaciatok = zaciatok->next;
                    free(tmp);

                }
                zaciatok = NULL;

                k = 0;
                break;

        }

    }


    return 0;
}








