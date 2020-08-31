#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {
//
	acquire(&(shm_table.lock));
    	int exists = -1;
   	struct proc *curproc = myproc(); 	// for pgdir parameter
	int i;
    	for (i = 0; i < 64; i++) {
        	if (shm_table.shm_pages[i].id == id) {
			exists = i;
		}
    	}

    	if (exists >= 0) {	//case 1: id already exists
		uint newPointer = PGROUNDUP(curproc->sz);
                mappages(curproc->pgdir, (void*)newPointer, PGSIZE, V2P(shm_table.shm_pages[exists].frame), PTE_W | PTE_U);
                *pointer = (char*) newPointer;
                shm_table.shm_pages[exists].refcnt = shm_table.shm_pages[exists].refcnt + 1;
    	}

	else {	//case 2: does NOT exist yet
		int emptyPage = 0;
		for (i = 0; i < 64; i++) {
                	if (shm_table.shm_pages[i].id == 0 && shm_table.shm_pages[i].refcnt == 0) {
				if (emptyPage != -1) {
                        		emptyPage = i;
				}
        		}
		}
                shm_table.shm_pages[emptyPage].id = id;
                shm_table.shm_pages[emptyPage].frame = kalloc();
                memset(shm_table.shm_pages[emptyPage].frame, 0, PGSIZE);
                shm_table.shm_pages[emptyPage].refcnt = 1;
                uint newPointer = PGROUNDUP(curproc->sz);
                mappages(curproc->pgdir, (void*)newPointer, PGSIZE, V2P(shm_table.shm_pages[emptyPage].frame), PTE_W | PTE_U);
                *pointer = (char*) newPointer;
	}
	release(&(shm_table.lock));
//
return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//
	acquire(&(shm_table.lock));
	int i;
    	for (i = 0; i < 64; i++) {
        	if (shm_table.shm_pages[i].id == id) {
			shm_table.shm_pages[i].refcnt = shm_table.shm_pages[i].refcnt - 1;
			if (shm_table.shm_pages[i].refcnt == 0) { // reset everything to 0
				shm_table.shm_pages[i].id = 0;
            			shm_table.shm_pages[i].frame = 0;
			}
		}
    	}
    release(&(shm_table.lock));
//
return 0; //added to remove compiler warning -- you should decide what to return
}
