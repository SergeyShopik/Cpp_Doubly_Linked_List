#include"dualList.h"

int main()
{
	srand(time(0));
	dualList list;
	initDualList(list);

	// 1. Sort list with selection sort. 
	dualList resultList;
	initDualList(resultList);

	for (size_t i = 0; i < 10; i++)
		pushFront(list, 100 - rand() % 50);

	printList(list);
	choiceSort(list, resultList);
	printList(resultList);

	// 2. N grey and M white mice are in the circle. Cat rounds circle clockwise and eats each s mice.
	// Count starts with a grey mouse. Determine initial order of mice in circle if some time later K grey and L white mice are left.
	// Grey - 1, white - 0.
	dualList miceList;
	initDualList(miceList);
	int N = 5, M = 5, K = 3, L = 2, s = 3;
	/*std::cout << "Enter N, M, K, L, s";
	std::cin >> N >> M >> K >> L >> s;*/
	
	//create result list of K and L mice
	for (size_t i = 0; i < K; i++)
		pushFront(miceList, 1);
	for (size_t i = 0; i < L; i++)
		pushFront(miceList, 0);

	miceList = mice(miceList, N, M, K, L, s);
	printList(miceList);

	// 3. Change every element in n*m matrix to the next closest biggest element. Change to zero if no such element.
	const int n = 5;
	const int m = 7;
	int matrix[n][m];
	dualList matrixList;
	initDualList(matrixList);

	//init matrix
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}
	//print matrix
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	//create list
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m - 1; j++)
		{
			if (matrix[i][j + 1] > matrix[i][j])
				pushBack(matrixList, matrix[i][j + 1]);
			else
				pushBack(matrixList, 0);
		}
	}
	printList(matrixList);

	return 0;
}