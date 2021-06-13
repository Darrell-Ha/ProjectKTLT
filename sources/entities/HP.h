#ifndef HP_H
    #define HP_H
    #include <stdio.h>
    #include <string.h>
    #define fileHP "D:\\ProjectKTLT\\fileBin\\HP.bin"
    #define temp_fileHP "D:\\ProjectKTLT\\fileBin\\temp_HP.bin"

    
    struct HocPhan{
        char maHP[8];           
        char tenHP[22];
        int tin;  
    };
    typedef struct HocPhan HP;         
    


    int WriteHP_ToBIN (HP hphan); 
    int Delete_HP(char infor[]);  
    int Update_HP(char infor[], HP new_hphan, int position);


    int CheckExist_HP_toPosition(char infor[]);  
    void PrintHeaderFor_HP();   
    void Print_HP_bin();        
    
    void PrintHP(HP hphan, int position);    
    HP FindHP(int position);  
    HP GetHP_withNoCheck(char maHP[]);

    int ChangeStruct_To_HP_bin(int position,HP new_hpan); 
    int IsBlank_HP(HP hphan);


    /////////--------------------CODING----------------/////////////
 
    int IsBlank_HP(HP hphan){
        if((strcmp(hphan.maHP,"")==0) &&(strcmp(hphan.tenHP,"")==0) && hphan.tin==-1){
            return 0;
        }else{
            return -1;
        }
    }


    void PrintHeaderFor_HP(){
        printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
        printf("\t\t\t|%4s |%14s  |%18s     |%10s|\n","STT","Ma hoc phan","Ten hoc phan","So tin chi");
        printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
    }


    /**     Chức năng phụ : in danh sách học phần hiện có       **/
    void Print_HP_bin(){
        HP tempHp;
        int sizeOfFile = GetSizeOf_bin(fileHP);
        int count=0;
        FILE *hpBin;

        printf("\n");
        printf("\t\t\t+---------------------------------------------------------+\n");
        printf("\t\t\t|\t\t%s\t\t  |\n","DANH SACH CAC HOC PHAN HIEN CO");
        PrintHeaderFor_HP();
        hpBin=fopen(fileHP,"rb");
        if(hpBin!=NULL){
            while(ftell(hpBin)<sizeOfFile){             
                fread(&tempHp, sizeof(HP),1,hpBin);
                printf("\t\t\t|%3d  |%12s    |%20s   |%5d     |\n",++count,tempHp.maHP,tempHp.tenHP,tempHp.tin);
                printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
            }
        }else{
            printf("CANNOT OPEN FILE HP.bin\n");
        }
        fclose(hpBin);
        
    }


    /**     Chức năng phụ: in học phần ra ngoài console|| IN: Học phần nào đó**/
    void PrintHP(HP hphan, int position){
        if(position!=-1){
            PrintHeaderFor_HP();
            printf("\t\t\t|%3d  |%12s    |%20s   |%5d     |\n",position,hphan.maHP,hphan.tenHP,hphan.tin);
            printf("\t\t\t+-----+----------------+-----------------------+----------+\n");
        }else{
            printf("NOT FOUND SUBJECT!!\n");
        }    
    }

    
    int ChangeStruct_To_HP_bin(int position,HP new_hpan){
        FILE *hpBin, *temp_hpBin;
        HP exchangeHP;
        int sizeOfFile = GetSizeOf_bin(fileHP);
        int indexByte=0;

        if(position!=-1){
            hpBin = fopen(fileHP,"rb");
            if(hpBin!=NULL){
                temp_hpBin = fopen(temp_fileHP,"wb");
                if(temp_hpBin!=NULL){
                    while(indexByte<sizeOfFile){
                        if(indexByte!=(position-1)*sizeof(HP)){
                            fread(&exchangeHP,sizeof(HP),1,hpBin);
                            fwrite((char*)&exchangeHP,sizeof(HP),1,temp_hpBin);
                        }else{
                            if(strcmp(new_hpan.maHP,"")!=0){
                                fwrite((char*)&new_hpan,sizeof(HP),1,temp_hpBin);
                            }
                            fseek(hpBin,sizeof(HP),SEEK_CUR);
                        }
                        indexByte=ftell(hpBin);
                    }
                }else{
                    printf("CANNOT OPEN FILE temp_HP.bin\n");
                }
                fclose(temp_hpBin);
            }else{
                printf("CANNOT OPEN FILE HP.bin\n");
            }
            fclose(hpBin);

        }else{
            printf("UNVALID POSITION, NOTHING CHANGES!!\n");
        }
        if(indexByte!=0){
            if(remove(fileHP)==0){
                rename(temp_fileHP,fileHP);
                return 0;
            }else{
                printf("UPDATE FAIL!!\n");
            }                
        }
        return -1;
    }

    
    int CheckExist_HP_toPosition(char infor[]){
        HP tempHp={"","",0};
        int sizeOfFile = GetSizeOf_bin(fileHP);
        int count=0,result=0;
        FILE *hpBin;

        hpBin=fopen(fileHP,"rb");
        if(hpBin!=NULL){
            while(ftell(hpBin)<sizeOfFile){
                count++;
                fread(&tempHp, sizeof(HP),1,hpBin);
                if(strcmp(tempHp.maHP,infor)==0 || strcmp(tempHp.tenHP,infor)==0){
                    printf("THIS SUBJECT: %s EXISTED!!!!\n",infor);
                    result=count;

                    break;
                }
            }
            if((ftell(hpBin)==sizeOfFile && result==0) || count==0){
                printf("THIS SUBJECT: %s DOESN'T EXIST!!\n",infor);
                result=-1;
            }
        }else{
            printf("CANNOT OPEN FILE HP.bin\n");
            result=-1;
        }
        fclose(hpBin);
        return result;
    }

    
    HP FindHP(int position){
        HP tempHp={"","",0};
        FILE *hpBin;

        if(position!=-1){
            hpBin=fopen(fileHP,"rb");
            if(hpBin!=NULL){
                fseek(hpBin,(position-1)*sizeof(HP),SEEK_SET);
                fread(&tempHp,sizeof(HP),1,hpBin);
                PrintHP(tempHp,position);
            }else{
                printf("CANNOT OPEN FILE HP.bin\n");
            }
            fclose(hpBin);
        }else{
            printf("THIS OBJECT DOESN'T EXIST!!\n");
        }    
        return tempHp;
    }
    


    HP GetHP_withNoCheck(char maHP[]){
        HP hphan={"","",0};
        FILE *hpBin;
        int sizeOfFile = GetSizeOf_bin(fileHP);
        hpBin = fopen(fileHP,"rb");
        if(hpBin!=NULL){
            while(ftell(hpBin)<sizeOfFile){
                fread(&hphan,sizeof(HP),1,hpBin);
                if(strcmp(hphan.maHP,maHP)==0){
                    fclose(hpBin);
                    break;
                }
            }
        }else{
            printf("GetHP_withNoCheck : CANNOT OPEN FILE HP.bin!!\n");
            fclose(hpBin);
        }
        return hphan;
    }

    int WriteHP_ToBIN (HP hphan){
        FILE *hpBin;
        int position=-1;

        hpBin=fopen(fileHP,"ab");
        if(hpBin!=NULL){
            if(IsBlank_HP(hphan)!=0){      
                fwrite(&hphan,sizeof(HP),1,hpBin);
                printf("INSERT SUCCESSFULLY!!\n");
                position = ftell(hpBin)/sizeof(HP);
            }else{
                printf("THIS SUBJECT is BLANK\n");
                printf("PLEASE READ \"HP.bin\" AGAIN BEFORE INSERTING ANOTHER!!\n");
            }
        }else{
            printf("CANNOT OPEN FILE HP.bin\n");
        }
        fclose(hpBin);
        return position;
    }
    
    int Delete_HP(char infor[]){
        
        int position = CheckExist_HP_toPosition(infor);
        int status=-1;
        HP blankHP ={"","",0};

        if(position!=-1){
            status = ChangeStruct_To_HP_bin(position,blankHP);
            if(status!=0){
                printf("UNFORTUNATELY, DELETE \"%s\" UNSUCCESSFULLY!!\n", infor);
            }else{
                printf("RESULT: \n");
                Print_HP_bin();
                printf("DELETE \"%s\" SUCCESSFULLY!!\n", infor);
            }
        }else{
            printf("DELETE FAIL!!!\n");
        }
        return status;
    }

    
    int Update_HP(char infor[], HP new_hphan, int position){
        FILE *hpBin, *temp_hpBin;
        HP exchangeHP = {"","",-2};
        int status=-1;
        int positionName, positionId;
        char old_maHP[8], old_tenHP[22];
        int old_tin;

        if(position!=-1){
            exchangeHP = FindHP(position);
            strcpy(old_maHP,exchangeHP.maHP);
            strcpy(old_tenHP,exchangeHP.tenHP);
            old_tin = exchangeHP.tin;
            if(strcmp(new_hphan.maHP,"")!=0){
                strcpy(exchangeHP.maHP,new_hphan.maHP);
            }
            if(strcmp(new_hphan.tenHP,"")!=0){
                strcpy(exchangeHP.tenHP,new_hphan.tenHP);
            }
            if(new_hphan.tin!=-1){
                if(new_hphan.tin<-1){
                    printf("ERROR!! Value for \"tin\" can't be negative!!\n");
                    printf("UPDATE FAIL!!\n");
                    return -1;
                }else{
                    exchangeHP.tin=new_hphan.tin;
                }
            }
            if(strcmp(old_maHP,exchangeHP.maHP)!=0 || strcmp(old_tenHP,exchangeHP.tenHP)!=0 || old_tin!=exchangeHP.tin){
                positionName = CheckExist_HP_toPosition(exchangeHP.tenHP);
                positionId = CheckExist_HP_toPosition(exchangeHP.maHP);
                if((positionId==position && positionName==-1)||(positionId==-1 && positionName==position)||(positionId==position && positionName==position)||(positionId==-1 && positionName ==-1)){
                    
                    status = ChangeStruct_To_HP_bin(position,exchangeHP);
                    if(status!=-1){
                        
                        if(strcmp(old_tenHP,exchangeHP.tenHP)!=0 ){
                            printf("UPDATE %s to %s SUCCESSFULLY!!\n",infor,exchangeHP.tenHP);
                        }
                        if(strcmp(old_maHP,exchangeHP.maHP)!=0){
                            printf("UPDATE %s to %s SUCCESSFULLY!!\n",infor,exchangeHP.maHP);
                        }
                        if(old_tin!=exchangeHP.tin){
                            printf("UPDATE %s: %d tin to %d tin  SUCCESSFULLY!!\n",infor,old_tin,exchangeHP.tin);
                        }
                        
                    }else{
                        printf("UNFORTUNATELY, UPDATE \"%s\" UNSUCCESSFULLY!!\n", infor);
                    }
                }else{
                    printf("%s EXISTED, READ HP.bin CAREFULLY\n",infor);
                }
            }else{
                printf("NOTHING CHANGE!!!\n");
            }
        }else{
            
            printf("UPDATE FAIL!!\n");
        }
        return status;
        
    }

#endif