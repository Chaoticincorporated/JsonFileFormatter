#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <fstream>

using namespace std;

//Maxwell Schriner
//FileFormat Header file

struct NodeBase {
	string name;
	string nodeType;
	bool primeForFileData;
	NodeBase* link;
	ArrayBody arrayData;
	ObjectBody objectData;
	int intData;
	string stringData;
	double doubleDate;
};

class DataGroupings {
public:
	DataGroupings();
	~DataGroupings();
	void initializeFile();
	void deleteGrouping(NodeBase*);
	int countNodesInGroup(NodeBase*);
	void createStructureForArray(bool);
	void createStructureForObject(bool);
	void formatData(ostream&);
	void formatData(ostream&, istream&);
private:
	NodeBase* firstNode;
};

class ObjectBody : public DataGroupings {
public:
	ObjectBody();
	~ObjectBody();
	NodeBase addNode(string /*name*/, string /*nodeType*/, bool /*primeForFileData*/);
private:
};

class ArrayBody : public DataGroupings {
public:
	ArrayBody();
	~ArrayBody();
	NodeBase addNode(string /*nodeType*/);
private:
};
