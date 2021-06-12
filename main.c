#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#define MAX_CHAR 1000
const char path_KhoanThu[] = "D:\\dataKhoanThu.txt";
const char path_KhoanChi[] = "D:\\dataKhoanChi.txt";
//time ( thoi gian cu the tai thoi diem dang xet)
typedef struct {
    int ngay;
    int thang;
    int nam;
}Time;
//-end time

//record khoan thu
typedef struct
{
    long tien_thu;
    char mo_ta[MAX_CHAR];
    Time time;
}KhoanThu;

typedef struct
{
    KhoanThu data;
    struct Node_KhoanThu *pNext;
}Node_KhoanThu;

typedef struct
{
    Node_KhoanThu *pHead;
    Node_KhoanThu *pTail;
}list_KhoanThu;

void khoiTaoListKhoanThu(list_KhoanThu *l){
    l->pHead = NULL;
    l->pTail = NULL;
}

KhoanThu taoKhoanThu()
{
    KhoanThu temp;
    char check;
    printf("nhap thoi gian: \n");
    printf("nhap nam: ");
    scanf("%d",&temp.time.nam);
    do{
    printf("nhap thang: ");
    scanf("%d",&temp.time.thang);
    }while(temp.time.thang < 1 || temp.time.thang > 12);
    switch(temp.time.thang){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:{
            do{
                printf("nhap ngay: ");
                scanf("%d",&temp.time.ngay);
            }while(temp.time.ngay < 1 || temp.time.ngay > 31);
            break;
        }
        case 4: case 6: case 9: case 11:{
             do{
                printf("nhap ngay: ");
                scanf("%d",&temp.time.ngay);
            }while(temp.time.ngay < 1 || temp.time.ngay > 30);
            break;
        }
        case 2:{
             do{
                printf("nhap ngay: ");
                scanf("%d",&temp.time.ngay);
            }while(temp.time.ngay < 1 || temp.time.ngay > 29);
            break;
        }
    }
    printf("nhap so tien thu duoc: ");
    scanf("%d",&temp.tien_thu);
    printf("nhap mo ta cho khoan thu nay khong? [y/n]\n");
    check = getch();
    if(check == 'y'){
        char c[MAX_CHAR];
        fflush(stdin);
        printf("moi nhap mo ta: ");
        gets(c);
        strcpy(temp.mo_ta,c);
        strcat(temp.mo_ta,".");
    }else{
        strcpy(temp.mo_ta,"khong co mo ta.");
    }
    return temp;
}

Node_KhoanThu* TaoNode_KhoanThu()
{
    Node_KhoanThu *p = (Node_KhoanThu*)malloc(sizeof(Node_KhoanThu));
    p->data = taoKhoanThu();
    p->pNext = NULL;
    return p;
}

void taoDataKhoanThu(list_KhoanThu *l)
{
    char key;
    do{
        printf("khoi tao du lieu: \n");
        Node_KhoanThu *p = TaoNode_KhoanThu();
        if(l->pHead == NULL){
            l->pHead = p;
        }else{
            if(l->pTail == NULL){
                l->pTail = p;
                l->pHead->pNext = p;
            }else{
                l->pTail->pNext = p;
                l->pTail = p;
            }
        }
        printf("ban co muon nhap them khoan thu khong? [y/n]");
        key = getch();
    }while(key != 'n');
}

void xuatKhoanThuRaManHinh(list_KhoanThu l){
    Node_KhoanThu *p = l.pHead;
    do{
        printf("---------------\n");
        printf("thoi gian: %d/%d/%d\n",p->data.time.ngay,p->data.time.thang,p->data.time.nam);
        printf("khoan thu: %d\n",p->data.tien_thu);
        printf("mo ta khoan thu: %s\n",p->data.mo_ta);
        printf("---------------\n");
        p = p->pNext;
    }while(p != NULL);

}

void inFileKhoanThu(list_KhoanThu l,FILE *f)
{
    f = fopen(path_KhoanThu,"w");
    fprintf(f,"%10s%25s%50s\n","Thoi gian","So tien thu","Mo ta so tien thu");
    Node_KhoanThu *p = l.pHead;
    do{
        fprintf(f,"%2d/%2d/%-4d%25s",p->data.time.ngay,p->data.time.thang,p->data.time.nam," ");
        fprintf(f,"%-30d",p->data.tien_thu);
        fprintf(f,"%-s\n",p->data.mo_ta);
        p = p->pNext;
    }while(p != NULL);
    fclose(f);
}
//note chua hoan thanh
void docFileKhoanThu(list_KhoanThu *l,FILE *f)
{
    f = fopen(path_KhoanThu,"r");
    char temp;
    fseek(f,86,SEEK_SET);
    while(1){
        Node_KhoanThu *p = (Node_KhoanThu*)malloc(sizeof(Node_KhoanThu));
        fscanf(f,"%d",&p->data.time.ngay);
        fscanf(f,"%*c%d",&p->data.time.thang);
        fscanf(f,"%*c%d",&p->data.time.nam);
        while(1){
            temp = fgetc(f);
            if(temp != ' '){
                fseek(f,-1,SEEK_CUR);
                fscanf(f,"%d",&p->data.tien_thu);
                break;
            }
        }

        while(1){
            temp = fgetc(f);
            if(temp != ' '){
                fseek(f,-1,SEEK_CUR);
                fscanf(f,"%[^.]",p->data.mo_ta);
                break;
            }
        }
        temp = fgetc(f);
        if(l->pHead == NULL){
            l->pHead = p;
            l->pHead->pNext = NULL;
        }else{
            if(l->pTail == NULL){
                l->pTail = p;
                l->pHead->pNext = p;
            }else{
                l->pTail->pNext = p;
                l->pTail = p;
            }

        }

        if(temp == EOF){
            break;
        }
    }
    fclose(f);
}

long tongKhoanThuThang(list_KhoanThu l,int thang,int nam){
    long tien = 0;
    Node_KhoanThu *p = l.pHead;
    do{
        if(p->data.time.thang == thang && p->data.time.nam == nam){
            tien += p->data.tien_thu;
        }
        p = p->pNext;
    }while(p != NULL);
    return tien;
}


//-end record khoan thu

//record khoan chi
//-------------------------------------------------------
typedef struct
{
    char ten_loai[MAX_CHAR];
    long tien_chi;
}LoaiTienChi;

typedef struct
{
    LoaiTienChi data;
    struct Node_LoaiTienChi *pNext;
}Node_LoaiTienChi;

typedef struct
{
    Node_LoaiTienChi *pHead;
    Node_LoaiTienChi *pTail;
}list_LoaiTienChi;

void khoiTaoListLoaiTienChi(list_LoaiTienChi *l)
{
    l->pHead = NULL;
    l->pTail = NULL;
}

LoaiTienChi taoLoaiTienChi()
{
    LoaiTienChi temp;
    printf("nhap ten cua khoan chi: ");
    gets(temp.ten_loai);
    //----code tiep vao day
    printf("nhap so tien: ");
    scanf("%d",&temp.tien_chi);
    getchar();
    return temp;
}

Node_LoaiTienChi* taoNode_LoaiTienChi()
{
    Node_LoaiTienChi *p = (Node_LoaiTienChi*)malloc(sizeof(Node_LoaiTienChi));
    p->data = taoLoaiTienChi();
    p->pNext = NULL;
    return p;
}
//-----------------------------------------------------------
//-----------------------------------------------------------
typedef struct
{
    Time time;
    list_LoaiTienChi loai_tien_chi;
    long tong_tien_chi;
}KhoanChi;

typedef struct
{
    KhoanChi data;
    struct Node_KhoanChi *pNext;
}Node_KhoanChi;

typedef struct
{
    Node_KhoanChi *pHead;
    Node_KhoanChi *pTail;
}list_KhoanChi;

void khoiTaoListKhoanChi(list_KhoanChi *l)
{
    l->pHead = NULL;
    l->pTail = NULL;
}

KhoanChi taoKhoanChi()
{
    KhoanChi temp;
    char check;
    temp.tong_tien_chi = 0;
    printf("nhap thoi gian: \n");
    printf("nhap nam: ");
    scanf("%d",&temp.time.nam);
    do{
    printf("nhap thang: ");
    scanf("%d",&temp.time.thang);
    }while(temp.time.thang < 1 || temp.time.thang > 12);
    switch(temp.time.thang){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:{
            do{
                printf("nhap ngay: ");
                scanf("%d",&temp.time.ngay);
            }while(temp.time.ngay < 1 || temp.time.ngay > 31);
            break;
        }
        case 4: case 6: case 9: case 11:{
             do{
                printf("nhap ngay: ");
                scanf("%d",&temp.time.ngay);
            }while(temp.time.ngay < 1 || temp.time.ngay > 30);
            break;
        }
        case 2:{
             do{
                printf("nhap ngay: ");
                scanf("%d",&temp.time.ngay);
            }while(temp.time.ngay < 1 || temp.time.ngay > 29);
            break;
        }
    }
    fflush(stdin);
    printf("nhap cac khoan chi trong ngay: \n");
    khoiTaoListLoaiTienChi(&temp.loai_tien_chi);
    do{
    if(temp.loai_tien_chi.pHead == NULL){
        Node_LoaiTienChi *p = taoNode_LoaiTienChi();
        temp.loai_tien_chi.pHead = p;
        temp.tong_tien_chi += p->data.tien_chi;
    }else{
        Node_LoaiTienChi *p = taoNode_LoaiTienChi();
        temp.tong_tien_chi += p->data.tien_chi;
        if(temp.loai_tien_chi.pTail == NULL){
            temp.loai_tien_chi.pTail = p;
            temp.loai_tien_chi.pHead->pNext = p;
        }else{
            temp.loai_tien_chi.pTail->pNext = p;
            temp.loai_tien_chi.pTail = p;
        }
    }
    printf("ban muon nhap them nua khong? [y/n]");
    check = getch();
    }while(check!='n');
    return temp;
}

Node_KhoanChi* taoNode_KhoanChi()
{
    Node_KhoanChi *p = (Node_KhoanChi*)malloc(sizeof(Node_KhoanChi));
    p->data = taoKhoanChi();
    p->pNext = NULL;
    return p;
}

long tongKhoanChiThang(list_KhoanChi l,int thang,int nam){
    long tien = 0;
    Node_KhoanChi *p = l.pHead;
    do{
        if(p->data.time.thang == thang && p->data.time.nam == nam){
            Node_LoaiTienChi *p1 = p->data.loai_tien_chi.pHead;
            do{
                tien += p1->data.tien_chi;
                p1 = p1->pNext;
            }while(p1 != NULL);
        }
        p = p->pNext;
    }while(p != NULL);
    return tien;
}

void taoDataKhoanChi(list_KhoanChi *l)
{
    char key;
    do{
        printf("khoi tao du lieu: \n");
        Node_KhoanChi *p = taoNode_KhoanChi();
        if(l->pHead == NULL){
            l->pHead = p;
        }else{
            if(l->pTail == NULL){
                l->pTail = p;
                l->pHead->pNext = p;
            }else{
                l->pTail->pNext = p;
                l->pTail = p;
            }
        }
        printf("ban co muon nhap them khoan chi khong? [y/n]");
        key = getch();
    }while(key != 'n');
}

void xuatKhoanChiRaManHinh(list_KhoanChi l){
    Node_KhoanChi *p = l.pHead;
    do{
        printf("---------------\n");
        printf("thoi gian: %d/%d/%d\n",p->data.time.ngay,p->data.time.thang,p->data.time.nam);
        Node_LoaiTienChi *p1 = p->data.loai_tien_chi.pHead;
        do{
            printf("loai tien chi: %s, so tien chi: %d\n",p1->data.ten_loai,p1->data.tien_chi);
            p1 = p1->pNext;
        }while(p1 != NULL);
        printf("---------------\n");
        p = p->pNext;
    }while(p != NULL);

}

void inFileKhoanChi(list_KhoanChi l,FILE *f)
{
    f = fopen(path_KhoanChi,"w");
    fprintf(f,"%10s%50s\n","Thoi gian","Loai tien chi - so tien chi\n");
    Node_KhoanChi *p = l.pHead;
    do{
        fprintf(f,"%2d/%2d/%-4d%25s",p->data.time.ngay,p->data.time.thang,p->data.time.nam," ");
        Node_LoaiTienChi *p1 = p->data.loai_tien_chi.pHead;
        do{
            fprintf(f,"%s:%d, ",p1->data.ten_loai,p1->data.tien_chi);
            p1 = p1->pNext;
        }while(p1 != NULL);
        fprintf(f,"\n");
        p = p->pNext;
    }while(p != NULL);
    fclose(f);
}
//-----------------------------------------------------------
//-end record khoan chi
void menu_main()
{
    printf("----------------------------\n");
    printf("1. menu khoan thu.\n");
    printf("2. menu khoan chi.\n");
    printf("0. ket thuc chuong trinh.\n");
    printf("----------------------------\n");
}

void menu_chi()
{
    printf("menu chuc nang\n");
    printf("----------------------------\n");
    printf("1. Them ban ghi cua khoan chi.\n");
    printf("2. Xem du lieu khoan chi.\n");
    printf("3. Xoa ban ghi cua khoan chi.( theo ngay )\n");
    printf("4. Tim kiem theo ngay.\n");
    printf("5. Thong tin ngay chi tieu nhieu nhat thang.\n");
    printf("6. Tong tien chi theo thang.\n");
    printf("0. quay lai.\n");
    printf("----------------------------\n");
}

void menu_thu()
{
    printf("menu chuc nang\n");
    printf("----------------------------\n");
    printf("1. Them ban ghi cua khoan thu.\n");
    printf("2. Xem du lieu khoan thu\n");
    printf("3. Xoa ban ghi cua khoan thu.( theo ngay)\n");
    printf("4. Tim kiem khoan thu theo ngay.\n");
    printf("0. quay lai.\n");
    printf("----------------------------\n");
}

int main()
{
    list_KhoanThu dataKhoanThu;
    list_KhoanChi dataKhoanChi;
    khoiTaoListKhoanThu(&dataKhoanThu);
    khoiTaoListKhoanChi(&dataKhoanChi);
    FILE *fptr;

    printf("tao data khoan chi: \n");
    taoDataKhoanChi(&dataKhoanChi);

    printf("tao data khoan thu: \n");
    taoDataKhoanThu(&dataKhoanThu);



    char key_main;
    char key_thu;
    char key_chi;
    Label: do{
        system("cls");
        printf("Chuong trinh quan ly thu chi\n");
        menu_main();
        printf("moi ban chon phim chuc nang: ");
        key_main = getch();
        if(key_main == '0'){
            char key_check;
            printf("Chuan bi ket thuc chuong trinh, ban co muon in du lieu ra file khong? [y/n]");
            key_check = getch();
            switch(key_check)
            {
            case 'y':
                {
                    printf("Da in ra file\n");
                    inFileKhoanThu(dataKhoanThu,fptr);
                    inFileKhoanChi(dataKhoanChi,fptr);
                    break;
                }
            case 'n':
                {
                    printf("Ket thuc chuong trinh!!");
                    break;
                }
            }
            break;
        }
        switch(key_main)
        {
        case '1':
            {
                do{
                system("cls");
                menu_thu();
                printf("moi ban chon phim chuc nang: ");
                key_thu = getch();
                if(key_thu == '0'){
                    break;
                }
                switch(key_thu)
                {
                case '1':
                    {
                        taoDataKhoanThu(&dataKhoanThu);
                        break;
                    }
                case '2':
                    {
                        xuatKhoanThuRaManHinh(dataKhoanThu);
                        break;
                    }
                case '3':
                    {
                        int ngay, thang, nam;
                        bool check = false;
                        printf("xoa khoan thu theo ngay: \n");
                        printf("moi nhap ngay: "); scanf("%d",&ngay);
                        printf("moi nhap thang: "); scanf("%d",&thang);
                        printf("moi nhap nam: "); scanf("%d",&nam);
                        Node_KhoanThu *p0 = dataKhoanThu.pHead;
                        Node_KhoanThu *p1 = p0->pNext;
                        while(1){
                            if(p0->data.time.ngay == ngay && p0->data.time.thang == thang && p0->data.time.nam == nam){
                                dataKhoanThu.pHead = p1;
                                check = true;
                                break;
                            }
                            if(p1->data.time.ngay == ngay && p1->data.time.thang == thang && p1->data.time.nam == nam){
                                p0->pNext = p1->pNext;
                                check = true;
                                break;
                            }
                            p0 = p0->pNext;
                            p1 = p1->pNext;
                        }
                        if(check){
                            printf("da xoa xong du lieu.\n");
                        }else{
                            printf("khong tim thay du lieu vao ngay ma ban nhac toi,vui long kiem tra lai!!\n");
                        }
                        break;
                    }
                case '4':
                    {
                        int ngay, thang, nam;
                        bool check = false;
                        printf("tim kiem khoan thu theo ngay: \n");
                        printf("moi nhap ngay: "); scanf("%d",&ngay);
                        printf("moi nhap thang: "); scanf("%d",&thang);
                        printf("moi nhap nam: "); scanf("%d",&nam);
                        Node_KhoanThu *p = dataKhoanThu.pHead;
                        do{
                            if(p->data.time.ngay == ngay && p->data.time.thang == thang && p->data.time.nam == nam){
                                printf("---------------\n");
                                printf("thoi gian: %d/%d/%d\n",p->data.time.ngay,p->data.time.thang,p->data.time.nam);
                                printf("khoan thu: %d\n",p->data.tien_thu);
                                printf("mo ta khoan thu: %s\n",p->data.mo_ta);
                                printf("---------------\n");
                                check = true;
                                break;
                            }
                            p = p->pNext;
                        }while(p != NULL);
                        if(!check){
                            printf("khong tim thay du lieu vao ngay ma ban nhac toi,vui long kiem tra lai!!\n");
                        }
                        break;
                    }
                }
                printf("nhan phim bat ki de tiep tuc.\n");
                getch();
                }while(key_thu != '0');
                goto Label;
            }
        case '2':
            {
                do{
                    system("cls");
                    menu_chi();
                    printf("moi ban chon phim chuc nang: ");
                    key_chi = getch();
                    if(key_chi == '0'){
                        break;
                    }
                    switch(key_chi)
                    {
                        case '1':
                        {
                        taoDataKhoanChi(&dataKhoanChi);
                        break;
                        }
                    case '2':
                        {
                        xuatKhoanChiRaManHinh(dataKhoanChi);
                        break;
                        }
                    case '3':
                        {
                            int ngay, thang, nam;
                        bool check = false;
                        printf("xoa khoan chi theo ngay: \n");
                        printf("moi nhap ngay: "); scanf("%d",&ngay);
                        printf("moi nhap thang: "); scanf("%d",&thang);
                        printf("moi nhap nam: "); scanf("%d",&nam);
                        Node_KhoanChi *p0 = dataKhoanChi.pHead;
                        Node_KhoanChi *p1 = p0->pNext;
                        while(1){
                            if(p0->data.time.ngay == ngay && p0->data.time.thang == thang && p0->data.time.nam == nam){
                                dataKhoanChi.pHead = p1;
                                check = true;
                                break;
                            }
                            if(p1->data.time.ngay == ngay && p1->data.time.thang == thang && p1->data.time.nam == nam){
                                p0->pNext = p1->pNext;
                                check = true;
                                break;
                            }
                            p0 = p0->pNext;
                            p1 = p1->pNext;
                        }
                        if(check){
                            printf("da xoa xong du lieu.\n");
                        }else{
                            printf("khong tim thay du lieu vao ngay ma ban nhac toi,vui long kiem tra lai!!\n");
                        }
                        break;
                        }
                        case '4':
                        {
                        int ngay, thang, nam;
                        bool check = false;
                        printf("tim kiem khoan chi theo ngay: \n");
                        printf("moi nhap ngay: "); scanf("%d",&ngay);
                        printf("moi nhap thang: "); scanf("%d",&thang);
                        printf("moi nhap nam: "); scanf("%d",&nam);
                        Node_KhoanChi *p = dataKhoanChi.pHead;
                        do{
                            if(p->data.time.ngay == ngay && p->data.time.thang == thang && p->data.time.nam == nam){
                                printf("---------------\n");
                                printf("thoi gian: %d/%d/%d\n",p->data.time.ngay,p->data.time.thang,p->data.time.nam);
                                Node_LoaiTienChi *p1 = p->data.loai_tien_chi.pHead;
                                    do{
                                        printf("loai tien chi: %s, so tien chi: %d",p1->data.ten_loai,p1->data.tien_chi);
                                        p1 = p1->pNext;
                                    }while(p1 != NULL);
                                printf("---------------\n");
                                check = true;
                                break;
                            }
                            p = p->pNext;
                        }while(p != NULL);
                        if(!check){
                            printf("khong tim thay du lieu vao ngay ma ban nhac toi,vui long kiem tra lai!!\n");
                        }
                        break;
                        }

                        case '5':
                            {
                                int max = 0;
                                printf("thong tin ngay chi nhieu nhat thang: \n");
                                Node_KhoanChi *p = dataKhoanChi.pHead;
                                Node_KhoanChi *pMax;
                                do{
                                    if(p->data.tong_tien_chi > max){
                                        pMax = p;
                                    }
                                    p = p->pNext;
                                }while(p != NULL);
                                printf("---------------\n");
                                printf("thoi gian: %d/%d/%d\n",pMax->data.time.ngay,pMax->data.time.thang,pMax->data.time.nam);
                                Node_LoaiTienChi *p1 = pMax->data.loai_tien_chi.pHead;
                                    do{
                                        printf("loai tien chi: %s, so tien chi: %d",p1->data.ten_loai,p1->data.tien_chi);
                                        p1 = p1->pNext;
                                    }while(p1 != NULL);
                                printf("Tong tien chi: %d\n",pMax->data.tong_tien_chi);
                                printf("---------------\n");
                                break;
                            }
                        case '6':
                            {
                                int thang, nam;
                                printf("Nhap thang ban can tinh tong tien: "); scanf("%d",&thang);
                                printf("Nhap nam cua thang tren: "); scanf("%d",&nam);
                                printf("tong khoan chi thang %d nam %d: %d\n",thang, nam, tongKhoanChiThang(dataKhoanChi,thang,nam));
                                break;
                            }
                    }
                    printf("nhan phim bat ki de tiep tuc.\n");
                    getch();
                }while(key_chi != '0');
                goto Label;
            }
        }
    }while(1);

    return 0;
}
