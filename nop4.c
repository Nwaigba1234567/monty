#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_FAILURE 1
#define BUFFER_SIZE 1024

void execute_nop()
{
    /* This function does nothing */
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    char *file_path = argv[1];
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("Error: Can't open file %s\n", file_path);
        return EXIT_FAILURE;
    }

    // Read the file line by line
    char line[BUFFER_SIZE];
    int line_number = 1;

#ifdef _POSIX_C_SOURCE
    char *buffer = NULL;
    size_t line_length = 0;
    ssize_t read;

    while ((read = getline(&buffer, &line_length, file)) != -1)
    {
        // Copy the line to the fixed-size buffer
        strncpy(line, buffer, sizeof(line));

        // Remove the trailing newline character, if present
        line[strcspn(line, "\n")] = '\0';

        // Parse the opcode from the line
        char *opcode = strtok(line, " \t");

        // Ignore empty lines and comments
        if (opcode == NULL || opcode[0] == '#')
        {
            line_number++;
            continue;
        }

        // Execute the corresponding opcode
        if (strcmp(opcode, "nop") == 0)
        {
            execute_nop();
        }
        else
        {
            printf("L%d: unknown instruction %s\n", line_number, opcode);
            free(buffer);
            fclose(file);
            return EXIT_FAILURE;
        }

        line_number++;
    }

    free(buffer);
#else
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Remove the trailing newline character, if present
        line[strcspn(line, "\n")] = '\0';

        // Parse the opcode from the line
        char *opcode = strtok(line, " \t");

        // Ignore empty lines and comments
        if (opcode == NULL || opcode[0] == '#')
        {
            line_number++;
            continue;
        }

        // Execute the corresponding opcode
        if (strcmp(opcode, "nop") == 0)
        {
            execute_nop();
        }
        else
        {
            printf("L%d: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            return EXIT_FAILURE;
        }

        line_number++;
    }
#endif

    fclose(file);

    return 0;
}

