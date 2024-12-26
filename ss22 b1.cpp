#include<stdio.h>
#include<string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} sinhVien;

void printStudents(sinhVien sv[], int *n){
	if (n == 0) {
    printf("Danh sach rong.\n");
    } else {
        for (int i = 0; i < *n; i++) {
           	printf("ID: %d\n", sv[i].id);
           	printf("Ten: %s",sv[i].name);
           	printf("Tuoi: %d\n",sv[i].age);
        }
    }
}
void addStudent(sinhVien sv[], int *n) {
    sinhVien newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    fflush(stdin);
    printf("Nhap ten: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    fflush(stdin);
    printf("Nhap tuoi: ");
    scanf("%d", &newStudent.age);
    sv[*n] = newStudent;
    (*n)++;
    FILE *file; 
	file = fopen("students.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file\n");
        return;
    }
    fwrite(n, sizeof(int), 1, file);
    fwrite(sv, sizeof(sinhVien), *n, file);
    fclose(file);
	
}
void deleteStudent(sinhVien sv[], int *n) {
    int id;
    printf("Nhap ID sinh vien muon xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *n; i++) {
        if (sv[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                sv[j] = sv[j + 1];
            }
            (*n)--;
            FILE *file;
			file = fopen("students.bin", "wb");
            if (file == NULL) {
        		printf("Khong the mo file\n");
        		return;
    		}
            fwrite(n, sizeof(int), 1, file);
            fwrite(sv, sizeof(sinhVien), *n, file);
            fclose(file);
            printf("Da xoa sinh vien id %d\n", id);
            return;
        }
    }
    printf("ID %d khong ton tai\n", id);
}
void searchStudent(sinhVien sv[], int *n) {
    int id;
    printf("Nhap ID sinh vien muon tim: ");
    scanf("%d", &id);
    for (int i = 0; i < *n; i++) {
        if (sv[i].id == id) {
            printf("Tim thay: ID: %d, Ten: %s, Tuoi: %d\n", sv[i].id, sv[i].name, sv[i].age);
            return;
        }
    }
    printf("id %d khong ton tai", id);
}
void sortStudents(sinhVien sv[], int *n) {
    for (int i = 0; i < *n - 1; i++) {
        for (int j = i + 1; j < *n; j++) {
            if (sv[i].id > sv[j].id) {
                sinhVien temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    FILE *file;
	file = fopen("students.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file\n");
        return;
    }
    fwrite(&n, sizeof(int), 1, file);
    fwrite(sv, sizeof(sinhVien), *n, file);
    fclose(file);
    printf("Danh sach da duoc sap xep.\n");
}
void editStudent(sinhVien sv[], int *n) {
    int id;
    printf("Nhap ID muon sua: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if (sv[i].id == id) {
            printf("Nhap ten moi: ");
            getchar();
            fgets(sv[i].name, sizeof(sv[i].name), stdin);
            sv[i].name[strcspn(sv[i].name, "\n")] = 0;
            printf("Nhap tuoi moi: ");
            scanf("%d", &sv[i].age);
            FILE *file;
			file = fopen("students.bin", "wb");
            if (file == NULL) {
        		printf("Khong the mo file\n");
        		return;
    		}
            fwrite(n, sizeof(int), 1, file);
            fwrite(sv, sizeof(sinhVien), *n, file);
            fclose(file);
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }
    printf("ID %d khong tim thay\n", id);
}

int main(){
	sinhVien sv[100];
	int n;
	int choose;
    do {
    	printf("\nMENU\n");
    	printf("1. In danh sach sinh vien\n");
    	printf("2. Them sinh vien\n");
    	printf("3. Sua thong tin sinh vien\n");
    	printf("4. Xoa sinh vien\n");
    	printf("5. Tim kiem sinh vien\n");
    	printf("6. Sap xep danh sach sinh vien\n");
    	printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choose);

        switch (choose) {
            case 1:
                printStudents(sv,&n);
                break;
            case 2:
                addStudent(sv,&n);
                break;
            case 3:
                editStudent(sv,&n);
                break;
            case 4:
                deleteStudent(sv,&n);
                break;
            case 5:
                searchStudent(sv,&n);
                break;
            case 6:
                sortStudents(sv,&n);
                break;
            case 7:
                printf("Thoat chuong trinh");
                break;
            default:
                printf("Lua chon khong hop le");
        }
    } while (choose != 7);
	return 0;
}
