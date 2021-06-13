#include <D:\ProjectKTLT\sources\functions\Program.h>
#include <conio.h>

// Chạy chương trình cho section1 //
    void ProgramSection1(int subsection);

    void Control_DiemThi();
    void Control_CPA();
//
void ProgramSection1(int subsection){
    system("cls");
    Header();
    printf("\n");
    switch(subsection){
        case 0:
            Print_SV_bin();     /// đã được viết ở SV.h
        break;
        case 1: 
            Print_HP_bin();     // đã được viết ở HP.h
        break;
        case 2:
            Control_DiemThi();  /// ở Program.h
        break;
        case 3:
            Control_CPA();      // ở Program.h
        break;
        default:
        printf(COL_Font_Notice"SOMETHING WENT WRONG!!!" reset "\n");
    }
    printf(COL_Font"Press to continue!!" reset);
    printf("\n");
    getch();
}