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
};
struct IntNode : public NodeBase {
	int intData;
};
struct StringNode : public NodeBase {
	string stringData;
};
struct DoubleNode : public NodeBase {
	double doubleDate;
};
struct CharNode : public NodeBase {
	char charData;
};

class DataGroupings {
public:
	DataGroupings();
	~DataGroupings();
	int countNodesInGroup();
private:
	NodeBase* firstNode;
};

class ObjectBody : public DataGroupings {
public:
	ObjectBody();
	~ObjectBody();
	void addNode(string /*name*/, string /*nodeType*/, bool /*primeForFileData*/);
private:
};
struct ObjectNode : public NodeBase {
	ObjectBody objectData;
};

class ArrayBody : public DataGroupings {
public:
	ArrayBody();
	~ArrayBody();
	void addNode(string /*nodeType*/, bool /*primeForFileData*/);
private:
};
struct ArrayNode : public NodeBase  {
	ArrayBody arrayData;
};

class Formatter {
public:
	Formatter();
	~Formatter();

	void formatData(ostream&);
private:
	DataGroupings fileBase;
};