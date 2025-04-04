//Item inventory Program:
//by Jose peña and Ivan Ferrat
//this program is an inventory system that we can add,remove, an exit the application
//Objects, attributes and operations are named in pascal case
//variables declared inside functions are lowercase
//constants declared in macros are written in mayus
//The items are declared in item.txt

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> 


#define ADDITEM 1
#define REMOVEITEM 2
#define SHOWINVENTORY 3
#define EXITMENU 4

struct ItemStats
{
	float Health;
	float Armor;
	float Damage;	
};


class Item
{
private:
	std::string Name;
	std::string Description;
	ItemStats ItemStats;

public:
	std::string UniqueId;

	Item(const std::string name, const std::string description,const std::string uniqueid, const float health = 0, const float armor = 0, const float damage = 0)
	{
		Name = name;
		Description = description;
		UniqueId = uniqueid;
		ItemStats.Health = health;
		ItemStats.Armor = armor;
		ItemStats.Damage = damage;
	
	}

	void ShowName()
	{
		std::cout << " Item Name: " << Name << std::endl;
	}

	void ShowDescription()
	{
		std::cout << " Item Description: " << Description << std::endl;
	}

	void ShowStats()
	{
		std::cout << " Stats: " << std::endl;
		std::cout << " health: " << ItemStats.Health << " armor:" << ItemStats.Armor << " Damage: " << ItemStats.Damage << std::endl;
	}


};

class Inventory
{
private:
	//This Map is our Count for the inventory
	std::map<std::string, int> ItemCountInventory;
	//the information of items is stored in this vector
	std::vector<Item>  Items;
public:
	Inventory(const std::vector<Item>  ItemsToRegister)
	{
		Items = ItemsToRegister;
		for (const Item& itemtoregister : ItemsToRegister) 
		{
			ItemCountInventory.insert({ itemtoregister.UniqueId,0});
		}
	}

	void AddItemToInventory() 
	{
	
		int option = PickAnItem();
		std::cout << "Added 1 unit" << std::endl;
		ItemCountInventory.at(Items[option - 1].UniqueId)++;
		system("pause");
		system("ClS");

	}

	void RemoveItemToInventory()
	{

		int option = PickAnItem();
		if (ItemCountInventory.at(Items[option - 1].UniqueId) <= 0) 
		{
			std::cout << "This item is not found in the inventory"<<std::endl;
			ItemCountInventory.at(Items[option - 1].UniqueId) = 0;
			system("pause");
			system("ClS");

		}
		else
		{
			std::cout << "Removed 1 unit" << std::endl;
			ItemCountInventory.at(Items[option - 1].UniqueId)--;
			system("pause");
			system("ClS");

		}
		

	}


	//Its a while true because we return a value to break the flow of the loop
	int PickAnItem() 
	{
		while (true) {
			for (int i = 0; i < Items.size(); i++)
			{
				std::cout << i + 1 << "( ";
				Items[i].ShowName();

			}
			int option;
			std::cout << "Choose an item " << std::endl;

			std::cin >> option;

			if (option > 0 && option - 1 < Items.size())
			{
				return option;
			}
			else
			{
				std::cout << "Please type something valid" << std::endl;
				system("pause");
				system("ClS");
			}
		}
		
	}
	void DisplayInventoryItems()
	{
		int itemsininventory=0;
		for (auto item : Items)
		{
			if (ItemCountInventory[item.UniqueId]>0)
			{
				item.ShowName();
				item.ShowDescription();
				item.ShowStats();
				std::cout << "quantity: " << ItemCountInventory[item.UniqueId] << std::endl;
				itemsininventory++;
				system("pause");
				system("ClS");
			}
		}
		if (itemsininventory == 0) 
		{
			std::cout << "Theres no items in your inventory" << std::endl;
			system("pause");
			system("ClS");
		}
	}

};

//obtain a  item.txt file an convert it to item  
Item  GenerateItemFromString(const std::string& line) 
{
	std::stringstream linestringsteam(line);
	std::string name,description,uid,health,armor,damage;
	std::getline(linestringsteam,name,',');
	std::getline(linestringsteam, description, ',');
	std::getline(linestringsteam, uid, ',');
	std::getline(linestringsteam, health, ',');
	std::getline(linestringsteam, armor, ',');
	std::getline(linestringsteam, damage, ',');
	Item result(name, description, uid, std::stoi(health, 0, 10), std::stoi(armor, 0, 10), std::stoi(damage, 0, 10));
	return result;

}
std::vector<Item> GetItemsFromFile() 
{
	std::ifstream file("items.txt");
	std::string line;
	std::vector<Item> items;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			items.push_back(GenerateItemFromString(line));
		}
	}
	file.close();

	return items;
}
int main() 
{
	
	Inventory inventory(GetItemsFromFile());
	std::cout << "Welcome to the Inventory System" << std::endl;
	bool istheapplicationrunning = true;
	while (istheapplicationrunning)
	{
		int opcion;

		std::cout << "The Choices Are:" << std::endl;
		
		std::cout << "1( Add an item to the inventory" << std::endl;
		std::cout << "2( Delete an item from the inventory" << std::endl;
		std::cout << "3( Show Inventory" << std::endl;
		std::cout << "4( Exit" << std::endl;

		std::cin >> opcion;

		switch (opcion) 
		{
		case ADDITEM:
			system("ClS");
			inventory.AddItemToInventory();
			break;
		case REMOVEITEM:
			system("ClS");
			inventory.RemoveItemToInventory();
			break;
		case SHOWINVENTORY:
			system("ClS");
			inventory.DisplayInventoryItems();
			break;
		case  EXITMENU:
			system("ClS");
			istheapplicationrunning = false;
			std::cout << "Thank you for using the inventory system" << std::endl;
			break;
		default:
			std::cout << "please pick a valid choice" << std::endl;
			system("pause");
			system("ClS");
			break;

		}
		
	}

}
