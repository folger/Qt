#ifndef __MAKE_H__
#define __MAKE_H__

#include <vector>
#define INFO_FILE "infos.json"
class DoJob
{
public:
	DoJob();
	static bool InfoExists();

	bool Do(bool x64);
	bool GetFuncNames(std::vector<QString>& names);

private:
	bool ReadInfos();

	struct Info
	{
		QString& GetFunc(bool x64) { return x64 ? ok9_64_func : ok9_func; }
		QString ok9_func;
		QString ok9_64_func;
		std::vector<char> bytecodes;
	};
	std::vector<Info> infos_;

	char inforead_;
};

#endif /// __MAKE_H__

