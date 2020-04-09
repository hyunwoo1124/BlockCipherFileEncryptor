#include <string>
#include "CipherInterface.h"
#include "AES.h"
#include "DES.h"

#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "fstream"

using namespace std;

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
	 // Check the number of parameters is correct
	 if (argc < 6) {
			 // Tell the user how to run the program
			 std::cerr << "Usage: " << argv[0] << " <CIPHER NAME> <KEY> <ENC/DEC>" <<
			 " <INPUT FILE> <OUTPUT FILE>" << std::endl;
			 // close program because incorrect parameters
			 return 1;
	 }

	string ciphername = argv[1];
	// Since we are passiing const unsigned char* in the setKey function
	// We should also saving value as const unsigned char*
	// However, by doing this, we need to convert our input into it as well
	const unsigned char* key = (const unsigned char*)argv[2];
	string method = argv[3];
	string inputText = argv[4];
	string outputText = argv[5];

	// print out user input
	cout << "ciphername: " << ciphername << endl;
	cout << "key: " << key << endl;
	cout << "method: " << method << endl;
	cout << "inputText: " << inputText << endl;
	cout << "outputText: " << outputText << endl;

	// Read file
	FILE * file;
	unsigned char* textData = new unsigned char[16];
	file = fopen(inputText.c_str(), "rb");
	if (file == NULL) {
		cerr << "Error Occurred " << endl;
	}

	while (!feof(file)){
		fread(textData,sizeof(char*),16,file);
	}
	fclose(file);
	cout << "Element in the Array" << endl;
	for (int i = 0; i < 16; i++)
		cout << textData[i] << " ";
	cout << endl;

	CipherInterface* cipher = 0;

	if (ciphername == "AES") {
		cout << "Testing AES" << endl;
		cipher = new AES();
		unsigned char* output;
		unsigned char* outputdec;
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		if(!cipher->setKey((unsigned char*)key)){
				cerr << "Set Key error, code can't compile " << endl;
			}
		FILE * file;
		file = fopen(outputText.c_str(), "wb");
		if(method == "ENC"){
			output = cipher->encrypt((unsigned char*)textData);
			cout << "The encrypted text is: " << output << endl;
			fwrite(output, sizeof(char), 16,file);
		}
		else if(method == "DEC") {
			outputdec = cipher->decrypt((unsigned char*)textData);
			cout << "The decrypted text is: " << outputdec << endl;
			fwrite(outputdec, sizeof(char), 16,file);
		}
		else {
			cout << "Method is Unknown, please recheck your method" << endl;
			cout << "ENC for encryption" << endl;
			cout << "DEC for decryption" << endl;
		}
		fclose(file);

	}
	return 0;
}
