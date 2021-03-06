#include "SaveData.h"
#include "StringFormatter.h"

LoveEngine::Utilities::StringFormatter LoveEngine::Utilities::SaveData::readData(const std::string& _file)
{
	std::string dir = "./resources/savedata/" + _file + ".bin";
	FILE* fd;

	fopen_s(&fd, dir.c_str(), "r");

	if (fd == NULL)
	{
		std::cerr << "No existe el archivo: " << dir << "\n";
		return StringFormatter("");
	}

	int size;
	fread_s(&size, sizeof(int), sizeof(int), 1, fd);
	
	char* message = new char [size];
	fread_s(message, size, 1, size, fd);

	fclose(fd);

	std::string rawMessage = message;

	delete message;

	return StringFormatter(rawMessage);
}

void LoveEngine::Utilities::SaveData::saveData(const std::string& _file, const std::string& messageToSave)
{

	std::string dir = "./resources/savedata/" + _file + ".bin";
	FILE* fd;

	int i = fopen_s(&fd, dir.c_str(), "w");
	if (i != 0) {
		return;
	}

	int lenght = messageToSave.length() + 1 ;
	fwrite(&lenght, sizeof(int), 1, fd);
	fseek(fd, 0, SEEK_END);
	fwrite(messageToSave.c_str(), 1, lenght, fd);


	fclose(fd);
}
