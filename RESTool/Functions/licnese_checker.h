#pragma once
#include "stdafx.h"
#include <WinInet.h>
#include <Windows.h>

#pragma comment(lib, "wininet.lib")

bool verifyLicenseKey(const std::string& licenseKey, const std::string& appSecret)
{
    HINTERNET hInternet = InternetOpenA("HTTP Request", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "Failed to initialize WinINet" << std::endl;
        cout << endl;
        cout << "Press Enter to exit..." << endl;
        getchar();
        exit(1);
    }

    std::string url = "https://keys2.patchkit.net/v2/keys/" + licenseKey + "?app_secret=" + appSecret;

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        std::cerr << "Failed to open URL" << std::endl;
        cout << endl;
        cout << "Press Enter to exit..." << endl;
        getchar();
        InternetCloseHandle(hInternet);
        exit(1);
    }

    DWORD statusCode = 0;
    DWORD statusCodeSize = sizeof(statusCode);
    HttpQueryInfoA(hConnect, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, NULL);

    bool isValid = (statusCode == HTTP_STATUS_OK);

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return isValid;
}

    void checkLicenseKey()
    {
        std::string licenseKey;
        std::ifstream licenseFile("license.key");
        if (licenseFile.is_open())
        {
            std::string line;
            while (std::getline(licenseFile, line))
            {
                if (line.find("licensekey=") == 0)
                {
                    licenseKey = line.substr(11);
                    break;
                }
            }
            licenseFile.close();
        }

        if (licenseKey.empty())
        {
            std::cerr << "License key not found. Contact the author of the program for details." << std::endl;
            std::cout << std::endl;
            std::cout << "Press Enter to exit..." << std::endl;
            std::getchar();
            exit(1);
        }

        std::string appSecret = "";  // AppSecret

        if (!verifyLicenseKey(licenseKey, appSecret))
        {
            std::cerr << "Invalid or blocked license key. Contact the author of the program for details." << std::endl;
            std::cout << std::endl;
            std::cout << "Press Enter to exit..." << std::endl;
            std::getchar();
            exit(1);
        }
    }
