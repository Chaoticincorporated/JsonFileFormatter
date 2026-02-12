#include "FileFormat.h"

//Maxwell Schriner
//FileFormat Implementation file

//Classless Functions

//take a yes or no input question and then validates the user input
bool booleanInput(string question)
{
	char userResponse;
	bool returnValue;
	cout << question << endl;
	cout << "Please respond with a lowercase y or n: ";
	cin >> userResponse;
	while (userResponse != 'y' || userResponse != 'n')
	{
		cout << "Invalid response, please respond with a lowercase y or n: ";
		cin >> userResponse;
	}
	switch (userResponse)
	{
	case 'y':
		returnValue = true;
		break;
	case 'n':
		returnValue = false;
		break;
	}
	return returnValue;
}

string validateNodeType()
{
	char userResponse;
	string returnValue = "";
	cout << "what type of data value would you like to add?" << endl;
	
	do
	{
		if (returnValue == "invalid")
			cout << "invalid response, plase try again." << endl;
		cout << "a = array, o = object, i = int, s = string and d = double. please use lowercase:";
		cin >> userResponse;
		switch (userResponse)
		{
		case 'a':
			returnValue = "array";
			break;
		case 'o':
			returnValue = "object";
			break;
		case 'i':
			returnValue = "int";
			break;
		case 's':
			returnValue = "string";
			break;
		case 'd':
			returnValue = "double";
			break;
		default:
			returnValue = "invalid";
		}
	} while (returnValue != "invalid");
	return returnValue;
}
string validateFileBase()
{
	char userResponse;
	string returnValue = "";
	cout << "what type of data value would you like to add?" << endl;
	do
	{
		if (returnValue == "invalid")
			cout << "invalid response, plase try again." << endl;
		cout << "a = array, o = object. please use lowercase:";
		cin >> userResponse;
		switch (userResponse)
		{
		case 'a':
			returnValue = "array";
			break;
		case 'o':
			returnValue = "object";
			break;
		default:
			returnValue = "invalid";
		}
	} while (returnValue != "invalid");
	return returnValue;
}

//base DataGroupings class
DataGroupings::DataGroupings()
{
	firstNode = NULL;
}
void DataGroupings::deleteGrouping(NodeBase* walker)
{
	cout << "deleting node" << endl;
	NodeBase* stalker = NULL;
	while (walker != NULL)
	{
		if (walker->nodeType == "array")
			walker->arrayData.deleteGrouping(walker->link);
		else if (walker->nodeType == "object")
			walker->objectData.deleteGrouping(walker->link);
		stalker = walker;
		walker = walker->link;
		delete stalker;
	}
}
DataGroupings::~DataGroupings()
{
	deleteGrouping(firstNode);
}
int DataGroupings::countNodesInGroup(NodeBase* walker)
{
	int totalNodes = 0;
	while (walker != NULL)
	{
		if (walker->nodeType == "array")
			totalNodes += walker->arrayData.countNodesInGroup(walker->link);
		else if (walker->nodeType == "object")
			totalNodes += walker->objectData.countNodesInGroup(walker->link);
		walker = walker->link;
		totalNodes++;
	}
	return totalNodes;
}
void DataGroupings::createStructureForArray(bool isStartOfFile, int layer)
{
	NodeBase* walker = firstNode;
	bool inputingData;
	do
	{
		NodeBase* builder = new NodeBase; 
		builder->nodeType = validateNodeType();
		builder->dataDepth = layer + 1;
		builder->link = NULL;
		if (builder->nodeType == "array" || builder->nodeType == "object")
		{
			builder->dataGroups = DataGroupings();
			bool populateGrouping = booleanInput("Would you like to populate this data grouping?");
			if (populateGrouping && builder->nodeType == "array")
				builder->dataGroups.createStructureForArray(false, builder->dataDepth);
			else if (populateGrouping)
				builder->dataGroups.createStructureForObject(false, builder->dataDepth);
		}

		if (firstNode == NULL)
			firstNode = builder;
		else
		{
			walker->link = builder;
			walker = walker->link;
		}

		if (isStartOfFile)
			inputingData = booleanInput("Would you like to add another value to this array?");
	} while (inputingData);
}
void DataGroupings::createStructureForObject(bool isStartOfFile, int layer)
{
	NodeBase* walker = firstNode;
	bool inputingData = false;
	do
	{
		NodeBase* builder = new NodeBase;
		builder->nodeType = validateNodeType();
		builder->dataDepth = layer + 1;
		builder->link = NULL;

		builder->primeForFileData = booleanInput("Will this member be populated via a file?");
		cout << "what would you like to name this member: ";
		cin.ignore(80, '\n');
		getline(cin, builder->name);

		if (builder->nodeType == "array" || builder->nodeType == "object")
		{
			builder->dataGroups = DataGroupings();
			bool populateGrouping = booleanInput("Would you like to populate this data grouping?");
			if (populateGrouping && builder->nodeType == "array")
				builder->dataGroups.createStructureForArray(false, builder->dataDepth);
			else if (populateGrouping)
				builder->dataGroups.createStructureForObject(false, builder->dataDepth);
		}

		if (firstNode == NULL)
			firstNode = builder;
		else
		{
			walker->link = builder;
			walker = walker->link;
		}

		if(isStartOfFile)
			inputingData = booleanInput("Would you like to add another member to this object?");
	} while (inputingData);
}



//Formatter class
Formatter::Formatter()
{
	
	fileBase = new NodeBase;
	fileBase->dataDepth = 0;
	fileBase->nodeType = validateFileBase();
	fileBase->dataGroups = DataGroupings();
}
Formatter::~Formatter()
{
	delete fileBase;
}

/*
if (baseType == "array")
		fileBase->dataGroups;
	else
		fileBase->objectData = ObjectBody();
*/

/*
//derived ObjectBody class
ObjectBody::ObjectBody() : DataGroupings() {}
ObjectBody::~ObjectBody() {}

//derived ArrayBody class
ArrayBody::ArrayBody() : DataGroupings() {}
ArrayBody::~ArrayBody() {}
*/