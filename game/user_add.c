#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 5
#define MAX_NOME 1000

typedef struct
{
    char *nome;
    int pontuacao;
} RECORDE;

typedef struct
{
    RECORDE vetor[MAX_ARRAY];
    int n;

} ARRAY;

RECORDE elemento(ARRAY *, int);
int tamanho(ARRAY *);
void insere(ARRAY *, RECORDE);

void remove_posicao(ARRAY *, int);
void printa(ARRAY *);
void sort(ARRAY *);
void bubble_sort(RECORDE *, int);

void User_add(char* NewRecName,int NewRecPt)
{
    FILE *scores;
    char *arqv = "Scores.txt";

    fopen(arqv,"w+");

    RECORDE rec[6];

    for(int i=0;i<5;i++)
    {
        fscanf(arqv,"%s %d",&rec[i].nome,&rec[i].pontuacao);
    }

    rec[5].nome = NewRecName;
    rec[5].pontuacao = NewRecPt;

    ARRAY array;
    array.n = 0;

    for(int i=0;i<6;i++)
    {
        insere(&array,rec[i]);
    }

    rewind(scores);

    printa(&array);
}

RECORDE elemento(ARRAY *array, int posicao)
{
	return array->vetor[posicao];
}

int tamanho(ARRAY *array)
{
	return array->n;
}

void insere(ARRAY *array, RECORDE recorde)
{
    if(tamanho(array) < MAX_ARRAY)
    {
        array->vetor[tamanho(array)] = recorde;
        array->n += 1;
    }
    else
    {
        RECORDE menor_recorde;
        menor_recorde = elemento(array, MAX_ARRAY - 1);

        if(menor_recorde.pontuacao >= recorde.pontuacao)
        {
            return;
        }
        else
        {
            remove_posicao(array, MAX_ARRAY - 1);
            insere(array, recorde);
            return;
        }
    }

    sort(array);
}

void remove_posicao(ARRAY *array, int posicao)
{
	if(tamanho(array) == 0)
	{
		return;
	}
	else if(tamanho(array) == 1)
	{
		array->n -= 1;
		return;
	}
	else
	{
		array->n -= 1;
		array->vetor[posicao] = array->vetor[tamanho(array)];
	}

    sort(array);
}

void printa(ARRAY *array)
{
	int i;
    RECORDE recorde;
	printf("Recordes:\n");

	for(i = 0; i < tamanho(array); i++)
	{
        recorde = elemento(array, i);
        printf("%s %d", i+1, recorde.nome, recorde.pontuacao);
	}
}

void sort(ARRAY *array)
{
	bubble_sort(array->vetor, array->n);
}

void bubble_sort(RECORDE list[], int n)
{
	int i, j;
    RECORDE swap;

	for(i = 0 ; i < ( n - 1 ); i++)
	{
		for(j = 0 ; j < n - i - 1; j++)
		{
			if(list[j].pontuacao < list[j+1].pontuacao)
			{
				swap = list[j];
				list[j] = list[j+1];
				list[j+1] = swap;
			}
		}
	}
}
