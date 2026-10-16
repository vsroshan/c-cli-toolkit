#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void print_usage(const char *program_name)
{
    printf("C CLI Toolkit\n\n");
    printf("Usage:\n");
    printf("  %s help\n", program_name);
    printf("  %s reverse <text>\n", program_name);
    printf("  %s temperature <celsius>\n", program_name);
    printf("  %s count <file>\n", program_name);
    printf("  %s bytes <file>\n", program_name);
    printf("  %s stats <numbers-file>\n\n", program_name);
    printf("Commands:\n");
    printf("  reverse      Reverse text.\n");
    printf("  temperature  Convert Celsius to Fahrenheit.\n");
    printf("  count        Count lines, words, and bytes.\n");
    printf("  bytes        Display file size in bytes.\n");
    printf("  stats        Calculate numeric statistics.\n");
}
static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    errno = 0;
    double parsed = strtod(text, &end);
    if (text == end ||
        *end != '\0' ||
        errno == ERANGE ||
        !isfinite(parsed))
    {
        return 0;
    }
    *value = parsed;
    return 1;
}
static int command_reverse(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,
                "Error: provide one text argument.\n");
        fprintf(stderr,
                "Example: ./toolkit reverse hello\n");
        return 1;
    }
    const char *text = argv[2];
    size_t length = strlen(text);
    printf("Original: %s\n", text);
    printf("Reversed: ");
    for (size_t i = length; i > 0; i--)
    {
        putchar(text[i - 1]);
    }
    putchar('\n');
    return 0;
}
static int command_temperature(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,
                "Error: provide a Celsius temperature.\n");
        fprintf(stderr,
                "Example: ./toolkit temperature 32\n");
        return 1;
    }
    double celsius;
    if (!parse_double(argv[2], &celsius))
    {
        fprintf(stderr,
                "Error: invalid temperature '%s'.\n",
                argv[2]);
        return 1;
    }
    double fahrenheit =
        (celsius * 9.0 / 5.0) + 32.0;
    printf("%.2f Celsius = %.2f Fahrenheit\n",
           celsius,
           fahrenheit);
    return 0;
}
static int command_bytes(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,
                "Error: provide a file path.\n");
        return 1;
    }
    FILE *file = fopen(argv[2], "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    if (fseek(file, 0, SEEK_END) != 0)
    {
        perror("Error seeking in file");
        fclose(file);
        return 1;
    }
    long size = ftell(file);
    if (size < 0)
    {
        perror("Error determining file size");
        fclose(file);
        return 1;
    }
    printf("File: %s\n", argv[2]);
    printf("Size: %ld bytes\n", size);
    fclose(file);
    return 0;
}
static int command_count(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,
                "Error: provide a file path.\n");
        return 1;
    }
    FILE *file = fopen(argv[2], "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    unsigned long long bytes = 0;
    unsigned long long lines = 0;
    unsigned long long words = 0;
    int in_word = 0;
    int ch;
    int last_character = '\n';
    while ((ch = fgetc(file)) != EOF)
    {
        bytes++;
        last_character = ch;
        if (ch == '\n')
        {
            lines++;
        }
        if (isspace((unsigned char) ch))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            words++;
            in_word = 1;
        }
    }
    if (ferror(file))
    {
        perror("Error reading file");
        fclose(file);
        return 1;
    }
    if (bytes > 0 && last_character != '\n')
    {
        lines++;
    }
    printf("File:  %s\n", argv[2]);
    printf("Lines: %llu\n", lines);
    printf("Words: %llu\n", words);
    printf("Bytes: %llu\n", bytes);
    fclose(file);
    return 0;
}
static int command_stats(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,
                "Error: provide a numbers file.\n");
        fprintf(stderr,
                "Example: ./toolkit stats numbers.txt\n");
        return 1;
    }
    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    unsigned long long count = 0;
    double minimum = 0.0;
    double maximum = 0.0;
    long double sum = 0.0L;
    char token[256];
    while (fscanf(file, "%255s", token) == 1)
    {
        double number;
        if (!parse_double(token, &number))
        {
            fprintf(stderr,
                    "Error: '%s' is not a valid number.\n",
                    token);
            fclose(file);
            return 1;
        }
        if (count == 0)
        {
            minimum = number;
            maximum = number;
        }
        else
        {
            if (number < minimum)
            {
                minimum = number;
            }
            if (number > maximum)
            {
                maximum = number;
            }
        }
        sum += (long double) number;
        count++;
    }
    if (ferror(file))
    {
        perror("Error reading file");
        fclose(file);
        return 1;
    }
    fclose(file);
    if (count == 0)
    {
        fprintf(stderr,
                "Error: the file contains no numbers.\n");
        return 1;
    }
    long double average =
        sum / (long double) count;
    printf("Count:   %llu\n", count);
    printf("Minimum: %.6g\n", minimum);
    printf("Maximum: %.6g\n", maximum);
    printf("Average: %.2Lf\n", average);
    return 0;
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "help") == 0 ||
        strcmp(argv[1], "--help") == 0 ||
        strcmp(argv[1], "-h") == 0)
    {
        print_usage(argv[0]);
        return 0;
    }
    if (strcmp(argv[1], "reverse") == 0)
    {
        return command_reverse(argc, argv);
    }
    if (strcmp(argv[1], "temperature") == 0)
    {
        return command_temperature(argc, argv);
    }
    if (strcmp(argv[1], "count") == 0)
    {
        return command_count(argc, argv);
    }
    if (strcmp(argv[1], "bytes") == 0)
    {
        return command_bytes(argc, argv);
    }
    if (strcmp(argv[1], "stats") == 0)
    {
        return command_stats(argc, argv);
    }
    fprintf(stderr,
            "Error: unknown command '%s'.\n\n",
            argv[1]);
    print_usage(argv[0]);
    return 1;
}
