void emptyArray (char*,char*);
int getFileSectorsnumber (char*);

main(){
	while(1){
 char line[512];
 // 7 becase it is the longest command name length
 char commandName[7] ;
 char buffer[13312];
  char directoryArray[512];
char buffer2[13312];
//char buffer3[13312];
 int i =0;
 int j =0;
 int z=0;
 int x=0;
 int na=0;
 int k = 0;
 char fileName[10];
  char fileName2[10];

  int sectorsNumber = 0;
    int newFileSectors = 1;
   int check ;

   char directoryContents[16];
  interrupt(0x21,0,"SHELL>\0",0,0);
 interrupt(0x21,1,line,0,0);

 // get the command name
 for(i=0;i<7;i++){
 	
 	if(line[i] != " "){
 		
        commandName[i] = line[i];
 	}else{
 		
 		break;
 	}
 }
    
    if(commandName[0] == 'v' && commandName[1]=='i' && commandName[2]=='e' && commandName[3]=='w'){
    	for(i=5;i<512;i++){
    		if(line[i]){
            
              fileName[j] = line[i];
              j++;
    		}else{
    			fileName[j] = '\0';
          j=0;
    			break;
    		}
          }
            
            sectorsNumber= getFileSectorsnumber(fileName);
                  
                   if(sectorsNumber==0){
                     interrupt(0x21, 0, "No such file found\0", 0, 0);
                   }else{
                            interrupt(0x21, 3,fileName, buffer, 0); /*read the file into buffer*/
                            interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
                        sectorsNumber = 0;  
                   }
                     
          
            interrupt(0x21, 0, 0xd , 0, 0);                                  
              interrupt(0x21, 0, 0xa, 0, 0);
    	     emptyArray(buffer,line);
         emptyArray(fileName,fileName2);

    }else{
        if(commandName[0] == 'e' && commandName[1]=='x' && commandName[2]=='e' && commandName[3]=='c' && commandName[4]=='u' && commandName[5]=='t' && commandName[6]=='e') {
              for(i=8;i<512;i++){
        if(line[i]){
              fileName[j] = line[i];
              j++;
        }else{
          fileName[j] = "\0";
          j=0;
          break;
        }
          }
          sectorsNumber= getFileSectorsnumber(fileName);
                  
                   if(sectorsNumber==0){
                     interrupt(0x21, 0, "No such file found\0", 0, 0);
                   }else{
                         interrupt(0x21, 4, fileName, 0x2000, 0);
                        sectorsNumber = 0;  
                   }

         
            interrupt(0x21, 0, 0xd , 0, 0);                              
            interrupt(0x21, 0, 0xa, 0, 0);
         emptyArray(buffer,line);
         emptyArray(fileName,fileName2);
        }else{
             if(commandName[0] == 'd' && commandName[1]=='e' && commandName[2]=='l' && commandName[3]=='e' && commandName[4]=='t' && commandName[5]=='e'){
                  for(i=7;i<512;i++){
                     if(line[i]){
                  fileName[j] = line[i];
                  j++;
           }else{
                fileName[j] = '\0';
                j=0;
                break;
                }
             }   
                   sectorsNumber= getFileSectorsnumber(fileName);
                  
                   if(sectorsNumber==0){
                     interrupt(0x21, 0, "No such file found\0", 0, 0);
                   }else{
                        interrupt(0x21, 7, fileName, 0, 0);
                        interrupt(0x21, 0, "file is deleted\0", 0, 0);
                        sectorsNumber = 0;  
                   }
             
 
                
                   interrupt(0x21, 0, 0xd , 0, 0);                                 
                  interrupt(0x21, 0, 0xa, 0, 0);
                emptyArray(buffer,line);
         emptyArray(fileName,fileName2);
             }else{
                if(commandName[0] == 'c' && commandName[1]=='o' && commandName[2]=='p' && commandName[3]=='y'){
                            // getting the   first file name
                         j=0; 
                         z=0;      
                  for(i=5;i<512;i++){

                     if(line[i] !=' '){
                       //interrupt(0x21, 0, "ja \0", 0, 0);
                  fileName[j] = line[i];
                  j++;
                  z++;
                     }else{
                       if(z<6){
                           fileName[j]=0x0;
                            z++;
                            j++;
                       }else{
                          fileName[j] = '\0';
                           j=0;
                           z=0;
                       }
                   
                     break;
                       }
                   }
                         
                         // getting the second file name
                            j=0;
                     for(z=i+1;z<512;z++){
                     if(line[z]){
                     
                  fileName2[j] = line[z];
                  j++;
                     }else{
                       if(z<6){
                           fileName2[j]=0x0;
                            z++;
                            j++;
                       }else{
                          fileName2[z] = '\0';
                           j=0;
                           z=0;
                                break;
                       }
                   

                
                       }
                   }
                   

                   
                        
                   
                   // get the number of sectors for file1 data
                    
                    

                  sectorsNumber= getFileSectorsnumber(fileName);
                  
                   if(sectorsNumber==0){
                     interrupt(0x21, 0, "No such file found\0", 0, 0);
                   }else{
                    interrupt(0x21, 3,fileName, buffer, 0);/*read the file1 into buffer*/
                    interrupt(0x21,8, fileName2, buffer, sectorsNumber); 
                    interrupt(0x21, 0, "Copying completed successfully\0", 0, 0);
                   }
                    
                                        interrupt(0x21, 0, 0xd , 0, 0);                                 
                                        interrupt(0x21, 0, 0xa, 0, 0);
                                        emptyArray(buffer,line);
                                        emptyArray(fileName,fileName2);
               
                  


                }else
                { 
                    if(commandName[0] == 'd' && commandName[1]=='i' && commandName[2]=='r'){
                     
                              char line[512];
                              int i = 0;
                              int fileNameCounter=0;
                              int fileNumber = 0;
                              
                              interrupt(0x21,2,line,2,0); // load directory
                              for(i=0;i<512;i+=32){
                               //interrupt(0x21, 0, "Bad!\0", 0, 0);
                                     if(line[i]!=0x0){
                                       //interrupt(0x21, 0, "Bad2!\0", 0, 0);
                                     for(j=0;j<6;j++){
                                       if(line[i+j] != 0x0){
                                         fileName2[j] = line[i+j];
                                       }
                                     
                                     }
                                     j++;

                                     interrupt(0x21, 0, 0xd , 0, 0);
                                     interrupt(0x21, 0, 0xa, 0, 0);
                                     
                                    interrupt(0x21, 0, fileName2, 0, 0);
                                                
                                               emptyArray(fileName,fileName2);
                                   }
                                 }
                                  interrupt(0x21, 0, 0xa, 0, 0);
                                     interrupt(0x21, 0, 0xd , 0, 0);
                              }
                                    
                    else{
                        if(commandName[0] == 'c' && commandName[1]=='r' && commandName[2]=='e' && commandName[3]=='a' && commandName[4]=='t' && commandName[5]=='e'){
                             
                             for(i=7;i<512;i++){
                               if(line[i]){
                               fileName[j] = line[i];
                              j++;
                               }else{
                                      fileName[j] = '\0';
                                          j=0;
                                       break;
                                      }
                                        } 
                             
                             
                              z=0;  
                            while(1){
                            
                              interrupt(0x21,1,buffer,0,0);
                                     
                                  if(buffer[0] == 0x0){
                                         interrupt(0x21, 0, "The file is stored successfully\0", 0, 0);
                                         interrupt(0x21, 0, 0xd , 0, 0);
                                         interrupt(0x21, 0, 0xa, 0, 0);
                                   break;
                                  }else{
                                    for(i=0;i<13312;i++){
                                        //interrupt(0x21, 0, "here4 \0", 0, 0);
                                        // if(buffer[i]== 0x0){
                                        //     interrupt(0x21, 0, "here5 \0", 0, 0);
                                        // }
                                    if(buffer[i]){
                                      //interrupt(0x21, 0, "here2 \0", 0, 0);
                                      if(j<512){
                                             
                                             j++;
                                          }else{
                                            newFileSectors++;
                                            j=1;
                                          }

                                      buffer2[z] = buffer[i];
                                      z++;
                                    }else{
                                
                                      break;
                                    }
                                  } 
                                  }
                                
                                  buffer2[z] = ' ';
                                      z++;                           
                            }
                            interrupt(0x21,8, fileName, buffer2, newFileSectors);
                               interrupt(0x21, 0, 0xd , 0, 0);
                        interrupt(0x21, 0, 0xa, 0, 0);
                       }else{
                         interrupt(0x21, 0, "Bad Command!\0", 0, 0);
                         interrupt(0x21, 0, 0xd , 0, 0);
                        interrupt(0x21, 0, 0xa, 0, 0);
                       emptyArray(buffer,line);
                       emptyArray(fileName,fileName2);
                       }
                      
                    } 
               
                 }
        }
   
    } 

  }
}
     


}


void emptyArray (char* buffer,char* line){
 
  int i ;
  int j;
  for(i=0;i<512;i++){
    if(line[i]){

       line[i] = ' ';
    }
   
  }
  for(j=0;j<13312;j++){
    if(buffer[j]){
     buffer[j]= ' ';
    }
  }
}


int getFileSectorsnumber (char* a){
      int sectorsNumber = 0;
   char line[512];
   int i = 0;
   int fileNameCounter=0;
   int fileNumber = 0;
   int j =0;
  interrupt(0x21,2,line,2,0); // load directory

  
  
 
   for(i =0 ; i<512 ; i++ ){

    if(fileNameCounter == 6 ){
    //printString("heree1");
   
       if(i < (fileNumber+1)*32){
                     
             if(line[i] != 0x0){
               
                 
              sectorsNumber++;
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

          //interrupt(0x21, 0, "here3\0", 0, 0);
              fileNumber++;
            i = (fileNumber*32) -1;
            fileNameCounter = 0;
            
          }
        

         
     }

  }
  return sectorsNumber; 
  
}