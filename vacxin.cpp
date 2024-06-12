/**
 * @file code.cpp
 * @author Nguyen Trung Hieu (Hieu.NT234009@sis.hust.edu.vn)
 * @brief He thong quan ly trung tam tiem chung
 * @version 1.0
 * @date 2024-06-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include<stdio.h> // thu vien cho lenh nhap xuat du lieu
#include<string.h> // thu vien cho string
#include<stdlib.h> // thu vien cho cap phat mang dong trong C

/* Khai bao struct cho Date */
typedef struct
{
    int day;
    int month;
    int year;
} Date;

/* Khai bao struct cho vac xin */
typedef struct 
{
    char vacName[50];
    char ingredients[100]; // thanh phan cua vac xin
    char target[100]; // doi tuong su dung vac xin
    char guide[100]; // huong dan su dung
    int inventory; // luong ton kho
    Date expiryDate; // han su dung
} Vaccine;

/* Khai bao cac ham se su dung */
// Ham kiem tra tinh hop le cua ngay thang nam nhap vao
int validDate(Date date);

// Ham nhap thong tin vac xin
void inputVac(Vaccine *vaccine);

// Ham hien thi thong tin vac xin
void displayVac(Vaccine vaccine);

// Ham tim kiem  va hien thi vac xin qua ten vac xin
void searchVac(Vaccine vaccine[], int numofVac, char *vacSearch); //numofVac la so loai vac xin; vacSearch la ten loai vac xin muon tim kiem

// Ham sap xep va hien thi nhung loai vac xin theo han su dung
void searchExpiry(Vaccine vaccine[], int numofVac);

// Ham so sanh han su dung hai loai vac xin
int cmpVac(Vaccine v1, Vaccine v2);

// Ham sap xep so luong ton kho moi loai vac xin
void sortInven(Vaccine vaccine[], int numofVac);

// Ham nhap them vac xin moi 
void addVac(Vaccine **vaccine, int *numofVac, int newAddvac); // newAddvac la so luong vac xin moi muon nhap

// Ham cap nhat thong tin 1 vac xin da nhap
void deleteVac(Vaccine **vaccine, int *numofVac, int index); // index la so thu tu cua vac xin 

// Ham xoa thong tin 1 vac xin da nhap
int main() // ham main
{
    int numofVac; // So luong loai vac xin
    char vacSearch[50]; // Ten loai vac xin tim kiem
    int choice, continueInput; // bien phuc vu menu lua chon hanh dong
    printf("Nhap so luong loai vaccine: ");
    scanf("%d", &numofVac);
    Vaccine *vaccine = (Vaccine *)malloc(numofVac*sizeof(Vaccine));
    for(int i = 0; i < numofVac; i ++)
    {
        printf("\nNhap thong loai vaccine thu %d: ", i + 1);
        inputVac(&vaccine[i]);
    }
    do
    {
        printf("\n1.Tim kiem vac xin qua ten (Nhap ban phim so 1)");
        printf("\n2.Sap xep vac xin theo so luong ton kho (Nhap ban phim so 2)");
        printf("\n3.Sap xep vac xin theo han su dung (Nhap ban phim so 3)");
        printf("\n4.Nhap thong tin them vac xin moi (Nhap ban phim so 4)");
        printf("\n5.Xoa 1 vac xin da nhap (Nhap ban phim so 5)");
        printf("\nHay lua chon hanh dong tiep theo cua ban: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("\nNhap ten loai vac xin muon tim kiem: ");
                fflush(stdin);
                fgets(vacSearch, sizeof(vacSearch), stdin);
                vacSearch[strlen(vacSearch) - 1] = '\0';
                searchVac(vaccine, numofVac, vacSearch);
                break;
            case 2:
                printf("\nDanh sach vac xin sap xep theo so luong ton kho:");
                sortInven(vaccine, numofVac);
                break;
            case 3:
                printf("\nDanh sach vac xin sap xep theo han su dung: ");
                searchExpiry(vaccine, numofVac);
                break;
            case 4:
                int newAddvac;
                printf("\nNhap so luong vac xin them moi: ");
                scanf("%d", &newAddvac);
                addVac(&vaccine, &numofVac, newAddvac);
                break;
            case 5:
                int index;
                printf("\nNhap so thu tu cua vac xin muon xoa: ");
                scanf("%d", &index);
                deleteVac(&vaccine, &numofVac, index);
                break;
            default:
                printf("\nKhong hop le. Hay nhap mot so tu 1 den 5");
                continue;
        }
        printf("\nBan co muon tiep tuc khong? (Y/N): ");
        fflush(stdin);
        scanf("%c", &continueInput);
    } while (continueInput == 'y' || continueInput == 'Y');
    free(vaccine);
    return 0;
}

/* Dinh nghia cac ham da su dung */
int validDate(Date date)
{
    if(date.year < 2024) // Kiem tra nam
        return 0;
    if(date.month < 1 || date.month > 12) // Kiem tra thang
        return 0;
    int daysInmonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // So ngay trong thang
    if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) // Kiem tra nam nhuan
    {
        daysInmonth[1] = 29;
    }
    if (date.day < 1 || date.day > daysInmonth[date.month - 1]) // Kiem tra so ngay trong thang
        return 0;
    return 1;
}

void inputVac(Vaccine *vaccine)
{
    printf("\nNhap ten loai vaccine: ");
    fflush(stdin);
    fgets(vaccine->vacName, sizeof(vaccine->vacName), stdin);
    vaccine->vacName[strlen(vaccine->vacName) - 1] = '\0'; // Bo ky tu xuong dong
    printf("\nNhap thanh phan cua vaccine: ");
    fflush(stdin);
    fgets(vaccine->ingredients, sizeof(vaccine->ingredients), stdin);
    vaccine->ingredients[strlen(vaccine->ingredients) - 1] = '\0';
    printf("\nNhap doi tuong su dung: ");
    fflush(stdin);
    fgets(vaccine->target, sizeof(vaccine->target), stdin);
    vaccine->target[strlen(vaccine->target) - 1] = '\0';
    printf("\nNhap huong dan su dung: ");
    fflush(stdin);
    fgets(vaccine->guide, sizeof(vaccine->guide), stdin);
    vaccine->guide[strlen(vaccine->guide) - 1] = '\0';
    while(1)
    {
        printf("\nNhap so luong thuoc ton kho: ");
        scanf("%d", &vaccine->inventory);
        if(vaccine->inventory > 0)
        {
            break;
        }
        else
        {
            printf("Vui long nhap so luong thuoc hop le");
        }
    }
    while(1)
    {
        printf("\nNhap han su dung (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &vaccine->expiryDate.year, &vaccine->expiryDate.month, &vaccine->expiryDate.day);
        if(validDate(vaccine->expiryDate))
        {
            break;
        }
        else
        {
            printf("\nXin nhap ngay thang nam hop le");
        }
    }
   
}

void displayVac(Vaccine vaccine)
{
    printf("\nTen loai vaccine: %s", vaccine.vacName);
    printf("\nThanh phan vaccine: %s", vaccine.ingredients);
    printf("\nDoi tuong su dung: %s", vaccine.target);
    printf("\nHuong dan su dung: %s", vaccine.guide);
    printf("\nLuong ton kho: %d", vaccine.inventory);
    printf("\nHan su dung: %d-%d-%d", vaccine.expiryDate.day, vaccine.expiryDate.month, vaccine.expiryDate.year);
}

void searchVac(Vaccine vaccine[], int numofVac, char *vacSearch)
{
    int found = 0;
    for(int i = 0; i < numofVac; i ++)
    {
        if(strcmp(vaccine[i].vacName, vacSearch) == 0)
        {
            printf("\nSo thu tu: %d", i); // so thu tu trong mang, thuan tiec cho viec tim kiem vac xin de xoa thong tin phia sau
            displayVac(vaccine[i]);
            found = 1;
        }
    }
    if(!found)
    {
        printf("\nKhong tim thay thong tin vac xin co ten tuong ung");
    }
}

void sortInven(Vaccine vaccine[], int numofVac)
{
    Vaccine temp;
    for(int i = 0; i < numofVac - 1; i ++)
    {
        for(int j = i + 1; j < numofVac; j ++)
        {
            if(vaccine[i].inventory > vaccine[j].inventory)
            {
                temp = vaccine[i];
                vaccine[i] = vaccine[j];
                vaccine[j] = temp;
            }
        }
    }
    for(int i = 0; i < numofVac; i ++)
    {
        printf("\nVac xin: %s - So luong: %d", vaccine[i].vacName, vaccine[i].inventory);
    }
}

int cmpVac(Vaccine v1, Vaccine v2)
{
    if(v1.expiryDate.year != v2.expiryDate.year)
    {
        return v1.expiryDate.year - v2.expiryDate.year;
    }   
    if(v1.expiryDate.month != v2.expiryDate.month)
    {
        return v1.expiryDate.month - v2.expiryDate.month;
    }
    return v1.expiryDate.day - v2.expiryDate.day;
}
void searchExpiry(Vaccine vaccine[], int numofVac)
{
    Vaccine temp;
    for(int i = 0; i < numofVac - 1; i ++)
    {
        for(int j = i + 1; j < numofVac; j ++)
        {
            if(cmpVac(vaccine[i], vaccine[j]) > 0)
            {
                temp = vaccine[i];
                vaccine[i] = vaccine[j];
                vaccine[j] = temp;
            }
        }
    }
    for(int i = 0; i < numofVac; i ++)
    {
        printf("\nVac xin: %s - Han su dung(YYYY-MM-DD): %d-%d-%d", vaccine[i].vacName, vaccine[i].expiryDate.year, vaccine[i].expiryDate.month, vaccine[i].expiryDate.day);
    }
}

void addVac(Vaccine **vaccine, int *numofVac, int newAddvac)
{
    *vaccine = (Vaccine *)realloc(*vaccine, (*numofVac + newAddvac) * sizeof(Vaccine));
    for (int i = 0; i < newAddvac; i++) 
    {
        printf("Nhap thong tin cho vac xin thu %d:\n", *numofVac + 1);
        inputVac(&(*vaccine)[*numofVac]);
        (*numofVac)++;
    }
}

void deleteVac(Vaccine **vaccine, int *numofVac, int index)
{
    *numofVac -= 1;
    for(int i = index; i < *numofVac - 1; i ++ )
    {
        (*vaccine)[index] = (*vaccine)[index + 1];
    }
    *vaccine = (Vaccine *)realloc(*vaccine, (*numofVac - 1) * sizeof(Vaccine));
    *numofVac --;
}


hi hiệp đây

hgghghghghgh