//字符串匹配

#include<iostream>
#include<cstring>

//前置所需函数

//字符串长度计算
int strlenth(char a[])
{
	char ch = a[0];
	int count = 0;
	while (ch != '\0')
	{
		count++;
		ch = a[count];
	}
	return count;
}

//暴力算法 时间复杂度O（m*n）
int find(char a[], char b[])
{
	int m = strlenth(a);
	int n = strlenth(b);
	for (int i = 0; i < m; i++)
	{
		int j;
		for (j = 0; j < n; j++)
		{
			if (a[i + j] != b[j])
				break;
		}
		if (j == n) return i;
	}
	return -1;
}


//kmp算法
void Next(char a[], int next[])
{
	next[1] = 0;
	next[2] = 1;
	int j = 1;
	int i = 2;
	int m = strlenth(a);
	while (i < m)
	{
		if (j == 0 || a[j - 1] == a[i - 1])
		{
			i++; j++;
			if (a[j - 1] != a[i - 1])
			{
				next[i] = j;
			}
			else {
				next[i] = next[j];
			}
		}
		else {
			j = next[j];
		}
	}
}

int kmp(char a[], char b[], int next[])
{
	int m = strlenth(a);
	int n = strlenth(b);
	Next(b, next);
	int i = 1, j = 1;
	while (i <= m && j <= n)
	{
		if (j == 0 || a[i - 1] == b[j - 1]) {
			i++;j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j > n) return (i - n);
	return -1;
}

int main(void)
{
	char a[] = "abaabccccaaabab";
	char b[] = "abc";
	int next[5] = { 0 };
	int ans = kmp(a, b, next);
	std::cout << ans;
	return 0;
}