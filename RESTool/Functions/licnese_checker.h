#include "stdafx.h"
#include <WinInet.h>
#include <Windows.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#pragma comment(lib, "wininet.lib")

// ������� ��� �������� ������������� �����
bool verifyLicenseKey(const std::string& licenseKey, const std::string& appSecret)
{
    // ������������� WinINet
    HINTERNET hInternet = InternetOpenA("HTTP Request", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "Failed to initialize WinINet" << std::endl;
        cout << endl;
        cout << "Press Enter to exit..." << endl;
        getchar();
        return false;
    }

    std::string url = "https://keys2.patchkit.net/v2/keys/" + licenseKey + "?app_secret=" + appSecret;

    // �������� ����������
    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        std::cerr << "Failed to open URL" << std::endl;
        cout << endl;
        cout << "Press Enter to exit..." << endl;
        getchar();
        InternetCloseHandle(hInternet);
        return false;
    }

    // ��������� ���������� � ������� ������
    DWORD statusCode = 0;
    DWORD statusCodeSize = sizeof(statusCode);
    HttpQueryInfoA(hConnect, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, NULL);

    // �������� ������� ������
    bool isValid = (statusCode == HTTP_STATUS_OK);

    // �������� ���������� � ������������ �������� WinINet
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return isValid;
}