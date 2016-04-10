void printString (char*); 
void readString (char*);
int divide(int,int);
int modulus (int,int);
void readSector(char*, int);
void handleInterrupt21(int, int , int, int );

// main()
// {
// char line[80];
// printString("Enter a line: \0");
// readString(line);
// printString(line);
    
// 	while(1);
// }

void printString (char* a){
int i ;
for ( i=0 ; a[i]!='\0'; i++){
	interrupt(0x10 ,0xE*256 + a[i] ,0,0,0 );
} 
}

void readString (char* a){

	int i = 0;
	while(1){
	 int asci = interrupt(0x16);
		if(asci == 0xd){
			interrupt(0x10 ,0xE*256 + 0xa ,0,0,0 );
			interrupt(0x10 ,0xE*256 + 0x0,0,0,0 );
			a[i] = '\0';
			break;
		}else{
			if(asci == 0x8){
				interrupt(0x10 ,0xE*256 + asci ,0,0,0 );
				interrupt(0x10 ,0xE*256 + ' ' ,0,0,0 );
				interrupt(0x10 ,0xE*256 + asci ,0,0,0 );

				i = i -2 ;
			}else{
				a[i] = asci;
				interrupt(0x10 ,0xE*256 + asci ,0,0,0 );
			}
			
		}
           i = i+1;
	}
      
}

int divide(int number, int devisor) {

    int temp = 1;
    int quotient = 0;

    while (devisor <= number) {
        devisor <<= 1;
        temp <<= 1;
    }
   
    while (temp > 1) {
        devisor >>= 1;
        temp >>= 1;

        if (number >= devisor) {
            number -= devisor;
       
            quotient += temp;
        }
    }

    return quotient;
}

int modulus(int number, int devisor){
	int x = divide(number,devisor);
	int remidner = number - (x*devisor);
	return remidner;
}


void readSector(char* buffer, int sector){
  int relativeSector = modulus(sector,18) + 1;
  int head = modulus(divide(sector,18),2);
  int track =  divide(sector,36);	


   int AX = 2*256 +1;
   int BX = buffer ; 
   int CX = track*256 +relativeSector;
   int DX = head*256 + 0 ;
 
  interrupt(0x13,AX,BX,CX,DX);


}


void handleInterrupt21(int ax, int bx, int cx, int dx){
	if (ax == 0)
	{
		printString(bx);
	}
	else if (ax == 1)
	{
		readString(bx);
	}
	else if (ax == 2)
	{
		readSector(bx,cx);
	}
	else
		printString("ERROR !!!");
}
