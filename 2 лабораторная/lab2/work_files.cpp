#include "lab-2.hpp"
//#include "../lab-3/lab_3.hpp"

void write_enc(string file_name, long long *enc, uint64_t length)
{
	ofstream file;
	file.open(file_name, ios::binary);

	//file << length << " ";
	for(uint64_t i = 0; i < length; ++i) {
		file << enc[i] << " ";
	}

	file.close();
}

void write_dec(string file_name, long long *dec, uint64_t length)
{
	ofstream file;
	file.open(file_name, ios::binary);

	for(uint64_t i = 0; i < length; ++i) {
		file << (char)dec[i];
        //cout << (char)dec[i] << endl;
	}

	file.close();
}

string read_dec(string file_name)
{
	ifstream file;
	file.open(file_name, ios::binary);
	stringstream buffer;
	buffer << file.rdbuf();

	file.close();
	return buffer.str();
}

long long *read_enc(string file_name, uint64_t *length)
{
	ifstream file;
	file.open(file_name);

	file >> *length;
	long long *enc = new long long [*length];

	for(uint64_t i = 0; i < *length; ++i) {
		file >> enc[i];
	}
	file.close();

	return enc;
}
