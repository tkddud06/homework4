#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { // ����� ���ϰ� �Ű������� �ѱ�� �����ϱ� ����, struct Matrix ����
    int row;
    int col;
    int** matrix; // �����δ� �� ����� row, col �����Ϳ�, ���� �����͸� �����Ҵ��Ͽ� ����ϱ� ���� ���� ������ ���� matrix�� ����.
} Matrix;

Matrix create_matrix(int row, int col); // ����� �����Ҵ��Ͽ� �����ϴ� �Լ�

void rand_data(Matrix temp); // ����� �����ͷ� ������ ����ִ� �Լ�

int check_possible_calc1(Matrix temp1, Matrix temp2); // ��İ� ������ ������ �������� Ȯ���ϴ� �Լ� (�����ҽ� 1, �ƴҽ� 0 ����)

int check_possible_calc2(Matrix temp1, Matrix temp2); // ��İ� ������ �������� Ȯ���ϴ� �Լ� (�����ҽ� 1, �ƴҽ� 0 ����)

void print_matrix(Matrix temp); // ��� ����Ʈ �Լ�

Matrix addition_matrix(Matrix temp1, Matrix temp2); // ��� ���� �Լ�

Matrix subtraction_matrix(Matrix temp1, Matrix temp2); // ��� ���� �Լ�

Matrix transpose_matrix(Matrix temp); // �Է¹��� ����� ��ġ����� �����ִ� �Լ�

Matrix multiply_matrix(Matrix temp1, Matrix temp2); // ��� ���� �Լ�

void free_matrix(Matrix temp); // ��� �����Ҵ� ���� �Լ�

int main()
{
    Matrix a; 
    Matrix b;
    
    int row, col;

    srand(time(NULL));

    // scanf�� ��, �� �Է¹��� ��, matrix ���� �Լ� ȣ��

    printf("A ����� ��� �� ���� �Է��ϼ��� : ");
    scanf("%d %d", &row, &col);
    a = create_matrix(row, col); 

    printf("B ����� ��� �� ���� �Է��ϼ��� : ");
    scanf("%d %d", &row, &col);
    b = create_matrix(row, col); 

    // ���� ���� �Լ� ȣ��
    rand_data(a); 
    rand_data(b); 
    
    // A, B ��� ����Ʈ
    printf("------ A ��� ------\n");
    print_matrix(a); 
    printf("------ B ��� ------\n");
    print_matrix(b);

    // ����, ����, A�� ��ġ, ������ ��� ����� ���� ���ϰ�, ����Ʈ
    Matrix addmat = addition_matrix(a,b);
    Matrix submat = subtraction_matrix(a,b);
    Matrix tranmat = transpose_matrix(a);
    Matrix multimat = multiply_matrix(a, b);

    printf("------ A + B ��� ------\n");
    print_matrix(addmat);
    printf("------ A - B ��� ------\n");
    print_matrix(submat);
    printf("------ A�� ��ġ ��� ------\n");
    print_matrix(tranmat);
    printf("------ A * B ��� ------\n");
    print_matrix(multimat);

    // ��� ��� free
    free_matrix(a);
    free_matrix(b);
    free_matrix(addmat);
    free_matrix(submat);
    free_matrix(tranmat);
    free_matrix(multimat);

    printf("\n[----- [�ֻ�]  [2022041062] -----]\n");

    return 0;
}


Matrix create_matrix(int row, int col) // ��� ���� ���� �Է¹ް�, ����� �����Ҵ��Ͽ� ������ ��, �����ͷ� ������ �����ϴ� �Լ�
{
    Matrix temp;
    int i, j;

    temp.row = row;
    temp.col = col;



    temp.matrix = (int**)malloc(sizeof(int*) * temp.row); // �� ����ŭ �����Ҵ�

    if (temp.matrix == NULL) // �Ҵ� ���н�
    {
        fprintf(stderr, "malloc ���� �߻�!");
        exit(1);
    }

    for(i = 0; i < temp.row; i++)
    {
        temp.matrix[i] = (int*)malloc(sizeof(int) * temp.col); // �� �࿡, �� ����ŭ �����Ҵ�

        if (temp.matrix[i] == NULL) // �Ҵ� ���н�
        {
        fprintf(stderr, "malloc ���� �߻�!");
        exit(1);
        }
    }
    
    return temp;
}

void rand_data(Matrix temp) // ����� �����ͷ� ������ ����ִ� �Լ�
{
    int i, j;
    for(i = 0; i < temp.row; i++)
    {
        for(j = 0; j < temp.col; j++)
        {
            temp.matrix[i][j] = rand() % 100; // �����ʹ� 100 �̸��� ������ ����
        }
    }

}

int check_possible_calc1(Matrix temp1, Matrix temp2) // ��İ� ������ ������ �������� Ȯ���ϴ� �Լ� (�����ҽ� 1, �ƴҽ� 0 ����)
{
    if ((temp1.row == temp2.row) && (temp1.col == temp2.col)) // ��İ� ���� Ȥ�� ������ �����Ϸ���, �� ����� ��� ���� ���� ��ġ�ؾ� �Ѵ�.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_possible_calc2(Matrix temp1, Matrix temp2) // ��İ� ������ �������� Ȯ���ϴ� �Լ� (�����ҽ� 1, �ƴҽ� 0 ����)
{
    if (temp1.col == temp2.row) // ��İ� ������ �����Ϸ���, �� ����� ���� ����, �� ����� ���� ���� ��ġ�ؾ� �Ѵ�.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_matrix(Matrix temp) // ��� ����Ʈ �Լ�
{
    int i, j;
    for(i = 0; i < temp.row; i++)
    {
        for(j = 0; j < temp.col; j++)
        {
            printf("%d ", temp.matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Matrix addition_matrix(Matrix temp1, Matrix temp2) // ��� ���� �Լ�
{
    int i, j;

    if(!check_possible_calc1(temp1, temp2))
    {
        fprintf(stderr, "�ش� ��ĳ����� ������ �Ұ����մϴ�.\n");
        exit(1);
    }
    else
    {
        Matrix result = create_matrix(temp1.row, temp1.col); // temp2�� row, col�� �ᵵ �������.

        for(i = 0; i < result.row; i++) // ���ο� result ����� ����, ���� ����� ����
        {
            for(j = 0; j < result.col; j++)
            {
                result.matrix[i][j] = temp1.matrix[i][j] + temp2.matrix[i][j];
            }
        }
        return result;
    }

}

Matrix subtraction_matrix(Matrix temp1, Matrix temp2) // ��� ���� �Լ�
{
    int i, j;

    if(!check_possible_calc1(temp1, temp2))
    {
        fprintf(stderr, "�ش� ��ĳ����� ������ �Ұ����մϴ�.\n");
        exit(1);
    }
    else
    {
        Matrix result = create_matrix(temp1.row, temp1.col); // temp2�� �͵� �ᵵ �������.

        for(i = 0; i < result.row; i++) // ���ο� result ����� ����, ���� ����� ����
        {
            for(j = 0; j < result.col; j++)
            {
                result.matrix[i][j] = temp1.matrix[i][j] - temp2.matrix[i][j];
            }
        }
        return result;
    }

}

Matrix transpose_matrix(Matrix temp) // �Է¹��� ����� ��ġ����� �����ִ� �Լ�
{
    int i, j;

    Matrix result = create_matrix(temp.col, temp.row); // ��, ���� �������� �ϹǷ�, �ݴ�� �ۼ�

    for(i = 0; i < result.row; i++) // ���ο� result ����� ����, ���� ����� ��� ���� �ٷ�� ������ �ݴ�� ���� ����� ���� ��ġ����� ����.
    {
        for(j = 0; j < result.col; j++)
        {
           result.matrix[i][j] = temp.matrix[j][i];
        }
    }
    return result;
}

Matrix multiply_matrix(Matrix temp1, Matrix temp2) // ��� ���� �Լ�
{
    int i, j;
    int x; // x�� temp1�� ����, temp2�� ���� ������ ���� ���� ����ϴ� ����.
    int sum = 0;

    if(!check_possible_calc2(temp1, temp2)) // �Ű����� ���� �ٲ��� �ʵ��� �����ؾ���.
    {
        fprintf(stderr, "�ش� ��ĳ����� ������ �Ұ����մϴ�.\n");
        exit(1);
    }
    else
    {
        Matrix result = create_matrix(temp1.row, temp2.col); 

        for(i = 0; i < result.row; i++)
        {
            for(j = 0; j < result.col; j++) // ���ο� result ����� ����, ����� ���� ��Ģ�� ����, 
            // �ش��ϴ� ���� ��ġ�� �� ��ȣ�� ���� �� ����� ���ҵ�� �ش� ���� ��ġ�� �� ��ȣ�� ���� �� ����� ���ҵ��� ���� ���ؼ� ����.
            {
                for(x = 0; x < temp1.col; x++) // temp1.col ��� temp2.row�� �ڵ带 �ᵵ ��. 
                {
                    sum += temp1.matrix[i][x] * temp2.matrix[x][j]; 
                }
                result.matrix[i][j] = sum;
                sum = 0;
            }
        }
        return result;
    }

}

void free_matrix(Matrix temp) // ��� �����Ҵ� ���� �Լ�
{
    int i;

    for(i = 0; i < temp.row; i++)
    {
        free(temp.matrix[i]); // �� �� ����
    }

    free(temp.matrix); // ��ü ���� �Ϸ�
}