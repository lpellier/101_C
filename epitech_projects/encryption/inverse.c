#include "encryption.h"
 
// function for the calculation of determinant
float determinant(int **a, int k)
{
	float s = 1, det = 0;
	int **b;

	b = malloc(sizeof(int *) * k);
	for (int i = 0; i < k; i++)
		b[i] = malloc(sizeof(int) * k);

	int i, j, m, n, c;
	if (k == 1)
		return (a[0][0]);
    else
    {
		det = 0;
		for (c = 0; c < k; c++)
		{
			m = 0;
        	n = 0;
        	for (i = 0;i < k; i++)
          	{
            	for (j = 0 ;j < k; j++)
              	{
                	b[i][j] = 0;
               		if (i != 0 && j != c)
					{
                   		b[m][n] = a[i][j];
                   		if (n < (k - 2))
                    		n++;
                   		else
                    	{
                     		n = 0;
                     		m++;
                    	}
                   	}
               	}
            }
          	det = det + s * (a[0][c] * determinant(b, k - 1));
          	s = -1 * s;
        }
	}

    return (det);
}
 
 
// function for cofactor calculation
float ** cofactor(int **num, int f)
{
	int **b;
	float **fac;
	int p, q, m, n, i, j;

	b = malloc(sizeof(int *) * f);
	for (int i = 0; i < f; i++)
		b[i] = malloc(sizeof(int) * f);

	fac = malloc(sizeof(float *) * f);
	for (int i = 0; i < f; i++)
		fac[i] = malloc(sizeof(float) * f);
	for (q = 0;q < f; q++)
	{
		for (p = 0;p < f; p++)
		{
			m = 0;
			n = 0;
			for (i = 0;i < f; i++)
			{
				for (j = 0;j < f; j++)
				{
					if (i != q && j != p)
					{
						b[m][n] = num[i][j];
						if (n < (f - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
		}
	}
	return (transpose(num, fac, f));
}
 
 
///function to find the transpose of a matrix
float ** transpose(int **num, float **fac, int r)
{
	int i, j;
	int **b;
	float **inverse;
	float d;

	b = malloc(sizeof(int *) * r);
	for (int i = 0; i < r; i++)
		b[i] = malloc(sizeof(int) * r);
	
	inverse = malloc(sizeof(float *) * r);
	for (int i = 0; i < r; i++)
		inverse[i] = malloc(sizeof(float) * r);
	for (i = 0;i < r; i++)
		for (j = 0;j < r; j++)
			b[i][j] = fac[j][i];

	d = determinant(num, r);
	for (i = 0;i < r; i++)
		for (j = 0;j < r; j++)
			inverse[i][j] = b[i][j] / d;

	return inverse;
}
