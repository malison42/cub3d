/* Тест-раннер для парсера карт
   Запускает parse_game_file для каждого файла из списка и печатает результат.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing_map.h"

int main(void)
{
    struct test_case { const char *path; int expect_success; };

    struct test_case tests[] = {
        { "test_maps/valid.cub", 1 },
        { "test_maps/valid_extra_empty_lines.cub", 1 },
    { "test_maps/valid_permuted_elements.cub", 1 },
    { "test_maps/invalid_nonrect_spaces.cub", 0 },
        { "test_maps/invalid_unclosed.cub", 0 },
        { "test_maps/invalid_char.cub", 0 },
        { "test_maps/invalid_multiple_players.cub", 0 },
        { "test_maps/invalid_missing_texture.cub", 0 },
        { "test_maps/invalid_bad_color.cub", 0 },
        { "test_maps/invalid_player_on_edge.cub", 0 },
        { "test_maps/invalid_no_map.cub", 0 },
        { "test_maps/spaces_unclosed.cub", 0 },
        { NULL, 0 }
    };

    int i = 0;
    int unexpected_failures = 0;

    while (tests[i].path)
    {
        printf("=== Test: %s ===\n", tests[i].path);
        t_game *game = calloc(1, sizeof(t_game));
        if (!game)
        {
            perror("calloc");
            return 1;
        }
        game->texture = malloc(sizeof(t_textures));
        if (!game->texture)
        {
            perror("malloc");
            free(game);
            return 1;
        }

        char *argv[3];
        argv[0] = "test_runner";
        argv[1] = (char *)tests[i].path;
        argv[2] = NULL;

        int rc = parse_game_file(game, argv, 2);
        int succeeded = (rc != 0); /* в проекте parse_game_file возвращает ненулевое при успехе */
        printf("parse_game_file returned: %d -> %s\n", rc, succeeded ? "success" : "failure");

        if (succeeded != tests[i].expect_success)
        {
            printf("  -> ОЖИДАНИЕ: %s, ФАКТ: %s\n",
                   tests[i].expect_success ? "success" : "failure",
                   succeeded ? "success" : "failure");
            unexpected_failures++;
        }

        free(game->texture);
        free(game);
        printf("\n");
        i++;
    }

    if (unexpected_failures)
    {
        printf("%d unexpected failures\n", unexpected_failures);
        return 1;
    }

    printf("All tests finished.\n");
    return 0;
}
