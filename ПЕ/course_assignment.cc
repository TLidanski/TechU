#include <iostream>
#include <fstream>
#include <string>
#include <list> 
#include <vector>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <functional> // reference wrapper
#include<stdarg.h>

#define MANUFACTURER_FILE "manufacturers.txt"
 
using namespace std;

class Optic {
private:
	string type;
	int width;
	int size;
	string material;
public:
	Optic(string type, int width, int size, string material) {
		this->type = type;
		this->width = width;
		this->size = size;
		this->material = material;
	}

	Optic(const Optic &optic) {
		type = optic.type;
		width = optic.width;
		size = optic.size;
		material = optic.material;
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
};

class OpticsManufacturer {
private:
	string bulstat;
	string name;
	string address;
	string phoneNumber;
	list<Optic> availableOptics;

public:
	OpticsManufacturer(string bulstat, string name, string address, string phoneNumber) {
		this->bulstat = bulstat;
		this->name = name;
		this->address = address;
		this->phoneNumber = phoneNumber;
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

	void printAvailableOptics() {
		for (list<Optic>::iterator i = availableOptics.begin(); i != availableOptics.end(); ++i) {
			//cout << "Company Bulstat: " << i->bulstat << endl << "Company Name: " << i->name << endl << "Address" << i->address << endl << "Phone Number" << i->phoneNumber << endl;
			cout << "Optics Type: " << i->getType() << endl << "Width: " << i->getWidth() << endl << "Size: " << i->getSize() << endl << "Optics Material: " << i->getMaterial() << endl << endl;
		}
	}
};

class IOUtils {
private:
	string manufacturersFile;

public:
	IOUtils() {
		manufacturersFile = MANUFACTURER_FILE;
	}

	void writeManufacturerToFile(OpticsManufacturer manufacturer) {
		fstream file;
		file.open(manufacturersFile.c_str(), ios::app);

		if(file.is_open()) {
			// file.write((char*)&manufacturer, sizeof(OpticsManufacturer));

			// file.close();

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
		cout << "Executed Register Item" << endl;

		
	}
};

class RegisterOpticItem : public MenuItem {
public:
	RegisterOpticItem(const char* title): MenuItem(title) {}

	void execute() {}
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
	RegisterManufacturerItem registerManufacturer("Register Manufacturer");
	RegisterOpticItem registerOptic("Register Optic");
	
	Menu<MenuItem> menu({registerManufacturer, registerOptic});

	menu.start();

	return 0;
}