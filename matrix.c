#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { // 행렬을 편리하게 매개변수로 넘기고 관리하기 위해, struct Matrix 정의
    int row;
    int col;
    int** matrix; // 변수로는 그 행렬의 row, col 데이터와, 실제 데이터를 동적할당하여 사용하기 위한 이중 포인터 변수 matrix를 가짐.
} Matrix;

Matrix create_matrix(int row, int col); // 행렬을 동적할당하여 생성하는 함수

void rand_data(Matrix temp); // 행렬의 데이터로 난수를 집어넣는 함수

int check_possible_calc1(Matrix temp1, Matrix temp2); // 행렬간 덧셈과 뺄셈이 가능한지 확인하는 함수 (가능할시 1, 아닐시 0 리턴)

int check_possible_calc2(Matrix temp1, Matrix temp2); // 행렬간 곱셈이 가능한지 확인하는 함수 (가능할시 1, 아닐시 0 리턴)

void print_matrix(Matrix temp); // 행렬 프린트 함수

Matrix addition_matrix(Matrix temp1, Matrix temp2); // 행렬 덧셈 함수

Matrix subtraction_matrix(Matrix temp1, Matrix temp2); // 행렬 뺄셈 함수

Matrix transpose_matrix(Matrix temp); // 입력받은 행렬의 전치행렬을 구해주는 함수

Matrix multiply_matrix(Matrix temp1, Matrix temp2); // 행렬 곱셈 함수

void free_matrix(Matrix temp); // 행렬 동적할당 해지 함수

int main()
{
    Matrix a; 
    Matrix b;
    
    int row, col;

    srand(time(NULL));

    // scanf로 행, 열 입력받은 후, matrix 생성 함수 호출

    printf("A 행렬의 행과 열 수를 입력하세요 : ");
    scanf("%d %d", &row, &col);
    a = create_matrix(row, col); 

    printf("B 행렬의 행과 열 수를 입력하세요 : ");
    scanf("%d %d", &row, &col);
    b = create_matrix(row, col); 

    // 난수 대입 함수 호출
    rand_data(a); 
    rand_data(b); 
    
    // A, B 행렬 프린트
    printf("------ A 행렬 ------\n");
    print_matrix(a); 
    printf("------ B 행렬 ------\n");
    print_matrix(b);

    // 덧셈, 뺄셈, A의 전치, 곱셈의 결과 행렬을 각각 구하고, 프린트
    Matrix addmat = addition_matrix(a,b);
    Matrix submat = subtraction_matrix(a,b);
    Matrix tranmat = transpose_matrix(a);
    Matrix multimat = multiply_matrix(a, b);

    printf("------ A + B 행렬 ------\n");
    print_matrix(addmat);
    printf("------ A - B 행렬 ------\n");
    print_matrix(submat);
    printf("------ A의 전치 행렬 ------\n");
    print_matrix(tranmat);
    printf("------ A * B 행렬 ------\n");
    print_matrix(multimat);

    // 모든 행렬 free
    free_matrix(a);
    free_matrix(b);
    free_matrix(addmat);
    free_matrix(submat);
    free_matrix(tranmat);
    free_matrix(multimat);

    printf("\n[----- [최상영]  [2022041062] -----]\n");

    return 0;
}


Matrix create_matrix(int row, int col) // 행과 열의 수를 입력받고, 행렬을 동적할당하여 생성한 뒤, 데이터로 난수를 대입하는 함수
{
    Matrix temp;
    int i, j;

    temp.row = row;
    temp.col = col;



    temp.matrix = (int**)malloc(sizeof(int*) * temp.row); // 행 수만큼 동적할당

    if (temp.matrix == NULL) // 할당 실패시
    {
        fprintf(stderr, "malloc 에러 발생!");
        exit(1);
    }

    for(i = 0; i < temp.row; i++)
    {
        temp.matrix[i] = (int*)malloc(sizeof(int) * temp.col); // 각 행에, 열 수만큼 동적할당

        if (temp.matrix[i] == NULL) // 할당 실패시
        {
        fprintf(stderr, "malloc 에러 발생!");
        exit(1);
        }
    }
    
    return temp;
}

void rand_data(Matrix temp) // 행렬의 데이터로 난수를 집어넣는 함수
{
    int i, j;
    for(i = 0; i < temp.row; i++)
    {
        for(j = 0; j < temp.col; j++)
        {
            temp.matrix[i][j] = rand() % 100; // 데이터는 100 미만의 난수로 설정
        }
    }

}

int check_possible_calc1(Matrix temp1, Matrix temp2) // 행렬간 덧셈과 뺄셈이 가능한지 확인하는 함수 (가능할시 1, 아닐시 0 리턴)
{
    if ((temp1.row == temp2.row) && (temp1.col == temp2.col)) // 행렬간 덧셈 혹은 뺄셈이 가능하려면, 두 행렬의 행과 열의 수가 일치해야 한다.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_possible_calc2(Matrix temp1, Matrix temp2) // 행렬간 곱셈이 가능한지 확인하는 함수 (가능할시 1, 아닐시 0 리턴)
{
    if (temp1.col == temp2.row) // 행렬간 곱셈이 가능하려면, 앞 행렬의 열의 수와, 뒷 행렬의 행의 수가 일치해야 한다.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_matrix(Matrix temp) // 행렬 프린트 함수
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

Matrix addition_matrix(Matrix temp1, Matrix temp2) // 행렬 덧셈 함수
{
    int i, j;

    if(!check_possible_calc1(temp1, temp2))
    {
        fprintf(stderr, "해당 행렬끼리는 덧셈이 불가능합니다.\n");
        exit(1);
    }
    else
    {
        Matrix result = create_matrix(temp1.row, temp1.col); // temp2의 row, col들 써도 상관없음.

        for(i = 0; i < result.row; i++) // 새로운 result 행렬을 만들어서, 합의 결과를 구함
        {
            for(j = 0; j < result.col; j++)
            {
                result.matrix[i][j] = temp1.matrix[i][j] + temp2.matrix[i][j];
            }
        }
        return result;
    }

}

Matrix subtraction_matrix(Matrix temp1, Matrix temp2) // 행렬 뺄셈 함수
{
    int i, j;

    if(!check_possible_calc1(temp1, temp2))
    {
        fprintf(stderr, "해당 행렬끼리는 뺄셈이 불가능합니다.\n");
        exit(1);
    }
    else
    {
        Matrix result = create_matrix(temp1.row, temp1.col); // temp2의 것들 써도 상관없음.

        for(i = 0; i < result.row; i++) // 새로운 result 행렬을 만들어서, 차의 결과를 구함
        {
            for(j = 0; j < result.col; j++)
            {
                result.matrix[i][j] = temp1.matrix[i][j] - temp2.matrix[i][j];
            }
        }
        return result;
    }

}

Matrix transpose_matrix(Matrix temp) // 입력받은 행렬의 전치행렬을 구해주는 함수
{
    int i, j;

    Matrix result = create_matrix(temp.col, temp.row); // 행, 열이 뒤집혀야 하므로, 반대로 작성

    for(i = 0; i < result.row; i++) // 새로운 result 행렬을 만들어서, 기존 행렬의 행과 열을 다루는 변수를 반대로 쓰는 방법을 통해 전치행렬을 만듬.
    {
        for(j = 0; j < result.col; j++)
        {
           result.matrix[i][j] = temp.matrix[j][i];
        }
    }
    return result;
}

Matrix multiply_matrix(Matrix temp1, Matrix temp2) // 행렬 곱셈 함수
{
    int i, j;
    int x; // x는 temp1의 열과, temp2의 행을 끝까지 돌기 위해 사용하는 변수.
    int sum = 0;

    if(!check_possible_calc2(temp1, temp2)) // 매개변수 순서 바뀌지 않도록 주의해야함.
    {
        fprintf(stderr, "해당 행렬끼리는 곱셈이 불가능합니다.\n");
        exit(1);
    }
    else
    {
        Matrix result = create_matrix(temp1.row, temp2.col); 

        for(i = 0; i < result.row; i++)
        {
            for(j = 0; j < result.col; j++) // 새로운 result 행렬을 만들어서, 행렬의 곱셈 규칙에 따라, 
            // 해당하는 원소 위치의 행 번호를 가진 앞 행렬의 원소들과 해당 원소 위치의 열 번호를 가진 뒷 행렬의 원소들을 각각 곱해서 더함.
            {
                for(x = 0; x < temp1.col; x++) // temp1.col 대신 temp2.row로 코드를 써도 됨. 
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

void free_matrix(Matrix temp) // 행렬 동적할당 해지 함수
{
    int i;

    for(i = 0; i < temp.row; i++)
    {
        free(temp.matrix[i]); // 각 행 프리
    }

    free(temp.matrix); // 전체 프리 완료
}