#pragma once
#include <string>
#include <vector>

enum class JSONType
{
	JNull = 0,
	JObject = 1,
	JArray = 2,
	JNum = 3,
	JString = 4,
	JBool = 5
};

class JSONObject;
class JSONValue;

class JSONArray
{
public:
	JSONArray() = default;
	~JSONArray() {};
	JSONArray(std::string InValue);

	std::string Stringify();

private:
	std::string StringifyNum();
	std::string StringifyString();
	std::string StringifyBool();

private:
	union {
		std::vector<double> Num_Value;
		std::vector<std::string> String_Value;
		std::vector<bool> Bool_Value;
	};
	JSONType Type = JSONType::JNull;
};

class JSONObject
{
public:
	JSONObject() {};
	~JSONObject() {};

	JSONObject(std::vector<JSONValue*> InMembers):Members(InMembers) { };

	std::string Stringify();
public:
	std::vector<JSONValue*> Members;
};

class JSONValue
{
public:
	JSONValue() { Object_Value = nullptr; };
	~JSONValue() {};

	JSONValue(std::string InName, bool InValue) { Name = InName; Type = JSONType::JBool; Bool_Value = InValue; };
	JSONValue(std::string InName, double InValue) { Name = InName; Type = JSONType::JNum; Num_Vaulue = InValue; };
	JSONValue(std::string InName, std::string* InValue) { Name = InName; Type = JSONType::JString; String_Value = InValue; };
	JSONValue(std::string InName, JSONArray* InValue) { Name = InName; Type = JSONType::JArray; Array_Value = InValue; };
	JSONValue(std::string InName, JSONObject* InValue) { Name = InName; Type = JSONType::JObject; Object_Value = InValue; };
	JSONValue(std::string InName) { Name = InName; Type = JSONType::JNull; };

	std::string Stringify();

private:
	union
	{
		bool Bool_Value;
		double Num_Vaulue;
		std::string* String_Value;
		JSONArray* Array_Value;
		JSONObject* Object_Value;
	};

public:
	JSONType Type = JSONType::JNull;
	std::string Name = "";
};

class JSON
{
public:
	std::string Stringify(std::vector<JSONValue*> InData);
	std::vector<JSONValue*> Parse(std::string InJSONStr);

private:
	JSONValue* ParseJSONObject(std::string InJSONStr, std::size_t& InValueEnd);
	JSONValue* ParseJSONArray(std::string InJSONStr, std::size_t& InValueEnd);
	JSONValue* ParseBool(std::string InJSONStr, std::size_t& InValueEnd);
	JSONValue* ParseString(std::string InJSONStr, std::size_t& InValueEnd);
	JSONValue* ParseNum(std::string InJSONStr, std::size_t& InValueEnd);
	JSONValue* ParseNull(std::string InJSONStr, std::size_t& InValueEnd);
};

