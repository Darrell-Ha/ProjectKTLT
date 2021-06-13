#ifndef MENU_H
    #define MENU_H
    #include <D:\ProjectKTLT\sources\functions\Section1.h>
    #include <D:\ProjectKTLT\sources\functions\Section2.h>
    #include <stdlib.h>
    #include <conio.h>


    char Section[3][30] = {"View Data in Bin", "Interact Data", "Exit Program"};

    char Section1[4][30] = {"List Student", "List Subject", "See Detail Point by Selection", "List CPA by Selection"};
    char Section2[3][30] = {"Write Data to Bin","Delete Data", "Update Data"};


    ////// PROTOTYPE FOR MENU "TOGGLE LIST - tự code - 28/5/2021 - by Hà Trọng Đạt "
    ///// Phần màu:         tham khảo bảng ANSI COLOR 
    void InstructionMENU();
    void InstructionTOGGLE();
    void Menu();
    void PrintBorder(int count, char color[], SYMBOL type); //// ở giữa Header
    void PrintBlank(int count);
    void HeaderToMenu_SECTION(int subsection);
    void Header();
    void PrintHeart(int count);
    int MenuSubsection1(int subsection);
    int MenuSubsection2(int subsection);
    int GetMenuSubsection(int section, int subsection);


    ///////////////////                 CODING              /////////////////////
    void PrintBlank(int count){
        int i=0;
        for(i=0; i<count ;i++){
            printf(" ");
        }
    }
    void PrintBorder(int count, char color[], SYMBOL type){
        int i;
        for(i=0;i<count;i++){
            printf("%s%c",color,type);
        }
        printf(reset);
    }
    void PrintHeart(int count){
        int i;
        for(i=0;i<count;i++){
            printf(COL_Font "%c",HEART);
        }
        printf(reset);
    }
    void Header(){
        printf("\n");
        PrintBorder(98,COL_Font,BORDER);printf("\n");
        printf(COL_BG "           " COL_Txt_inBG "PROGRAM FOR TOPIC 6:" );
        printf(reset COL_BG);
        PrintBlank(67);
        printf(reset "\n");
        printf(COL_BG);
        PrintBlank(36);
        printf(COL_Txt_inBG"STUDENT INFORMATION SYSTEM - SIS");
        printf(reset COL_BG);
        PrintBlank(30);
        printf(reset "\n");
        printf(COL_BG COL_Txt_inBG);
        PrintBlank(73);
        printf("BY 20195851 & 20195849");
        PrintBlank(3);
        printf(reset "\n");
        PrintBorder(98,COL_Font,BORDER);printf("\n");
    }
    void InstructionMENU(){
        printf(COL_Font "@ Press: " COL_Font_Notice "%c" COL_Font " to the next" reset "\n",ARROW_RIGHT);
        printf(COL_Font "@ Press: " COL_Font_Notice "%c" COL_Font " to the previous" reset "\n",ARROW_LEFT);
        printf(COL_Font "@ Press: " COL_Font_Notice "%c" COL_Font " or 'Enter' to the open the toggle " COL_Font_Notice "(%c)" reset "\n",ARROW_DOWN,TOGGLE_RIGHT);
        printf(COL_Font "@ Press: " COL_Font_Notice "%c" COL_Font " to the escape the toggle " COL_Font_Notice "(%c)" reset "\n",ARROW_LEFT,TOGGLE_DOWN);
        printf(COL_Font "--------------------------------------------------------------------------------------------------" reset "\n");
    }
    void InstructionTOGGLE(){
        printf(COL_Font "@ Press: " COL_Font_Notice "%c" COL_Font " to the next" reset "\n",ARROW_DOWN);
        printf(COL_Font "@ Press: " COL_Font_Notice "%c" COL_Font " to the previous" reset "\n",ARROW_UP);
        printf(COL_Font "@ Press: "COL_Font_Notice"'Enter'"COL_Font" to the selection " COL_Font_Notice "(%c)" reset "\n",ITEM);
        printf(COL_Font "@ Press: " COL_Font_Notice "%c" COL_Font " to the escape the toggle " COL_Font_Notice "(%c)" reset "\n",ARROW_LEFT,TOGGLE_DOWN);
        printf(COL_Font "--------------------------------------------------------------------------------------------------" reset "\n");
    }

    void HeaderToMenu_SECTION(int subsection){
        PrintBorder(38,COL_Font,BORDER);
        printf(COL_Font "@@@ INSTRUCTION @@@" reset);
        PrintBorder(40,COL_Font,BORDER);
        printf("\n");
        if(subsection==-1){
            InstructionMENU();
        }else{
            InstructionTOGGLE();
        }
        Header();
    }
    void Menu(){
        char pointerPro;
        int load;
        int section = 1;
        int subsection =-1;
        while(1){
            system("cls");
            HeaderToMenu_SECTION(subsection);
            printf("\n"COL_Font "--------------------------------------------------------------------------------------------------" reset "\n");
            for(load = 0; load < 3; load++){
                if(load == section){
                    printf(COL_BG);
                    PrintBlank(10);
                    if(subsection==-1){
                        printf(COL_Txt_inBG"%c %s"reset COL_BG,TOGGLE_RIGHT,Section[load]);
                    }else{
                        printf(COL_Txt_inBG"%c %s"reset COL_BG,TOGGLE_DOWN,Section[load]);
                    }
                    PrintBlank(10);
                    printf(reset" ");
                }else{
                    printf(COL_Font_Notice " %c" COL_Font " %s\t\t" reset ,TOGGLE_RIGHT,Section[load]);
                }
            }
            if(subsection!=-1){
                printf("\n");
                subsection = GetMenuSubsection(section, subsection);
            }else{
                if(subsection==-1){
                    printf("\n");
                    printf("\n"COL_Font "--------------------------------------------------------------------------------------------------" reset "\n\n");
                    pointerPro = getch();
                    if (pointerPro == KEY_LEFT){
                        section = (section + 2) % 3;
                    }else if (pointerPro == KEY_RIGHT){
                        section = (section + 4) % 3;
                    }else if (pointerPro == '\r' || pointerPro == KEY_DOWN){
                        if (section==2){
                            printf(COL_Font "ARE YOU SURE TO EXIT PROGRAM "COL_Font_Notice"(y/n)? "reset);
                            fflush(stdin);
                            pointerPro = getchar();
                            printf("\n");
                            if(pointerPro == 'y'){
                                PrintBorder(40,COL_Font,BORDER);
                                printf(COL_Font "!!! GOODBYE !!!" reset);
                                PrintBorder(43,COL_Font,BORDER);
                                break;
                            }
                        }else{
                            subsection = 0;
                        }
                    }
                }
            }
        }   
        
    }

    int GetMenuSubsection(int section, int subsection){
        int response =-1;
        if(section == 0){
            response = MenuSubsection1(subsection);
        }else if (section == 1){
            response = MenuSubsection2(subsection);
        }
        return response;
    }

    int MenuSubsection1(int subsection){
        int load;
        char pointerPro;
        printf(COL_BG);
        PrintBlank(38);
        printf(reset "\n");
        PrintBorder(98,COL_Font,BORDER);printf("\n");
        printf(reset "\n");
        for(load = 0; load < 4; load++){
            printf("\t\t");
            if(load == subsection){
                printf(COL_BG);
                printf(COL_Txt_inBG" %c %s"reset COL_BG"                " reset "\n" ,ITEM,Section1[load]);
            }else{
                printf(COL_Font_Notice " %c" COL_Font " %s" reset "\n" ,ITEM,Section1[load]);
            }
        }
        printf("\n");
        printf("\n"COL_Font "--------------------------------------------------------------------------------------------------" reset "\n\n");
        pointerPro = getch();
        if (pointerPro == KEY_UP){
            subsection = (subsection + 3) % 4;
        }else if ((pointerPro == KEY_DOWN) || (pointerPro == KEY_RIGHT)){
            subsection = (subsection + 5) % 4;
        }else if ((pointerPro == KEY_LEFT)){
            subsection = -1;
        }else if ((pointerPro == '\r')){
            ProgramSection1(subsection);
        }
        return subsection;

    }
    int MenuSubsection2(int subsection){
        int load;
        char pointerPro;
        printf("\t\t\t        ");
        printf(COL_BG);
        PrintBlank(35);
        printf(reset "\n");
        PrintBorder(98,COL_Font,BORDER);printf("\n");
        printf(reset "\n");
        for(load = 0; load < 3; load++){
            printf("\t\t");
            if(load == subsection){
                printf(COL_BG);
                printf(COL_Txt_inBG" %c %s"reset COL_BG"                " reset "\n" ,ITEM,Section2[load]);
            }else{
                printf(COL_Font_Notice " %c" COL_Font " %s" reset "\n" ,ITEM,Section2[load]);
            }
        }
        printf("\n");
        printf("\n"COL_Font "--------------------------------------------------------------------------------------------------" reset "\n\n");
        pointerPro = getch();
        if (pointerPro == KEY_UP){
            subsection = (subsection + 2) % 3;
        }else if ((pointerPro == KEY_DOWN) || (pointerPro == KEY_RIGHT)){
            subsection = (subsection + 4) % 3;
        }else if ((pointerPro == KEY_LEFT)){
            subsection = -1;
        }else if ((pointerPro == '\r')){
            ProgramSection2(subsection);
        }
        return subsection;
        
    }

#endif