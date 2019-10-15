#include<iostream>
#include<string>
#include<cstring>
#include<ctype.h>
#include<fstream>
#define N 50
using namespace std;

typedef struct Tree{
	char data[N];
	int count;
	struct Tree *lchild;
	struct Tree *rchild;
}Tree,*bTree;
class Word{
public:
	Word();
	int get_word(int start, int end, char* p, char* word);
	void create_Tree(char* m, bTree& b); 
	void Order(bTree b, FILE* q);
	int sum;
	char temp[N];
	char temp1[N];
	char word[N];
	char file_Name[20];
	int j;
	int i;
};

Word::Word()
{
	sum = 0;
	j = 0;
	i = 0;
}

int Word::get_word(int start, int end, char* p, char* word)
{
	memset(word, 0, sizeof(char));
	for ( i = start; i<end; i++)
	{
		if (isalpha(p[i]))
		{
			word[j] = p[i];
			j++;
		}
		else if (j == 0)
		{
			continue;
		}
		else
		{
			word[j] = '\0';
			j = 0;
			sum++;
			break;
		}
	}
	return i;
}

void Word::create_Tree(char* m, bTree& b)
{
	strcpy(temp, m);
	temp[0] = tolower(m[0]);
	if (b == NULL)
	{
		b = (bTree)malloc(sizeof(Tree));
		strcpy(b->data, m);
		b->count = 1;
		b->lchild = NULL;
		b->rchild = NULL;
	}
	else
	{
		strcpy(temp1, b->data);
		temp1[0] = tolower(b->data[0]);
		if (strcmp(temp, temp1) == -1)
		{
			create_Tree(m, b->lchild);
		}
		else if (strcmp(temp, temp1) == 1)
		{
			create_Tree(m, b->rchild);
		}
		else
		{
			b->count++;
		}
	}
}

void Word::Order(bTree b, FILE* q)
{
	if (b != NULL)
	{
		Order(b->lchild, q);
		fprintf(q, "\t%-30s 次数:%-9d\t\n", b->data, b->count);
		printf("\t%-30s 次数:%-9d\t\n", b->data, b->count);
		Order(b->rchild, q);
	}
}
int main()
{
	Word w;
	while (true)
	{
		memset(w.file_Name, 0, sizeof(w.file_Name));
		
		cout << "请输入要进行词频统计的文件" << endl;
		cin >> w.file_Name;
		FILE *q;
		 
		q=fopen(w.file_Name,"rb");
		if (q==NULL)
		{
			cout << "找不到文件" << endl;
			return false;
		}
		cout << "成功打开文件" << w.file_Name << endl;
		/*读取文件*/
		fseek(q, 0, SEEK_END);
		int len = ftell(q);
		rewind(q);
		char *p = new char[len + 1];
		p[len] = 0;
		fread(p, 1, len, q);
		fclose(q);
		//读取单词
		cout << p << endl;
		cout << "\n\n" << endl;
		bTree b = NULL;
		while (w.i<len)
		{
			w.i = w.get_word(w.i, len, p, w.word);
			if (strlen(w.word) == 0)
			{
				break;
			}
			w.create_Tree(w.word, b);
		}
		
		memset(w.file_Name, 0, sizeof(w.file_Name));
		
	   cout<<"please enter the filename"<<endl;
		cin >> w.file_Name;
		q=fopen(w.file_Name,"w");
		if (q == NULL)
		{
			cout << "不能写入文件" << endl;
			return false;
		}
		cout<<"\n"<<endl;
		fprintf(q, "\t\tWorld Count Result: \n");
		cout<<"\t结果如下: \n"<<endl;
		fprintf(q, "\n");
		w.Order(b,q);
		fprintf(q, "\n");
		fprintf(q, "The total number of world in the article: %d\n", w.sum);
		printf("the numbe：%d\n", w.sum);
		fclose(q);
		cout<<"\n"<<endl;
		cout << "统计结果写入文件:" << w.file_Name << endl;
	}
	return 0;
}

