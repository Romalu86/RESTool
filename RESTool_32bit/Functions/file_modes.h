#ifndef FILE_MODES_H
#define FILE_MODES_H

#include <QString>

class FileUnpacker
{
public:
	static void processFileUnpackMode(const QString& resFilename, const QString& mode, bool alternativeModeEnabled);
};

#endif