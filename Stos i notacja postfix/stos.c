#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#pragma warning(disable : 4996)
struct stos
{
	char tab[100];
	int top;
};
struct stos2
{
	int tab[100];
	int top;
};

void push(char obiekt,struct stos *TAB)
{
	TAB->top++;

	TAB->tab[TAB->top] = obiekt;
}
void push2(int obiekt, struct stos2 *TAB)
{
	TAB->top++;
	
	TAB->tab[TAB->top] = obiekt;
}
void pop(struct stos *TAB)
{
	TAB->top--;
	
}
void pop2(struct stos2 * TAB)
{
	TAB->top--;

}
char peek(struct stos *TAB)
{
	return TAB->tab[TAB->top];
	
}

bool isEmpty(struct stos *TAB)
{
	if (TAB->top == 0) return true;
	else return false;
}
int size(struct stos *TAB)
{
	return TAB->top;
}
void INtoPOST(char letter,struct stos *STOS,struct stos *WYJSCIE)
{
	if (letter != '+'&&letter != '-'&&letter != '*'&&letter != '('&&letter != ')'&&letter != '/')
	{
		push(letter, WYJSCIE);
		
	}
	else if (letter == '(')
	{
		push(letter, STOS);
	}
	else if (letter == ')')
	{
		while (peek(STOS) != '(')
		{
			push(peek(STOS), WYJSCIE);
			pop(STOS);
		}
		pop(STOS);
	}
	else if (letter == '-'|| letter == '+')
	{
		while (peek(STOS) == '-' || peek(STOS) == '+'|| peek(STOS) == '*' || peek(STOS) == '/')
		{
			push(peek(STOS), WYJSCIE);
			pop(STOS);
		}
		push(letter, STOS);
	}
	else if (letter == '*' || letter == '/')
	{
		while (peek(STOS) == '*' || peek(STOS) == '/')
		{
			push(peek(STOS), WYJSCIE);
			pop(STOS);
			
		}
		push(letter, STOS);
    
	}
}
int main()
{
	struct stos STOS[1];
	struct stos WYJSCIE[1];
	STOS->top =0;
	
	WYJSCIE->top = 0;
	

	FILE *in = fopen("infix.txt", "r");
	if (in != NULL) {
		char line[BUFSIZ];
		while (fgets(line, sizeof line, in) != NULL) {
			char *start = line;
			char field;
			int n;
			while (sscanf(start, "%c%n", &field, &n) == 1) {
				
				start += n;
				
				INtoPOST(field, STOS, WYJSCIE);
				
			}
			while (isEmpty(STOS) == false)
			{
				push(peek(STOS), WYJSCIE);
				pop(STOS);
     
			}

			
		}

		fclose(in);
	}
	FILE *out = fopen("postfix.txt", "w");
	for (int i = 1; i < WYJSCIE->top+1; i++) {
		fprintf(out, "%c", WYJSCIE->tab[i]);
		
	}
	fclose(out);

	struct stos2 STOS2[1];
	STOS2->top = 0;
	int tablica[100];
	char tablica2[100];
	int i = 0, j = 0,ile=0;
	
	FILE *in2 = fopen("postfix2.txt", "r");
	char znak = getc(in2);
	while (znak!= EOF)
	{
		fscanf(in2, "%i", &tablica[i]);	
	    i++;
		znak = getc(in2);
		ile++;
	}
    fclose(in2);
	FILE *in3 = fopen("postfix2.txt", "r");
	i = 0;
	char znak2 = getc(in3);
	while (znak2 != EOF)
	{
		fscanf(in3, " %c", &tablica2[i]);
		i++;
		znak2 = getc(in3);
	}
	fclose(in3);
	int temp;
	for (i = 0; i < ile-1 ; i++)
	{
	
		if (tablica2[i] == '+')             
		{
		temp = (STOS2->tab[STOS2->top - 1]) +( STOS2->tab[STOS2->top ]);
		pop2(STOS2);
		pop2(STOS2);
		push2(temp, STOS2);
		
		}
		else if (tablica2[i] == '-')             
		{
			temp = (STOS2->tab[STOS2->top - 1]) - (STOS2->tab[STOS2->top ]);
			
			pop2(STOS2);
			pop2(STOS2);
			push2(temp, STOS2);
			
		}
		else if (tablica2[i] == '*')             
		{
			temp = (STOS2->tab[STOS2->top - 1]) *( STOS2->tab[STOS2->top ]);
			pop2(STOS2);
			pop2(STOS2);
			push2(temp, STOS2);
		}
		else if (tablica2[i] == '/')             
		{
			temp = (STOS2->tab[STOS2->top - 1]) / (STOS2->tab[STOS2->top ]);
			pop2(STOS2);
			pop2(STOS2);
			push2(temp, STOS2);
			
		}
		else
		{
			push2(tablica[i], STOS2);
			
		}
	}
	
	printf("\nWYNIK: %i\n", STOS2->tab[1]);
	system("pause");
	return 0;
}