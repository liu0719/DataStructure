#include<stdio.h>
#define MAXSize 5
//��ά�������תΪһά�����԰��д棬Ҳ���԰��д�
// �Գƾ���
// �����Ǿ����д�
bool UnderRow(int a[MAXSize][MAXSize], int result[]) {
    //�ж��Ƿ�Գ�
    for (int i = 0; i < MAXSize; i++)
    {
        //ֻ���ж����ǳ������Խ��ߵ���һ����
        for (int j = 0; j < i;j++)
        {
             if (a[i][j] != a[j][i]) {
                return false;
            }
        }
    }
    //������ָ�����ȵ�һά����
    //���д�,һ�д������һ��
    int index = 0;
    for (int i = 0; i < MAXSize; i++)
    {
        for (int j = 0;j <= i;j++){
           result[index++]=a[i][j] ;
        }
    }

    return true;
}
//�����ǰ��д�ӳ������������������������Ҫ���������±�����±�Ļ�����ô�б��׼Ҫ��һ��iҪ���i+1,j->j+1
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
//�Գ������Ǿ����д�
bool UnderCol(int a[MAXSize][MAXSize], int result[]) {
    int index = 0;
    for (int j = 0; j < MAXSize; j++) {
        //ע��i�Ǵ�j��ʼ��
        for (int i=j; i <MAXSize; i++){
            result[index++] = a[i][j];
        }
    }
    return true;
}
//�Գ������ǰ��д�ӳ��
bool GetValuesByNumCol(int b[], int i, int j, int& result) {
    if (i<1 || i>MAXSize || j<1 || j>MAXSize) {
        result = -1;
        return false;
    }
    //�����ĩ�(n+(n-i+2)),����������j-1)�����2�����ǵ�j��֮ǰ���е�Ԫ�ظ������ټ�����i-j��ʾ�ڵ�j��,���Ԫ�ص�λ�ã�
    //((MAXSize + (MAXSize - i + 2)) * (j - 1)) / 2 + (i - j),�±�Ϊ
    // ���ʽ�ӱ�ﵱǰ��ѯԪ���±��0��ʼ�������ǵڼ���Ԫ�أ�
    // ����±��Ǵ�1��ʼ��ô������Ҫ��һ
    //�����ǵ�����
    //012345  5���ǵ�����Ԫ��
    //123456  6���ǵ�����Ԫ�� 
    if (i >= j) {
        result = b[((MAXSize+(MAXSize-j+2))*(j-1))/2+(i-j)];
    }
    else {
        result = b[((MAXSize + (MAXSize - i + 2)) * (i - 1)) / 2 + (j - i)];
    }
    return true;
}

//���Ǿ��������Ǿ����д�
bool AnGleUnderCol(int a[MAXSize][MAXSize], int result[]) {
    int index = 0;
    for (int j = 0; j < MAXSize; j++) {
        //ע��i�Ǵ�j��ʼ��
        for (int i = j; i < MAXSize; i++) {
            result[index++] = a[i][j];
        }
        
        
    }
    //ȡ��һ����������Ԫ�ش���һγ����
    result[index] = a[0][MAXSize-1];
    return true;
}
//���Ǿ����д棬
bool AngleUnderRow(int a[MAXSize][MAXSize], int result[]) {
    //���д�,һ�д������һ��
    int index = 0;
    for (int i = 0; i < MAXSize; i++)
    {
        for (int j = 0; j <= i; j++) {
            result[index++] = a[i][j];
        }
    }
    //�����±���㿪ʼ������Ҫ��1
    result[index] = a[0][MAXSize-1];
    return true;
}
//���������ǰ��д�ӳ��
bool AnGleGetValuesByNumCol(int b[], int i, int j, int& result) {
    if (i<1 || i>MAXSize || j<1 || j>MAXSize) {
        result = -1;
        return false;
    }
    //�����ĩ�(n+(n-i+2)),����������j-1)�����2�����ǵ�j��֮ǰ���е�Ԫ�ظ������ټ�����i-j��ʾ�ڵ�j��,���Ԫ�ص�λ�ã�
    //((MAXSize + (MAXSize - i + 2)) * (j - 1)) / 2 + (i - j),�±�Ϊ
    // ���ʽ�ӱ�ﵱǰ��ѯԪ���±��0��ʼ�������ǵڼ���Ԫ�أ�
    // ����±��Ǵ�1��ʼ��ô������Ҫ��һ
    //�����ǵ�����
    //012345  5���ǵ�����Ԫ��
    //123456  6���ǵ�����Ԫ�� 
    if (i >= j) {
        result = b[((MAXSize + (MAXSize - j + 2)) * (j - 1)) / 2 + (i - j)];
    }
    else {
        result = b[((1+MAXSize)*MAXSize)/2];
    }
    return true;
}
//�����ǰ��д�ӳ������������������������Ҫ���������±�����±�Ļ�����ô�б��׼Ҫ��һ��iҪ���i+1,j->j+1
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
    printf("\n��ѯ\n");
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