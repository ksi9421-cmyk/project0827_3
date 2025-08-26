#include <iostream>
#include <algorithm>
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

	// 복사 생성자
	Inventory(const Inventory<T>& other)
	{
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		cout << "인벤토리 복사 완료" << endl;
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
			int newCapacity = capacity_ * 2;
			T* newArray = new T[newCapacity];
			for (int i = 0; i < size_; ++i)
				newArray[i] = pItems_[i];
			delete[] pItems_;
			pItems_ = newArray;
			capacity_ = newCapacity;

			pItems_[size_] = item;
			++size_;
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

	void Resize(int newCapacity)
	{
		if (newCapacity <= 0) return; // 안전 체크
		
		T* newArray = new T[newCapacity];
		int copySize = (newCapacity < size_) ? newCapacity : size_; // 잘라낼 경우 대비
		for (int i = 0; i < copySize; ++i)
			newArray[i] = pItems_[i];

		delete[] pItems_;
		pItems_ = newArray;
		capacity_ = newCapacity;
		size_ = copySize;  // size_는 newCapacity보다 크면 잘라냄
	}

	void SortItems()  
	{
		sort(pItems_, pItems_ + size_, [](const T& a, const T& b)
			{return a.GetPrice() > b.GetPrice(); } );
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
	void Assign(const Inventory<T>& other) 
	{
		if (this == &other) return;  // 자기 자신 대입 방지

		delete[] pItems_;
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i)
			pItems_[i] = other.pItems_[i];
		
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

	int GetPrice() const { return price_; }
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