#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QRegularExpression>
#include <QMessageBox>
#include "make.h"

QString DoJob::GetAbsFile(const QString& file)
{
	//return "H:\\CheckCode\\Qt\\MakeProOrange\\" + file;
	return file;
}

DoJob::DoJob() : inforead_(-1)
{
}

bool DoJob::InfoExists()
{
	return QFile::exists(GetAbsFile(INFO_FILE));
}

bool DoJob::GetFuncNames(std::vector<QString>& names)
{
	if (!ReadInfos())
		return false;

	names.reserve(infos_.size());
	for (auto& info : infos_)
	{
		auto func = info.GetFunc(false);
		func.remove(0, 1);
		auto posAt = func.indexOf('@');
		names.push_back(func.left(posAt));
	}
	return true;
}

bool DoJob::Do(bool x64, std::function<bool (size_t)> pfnCheckInfo/* = nullptr*/)
{
	if (!ReadInfos())
		return false;

	QString module = x64 ? "ok9_64" : "ok9";
	QFile mapfile(GetAbsFile(module + ".map"));
	if (!mapfile.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(nullptr, "Error", mapfile.fileName() + " is missing");
		return false;
	}
	QString dll(GetAbsFile(module + ".dll"));
	if (!QFile::exists(dll))
	{
		QMessageBox::information(nullptr, "Error", dll + " is missing");
		return false;
	}

	std::vector<QRegularExpression> patterns;
	std::vector<std::vector<char>> bytecodes;
	for (size_t ii=0; ii<infos_.size(); ++ii)
	{
		if (pfnCheckInfo && !pfnCheckInfo(ii))
			continue;
		auto& info = infos_[ii];
		QString pattern = "0001:(\\w+)\\s+";
		pattern += QRegularExpression::escape(info.GetFunc(x64));
		patterns.push_back(QRegularExpression(pattern));
		bytecodes.push_back(info.bytecodes);
	}

	std::vector<QString> addresses;
	std::vector<std::vector<char>> bytecodes2;
	QTextStream in(&mapfile);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		for (size_t ii=0; ii<patterns.size(); ++ii)
		{
			auto mm = patterns[ii].match(line);
			if (mm.hasMatch())
			{
				addresses.push_back(mm.captured(1));
				bytecodes2.push_back(bytecodes[ii]);
				patterns.erase(patterns.begin() + ii);
				bytecodes.erase(bytecodes.begin() + ii);
				break;
			}
		}
	}
	mapfile.close();

	QString crackedFile(GetAbsFile(module + "_cracked" + ".dll"));
	QFile::remove(crackedFile);
	QFile::copy(dll, crackedFile);
	QFile dllfile(crackedFile);
	dllfile.open(QIODevice::ReadWrite);
	for (size_t ii=0; ii<addresses.size(); ++ii)
	{
		qint64 pos = addresses[ii].toInt(nullptr, 16) + 0x400;
		dllfile.seek(pos);
		dllfile.write(bytecodes2[ii].data(), bytecodes2[ii].size());
	}
	dllfile.close();
	QMessageBox::information(nullptr, "Message", crackedFile + "is generated");

	return true;
}

bool DoJob::ReadInfos()
{
	if (inforead_ != -1)
		return inforead_;

	inforead_ = 0;
	QFile loadFile(GetAbsFile(INFO_FILE));
	if (!loadFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(nullptr, "Error", GetAbsFile(INFO_FILE) + " is missing");
		return false;
	}

	QJsonDocument doc(QJsonDocument::fromJson(loadFile.readAll()));
	const QJsonObject& json = doc.object();

	QJsonArray ok9_funcs = json["ok9"].toArray();
	QJsonArray ok9_64_funcs = json["ok9_64"].toArray();
	QJsonArray bytecodes = json["bcodes"].toArray();
	int size = ok9_funcs.size();
	if (size == ok9_64_funcs.size() && size == bytecodes.size())
	{
		infos_.resize(size);
		for (int ii=0; ii<size; ++ii)
		{
			auto& info = infos_[ii];
			info.ok9_func = ok9_funcs[ii].toString();
			info.ok9_64_func = ok9_64_funcs[ii].toString();

			QJsonArray codes = bytecodes[ii].toArray();
			info.bytecodes.resize(codes.size());
			for (int jj=0; jj<codes.size(); ++jj)
			{
				info.bytecodes[jj] = codes[jj].toString().toInt(nullptr, 16);
			}
		}
		inforead_ = 1;
		return true;
	}
	return false;
}




