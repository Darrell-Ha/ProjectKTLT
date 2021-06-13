#include <D:\ProjectKTLT\sources\functions\Program.h>
#include <stdlib.h>
// Chạy chương trình cho section 2
    void ProgramSection2(int subsection);
    
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
//


void ProgramSection2(int subsection){
    system("cls");
    Header();
    printf("\n");
    switch(subsection){
        case 0:
            Control_WriteData();
        break;
        case 1: 
            Control_DeleteData();
        break;
        case 2:
            Control_UpdateData();
        break;
        default:
        printf(COL_Font_Notice"SOMETHING WENT WRONG!!!" reset "\n");
    }
    printf(COL_Font"Press to continue!!" reset);
    printf("\n");
    getch();
}



void Control_WriteData(){
    char pointerPro;
    printf(COL_Font"('^_^'') You want To write data to: \n" reset);
    printf(COL_Font_Notice"\t a. SinhVien?\t");
    printf("b. HocPhan\t");
    printf("c. DiemThi\n"reset);
    printf(COL_Font"\t Type a,b,c: "reset);
    fflush(stdin);
    pointerPro = getchar();
    while((pointerPro!= 'a') && (pointerPro !='b') && (pointerPro!='c')){
        printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
        fflush(stdin);
        pointerPro = getchar();
    }
    if(pointerPro == 'a'){
        Process_WriteData_SV();
    }else if(pointerPro == 'b'){
        Process_WriteData_HP();
    }else{
        Process_WriteData_DT();
    }
}


void Control_DeleteData(){
    char pointerPro;
    printf(COL_Font"('^_^'') You want To DELETE a: \n" reset);
    printf(COL_Font_Notice"\t a. SinhVien?\t");
    printf("b. HocPhan\t");
    printf("c. DiemThi\n"reset);
    printf(COL_Font"\t Type a,b,c: "reset);
    fflush(stdin);
    pointerPro = getchar();
    printf("\n");
    while((pointerPro!= 'a') && (pointerPro !='b') && (pointerPro!='c')){
        printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
        fflush(stdin);
        pointerPro = getchar();
    }
    if(pointerPro == 'a'){
        Process_DeleteData_SV();
    }else if(pointerPro == 'b'){
        Process_DeleteData_HP();
    }else{
        Process_DeleteData_DT();
    }  
}

void Control_UpdateData(){
    char pointerPro;
    printf(COL_Font"('^_^'') You want To UPDATE: \n" reset);
    printf(COL_Font_Notice"\t a. SinhVien?\t");
    printf("b. HocPhan\t");
    printf("c. DiemThi\t");
    printf("d. CPA"reset"\n");
    printf(COL_Font"\t Type a,b,c,d: "reset);
    fflush(stdin);
    pointerPro = getchar();
    printf("\n");
    while((pointerPro!= 'a') && (pointerPro !='b') && (pointerPro!='c') && (pointerPro!='d')){
        printf(COL_Font_Notice "(''@_@'') PLEASE TYPE AGAIN!! I CAN'T GET IT!: " reset);
        fflush(stdin);
        pointerPro = getchar();
    }
    if(pointerPro == 'a'){
        Process_UpdateData_SV();
    }else if(pointerPro == 'b'){
        Process_UpdateData_HP();
    }else if(pointerPro == 'c'){
        Process_UpdateData_DT();
    }else{
        Process_UpdateData_CPA();
    }    
}