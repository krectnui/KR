#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<locale.h>

#define HEIGHT 6
#define WIDTH 8
#define WIDTH2 9


int** arr_memory();
int** arr_memory_fl();
int file(int** points);

int tabl(int** points);//����� ������� � ������ �������
int tabl2(int** points, int maxpoint[WIDTH], float sum, float** res);//���������� ������� ��������������� ���������� 
int printf_funct(int** points, int maxpoint[WIDTH], float sum, float** res, int c);//����� �������������� �������
int no_tour( float** res);//����� �������������� ������� ��� ����� ������-���� �������
int maxmin(float** res, int x);//����� ������� �� ��������� : ������, ������, ��������� �����/����� n ���������� �����
int sort(int** points, int maxpoint[WIDTH], float sum, float** res, int numbigrok[HEIGHT]);//���������� ����������� �� �������� (�� �������� ��� �� �����������)
int maxminsrob( float** res);//��������� ������������,�����������,�����,������� ���������� ����� �� �����������
int zamena(int** points);//�������� �������� � ������� 

int main() {
	setlocale(LC_ALL, "RUS");

	int maxpoint[WIDTH] = { 800,900,750,700,750,500,700,600 };
	int numbigrok[6] = { 1,2,3,4,5,6 };

	int c = 0;
	int k = 0;
	int x = 0;

	int** points = arr_memory();
	float** res = arr_memory_fl();

	float sum = 0.0;

	file(points);
	
	tabl2(points, maxpoint, sum, res);

	while (c != 8) {
		puts("�������� ����� �� ��������������� ������ : \n1)����� ������� �������� �����������\n2)�������������� �������\n3)�������������� ������� ��� ������-���� �������\n4)������ ���������, ������ ��������� ��� ����������, ��������� ����� ��� ����� ���������� ���������� ����� \n5)������� ��������\n6)����������, ����������, ������� � ����� ���������� ����� ����� �������\n7)������ �����\n8)����� �� ���������");
		scanf("%d", &c);
		getchar();
		switch (c)
		{
		case 1:
			puts("\t\t ������� �������� � '������� �������'");
			puts("   ��������|  ATP  |  WTA  |   AO   |  GS  |  RG  |  Wd  |  US OP  |  ITF |");
			tabl(points);
			
			break;

		case 2:
			
			puts("\t\t �������������� ������� �������� � '������� �������'");
			puts("    ��������|    ATP  |   WTA  |   AO   |  GS  |  RG  |  Wd  |  US OP  |  ITF | ����� �����|");
			printf_funct(points, maxpoint, sum, res, c);

			break;
		case 3:
			system("cls");
			puts("������� ����� �������, ������� �� ����� �����������");
			puts(" ATP - 1| WTA - 2| AO - 3| GS - 4| RG - 5| Wd - 6| US OP - 7| ITF - 8|");
			no_tour( res);

			break;

		case 4:
			system("cls");
			puts("\n");
			puts("1)������ ���������\n2)������ ���������\n3)���������, ��������� ������ ��������� ���������� �����\n4)���������, ��������� ������ ��������� ���������� �����\n");
			maxmin(res,x);

			break;

		case 5:
			
			puts("\n");
			puts("�������� ����������\n1)�� ��������\n2)�� �����������");
			sort(points, maxpoint, sum, res, numbigrok);

			break;

		case 6:
			system("cls");
			maxminsrob(res);
			break;

		case 7 : 
			system("cls");
			zamena(points);
			break;
		case 8:
			exit(EXIT_SUCCESS);
			break;

		}
	}
}

int** arr_memory()
{
	int** array = (int**)malloc(HEIGHT * sizeof(int*));
	for (int i = 0; i < HEIGHT; i++) {
		array[i] = (int*)malloc(30 * sizeof(int));
	}
	return array;
}
 
int** arr_memory_fl()
{
	float** array = (float**)malloc(HEIGHT * sizeof(float*));
	for (int i = 0; i < HEIGHT; i++) {
		array[i] = (float*)malloc(30 * sizeof(float));
	}
	return array;
}

int file(int** points) {
	FILE* pog;
	pog = fopen("point.txt", "r");
	if (pog == NULL) {
		printf("ERROR");
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			fscanf(pog, "%d", &points[i][j]);
		}
	}
	return points;
}


int tabl(int** points) {
	
	for (int i = 0; i < HEIGHT; i++)
	{
		printf("��������� %d|", i + 1);
		for (int j = 0; j < WIDTH; j++) {
			printf(" %5d  ", points[i][j]);
		}puts("\n");
	}
	
	return points;
	
}

int tabl2(int** points, int maxpoint[WIDTH], float sum, float** res) {
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++) {
			res[i][j] = (float)points[i][j] / maxpoint[j];
			sum += res[i][j];
		}
		res[i][WIDTH ] = sum;
		sum = 0;
	}

	return res;
}

int printf_funct(int** points, int maxpoint[WIDTH], float sum, float** res) {
	tabl2(points, maxpoint, sum, res);
	for (int i = 0; i < HEIGHT; i++)
	{
		printf("��������� %d |", i + 1);
		for (int j = 0; j < WIDTH2; j++) {
			printf(" %7.2f", res[i][j]);

		}
		puts("\n");
	}
}
int no_tour( float** res){
		
		int u = 0;
		puts("\n");
		
		scanf("%d", &u);
		getchar();

		puts("\t\t �������������� ������� �������� � '������� �������'");
		puts("    ��������|     ATP    |    WTA    |    AO    |    GS   |   RG    |   Wd   |   US OP   |   ITF  | ����� �����|");

		for (int i = 0; i < HEIGHT; i++)
		{
			printf("��������� %d |", i + 1);
			for (int j = 0; j < WIDTH; j++) {
				if (j + 1 == u)  printf("         ");
				else {
					printf("   %7.2f ", res[i][j]);
				}
			} printf(" %8.2f", res[i][WIDTH] - res[i][u - 1]);
			puts("\n");
		}
}
int maxmin( float** res, int x) {
	scanf("%d",&x);

	if (x == 1) {
		float max = -100000.0;
		int index = 0;
		for (int i = 0; i < HEIGHT; i++) {
			if (res[i][WIDTH] > max) {
				max = res[i][WIDTH];
				index = i;
			}
		}
		puts("\n");
		printf("������ ��������� %d ����� - %.2f\n", index + 1, max);
		puts("\n");
	}
	else if (x == 2) {
		float min = 100000.0;
		int index1 = 0;
		for (int i = 0; i < HEIGHT; i++) {
			if (res[i][WIDTH] < min) {
				min = res[i][WIDTH];
				index1 = i;
			}
		}
		puts("\n");
		printf("������ ��������� %d ����� - %.2f\n", index1 + 1, min);
		puts("\n");
	}
	else if (x == 3) {
		puts("������� ���������� ����� ");
		int x1 = 0;
		scanf("%d", &x1);
		for (int i = 0; i < HEIGHT; i++) {
			if (res[i][WIDTH] > x1) {
				printf("��������� %d - %.2f\n", i + 1, res[i][WIDTH]);
			}
		}
		puts("\n");
	}
	else if (x == 4) {
		puts("������� ���������� ����� ");
		int x1 = 0;
		scanf("%d", &x1);
		for (int i = 0; i < HEIGHT; i++) {
			if (res[i][WIDTH] < x1) {
				printf("��������� %d - %.2f\n", i + 1, res[i][WIDTH]);
			}
		}
		puts("\n");
	}

	return 0;
}
int sort(int** points, int maxpoint[WIDTH], float sum, float** res, int numbigrok[HEIGHT]) {
		int x2 = 0;
		scanf("%d", &x2);

		if (x2 == 1) {
			tabl2(points, maxpoint, sum, res);
			puts("\t\t ������� �������� � '������� �������'");
			puts("       ��������|     ATP    |   WTA   |    AO    |    GS   |   RG    |   Wd   |   US OP   |   ITF  | ����� �����|");
			for (int i = 0; i < HEIGHT - 1; i++)
			{

				if (res[i][WIDTH] > res[i + 1][WIDTH]) {

					for (int j = 0; j < WIDTH2; j++) {
						float t = res[i][j];
						res[i][j] = res[i + 1][j];
						res[i + 1][j] = t;
						int tvr = 0;
						tvr = numbigrok[i];
						numbigrok[i] = numbigrok[i + 1];
						numbigrok[i + 1] = tvr;
					}
				}
			}
			for	(int i = 0; i < HEIGHT; i++) {
				printf("%d) ��������� %d |", i + 1, numbigrok[i]);
				for (int j = 0; j < WIDTH2; j++) {
					printf("  %8.2f", res[i][j]);
				}
				puts("\n");
			}
			puts("\n");
			for (int i = 0; i < HEIGHT; i++) {
				numbigrok[i] = i + 1;
			}
		}

		else if (x2 == 2) {
			tabl2(points, maxpoint, sum, res);
			puts("\t\t ������� �������� � '������� �������'");
			puts("       ��������|     ATP    |   WTA   |    AO    |    GS   |   RG    |   Wd   |   US OP   |   ITF  | ����� �����|");
			for (int z = 0; z < HEIGHT; z++) {
				for (int i = 0; i < HEIGHT - 1; i++)
				{
					if (res[i][WIDTH] < res[i + 1][WIDTH]) {

						for (int j = 0; j < WIDTH2; j++) {
							float t = res[i][j];
							res[i][j] = res[i + 1][j];
							res[i + 1][j] = t;
							int tvr = 0;
							tvr = numbigrok[i];
							numbigrok[i] = numbigrok[i + 1];
							numbigrok[i + 1] = tvr;
						}
					}
				}
			}
			for (int i = 0; i < HEIGHT; i++) {
				printf("%d) ��������� %d |", i + 1, numbigrok[i]);
				for (int j = 0; j < WIDTH2; j++) {
					printf("  %8.2f", res[i][j]);
				}
				puts("\n");
			}
			for (int i = 0; i < HEIGHT; i++) {
				numbigrok[i] = i + 1;
			}
		}

		else {
			puts("������");
		}
		return 0;

	

}
int maxminsrob(float** res) {

	puts("\n");
	float max = -100000.0;
	int index = 0;
	for (int i = 0; i < HEIGHT; i++) {
		if (res[i][WIDTH] > max) {
			max = res[i][WIDTH];
			index = i;
		}
	}
	printf("��������� %d ������ ���������� ���������� ����� : %4.2f\n", index+1, max);

	float min = 100000.0;
	int index1 = 0;
	for (int i = 0; i < HEIGHT; i++) {
		if (res[i][WIDTH] < min) {
			min = res[i][WIDTH];
			index1 = i;
		}
	}
	printf("��������� %d ������ ���������� ���������� ����� : %4.2f\n", index1+1, min);

	float sred = 0.0;
	float ressred = 0.0;
	for (int i = 0; i < HEIGHT; i++) {
		sred += res[i][WIDTH];
	}
	ressred = sred / HEIGHT;
	printf("������� ���������� �����, ��������� ������������ : %4.2f\n", ressred);

	float sum1 = 0.0;
	for (int i = 0; i < HEIGHT; i++) {
		sum1 += res[i][WIDTH];
	}
	printf("����� ���������� �����, ��������� ������������ : %4.2f\n", sum1);
	puts("\n");
	return 0;
}

int zamena(int** points) {

	int x = 0, y = 0;
	int m;
	puts("���������");
	scanf("%i", &x);
	puts("����� ������� :| ATP - 1| WTA - 2| AO - 3| GS - 4| RG - 5| Wd - 6| US OP - 7| ITF - 8|");
	scanf("%i", &y);
	printf("����� � ���������� %d:", x);
	scanf("%i", &m); 
	points[x-1][y-1] = m;

}