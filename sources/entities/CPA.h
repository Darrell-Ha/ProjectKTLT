#ifndef CPA_H
    #define CPA_H
    #ifndef SV_H
        #include <D:\ProjectKTLT\sources\entities\SV.h>
    #endif
    #ifndef HP_H
        #include <D:\ProjectKTLT\sources\entities\HP.h>
    #endif
    #ifndef DIEMTHI_H
        #include <D:\ProjectKTLT\sources\entities\DIEMTHI.h>
    #endif


    #define fileCPA "D:\\ProjectKTLT\\fileBin\\CPA.bin"
    #define temp_fileCPA "D:\\ProjectKTLT\\fileBin\\temp_CPA.bin"


    struct CPAForStudent{
        long MSSV;
        float cpa; 
    };
    typedef struct CPAForStudent CPA;

    

    //////      MỤC TIÊU CHO CÂU 3        /////
    // Chức năng chính: Tính điểm trung bình tích lũy theo thang 4 của sinh viên 

    CPA GetCPA_byCalc(long MSSV);      

    void Update_CPA_bin();
    void WriteAndUpdateCPA_toBIN(CPA cpaStudent, char nameFile[]);


    //          MỤC TIÊU CHO CÂU 6      ///
    // Chức năng chính: Hiển thị điểm trung bình tích lũy của sinh viên

    void PrintCPA_OfSV(long MSSV);

    void Print_CPA_bin();
    float Round_diem4(float diem);
    float Round_CPA(float cpa);
    int CheckExist_CPA_toPosition(long MSSV);
    void PrintHeaderForCPA();
    void PrintSV_WithCPA(int position, SV svien, float cpa);

    //////////////////      CODING          ////////////

    float Round_diem4(float diem){
        if(diem < 3.95){
            return 0;
        }else if (diem < 4.95){
            return 1;
        }else if (diem <5.45){
            return 1.5;
        }else if (diem <6.45){
            return 2;
        }else if (diem < 6.95){
            return 2.5;
        }else if (diem < 7.95){
            return 3;
        }else if (diem < 8.45){
            return 3.5;
        }else{
            return 4;
        }
    }

    float Round_CPA(float cpa){
        int integer;
        float decimal;
        float result = cpa*100;
        integer = result;
        decimal = result-integer;                   
        if(decimal<0.5){                            
            cpa = (float)integer/100;
        }else{
            cpa = (float)(integer+1)/100;
        }
        return cpa;
    }

    void PrintHeaderForCPA(){
        printf("\n");
        printf("\t+----------------------------------------------------------------------------------+\n");
        printf("\t|\t\t\t%s\t\t\t   |\n","BANG DIEM TRUNG BINH TICH LUY (CPA) ");
        printf("\t+-----+----------------+------------+------------------+-----------+---------------+\n");
        printf("\t|%5s|%16s|%30s             |%15s|\n"," "," ","Ten Sinh vien"," "," ");
        printf("\t|%4s |%12s    |------------+------------------+-----------|  %7s      |\n","STT","Ma so SV","CPA");
        printf("\t|%5s|%16s|%7s     |%10s        |%9s  |%15s|\n"," "," ","Ho","Dem","Ten"," ");
        printf("\t+-----+----------------+------------+------------------+-----------+---------------+\n");
    }

    void PrintSV_WithCPA(int position, SV svien, float cpa){
        printf("\t|%3d  |%12d    |%10s  |%17s |%9s  |   %6.2f      |\n"
        ,position,svien.MSSV, svien.ho, svien.dem, svien.ten
        , cpa);
        printf("\t+-----+----------------+------------+------------------+-----------+---------------+\n");
    }
    
    void PrintCPA_OfSV(long MSSV){
        FILE *cpaBin;
        SV searchSV;
        CPA searchCPA;

        int position = CheckExist_CPA_toPosition(MSSV);
        if(position!=-1){
            cpaBin = fopen(fileCPA,"rb");
            if(cpaBin!=NULL){
                searchSV = GetSV_withNoCheck(MSSV);                 
                fseek(cpaBin,(position-1)*sizeof(CPA),SEEK_SET);     
                fread(&searchCPA,sizeof(CPA),1,cpaBin);
                PrintHeaderForCPA();
                PrintSV_WithCPA(position,searchSV,searchCPA.cpa);
            }else{
                printf("PrintCPA_OfSV: CANNOT OPEN FILE CPA.bin\n");
            }
            fclose(cpaBin); 
        }else{
            printf("CANNOT PRINT!!\n");
        }
    }
    

    void Print_CPA_bin(){               
        FILE *cpaBin;
        SV svien = {0,"","","","",0,0,0};
        CPA search;
        int sizeOfFile= GetSizeOf_bin(fileCPA);
        int count=0;
        cpaBin = fopen(fileCPA,"rb");
        if(cpaBin!=NULL){
            PrintHeaderForCPA();
            while(ftell(cpaBin)<sizeOfFile){
                count++;
                fread(&search,sizeof(CPA),1,cpaBin);
                svien = GetSV_withNoCheck(search.MSSV);
                PrintSV_WithCPA(count,svien,search.cpa);
            }
        }else{
            printf("Print_CPA_bin: CANNOT OPEN CPA.bin\n");
        }
        fclose(cpaBin);
    }

    
    int CheckExist_CPA_toPosition(long MSSV){
        FILE *cpaBin;
        CPA searchCPA;
        int sizeOfFile = GetSizeOf_bin(fileCPA);
        int count =0, result =0;
        int statusSV = CheckExist_SV_toPosition(MSSV);
        if(statusSV!=-1){
            cpaBin=fopen(fileCPA,"rb");
            while(ftell(cpaBin)<sizeOfFile){
                count++;
                fread(&searchCPA,sizeof(CPA),1,cpaBin);
                if(searchCPA.MSSV==MSSV){
                    printf("THIS RECORD CPA EXISTED!!\n");
                    result = count;
                    break;
                }
            }
            if((ftell(cpaBin)==sizeOfFile && result==0) || count==0){
                printf("THIS RECORD CPA OF %ld DOESN'T EXIST!!\n",MSSV);
                result=-1;
            }
            fclose(cpaBin);
        }else{
            result = -1;
        }
        return result;
    }

    /** ------------------------------------------------------------------------------------------------------------ 
     * FUNCTION: Tính điểm CPA cho sinh viên dựa vào dữ liệu các file BIN
     * IN: Mã số sinh viên
     * OUT: CPA của sinh viên theo thang 4
     * - Duyệt file DIEMTHI.bin
     * - Tìm dữ liệu struct có cùng MSSV với đầu vào
     * - Mỗi lần tìm thấy sẽ tiến hành tìm struct HocPhan để lấy được dữ liệu tín học  
     * - Từ lượng tín học, lấy tín x điểm của môn đó (đã được làm tròn) bằng 1 tổng 
     *      lưu trữ số lượng tín đã học và tích lũy các tổng trên.
     * - Kết thúc duyệt file, lấy tích lũy tổng/số tín = CPA
     * - Kết quả thu được đem đi quy đổi cho thang 4 điểm
     * - return CPA thu được
     * *
     * **
     * *** DO DỮ LIỆU Ở 3 FILE là MSSV.bin, HP.bin, DIEMTHI.bin 
     *     Đều đã được đảm bảo tính đúng đắn, nhất quán 
     *     nên việc tính điểm CPA bằng 3 file trên sẽ không cần phải kiểm tra sự tồn tại của sinh viên ****
     * ---------------------------------------------------------------------------------------------------------------
    **/
    CPA GetCPA_byCalc(long MSSV){
        CPA result={0,0};                       
        HP tempHP;
        DT searchDT;
        float roundDiem4;
        int sizeOfFile = GetSizeOf_bin(fileDIEMTHI);
        int countTin=0, sumPoint=0;
        FILE *dtBin;

        dtBin = fopen(fileDIEMTHI,"rb");
        if(dtBin!=NULL){
            
            while(ftell(dtBin)<sizeOfFile){
                fread(&searchDT,sizeof(DT),1,dtBin);
                if(searchDT.MSSV==MSSV){
                    roundDiem4 = Round_diem4(searchDT.diem);
                    tempHP = GetHP_withNoCheck(searchDT.maHP);
                    countTin+=tempHP.tin;
                    sumPoint+=tempHP.tin*roundDiem4;
                }
            }
            if(countTin==0){                                            
                result.MSSV=-1;                                          
                printf("WARNING: DATA %ld IN FILE MAY BE LOST!!\n",MSSV);   
            }else{
                result.MSSV=MSSV;
                result.cpa=Round_CPA((float)sumPoint/countTin);
            }
        }else{
            printf("GetCPA_byCalc: CANNOT OPEN DIEMTHI.bin\n");
        }
        fclose(dtBin);
        return result;
    }

    
    void WriteAndUpdateCPA_toBIN(CPA cpaStudent, char nameFile[]){
        FILE *cpaBin;
        CPA searchCPA;
        cpaBin = fopen(nameFile,"ab");
        if(cpaBin!=NULL){
            cpaStudent.cpa = Round_CPA(cpaStudent.cpa);
            fwrite(&cpaStudent,sizeof(CPA),1,cpaBin);
            printf("WRITE and UPDATE CPA FOR %ld SUCCESFULLY\n",cpaStudent.MSSV);
        }else{  
            printf("WriteCPA_toBIN: CANNOT OPEN FILE CPA.bin\n");
        }
        fclose(cpaBin);
    }
    
    void Update_CPA_bin(){
        FILE *svBin, *cpaBin;
        SV searchSV;
        CPA new_CPA;
        int sizeOfFile =  GetSizeOf_bin(fileSV);
        svBin = fopen(fileSV,"rb+");
        if(svBin!=NULL){
            while(ftell(svBin)<sizeOfFile){
                fread(&searchSV,sizeof(SV),1,svBin);
                new_CPA = GetCPA_byCalc(searchSV.MSSV);
                if(new_CPA.MSSV!=-1){
                    WriteAndUpdateCPA_toBIN(new_CPA,temp_fileCPA);
                }
            }
            remove(fileCPA);
            rename(temp_fileCPA,fileCPA);
        }else{
            printf("Update_CPA_bin: CANNOT OPEN SV.bin!!\n");
        }
        fclose(svBin);   
    }



#endif