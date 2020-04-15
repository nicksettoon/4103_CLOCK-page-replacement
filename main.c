/*
Name: Nicklaus Settoon
Project: PA-2 (Page Replacement Algorithm)
File: main.c
Instructor: Feng Chen
Class: cs4103-sp20
LogonID: cs410361
*/

#include <stdio.h>


struct clock_entry{
    int* pgaddr;
    unsigned int dirty : 1;
    unsigned int ref : 1;
    struct clock_entry* nextpage;
};
typedef struct clock_entry clk;

// enum PageOperation {READ = 0, WRITE};
// struct page_ref_list_entry{
//     enum PageOperation op;
//     int pagenum;
//     struct page_ref_list_entry* nextref;
// };
// typedef struct page_ref_list_entry pg_ref;
// pg_ref* listhead;   //head of the page reference list
// pg_ref* prevref = &listhead; // 
// pg_ref* ref = (pg_ref *) malloc(sizeof(pg_ref));
// ref->pagenum = pagenum;
// ref->op = 0;

int main(int argcount, char* argv[]) {

    //get page frame count
    const int PAGE_FRAMES = *argv[1];
    //open page reference file
    FILE* page_refs = fopen(argv[2],"r");
    //set memory access cost
    const int MEM_ACCESS_TIME = *argv[3];
    //set disk read cost
    const int SWAP_IN_TIME = *argv[4];
    //set disk write cost
    const int SWAP_OUT_TIME = *argv[5];

    if (page_refs == NULL){//file isn't open
        printf("Couldn't open page references file.\n");
        return 0;
    }
    else
        printf("Page references file opened.\n");
    
    int i = 0; //counter for page currentref count
    char currentref[10];//need to set readline width = page frame digits + 2 

    char operation; //page operation read from file
    int pagenum;    //page number read from file
    
    while (fgets(currentref, 10, page_refs) != NULL)
    {//grab each page reference line in the text file
        i++;
        printf("%s", currentref); //print the line
        sscanf(currentref,"%s %d", &operation, &pagenum); //parse line

        if (operation == 'r' || operation == 'R')
        {//if reference is a read
            printf("%d: read page %d\n", i, pagenum);
        }
        else if (operation == 'w' || operation == 'W')
        {//if reference is a write
            printf("%d: write page %d\n", i, pagenum);
        }
        else
        {
            printf("Did not understand reference #%d.\n", i);
        }
        printf("\n");
    }
    fclose(page_refs);
    
    return 0;
}