#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


typedef enum {
	LOW = 1,
	MEDIUM = 2,
	HIGH = 3,
} Graphics_Quality;

struct engine {
	char name[50];
	char target_platform[50];
	float stable_fps;
	char physics_support;
	Graphics_Quality graphics_quality;
	float size_sdk;
	double license_cost;
};

typedef struct engine Engine;
Engine one;

int write_file(char* fname, int size, Engine* one);
int input_engine(Engine* one, int size);

int main()
{
	setlocale(LC_ALL, "RUS");
	int size;
	char fname[20] = "engine.txt";

	printf("Введите количество движков\n");
	scanf("%d", &size);

	Engine* one = (Engine*)malloc(size * sizeof(Engine));
	if (one == NULL) {
		printf("Ошибка выделения памяти!\n");
		return 0;
	}
	for (int i = 0; i < size; i++) {
		input_engine(&one[i], i);
	}
	write_file(fname, size, one);

	free(one);
}

int input_engine(Engine* one, int size)
{
	getchar();
	puts("Введите название:");
	fgets(one->name, sizeof(one->name), stdin);
	one->name[strcspn(one->name, "\n")] = 0;
	
	puts("Введите целевую платформу:");
	fgets(one->target_platform, sizeof(one->target_platform), stdin);
	one->target_platform[strcspn(one->target_platform, "\n")] = 0;

	puts("Введите стабильный FPS:");
	scanf("%f", &one->stable_fps);
	getchar();

	puts("Поддержка физики (+ - да, - - нет):");
	scanf(" %c", &one->physics_support);


	int graphics;
	puts("Введите качество графики (1 - Низкое /2 - Среднее /3 - Высокое):");
	scanf("%d", &graphics);

	if (graphics < 1 || graphics > 3) {
		graphics = 0;
	}
	one->graphics_quality = (Graphics_Quality)graphics;


	puts("Введите размер SDK:");
	scanf("%f", &one->size_sdk);

	puts("Введите стоимость лицензии:");
	scanf("%lf", &one->license_cost);
	puts("-----------------------------------------------------------");
}

int write_file(char* fname, int size, Engine* one)
{
	FILE* out;
	if ((out = fopen(fname, "wt")) == NULL)
	{
		printf("Ошибка открытия файла для записи");
		return 0;
	}
	for (int i = 0; i < size; i++)
	{
		const char* quality_str = "";
		switch (one[i].graphics_quality) {
		case LOW:
			quality_str = "Низкое";
			break;
		case MEDIUM:
			quality_str = "Среднее";
			break;
		case HIGH:
			quality_str = "Высокое";
			break;
		}
		fprintf(out, "Название: %s; ", one[i].name);
		fprintf(out, "Целевая платформа: %s; ", one[i].target_platform);
		fprintf(out, "Стабильный FPS: %f; ", one[i].stable_fps);
		fprintf(out, "Поддержка физики: %c; ", one[i].physics_support);
		fprintf(out, "Качество графики: %s; ", quality_str);
		fprintf(out, "Размер SDK: %f ГБ; ", one[i].size_sdk);
		fprintf(out, "Стоимость лицензии: %lf\n", one[i].license_cost);

	}
	fclose(out);
}