#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "AVL.h"
int main()
{
	Ptr tree = nullptr;

	int x;
	bool h = true;
	char c;

	while (1)
	{
		printf("===============================================================================\n");
		printf("enter command [i - insert, d - delete, e - exit]: ");
		scanf("%c", &c);
		if (c == 'e') break;
		printf("enter key: ");
		scanf("%d", &x);
		if (c == 'i')
		{
			printf("insert %d:\n", x);
			search(x, tree, h);
			PrintTree(tree);
		}
		else if (c == 'd')
		{
			printf("delete %d:\n", x);
			Delete(x, tree, h);
			PrintTree(tree);
		}
		else printf("ERROR: wrong command\n");
		getchar();
	}

	return 0;
}