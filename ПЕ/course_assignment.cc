#include <iostream>
#include <fstream>
#include <string>
#include <list> 
#include <vector>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <functional>

#include "cereal/cereal.hpp"
#include "cereal/access.hpp"
#include "cereal/macros.hpp"

#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/list.hpp"

#define MANUFACTURER_FILE "manufacturers.json"
#define OPTICS_FILE "optics.json"
 
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

	friend ostream& operator << (ostream& out, OpticsManufacturer &man) {
		out << "Company Bulstat: " << man.bulstat << endl << "Company Name: " << man.name << endl << "Address" << man.address << endl << "Phone Number" << man.phoneNumber << endl;

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

		if(file.is_open()) {
			{
				JSONInputArchive archiveIn(file);
				archiveIn(collection);
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

		cout << "Enter a phone number" << endl;
		getline(cin, phone);

		OpticsManufacturer manufacturer(bulstat, name, address, phone);		

		globalManufacturers.push_back(manufacturer);
	}
};

class RegisterOpticItem : public MenuItem {
public:
	RegisterOpticItem(const char* title): MenuItem(title) {}

	void execute() {
		double price;
		int width, size;
		string type, material;

		cin.ignore(1, '\n');

		cout << "Enter the optic size" << endl;
		getline(cin, type);

		cout << "Enter the width" << endl;
		cin >> width;

		cout << "Enter the size" << endl;
		cin >> size;
		cin.ignore(1, '\n');

		cout << "Enter the material" << endl;
		getline(cin, material);

		cout << "Enter the price" << endl;
		cin >> price;

		Optic optic(type, width, size, material, price);

		globalOptics.push_back(optic);
	}
};

class ExitItem : public MenuItem {
public:
	ExitItem(const char* title): MenuItem(title) {}

	void execute() {
		IOUtils io;

		io.writeToFile(MANUFACTURER_FILE, globalManufacturers);
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
		} while (i != 5);
	}

	~Menu() {}
};

int main() {
	IOUtils io;

	RegisterManufacturerItem registerManufacturer("Register Manufacturer");
	RegisterOpticItem registerOptic("Register Optic");

	ExitItem exit("Exit");
	
	Menu<MenuItem> menu({
		registerManufacturer, 
		registerOptic,
		exit
	});

	io.readFile(MANUFACTURER_FILE, globalManufacturers);

	menu.start();

	return 0;
}