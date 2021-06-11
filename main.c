#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1000

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
    printf("nhap mo ta cho khoan thu nay khong? [y/n]");
    check = getch();
    if(check == 'y'){
        fflush(stdin);
        gets(temp.mo_ta);
    }else{
        strcpy(temp.mo_ta,"khong co mo ta");
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
    char ten[MAX_CHAR];
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
    printf("nhap cac khoan chi trong ngay: \n");
    khoiTaoListLoaiTienChi(&temp.loai_tien_chi);
    do{
    if(temp.loai_tien_chi.pHead == NULL){
        Node_LoaiTienChi *p = taoNode_LoaiTienChi();
        temp.loai_tien_chi.pHead = p;
    }else{
        Node_LoaiTienChi *p = taoNode_LoaiTienChi();
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
//-----------------------------------------------------------
//-end record khoan chi

int main()
{
    FILE *fptr;
    if((fptr = fopen("D:\\dataThu.txt","r")) == NULL){
        printf("File du lieu khoan thu chua co, tao moi du lieu...\n");

    }else{

    }
    return 0;
}
