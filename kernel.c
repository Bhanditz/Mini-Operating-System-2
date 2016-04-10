void readFile(char*,char*);
void printString (char*); 
void readString (char*);
int divide(int,int);
int modulus (int,int);
void readSector(char*, int);
void handleInterrupt21(int, int , int, int );
void executeProgram(char*,int);
void terminate();
void writeSector(char*,int); 
void deleteFile(char*);
void writeFile(char*, char*, int);
int getTheFirstEmptySectorNumber(char*);
void emptyArray (char*);
main()
{

//  	// test step 1
 // char buffer[13312]; /*this is the maximum size of a file*/
 // makeInterrupt21();

 // interrupt(0x21, 3, "tstprg\0", buffer, 0); /*read the file into buffer*/

 // interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
// while(1); /*hang up*/

// test step 2
// makeInterrupt21();
// printString("here1");
// interrupt(0x21, 4, "tstprg\0", 0x2000, 0);
// printString("here2");
// while(1);

// test step 3
  // makeInterrupt21();
  // interrupt(0x21, 5, "tstprg\0", 0x2000, 0);
  // while(1);

// test step4

 // char buffer[512];
 // makeInterrupt21();
 // interrupt(0x21, 6, "Hello Worlds", 30, 0);
 
 // readSector(buffer, 30);
 // printString(buffer);
 // while(1);

// test step5
// char buffer[13312];
// makeInterrupt21();
// interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
// interrupt(0x21, 3, "messag\0", buffer, 0); // try to read messag
// interrupt(0x21, 0, buffer, 0, 0); //print out the contents of buffer
//  while(1);
//   int i ;
//   char buffer2[13312];
// buffer2[0]="h"; buffer2[1]="e"; buffer2[2]="l";
//   for(i=0;i<6;i++){
//     if(buffer2[i]){
//       printString("found");
//     }else{
//       printString("not");
//     }
//   }

//  while(1);

  // test step6


//  int i=0;
//   char line[512];
//  char buffer1[13312];
// char buffer2[13312];
// buffer2[0]='h'; buffer2[1]='a'; buffer2[2]='t'; buffer2[3]='e';
// buffer2[4]='m';
// for(i=5; i<13312; i++) buffer2[i]=0x0;
// makeInterrupt21();
// interrupt(0x21,8, "testW\0", buffer2, 1); //write file testW
// printString(0xd);
// printString(0xa);
// interrupt(0x21,3, "testW\0", buffer1, 0); //read file testW
// printString(buffer1);

 makeInterrupt21();
 interrupt(0x21,4,"shell\0", 0x2000, 0); 
  while(1);
}

void printString (char* a){
int i ;
 if(a==0xd){
  interrupt(0x10 ,0xE*256 + a ,0,0,0 );
 }else{
    if(a==0xa){
      interrupt(0x10 ,0xE*256 +a ,0,0,0 );
    }else{
      for ( i=0 ; a[i]!='\0'; i++){
  interrupt(0x10 ,0xE*256 + a[i] ,0,0,0 );
}
    }
 }

 
}

void readString (char* a){

	int i = 0;
	while(1){
	 int asci = interrupt(0x16);
		if(asci == 0xd){
        interrupt(0x10 ,0xE*256 + 0xd ,0,0,0 );
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
		if(ax == 3){
     
			readFile(bx,cx);
			
		}else{
			if(ax ==4){
				executeProgram(bx,cx);
			}else{
				if(ax==5){
					terminate();
				}else{
          if(ax==6){
         
            writeSector(bx,cx);
          }else{
             if(ax==7){
              deleteFile(bx);
             }else{
              if(ax == 8){
                writeFile(bx,cx,dx);
              }else{
               printString("ERROR !!!");
              
              }
             }
             
          }
				
				}
				
			}
		}
	
}

 void readFile (char* a , char* buffer){
  
   char line[512];
   int i = 0;
   int fileNameCounter=0;
   int fileNumber = 0;
 
   int  sectorNumber = 0;
   readSector(line,2);
    
    
  
 
   for(i =0 ; i<512 ; i++ ){

   	if(fileNameCounter == 6 ){
   	//printString("heree1");
   		 if(i < (fileNumber+1)*32){
   		 	       
             if(line[i] != 0x0){
               
             	readSector(buffer+(512*sectorNumber),line[i]);
             	sectorNumber++;
             }else{
             	  
             	break;
             }
   		 }else{
   		 	break;
   		 }
   	}

     if(fileNameCounter < 6){
          
            if(line[i] == a[fileNameCounter] || !a[fileNameCounter]){
               
         		fileNameCounter++;
            //printString("here2");
          }else{
          
          	  fileNumber++;
            i = (fileNumber*32) -1;
            fileNameCounter = 0;

          }
        

         
     }

   }
   
  
}


void executeProgram(char* name, int segment){
	int i ;
     char buffer[13312];
     readFile(name,buffer);
     //printString("heree");
     for(i=0;i<13312;i++){
     	// if(buffer[i] != 0x0){
      //      printString("buffer");
      // }
     		//printString("here2");
     		putInMemory(segment,0x0000+i,buffer[i]);
     	//}else{
     	//break;
     	//}
     }
     launchProgram(segment);
}

void terminate(){


  makeInterrupt21();
 interrupt(0x21,4,"shell\0", 0x2000, 0); 
}


void writeSector(char* buffer, int sector){
  int relativeSector = modulus(sector,18) + 1;
  int head = modulus(divide(sector,18),2);
  int track =  divide(sector,36); 


   int AX = 3*256 +1;
  // int BX = buffer ; 
   int CX = track*256 +relativeSector;
   int DX = head*256 + 0 ;
 
  interrupt(0x13,AX,buffer,CX,DX);


}

void deleteFile(char* a){
    int flag = 0;
   int i = 0;
   int fileNameCounter=0;
   int fileNumber = 0;
  char mapArray [512];
  char line [512];
  readSector(mapArray,1);
  readSector(line,2);

    for(i =0 ; i<512 ; i++ ){

    if(fileNameCounter == 6){
    
       if(i < (fileNumber+1)*32){
                 // setting the filename to 0x0 in the dir
               if(flag == 0){
                line[i-6] = 0x0;
                line[i-5] = 0x0;
                line[i-4] = 0x0;
                line[i-3] = 0x0;
                line[i-2] = 0x0;
                line[i-1] = 0x0;
                flag =1;
               
               }

             if(line[i] != 0x0){
              
               mapArray[line[i]-1] = 0x00;
               line[i] = 0x0;
              
             }else{
                
              break;
             }
       }else{
        break;
       }
    }

     if(fileNameCounter < 6){
            if(line[i] == a[fileNameCounter]){
               
            fileNameCounter++;
          }else{
            
              fileNumber++;
            i = (fileNumber*32) -1;
            fileNameCounter = 0;

          }
        

         
     }

   }

    writeSector(mapArray,1);
    writeSector(line,2);

}
// int getSize(char* name){ 
//    int counter = 0; 

//       while(name[counnter] != null){ 
//           counter++;
//       }
// }
void writeFile(char* name, char* buffer, int secNum){
   int fileNameCounter =0;
      int i; 
     char mapArray [512];
     char directoryArray [512];
     char sectorBuffer [512];
     int emptyfileFound = 0;
      int bufferIndex = 0;
      int EmptySectorNumber;
      int j=0;
      int sectorNumber =0;
      readSector(mapArray,1);
      readSector(directoryArray,2); 
      
      for(i=0; i<512; i++){ 

       // checking for empty file

        if(directoryArray[i] != 0x00 && emptyfileFound == 0){
          i = i+31;
          
      
          
        }else{
          //printString("here2 \0");
        
          emptyfileFound =1;
        }
         if(directoryArray[i] == 0x0 && emptyfileFound ==1){ 
              // adding name of the file to the directory 

            if(fileNameCounter<6){  
                if(name[fileNameCounter]){
                  directoryArray[i] = name[fileNameCounter];
                  fileNameCounter++;
                }else{
                  //directoryArray[i]= 0x0;
                  fileNameCounter++;
                }
            } 
            else { 
               // adding the content of the file to the sector
                
                EmptySectorNumber = getTheFirstEmptySectorNumber(mapArray);
                if(secNum != 0){
                 
                  mapArray[EmptySectorNumber] = 0xFF;
                  directoryArray[i] = EmptySectorNumber;
                  for(j=0;j<512;j++){
                       
                     sectorBuffer[j]= buffer[(sectorNumber*32)+j];
                  }
                  writeSector(sectorBuffer,EmptySectorNumber);
                  EmptySectorNumber++;
                  secNum--;
                  bufferIndex++;
                  emptyArray(buffer);
                }else{
                 
                  break;
                }
            }
         }
      }
    writeSector(mapArray,1);
    writeSector(directoryArray,2);
}

int getTheFirstEmptySectorNumber(char* map){
  int i;
  for(i=0;i<512;i++){
    if(map[i] == 0x00){
      
      return i;
    }
  }
}

void emptyArray (char* line){
 
  int i ;

  for(i=0;i<512;i++){
    if(line[i]){

       line[i] = ' ';
    }
   
  }
  
}