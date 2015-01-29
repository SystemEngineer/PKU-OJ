#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lcs(int* seq, int len)
{
    int* state;
    state = malloc(len*sizeof(int));
    if(!state){
        return 0;
    }
    memset(state, 0, len*sizeof(int));
    int lcs_of_row = seq[0];
    state[0] = seq[0];
    for(int i = 1; i < len; i++){
        if(state[i-1] < 0){
            state[i] = seq[i];
        }else{
            state[i] = state[i-1] + seq[i];
        }
        if(state[i] > lcs_of_row){
            lcs_of_row = state[i];
        }
    }
    return lcs_of_row;
}

int main()
{ 
    int dimention;
    char** input;
    int* sum_of_col;
    int temp_sum,max_sum;
    int i,j,row,col;
    max_sum = 0;

    scanf("%d",&dimention);
    input = (char**)malloc(dimention*sizeof(char*));
    sum_of_col = (int*)malloc(dimention*sizeof(int));
    if((!input)||(!sum_of_col)){
        return -1;
    }
    for(i = 0; i < dimention; i++){
        input[i] = (char*)malloc(dimention*sizeof(char));
        if(!input[i]){
            return -1;
        }
    }
    
    memset(sum_of_col, 0, dimention*sizeof(int));
    for(i = 0; i < dimention; i++){
        for(j = 0; j < dimention; j++)
        scanf("%d", &input[i][j]);
    }

    for(i = 0; i < dimention; i++){
        for(j = dimention - 1; j >= i; j--){
            //Make the sum of each row
            memset(sum_of_col, 0, dimention*sizeof(int));
            for(col = 0; col < dimention; col++){
                for(row = i; row <= j; row++){
                    sum_of_col[col] += input[row][col];
                }
            }
            //Get the LCS
            temp_sum = lcs(sum_of_col,dimention);
            if(temp_sum > max_sum){
                max_sum = temp_sum;
            }
        }
    }
    printf("%d\n",max_sum);
}