#include "TASK.h"
#include <locale.h>

int main() {

    setlocale(LC_ALL, "Russian");

    char mem[50] = "";  // �������� ����� ������

    while(1) {
        int item;
        printf("\n1. ��������� � �������� �������� ������\n");
        printf("2. �������� ������\n");
        printf("3. ������\n");
        printf("4. �����\n");
        scanf("%i", &item);
        getchar();

        if(item == 1) {
            char string[100];
            char buf[350];  // �������� ������ ������

            printf("\n������� ���������, �������� �������� ���������\n");
            printf("%s ", mem);
            fgets(string, sizeof(string), stdin);
            string[strcspn(string, "\n")] = '\0';  // ������� ������� ������

            snprintf(buf, sizeof(buf), "%s %s", mem, string);  // ���������� �����������

            char *res = stacked(buf);
            if(res) {
                strncpy(mem, res, 49);
                mem[49] = '\0';  // ����������� ���������� ������
                printf("\n���������: %s\n", mem);
                free(res);
            }
        }
        else if(item == 2) {
            strcpy(mem, "");
            printf("\n������ �������\n");
        }
        else if(item == 3) {
            printf("\n-----------------------\n");
            printf("����������� �������� �������� ������\n");
            printf("�������������� �������� � ���������:\n");
            printf("��������: + - * / pow avg2 log\n");
            printf("�������: u- (������� �����) inv (1/x)\n");
            printf("������������������: sin cos tan cot sec csc\n");
            printf("���������������: sinh cosh tanh\n");
            printf("�������� ������������������: asin acos atan\n");
            printf("�������� ���������������: asinh acosh atanh\n");
            printf("����������/���������: exp sqrt ln log10 log2\n");
            printf("��������������: avgn (n �����) stddevn (n �����)\n");
            printf("���������: pi e\n");
            printf("��������� ����� ����������� ����� ����������\n");
            printf("������: 5 3 2 * + -> 5 + (3*2) = 11\n");
            printf("-----------------------\n\n");
        }
        else {
            break;
        }
    }
    return 0;
}
