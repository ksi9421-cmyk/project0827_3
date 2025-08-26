#include <iostream>
using namespace std;

template <typename T>
class Inventory
{
private:
	T* pItems_;
	int capacity_;
	int size_;

public:
	// 생성자
	Inventory(int capacity = 10) : capacity_(capacity > 0 ? capacity : 1), size_(0)
	{
		pItems_ = new T[capacity_];        //동적 배열 할당
	}

	// 소멸자
	~Inventory()
	{
		delete[] pItems_;
		pItems_ = nullptr;
	}

	void AddItem(const T& item)
	{
		if (size_ < capacity_)
		{
			pItems_[size_] = item;
			++size_;
		}
		else
		{
			cout << "인벤토리가 꽉 찼습니다!" << endl;
		}
	}

	void RemoveLastItem()
	{
		if (size_ > 0)
		{
			--size_;
		}
		else
		{
			cout << "인벤토리가 비어있습니다." << endl;
		}
	}

	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }
	
	void PrintAllItems() const
	{
		if (size_ == 0)
		{
			cout << "(비어있음)" << endl;
		}
		for (int i = 0; i < size_; ++i)
		{
			pItems_[i].PrintInfo();
		}
	}
	
};

class Item
{
private:
	string name_;
	int price_;

public:
	Item(string name = "???", int price = 0) : name_(name), price_(price) {}

	void PrintInfo() const
	{
		cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
	}
};

// 테스트용 메인함수
int main()
{
	Inventory<Item> inv(3);
	inv.AddItem(Item("칼", 100));
	inv.AddItem(Item("포션", 50));
	inv.PrintAllItems();

	inv.RemoveLastItem();
	inv.PrintAllItems();
}