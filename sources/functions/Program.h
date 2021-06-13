#ifndef PROGRAM_H
    #define PROGRAM_H
    #ifndef SV_H
        #include <D:\ProjectKTLT\sources\entities\SV.h>
    #endif
    #ifndef HP_H
        #include <D:\ProjectKTLT\sources\entities\HP.h>
    #endif
    #ifndef DIEMTHI_H
        #include <D:\ProjectKTLT\sources\entities\DIEMTHI.h>
    #endif
    #ifndef CPA_H
        #include <D:\ProjectKTLT\sources\entities\CPA.h>
    #endif
    #ifndef ANSI_H
        #include <D:\ProjectKTLT\sources\functions\ANSI-color-codes.h>    
    #endif
    
    #include <string.h>
    #include <conio.h>
    #include <stdio.h>
    #include <stdlib.h>


    #define COL_BG          WHTHB          
    #define COL_Txt_inBG    UBLK           
    #define COL_Font        BHWHT          
    #define COL_Font_Notice BHGRN          
    #define COL_Font_Warn   BHRED          
    #define COL_Font_Check  BHCYN            
 
    enum switchKey {KEY_UP = 72, KEY_DOWN = 80, KEY_RIGHT = 77, KEY_LEFT = 75, ESC=27};
    typedef enum switchKey SWITCH;

    enum symBol {
        TOGGLE_RIGHT = 16, TOGGLE_LEFT = 17, TOGGLE_UP = 30,TOGGLE_DOWN = 31,
        ARROW_UP = 24, ARROW_DOWN = 25 ,ARROW_RIGHT = 26, ARROW_LEFT = 17, 
        ITEM = 4, BORDER = 177, HEART = 3 
    };
    typedef enum symBol SYMBOL;

    enum processing {INSERT = 1, DELETE, UPDATE};
    typedef enum processing PROCESS;

    //Prototype for Menu
    void InstructionMENU();
    void InstructionTOGGLE();
    void Menu();
    void PrintBorder(int count, char color[], SYMBOL type); 
    void PrintBlank(int count);
    void HeaderToMenu_SECTION(int subsection);
    void Header();

    int MenuSubsection1(int subsection);
    int MenuSubsection2(int subsection);
    int GetMenuSubsection(int section, int subsection);
    ///// End prototype for menu
    

    //// Prototype for Program
    void ProgramSection1(int subsection);   // chạy view data

    void Control_DiemThi();
    void Control_CPA();
    void ProgramSection2(int subsection);   // chạy interact data
    
    void Control_WriteData();
    void Process_WriteData_SV();
    void Process_WriteData_HP();
    void Process_WriteData_DT();


    void Control_DeleteData();
    void Process_DeleteData_SV();
    void Process_DeleteData_HP();
    void Process_DeleteData_DT();



    void Control_UpdateData();
    void Process_UpdateData_SV();
    void Process_UpdateData_HP();
    void Process_UpdateData_DT();
    void Process_UpdateData_CPA();

    void StatusProcess(PROCESS type, int count, char colorStatus[]);    
    // End prototype for program


   /////////////////////////////////        CODING      ///////////////////////////////
    
    void StatusProcess(PROCESS type, int count, char colorStatus[]){
        
        system("cls");
        Header();
        printf("\n");
        printf(colorStatus);
        if(type == INSERT){
            printf("INSERTING: ");
        }else if(type == UPDATE){
            printf("UPDATING: ");
        }else{
            printf("DELETING: ");
        }
        PrintBorder(count, colorStatus, BORDER);
        printf(reset "\n");
    }

    ///////////////////        BEGIN PROGRAM 1       ////////////////////

    void Control_DiemThi(){
        char maHP[8] = "";
        long MSSV=0;
        float diem;
        char pointerPro;
        SELECT type;
        printf(COL_Font_Notice"('^_^'')"COL_Font" You want a list which: \n"reset);
        printf(COL_Font_Notice"\t a. Is a record of a specific student?\n");
        printf("\t b. Is a record of a specific subject?\n" reset);
        printf(COL_Font"\t Type a or b: "reset);
        fflush(stdin);
        pointerPro = getchar();
        printf("\n");
        while((pointerPro != 'a')&& (pointerPro!='b')){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
            fflush(stdin);
            pointerPro = getchar();
        }
        if(pointerPro == 'a'){
            printf(COL_Font_Notice"('^_^'')"COL_Font" Please type"COL_Font_Notice" MSSV: " reset);
            scanf("%d",&MSSV);
        }else{
            printf(COL_Font_Notice"('^_^'')"COL_Font" Please type"COL_Font_Notice" maHP: " reset);
            scanf(" %[^\n]%*c",maHP);
        }
        printf(COL_Font_Notice"('^_^'') You want all of record, don't you?? (y/n): "reset);
        fflush(stdin);
        pointerPro = getchar();
        printf("\n");
        while((pointerPro != 'y') && (pointerPro!='n')){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
            fflush(stdin);
            pointerPro = getchar();
        }
        if(pointerPro == 'n'){
            printf(COL_Font_Notice"('^_^'')???"COL_Font" Set the point to be limitation: " reset);
            scanf("%f",&diem);
            printf(COL_Font_Notice"('^_^'')???"COL_Font" Type your selection\n"reset);
            printf(COL_Font_Notice"\ta. Lower than limit\n");
            printf("\tb. Lower or equal limit\n");
            printf("\tc. Equal limit\n");
            printf("\td. Greater or equal limit\n");
            printf("\te. Greater than limit\n");
            printf(COL_Font"\tType a,b,c,d,e: "reset);
            fflush(stdin);
            pointerPro = getchar();
            if(pointerPro=='a'){
                type = LOWER;
            }else if(pointerPro =='b'){
                type = LOWER_EQ;
            }else if(pointerPro == 'c'){
                type = EQUAL;
            }else if(pointerPro == 'd'){
                type = GREAT_EQ;
            }else if(pointerPro == 'e'){
                type = GREAT;
            }else{
                type = ALL;
            }
        }else{
            type = ALL;
        }
        system("cls");
        Header();
        printf("\n");
        printf(COL_Font_Notice"\\('^O^')/ HERE WE GO!!" reset "\n");
        if(MSSV!=0){
            SelectDTBin_HP_BySV(MSSV,diem,type);
        }else{
            SelectDTBin_SV_byHP(maHP,diem,type);
        }
    }

    void Control_CPA(){
        long MSSV=0;
        char pointerPro;
        printf(COL_Font_Notice"('^_^'')"COL_Font" You want a list which: \n" reset);
        printf(COL_Font_Notice"\t a. Is a record of a specific student?\n");
        printf("\t b. Is a list of All of Student?\n"reset);
        printf(COL_Font"\t Type a or b: "reset);
        fflush(stdin);
        pointerPro = getchar();
        while((pointerPro != 'a')&& (pointerPro!='b')){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
            fflush(stdin);
            pointerPro = getchar();
        }
        if(pointerPro == 'a'){
            printf(COL_Font_Notice"('^_^'')"COL_Font" Please type MSSV: " reset);
            scanf("%d",&MSSV);
        }
        system("cls");
        Header();
        printf("\n");
        printf(COL_Font_Notice"\n\\('^O^')/ HERE WE GO!!" reset "\n");
        if(MSSV!=0){
            PrintCPA_OfSV(MSSV);
        }else{
            Print_CPA_bin();
        }
    }


    ////////////////////////////////        END PROGRAM 1           //////////////////////////////////

    ///////////////////////////////         BEGIN PROGRAM 2         //////////////////////////////////
    
    void Process_WriteData_SV(){
        SV new_Sv;
        int position ; 
        StatusProcess(INSERT, 5,COL_Font_Notice);
        printf(COL_Font_Notice"%cNEW SinhVien:" reset "\n",ITEM);
        printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" MSSV: " reset);
        scanf("%d",&new_Sv.MSSV);
        while(new_Sv.MSSV<10000000 || new_Sv.MSSV>99999999){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
            scanf("%d",&new_Sv.MSSV);
        }
        position = CheckExist_SV_toPosition(new_Sv.MSSV);
        if(position==-1){               /// Nếu MSSV nhập vào chưa tồn tại
            StatusProcess(INSERT, 20, COL_Font_Notice);
            printf(COL_Font_Check"\n\t\t%c%c CAN INSERT %ld! %c%c" reset "\n\n",TOGGLE_RIGHT,TOGGLE_RIGHT,new_Sv.MSSV,TOGGLE_LEFT,TOGGLE_LEFT);
            printf(COL_Font_Notice"%cNEW SinhVien: %ld" reset "\n",ITEM,new_Sv.MSSV);

            printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" Family Name: " reset);
            scanf(" %[^\n]%*c",new_Sv.ho);
            while(strcmp(new_Sv.ho,"")==0){
                printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! Not Blank DATA!: " reset );
                scanf(" %[^\n]%*c",new_Sv.ho);
            }
            printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" Middle Name: " reset);
            scanf(" %[^\n]%*c",new_Sv.dem);
            while(strcmp(new_Sv.dem,"")==0){
                printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! Not Blank DATA!: " reset );
                scanf(" %[^\n]%*c",new_Sv.dem);
            }
            printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" Name: " reset);
            scanf(" %[^\n]%*c",new_Sv.ten);
            while(strcmp(new_Sv.ten,"")==0){
                printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! Not Blank DATA!: " reset );
                scanf(" %[^\n]%*c",new_Sv.ten);
            }
            StatusProcess(INSERT,50, COL_Font_Notice);
            printf(COL_Font_Notice"%cNEW SinhVien: %ld %c %s %s %s" reset "\n",
                ITEM,new_Sv.MSSV,
                ARROW_LEFT,new_Sv.ho,new_Sv.dem,new_Sv.ten);
            printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" DateOfBirth: " reset "\n");
            printf(COL_Font_Notice"\tNgaySinh: "reset);
            scanf("%d",&new_Sv.ngaySinh);
            printf(COL_Font_Notice"\tThangSinh: "reset);
            scanf("%d",&new_Sv.thangSinh);
            printf(COL_Font_Notice"\tNamSinh: "reset);
            scanf("%d",&new_Sv.nam);

            StatusProcess(INSERT,70,COL_Font_Notice);
            printf(COL_Font_Notice"%cNEW SinhVien: %ld %c %s %s %s %c %02d/%02d/%d" reset "\n",
                ITEM,new_Sv.MSSV,
                ARROW_LEFT,new_Sv.ho,new_Sv.dem,new_Sv.ten,
                ARROW_LEFT,new_Sv.ngaySinh, new_Sv.thangSinh, new_Sv.nam);
            printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" Gender: (Nam/Nu): " reset);
            scanf(" %[^\n]%*c",new_Sv.gioiTinh);

            strcpy(new_Sv.gioiTinh,strupr(new_Sv.gioiTinh));
            while(strcmp(new_Sv.gioiTinh,"NAM")!=0 && strcmp(new_Sv.gioiTinh,"NU")!=0){
                printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
                scanf(" %[^\n]%*c",new_Sv.gioiTinh);
                strcpy(new_Sv.gioiTinh,strupr(new_Sv.gioiTinh));
            }
            if(strcmp(new_Sv.gioiTinh,"NAM")==0){
                strcpy(new_Sv.gioiTinh,"Nam");
            }else{
                strcpy(new_Sv.gioiTinh,"Nu");
            }
            
            StatusProcess(INSERT,87,COL_Font_Notice);
            printf(COL_Font_Notice"%cNEW SinhVien: %ld %c %s %s %s %c %02d/%02d/%d %c %s" reset "\n",
                ITEM,new_Sv.MSSV,
                ARROW_LEFT,new_Sv.ho,new_Sv.dem,new_Sv.ten,
                ARROW_LEFT,new_Sv.ngaySinh, new_Sv.thangSinh, new_Sv.nam,
                ARROW_LEFT,new_Sv.gioiTinh);
            printf(COL_Font_Notice"\n\\('^O^')/ HERE WE GO!!" reset "\n");
            position = WriteSV_ToBIN(new_Sv);
            PrintSV(new_Sv,position);      
        }else{
            StatusProcess(INSERT, 87, COL_Font_Warn);
            printf(COL_Font_Warn "\n!!(~_~\"\") YOU CAN'T OVERWRITE EXSITING STUDENT" reset "\n\n");
        }
    }

    void Process_WriteData_HP(){
        HP new_HP;
        int position;

        StatusProcess(INSERT, 5, COL_Font_Notice);
        printf(COL_Font_Notice"%cNEW HocPhan:" reset "\n",ITEM);
        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" Ma hoc phan: " reset);
        scanf(" %[^\n]%*c",new_HP.maHP);
        strcpy(new_HP.maHP,strupr(new_HP.maHP));
        while(strcmp(new_HP.maHP,"")==0){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!!!: " reset );
            scanf(" %[^\n]%*c",new_HP.maHP);
            strcpy(new_HP.maHP,strupr(new_HP.maHP));
        }
        position = CheckExist_HP_toPosition(new_HP.maHP);
        if(position==-1){           /// Nếu mã học phần chưa tồn tại
            StatusProcess(INSERT, 40, COL_Font_Notice);
            printf(COL_Font_Check"\n\t\t%c%c CAN INSERT %s! %c%c" reset "\n\n",TOGGLE_RIGHT,TOGGLE_RIGHT,new_HP.maHP,TOGGLE_LEFT,TOGGLE_LEFT);
            
            printf(COL_Font_Notice"%cNEW HocPhan: %s" reset "\n",ITEM,new_HP.maHP);
            printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" Ten hoc phan(cach nhau boi '_'): " reset);
            scanf(" %[^\n]%*c",new_HP.tenHP);
            while(strcmp(new_HP.tenHP,"")==0){
                printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT: " reset);
                scanf(" %[^\n]%*c",new_HP.tenHP);
            }

            StatusProcess(INSERT, 70, COL_Font_Notice);
            printf(COL_Font_Notice"%cNEW HocPhan: %s %c %s" reset "\n",
                ITEM,new_HP.maHP,
                ARROW_LEFT,new_HP.tenHP);
            printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" So tin chi: " reset);
            scanf("%d",&new_HP.tin);
            

            StatusProcess(INSERT,87,COL_Font_Notice);
            printf(COL_Font_Notice"%cNEW HocPhan: %s %c %s" reset "\n",
                ITEM,new_HP.maHP,
                ARROW_LEFT,new_HP.tenHP);
            printf(COL_Font_Notice"\n\\('^O^')/ HERE WE GO!!" reset "\n");
            WriteHP_ToBIN(new_HP);
            PrintHP(new_HP,CheckExist_HP_toPosition(new_HP.maHP));      ///kiểm tra lại và in kết quả  
        }else{
            StatusProcess(INSERT,87,COL_Font_Warn);
            printf(COL_Font_Notice "\n!!(~_~\"\") YOU CAN'T OVERWRITE SUBJECT" reset "\n\n");
        }
    }
    
    void Process_WriteData_DT(){
        DT new_DT;
        int position;
        char pointerPro;

        StatusProcess(INSERT, 5, COL_Font_Notice);
        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" MSSV: " reset);
        scanf("%d",&new_DT.MSSV);
        while(new_DT.MSSV<10000000 || new_DT.MSSV>99999999){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
            scanf("%d",&new_DT.MSSV);
        }
        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" Ma hoc phan: " reset);
        scanf(" %[^\n]%*c",new_DT.maHP);
        strcpy(new_DT.maHP,strupr(new_DT.maHP));

        position = CheckExist_DT_toPosition(new_DT.MSSV, new_DT.maHP);
        if(position==-1){
            StatusProcess(INSERT,50,COL_Font_Notice);
            printf(COL_Font_Check"\t\t%c%c CAN INSERT RECORD: %ld - %s! %c%c" reset "\n\n",TOGGLE_RIGHT,TOGGLE_RIGHT,new_DT.MSSV,new_DT.maHP,TOGGLE_LEFT,TOGGLE_LEFT);
            
            printf(COL_Font_Notice"%cNEW Record: %ld - %s" reset "\n",ITEM,new_DT.MSSV,new_DT.maHP);
            printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" So diem hoc phan: " reset);
            scanf("%f",&new_DT.diem);
            
            StatusProcess(INSERT,87,COL_Font_Notice);
            printf(COL_Font_Notice"%cNEW Record: %ld - %s %c %4.1f" reset "\n",ITEM,new_DT.MSSV,new_DT.maHP,ARROW_LEFT,new_DT.diem);
            printf(COL_Font_Notice"\n\\('^O^')/ HERE WE GO!!" reset "\n");
            position = WriteDT_toBIN(new_DT);
            
            if(position!=-1){   ///kiểm tra lại
                StatusProcess(UPDATE,87,COL_Font_Notice);
                printf(COL_Font_Notice "\n\\('^O^')/ "COL_Font"INSERT "COL_Font_Notice"%ld - %s"COL_Font" SUCCESSFULLY!\n" reset,new_DT.MSSV,new_DT.maHP);
                new_DT.diem= Round_diemHP(new_DT.diem);
                PrintDT(new_DT,position);       // in kết quả nếu thành công
                printf(COL_Font_Notice"\n\\('^O^')/ DO YOU WANT UPDATE CPA NOW\?\? (y/n)" reset);
                fflush(stdin);
                pointerPro = getchar();
                while((pointerPro!= 'y') && (pointerPro !='n')){
                    printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
                    fflush(stdin);
                    pointerPro = getchar();
                }
                if(pointerPro == 'y'){
                    Update_CPA_bin();
                    StatusProcess(UPDATE,87,COL_Font_Notice);
                    printf(COL_Font_Notice "\n\\('^O^')/ UPDATE CPA: %ld SUCCESSFULLY!\n" reset,new_DT.MSSV);
                }
            }else{
                StatusProcess(INSERT,87, COL_Font_Warn);
                printf(COL_Font_Warn "\n!!(~_~\"\") SOMETHING WENT WRONG!, CHECK YOUR FUNCTION AND DATA AGAIN" reset "\n\n"); 
            }
        }else{
            StatusProcess(INSERT,87, COL_Font_Warn);
            printf(COL_Font_Warn "\n!!(~_~\"\") YOU CAN'T OVERWRITE RECORD" reset "\n\n");    
        }

    }
    

    void Process_DeleteData_SV(){
        long MSSV;
        int status =-1;
        StatusProcess(DELETE, 5,COL_Font_Notice);
        printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" MSSV: " reset);
        scanf("%d",&MSSV);
        while(MSSV<10000000 || MSSV>99999999){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
            scanf("%d",&MSSV);
        }
        status = Delete_SV(MSSV);
        if(status!=-1){
            Sync_DT_binForSV(MSSV);
            StatusProcess(DELETE,87,COL_Font_Notice);
            printf(COL_Font_Notice"\n\\('^O^')/ HERE WE GO!!" reset "\n");
            printf(COL_Font_Notice"\tRESULT:" reset"\n");
            Print_SV_bin();
        }else{
            StatusProcess(INSERT,87, COL_Font_Warn);
            printf(COL_Font_Warn "\n!!(~_~\"\") ERROR: SYNCHRONIZE HP ERROR" reset "\n\n");
        }
        
    }
    

    void Process_DeleteData_HP(){
        char maHP[8];
        int status = -1;
        StatusProcess(DELETE, 5,COL_Font_Notice);
        printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" Ma hoc phan: " reset);
        scanf(" %[^\n]%*c",maHP);
        strcpy(maHP,strupr(maHP));
        while(strcmp(maHP,"")==0){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!!!: " reset );
            scanf(" %[^\n]%*c",maHP);
            strcpy(maHP,strupr(maHP));
        }
        status = Delete_HP(maHP);
        if(status!=-1){
            Sync_DT_binForHP(maHP);
            StatusProcess(DELETE,87,COL_Font_Notice);
            printf(COL_Font_Notice"\n\\('^O^')/ HERE WE GO!!" reset "\n");
            printf(COL_Font_Notice"\tRESULT:" reset"\n");
            Print_HP_bin();
        }else{
            StatusProcess(INSERT,87, COL_Font_Warn);
            printf(COL_Font_Notice "\n!!(~_~\"\") ERROR: SYNCHRONIZE HP ERROR" reset "\n\n");
        }
    }

    void Process_DeleteData_DT(){
        long MSSV;
        char maHP[8];
        int status;
        StatusProcess(DELETE, 5,COL_Font_Notice);
        printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" MSSV: " reset);
        scanf("%d",&MSSV);
        while(MSSV<10000000 || MSSV>99999999){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
            scanf("%d",&MSSV);
        }
        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" Ma hoc phan: " reset);
        scanf(" %[^\n]%*c",maHP);
        strcpy(maHP,strupr(maHP));
        while(strcmp(maHP,"")==0){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!!!: " reset );
            scanf(" %[^\n]%*c",maHP);
            strcpy(maHP,strupr(maHP));
        }
        status = Delete_DT(MSSV,maHP,0);
        if(status!=-1){
            StatusProcess(DELETE,87,COL_Font_Notice);
            printf(COL_Font_Notice"\n\\('^O^')/ HERE WE GO!!" reset "\n");
            printf(COL_Font_Notice"\tRESULT:" reset"\n");
            SelectDTBin_HP_BySV(MSSV,10,ALL);
        }else{
            StatusProcess(INSERT,87, COL_Font_Warn);
            printf(COL_Font_Warn "\n!!(~_~\"\") ERROR: SYNCHRONIZE HP ERROR" reset "\n\n"); 
        }
    }


    void Process_UpdateData_SV(){
        long MSSV;
        SV new_Sv = {0,"","","","",0,0,0};
        int position ; 
        char pointerPro;
        int status = -1;
        StatusProcess(UPDATE, 5,COL_Font_Notice);
        printf(COL_Font_Notice"%cNEW SinhVien:" reset "\n",ITEM);
        printf(COL_Font_Notice"('^_^'')?"COL_Font" Please type"COL_Font_Notice" MSSV you want to change: " reset);
        scanf("%d",&MSSV);
        while(MSSV<10000000 || MSSV>99999999){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
            scanf("%d",&MSSV);
        }
        position = CheckExist_SV_toPosition(MSSV);
        if(position!=-1){
            do{
                StatusProcess(UPDATE, 70, COL_Font_Notice);
                printf(COL_Font_Check"\t\t%c%c CAN UPDATE %ld! %c%c" reset "\n\n",TOGGLE_RIGHT,TOGGLE_RIGHT,MSSV,TOGGLE_LEFT,TOGGLE_LEFT);
                printf(COL_Font_Notice "('^_^'')?"COL_Font" You want to change: " reset"\n");
                printf(COL_Font_Notice "a, MSSV\tb, Ho\tc,Dem\td, Ten\te, Ngay_Thang_Nam Sinh\tf, GioiTinh\n");
                printf("\tPlease type a,b,c,d,e,f\n");
                printf("\tor Press x stop changing: " reset);
                fflush(stdin);
                pointerPro = getchar();
                if(pointerPro!='x'){
                    if(pointerPro=='a'){
                        printf(COL_Font_Notice "('^_^'')?"COL_Font"Please type"COL_Font_Notice" MSSV you want to change: " reset);
                        scanf("%d",&new_Sv.MSSV);
                        while(new_Sv.MSSV<10000000 || new_Sv.MSSV>99999999){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
                            scanf("%d",&new_Sv.MSSV);
                        }
                    }else if(pointerPro=='b'){
                        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" Family Name: " reset);
                        scanf(" %[^\n]%*c",new_Sv.ho);
                        while(strcmp(new_Sv.ho,"")==0){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! Not Blank DATA!: " reset );
                            scanf(" %[^\n]%*c",new_Sv.ho);
                        }
                    }else if(pointerPro=='c'){
                        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" Middle Name: " reset);
                        scanf(" %[^\n]%*c",new_Sv.dem);
                    }else if(pointerPro=='d'){
                        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" Name: " reset);
                        scanf(" %[^\n]%*c",new_Sv.ten);
                        while(strcmp(new_Sv.ten,"")==0){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! Not Blank DATA!: " reset );
                            scanf(" %[^\n]%*c",new_Sv.ten);
                        }
                    }else if(pointerPro == 'e'){
                        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" DateOfBirth: " reset "\n");
                        printf(COL_Font_Notice"\tNgaySinh: "reset);
                        scanf("%d",&new_Sv.ngaySinh);
                        printf(COL_Font_Notice"\tThangSinh: "reset);
                        scanf("%d",&new_Sv.thangSinh);
                        printf(COL_Font_Notice"\tNamSinh: "reset);
                        scanf("%d",&new_Sv.nam);
                    }else if(pointerPro =='f'){
                        printf(COL_Font_Notice "('^_^'')?"COL_Font" Please type"COL_Font_Notice" Gender: (Nam/Nu): " reset);
                        scanf(" %[^\n]%*c",new_Sv.gioiTinh);
                        strcpy(new_Sv.gioiTinh,strupr(new_Sv.gioiTinh));
                
                        while(strcmp(new_Sv.gioiTinh,"NAM")!=0 && strcmp(new_Sv.gioiTinh,"NU")!=0){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
                            scanf(" %[^\n]%*c",new_Sv.gioiTinh);
                            strcpy(new_Sv.gioiTinh,strupr(new_Sv.gioiTinh));
                        }
                        
                        if(strcmp(new_Sv.gioiTinh,"NAM")==0){
                            strcpy(new_Sv.gioiTinh,"Nam");
                        }else{
                            strcpy(new_Sv.gioiTinh,"Nu");
                        }
                    }else{
                        printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
                    }
                }else{
                    break;
                }
            }while(1);
            if((pointerPro == 'x') && (IsBlank_SV(new_Sv)==0)){
                StatusProcess(UPDATE, 87, COL_Font_Warn);
                printf(COL_Font_Warn"!!(~_~\"\") NOTHING CHANGE!" reset "\n");
            }else{
                status = Update_SV(MSSV,new_Sv,position);
                if(status!=-1){
                    StatusProcess(UPDATE,87,COL_Font_Notice);
                    printf(COL_Font"\n\\('^O^')/ HERE WE GO!!" reset "\n");
                    printf(COL_Font_Notice "RESULT: " reset "\n");
                    FindSV(position);
                }else{
                    StatusProcess(UPDATE, 87, COL_Font_Warn);
                    printf(COL_Font_Notice "\n!!(~_~\"\") PROCESS FAIL!" reset "\n\n");
                }
            }
        }else{
            StatusProcess(UPDATE, 87, COL_Font_Warn);
            printf(COL_Font_Notice "\n!!(~_~\"\") PROCESS FAIL!" reset "\n\n");
        }
    }

    void Process_UpdateData_HP(){
        char maHP[8];
        HP new_HP = {"","",-1};
        int position ; 
        int status =-1;
        char pointerPro;

        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" Ma hoc phan: " reset);
        scanf(" %[^\n]%*c",maHP);
        strcpy(maHP,strupr(maHP));
        while(strcmp(maHP,"")==0){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!!!: " reset );
            scanf(" %[^\n]%*c",maHP);
            strcpy(maHP,strupr(maHP));
        }
        position  = CheckExist_HP_toPosition(maHP);
        if(position !=-1){
            do{
                StatusProcess(UPDATE, 70, COL_Font_Notice);
                printf(COL_Font_Check"\t\t%c%c CAN UPDATE %s! %c%c" reset "\n\n",TOGGLE_RIGHT,TOGGLE_RIGHT,maHP,TOGGLE_LEFT,TOGGLE_LEFT);
                printf(COL_Font "('^_^'')? You want to change: " reset"\n");
                printf(COL_Font_Notice "a, Ma Hoc Phan\tb, Ten Hoc Phan\tc,So tin chi\n");
                printf("\tPlease type a,b,c\n");
                printf("\tor Press x stop changing: " reset);
                fflush(stdin);
                pointerPro = getchar();
                if(pointerPro!='x'){
                    if(pointerPro=='a'){
                        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" Ma hoc phan: " reset);
                        scanf(" %[^\n]%*c",new_HP.maHP);
                        strcpy(new_HP.maHP,strupr(new_HP.maHP));
                        while(strcmp(new_HP.maHP,"")==0){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!!!: " reset );
                            scanf(" %[^\n]%*c",new_HP.maHP);
                            strcpy(new_HP.maHP,strupr(new_HP.maHP));
                        }                    
                    }else if (pointerPro =='b'){
                        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" Ten hoc phan(cach nhau boi '_'): " reset);
                        scanf(" %[^\n]%*c",new_HP.tenHP);
                        while(strcmp(new_HP.tenHP,"")==0){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT: " reset);
                            scanf(" %[^\n]%*c",new_HP.tenHP);
                        }
                    }else if (pointerPro == 'c'){
                        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" So tin chi: " reset);
                        scanf("%d",&new_HP.tin);
                    }else{
                        printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT: " reset);
                    }
                }else{
                    break;
                }
            }while(1);
            if((pointerPro == 'x') && (IsBlank_HP(new_HP)==0)){
                StatusProcess(UPDATE, 87, COL_Font_Warn);
                printf(COL_Font_Warn"!!(~_~\"\") NOTHING CHANGE!" reset "\n");
            }else{
                status = Update_HP(maHP,new_HP,position);
                if(status!=-1){
                    StatusProcess(UPDATE,87,COL_Font_Notice);
                    printf(COL_Font"\n\\('^O^')/ HERE WE GO!!" reset "\n");
                    printf(COL_Font_Notice "RESULT: " reset "\n");

                    FindHP(position);
                }else{
                    printf(COL_Font_Notice "\n!!(~_~\"\") PROCESS FAIL!" reset "\n\n"); 
                }
            }
        }else{
            StatusProcess(UPDATE, 87, COL_Font_Warn);
            printf(COL_Font_Notice "\n!!(~_~\"\") PROCESS FAIL!" reset "\n\n");  
        }

    }

    void Process_UpdateData_DT(){
        long MSSV;
        char maHP[8];
        DT new_DT = {0,"",0};
        int position;
        int status = -1;
        char pointerPro;
        StatusProcess(UPDATE, 5,COL_Font_Notice);
        printf(COL_Font_Notice"%cNEW SinhVien:" reset "\n",ITEM);
        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" MSSV you want to change: " reset);
        scanf("%d",&MSSV);
        while(MSSV<10000000 || MSSV>99999999){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
            scanf("%d",&MSSV);
        }
        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" Ma hoc phan: " reset);
        scanf(" %[^\n]%*c",maHP);
        strcpy(maHP,strupr(maHP));
        while(strcmp(maHP,"")==0){
            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!!!: " reset );
            scanf(" %[^\n]%*c",maHP);
            strcpy(maHP,strupr(maHP));
        }

        position = CheckExist_DT_toPosition(MSSV,maHP);
        if(position!=-1){
            new_DT = FindDT(position);
            do{
                StatusProcess(UPDATE, 70, COL_Font_Notice);
                printf(COL_Font_Check"\t\t%c%c CAN UPDATE RECORD: %ld - %s! %c%c" reset "\n\n",TOGGLE_RIGHT,TOGGLE_RIGHT,MSSV,maHP,TOGGLE_LEFT,TOGGLE_LEFT);
                printf(COL_Font "('^_^'')? You want to change: " reset"\n");
                printf(COL_Font_Notice "a, Ma so sinh vien \tb, Ma hoc phan\tc,Diem\n");
                printf("\tPlease type a,b,c\n");
                printf("\tor Press x stop changing: " reset);
                fflush(stdin);
                pointerPro = getchar();
                if(pointerPro!='x'){
                    if(pointerPro=='a'){
                        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" MSSV you want to change: " reset);
                        scanf("%d",&new_DT.MSSV);
                        while(new_DT.MSSV<10000000 || new_DT.MSSV>99999999){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! MSSV needs 8 digits!: " reset );
                            scanf("%d",&new_DT.MSSV);
                        }
                    }else if(pointerPro =='b'){
                        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" Ma hoc phan: " reset);
                        scanf(" %[^\n]%*c",new_DT.maHP);
                        strcpy(new_DT.maHP,strupr(new_DT.maHP));
                        while(strcmp(new_DT.maHP,"")==0){
                            printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!!!: " reset );
                            scanf(" %[^\n]%*c",new_DT.maHP);
                            strcpy(new_DT.maHP,strupr(new_DT.maHP));
                        }
                    }else if (pointerPro =='c'){
                        printf(COL_Font "('^_^'')? Please type"COL_Font_Notice" So diem hoc phan: " reset);
                        scanf("%f",&new_DT.diem);
            
                    }else{
                        printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT: " reset);
                    }
                }else{
                    break;
                }
            }while(1);
            if((pointerPro == 'x') && (IsBlank_DT(new_DT)==0)){
                StatusProcess(UPDATE, 87, COL_Font_Warn);
                printf(COL_Font_Warn"!!(~_~\"\") NOTHING CHANGE!" reset "\n");
            }else{
                status = Update_DT(MSSV,maHP,new_DT,position);
                if(status!=-1){
                    StatusProcess(UPDATE,87,COL_Font_Notice);
                    printf(COL_Font"\n\\('^O^')/ HERE WE GO!!" reset "\n");
                    printf(COL_Font_Notice "RESULT: " reset "\n");
                    
                    FindDT(position);
                }else{
                    printf(COL_Font_Notice "\n!!(~_~\"\") PROCESS FAIL!" reset "\n\n");        
                }
            }
        }else{
            StatusProcess(UPDATE, 87, COL_Font_Warn);
            printf(COL_Font_Notice "\n!!(~_~\"\") PROCESS FAIL!" reset "\n\n"); 
        }
    }

    void Process_UpdateData_CPA(){
        Update_CPA_bin();
        StatusProcess(UPDATE,87,COL_Font_Notice);
        printf(COL_Font_Notice "\n\\('^O^')/ UPDATE CPA SUCCESSFULLY!\n" reset);
        Print_CPA_bin();
    }
    

#endif

