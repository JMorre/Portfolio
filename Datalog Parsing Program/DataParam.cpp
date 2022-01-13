#include "DataParam.h"

DataParam::DataParam() { //

}

DataParam::~DataParam() { //

}

void DataParam::SetData(Token* NewData) {
	Data = *NewData;
}

std::string DataParam::ToString() const {
	return Data.ReturnString();
}

Token* DataParam::GetData() {
	return &Data;
}