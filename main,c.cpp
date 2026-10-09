#include <stdio.h>

struct Subscription {
    int user_id;
    char account_name[30];
    int plan_type;
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;
};

int main() {
    int n;
    int i;
    int total_downgraded = 0;
    int total_violations = 0;

    do {
        printf("Nhap so luong tai khoan N (1 <= N <= 50): ");
        if (scanf("%d", &n) != 1 || n < 1 || n > 50) {
            printf("[LOI] So luong khong hop le! Vui long nhap lai.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    struct Subscription subs[50];

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);
        
        printf("Ma tai khoan (user_id): ");
        scanf("%d", &subs[i].user_id);

        printf("Ten tai khoan / Email (account_name): ");
        scanf("%s", subs[i].account_name);

        do {
            printf("Hang goi (1: Free, 2: Individual, 3: Family): ");
            scanf("%d", &subs[i].plan_type);
            if (subs[i].plan_type < 1 || subs[i].plan_type > 3) {
                printf("[LOI] Hang goi khong hop le (tu 1 den 3). Nhap lai!\n");
            } else {
                break;
            }
        } while (1);

        printf("So thiet bi dang ket noi (active_devices): ");
        scanf("%d", &subs[i].active_devices);
        if (subs[i].active_devices < 0) subs[i].active_devices = 0;

        printf("So ngay cham thanh toán (days_overdue): ");
        scanf("%d", &subs[i].days_overdue);
        if (subs[i].days_overdue < 0) subs[i].days_overdue = 0;

        subs[i].account_status = 1;
    }

    for (i = 0; i < n; i++) {
        if (subs[i].plan_type == 1) {
            subs[i].max_devices = 1;
        } else if (subs[i].plan_type == 2) {
            subs[i].max_devices = 1;
        } else if (subs[i].plan_type == 3) {
            subs[i].max_devices = 5;
        }

        if (subs[i].days_overdue > 3) {
            subs[i].plan_type = 1;
            subs[i].max_devices = 1;
            subs[i].account_status = 0;
            total_downgraded++;
        }

        if (subs[i].active_devices > subs[i].max_devices) {
            total_violations++;
        }
    }

    printf("\n\n=========================================================================================\n");
    printf("                       BAO CAO RA SOAT & QUAN LY TAI KHOAN SAAS                          \n");
    printf("=========================================================================================\n");
    printf("%-8s %-18s %-12s %-15s %-12s %-12s\n", "MA TK", "TEN TAI KHOAN", "GOI", "THI?T B? (D/T)", "NO (NGÀY)", "TR?NG THÁI");
    printf("-----------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        char plan_name[20];
        if (subs[i].plan_type == 1) sprintf(plan_name, "Free");
        else if (subs[i].plan_type == 2) sprintf(plan_name, "Individual");
        else if (subs[i].plan_type == 3) sprintf(plan_name, "Family");

        char device_info[20];
        sprintf(device_info, "%d/%d", subs[i].active_devices, subs[i].max_devices);

        char status_str[20];
        if (subs[i].account_status == 1) {
            sprintf(status_str, "Active");
        } else {
            sprintf(status_str, "Downgraded");
        }

        printf("%-8d %-18s %-12s %-15s %-12d %-12s\n",
               subs[i].user_id,
               subs[i].account_name,
               plan_name,
               device_info,
               subs[i].days_overdue,
               status_str);
    }

    printf("-----------------------------------------------------------------------------------------\n");
    printf("BAO CAO THONG KE VAN HANH:\n");
    printf("- Tong so tai khoan da ra soat: %d\n", n);
    printf("- So luong tai khoan bi ha cap ve goi Free do no cuoc > 3 ngay: %d\n", total_downgraded);
    printf("- So luong tai khoan dang vi pham vuot qua so thiet bi cho phep: %d\n", total_violations);
    printf("=========================================================================================\n");

    return 0;
}
