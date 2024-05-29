#include<stdio.h>
#define MAXSize 5
//二维数组可以转为一维，可以按行存，也可以按列存
// 对称矩阵
// 下三角矩阵按行存
bool UnderRow(int a[MAXSize][MAXSize], int result[]) {
    //判断是否对称
    for (int i = 0; i < MAXSize; i++)
    {
        //只会判断三角除了主对角线的另一部分
        for (int j = 0; j < i;j++)
        {
             if (a[i][j] != a[j][i]) {
                return false;
            }
        }
    }
    //创建好指定长度的一维数组
    //按行存,一行存完存另一行
    int index = 0;
    for (int i = 0; i < MAXSize; i++)
    {
        for (int j = 0;j <= i;j++){
           result[index++]=a[i][j] ;
        }
    }

    return true;
}
//下三角按行存映射输入的是列数和行数，如果要是输入行下标和列下标的话，那么判别标准要减一，i要变成i+1,j->j+1
bool GetValuesByNum(int b[],int i,int j,int &result) {
    if (i<1 || i>MAXSize || j<1 || j>MAXSize) {
        result = -1;
        return false;
    }
    if (i >= j) {
        result = b[(i*(i - 1))/2+j- 1];
    }
    else {
        result = b[(j * (j - 1)) / 2 + i - 1];
    }
    return true;
}
//对称下三角矩阵按列存
bool UnderCol(int a[MAXSize][MAXSize], int result[]) {
    int index = 0;
    for (int j = 0; j < MAXSize; j++) {
        //注意i是从j开始的
        for (int i=j; i <MAXSize; i++){
            result[index++] = a[i][j];
        }
    }
    return true;
}
//对称下三角按列存映射
bool GetValuesByNumCol(int b[], int i, int j, int& result) {
    if (i<1 || i>MAXSize || j<1 || j>MAXSize) {
        result = -1;
        return false;
    }
    //首项加末项，(n+(n-i+2)),乘以项数（j-1)项，除以2，这是第j列之前所有的元素个数，再加上用i-j表示在第j列,这个元素的位置，
    //((MAXSize + (MAXSize - i + 2)) * (j - 1)) / 2 + (i - j),下表为
    // 这个式子表达当前查询元素下标从0开始的数列是第几个元素，
    // 如果下标是从1开始那么后面需要加一
    //假设是第六个
    //012345  5就是第六个元素
    //123456  6才是第六个元素 
    if (i >= j) {
        result = b[((MAXSize+(MAXSize-j+2))*(j-1))/2+(i-j)];
    }
    else {
        result = b[((MAXSize + (MAXSize - i + 2)) * (i - 1)) / 2 + (j - i)];
    }
    return true;
}

//三角矩阵下三角矩阵按列存
bool AnGleUnderCol(int a[MAXSize][MAXSize], int result[]) {
    int index = 0;
    for (int j = 0; j < MAXSize; j++) {
        //注意i是从j开始的
        for (int i = j; i < MAXSize; i++) {
            result[index++] = a[i][j];
        }
        
        
    }
    //取另一部分最角里的元素存入一纬数组
    result[index] = a[0][MAXSize-1];
    return true;
}
//三角矩阵按行存，
bool AngleUnderRow(int a[MAXSize][MAXSize], int result[]) {
    //按行存,一行存完存另一行
    int index = 0;
    for (int i = 0; i < MAXSize; i++)
    {
        for (int j = 0; j <= i; j++) {
            result[index++] = a[i][j];
        }
    }
    //矩阵下标从零开始，所以要加1
    result[index] = a[0][MAXSize-1];
    return true;
}
//三角下三角按列存映射
bool AnGleGetValuesByNumCol(int b[], int i, int j, int& result) {
    if (i<1 || i>MAXSize || j<1 || j>MAXSize) {
        result = -1;
        return false;
    }
    //首项加末项，(n+(n-i+2)),乘以项数（j-1)项，除以2，这是第j列之前所有的元素个数，再加上用i-j表示在第j列,这个元素的位置，
    //((MAXSize + (MAXSize - i + 2)) * (j - 1)) / 2 + (i - j),下表为
    // 这个式子表达当前查询元素下标从0开始的数列是第几个元素，
    // 如果下标是从1开始那么后面需要加一
    //假设是第六个
    //012345  5就是第六个元素
    //123456  6才是第六个元素 
    if (i >= j) {
        result = b[((MAXSize + (MAXSize - j + 2)) * (j - 1)) / 2 + (i - j)];
    }
    else {
        result = b[((1+MAXSize)*MAXSize)/2];
    }
    return true;
}
//下三角按行存映射输入的是列数和行数，如果要是输入行下标和列下标的话，那么判别标准要减一，i要变成i+1,j->j+1
bool AngleGetValuesByNumRow(int b[], int i, int j, int& result) {
    if (i<1 || i>MAXSize || j<1 || j>MAXSize) {
        result = -1;
        return false;
    }
    if (i >= j) {
        result = b[(i * (i - 1)) / 2 + j - 1];
    }
    else {
        result = b[((1+MAXSize)*MAXSize)/2];
    }
    return true;
}
int main() {
    int a[MAXSize][MAXSize] = {
        {1,2,3,4,5},
        {2,2,6,7,8},
        {3,6,3,9,10},
        {4,7,9,4,11},
        {5,8,10,11,5},
    };
    int result[100] = {};
    bool err=UnderRow(a, result);
    if (err)
    {
        printf("ok!\n");
    }
    else {
        printf("error!\n");
    }
    for (int i = 0; i < ((1 + MAXSize) * MAXSize) / 2; i++)
    {

        printf("[%d]", result[i]);
    }
    printf("\n查询\n");
    int num = 0;
    err=GetValuesByNum(result, 4, 3, num);
    if (err) {
        printf("%d\n",num);
    }
    else {
        printf("error!\n");
    }
     err = UnderCol(a, result);
    if (err)
    {
        printf("ok!\n");
    }
    else {
        printf("error!\n");
    }
    for (int i = 0; i < ((1 + MAXSize) * MAXSize) / 2; i++)
    {

        printf("[%d]", result[i]);
    }
    printf("\n");
    err = GetValuesByNumCol(result, 2, 3, num);
    if (err) {
        printf("%d\n", num);
    }
    else {
        printf("error!\n");
    }
    int b[MAXSize][MAXSize] = {
        {1,0,0,0,99},
        {2,2,0,0,0},
        {3,6,3,0,0},
        {4,7,9,4,0},
        {5,8,10,11,5},
    };
    AngleUnderRow(b, result);
      for (int i = 0; i < ((1 + MAXSize) * MAXSize) / 2+1; i++)
      {
          printf("[%d]", result[i]);
      }
      printf("\n");
      AngleGetValuesByNumRow(result, 5, 3, num);
      if (err) {
          printf("\n%d\n", num);
      }
      else {
          printf("error!\n");
      }
      AnGleUnderCol(b, result);
      for (int i = 0; i < ((1 + MAXSize) * MAXSize) / 2 + 1; i++)
      {

          printf("[%d]", result[i]);
      }
      AnGleGetValuesByNumCol(result, 5, 3, num);
      if (err) {
          printf("\n%d\n", num);
      }
      else {
          printf("error!\n");
      }
    return 0;
}