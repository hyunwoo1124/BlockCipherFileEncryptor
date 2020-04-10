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
	unsigned int size = 0;
	file = fopen(inputText.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	size = ftell(file);

	unsigned char* textData;
	if (file == NULL) {
		cerr << "Error Occurred " << endl;
	}

	// Saving file data char by char into textData 
	while (!feof(file)){
		fread(textData,sizeof(char),size,file);
	}

	// Close file after finish reading
	fclose(file);

	//Print out element of the array to make sure we saved correctly
	cout << "Element in the Array" << endl;
	for (int i = 0; i < 16; i++)
		cout << textData[i] << " ";
	cout << endl;

	// Initializing cipher
	CipherInterface* cipher = 0;

	// Checking if method is AES or DES 
	// if (ciphername == "AES") {
	// 	// Create an instance of AES
	// 	cout << "Testing AES" << endl;
	// 	cipher = new AES();

	// 	// Creating two temp variable to store encrypted and decrypted text 
	// 	unsigned char* outputEnc;
	// 	unsigned char* outputDec;
		
	// 	// Check if cipher is successfully created
	// 	if(!cipher)
	// 	{
	// 		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
	// 		__FILE__, __FUNCTION__, __LINE__);
	// 		exit(-1);
	// 	}

	// 	// Set key will check whether the key is for encryption or decryptiion
	// 	if(!cipher->setKey((unsigned char*)key)){
	// 			cerr << "Set Key error, code can't compile " << endl;
	// 		}
		
	// 	// Write to a file 
	// 	FILE * file;
	// 	file = fopen(outputText.c_str(), "wb");
	// 	// Check if it is encrypt method
	// 	if(method == "ENC"){
	// 		outputEnc = cipher->encrypt((unsigned char*)textData);
	// 		cout << "The encrypted text is: " << outputEnc << endl;
	// 		fwrite(outputEnc, sizeof(char), 16,file);
	// 	}
	// 	// Check if it is decrypt method
	// 	else if(method == "DEC") {
	// 		outputDec = cipher->decrypt((unsigned char*)textData);
	// 		cout << "The decrypted text is: " << outputDec << endl;
	// 		fwrite(outputDec, sizeof(char), 16,file);
	// 	}
	// 	// If user choose something else
	// 	else {
	// 		cout << "Method is Unknown, please recheck your method" << endl;
	// 		cout << "ENC for encryption" << endl;
	// 		cout << "DEC for decryption" << endl;
	// 	}
	// 	// Close file after finish writing
	// 	fclose(file);

	// } else if (ciphername == "DES") {
	// 	cout << "Testing DES" << endl;
	// 	cipher = new DES();
	// 	if(!cipher) {
	// 		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
	// 	  __FILE__,__FUNCTION__,__LINE__);
	// 		exit(-1);
	// 	}

	// 	if (method == "ENC"){
	// 		cout << "ENCODE" << endl;
	// 		//TODO: Add ENC DES here
	// 	} else if (method == "DEC") {
	// 		cout << "DECODE" << endl;
	// 		//TODO: Add DEC DES here
	// 	} else {
	// 		cout << "Method is Unknown, please recheck your method" << endl;
	// 		cout << "ENC for encryption" << endl;
	// 		cout << "DEC for decryption" << endl;
	// 	}
 	// }

	return 0;
}
