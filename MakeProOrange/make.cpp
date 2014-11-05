#include <iostream>
#include <fstream>
#include <vector>

static bool cracked(const char* module)
{
    //std::vector<std::regex> patterns;
    //for (auto func : funcs)
	//{
		//std::string pattern = "0001:(\\w+)\\s+";
		//pattern += func;
		//patterns.push_back(std::regex(pattern));
	//}

	std::ifstream mapfile(std::string(module) + ".map");
	if (!mapfile.is_open())
	{
		std::cout << "map file not found" << std::endl;
		return false;
	}

	std::vector<std::string> addresses;
	std::string oneline;
	while (std::getline(mapfile, oneline))
	{
		//for (auto& pattern : patterns)
		//{
			//std::smatch mm;
			//if (std::regex_search(oneline, mm, pattern))
			//{
				//addresses.push_back(mm[1].str());
				//break;
			//}
		//}
	}
    mapfile.close();

	for (auto& address : addresses)
	{
		std::cout << address << std::endl;
	}

	return true;
}

int main()
{
	cracked("ok9") && cracked("ok9");
	return 0;
}

