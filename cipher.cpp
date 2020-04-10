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

	unsigned char* textData = new unsigned char[8];

	// Read file
	FILE * fileRead;
	fileRead = fopen(inputText.c_str(), "rb");
	if (fileRead == NULL) {
		cerr << "Error Occurred " << endl;
	}
		
	// Write to a file 
	FILE * fileWrite;
	fileWrite = fopen(outputText.c_str(), "wb");
	if (fileWrite == NULL) {
		cerr << "Error Occurred " << endl;
	}

	// Initializing cipher
	CipherInterface* cipher = NULL;

	// Checking if method is AES or DES 
	// Checking if method is AES or DES 
	if (ciphername == "AES") {
		// Create an instance of AES
		cout << "Testing AES" << endl;
		cipher = new AES();

		// Creating a new key with a byte in front to determine encrypt and decrypt
		size_t size = int(*key);
		unsigned char* newKey = new unsigned char[size+1];
		if (method == "ENC"){
			newKey[0] = '0';
			for (int i = 0; i < size; i++)
				newKey[i+1] = key[i];
		}
		else{
			newKey[0] = '1';
			for (int i = 0; i < size; i++)
				newKey[i+1] = key[i];
		}
		
		cout << "New Key: " << newKey << endl;

		// Check if cipher is successfully created
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		// Creating two temp variable to store encrypted and decrypted text 
		unsigned char* processText;
		textData = new unsigned char[16];

		// Set key will check whether the key is for encryption or decryptiion
		if(!cipher->setKey((unsigned char*)newKey)){
			cerr << "Set Key error, code can't compile " << endl;
		}

		unsigned int numRead = 0;
		// Check if it is encrypt method
		if(method == "ENC"){
			// Saving file data char by char into textData 
			while (!feof(fileRead)){
				numRead = fread(textData,sizeof(char),16,fileRead);
				// Padding, If the plaintext is not 16 bytes, fill in empty with 0
				if(numRead != 0) {
					if (numRead != 16 ){
						for (int i = numRead; i < 16; i++){
							textData[i] = '0';
						}
					} 
					processText = cipher->encrypt(textData);
					fwrite(processText, sizeof(char), 16,fileWrite);
					cout << "Encrypted Text: " << processText << endl;
					
				}
			}
		}
		// Check if it is decrypt method
		else if(method == "DEC") {
			while (!feof(fileRead)){
				numRead = fread(textData,sizeof(char),16,fileRead);
				if (numRead != 0) {
					for (int i = 0; i < 16; i++)
						cout << textData[i] << " ";
					cout << endl;
					processText = cipher->decrypt(textData);
					fwrite(processText, sizeof(char), 16,fileWrite);
					cout << "Decrypted Text: " << processText << endl;
				}
			}
		}
		// If user choose something else
		else {
			cout << "Method is Unknown, please recheck your method" << endl;
			cout << "ENC for encryption" << endl;
			cout << "DEC for decryption" << endl;
		}
		fclose(fileRead);
		fclose(fileWrite);
	} else if (ciphername == "DES") {

		cerr << "In DES" << endl;
		cipher =new DES();
		if(cipher == NULL){
			fprintf(stderr, "Error not allocated DES\n");
		}
			
		if(!cipher->setKey((unsigned char*)key)){
			cerr << "Set Key error, code can't compile " << endl;
		}
		cerr << "Finished setting the key!" << endl;	
		unsigned char* processedText = NULL;
	        int numWritten;
		// Saving file data char by char into textData 
		while (!feof(fileRead)){


			int numRead  = fread(textData,sizeof(char),8,fileRead);

			//  Not reached the end of the file
			if(numRead != 0)
			{
				// If numRead < 8 --? Padd
				// Encrypt
				// Write to the output

				for(int i = numRead ; i < 8; i++){
					textData[i] = 0;
				}

				if(method == "ENC"){
					processedText = cipher->encrypt((const unsigned char*)textData);
				}
				else{
					processedText = cipher->decrypt((const unsigned char*)textData);
				}

				numWritten =  fwrite(processedText, sizeof(char), 8, fileWrite);

				if(numWritten < 8) { fprintf(stderr, "Failed to write the output file!\n"); }


			}
			//Encrypt a block
			//Write a block

		}

		// Close file after finish reading
		fclose(fileRead);
		fclose(fileWrite);



	}

	return 0;
}
