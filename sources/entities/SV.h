#ifndef SV_H
    #define SV_H
    #include <stdio.h>
    #include <string.h>
    #define fileSV  "D:\\ProjectKTLT\\fileBin\\SV.bin"
    #define temp_fileSV "D:\\ProjectKTLT\\fileBin\\temp_SV.bin"
    

    struct SinhVien{
        long MSSV;
        char ho[10], dem[20], ten[8];
        char gioiTinh[4];
        int ngaySinh, thangSinh, nam;
    };
    typedef struct SinhVien SV;
    
    ////////    PROTOTYPE FOR SV

    int CheckExist_SV_toPosition(long MSSV);  
    int WriteSV_ToBIN (SV svien); 
    int Delete_SV(long MSSV);  
    int Update_SV(long MSSV, SV new_svien, int position);
 
    //////////////////////////////////////////////////////////////////   
    void Print_SV_bin();  
    void PrintHeaderFor_SV();
    void PrintSV(SV svien, int position); 

    SV FindSV(int position); 
    SV GetSV_withNoCheck(long MSSV); 
    int ChangeStruct_To_SV_bin(int position,SV new_svien);
    int IsBlank_SV(SV svien);       
    int IsValidDay(int ngay, int thang, int nam);      
    int GetSizeOf_bin(char fileName[]); 

    //////////////////       END PROTOTYPE      ///////////////////////////////
    /**
     * 
     * 
     * 
     * 
     * 
     * 
     * 
     * 
    **/  
    //////////////////////      CODING         //////////////////////////////


    int GetSizeOf_bin(char fileName[]){
        int sizeOfFile = 0;
        FILE *hpBin;
        hpBin = fopen(fileName,"rb");
        if(hpBin != NULL){
            fseek(hpBin,0,SEEK_END);                
            sizeOfFile = ftell(hpBin);              
            fseek(hpBin,0,SEEK_SET);            
        }else{
            printf("GetSizeOf_HP_bin: CANNOT OPEN File.bin!!\n");
            printf("%s\n",fileName);
            sizeOfFile = -1;
        }
        fclose(hpBin); 
        return sizeOfFile;   
    }
    

    int IsBlank_SV(SV svien){
        if((svien.MSSV == 0) && strcmp(svien.ho,"")==0 
        && strcmp(svien.dem,"")==0 
        && strcmp(svien.ten,"")==0 
        && strcmp(svien.gioiTinh,"")==0 
        && svien.ngaySinh==0 
        && svien.ngaySinh==0 
        && svien.nam==0){
            return 0;
        }else{
            return -1;
        }
    }


        int IsValidDay(int ngay, int thang, int nam){
            if(nam>=0){
                if(thang <1 || thang >12){
                    return -1;
                }else{
                    if(ngay==31){
                        if(thang!=2 && thang!=4 && thang!=6 && thang!=9 && thang!=11){
                            return 0;
                        }else{
                            return -1;
                        }
                    }else if(ngay==30){
                        if(thang==2){
                            return -1;
                        }else{
                            return 0;
                        }
                    }else if(ngay>31|| ngay<1){
                        return -1;
                    }else{
                        if(ngay==29 && thang ==2){
                            if((nam%400==0)||((nam%4==0) && nam%100!=0)){
                                return 0;
                            }else{
                                return -1;
                            }
                        }else{
                            return 0;
                        }
                    }    
                }       
            }else{
                return -1;
            }  
        }

    void PrintHeaderFor_SV(){
        printf("+-----+----------------+-------------------------------------------+---------------+-------------+\n");
        printf("|%5s|%16s|%30s             |%15s|%11s  |\n"," "," ","Ten Sinh vien"," "," ");
        printf("|%4s |%12s    |------------+------------------+-----------|%12s   |%11s  |\n","STT","Ma so SV","Ngay sinh","Gioi tinh");
        printf("|%5s|%16s|%7s     |%10s        |%9s  |%15s|%11s  |\n"," "," ","Ho","Dem","Ten"," "," ");
        printf("+-----+----------------+------------+------------------+-----------+---------------+-------------+\n");
    }



    void Print_SV_bin(){
        SV tempSv;
        int sizeOfFile = GetSizeOf_bin(fileSV);
        int count=0;
        FILE *svBin;

        printf("\n");
        printf("+------------------------------------------------------------------------------------------------+\n");
        printf("|\t\t\t\t%2s\t\t\t\t\t |\n","DANH SACH SINH VIEN HIEN CO");
        PrintHeaderFor_SV();
        
        svBin=fopen(fileSV,"rb");
        if(svBin!=NULL){
            while(ftell(svBin)<sizeOfFile){             
                fread(&tempSv, sizeof(SV),1,svBin);
                printf("|%3d  |%12d    |%10s  |%17s |%9s  |   %02d/%02d/%4d  |%8s     |\n"
                , ++count, tempSv.MSSV, tempSv.ho, tempSv.dem, tempSv.ten
                , tempSv.ngaySinh,tempSv.thangSinh,tempSv.nam,tempSv.gioiTinh);
                printf("+-----+----------------+------------+------------------+-----------+---------------+-------------+\n");
            }
        }else{
            printf("CANNOT OPEN FILE SV.bin\n");
        }
        fclose(svBin);
        
    }


    void PrintSV(SV svien, int position){
        if(position !=-1){
            PrintHeaderFor_SV();
            printf("|%3d  |%12d    |%10s  |%17s |%9s  |   %02d/%02d/%4d  |%8s     |\n",position,svien.MSSV,svien.ho,svien.dem,svien.ten,svien.ngaySinh,svien.thangSinh,svien.nam,svien.gioiTinh);
            printf("+-----+----------------+------------+------------------+-----------+---------------+-------------+\n");
        }else{
            printf("NOT FOUND!!\n");
        }
            
    }
    
    int ChangeStruct_To_SV_bin(int position,SV new_svien){
        FILE *svBin, *temp_svBin;
        SV exchangeSV;
        int sizeOfFile = GetSizeOf_bin(fileSV);
        int indexByte=0;

        if(position!=-1){
            svBin = fopen(fileSV,"rb");
            if(svBin!=NULL){
                temp_svBin = fopen(temp_fileSV,"wb");
                if(temp_svBin!=NULL){
                    while(indexByte<sizeOfFile){
                        if(indexByte!=(position-1)*sizeof(SV)){
                            fread(&exchangeSV,sizeof(SV),1,svBin);
                            fwrite((char*)&exchangeSV,sizeof(SV),1,temp_svBin);
                        }else{
                            if(IsBlank_SV(new_svien)!=0){
                                fwrite((char*)&new_svien,sizeof(SV),1,temp_svBin);
                            }
                            fseek(svBin,sizeof(SV),SEEK_CUR);
                        }
                        indexByte=ftell(svBin);
                    }
                }else{
                    printf("CANNOT OPEN FILE temp_SV.bin\n");
                }
                fclose(temp_svBin);
            }else{
                printf("CANNOT OPEN FILE SV.bin\n");
            }
            fclose(svBin);

        }else{
            printf("UNVALID POSITION, NOTHING CHANGES!!\n");
        }
        if(indexByte!=0){
            if(remove(fileSV)==0){
                rename(temp_fileSV,fileSV);
                return 0;
            }else{
                printf("UPDATE FAIL!!\n");
            }               
        }
        return -1;
    }

    int CheckExist_SV_toPosition(long MSSV){
        SV tempSV={0,"","","","",0,0,0};
        int sizeOfFile = GetSizeOf_bin(fileSV);
        int count=0,result=0;
        FILE *svBin;

        svBin=fopen(fileSV,"rb");
        if(svBin!=NULL){
            while(ftell(svBin)<sizeOfFile){
                count++;
                fread(&tempSV, sizeof(SV),1,svBin);
                if(tempSV.MSSV==MSSV){
                    printf("THIS STUDENT: %ld EXISTED!!!!\n",MSSV);
                    result=count;
                    break;
                }
            }
            if((ftell(svBin)==sizeOfFile && result==0) || count==0){
                printf("THIS STUDENT: %ld DOESN'T EXIST!!\n",MSSV);
                result=-1;
            }
        }else{
            printf("CANNOT OPEN FILE SV.bin\n");
            result=-1;
        }
        fclose(svBin);
        return result;
    }
    
    SV GetSV_withNoCheck(long MSSV){
        SV svien={0,"","","","",0,0,0};
        FILE *svBin;
        int sizeOfFile = GetSizeOf_bin(fileSV);
        svBin = fopen(fileSV,"rb");
        if(svBin!=NULL){
            while(ftell(svBin)<sizeOfFile){
                fread(&svien,sizeof(SV),1,svBin);
                if(svien.MSSV==MSSV){
                    fclose(svBin);
                    break;
                }
            }
        }else{
            printf("GetSV_withNoCheck : CANNOT OPEN FILE SV.bin!!\n");
            fclose(svBin);
        }
        return svien;
    }
    
    SV FindSV(int position){
        SV tempSV={0,"","","","",0,0,0};
        FILE *svBin;

        if(position!=-1){
            svBin=fopen(fileSV,"rb");
            if(svBin!=NULL){
                fseek(svBin,(position-1)*sizeof(SV),SEEK_SET);
                fread(&tempSV,sizeof(SV),1,svBin);
                PrintSV(tempSV,position);   // lưu ý
            }else{
                printf("CANNOT OPEN FILE SV.bin\n");
            }
            fclose(svBin);
        }else{
            printf("THIS OBJECT DOESN'T EXIST!!\n");
        }    
        return tempSV;
    }

    

    int WriteSV_ToBIN (SV svien){
        FILE *svBin;
        int position=-1;

        svBin=fopen(fileSV,"ab");
        if(svBin!=NULL){
            if(IsValidDay(svien.ngaySinh,svien.thangSinh,svien.nam)==0 && IsBlank_SV(svien)!=0){     
                fwrite(&svien,sizeof(SV),1,svBin);
                printf("INSERT SUCCESSFULLY!!\n");
                position=ftell(svBin)/sizeof(SV);
            }else{
                printf("PLEASE READ \"SV.bin\" AGAIN BEFORE INSERTING ANOTHER!!\n");
            }
        }else{
            printf("CANNOT OPEN FILE SV.bin\n");
        }
        fclose(svBin);
        return position;
    }
    
    int Delete_SV(long MSSV){
        
        int position = CheckExist_SV_toPosition(MSSV);
        int status=-1;
        SV blankSV ={0,"","","","",0,0,0};

        if(position!=-1){
            status = ChangeStruct_To_SV_bin(position,blankSV);
            if(status!=0){
                printf("UNFORTUNATELY, DELETE \"%ld\" UNSUCCESSFULLY!!\n", MSSV);
            }else{
                printf("RESULT: \n");
                Print_SV_bin();
                printf("DELETE \"%ld\" SUCCESSFULLY!!\n", MSSV);
            }
        }else{
            printf("DELETE FAIL!!!\n");
            status = position;
        }
        return status;

    }

    
    int Update_SV(long MSSV, SV new_svien, int position){
        SV exchangeSV = {0,"","","","",0,0,0};
        int status = -1;
        int checkPositionOfNew = CheckExist_SV_toPosition(new_svien.MSSV);
        
        if(IsBlank_SV(new_svien)==0){
            printf("UPDATE FAIL!! YOU CAN'T SET A BLANK SV INTO FILE\n");
        }else{
            if(position!=-1){
                if(checkPositionOfNew == position || checkPositionOfNew == -1){
                    exchangeSV = FindSV(position);
                    if(exchangeSV.MSSV!=new_svien.MSSV && checkPositionOfNew==-1 && new_svien.MSSV!=0){
                        exchangeSV.MSSV = new_svien.MSSV;
                        printf("UPDATING..... %ld: MSSV => %ld\n",MSSV,exchangeSV.MSSV);
                    }
                    if(strcmp(new_svien.ho,"")!=0 && strcmp(new_svien.ho,exchangeSV.ho)!=0){
                        strcpy(exchangeSV.ho,new_svien.ho);
                        printf("UPDATING..... %ld: ho => %s\n",MSSV,exchangeSV.ho);
                    }
                    if(strcmp(new_svien.dem,"")!=0 && strcmp(new_svien.dem,exchangeSV.dem)!=0 ){
                        strcpy(exchangeSV.dem,new_svien.dem);
                        printf("UPDATING..... %ld: dem => %s\n",MSSV,exchangeSV.dem);
                    }
                    if(strcmp(new_svien.ten,"")!=0 && strcmp(new_svien.ten,exchangeSV.ten)!=0){
                        strcpy(exchangeSV.ten,new_svien.ten);
                        printf("UPDATING..... %ld: ten => %s \n",MSSV,exchangeSV.ten);
                    }
                    if(strcmp(new_svien.gioiTinh,"")!=0 && strcmp(exchangeSV.gioiTinh,new_svien.gioiTinh)!=0){
                        strcpy(exchangeSV.gioiTinh,new_svien.gioiTinh);
                        printf("UPDATING..... %ld: gioiTinh => %s\n",MSSV,exchangeSV.gioiTinh);
                    }
                    if(new_svien.ngaySinh!=0){
                        exchangeSV.ngaySinh=new_svien.ngaySinh;
                        printf("UPDATING..... %ld: ngaySinh => %d\n",MSSV,exchangeSV.ngaySinh);
                    }
                    if(new_svien.thangSinh!=0){
                        exchangeSV.thangSinh=new_svien.thangSinh;
                        printf("UPDATING..... %ld: thangSinh => %d\n",MSSV,exchangeSV.thangSinh);
                    }
                    if(new_svien.nam!=0){
                        exchangeSV.nam=new_svien.nam;
                        printf("UPDATING..... %ld: nam => %d\n",MSSV,exchangeSV.nam);
                    }
                    if(IsValidDay(exchangeSV.ngaySinh,exchangeSV.thangSinh,exchangeSV.nam)==0){
                        status = ChangeStruct_To_SV_bin(position,exchangeSV);
                        if(status!=-1){
                            printf("UPDATE \"%ld\" SUCCESSFULLY!!\n",MSSV);
                        }else{
                            printf("UNFORTUNATELY, UPDATE \"%ld\" UNSUCCESSFULLY!!\n", MSSV);
                        }
                    }else{
                        printf("UPDATE FAIL!! THE INFORMATION_DAY INCORRECT!!\n");
                    }
                    
                }else{
                    printf("THIS STUDENT CAN'T BE UPDATED CAUSE ITS EXISTENCE!! PLEASE CHECK AGAIN\n");
                }

            }else{
                printf("UPDATE FAIL!!\n");
            }
        }
        return status;
    }



#endif