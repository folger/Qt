#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QRegularExpression>
#include "make.h"

QString GetAbsFile(const QString& file)
{
	return "H:\\CheckCode\\Qt\\MakeProOrange\\" + file;
	//return file;
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

bool DoJob::Do(bool x64)
{
	if (!ReadInfos())
		return false;

	std::vector<QRegularExpression> patterns;
	for (auto info : infos_)
	{
		QString pattern = "0001:(\\w+)\\s+";
		pattern += QRegularExpression::escape(info.GetFunc(x64));
		patterns.push_back(QRegularExpression(pattern));
	}

	QString module = x64 ? "ok9_64" : "ok9";
	QFile mapfile(GetAbsFile(module + ".map"));
	if (!mapfile.open(QIODevice::ReadOnly))
	{
		qDebug() << mapfile.fileName() + " not found";
		return false;
	}

	std::vector<QString> addresses;
	QTextStream in(&mapfile);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		for (auto& re : patterns)
		{
			auto mm = re.match(line);
			if (mm.hasMatch())
			{
				addresses.push_back(mm.captured(1));
				break;
			}
		}
		if (addresses.size() == infos_.size())
			break;
	}
	mapfile.close();

	QString crackedFile(GetAbsFile(module + "_cracked" + ".dll"));
	QFile::remove(crackedFile);
	QFile::copy(GetAbsFile(module + ".dll"), crackedFile);
	QFile dllfile(crackedFile);
	dllfile.open(QIODevice::ReadWrite);
	for (size_t ii=0; ii<addresses.size(); ++ii)
	{
		qint64 pos = addresses[ii].toInt(nullptr, 16) + 0x400;
		dllfile.seek(pos);
		dllfile.write(infos_[ii].bytecodes.data(), infos_[ii].bytecodes.size());
	}
	dllfile.close();

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
		qDebug() << "infos.json not found";
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




