#include<stdio.h>
#define MAXSize 5
//二维数组可以转为一维，可以按行存，也可以按列存
// 对称矩阵
// 下三角矩阵按行存
bool UnderRow(int a[MAXSize][MAXSize],int result[]){
    //判断是否对称
for (int i =0 ; i < MAXSize; i++)
{
    for (int j=0; j < i; j++)
    {
        if(a[i][j]!=a[j][i]){
            return false;
        }
    }
    
}
    //按行存
    for (int i = 0; i < MAXSize; i++)
    {
        for (int j=0; j <= i; j++)
    {
        //二维数组和一维数组下标关系{(i(i-1)/2)+j-1}
        //下标从零开始要减一
        result[(i*(i-1))/2+j-1]=a[i][j];
    }
    }
    
    return true;
}
int main(){
    int a[MAXSize][MAXSize]={
        {1,2,3,4,5},
        {2,2,6,7,8},
        {3,6,3,9,10},
        {4,7,9,4,11},
        {5,8,10,11,5},
    };
    int result[((1+MAXSize)*MAXSize)/2]={};
    if (UnderRow(a,result))
    {
        printf("ok!");
    }else{
        printf("error!");
    }
    for (int i = 0; i < sizeof(result)/sizeof(result[0]); i++)
    {
        
        printf("[%d]",a[i]);
    }
    
    return 0;
}