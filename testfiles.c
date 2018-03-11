#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	FILE *fp;
	fp = fopen("rand.txt", "w");

	int num;
	int i;
	for (i=0; i<5000; i++)
	{
		num = rand() % (499 + 1 -1) + 1;
		fprintf(fp, "%d\n",num);
	}
	fclose(fp);
	return 1;
	
}	
