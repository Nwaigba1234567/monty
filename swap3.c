#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 1024
#define EXIT_FAILURE 1
#define BUFFER_SIZE 1024

int stack[STACK_SIZE];
int stack_size = 0;

void execute_nop()
{
    /* This function does nothing */
}

void execute_swap(int line_number)
{
	int temp = stack[stack_size - 1];
	stack[stack_size - 1] = stack[stack_size - 2];
	stack[stack_size - 2] = temp;

    if (stack_size < 2)
    {
        printf("L%d: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    stack[stack_size - 1] = stack[stack_size - 2];
    stack[stack_size - 2] = temp;
}

int main(int argc, char *argv[])
{
	char line[BUFFER_SIZE];
        int line_number = 1;
        char *file_path = argv[1];
        FILE *file = fopen(file_path, "r");

    if (argc != 2)
    {
        printf("USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    if (file == NULL)
    {
        printf("Error: Can't open file %s\n", file_path);
        return EXIT_FAILURE;
    }


#ifdef _POSIX_C_SOURCE
    char *buffer = NULL;
    size_t line_length = 0;
    ssize_t read;
     char *opcode = strtok(line, " \t");
     char *opcode = strtok(line, " \t");

    while ((read = getline(&buffer, &line_length, file)) != -1)
    {
        /* Copy the line to the fixed-size buffer*/
        strncpy(line, buffer, sizeof(line));

        /* Remove the trailing newline character, if present*/
        line[strcspn(line, "\n")] = '\0';

        /* Parse the opcode from the line*/
        char *opcode = strtok(line, " \t");

        /* Ignore empty lines and comments*/
        if (opcode == NULL || opcode[0] == '#')
        {
            line_number++;
            continue;
        }

        /* Execute the corresponding opcode*/
        if (strcmp(opcode, "nop") == 0)
        {
            execute_nop();
        }
        else if (strcmp(opcode, "swap") == 0)
        {
            execute_swap(line_number);
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
	    char *opcode = strtok(line, " \t");

        /* Remove the trailing newline character, if present*/
        line[strcspn(line, "\n")] = '\0';

        /* Ignore empty lines and comments*/
        if (opcode == NULL || opcode[0] == '#')
        {
            line_number++;
            continue;
        }

        /* Execute the corresponding opcode*/
        if (strcmp(opcode, "nop") == 0)
        {
            execute_nop();
        }
        else if (strcmp(opcode, "swap") == 0)
        {
            execute_swap(line_number);
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

