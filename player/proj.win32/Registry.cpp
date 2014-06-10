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

#include "stdafx.h"
#include "Registry.h"

//////////////////////////////////////////////////////////////////////
// Utilities Function (private)
//////////////////////////////////////////////////////////////////////

static void __fastcall GetSystemErrorMessage(DWORD dwError, std::string& strRecvMsg)
{
	PSTR pszError;

	if (FormatMessageA(FORMAT_MESSAGE_MAX_WIDTH_MASK | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, reinterpret_cast<PSTR>(&pszError), 256, NULL))
	{
		strRecvMsg = pszError;
		LocalFree(pszError);
	}
	else
	{
		char szError[sizeof("Unknown Error (%u)") + 64];

		sprintf(szError, "Unknown Error (%u)", dwError);

		strRecvMsg = szError;
	}
}

//////////////////////////////////////////////////////////////////////
// Constructor/Destructor
//////////////////////////////////////////////////////////////////////

CRegistry::CRegistry(HKEY hRoot, PCWSTR pszSubKey, REGSAM samDesired, bool blCreateIfNotExist) : m_hKey(NULL), m_hUser(NULL)
{
	LONG nRet;

	// Check Parameter
	if (!hRoot)
		throw std::invalid_argument("hRoot is not a valid Registry Key Handle");
	if (!pszSubKey)
		throw std::invalid_argument("pszSubKey is a NULL Pointer");

	// Check hRoot
	if (HKEY_CURRENT_USER == hRoot)
	{
		nRet = ::RegOpenCurrentUser(KEY_ALL_ACCESS, &m_hUser);

		if (nRet != ERROR_SUCCESS)
		{
			std::string strError, strMsg;

			// Get Error Message
			::GetSystemErrorMessage(nRet, strError);

			// Generate Error Message
			strMsg = "Couldn't open a Registry Key HKEY_CURRENT_USER. ";
			strMsg += strError;

			throw std::runtime_error(strError);
		}
		
		hRoot = m_hUser;
	}

	// Open Key
	if (blCreateIfNotExist)
		nRet = ::RegCreateKeyExW(hRoot, pszSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, samDesired, NULL, &m_hKey, NULL);
	else
		nRet = ::RegOpenKeyExW(hRoot, pszSubKey, 0, samDesired, &m_hKey);

	if (nRet != ERROR_SUCCESS)
	{
		std::string strError, strMsg;

		// Get Error Message
		::GetSystemErrorMessage(nRet, strError);

		// Generate Error Message
		strMsg = "Couldn't open or create a Registry Key. ";
		strMsg += strError;

		throw std::runtime_error(strError);
	}
}

CRegistry::CRegistry(HKEY hRoot, PCSTR pszSubKey, REGSAM samDesired, bool blCreateIfNotExist) :m_hKey(NULL), m_hUser(NULL)
{
	LONG nRet;

	// Check Parameter
	if (!hRoot)
		throw std::invalid_argument("hRoot is not a valid Registry Key Handle");
	if (!pszSubKey)
		throw std::invalid_argument("pszSubKey is a NULL Pointer");

	// Check hRoot
	if (HKEY_CURRENT_USER == hRoot)
	{
		nRet = ::RegOpenCurrentUser(KEY_ALL_ACCESS, &m_hUser);

		if (nRet != ERROR_SUCCESS)
		{
			std::string strError, strMsg;

			// Get Error Message
			::GetSystemErrorMessage(nRet, strError);

			// Generate Error Message
			strMsg = "Couldn't open a Registry Key HKEY_CURRENT_USER. ";
			strMsg += strError;

			throw std::runtime_error(strError);
		}

		hRoot = m_hUser;
	}

	// Open Key
	if (blCreateIfNotExist)
		nRet = ::RegCreateKeyExA(hRoot, pszSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, samDesired, NULL, &m_hKey, NULL);
	else
		nRet = ::RegOpenKeyExA(hRoot, pszSubKey, 0, samDesired, &m_hKey);

	if (nRet != ERROR_SUCCESS)
	{
		std::string strError, strMsg;

		// Get Error Message
		::GetSystemErrorMessage(nRet, strError);

		// Generate Error Message
		strMsg = "Couldn't open or create a Registry Key. ";
		strMsg += strError;

		throw std::runtime_error(strError);
	}
}

CRegistry::CRegistry(const CRegistry& that) : m_hKey(NULL), m_hUser(NULL)
{
	try
	{
		*this = that;
	}
	catch (...)
	{
		// Re-throw an exception
		throw;
	}
}

CRegistry::~CRegistry()
{
	// Close Key Handle
	if (m_hKey)
		::RegCloseKey(m_hKey);
	if (m_hUser)
		::RegCloseKey(m_hUser);
}

//////////////////////////////////////////////////////////////////////
// Modify Data Operator (public)
//////////////////////////////////////////////////////////////////////

CRegistry& CRegistry::operator= (const CRegistry& that)
{
	HANDLE	hProcess;

	hProcess = ::GetCurrentProcess();

	// Reset var
	::RegCloseKey(m_hKey);
	::RegCloseKey(m_hUser);

	m_hKey	= NULL;
	m_hUser	= NULL;

	// Duplicate Registry Handle
	if (that.m_hKey && !::DuplicateHandle(hProcess, that.m_hKey, hProcess, reinterpret_cast<PHANDLE>(&m_hKey), 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		std::string strError, strMsg;

		// Get Error Message
		::GetSystemErrorMessage(::GetLastError(), strError);

		// Generate Error Message
		strMsg = "Unable to duplicate m_hKey Handle. ";
		strMsg += strError;

		throw std::runtime_error(strError);
	}

	if (that.m_hUser && !::DuplicateHandle(hProcess, that.m_hUser, hProcess, reinterpret_cast<PHANDLE>(&m_hUser), 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		std::string strError, strMsg;

		// Get Error Message
		::GetSystemErrorMessage(::GetLastError(), strError);

		// Generate Error Message
		strMsg = "Unable to duplicate m_hUser Handle. ";
		strMsg += strError;

		throw std::runtime_error(strError);
	}

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Write Value Method (public)
//////////////////////////////////////////////////////////////////////

DWORD CRegistry::WriteBinaryValue(LPCVOID lpValue, DWORD dwLength, PCWSTR pszValueName) const
{
	return ::RegSetValueExW(m_hKey, pszValueName, 0, REG_BINARY, reinterpret_cast<const BYTE*>(lpValue), dwLength);
}

DWORD CRegistry::WriteBinaryValue(LPCVOID lpValue, DWORD dwLength, PCSTR pszValueName) const
{
	return ::RegSetValueExA(m_hKey, pszValueName, 0, REG_BINARY, reinterpret_cast<const BYTE*>(lpValue), dwLength);
}

DWORD CRegistry::WriteDoubleWordValue(DWORD dwValue, PCWSTR pszValueName) const
{
	return ::RegSetValueExW(m_hKey, pszValueName, 0, REG_DWORD, reinterpret_cast<LPBYTE>(&dwValue), sizeof(DWORD));
}

DWORD CRegistry::WriteDoubleWordValue(DWORD dwValue, PCSTR pszValueName) const
{
	return ::RegSetValueExA(m_hKey, pszValueName, 0, REG_DWORD, reinterpret_cast<LPBYTE>(&dwValue), sizeof(DWORD));
}

DWORD CRegistry::WriteStringValue(PCWSTR pszValue, PCWSTR pszValueName) const
{
	if (!pszValue)
		return ERROR_INVALID_PARAMETER;

	return ::RegSetValueExW(m_hKey, pszValueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(pszValue), (wcslen(pszValue) + 1) * sizeof(WCHAR));
}

DWORD CRegistry::WriteStringValue(PCSTR pszValue, PCSTR pszValueName) const
{
	if (!pszValue)
		return ERROR_INVALID_PARAMETER;

	return ::RegSetValueExA(m_hKey, pszValueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(pszValue), strlen(pszValue) + 1);
}

//////////////////////////////////////////////////////////////////////
// Read Value Method (public)
//////////////////////////////////////////////////////////////////////

DWORD CRegistry::ReadBinaryValue(LPVOID lpValue, DWORD dwSize, PCWSTR pszValueName, PDWORD pType) const
{
	return ::RegQueryValueExW(m_hKey, pszValueName, NULL, pType, reinterpret_cast<LPBYTE>(lpValue), &dwSize);
}

DWORD CRegistry::ReadBinaryValue(LPVOID lpValue, DWORD dwSize, PCSTR pszValueName, PDWORD pType) const
{
	return ::RegQueryValueExA(m_hKey, pszValueName, NULL, pType, reinterpret_cast<LPBYTE>(lpValue), &dwSize);
}

DWORD CRegistry::ReadDoubleWordValue(PDWORD pValue, PCWSTR pszValueName, PDWORD pType) const
{
	DWORD dwSize = sizeof(DWORD);

	return ::RegQueryValueExW(m_hKey, pszValueName, NULL, pType, reinterpret_cast<LPBYTE>(pValue), &dwSize);
}

DWORD CRegistry::ReadDoubleWordValue(PDWORD pValue, PCSTR pszValueName, PDWORD pType) const
{
	DWORD dwSize = sizeof(DWORD);

	return ::RegQueryValueExA(m_hKey, pszValueName, NULL, pType, reinterpret_cast<LPBYTE>(pValue), &dwSize);
}

DWORD CRegistry::ReadStringValue(std::wstring& strValue, PCWSTR pszValueName, PDWORD pType) const
{
	DWORD	dwSize, dwRet;
	PWSTR	pszValue;
	HANDLE	hHeap;

	// Determine data size
	dwRet = ::RegQueryValueExW(m_hKey, pszValueName, NULL, pType, NULL, &dwSize);
	if (dwRet != ERROR_SUCCESS)
		return dwRet;

	// Alloc buffer
	hHeap		= ::GetProcessHeap();
	pszValue	= reinterpret_cast<PWSTR>(::HeapAlloc(hHeap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, dwSize + sizeof(WCHAR)));

	// Read value
	dwRet = ::RegQueryValueExW(m_hKey, pszValueName, NULL, pType, reinterpret_cast<LPBYTE>(pszValue), &dwSize);

	if (ERROR_SUCCESS == dwRet)
		strValue = pszValue;

	// Free buffer
	::HeapFree(hHeap, 0, pszValue);

	return dwRet;
}

DWORD CRegistry::ReadStringValue(std::string& strValue, PCSTR pszValueName, PDWORD pType) const
{
	DWORD	dwSize, dwRet;
	PSTR	pszValue;
	HANDLE	hHeap;

	// Determine data size
	dwRet = ::RegQueryValueExA(m_hKey, pszValueName, NULL, pType, NULL, &dwSize);
	if (dwRet != ERROR_SUCCESS)
		return dwRet;

	// Alloc buffer
	hHeap		= ::GetProcessHeap();
	pszValue	= reinterpret_cast<PSTR>(::HeapAlloc(hHeap, HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, dwSize + 1));

	// Read value
	dwRet = ::RegQueryValueExA(m_hKey, pszValueName, NULL, pType, reinterpret_cast<LPBYTE>(pszValue), &dwSize);

	if (ERROR_SUCCESS == dwRet)
		strValue = pszValue;

	// Free buffer
	::HeapFree(hHeap, 0, pszValue);

	return dwRet;
}
