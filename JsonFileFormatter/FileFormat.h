#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <fstream>

using namespace std;

//Maxwell Schriner
//FileFormat Header file

struct NodeBase {
	int dataDepth; //how many nested arrays or objects down the data is
	string name;
	string nodeType;
	bool primeForFileData;
	NodeBase* link;
	DataGroupings dataGroups;
	int intData;
	string stringData;
	double doubleDate;
};

class DataGroupings {
public:
	DataGroupings();
	~DataGroupings();
	void deleteGrouping(NodeBase*);
	int countNodesInGroup(NodeBase*);
	void createStructureForArray(bool, int);
	void createStructureForObject(bool, int);
	void formatData(ostream&);
	void formatData(ostream&, istream&);
private:
	NodeBase* firstNode;
};



class Formatter
{
public:
	Formatter();
	~Formatter();
private:
	NodeBase* fileBase;
};

/*
class ObjectBody : public DataGroupings {
public:
	ObjectBody();
	~ObjectBody();
	//NodeBase addNode(string name, string nodeType, bool primeForFileData);
private:
};

class ArrayBody : public DataGroupings {
public:
	ArrayBody();
	~ArrayBody();
	//NodeBase addNode(string nodeType);
private:
};

*/