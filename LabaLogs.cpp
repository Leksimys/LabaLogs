#include <iostream>
#include <regex>
#include <filesystem>
#include <fstream>

using namespace std;

namespace fs = filesystem;

int main()
{
	int chekDevice = 0;
	string fileName;
	cout << "Device name: ";
	cin >> fileName;
	if (fileName == "^" || fileName == "_" || fileName == "?" || fileName == "$" ||  fileName == "*" || fileName == "(" || fileName == ")" ||  fileName == "+" || fileName == ":")
	{
		cout << "Unknown character entered" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cmatch result;
		regex regular("garbage");
		if (regex_search(fileName.c_str(), result, regular))
		{
			cout << "" << endl;
			system("pause");
			return 0;
		}
	}
	for (auto& p : fs::directory_iterator("logs"))
	{
		string dock;
		fstream dockRead(p.path(), std::ios::in);
		while (getline(dockRead, dock))
		{
			cmatch result;
			regex regular("([\\d]+)""(:)""(.+)""(:)""([\\d]+)");
			if (regex_search(dock.c_str(), result, regular))
			{
				if (result[3] == fileName)
				{
					chekDevice++;
					string path = p.path().string();
					cmatch resultPath;
					regex regPath("(log_)""(.)""(.+)""([\\s])""(.+)""([)])""(.txt)");
					if (regex_search(path.c_str(), resultPath, regPath))
					{
						cout << "date: " << resultPath[3] << " time: " << resultPath[5] << "-";
					}
				
					cmatch result;
					regex regular("([\\d]+)""(:)""(.+)""(:)""([\\d]+)");
					if (regex_search(dock.c_str(), result, regular))
					{
						cout << result[1] << "  " << result[3] << "  " << "result: " << result[5] << endl;
					}
				}
			}

		}
		dockRead.close();
	}
	if (chekDevice == 0)
		cout << "Device not found\n";
	system("pause");
	return 0;
}