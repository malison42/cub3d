#include <string.h>
#include <unistd.h> // Для close
#include "parsing_map.h"
// Структура для тестов
typedef struct s_test_case
{
    char    *filepath;
    int     expected;
    char    *description;
} t_test_case;

void	free_path_texture(t_parsing_var *game_var)
{
	int i = 0;

	while (i < 4)
	{
		free(game_var->texturs[i].path_texture);
		 game_var->texturs[i].path_texture = NULL;
		i++;
	}
}

// --- Адаптированная тестовая функция ---
int run_single_test(char *filepath, char *test_name, int expected_result)
{
    int             fd;
    t_parsing_var   game_var;
    int             result;

    printf("Тест [%-40s]: ", test_name);

    // 1. Открытие файла
    fd = open(filepath, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening test file");
        printf("❌ FAIL (Не удалось открыть файл: %s)\n", filepath);
        return (1); // 1 ошибка
    }

    // 2. Инициализация структуры
    memset(&game_var, 0, sizeof(t_parsing_var));

    // 3. Запуск тестируемой функции
    result = parsing_configs(fd, &game_var);
	free_path_texture(&game_var);
    // 4. Закрытие файла
	get_next_line(-1);
    close(fd);

    // 5. Проверка результата
    if (result == expected_result)
    {
        printf("✅ OK. (Получено: %d)\n", result);
        // Дополнительная проверка для успешного случая:
        if (result == 1 && game_var.flags_mask != 0x3F)
        {

            printf("❌ FAIL. (Ожидалась установка всех флагов, flags_mask = %d)\n", game_var.flags_mask);
            return (1);
        }
    }
    else
    {
        printf("❌ FAIL. (Ожидалось: %d, Получено: %d)\n", expected_result, result);
        return (1); // 1 ошибка
    }

    return (0); // 0 ошибок
}

// --- Главная функция main ---
// int main(void)
// {
//     int errors = 0;

//     t_test_case tests[] = {
//       //  {"./test_1_success.cub", 1, "Полная и валидная конфигурация"},
//       //  {"./test_2_fail_dup.cub", 0, "Ошибка: Дубликат идентификатора (NO)"},
//         {"./test_3_fail_miss.cub", 0, "Ошибка: Неполная конфигурация (нет C)"},
//         {NULL, 0, NULL}
//     };

//     printf("--- 🧪 Тестирование parsing_configs с реальными файлами ---\n");

//     for (int i = 0; tests[i].filepath != NULL; i++)
//     {
//         errors += run_single_test(
//             tests[i].filepath,
//             tests[i].description,
//             tests[i].expected
//         );
//     }

//     printf("\n--- Итог: %d ошибок ---\n", errors);
//     return (errors > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
// }
