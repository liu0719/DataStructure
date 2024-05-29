#include<stdio.h>
#include<string.h>
#define MaxLen 10
typedef struct {
	char ch[MaxLen];
	int length;
}SString;
//求KMP的next数组
bool GetKmpNext(SString s, int next[]) {
	if (s.length == 0) {
		return false;
	}
	int p, q, n;
	next[1] = 0;
	for (int i = 2; i <= s.length; i++) {
		n = i;
		p = 2; q = 1;
		while (p < i) {
			if (s.ch[p] != s.ch[q]) {
				p++; n = i;
			}
			else {
				if (n == i) { n = p; }
				p++; q++;
			}
		}
		next[i] = i - n + 1;
	}
	return true;
}
void GetNext(SString s, int next[]) {
	next[1] = 0; // 规定
	// i: next数组的索引
	// i: next数组的索引0053
	// j: 模式串的索引
	int i = 1, j = 0;
	while (i < s.length) {
		if (j == 0 || s.ch[i] == s.ch[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
}
bool GetNextVal(int nextval[], int *next, SString s) {
	nextval[1] = 0;
	for (int i = 2; i <= s.length; i++)
	{
		if (s.ch[i] == s.ch[next[i]]) {
			nextval[i] = nextval[next[i]];
		}
		else {
			nextval[i] = next[i];
		}
	}
	return true;
}
//kmp匹配
int Index_Kmp(SString s, SString t, int next[]) {//next数组标志着遇见不相等时下一次j的匹配位置，i不动。
	int i = 1, j = 1;
	while (i <= s.length&& j <= t.length) {
		if (j == 0 || s.ch[i] == t.ch[j]) {
			i++; j++;
		}
		else {
			j = next[j];//根据next数组来移动
		}
	}
	if (j > t.length) {
		return i - t.length;
	}
	return 0;
}
int main() {
	SString s = { ' ','a','a','a','a','a','b' }; s.length = 6;
	int next[8];
	GetKmpNext(s, next);
	for (int i = 1; i <=6; i++)
	{
		printf("%d", next[i]);
	}
	printf("-------------");
	GetNext(s, next);
	for (int i = 1; i <= 6; i++)
	{
		printf("%d", next[i]);
	}
	printf("\n");
	int nextval[7] = {};
	GetNextVal(nextval, next, s);
		for (int i = 1; i <= 6; i++)
		{
			printf("%d", nextval[i]);
		}
	return 0;
}