#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
struct FProductData 
{
	string id;
	string name;
	string price;
	string category;
};

vector<FProductData> Products;
bool bReadFile;

vector<FProductData> LoadProductData()
{
	vector<FProductData> products;
	ifstream file("product_data.txt");
	if (!file.is_open())
	{
		return products;
	}
	string line;
	while (getline(file, line))
	{
		istringstream ss(line);
		string token;
		vector<string> tokens;
		while (getline(ss, token, ',')) 
		{
			tokens.push_back(token);
		}

		string line;
		while (getline(file, line)) 
		{
			stringstream ss(line);
			string idStr, name, priceStr, category;
			if (getline(ss, idStr, ',') && getline(ss, name, ',') &&
				getline(ss, priceStr, ',') && getline(ss, category, ',')) 
			{
				products.push_back({ idStr, name, priceStr, category });
			}
			else
			{
				continue; 
			}
		}
	}


	file.close();
	return products;
}


void BubbleSortProducts(bool Ascending = false) 
{
	int Size = Products.size();

	for (int i = 0; i < Size - 1; i++)
	{
		for (int j = 0; j < Size - i - 1; j++)
		{
			if (Ascending)
			{
				if (Products[j].price > Products[j + 1].price)
				{
					swap(Products[j], Products[j + 1]);
				}
			}
			else
			{
				if (Products[j].price < Products[j + 1].price)
				{
					swap(Products[j], Products[j + 1]);
				}
			}
		}
	}
}

void AddNewProduct(int ID, string Name, double Price, string Category) 
{
	if (!bReadFile)
	{
		return;
	}

	FProductData NewProduct;
	NewProduct.id = ID;
	NewProduct.name = Name;
	NewProduct.price = Price;
	NewProduct.category = Category;

	Products.push_back(NewProduct);
}

int SearchProductByID(string ID)
{
	for (size_t i = 0; i < Products.size(); ++i) 
	{
		if (Products[i].id == ID)
		{
			return i;
		}
	}
	return -1; 
}

void RemoveProduct(string ID)
{
	int Index = SearchProductByID(ID);

	if (Index != -1)
	{
		Products.erase(Products.begin() + Index);
	}
}

void InsertionSort() 
{
	int Size = Products.size();
	for (int i = 1; i < Size; ++i)
	{
		FProductData CurrentProduct = Products[i];
		int j = i - 1;
		while (j >= 0 && Products[j].price > CurrentProduct.price)
		{
			Products[j + 1] = Products[j];
			j = j - 1;
		}
		Products[j + 1] = CurrentProduct;
	}
}

vector<FProductData> SortByPriceRange(double MinPrice, double MaxPrice)
{
	vector<FProductData> ProductsInRange;

	for (const auto& Product : Products)
	{
		int ProductPrice = atoi(Product.price.c_str());

		if (ProductPrice >= MinPrice && ProductPrice <= MaxPrice)
		{
			ProductsInRange.push_back(Product);
		}
	}

	return ProductsInRange;
}

int main()
{
	Products = LoadProductData();

	for (int i = 0; i < Products.size(); i++) 
	{
		const FProductData& product = Products[i];
		cout << "ID: " << product.id << ", Name: " << product.name << ", Price: " << product.price << ", Category: " << product.category << endl;
	}

	BubbleSortProducts();

	cout << "BUBBLE SORTED" << endl;
	for (int i = 0; i < Products.size(); i++)
	{
		const FProductData& product = Products[i];
		cout << "ID: " << product.id << ", Name: " << product.name << ", Price: " << product.price << ", Category: " << product.category << endl;
	}

	vector<FProductData> ProductsInRange = SortByPriceRange(700, 900);


	cout << "SORTED BY PRICE RANGE (700-900)" << endl;
	for (int i = 0; i < ProductsInRange.size(); i++)
	{
		const FProductData& product = ProductsInRange[i];
		cout << "ID: " << product.id << ", Name: " << product.name << ", Price: " << product.price << ", Category: " << product.category << endl;
	}
}

