#ifndef DIEMTHI_H
    #define DIEMTHI_H
    #ifndef SV_H             
        #include <SV.h>
    #endif
    #ifndef HP_H
        #include <HP.h>
    #endif

    #include <string.h>
    #include <stdio.h>
    #define fileDIEMTHI "D:\\ProjectKTLT\\fileBin\\DIEMTHI.bin"
    #define temp_fileDIEMTHI "D:\\ProjectKTLT\\fileBin\\temp_DIEMTHI.bin"

    enum SELECTION {LOWER, LOWER_EQ, EQUAL, GREAT_EQ, GREAT, ALL};
    typedef enum SELECTION SELECT; 

    struct DiemThi {
        long MSSV;          
        char maHP[8];
        float diem;
    };
    typedef struct DiemThi DT;

    

    int CheckExist_DT_toPosition(long MSSV, char maHP[]); 
    int WriteDT_toBIN(DT diemHPSV);
    int Delete_DT(long MSSV, char maHP[], int check);  
    int Update_DT(long MSSV, char maHP[], DT new_dthi, int position);

    /////       MỤC TIÊU CHO CÂU 4      ////
    //Chức năng chính:   In bảng điểm của 1 sinh viên
    void SelectDTBin_HP_BySV(long MSSV, float diem, SELECT choice);
    void PrintHeaderForDT_HP_SV(long MSSV);
    void PrintHP_bySV_with_diemHP(int position,HP hphan, float diem);

    ////        MỤC TIÊU CHO CÂU 5      ///
    //Chức năng phụ:   In bảng điểm của 1 môn học
    void SelectDTBin_SV_byHP(char maHP[], float diem, SELECT choice);
    void PrintHeaderForDT_SV_HP(HP hphan);
    void PrintSV_byHP_with_diemHP(int position,SV svien, float diem);


    void PrintDT(DT dthi, int position);

    int FolowSelect(float diemDT, SELECT choice, float diem);    
    int IsValid_SV_HP(long MSSV, char maHP[]);
    float Round_diemHP(float diem);
    int IsValid_diemHP(float diem);
    int IsBlank_DT(DT dthi);
    int ChangeStruct_To_DT_bin(int position,DT new_dthi);
    DT FindDT(int position);
    DT GetDT_withNoCheck(long MSSV, char maHP[]);

    void Sync_DT_binForSV(long del_MSSV);
    void Sync_DT_binForHP(char del_maHP[]);

    //////////////////// CODING /////////////////////////////////////

    DT GetDT_withNoCheck(long MSSV, char maHP[]){
        FILE * dtBin;
        DT new_DT;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        dtBin = fopen(fileDIEMTHI,"rb");
        if(dtBin!=NULL){
            while(ftell(dtBin)<sizeOfFile){
                fread(&new_DT,sizeof(DT),1,dtBin);
                if((new_DT.MSSV==MSSV) && (strcmp(new_DT.maHP,maHP)==0)){
                    break;
                }
            }
        }else{
            printf("\nGetDT_withNoCheck CANNOT OPEN FILE DIEMTHI.h\n");
        }
        fclose(dtBin);
        return new_DT;
    }

    
    int IsBlank_DT(DT dthi){
        if((dthi.MSSV==0) && (strcmp(dthi.maHP,"")==0) && (dthi.diem==-1)){
            return 0;
        }else{
            return -1;
        }
    }
    
    int IsValid_SV_HP (long MSSV, char maHP[]){
        int count = 0;
        int positionOfSV = CheckExist_SV_toPosition(MSSV);   
        int positionOfHP = CheckExist_HP_toPosition(maHP);     
        if(positionOfSV==-1){                                           
            count ++;
            printf("!!! ERROR: STUDENT NOT FOUND!!\n");
            printf("PLEASE READ \"SV.bin\" to check out!\n");
        }
        if(positionOfHP==-1){                                       
            count++;
            printf("!!! ERROR: SUBJECT NOT FOUND!!\n");
            printf("PLEASE READ \"HP.bin\" to check out!\n");
        }
        if(count!=0){
            return -1;
        }else{
            return 0;
        }
    }
    
    int IsValid_diemHP(float diem){
        if(diem<0 || diem >10){
            printf("UNVALID VALUE: NOT IN 0<= DIEM <=10 \n");
            return -1;
        }else{
            return 0;
        }
    }

    
    float Round_diemHP(float diem){
        int integer = diem;
        float decimalPart = diem - integer;
        if(decimalPart<0.5){
            diem = integer;
        }else if (decimalPart<0.75){
            diem = integer + 0.5;
        }else{
            diem = integer + 1;
        }
        return diem;
    }

    // Chức năng phụ cho selection
    int FolowSelect(float diemDT, SELECT choice, float diem){
        if(((choice == LOWER) && (diemDT<diem))
            ||((choice == LOWER_EQ) && (diemDT <= diem))
            ||((choice == EQUAL) && (diemDT == diem))
            ||((choice == GREAT_EQ) && (diemDT >= diem))
            ||((choice == GREAT) && (diemDT > diem)) ){
                return 0;
        }else{
            return -1;
        }
    }

    /////// Chức năng phụ cho SelectDTBin_HP_bySV(MSSV)
    void PrintHP_bySV_with_diemHP(int position,HP hphan, float diem){
        printf("\t\t|%3d  |%12s    |%20s   |%5d     |   %4.1f    |\n",position,hphan.maHP,hphan.tenHP,hphan.tin,diem);
        printf("\t\t+-----+----------------+-----------------------+----------+-----------+\n");

    }
    /////// Chức năng phụ cho SelectDTBin_HP_bySV(MSSV)
    void PrintHeaderForDT_HP_SV(long MSSV){
        printf("\n");
        printf("\t\t+---------------------------------------------------------------------+\n");
        printf("\t\t|\t\t\t%2s: %ld\t\t      |\n","BANG DIEM SVIEN",MSSV);
        printf("\t\t+-----+----------------+-----------------------+----------+-----------+\n"); 
        printf("\t\t|%4s |%14s  |%18s     |%10s|%9s  |\n","STT","Ma hoc phan","Ten hoc phan","So tin chi","DiemThi");
        printf("\t\t+-----+----------------+-----------------------+----------+-----------+\n");  
    }
    

    void SelectDTBin_HP_BySV(long MSSV, float diem, SELECT choice){
        SV svien = {0,"","","","",0,0,0};                   
        HP hphan = {"","",0};                               
        DT searchDt ;                                      
        FILE *dtBin;                                        
        int positionOfSV = CheckExist_SV_toPosition(MSSV);  
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);  
        int count=0;

        if(positionOfSV!=-1){
            svien = FindSV(positionOfSV);               
            PrintHeaderForDT_HP_SV(MSSV);
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                while(ftell(dtBin)<sizeOfFile){
                    fread(&searchDt,sizeof(DT),1,dtBin);
                    if(searchDt.MSSV==MSSV){
                        if ((FolowSelect(searchDt.diem,choice,diem)==0) || (choice == ALL)){
                            count++;
                            hphan = GetHP_withNoCheck(searchDt.maHP);
                            PrintHP_bySV_with_diemHP(count,hphan,searchDt.diem);
                        }
                    }
                }
            }else{
                printf("SelectDTBin_HP_BySV: CANNOT OPEN FILE DIEMTHI.bin\n");
            }
            fclose(dtBin);
        }else{
            printf("CAN'T PRINT\n");
        }

    }
    
    
    void PrintDT(DT dthi, int position){
        HP hphan;
        if(position>-1){
            PrintHeaderForDT_HP_SV(dthi.MSSV);
            hphan = GetHP_withNoCheck(dthi.maHP);
            PrintHP_bySV_with_diemHP(position,hphan,dthi.diem);
        }else{
            printf("NOT FOUND RECORD!\n");
        }
    }

    /// Chức năng phụ cho Print_DT_bin
    void PrintHeaderForDT_SV_HP(HP hphan){
        printf("\n");
        printf("+----------------------------------------------------------------------------------+\n");
        printf("|\t    %2s: %20s - %s - %d tin chi\t   |\n","BANG DIEM HOC PHAN MON: ",hphan.tenHP,hphan.maHP,hphan.tin);
        printf("+-----+----------------+------------+------------------+-----------+---------------+\n");
        printf("|%5s|%16s|%30s             |%15s|\n"," "," ","Ten Sinh vien"," "," ");
        printf("|%4s |%12s    |------------+------------------+-----------|%14s |\n","STT","Ma so SV","Diem Hoc Phan");
        printf("|%5s|%16s|%7s     |%10s        |%9s  |%15s|\n"," "," ","Ho","Dem","Ten"," ");
        printf("+-----+----------------+------------+------------------+-----------+---------------+\n");
    }
    void PrintSV_byHP_with_diemHP(int position,SV svien, float diem){
        printf("|%3d  |%12d    |%10s  |%17s |%9s  |   %6.1f      |\n"
        ,position,svien.MSSV, svien.ho, svien.dem, svien.ten
        , diem);
        printf("+-----+----------------+------------+------------------+-----------+---------------+\n");
    }
    

    void SelectDTBin_SV_byHP(char maHP[], float limit, SELECT choice){
        SV svien = {0,"","","","",0,0,0};                   
        HP hphan = {"","",0};                               
        DT searchDt ;
        FILE *dtBin;                                        
        int positionOfHP = CheckExist_HP_toPosition(maHP);  
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);  
        int count=0;

        if(positionOfHP!=-1){
            hphan = FindHP(positionOfHP);                
            PrintHeaderForDT_SV_HP(hphan);
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                while(ftell(dtBin)<sizeOfFile){
                    fread(&searchDt,sizeof(DT),1,dtBin);
                    if(strcmp(searchDt.maHP,maHP)==0){
                        if (FolowSelect(searchDt.diem,choice,limit)==0 || (choice == ALL)){
                            count++;
                            svien = GetSV_withNoCheck(searchDt.MSSV);
                            PrintSV_byHP_with_diemHP(count,svien,searchDt.diem);    
                        }
                    }
                }
            }else{
                printf("SelectDTBin_SV_ByHP: CANNOT OPEN FILE DIEMTHI.bin\n");
            }
            fclose(dtBin);
        }else{
            printf("CAN'T PRINT\n");
        }
    }

    
    int CheckExist_DT_toPosition(long MSSV, char maHP[]){
        FILE *dtBin;
        DT searchDT;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int count=0, result=0;
        int status = IsValid_SV_HP(MSSV,maHP);

        if(status==0){
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                while(ftell(dtBin)<sizeOfFile){
                    count++;
                    fread(&searchDT,sizeof(DT),1,dtBin);
                    if(searchDT.MSSV==MSSV && (strcmp(searchDT.maHP,maHP)==0)){
                        printf("THIS RECORD: %ld, %s EXISTED!!\n",MSSV,maHP);
                        result = count;
                        break;
                    }
                }
                if((ftell(dtBin)==sizeOfFile && result==0) || count==0){    
                    printf("THIS RECORD: %ld - %s DOESN'T EXISTS!!\n",MSSV,maHP);
                    result=-1;                                              
                }
            }else{
                printf("CheckExist_DT_toPosition: \n");
                printf("CANNOT OPEN FILE DIEMTHI.bin\n");
                printf("CHECK YOUR FILE STREAM AGAIN!!\n");
                result=-1;
            }
            fclose(dtBin);
            return result;
        }else{
            result = -2;
        }
        return result;
    }
    
    int ChangeStruct_To_DT_bin(int position,DT new_dthi){
        FILE *dtBin, *temp_dtBin;
        DT exchangeDT;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int indexByte=0;

        if(position>-1){
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                temp_dtBin = fopen(temp_fileDIEMTHI,"wb");
                if(temp_dtBin!=NULL){
                    while(indexByte<sizeOfFile){
                        if(indexByte!=(position-1)*sizeof(DT)){
                            fread(&exchangeDT,sizeof(DT),1,dtBin);
                            fwrite((char*)&exchangeDT,sizeof(DT),1,temp_dtBin);
                        }else{
                            if(IsBlank_DT(new_dthi)!=0){
                                fwrite((char*)&new_dthi,sizeof(DT),1,temp_dtBin);
                            }
                            fseek(dtBin,sizeof(DT),SEEK_CUR);
                        }
                        indexByte=ftell(dtBin);
                    }
                }else{
                    printf("CANNOT OPEN FILE temp_DT.bin\n");
                }
                fclose(temp_dtBin);
            }else{
                printf("CANNOT OPEN FILE DT.bin\n");
            }
            fclose(dtBin);

        }else{
            printf("UNVALID POSITION, NOTHING CHANGES!!\n");
        }
        if(indexByte!=0){
            if(remove(fileDIEMTHI)==0){
                rename(temp_fileDIEMTHI,fileDIEMTHI);
                return 0;
            }else{
                printf("UPDATE FAIL!!\n");
            }                
        }
        return -1;
    }
    
    int WriteDT_toBIN(DT new_diemHPSV){
        FILE *dtBin;
        int position = -1;
        if(IsValid_diemHP(new_diemHPSV.diem)==0){
            printf("WRITING....\n");
            new_diemHPSV.diem = Round_diemHP(new_diemHPSV.diem);
            dtBin = fopen(fileDIEMTHI,"ab");
            if(dtBin!=NULL){
                fwrite(&new_diemHPSV,sizeof(DT),1,dtBin);
                printf("INSERT SUCCESSFULLY!!\n");
                position = ftell(dtBin)/sizeof(DT);
            }else{ 
                printf("CANNOT OPEN DIEMTHI.bin\nCHECK YOUR FILE STREAM AGAIN!!\n");
            }    
            fclose(dtBin);
        }else{
            printf("INSERT FAIL!!\n");
        }
        return position;
    }

    // Chức năng phụ: Lấy dữ liệu Dthi từ vị trí trong file và in ra màn hình
    DT FindDT(int position){
        DT tempDT={0,"",-1};
        FILE *dtBin;

        if(position>-1){
            dtBin=fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                fseek(dtBin,(position-1)*sizeof(DT),SEEK_SET);
                fread(&tempDT,sizeof(DT),1,dtBin);
                PrintDT(tempDT,position);
            }else{
                printf("CANNOT OPEN FILE DT.bin\n");
            }
            fclose(dtBin);
        }else{
            printf("THIS OBJECT DOESN'T EXIST!!\n");
        }    
        return tempDT;
    }
         
    int Delete_DT(long MSSV, char maHP[],int check){
        int position=0, status=-1, count=0;
        DT searchDT;
        DT blankDT ={0,"",-1};
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        FILE *dtBin;

        if(check!=-1){
           position = CheckExist_DT_toPosition(MSSV,maHP);
        }else{
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                while(ftell(dtBin)<sizeOfFile){
                    count++;
                    fread(&searchDT,sizeof(DT),1,dtBin);
                    if((searchDT.MSSV==MSSV) && (strcmp(searchDT.maHP,maHP))==0){
                        position=count;
                        break;
                    }
                }
            }else{
                printf("DELETE DT CAN NOT OPEN FILE\n");
            }
            fclose(dtBin);
        }
        if(position>-1){
            status = ChangeStruct_To_DT_bin(position,blankDT);
            if(status!=0){
                printf("UNFORTUNATELY, DELETE RECORD UNSUCCESSFULLY!!\n");
            }else{
                
                printf("DELETE RECORD SUCCESSFULLY!!\n");
            }
        }else{
            printf("DELETE FAIL!!!\n");
        }
        return status;
    } 


    int Update_DT(long MSSV, char maHP[], DT new_dthi, int position){
        DT exchangeDT = {0,"",-1};           
        float new_diem;
        int status=-1;
        
        int positionOfNew = CheckExist_DT_toPosition(new_dthi.MSSV,new_dthi.maHP);
        if(position>-1 && positionOfNew >-2){               
            exchangeDT = FindDT(position);
            if((positionOfNew==position) || (positionOfNew==-1)){
                if(exchangeDT.MSSV!=new_dthi.MSSV){
                    printf("UPDATING.....MSSV => %ld\n",new_dthi.MSSV);
                    exchangeDT.MSSV=new_dthi.MSSV;
                }
                if(strcmp(exchangeDT.maHP,new_dthi.maHP)!=0){
                    printf("UPDATING.....HocPhan => %s\n",new_dthi.maHP);
                    strcpy(exchangeDT.maHP,new_dthi.maHP);
                }
                if(IsValid_diemHP(new_dthi.diem)==0){
                    new_diem = Round_diemHP(new_dthi.diem);
                    if(exchangeDT.diem!=new_diem){
                        printf("UPDATING.....diem => %4.1f\n",new_diem);
                        exchangeDT.diem=new_diem;
                    }
                    status = ChangeStruct_To_DT_bin(position,exchangeDT);
                    if(status!=-1){
                        printf("UPDATE RECORD SUCCESSFULLY!!\n");
                    }else{
                        printf("UNFORTUNATELY, UPDATE RECORD UNSUCCESSFULLY!!\n");
                    }
                }else{
                    printf("CAN'T UPDATE Diem!!\n");
                }
            }else{
                printf("ERROR: DATA DUPLICATED!!\n");
            }
        }else{
            printf("UPDATE FAIL!!\n");
        }
        return status;
    }
    
    
    void Sync_DT_binForSV(long del_MSSV){
        FILE *dtBin;
        DT dthi;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int position=0;
        int statusDel=-1;
        int count=0;

        while(position*sizeof(DT)<sizeOfFile){
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                if(count!=1){
                    fseek(dtBin,(position)*sizeof(DT),SEEK_SET);
                }else{
                    fseek(dtBin,(position-1)*sizeof(DT),SEEK_SET);
                    position--;
                }
                fread(&dthi,sizeof(DT),1,dtBin);
                position++;
            }else{
                printf("ERROR!!CAN NOT OPEN FILE SYNC\n");
            }
            fclose(dtBin);
            if(dthi.MSSV==del_MSSV){
                statusDel = Delete_DT(del_MSSV,dthi.maHP,-1);
                if(statusDel!=-1){
                    sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
                    count=1;
                    continue;
                }else{
                    printf("CAN NOT DELETE DT\n");
                }
                
            }
            count=0;
        }
    }

    
    void Sync_DT_binForHP(char del_maHP[]){
        FILE *dtBin;
        DT dthi;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int position=0;
        int statusDel=-1;
        int count=0;

        while(position*sizeof(DT)<sizeOfFile){
            dtBin = fopen(fileDIEMTHI,"rb");
            if(dtBin!=NULL){
                if(count!=1){
                    fseek(dtBin,(position)*sizeof(DT),SEEK_SET);
                }else{
                    fseek(dtBin,(position-1)*sizeof(DT),SEEK_SET);
                    position--;
                }
                fread(&dthi,sizeof(DT),1,dtBin);
                position++;
            }else{
                printf("ERROR!!CAN NOT OPEN FILE SYNC\n");
            }
            fclose(dtBin);
            if(strcmp(dthi.maHP,del_maHP)==0){
                statusDel = Delete_DT(dthi.MSSV,del_maHP,-1);
                if(statusDel!=-1){
                    sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
                    count=1;
                    continue;
                }else{
                    printf("CAN NOT DELETE DT\n");
                }
                
            }
            count=0;
        }
    }

#endif

