#include <iostream>
#include <fstream>
#include <string>
#include <list> 
#include <vector>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <functional>
#include <chrono>
#include <ctime>
#include <typeinfo>

#include "cereal/cereal.hpp"
#include "cereal/access.hpp"
#include "cereal/macros.hpp"

#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/list.hpp"

#define MANUFACTURER_FILE "manufacturers.json"
#define OPTICS_FILE "optics.json"
#define RECEIPT_FILE "receipt.json"
 
using namespace std;
using namespace cereal;

class Optic;
class OpticsManufacturer;

vector<OpticsManufacturer> globalManufacturers;
vector<Optic> globalOptics;

class Optic {
private:
	string type;
	int width;
	int size;
	string material;
	double price;

public:
	Optic() {}

	Optic(string type, int width, int size, string material, double price) {
		this->type = type;
		this->width = width;
		this->size = size;
		this->material = material;
		this->price = price;
	}

	Optic(const Optic &optic) {
		type = optic.type;
		width = optic.width;
		size = optic.size;
		material = optic.material;
		price = optic.price;
	}

	template<class Archive>
	void serialize(Archive & archive) {
		archive(type, width, size, material, price); 
	}

	string getType() {
		return this->type;
	}

	int getWidth() {
		return this->width;
	}

	int getSize() {
		return this->size;
	}

	string getMaterial() {
		return this->material;
	}

	double getPrice() {
		return this->price;
	}

	friend ostream& operator << (ostream& out, Optic &optic) {
		out << "Optics Type: " << optic.type << " Width: " << optic.width << " Size: " << optic.size << " Optics Material: " << optic.material << " Price: " << optic.price << endl << endl;
	}
};

class OpticsManufacturer {
private:
	string bulstat;
	string name;
	string address;
	string phoneNumber;
	list<Optic> availableOptics;

public:
	OpticsManufacturer() {}

	OpticsManufacturer(string bulstat, string name, string address, string phoneNumber) {
		this->bulstat = bulstat;
		this->name = name;
		this->address = address;
		this->phoneNumber = phoneNumber;
	}

	template<class Archive>
	void serialize(Archive & archive) {
		archive(bulstat, name, address, phoneNumber, availableOptics); 
	}

	string getBulstat() {
		return this->bulstat;
	}

	string getName() {
		return this->name;
	}

	string getAddress() {
		return this->address;
	}

	string getPhoneNumber() {
		return this->phoneNumber;
	}

	void addOptic(Optic optic) {
		availableOptics.push_back(optic);
	}

	Optic getAvailableOptic(int index) {
		list<Optic>::iterator it = availableOptics.begin();
		advance(it, index);

		return *it;
	}

	friend ostream& operator << (ostream& out, OpticsManufacturer &man) {
		out << "Company Bulstat: " << man.bulstat << endl << "Company Name: " << man.name << endl << "Address: " << man.address << endl << "Phone Number: " << man.phoneNumber << endl << endl;

		out << "Available Optics: " << endl;
		for (list<Optic>::iterator i = man.availableOptics.begin(); i != man.availableOptics.end(); ++i) {
			
			out << "Optics Type: " << i->getType() << endl << "Width: " << i->getWidth() << endl << "Size: " << i->getSize() << endl << "Optics Material: " << i->getMaterial() << endl << "Price: " << i->getPrice() << endl << endl;
		}

		return out;
	}

};

class IOUtils {
private:
	

public:
	IOUtils() {}

	template <typename T, typename A>
	void readFile(string fileName, vector<T, A> &collection) {
		fstream file;
		file.open(fileName.c_str(), ios::in);

		bool isEmpty = file.peek() == ifstream::traits_type::eof();

		if(file.is_open()) {
			
			if(!isEmpty) {
				{
					JSONInputArchive archiveIn(file);
					archiveIn(collection);
				}
			}

			file.close();
		} else {

			cout << "File could not be opened" << endl;
		}

	}

	template <typename T, typename A>
	void writeToFile(string fileName, vector<T, A> &collection) {
		fstream file;
		file.open(fileName.c_str(), ios::out | ios::trunc);

		if(file.is_open()) {
			{
				JSONOutputArchive archiveOut(file);
				archiveOut(CEREAL_NVP(collection));
			}


			file.close();
		} else {

			cout << "File could not be opened" << endl;
		}
		
	}

	template <typename T, typename A>
	void printVector(vector<T, A> collection) {

		for(int i = 0; i < collection.size(); ++i) {
			cout << i+1 << ". " << endl << collection[i] ;
		}
	}

	template <typename T>
	T getValidatedInput(const char* prompt, function <bool(T)> validator) {
		T tmp;

		do {
			cout << prompt << endl;
			cin >> tmp;
		} while(!validator(tmp));

		return tmp;
	}
};

class MenuItem {
protected:
	const char* title;

public:
	MenuItem(const char* title) {
		this->title = title;
	};

	//virtual ~MenuItem();
	
	virtual void execute() = 0;

	const char* getTitle() {
		return title;
	}
};

class RegisterManufacturerItem : public MenuItem {
private:
	IOUtils io;

public:
	RegisterManufacturerItem(const char* title): MenuItem(title) {}

	void execute() {
		string bulstat, name, address, phone;

		cin.ignore(1, '\n');

		cout << "Enter the company BULSTAT" << endl;
		getline(cin, bulstat);

		cout << "Enter the company's name" << endl;
		getline(cin, name);

		cout << "Enter an address" << endl;
		getline(cin, address);

		phone = io.getValidatedInput<string>("Enter a phone number", [](string arg)->bool {
			return arg.find_first_not_of("0123456789") == string::npos;
		});

		OpticsManufacturer manufacturer(bulstat, name, address, phone);		

		globalManufacturers.push_back(manufacturer);
	}
};

class RegisterOpticItem : public MenuItem {
private:
	IOUtils io;

public:
	RegisterOpticItem(const char* title): MenuItem(title) {}

	void execute() {
		double price;
		int width, size;
		string type, material;

		cin.ignore(1, '\n');

		cout << "Enter the optic type" << endl;
		getline(cin, type);

		width = io.getValidatedInput<int>("Enter the width", [](int arg)->bool {
			return arg > 0;
		});

		size = io.getValidatedInput<int>("Enter the size", [](int arg)->bool {
			return arg > 0;
		});
		
		cin.ignore(1, '\n');

		cout << "Enter the material" << endl;
		getline(cin, material);

		price = io.getValidatedInput<double>("Enter the price", [](double arg)->bool {
			return arg > 0;
		});

		Optic optic(type, width, size, material, price);

		globalOptics.push_back(optic);
	}
};

class OrderItem : public MenuItem {
private:
	IOUtils io;
	vector<Optic> orderedOptics;

public:
	OrderItem(const char* title): MenuItem(title) {}

	void execute() {
		int manufacturerIndex, opticIndex;

		io.printVector(globalManufacturers);		

		manufacturerIndex = io.getValidatedInput<int>("Choose a manufacturer", [](int arg)->bool {
			return arg >= 0 && arg <= globalManufacturers.size();
		});
		

		do {
			cout << globalManufacturers[manufacturerIndex-1];

			opticIndex = io.getValidatedInput<int>("Choose an optic", [](int arg)->bool {
				return arg >= 0 && arg <= globalOptics.size();
			});
			
			
			if(opticIndex != 0)
				orderedOptics.push_back(globalManufacturers[manufacturerIndex-1].getAvailableOptic(opticIndex-1));

			cout << "To Exit Press 0" << endl;
		} while (opticIndex != 0);	

		double total = 0;
		for(Optic optic : orderedOptics) {
			cout << optic;

			total += optic.getPrice();
		}
		cout << "TOTAL: " << total << endl;

		if(!orderedOptics.empty())
			io.writeToFile(RECEIPT_FILE, orderedOptics);
	}
};

class AddOpticToManufacturerItem : public MenuItem {
private:
	IOUtils io;

public:
	AddOpticToManufacturerItem(const char* title): MenuItem(title) {}

	void execute() {
		int manufacturerIndex, opticIndex;

		io.printVector(globalManufacturers);

		manufacturerIndex = io.getValidatedInput<int>("Choose a manufacturer", [](int arg)->bool {
			return arg >= 0 && arg <= globalManufacturers.size();
		});

		io.printVector(globalOptics);

		opticIndex = io.getValidatedInput<int>("Choose an optic", [](int arg)->bool {
			return arg >= 0 && arg <= globalOptics.size();
		});

		globalManufacturers[manufacturerIndex-1].addOptic(globalOptics[opticIndex-1]);
	}
};

class ExitItem : public MenuItem {
private:
	IOUtils io;

public:
	ExitItem(const char* title): MenuItem(title) {}

	void execute() {
		io.writeToFile(MANUFACTURER_FILE, globalManufacturers);
		io.writeToFile(OPTICS_FILE, globalOptics);
	}
};

template <class T>
class Menu {
private:
	
	vector<reference_wrapper<T>> items;
public:

	Menu(initializer_list<reference_wrapper<T>> menuItems) {

		for(auto item : menuItems) {

			items.push_back(item.get());
		}
	}

	void printMenuItems() {

		cout << "Select:" << endl;
		for(int i = 0; i < items.size(); i++) {

			cout << i+1 << ". " << items[i].get().getTitle() << endl;
		}
	}

	void start() {
		int i;

		do {			

			printMenuItems();
			cin >> i;

			items[i-1].get().execute();
		} while (typeid(items[i-1].get()).name() != typeid(ExitItem).name());
	}

	~Menu() {}
};

int main() {
	IOUtils io;

	RegisterManufacturerItem registerManufacturer("Register Manufacturer");
	RegisterOpticItem registerOptic("Register Optic");
	OrderItem orderOptic("Order an Optic");
	AddOpticToManufacturerItem addOptic("Add an Optic to Manufacturer");

	ExitItem exit("Exit");
	
	Menu<MenuItem> menu({
		registerManufacturer, 
		registerOptic,
		orderOptic,
		addOptic,
		exit
	});

	io.readFile(MANUFACTURER_FILE, globalManufacturers);
	io.readFile(OPTICS_FILE, globalOptics);

	menu.start();

	return 0;
}