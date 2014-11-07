#ifndef __MAKE_H__
#define __MAKE_H__

#include <vector>
#include <functional>
#define INFO_FILE "infos.json"
class DoJob
{
public:
	DoJob();
	static bool InfoExists();
	static QString GetAbsFile(const QString& file);

	bool Do(bool x64, std::function<bool (size_t)> pfnCheckInfo = nullptr);
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

