#include<stdio.h>
#define MaxLen 255
typedef struct  {
	char ch[MaxLen];
	int length;
}SString;
//截取子串
bool SubString(SString &sub,SString s,int pos,int len) {
	sub.length = 0;
	//截取超过数组范围
	if (pos + len > s.length+1) {
		return false;
	}
	//0被废弃，要从1开始，所以len+pos 比如从一开始，截取6个，1+6=7，i从1开始,正好循环6次
	for (int  i = pos; i < pos+len; i++)
	{
		//存入sub中，长度++
		sub.ch[i - pos + 1] = s.ch[i];
		sub.length++;
	}
	return true;
}
//打印
bool PrintString(SString s) {
	for (int i = 1; i < s.length+1; i++)
	{
		printf("%c", s.ch[i]);
	}
	printf("\n");
	return true;
}
//比较
int ComPare(SString& s1, SString& s2) {//相等则返回0，s1>s2就返回>0,s1<s2就返回<0
	for (int  i = 1; i <= s1.length&&s2.length; i++)
	{
		if (s1.ch[i] != s2.ch[i]) {
			return s1.ch[i] - s2.ch[i];
		}
	}
	return s1.length - s2.length;
}
//查找子串（使用基本操作）
int IndexBase(SString &s,SString &t) {
	SString sub;//临时存放子串
	for (int i = 1; i <= s.length-t.length+1; i++)
	{
		//依次截取，朴素算法思想
		SubString(sub, s, i, t.length);
		if (ComPare(sub, t) == 0) {
			return i;
		}
	}
	return 0;
}
//查找子串
//int Index(SString s, SString t) {
//	//定义两个类指针，用来扫描s和t，时间复杂度为O(nm)
//	int i = 1, j = 1;
//	//当i超出或等于长度代表,没有匹配到，当j
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
	//定义两个类指针，用来扫描s和t，时间复杂度为O(nm)
	int i = 1, j = 1;
	//当i超出或等于长度代表,没有匹配到，当j
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
//	//0下标被废弃不用，要在1开始所以加1
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
//	printf("查找的字符串在索引中的位置：%d", index);
//	return 0;
//}