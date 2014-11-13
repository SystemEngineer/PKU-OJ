/*
1001 Exponentiation
Description
Problems involving the computation of exact values of very large magnitude and precision are common. For example, the computation of the national debt is a taxing experience for many computer systems. 
This problem requires that you write a program to compute the exact value of Rn where R is a real number ( 0.0 < R < 99.999 ) and n is an integer such that 0 < n <= 25.
Input
The input will consist of a set of pairs of values for R and n. The R value will occupy columns 1 through 6, and the n value will be in columns 8 and 9.
Output
The output will consist of one line for each line of input giving the exact value of R^n. Leading zeros should be suppressed in the output. Insignificant trailing zeros must not be printed. Don't print the decimal point if the result is an integer.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 200
#define MAX_INPUT_LINES 200

int char2int(char* a)
{
    if(*a >= 48){
        return *a - 48;
    }else{
        return *a;
    }
}

//Calculate m2 = m1*m2
void multi(char* m1, char* m2, int len1, int *len2)
{
    int tmp[MAX_STR_LEN] = {0};
    int i,j,m1_value,m2_value;
    
    //1.for each character, calc multi result
    for(i = 0; i < len1; i++){
        for(j = 0; j < *len2; j++){
            m1_value = char2int(m1+i);
            m2_value = char2int(m2+j);
            //printf("%d,%d\n",m1[i],m2[j]);
            tmp[i+j] += m1_value*m2_value; 
        }
    }
    //2.for each character in result, calc carry
    int carry = 0;
    for(i = 0; i < len1+*len2; i++){
        tmp[i] += carry;
        carry = tmp[i] / 10;
        tmp[i] = tmp[i] % 10;
        //3.put result into m2
        m2[i] = tmp[i] + 48;
    }
    for(j = len1 + *len2 -1; j > 0; j--){
        if(m2[j] != 48){
            *len2 = j + 1;
            break;
        }
    }
    return;
}

int main()
{
    char input[MAX_STR_LEN]={0};
    char* tmp_result;
    int power,i,j,len;
    int dec_point = 0;
    int lines = 0;
    char* result[MAX_INPUT_LINES];
    
    while(scanf("%s%d",input,&power) != EOF){
        //Malloc the result array
        result[lines] = malloc(MAX_STR_LEN);
        tmp_result = result[lines];
        memset(tmp_result,0,MAX_STR_LEN);
        len = strlen(input);
        j = 0;
        i = 0;
        if(power == 0){
             tmp_result[0] = '1';
             tmp_result[1] = '\0';
             lines++;
             continue;
         }
         if(power == 1){
            strncpy(tmp_result,input,MAX_STR_LEN);
            for(i = 0; i < strlen(tmp_result); i++){
                if(tmp_result[i] != 48){
                    break;
                }
            }
            tmp_result += i;
            result[lines] = tmp_result;
            for(i = strlen(tmp_result)-1; i >= 0; i--){
                if(tmp_result[i] == 48){
                    tmp_result[i] = '\0';
                }else{
                    break;
                }
            }
            if((1 == strlen(tmp_result))&&(tmp_result[0] == '.'))
                tmp_result[0] = '0';
            if(tmp_result[strlen(tmp_result)-1] == '.')
                tmp_result[strlen(tmp_result)-1] = '\0';
            lines++;
            continue;
        }
        lines++;
        //find dec point and remove it
        for(i = 0; i <= len; i++){
            if(input[i] != '.'){
                input[j] = input[i];
                j++;
            }
            else{
                //write down the dec point position
                dec_point = len - 1 - i;
            }
        }
        //dec point is removed, so str len should be decrease by 1
        len--;
        //printf("input is %s, dec point is %d\n",input,dec_point);
    
        char tmp;
        //Reverse the input str and send to multi
        for(i = 0; i < len/2; i++){
            tmp = input[i];
            input[i] = input[len-i-1];
            input[len-i-1] = tmp;
        }
        strncpy(tmp_result,input,MAX_STR_LEN);
        for(i = 1; i < power; i++){
            multi(input,tmp_result,strlen(input),&len);
        }
        //Add dec point to result
        j = 0;
        i = 0;
        int dec_pos = dec_point * power;
        for(i = dec_pos; i >= len; i--){
            if(tmp_result[i] < 48)
                tmp_result[i] += 48;
        }
        for(i = len; i > dec_pos; i--){
            tmp_result[i] = tmp_result[i-1];
        }
        tmp_result[dec_pos] = 46;
        len = len > dec_pos ? len : dec_pos; 
        len++;  //There is an additional '.'
        for(i = 0; i < len/2; i++){
            tmp = tmp_result[i];
            tmp_result[i] = tmp_result[len-i-1];
            tmp_result[len-i-1] = tmp;
        }
        //Remove zeroes at tail
        tmp_result[len] = '\0';
        if(dec_pos > 0){
            for(i = len - 1; i >=0; i--){
                if((tmp_result[i] != 48)&&(tmp_result[i] != 0)){
                    break;
                }else{
                    tmp_result[i] = '\0';
                }
            }
            if(tmp_result[i] == 46){
                tmp_result[i] = '\0';
            }
        }
        if(dec_pos == 0){
            //no fraction, remove the last '.'
            tmp_result[len-1] = '\0';
        }
    }//End while
    for(i = 0; i < lines; i++){
        printf("%s\n",result[i]);
    }
    
    return 0;
}
