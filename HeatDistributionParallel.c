#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <omp.h>

#define N 1000
#define AXIS_X 1000
#define AXIS_Y 1000
#define AXIS_Z 2

int main()
{
  int limit = 500000;
  int fill = (N-(N*.4))/2;
  double start, end;

	double ***p;
  int i,j,k,count=0;


	p=(double ***) malloc(AXIS_X * sizeof(double ***));

	for(i=0;  i<AXIS_X;  i++)
	{
		p[i]=(double **)malloc(AXIS_Y * sizeof(double *));

		for(j=0;  j<AXIS_Y;  j++)
		{
			p[i][j]=(double *)malloc(AXIS_Z * sizeof(double));
		}
	}

	for(k=0;  k<AXIS_Z;  k++) //init array
	{
		for(i=0;  i<AXIS_X;  i++)
		{
			for(j=0;  j<AXIS_Y;  j++)
			{
				*(*(*(p+i)+j)+k)= 20.0;
			}
		}
	}

  for(int x = 0; x<N; x++) //set fireplace wall
  {
    if(x<fill || x>(fill*2))
    {
      *(*(*(p+0)+x)+0) = 20.0;
      *(*(*(p+0)+x)+1)= 20.0;
    }
    else
    {
      *(*(*(p+0)+x)+0) = 100.0;
      *(*(*(p+0)+x)+1)= 100.0;
    }
  }

  for(int x = 0; x < N; x++) //set other walls
  {
    *(*(*(p+x)+0)+0) = 20.0;
    *(*(*(p+x)+N-1)+0)= 20.0;
    *(*(*(p+N-1)+x)+0) = 20.0;
    *(*(*(p+x)+0)+1)= 20.0;
    *(*(*(p+x)+N-1)+1) = 20.0;
    *(*(*(p+N-1)+x)+1)= 20.0;

  }

  count = 125;

  int next = 1;
  int current = 0;
  double temp1;
  double temp2;
  double temp3;
  double temp4;
  double temp5;

  start = omp_get_wtime();

  #pragma omp parallel for private(j, i, temp1, temp2, temp3, temp4, temp5 )
  for (int iteration = 0; iteration < limit; iteration++) //calculations
  {
    for (i = 1; i < 999; i++)
    {

      for (j = 1; j < 999; j++)
      {
        temp1 = p[i-1][j][current];
        temp2 = p[i+1][j][current];
        temp3 = p[i][j-1][current];
        temp4 = p[i][j+1][current];
        temp5 = .25 * (temp1 + temp2 +temp3 + temp4);
        *(*(*(p+i)+j)+next) = temp5;
      }
    }

    if(current == 0 && next == 1)
    {
      current = 1;
      next = 0;
    }

    else
    {
      current = 0;
      next = 1;
    }
  }

  end = omp_get_wtime();

  for(int a = 0; a<N; a = a + count) // print
  {
    for(int b =0; b<N; b = b + count)
    {
      printf("%f ", p[a][b][0]);
    }
    printf("\n");
  }

  printf("Time of computation: %f seconds\n", end-start);

  printf("Random sample point (8,500): %f\n", p[8][500][0]);

  for (int a = 0; a < N; a++)
  {
     for (int b = 0; b < N; b++)
     {
         free(p[a][b]);
     }
     free(p[a]);
  }
  free(p);

  return 0;
}
