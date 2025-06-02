#include "TASK.h"
#include <locale.h>

int main() {

    setlocale(LC_ALL, "Russian");

    char mem[50] = "";  // Увеличен буфер памяти

    while(1) {
        int item;
        printf("\n1. Вычислить в обратной польской записи\n");
        printf("2. Очистить память\n");
        printf("3. Помощь\n");
        printf("4. Выход\n");
        scanf("%i", &item);
        getchar();

        if(item == 1) {
            char string[100];
            char buf[350];  // Увеличен размер буфера

            printf("\nВведите выражение, разделяя элементы пробелами\n");
            printf("%s ", mem);
            fgets(string, sizeof(string), stdin);
            string[strcspn(string, "\n")] = '\0';  // Убираем перевод строки

            snprintf(buf, sizeof(buf), "%s %s", mem, string);  // Безопасное объединение

            char *res = stacked(buf);
            if(res) {
                strncpy(mem, res, 49);
                mem[49] = '\0';  // Гарантируем завершение строки
                printf("\nРезультат: %s\n", mem);
                free(res);
            }
        }
        else if(item == 2) {
            strcpy(mem, "");
            printf("\nПамять очищена\n");
        }
        else if(item == 3) {
            printf("\n-----------------------\n");
            printf("Калькулятор обратной польской записи\n");
            printf("Поддерживаемые операции и константы:\n");
            printf("Бинарные: + - * / pow avg2 log\n");
            printf("Унарные: u- (унарный минус) inv (1/x)\n");
            printf("Тригонометрические: sin cos tan cot sec csc\n");
            printf("Гиперболические: sinh cosh tanh\n");
            printf("Обратные тригонометрические: asin acos atan\n");
            printf("Обратные гиперболические: asinh acosh atanh\n");
            printf("Экспоненты/логарифмы: exp sqrt ln log10 log2\n");
            printf("Статистические: avgn (n чисел) stddevn (n чисел)\n");
            printf("Константы: pi e\n");
            printf("Состояние стека сохраняется между операциями\n");
            printf("Пример: 5 3 2 * + -> 5 + (3*2) = 11\n");
            printf("-----------------------\n\n");
        }
        else {
            break;
        }
    }
    return 0;
}
