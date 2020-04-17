/*
Name: Nicklaus Settoon
Project: PA-2 (Page Replacement Algorithm)
File: main.c
Instructor: Feng Chen
Class: cs4103-sp20
LogonID: cs410361
*/

#include <stdio.h>

struct page{
    int data;
    int pagenum;
};
typedef struct page pg;

pg* makePage(int _data, int _pagenum)
{//creates a new page object with the give parameters
    pg* newpage = malloc(sizeof *newpage);
    newpage->data = _data;
    newpage->pagenum = _pagenum;

    return newpage;
}

struct page_table_entry{
    struct page* pgaddr;
    unsigned int dirty : 1;
    unsigned int ref : 1;
    struct page_table_entry* prventry;
    struct page_table_entry* nxtentry;
};
typedef struct page_table_entry pgentry;

struct page_table{
    int currlength;
    int maxlength;
    unsigned int full : 1;
    pgentry* head;
    pgentry* tail;
};
typedef struct page_table table;

pgentry* insertPage(table* _tabletarget, pg* _targetpage, pgentry* _prventry)
{//creates an page table entry for the target page and inserts it after the target entry
    if (_tabletarget->full == 1) {//if page table is full
        printf("Cannot insert page: %d. Table is full.", _targetpage->pagenum);
        return NULL;
    }
    else {
        printf("Inserting page: %d", _targetpage->pagenum);
        pgentry* newentry = malloc(sizeof *newentry);
        newentry->pgaddr = _targetpage;
        newentry->dirty = 0;
        newentry->ref = 0;

        //adjust pointers
        newentry->prventry = _prventry;
        newentry->nxtentry = _prventry->nxtentry;
        _prventry->nxtentry = newentry;

        //update table metadata
        _tabletarget->currlength++;
        if (_tabletarget->currlength == _tabletarget->maxlength)
            _tabletarget->full = 1;
        
        return newentry;
    }
}

void deletePageEntry(table* _tabletarget, pgentry* _targetentry)
{
    //temp store appropriate pointers
    pg* page = _targetentry->pgaddr;
    pgentry* prv = _targetentry->prventry;
    pgentry* nxt = _targetentry->nxtentry;

    //stitch linked list together
    prv->nxtentry = nxt;
    nxt->prventry = prv;
    _tabletarget->currlength--;
    _tabletarget->full = 0;

    //if deleting the head of the linked list
    if(_tabletarget->head = _targetentry)
        _tabletarget->head = nxt;

    //if deleting the tail of the linked list
    if(_tabletarget->tail = _targetentry)
        _tabletarget->tail = prv;

    //free memory for page and its entry
    free(page);
    free(_targetentry);
}

pgentry* findPage(int _targetpage, table* _pagetable)
{//searches page table and returns page entry if found, NULL if not found.

}

pgentry* clockReplace(pgentry* _startpage)
{//CLOCK algorithm implementation for finding least recently used page for eviction from memory.

}

pgentry* swapIn(int _cost, int* _costcounter, int _targetpage, table* _tabletarget)
{//swaps the page frame from disk to memory, incrementing the counter.
    //make new page
    pg* newpage = makePage(0,_targetpage);

    //make new page table entry
    pgentry* newentry = insertPage(_tabletarget, newpage, _tabletarget->tail);

    //add on swap in cost
    (*_costcounter) += _cost;

    return newentry;
}

void swapOut(int _cost, int _costcounter, pgentry* _targetpage)
{//swaps the page frame from disk to memory, incrementing the counter.
    pg* victimpage = _targetpage->pgaddr;

}

int main(int argcount, char* argv[])
{//main is where the heart is.
    //get page frame count and create page table
    const int PAGE_FRAMES = *argv[1];
    table pages;
    pages.full = 0;
    pages.currlength = 0;
    pages.maxlength = PAGE_FRAMES;
    pages.head = NULL;

    //open page reference file
    FILE* pagerefs = fopen(argv[2],"r");

    //set memory access cost and init cost counter
    const int MEM_ACCESS_COST = *argv[3];
    int __totalmemaccesstime = 0;

    //set disk read cost and init cost counter
    const int SWAP_IN_COST = *argv[4];
    int __totalswapintime = 0;

    //set disk write cost and init cost counter
    const int SWAP_OUT_COST = *argv[5];
    int __totalswapouttime = 0;

    //counter for page references read from file
    int __totalrefcount = 0;

    //counter for page faults on read
    int __readfaults = 0;

    //counter for page faults on write
    int __writefaults = 0;

    if (pagerefs == NULL){//file isn't open
        printf("Couldn't open page references file.\n");
        return 0;
    }
    else//file is open
        printf("Page references file opened.\n");
    
    char currreadref[10];//need to set readline width = page frame digits + 2 
    char operation; //page operation read from file
    int pagenum;    //page number read from file
    
   tablewhile (fgets(currreadref, 10, pagerefs) != NULL)
    {//grab each page reference line in the text file
        __totalrefcount++;
        printf("%s", currreadref); //print the line
        sscanf(currreadref,"%s %d", &operation, &pagenum); //parse line

        if (page_table() == NULL) {//if page isn't in memory
            pgentry* newentry = swapIn(SWAP_IN_COST, &__totalswapintime, pagenum);//swap page in to memory

            if (pages.full == 1) {//if page table is full
                //find victim page
                //swap it out
                //put newentry in its place
            }
            else {//page table is empty
                //update
                //insert new page entry 
            }
            if (operation == 'r' || operation == 'R')
            {//if reference is a read
                newentry->ref = 1;//page has been read
                // printf("%d: read page %d\n", __totalrefcount, pagenum);
                __readfaults++;

            }
            else if (operation == 'w' || operation == 'W')
            {//if reference is a write
                newentry->ref = 1;//page has been read
                // printf("%d: write page %d\n", __totalrefcount, pagenum);
                __writefaults++;
            }
            else
            {
                printf("Did not understand reference #%d.\n", __totalrefcount);
            }
        }
        else {//page is found in memory
            /* code */
        }
        
        printf("\n");
    }
    fclose(pagerefs);
    
    return 0;
}