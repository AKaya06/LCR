#pragma once
#include "Exception.h"

#define JSON_MEMCHECK_EXISTS(___jsonObject, ___memberName) if (!___jsonObject.contains(___memberName)) { throw Exception(QString("JSON Object member \"") + ___memberName + "\" is missing"); }
#define JSON_MEMCHECK_TYPE(___jsonObject, ___memberName, ___memberType) if (!___jsonObject[___memberName].is##___memberType()) { throw Exception(QString("JSON Object member \"") + ___memberName + "\" is not a " #___memberType); } 
#define JSON_MEMCHECK(___jsonObject, ___memberName, ___memberType) JSON_MEMCHECK_EXISTS(___jsonObject, ___memberName); JSON_MEMCHECK_TYPE(___jsonObject, ___memberName, ___memberType)

#define JSON_ARRAYCHECK_TYPE(___jsonArray, ___arrayIndex, ___memberType) if (!___jsonArray[___arrayIndex].is##___memberType()) { throw Exception(QString("JSON Array entry at index \"") + QString::number(___arrayIndex) + "\" is not a " #___memberType); } 