#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int* ptr;
int *temp,*count;
/*
 *
 */
typedef struct
{
    int dim;
    int* data;
} UpperTriangularMatrix;
/*
 * initUpperTriangularMatrix
 *        - creates a new matrix
 *        - initializes the matrix by allocating enough memory
 */
UpperTriangularMatrix initUpperTriangularMatrix(int dim)
{
    int size=((dim+1)*dim)/2;
    UpperTriangularMatrix mat;
    mat.dim=dim;
    mat.data=(int*)malloc(size*sizeof(int));
    return mat;
}
/*
 * destroyUpperTriangularMatrix
 *        - frees the allocated memory
 *        - set dim to zero
 */
void destroyUpperTriangularMatrix(UpperTriangularMatrix *mat)
{
    free (mat->data);
    mat->dim=0;
}
/*
 * get: returns the item at mat[row][col]
 */
int get(UpperTriangularMatrix mat, int row, int col)
{
    int n=0;
    if (row>col)
    {
        return n;
    }
    else
    {
        if(row==0&&col==0)
        {
            count=temp;
        }
        else
        {
            // mat.data++;
            count++;
        }
        mat.data=count;
        n=*mat.data;
        return n;
    }

    //retrun -1;
}
/*
 * set: assigns mat[row][col] to val
 */
int set(UpperTriangularMatrix mat, int row, int col, int val)
{
    assert(row<=col || val==0);
    //for removing error
    if(row==0&&col==0)
    {
        count=temp;
    }
    else
    {
        count++;
        //mat.data++;
    }
    mat.data=count;
    *mat.data=val;
    return 0;
}
/*
 * addTriangularMatrices:
 *            sum = mat1 + mat2;
 */
UpperTriangularMatrix addTriangularMatrices(UpperTriangularMatrix mat1, UpperTriangularMatrix mat2)
{
    assert(mat1.dim == mat2.dim);
    UpperTriangularMatrix sum;
    sum.dim=mat1.dim;
    //initUpperTriangularMatrix(sum.dim);
    temp=sum.data;
    count=sum.data;
    for (int i=0; i<sum.dim; i++)
    {
        for (int j=0; j<sum.dim; j++)
        {
            *sum.data= *mat1.data + *mat2.data;
            sum.data++;
            mat1.data++;
            mat2.data++;
        }
    }
    return sum;
}
/*
 * convertFileToUpperTriangularMatrix
 *            assumes file format as follows:
 *            - first line contains dimensions
 *            - each row in a line
 *            - each row contains elements in the upper triangle only, space separated
 */
UpperTriangularMatrix convertFileToUpperTriangularMatrix(char* filename)
{
    UpperTriangularMatrix mat;
    int dim, val;
    int i, j;
    char line[512], *token;

    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);

    fscanf(fp, "%d\n", &dim);
    mat = initUpperTriangularMatrix(dim);
    for(i=0; i<mat.dim; i++)
        for(j=i; j<mat.dim; j++)
        {
            fscanf(fp, "%d", &val);
            set(mat, i, j, val);
        }

    fclose(fp);
    return mat;
}
/*
 *
 */
void printMatrix(char* title, UpperTriangularMatrix mat)
{
    int i, j;

    printf("%s\n", title);

    for(i=0; i<mat.dim; i++)
    {
        for(j=0; j<mat.dim; j++)
            printf("%5d  ", get(mat, i, j));
        printf("\n");
    }

    printf("...................................................\n");
}
/*
 *
 */
int main(int argc, char**argv)
{
    if(argc!=3)
    {
        printf("Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }

    UpperTriangularMatrix matA = convertFileToUpperTriangularMatrix(argv[1]);
    printMatrix("Matrix A\n========", matA);
    UpperTriangularMatrix matB = convertFileToUpperTriangularMatrix(argv[2]);
    printMatrix("Matrix B\n========", matB);

    UpperTriangularMatrix matC = addTriangularMatrices(matA, matB);
    printMatrix("Matrix C = A + B\n================", matC);

    destroyUpperTriangularMatrix(&matA);
    printMatrix("Matrix A (after destroy)\n========================", matA);
    destroyUpperTriangularMatrix(&matB);
    printMatrix("Matrix B (after destroy)\n========================", matB);
    destroyUpperTriangularMatrix(&matC);
    printMatrix("Matrix C (after destroy)\n========================", matC);

    return 0;
}
