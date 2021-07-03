#include <iostream>
#include <string>

#include "TR.cpp"

using namespace std;

template<typename T>
void Menu(Tr<T> t);

int main()
{
	Tr<string> t;
	Menu(t);



	return 0;
}

template<typename T>
void Menu(Tr<T> t)
{
	int n;
	T d;
	node<T> temp;
	while (1)
	{
		cout << "(1) 삽입 (2) 삭제 (3) 검색 (4) 출력 (0) 종료: ";
		cin >> n;

		switch (n)
		{
		case 1:
		{
			cout << "삽입하는 데이터를 입력하세요.\n";
			cout << "번호: ";
			cin >> temp.value;
			cout << "이름: ";
			cin >> temp.data;
			t.insert(temp);
		}
		break;
		case 2:
		{
			cout << "삭제하는 데이터를 입력하세요.\n";
			cout << "번호: ";
			cin >> n;
			t.Delete(n);
		}
		break;
		case 3:
		{
			cout << "번호로 검색(1), 이름으로 검색(2): ";
			cin >> n;
			
			if (n == 2)
			{
				cout << "검색하는 데이터를 입력하세요.\n";
				cout << "이름: ";
				cin >> temp.data;
				temp = *(t.Search(t.Root, temp.data));
			}
			else if (n == 1)
			{
				cout << "검색하는 번호를 입력하세요.\n";
				cout << "번호: ";
				cin >> temp.value;
				temp = *(t.Search(t.Root, temp.value));
			}

			if (temp.value == NULL)
				cout << "검색하는 데이터가 존재 하지 않습니다.\n";
			else
				cout << temp.value << " " << temp.data << endl;

		}
		break;
		case 4:
		{
			int size = 0;
			cout << t.check_depth(t.Root) << endl;
			cout << size << endl;
			cout << "[모든 노드 출력]\n";
			t.print(t.Root);
			t.print_Tree();
		}
		break;
		case 0:
			return;
		}

	}
}