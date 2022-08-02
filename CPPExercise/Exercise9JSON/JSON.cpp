#include "JSON.h"

std::string JSON::Stringify(std::vector<JSONValue*> InData)
{
    std::string Result = "{";
    std::vector<JSONValue*>::iterator ValueIterator = InData.begin();
    for (; ValueIterator != InData.end(); ++ValueIterator)
    {
        if (ValueIterator != InData.begin())
        {
            Result = Result + ",";
        }
        Result = Result + (*ValueIterator)->Stringify();
    }
    Result = Result + "}";
    return Result;
}

std::vector<JSONValue*> JSON::Parse(std::string InJSONStr)
{
	std::vector<JSONValue*> Result;
	std::string JSONStr = InJSONStr.substr(1, InJSONStr.size() - 2);
	std::size_t Current = JSONStr.find(":") + 1;
	while (Current != std::string::npos)
	{
		std::size_t ValueEnd;
		std::string ValueFirst = JSONStr.substr(Current, 1);
		if (ValueFirst == "{")
		{
			Result.push_back(ParseJSONObject(JSONStr, ValueEnd));
		}
		else if (ValueFirst == "[")
		{
			Result.push_back(ParseJSONArray(JSONStr, ValueEnd));
		}
		else if (ValueFirst == "n")
		{
			Result.push_back(ParseNull(JSONStr, ValueEnd));
		}
		else if (ValueFirst == "t" or ValueFirst == "f")
		{
			Result.push_back(ParseBool(JSONStr, ValueEnd));
		}
		else if (ValueFirst == "\"")
		{
			Result.push_back(ParseString(JSONStr, ValueEnd));
		}
		else
		{
			Result.push_back(ParseNum(JSONStr, ValueEnd));
		}
		if (ValueEnd >= JSONStr.size() - 1)
		{
			Current = std::string::npos;
		}
		else
		{
			JSONStr = JSONStr.substr(ValueEnd + 1, JSONStr.size() - ValueEnd + 1);
			Current = JSONStr.find(":") + 1;
		}
	}
    return Result;
}

JSONValue* JSON::ParseJSONArray(std::string InJSONStr, std::size_t& InValueEnd)
{
	std::size_t Current = InJSONStr.find(":");
	std::string Name = InJSONStr.substr(1, Current - 2);
	int LeftBrackets = 0;
	int RightBrackets = 0;
	for (int i = Current; i < InJSONStr.size(); ++i)
	{
		if (InJSONStr[i] == '[')
		{
			++LeftBrackets;
		}
		else if (InJSONStr[i] == ']')
		{
			++RightBrackets;
		}
		if (LeftBrackets == RightBrackets && LeftBrackets != 0)
		{
			InValueEnd = i + 1;
			std::string ValueString = InJSONStr.substr(Current + 1, i - Current);
			JSONArray* JSONArrayValue = new JSONArray(ValueString);
			return new JSONValue(Name, JSONArrayValue);
		}
	}
	return new JSONValue(Name);
}

JSONValue* JSON::ParseJSONObject(std::string InJSONStr, std::size_t& InValueEnd)
{
	std::size_t Current = InJSONStr.find(":");
	std::string Name = InJSONStr.substr(1, Current - 2);
	int LeftBraces = 0;
	int RightBraces = 0;
	for (int i = Current; i < InJSONStr.size(); ++i)
	{
		if (InJSONStr[i] == '{')
		{
			++LeftBraces;
		}
		else if (InJSONStr[i] == '}')
		{
			++RightBraces;
		}
		if (LeftBraces == RightBraces && LeftBraces != 0)
		{
			InValueEnd = i + 1;
			JSON JSONParse;
			std::string JObjectString = InJSONStr.substr(Current + 1, i - Current);
			std::vector<JSONValue*> JObjectMembers = JSONParse.Parse(JObjectString);
			JSONObject* JSONObjectValue = new JSONObject(JObjectMembers);
			return new JSONValue(Name, JSONObjectValue);
		}
	}
	return new JSONValue(Name);
}


JSONValue* JSON::ParseBool(std::string InJSONStr, std::size_t& InValueEnd)
{
	std::size_t Current = InJSONStr.find(":");
	std::string Name = InJSONStr.substr(1, Current - 2);
	for (int i = Current; i < InJSONStr.size(); ++i)
	{
		if (InJSONStr[i] == ',')
		{
			InValueEnd = i;
			return new JSONValue(Name, InJSONStr.substr(Current + 1, i - Current - 1) == "true");
		}
	}
	return new JSONValue(Name);
}

JSONValue* JSON::ParseString(std::string InJSONStr, std::size_t& InValueEnd)
{
	std::size_t Current = InJSONStr.find(":");
	std::string Name = InJSONStr.substr(1, Current - 2);
	for (int i = Current; i < InJSONStr.size(); ++i)
	{
		if (InJSONStr[i] == ',')
		{
			InValueEnd = i;
			std::string *StringValue = new std::string(InJSONStr.substr(Current + 2, i - Current - 3));
			return new JSONValue(Name, StringValue);
		}
	}
	return new JSONValue(Name);
}

JSONValue* JSON::ParseNum(std::string InJSONStr, std::size_t& InValueEnd)
{
	std::size_t Current = InJSONStr.find(":");
	std::string Name = InJSONStr.substr(1, Current - 2);
	for (int i = Current; i < InJSONStr.size(); ++i)
	{
		if (InJSONStr[i] == ',')
		{
			InValueEnd = i;
			return new JSONValue(Name, atof(InJSONStr.substr(Current + 1, i - Current - 1).c_str()));
		}
	}
	return new JSONValue(Name);
}

JSONValue* JSON::ParseNull(std::string InJSONStr, std::size_t& InValueEnd)
{
	std::size_t Current = InJSONStr.find(":");
	std::string Name = InJSONStr.substr(1, Current - 2);
	InValueEnd = Current + 4;
	return new JSONValue(Name);
}

std::string JSONValue::Stringify()
{
	std::string Result = "\"" + Name + "\":";
	switch (Type)
	{
	case JSONType::JNull:
		Result = Result + "null";
		break;
	case JSONType::JObject:
		Result = Result + Object_Value->Stringify();
		break;
	case JSONType::JArray:
		Result = Result + Array_Value->Stringify();
		break;
	case JSONType::JNum:
		Result = Result + std::to_string(Num_Vaulue);
		break;
	case JSONType::JString:
		Result = Result + *String_Value;
		break;
	case JSONType::JBool:
		if (Bool_Value == true)
		{
			Result = Result + "true";
		}
		else
		{
			Result = Result + "false";
		}
		break;
	}
	return Result;
}

std::string JSONObject::Stringify()
{
	JSON JSONString;
	std::string Result = JSONString.Stringify(Members);
	return Result;
}

JSONArray::JSONArray(std::string InValue)
{
	std::string FirstValue = InValue.substr(1, 1);
	std::string ContentValue = InValue.substr(1, InValue.size() - 2);
	if (FirstValue == "\"")
	{
		Type = JSONType::JString;
		std::vector<std::string> StringValue;
		std::size_t Current = ContentValue.find(",");
		while (Current != std::string::npos)
		{
			String_Value.push_back(ContentValue.substr(1, Current - 2));
			ContentValue = ContentValue.substr(Current + 1, ContentValue.size() - Current - 1);
			Current = ContentValue.find(",");
		}
		String_Value.push_back(ContentValue.substr(0, ContentValue.size()));
	}
	else if (FirstValue == "t" or FirstValue == "f")
	{
		Type = JSONType::JBool;
		std::vector<bool> BoolValue;
		std::size_t Current = ContentValue.find(",");
		while (Current != std::string::npos)
		{
			Bool_Value.push_back(ContentValue.substr(0, Current) == "true");
			ContentValue = ContentValue.substr(Current + 1, ContentValue.size() - Current - 1);
			Current = ContentValue.find(",");
		}
		Bool_Value.push_back(ContentValue.substr(0, ContentValue.size()) == "true");
	}
	else
	{
		Type = JSONType::JNum;
		std::size_t Current = ContentValue.find(",");
		while (Current != std::string::npos)
		{
			Num_Value.push_back(atof(ContentValue.substr(0, Current).c_str()));
			ContentValue = ContentValue.substr(Current + 1, ContentValue.size() - Current - 1);
			Current = ContentValue.find(",");
		}
		Num_Value.push_back(atof(ContentValue.substr(0, ContentValue.size()).c_str()));
	}
}

std::string JSONArray::Stringify()
{
	std::string Result = "[";
	switch (Type)
	{
	case JSONType::JNull:
		break;
	case JSONType::JArray:
		break;
	case JSONType::JNum:
		Result = Result + StringifyNum();
		break;
	case JSONType::JString:
		Result = Result + StringifyString();
		break;
	case JSONType::JBool:
		Result = Result + StringifyBool();
		break;
	default:
		break;
	}
	Result = Result + "]";
	return Result;
}

std::string JSONArray::StringifyNum()
{
	std::string Result;
	int SizeNum = Num_Value.size();
	for (int i = 0; i < SizeNum; ++i)
	{
		if (i != 0)
		{
			Result = Result + ",";
		}
		Result = Result + std::to_string(Num_Value[i]);
	}

	return Result;
}

std::string JSONArray::StringifyString()
{
	std::string Result;
	int SizeNum = String_Value.size();
	for (int i = 0; i < SizeNum; ++i)
	{
		if (i != 0)
		{
			Result = Result + ",";
		}
		Result = Result + String_Value[i];
	}

	return Result;
}

std::string JSONArray::StringifyBool()
{
	std::string Result;
	int SizeNum = Bool_Value.size();
	std::vector<bool>::iterator ValueIterator = Bool_Value.begin();
	for (int i = 0; i < SizeNum; ++i)
	{
		if (i != 0)
		{
			Result = Result + ",";
		}
		if (Bool_Value[i] == true)
		{
			Result = Result + "true";
		}
		else
		{
			Result = Result + "false";
		}
	}

	return Result;
}
