#include <iostream>
#include <windows.h>
#include <io.h>
#include <dxgi1_6.h>
#include <fcntl.h>
using namespace std;

static string wide_to_utf8(const wstring &w) {
    if (w.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), s.data(), n, nullptr, nullptr);
    return s;
}

int printSystemInfo() {
    char computerName[MAX_COMPUTERNAME_LENGTH + 1] = {0}; // 初始化为 0
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
    if (GetComputerNameA(computerName, &size)) {
        cout << computerName << endl;
    } else {
        cerr << "GetComputerNameA failed, error: " << GetLastError() << endl;
    }

    wchar_t userName[256] = {0};
    DWORD userNameSize = static_cast<DWORD>(sizeof(userName) / sizeof(wchar_t)); // 单位：字符数
    if (GetUserNameW(userName, &userNameSize)) {
        _setmode(_fileno(stdout), _O_U16TEXT);
        wcout << L"用户名: " << userName << endl;
    } else {
        cerr << "GetUserNameW failed, error: " << GetLastError() << endl;
    }

    return 0;
};

int getGraphInfo() {
    IDXGIFactory4 *factory = nullptr;
    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr)) {
        cerr << "CreateDXGIFactory1 failed: 0x" << hex << hr << endl;
        return 1;
    }

    UINT i = 0;
    IDXGIAdapter1 *adapter = nullptr;
    while (factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND) {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        wstring wdesc(desc.Description);
        string name = wide_to_utf8(wdesc);

        cout << "Adapter " << i << ": " << name << "\n";
        cout << "  VendorId: 0x" << hex << desc.VendorId
                  << "  DeviceId: 0x" << desc.DeviceId << dec << "\n";
        cout << "  DedicatedVideoMemory: " << (desc.DedicatedVideoMemory / 1024 / 1024) << " MB\n";
        cout << "  DedicatedSystemMemory: " << (desc.DedicatedSystemMemory / 1024 / 1024) << " MB\n";
        cout << "  SharedSystemMemory: " << (desc.SharedSystemMemory / 1024 / 1024) << " MB\n";
        cout << "  Flags: " << desc.Flags << "\n\n";

        adapter->Release();
        ++i;
    }

    factory->Release();
    return 1;
};

int main() {
    getGraphInfo();
	printSystemInfo();
    // cin.get();
}