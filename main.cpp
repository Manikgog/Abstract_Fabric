#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

class Chair
{
public:
	virtual void useChair() = 0;
	virtual ~Chair() {};
};

class VictorianChair : public Chair
{
public: 
	void useChair() override
	{
		std::cout << "Victorian style chair";
	}
	~VictorianChair()
	{
		std::cout << this << " destuctor object of class VictorianChair\n";
	}
};

class ModernChair : public Chair
{
public:
	void useChair() override
	{
		std::cout << "Modern style chair";
	}
	~ModernChair()
	{
		std::cout << this << " destuctor object of class ModernChair\n";
	}
};
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
class Table
{
public:
	virtual void useTable(Chair* chair) = 0;
	virtual ~Table() {};
};

class VictorianTable : public Table
{
public:
	void useTable(Chair* chair) override
	{
		std::cout << "Victorian style table with ";
		chair->useChair(); std::cout << std::endl;
	}
	~VictorianTable()
	{
		std::cout << this << " destuctor object of class VictorianTable\n";
	}
};

class ModernTable : public Table
{
public:
	void useTable(Chair* chair) override
	{
		std::cout << "Modern style table with ";
		chair->useChair(); std::cout << std::endl;
	}
	~ModernTable()
	{
		std::cout << this << " destuctor object of class ModernTable\n";
	}
};
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
class Factory
{
public:
	virtual Chair* createChair() = 0;
	virtual Table* createTable() = 0;
	virtual ~Factory() {};
};

class VictorianFactory : public Factory
{
public:
	Chair* p_victorian_chair = nullptr;
	Table* p_victorian_table = nullptr;
	Chair* createChair() override
	{
		p_victorian_chair = new VictorianChair();
		std::cout << this << "	Allocate memory for Victorian Chair*\n";
		return p_victorian_chair;
	}

	Table* createTable() override
	{
		p_victorian_table = new VictorianTable();
		std::cout << this << "	Allocate memory for Victorian Table*\n";
		return p_victorian_table;
	}
	~VictorianFactory()
	{
		std::cout << this << " destuctor object of class VictorianFactory\n";
		if(p_victorian_chair)
			delete p_victorian_chair;
		std::cout << this << " Release memory of VictorianChair class ModernFactory\n";
		if(p_victorian_table)
			delete p_victorian_table;
		std::cout << this << " Release memory of VictorianTable class ModernFactory\n";
	}
	
};

class ModernFactory : public Factory
{
public:
	Chair* p_modernChair = nullptr;
	Table* p_modernTable = nullptr;
	Chair* createChair() override
	{
		p_modernChair  = new ModernChair();
		std::cout << this << "	Allocate memory for ModernChair*\n";
		return p_modernChair;
		
	}

	Table* createTable() override
	{
		p_modernTable = new ModernTable();
		std::cout << this << "	Allocate memory for ModernTable*\n";
		return p_modernTable;
		
	}
	~ModernFactory()
	{
		std::cout << this << " destructor of modernChair class ModernFactory\n";
		if (p_modernChair)
		{
			delete p_modernChair;
			std::cout << this << " Release memory of modernChair class ModernFactory\n";
		}
		if (p_modernTable)
			delete p_modernTable;
			std::cout << this << " Release memory of modernTable class ModernFactory\n";
	}
};
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); // установка кодовой страницы на ввод текста
	srand(time(NULL));

	Factory* factory = new VictorianFactory();
	Chair* chair = factory->createChair();
	Table* table = factory->createTable();
	table->useTable(chair);
	std::cout << std::endl;
	Factory* factory2 = new ModernFactory();
	Chair* chair2 = factory2->createChair();
	Table* table2 = factory2->createTable();
	table2->useTable(chair2);
	delete factory;
	delete factory2;
	return 0;
}
