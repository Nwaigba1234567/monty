#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 1024

typedef struct
{
	int data[STACK_SIZE];
	int top;
}	Stack;

void stackInit(Stack *stack)
{
	stack->top = -1;
}

int stackIsEmpty(Stack *stack)
{
	return (stack)->top == -1;
}

int stackIsFull(Stack *stack)
{
	return (stack)->top == STACK_SIZE - 1;
}

void stackPush(Stack *stack, int value)
{
	if (stackIsFull(stack))
	{
	printf("Error: Stack overflow\n");
	exit(EXIT_FAILURE);
	}
	stack->data[++stack->top] = value;
}

int stackPop(Stack *stack)
{
	if (stackIsEmpty(stack))
	{
	printf("Error: Stack underflow\n");
	exit(EXIT_FAILURE);
	}
	return (stack)->data[stack->top--];
}

void executeAdd(Stack *stack, int lineNum)
{
	int operand1, operand2, result;

	if (stack->top < 1)
	{
	printf("Error on line %d: can't add, stack too short\n", lineNum);
	exit(EXIT_FAILURE);
	}
	
	operand1 = stackPop(stack);
	operand2 = stackPop(stack);
	result = operand1 + operand2;
	stackPush(stack, result);
}

void executeInstruction(Stack *stack, const char *instruction, int lineNum)
{
	if (strcmp(instruction, "add") == 0)
	{
	executeAdd(stack, lineNum);
	}
	else
	{
	printf("Error on line %d: unknown instruction '%s'\n", lineNum, instruction);
	exit(EXIT_FAILURE);
	}
}

void processFile(const char *filename)
{
	FILE *file = fopen(filename, "r");
	char line[256];
	char instruction[16];
	int lineNum = 1;

	Stack stack;

	stackInit(&stack);
	
	if (file == NULL)
	{
	printf("Error: Can't open file '%s'\n", filename);
	exit(EXIT_FAILURE);
	}
    
	while (fgets(line, sizeof(line), file))
	{
	    line[strcspn(line, "\n")] = '\0';
	
	if (sscanf(line, "%15s", instruction) == 1)
	{
		executeInstruction(&stack, instruction, lineNum);
	}
	lineNum++;
	}
	fclose(file);
}

int main(int argc, char *argv[])
{
	const char *filename;
	
	if (argc != 2)
    {
	printf("USAGE: monty file\n");

	return (EXIT_FAILURE);
	}
	filename = argv[1];
	processFile(filename);
	
	return (0);
}
