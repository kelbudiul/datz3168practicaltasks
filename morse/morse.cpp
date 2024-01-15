#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>



using namespace std;


string alphabet = "abcdefghijklmnopqrstuvwxyz";
string morse[] = { ".-","-...","-.-.","-..",".","..-.","--.","....",
"..",".---","-.-",".-..","--","-.","---",".--.","--.-", ".-.","...",
"-","..-","...-",".--","-..-","-.--","--.." };

char morse_to_alpha(const string& tkn)
{
	if (tkn.empty())
		return ' ';
	else if (tkn == "-...-")
		return ' ';
	for (int i = 0; i < 26; i++)
		if (morse[i] == tkn)
			return alphabet[i];
	return '*';     //  Couldn't translate
}

void morseEnglish(string tmp)
{
	string  message;
	string  token;
	string  result;


	message = tmp;

	for (int i = 0; i < message.length(); i++)
	{
		if (message[i] == '|')
		{   // end of a morse token
			result += morse_to_alpha(token);
			token.clear();
		}
		else
			token += message[i];
	}
	cout << result << endl;
}




void textTomorse(string text) {
	for (int i = 0; i < text.length(); i++) {
		text[i] = tolower(text[i]);
		switch (text[i]) {
		case 'a': cout << ".-"; break;
		case 'b': cout << "-..."; break;
		case 'w': cout << ".--"; break;
		case 'g': cout << "--."; break;
		case 'd': cout << "-.."; break;
		case 'e': cout << "."; break;
		case 'v': cout << "...-"; break;
		case 'z': cout << "--.."; break;
		case 'i': cout << ".."; break;
		case 'j': cout << ".---"; break;
		case 'k': cout << "-.-"; break;
		case 'l': cout << ".-.."; break;
		case 'm': cout << "--"; break;
		case 'n': cout << "-."; break;
		case 'o': cout << "---"; break;
		case 'p': cout << ".--."; break;
		case 'r': cout << ".-."; break;
		case 's': cout << "..."; break;
		case 't': cout << "-"; break;
		case 'u': cout << "..-"; break;
		case 'f': cout << "..-."; break;
		case 'h': cout << "...."; break;
		case 'c': cout << "-.-."; break;
		case 'q': cout << "--.-"; break;
		case 'y': cout << "-.--"; break;
		case 'x': cout << "-..-"; break;
		case '1': cout << ".----"; break;
		case '2': cout << "..---"; break;
		case '3': cout << "...--"; break;
		case '4': cout << "....-"; break;
		case '5': cout << "....."; break;
		case '6': cout << "-...."; break;
		case '7': cout << "--..."; break;
		case '8': cout << "---.."; break;
		case '9': cout << "----."; break;
		case '0': cout << "-----"; break;
		case '.': cout << "......"; break;
		case ',': cout << ".-.-.-"; break;
		case ':': cout << "---..."; break;
		case ';': cout << "-.-.-."; break;
		case '(': cout << "-.--.-"; break;
		case ')': cout << "-.--.-"; break;
		case '"': cout << ".-..-."; break;
		case '-': cout << "-....-"; break;
		case '/': cout << "-..-."; break;
		case '?': cout << "..--.."; break;
		case '!': cout << "--..--"; break;
		case ' ': cout << "-...-"; break;
		case '@': cout << ".--.-."; break;
		default: cout << ""; break;
		}
		cout << "|";
	}
	cout << endl;
}

int main() {


	int choice;
	int key;
	string tmp;
	string filename;
	fstream file;
	bool loop = false;

	cout << "Choose operation:" << "\n";
	cout << "Type 11 to convert Text to Morse" << "\n";
	cout << "Type 22 to convert Morse to Text" << "\n";
	cin >> choice;
	if (choice == 11)
	{
		loop = true;
		while (loop)
		{
			tmp = "";
			cout << "Provide filename:";
			cin >> filename;
			cout << endl;
			file.open(filename, ios::in);

			if (file.is_open())
			{
				file.clear();
				file.seekg(0, file.beg);
				cout << "Text _to_ morse:" << "\n";
				while (getline(file, tmp))
				{
					cout << tmp << "\n";
					textTomorse(tmp);
				}


			}
			else if (!file.is_open())
			{

				break;
			}

			cout << "To restart press 1, to quit press any key:";
			cin >> key;
			if (key == 1);
			else if (key != 1)
				break;
		}

	}
	else if (choice == 22) {
		loop = true;
		while (loop)
		{
			cout << "Provide filename:";
			cin >> filename;
			cout << endl;
			file.open(filename, ios::in);

			string morse_code;
			if (file.is_open())
			{
				file.clear();
				file.seekg(0, file.beg);

				cout << "\nSeparate Morse Code by blanks:\n";
				while (getline(file, morse_code))
				{
					cout << "Your code:\n";
					cout << morse_code;

					cout << "\n\nThe decoded message is:\n";
					morseEnglish(morse_code);
					cout << endl;

				}


			}
		}

	}
	else
	{
		cout << "Incorrect option!";
		exit(1);
	}

	file.close();

	return 0;
}