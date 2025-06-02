#include "TASK.h"
#include <ctype.h>

// Добавление элемента в стек с увеличенным буфером
node *push(node *head, int res, char *val) {
    node *node_one = malloc(sizeof(*node_one));
    if(!node_one) {
        free_stack(head);
        exit(1);
    }

    node_one->type = res;
    strncpy(node_one->value, val, 49);
    node_one->value[49] = '\0'; // Гарантируем завершение строки
    node_one->prev = head;
    return node_one;
}

// Извлечение элемента из стека
char *pop(node **head) {
    if(*head == NULL) {
        printf("\nНедостаточно значений или неверный порядок\n");
        return NULL;
    }

    char* val = strdup((*head)->value);
    if(!val) {
        free_stack(*head);
        exit(1);
    }

    node *adr = (*head)->prev;
    free(*head);
    *head = adr;
    return val;
}

// Освобождение памяти стека
void free_stack(node *h) {
    while (h) {
        node *p = h->prev;
        free(h);
        h = p;
    }
}

// Основная функция вычисления RPN с поддержкой всех операций
char *stacked(const char* string) {
    char* vals = strdup(string);
    if (!vals) {
        exit(1);
    }

    char* token = strtok(vals, " ");
    node* head = NULL;
    char local_buf[50]; // Локальный буфер для форматирования чисел

    while(token != NULL) {
        char *buf;
        double num = strtod(token, &buf);

        // Обработка чисел
        if(buf != token) {
            head = push(head, 1, token);
        }
        // Обработка констант
        else if(strcmp("pi", token) == 0) {
            snprintf(local_buf, 50, "%.10lf", M_PI);
            head = push(head, 1, local_buf);
        }
        else if(strcmp("e", token) == 0) {
            snprintf(local_buf, 50, "%.10lf", M_E);
            head = push(head, 1, local_buf);
        }
        // Обработка операций
        else {
            char *buf_val = pop(&head);
            if(!buf_val) {
                free(vals);
                free_stack(head);
                return NULL;
            }
            double first = strtod(buf_val, NULL);
            free(buf_val);

            // Арифметические операции
            if (strcmp(token, "+") == 0) {
                char* buf_val2 = pop(&head);
                if(!buf_val2) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double second = strtod(buf_val2, NULL);
                free(buf_val2);
                snprintf(local_buf, 50, "%.10lf", first + second);
                head = push(head, 1, local_buf);
            }
            else if (strcmp(token, "-") == 0) {
                char* buf_val2 = pop(&head);
                if(!buf_val2) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double second = strtod(buf_val2, NULL);
                free(buf_val2);
                snprintf(local_buf, 50, "%.10lf", second - first);
                head = push(head, 1, local_buf);
            }
            else if (strcmp(token, "*") == 0) {
                char* buf_val2 = pop(&head);
                if(!buf_val2) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double second = strtod(buf_val2, NULL);
                free(buf_val2);
                snprintf(local_buf, 50, "%.10lf", first * second);
                head = push(head, 1, local_buf);
            }
            else if (strcmp(token, "/") == 0) {
                if (first == 0) {
                    printf("\nДеление на ноль\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                char* buf_val2 = pop(&head);
                if(!buf_val2) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double second = strtod(buf_val2, NULL);
                free(buf_val2);
                snprintf(local_buf, 50, "%.10lf", second / first);
                head = push(head, 1, local_buf);
            }
            else if (strcmp(token, "pow") == 0) {
                char* buf_val2 = pop(&head);
                if(!buf_val2) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double second = strtod(buf_val2, NULL);
                free(buf_val2);
                snprintf(local_buf, 50, "%.10lf", pow(second, first));
                head = push(head, 1, local_buf);
            }
            // Унарные операции
            else if(strcmp(token, "u-") == 0) {
                snprintf(local_buf, 50, "%.10lf", -first);
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "inv") == 0) {
                if(first == 0) {
                    printf("\nДеление на ноль\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                snprintf(local_buf, 50, "%.10lf", 1.0 / first);
                head = push(head, 1, local_buf);
            }
            // Тригонометрические функции
            else if(strcmp(token, "sin") == 0) {
                snprintf(local_buf, 50, "%.10lf", sin(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "cos") == 0) {
                snprintf(local_buf, 50, "%.10lf", cos(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "tan") == 0) {
                snprintf(local_buf, 50, "%.10lf", tan(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "cot") == 0) {
                snprintf(local_buf, 50, "%.10lf", 1.0 / tan(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "sec") == 0) {
                snprintf(local_buf, 50, "%.10lf", 1.0 / cos(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "csc") == 0) {
                snprintf(local_buf, 50, "%.10lf", 1.0 / sin(first));
                head = push(head, 1, local_buf);
            }
            // Гиперболические функции
            else if(strcmp(token, "sinh") == 0) {
                snprintf(local_buf, 50, "%.10lf", sinh(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "cosh") == 0) {
                snprintf(local_buf, 50, "%.10lf", cosh(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "tanh") == 0) {
                snprintf(local_buf, 50, "%.10lf", tanh(first));
                head = push(head, 1, local_buf);
            }
            // Обратные тригонометрические
            else if(strcmp(token, "asin") == 0) {
                snprintf(local_buf, 50, "%.10lf", asin(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "acos") == 0) {
                snprintf(local_buf, 50, "%.10lf", acos(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "atan") == 0) {
                snprintf(local_buf, 50, "%.10lf", atan(first));
                head = push(head, 1, local_buf);
            }
            // Обратные гиперболические
            else if(strcmp(token, "asinh") == 0) {
                snprintf(local_buf, 50, "%.10lf", asinh(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "acosh") == 0) {
                snprintf(local_buf, 50, "%.10lf", acosh(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "atanh") == 0) {
                snprintf(local_buf, 50, "%.10lf", atanh(first));
                head = push(head, 1, local_buf);
            }
            // Экспонента и логарифмы
            else if(strcmp(token, "exp") == 0) {
                snprintf(local_buf, 50, "%.10lf", exp(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "sqrt") == 0) {
                if(first < 0) {
                    printf("\nКорень из отрицательного числа\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                snprintf(local_buf, 50, "%.10lf", sqrt(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "ln") == 0) {
                if(first <= 0) {
                    printf("\nЛогарифм неположительного числа\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                snprintf(local_buf, 50, "%.10lf", log(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "log10") == 0) {
                if(first <= 0) {
                    printf("\nЛогарифм неположительного числа\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                snprintf(local_buf, 50, "%.10lf", log10(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "log2") == 0) {
                if(first <= 0) {
                    printf("\nЛогарифм неположительного числа\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                snprintf(local_buf, 50, "%.10lf", log2(first));
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "log") == 0) {
                char* buf_val2 = pop(&head);
                if(!buf_val2) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double second = strtod(buf_val2, NULL);
                free(buf_val2);
                if(second <= 0 || first <= 0 || first == 1) {
                    printf("\nНеверные аргументы логарифма\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                snprintf(local_buf, 50, "%.10lf", log(second) / log(first));
                head = push(head, 1, local_buf);
            }
            // Статистические функции
            else if(strcmp(token, "avg2") == 0) {
                char* buf_val2 = pop(&head);
                if(!buf_val2) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double second = strtod(buf_val2, NULL);
                free(buf_val2);
                snprintf(local_buf, 50, "%.10lf", (first + second) / 2.0);
                head = push(head, 1, local_buf);
            }
            else if(strcmp(token, "avgn") == 0) {
                int n = (int)first;
                if(n <= 0) {
                    printf("\nНеверное количество элементов\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double sum = 0;
                double* nums = malloc(n * sizeof(double));
                if(!nums) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                for(int i = 0; i < n; i++) {
                    char* buf_val2 = pop(&head);
                    if(!buf_val2) {
                        free(nums);
                        free(vals);
                        free_stack(head);
                        return NULL;
                    }
                    nums[i] = strtod(buf_val2, NULL);
                    free(buf_val2);
                    sum += nums[i];
                }
                snprintf(local_buf, 50, "%.10lf", sum / n);
                head = push(head, 1, local_buf);
                free(nums);
            }
            else if(strcmp(token, "stddevn") == 0) {
                int n = (int)first;
                if(n <= 0) {
                    printf("\nНеверное количество элементов\n");
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                double sum = 0;
                double* nums = malloc(n * sizeof(double));
                if(!nums) {
                    free(vals);
                    free_stack(head);
                    return NULL;
                }
                for(int i = 0; i < n; i++) {
                    char* buf_val2 = pop(&head);
                    if(!buf_val2) {
                        free(nums);
                        free(vals);
                        free_stack(head);
                        return NULL;
                    }
                    nums[i] = strtod(buf_val2, NULL);
                    free(buf_val2);
                    sum += nums[i];
                }
                double mean = sum / n;
                double variance = 0;
                for(int i = 0; i < n; i++) {
                    variance += (nums[i] - mean) * (nums[i] - mean);
                }
                variance /= n;
                snprintf(local_buf, 50, "%.10lf", sqrt(variance));
                head = push(head, 1, local_buf);
                free(nums);
            }
            else {
                free(vals);
                free_stack(head);
                printf("\nНеверная операция: %s\n", token);
                return NULL;
            }
        }
        token = strtok(NULL, " ");
    }

    // Проверка корректности результата
    if(head == NULL) {
        printf("\nПустое выражение\n");
        free(vals);
        return NULL;
    }
    if(head->prev != NULL) {
        printf("\nНедостаточно операций\n");
        free_stack(head);
        free(vals);
        return NULL;
    }

    char* result = strdup(head->value);
    free_stack(head);
    free(vals);
    return result;
}

// Функция сравнения приоритетов операций (оставлена без изменений)
int oper_cmp(char *x, char *y, const oper* rank) {
    size_t first = 0, second = 0;
    for(const oper* i = rank; strcmp(i->name, "h") != 0; i++) {
        if(strcmp(x, i->name) == 0) first = i->rank;
        if(strcmp(y, i->name) == 0) second = i->rank;
    }
    return (first > second) ? 1 : (first == second) ? 0 : -1;
}

// Функция преобразования в обратную польскую запись (оставлена без изменений)
char **make_poli(char *rom) {
    char *string = strdup(rom);
    char **arr_out = malloc(100 * sizeof(char*));
    if(!arr_out) exit(1);

    char *stack[100];
    int out = -1, opers = -1;
    char *token = strtok(string, " ");

    oper ranks[] = {{1, "+"}, {1, "-"}, {2, "*"}, {2, "/"}, {4, "^"}, {10, "h"}};

    while(token) {
        char *end;
        double num = strtod(token, &end);

        if(end != token) {
            arr_out[++out] = strdup(token);
        }
        else if (strcmp(token, ")") == 0) {
            while (opers >= 0 && strcmp(stack[opers], "(") != 0) {
                arr_out[++out] = strdup(stack[opers--]);
            }
            if (opers >= 0 && strcmp(stack[opers], "(") == 0) opers--;
            else exit(1);
        }
        else if (strcmp(token, "(") == 0) {
            stack[++opers] = token;
        }
        else {
            while (opers >= 0 && strcmp(stack[opers], "(") != 0 &&
                   oper_cmp(stack[opers], token, ranks) >= 0) {
                arr_out[++out] = strdup(stack[opers--]);
            }
            stack[++opers] = token;
        }
        token = strtok(NULL, " ");
    }

    while (opers >= 0) {
        if (strcmp(stack[opers], "(") == 0 || strcmp(stack[opers], ")") == 0) exit(1);
        arr_out[++out] = strdup(stack[opers--]);
    }

    arr_out[++out] = NULL;
    free(string);
    return arr_out;
}
