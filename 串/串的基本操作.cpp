#include<stdio.h>
#define MaxLen 255
typedef struct  {
	char ch[MaxLen];
	int length;
}SString;
//��ȡ�Ӵ�
bool SubString(SString &sub,SString s,int pos,int len) {
	sub.length = 0;
	//��ȡ�������鷶Χ
	if (pos + len > s.length+1) {
		return false;
	}
	//0��������Ҫ��1��ʼ������len+pos �����һ��ʼ����ȡ6����1+6=7��i��1��ʼ,����ѭ��6��
	for (int  i = pos; i < pos+len; i++)
	{
		//����sub�У�����++
		sub.ch[i - pos + 1] = s.ch[i];
		sub.length++;
	}
	return true;
}
//��ӡ
bool PrintString(SString s) {
	for (int i = 1; i < s.length+1; i++)
	{
		printf("%c", s.ch[i]);
	}
	printf("\n");
	return true;
}
//�Ƚ�
int ComPare(SString& s1, SString& s2) {//����򷵻�0��s1>s2�ͷ���>0,s1<s2�ͷ���<0
	for (int  i = 1; i <= s1.length&&s2.length; i++)
	{
		if (s1.ch[i] != s2.ch[i]) {
			return s1.ch[i] - s2.ch[i];
		}
	}
	return s1.length - s2.length;
}
//�����Ӵ���ʹ�û���������
int IndexBase(SString &s,SString &t) {
	SString sub;//��ʱ����Ӵ�
	for (int i = 1; i <= s.length-t.length+1; i++)
	{
		//���ν�ȡ�������㷨˼��
		SubString(sub, s, i, t.length);
		if (ComPare(sub, t) == 0) {
			return i;
		}
	}
	return 0;
}
//�����Ӵ�
//int Index(SString s, SString t) {
//	//����������ָ�룬����ɨ��s��t��ʱ�临�Ӷ�ΪO(nm)
//	int i = 1, j = 1;
//	//��i��������ڳ��ȴ���,û��ƥ�䵽����j
//	for (i,j;
//		i <= s.length - t.length + 1 &&j<=t.length;
//		i++,j++)
//	{
//		if (s.ch[i] != t.ch[j]) {
//			i = i - j + 2;
//			j = 0;
//		}
//	}
//	if (j >= t.length) {
//		return i - t.length;
//	}
//	return 0;
//}
int Index(SString s, SString t) {
	//����������ָ�룬����ɨ��s��t��ʱ�临�Ӷ�ΪO(nm)
	int i = 1, j = 1;
	//��i��������ڳ��ȴ���,û��ƥ�䵽����j
	while(i <= s.length - t.length + 1 && j <= t.length)
	{
		if (s.ch[i] != t.ch[j]) {
			i = i - j + 2;
			j = 1;
		}
		else {
			i++; j++;
		}
	}
	if (j > t.length) {
		return i - t.length;
	}
	return 0;
}
//int main() {
//	SString s{};
//	//0�±걻�������ã�Ҫ��1��ʼ���Լ�1
//	for (int i = 97; i < 123; i++)
//	{
//		s.ch[i-97+1] = i;
//	}
//	s.length = 26;
//	PrintString(s);
//	SString sub{};
//	sub.length = 0;
//	SubString(sub, s, 8, 1);
//	PrintString(sub);
//	int index = Index(s, sub);
//	printf("���ҵ��ַ����������е�λ�ã�%d", index);
//	return 0;
//}