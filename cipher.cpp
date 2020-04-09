#include <string>
#include "CipherInterface.h"
#include "AES.h"
#include "DES.h"

#include <stdio.h>
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
	
	string ciphername = argv[1];
	// Since we are passiing const unsigned char* in the setKey function
	// We should also saving value as const unsigned char*
	// However, by doing this, we need to convert our input into it as well
	const unsigned char* key = (const unsigned char*)argv[2];
	string method = argv[3];
	string inputText = argv[4];
	string outputText = argv[5];

	// cout << "Testing 1 - 3 " << endl;
	cout << "ciphername: " << ciphername << endl;
	cout << "key: " << key << endl;
	cout << "method: " << method << endl;
	cout << "inputText: " << inputText << endl;
	cout << "outputText: " << outputText << endl;

	// ifstream inputFile;
	// inputFile.open (inputText);
	// if(!inputFile.is_open()){
	// 	cerr << "File can't be open !!! " <<endl;
	// }

	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = 0;  

	cout << "Testing AES" << endl;
	cipher = new AES();
	
		 
	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	
	/* Set the encryption key
	
	 * characters. Below is one example.
	 * Your program should take input from                           
	 * command line.
	 */
	cout << "Testing 1" << endl;
	if(!cipher->setKey((unsigned char*)"00123456789abcdef")){
		cerr << "Set Key error, code can't compile " << endl;
	}
	
	cerr << "Set key complete" << endl;
		
	/* Perform encryption */

	// string output = cipher->encrypt((unsigned char*)"hello world"));
	unsigned char* output; //= new unsigned char[100];
	output = cipher->encrypt((unsigned char*)"hello world12345");
	
	if(!cipher->setKey((unsigned char*)"10123456789abcdef")){
		cerr << "Set Key error, code can't compile " << endl;
	}
	unsigned char* outputdec; //= new unsigned char[100];
	outputdec = cipher->decrypt((unsigned char*)output);

	cerr << "The decrypted text is: " << outputdec << endl;
	
	//cout << "Output: " << output << endl; 
	

	// /* Perform decryption */
	// cipher->decrypt(cipherText);	
	
	return 0;
}
