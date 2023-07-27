#include <sstream>
#include <QFile>
#include <QMessageBox>

// File Functions

int ReadByte(FILE* file)
{
	char number;
	fread(&number, 1, 1, file);
	return number;
}

int ReadInt(FILE* file)
{
	int number;
	fread(&number, 1, 4, file);
	return number;
}

float ReadFloat(FILE* file)
{
	float number;
	fread(&number, 1, sizeof(float), file);
	return number;
}

// Name & VidName strings function
char* ReadString(FILE* file, FILE* out, const char* name)
{
	char buffer[4096];
	int stringsize = 0;
	fread(buffer, sizeof(char), sizeof(buffer) - 1, file);

	for (int i = 0; i < sizeof(buffer) - 1; ++i)
	{
		stringsize++;
		if (buffer[i] == 0x00)
		{
			fseek(file, ftell(file) - (sizeof(buffer) - 1) + stringsize, SEEK_SET);
			break;
		}
	}

	char* result = (char*)malloc((stringsize + 1) * sizeof(char));
	memcpy(result, buffer, stringsize);
	result[stringsize] = '\0';

	fprintf(out, "%s=%s\n", name, buffer);

	return result;
}

// SFX & ForceFeedback strings function
std::string ReadStringNoRTN(FILE* file) {
	int stringsize = 0;
	char ch;
	std::string buffer;

	while (fread(&ch, sizeof(char), 1, file) == 1) {
		if (ch == 0x00) {
			break;
		}
		buffer += ch;
		stringsize++;
	}

	return buffer;
}

// Function to read a specified number of lines from a file and generate a string with the paths
std::string readPathsFromFile(FILE* file, int numStrings) {
	std::vector<std::string> paths;
	std::string path;

	// Read a specified number of lines for file paths
	for (int i = 0; i < numStrings; ++i) {
		if (!feof(file)) {
			path = ReadStringNoRTN(file);
			paths.push_back(path);
		}
	}

	// Generate a string with file paths
	std::string buffer;
	for (const std::string& p : paths) {
		buffer += p + " ";
	}

	return buffer;
}

// Copy Header to Output files function
void copyFileContent(const QString& sourceFilename, const QString& destinationFilename) {
	QFile sourceFile(sourceFilename);
	QFile destinationFile(destinationFilename);

	if (!sourceFile.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
		QMessageBox::critical(nullptr, "Error", "Failed to open source file:\n" + sourceFilename + "\n\nPlease check your program installation. Make sure the 'data' folder and required files are present.");
		return;
	}

	if (!destinationFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered)) {
		QMessageBox::critical(nullptr, "Error", "Failed to open destination file:\n" + destinationFilename + "\n\nPlease check file permissions in the directory.");
		return;
	}

	QByteArray data = sourceFile.readAll();
	destinationFile.write(data);

	sourceFile.close();
	destinationFile.close();
}

// Working with float`s
std::string processFloatValues(const float* arrayf, int numValues, bool useTabulation = true)
{
	std::vector<std::string> values;
	for (int i = 0; i < numValues; ++i)
	{
		std::string str = std::to_string(arrayf[i]);
		str.erase(str.find_last_not_of('0') + 1, std::string::npos);
		str.erase(str.find_last_not_of('.') + 1, std::string::npos);
		values.push_back(str);
	}

	std::ostringstream oss;
	for (const auto& value : values)
	{
		if (useTabulation)
			oss << value << "\t";
		else
			oss << value << " ";
	}

	std::string formattedResult = oss.str();
	formattedResult.pop_back(); // Delete last tabulation or space

	return formattedResult;
}

// Working with int`s
std::string processIntValues(const int* arrayi, int numValues, bool useTabulation = true)
{
	std::ostringstream oss;
	for (int i = 0; i < numValues; ++i)
	{
		if (useTabulation)
			oss << arrayi[i] << "\t";
		else
			oss << arrayi[i] << " ";
	}

	std::string formattedResult = oss.str();
	formattedResult.pop_back(); // Delete last tabulation or space

	return formattedResult;
}
// End of File Functions