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

	printf("Ââåäèòå êîëè÷åñòâî äâèæêîâ\n");
	scanf("%d", &size);

	Engine* one = (Engine*)malloc(size * sizeof(Engine));
	if (one == NULL) {
		printf("Îøèáêà âûäåëåíèÿ ïàìÿòè!\n");
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
	puts("Ââåäèòå íàçâàíèå:");
	fgets(one->name, sizeof(one->name), stdin);
	one->name[strcspn(one->name, "\n")] = 0;
	
	puts("Ââåäèòå öåëåâóþ ïëàòôîðìó:");
	fgets(one->target_platform, sizeof(one->target_platform), stdin);
	one->target_platform[strcspn(one->target_platform, "\n")] = 0;

	puts("Ââåäèòå ñòàáèëüíûé FPS:");
	scanf("%f", &one->stable_fps);
	getchar();

	puts("Ïîääåðæêà ôèçèêè (+ - äà, - - íåò):");
	scanf(" %c", &one->physics_support);


	int graphics;
	puts("Ââåäèòå êà÷åñòâî ãðàôèêè (1 - Íèçêîå /2 - Ñðåäíåå /3 - Âûñîêîå):");
	scanf("%d", &graphics);

	if (graphics < 1 || graphics > 3) {
		graphics = 0;
	}
	one->graphics_quality = (Graphics_Quality)graphics;


	puts("Ââåäèòå ðàçìåð SDK:");
	scanf("%f", &one->size_sdk);

	puts("Ââåäèòå ñòîèìîñòü ëèöåíçèè:");
	scanf("%lf", &one->license_cost);
	puts("-----------------------------------------------------------");
}

int write_file(char* fname, int size, Engine* one)
{
	FILE* out;
	if ((out = fopen(fname, "wt")) == NULL)
	{
		printf("Îøèáêà îòêðûòèÿ ôàéëà äëÿ çàïèñè");
		return 0;
	}
	for (int i = 0; i < size; i++)
	{
		const char* quality_str = "";
		switch (one[i].graphics_quality) {
		case LOW:
			quality_str = "Íèçêîå";
			break;
		case MEDIUM:
			quality_str = "Ñðåäíåå";
			break;
		case HIGH:
			quality_str = "Âûñîêîå";
			break;
		}
		fprintf(out, "Íàçâàíèå: %s; ", one[i].name);
		fprintf(out, "Öåëåâàÿ ïëàòôîðìà: %s; ", one[i].target_platform);
		fprintf(out, "Ñòàáèëüíûé FPS: %f; ", one[i].stable_fps);
		fprintf(out, "Ïîääåðæêà ôèçèêè: %c; ", one[i].physics_support);
		fprintf(out, "Êà÷åñòâî ãðàôèêè: %s; ", quality_str);
		fprintf(out, "Ðàçìåð SDK: %f ÃÁ; ", one[i].size_sdk);
		fprintf(out, "Ñòîèìîñòü ëèöåíçèè: %lf\n", one[i].license_cost);

	}
	fclose(out);
}
