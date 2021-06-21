/*------Programmming Problem Chap 10 ---------
 implement a virtual memory manager
 group 16

------------------*/

//required header files
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int PAGE_TABLE_SIZE = 256;           //2^8 page table size
const int TLB_SIZE = 16;                   //16 enteries in table


struct TLB {                               //initializing TLB
	unsigned char pageNo[16];         //page number size
	unsigned char frameNo[16];        //frame number size
	int ind;                           // index
};

const int BUFFER_SIZE = 256;
const int PHYS_MEM_SIZE = 256;                       //page frame size


int read_Frame (int pageNumber, char *phys_Mem, int* openFrame){

	char one_frame[BUFFER_SIZE];
	memset(one_frame, 0, sizeof(one_frame));

// Backing store is a random access file
	FILE *fp;
	fp = fopen("BACKING_STORE.bin", "rb");
	if (fp == NULL){
		printf("File failed to open\n");
		exit(0);

	}

// c functions fseek() , fread() are used for performing i/o
	if (fread(one_frame, sizeof(char), PHYS_MEM_SIZE, fp)==0)
		printf("error in fread() function \n");

       // checking if the file has data available
	if (fseek(fp, pageNumber * PHYS_MEM_SIZE, SEEK_SET)!=0)
		printf("error in fseek() function \n");
		
// reading  256 bytes in available page frame
	int i = 0;
	for(i; i < PHYS_MEM_SIZE; i++){
		*((phys_Mem+(*openFrame)*PHYS_MEM_SIZE)+i) = one_frame[i];
		                      }
	(*openFrame)++;
	return (*openFrame)-1;
}




int findPage(int LAddress, char* PageTable, struct TLB *tlb,  char* phyMem, int* openFrame, int* pageFaults, int* TLBhits){

	unsigned char bit_mask = 0xFF;   //used masking to bit_mask  upper 16 bytes
	unsigned char offset;
	unsigned char pageNum;
	bool TLBhit = false;



       // printing the logical address of  page
	printf("Virtual adress: %d\t", LAddress);

       // extracting the page number and offset
	pageNum = (LAddress >> 8) & bit_mask;
	offset = LAddress & bit_mask;


	//checking if the tlb has the page present
	int frame = 0;
	int i = 0;
	for (i; i < TLB_SIZE; i++){
		if(tlb->pageNo[i] == pageNum){
			frame = tlb->frameNo[i];
			TLBhit = true;
			(*TLBhits)++;
		}

	}

	int value;
	int newFrame = 0;
	//Check if TLB does not contain the page we want
	if (TLBhit == false){
		//check if page table doesnot contain the page we want
		if (PageTable[pageNum] != -1){
		//	printf("Pagehit");
		}
		else{
	        //in case of page fault here
			newFrame = read_Frame(pageNum, phyMem, openFrame);
			PageTable[pageNum] = newFrame;
			(*pageFaults)++;

		}
		frame = PageTable[pageNum];
		tlb->pageNo[tlb->ind] = pageNum;
		tlb->frameNo[tlb->ind] = PageTable[pageNum];
		tlb->ind = (tlb->ind + 1)%TLB_SIZE;

	}
	int index = ((unsigned char)frame*PHYS_MEM_SIZE)+offset;
	value = *(phyMem+index);
	printf("Physical address: %d\t Value: %d\n",index, value);

	return 0;
}



//Main function begins here
int main (int argc, char* argv[]){

       if (argc < 2){
		printf("Not enough arguments\nProgram Exiting\n");
		exit(0);
	}
       FILE *fd;
	fd = fopen(argv[1], "r");
	if (fd == NULL){
		printf("File failed to open\n");
		exit(0);
	}


	int openFrame = 0;
	int pageFaults = 0;
	int TLBhits = 0;
	float pageFaultRate;
	float TLBHitRate;

//initializing page table
	unsigned char PageTable[PAGE_TABLE_SIZE];
	memset(PageTable, -1, sizeof(PageTable));


//initializing TLB
    struct TLB tlb;
	memset(tlb.pageNo, -1, sizeof(tlb.pageNo));
	memset(tlb.frameNo, -1, sizeof(tlb.frameNo));
	tlb.ind = 0;

//iniitalizng phyisical memory
	char PhyMem[PHYS_MEM_SIZE][PHYS_MEM_SIZE]; //65,536 bytes (256 frames × 256-byte frame size)

    int inputCount = 0;
	int v;

	while (fscanf(fd, "%d", &v)==1){
		findPage(v, PageTable, &tlb, (char*)PhyMem, &openFrame, &pageFaults, &TLBhits);
		inputCount++;
	}

	pageFaultRate = (float)pageFaults / (float)inputCount;
	TLBHitRate = (float)TLBhits / (float)inputCount;
	printf("*******   Page Fault Rate: %.4f  \n TLB hit rate= %.4f\n*****",pageFaultRate, TLBHitRate);
	pclose(fd);
	return 0;

}
