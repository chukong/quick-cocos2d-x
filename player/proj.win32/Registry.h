//////////////////////////////////////////////////////////////////////
// Copyright 2010 Putta Khunchalee
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//////////////////////////////////////////////////////////////////////

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#include <string>
#include "stdafx.h"

using namespace std;

class CRegistry
{
public: // Constructor/Destructor
	CRegistry(HKEY hRoot, PCWSTR pszSubKey, REGSAM samDesired = KEY_ALL_ACCESS, bool blCreateIfNotExist = true) throw(...);
	CRegistry(HKEY hRoot, PCSTR pszSubKey, REGSAM samDesired = KEY_ALL_ACCESS, bool blCreateIfNotExist = true) throw(...);
	CRegistry(const CRegistry& that) throw(...);
	virtual ~CRegistry() throw();
public: // Modify Data Operator
	CRegistry& __fastcall operator= (const CRegistry& that) throw(...);
public: // Write Value Method
	DWORD WriteBinaryValue(LPCVOID lpValue, DWORD dwLength, PCWSTR pszValueName = NULL) const throw();
	DWORD WriteBinaryValue(LPCVOID lpValue, DWORD dwLength, PCSTR pszValueName = NULL) const throw();
	DWORD WriteDoubleWordValue(DWORD dwValue, PCWSTR pszValueName = NULL) const throw();
	DWORD WriteDoubleWordValue(DWORD dwValue, PCSTR pszValueName = NULL) const throw();
	DWORD WriteStringValue(PCWSTR pszValue, PCWSTR pszValueName = NULL) const throw();
	DWORD WriteStringValue(PCSTR pszValue, PCSTR pszValueName = NULL) const throw();
public: // Read Value Method
	DWORD ReadBinaryValue(LPVOID lpValue, DWORD dwSize, PCWSTR pszValueName = NULL, PDWORD pType = NULL) const throw();
	DWORD ReadBinaryValue(LPVOID lpValue, DWORD dwSize, PCSTR pszValueName = NULL, PDWORD pType = NULL) const throw();
	DWORD ReadDoubleWordValue(PDWORD pValue, PCWSTR pszValueName = NULL, PDWORD pType = NULL) const throw();
	DWORD ReadDoubleWordValue(PDWORD pValue, PCSTR pszValueName = NULL, PDWORD pType = NULL) const throw();
	DWORD ReadStringValue(std::wstring& strValue, PCWSTR pszValueName = NULL, PDWORD pType = NULL) const throw();
	DWORD ReadStringValue(std::string& strValue, PCSTR pszValueName = NULL, PDWORD pType = NULL) const throw();
protected: // Registry Key Handle
	HKEY	m_hKey;
	HKEY	m_hUser;
};

#endif /* _REGISTRY_H_ */
