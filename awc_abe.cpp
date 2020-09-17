/*
    A Simple and New ( Half-Modern ) Cryptography Tool.
    Developer Ali Salehikia <theredhat@tuta.io>
    Version 1.1
    UNLICENSED
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class FileEncryption {
/*
    FileEncryption Class,
    2 Constructors (1 empty constructor, 1 constructor as main constructor)
*/
private:
    vector<string> words, encryptedWords;
    vector<int> cases, keys;
    /*
        vector words that contains plain text words, vector encryptedWords contains the words user input for create Cipher Text,
        vector cases that contains the cases of ciphers or encryptedWords the user specified, vector keys that contains a specified char from a string in words minus a string[case] from encryptedWords.
    */
public:
    FileEncryption() = default;

    explicit FileEncryption(const string &file) { // Filename as argument
        ifstream fileForEncrypt(file);  // open file for encryption
        if (fileForEncrypt.fail()) {
            cerr << "\033[91mError in opening " << file << "\033[0m" << endl;
            exit(10);
        }   // Exit with code 10 if file opening failed
        else { // if file opening wasn't failed
            stringstream wordStream;
            /*
                wordStream, a String Stream for get words from file (get from content at line 38)
            */
            string content, get;
            /*
              Two basic_string<char>, one for get input from the file (content)
              one for get word from wordStream String Stream
            */
            cout << "\033[93m !! CASE NUMBER STARTS FROM 0 !!\033[0m" << endl;  // Show a tip
            while (fileForEncrypt) {  // a loop for get Plain Text
                getline(fileForEncrypt, content);
                for (char &str : content) {
                    if (str == ' ') {
                        continue;
                    }   // Pass if there was any space
                    wordStream << str;
                }
                getline(wordStream, get);    //  add word to get (at line 38 declared)
                wordStream.clear();
                words.push_back(get);   //  push back word to words vector (at line 19 declared)
            }
            int iter{1}, iter2{1};
            unsigned int _case;
            string word;
            /*
                Two Integers, one for get Plain Text word number,
                one for get Cipher Text word number ( or the word that user entered or Plain Text Word case )
            */
            for (string &getWord:words) {   // a loop for get a word from words vector (at line 19 declared)
                cout << iter << ". " << getWord << endl;
                for (char &getCharacter:getWord) {  // a loop for get a character from a word from words vector
                    cout << endl << "Word " << iter2 << ": ";
                    cin >> word;
                    encryptedWords.push_back(word); // push back the specified cipher word
                    cout << "Case: ";
                    cin >> _case;
                    if (_case >=
                        word.length()) {    // if the case user entered was greater or equal (as numbers start from 0) than length of word
                        cerr << "\033[92m Warning: The case you entered is greater than length of the word " << iter2
                             << ", using case " << (word.length() - 1) << " instread of " << _case << "\033[0m" << endl;
                        _case = (word.length() - 1);
                    }
                    keys.push_back(getCharacter - word[_case]); // push back the key
                    cases.push_back(_case);
                    iter2++;
                }
                iter++;
            }
            cout << endl;
        }   // end of else
        cout << endl << endl << endl;
        /* Cipher Text File */
        stringstream cipherFileName, casesFileName, keysFileName; // String Stream For File Names
        cipherFileName << file << ".cph";
        ofstream cipherStream(cipherFileName.str(), ios::trunc); // Create Cipher Text File
        cipherFileName.clear();
        /* end */
        /* Cases File */
        casesFileName << file << ".case";
        ofstream caseStream(casesFileName.str(), ios::trunc);
        casesFileName.clear();
        /* end */
        /* Keys File */
        keysFileName << file << ".key";
        ofstream keyStream(keysFileName.str(), ios::trunc);
        keysFileName.clear();
        /* end */

        if (cipherStream.fail() || caseStream.fail() || keyStream.fail()) {
            cerr << "\033[91mError in creating files.\033[0m" << endl;
            exit(10);
        }   // Exit with code 10 if any of streams are failed
        /* Print Results */
        cout << "\033[96m|-_results_-|\033[0m" << endl << endl;
        cout << "Plain Text: " << endl;
        for (auto &at : words) {
            cout << at << " ";
        }
        cout << endl << endl;
        cout << "Cipher Text: " << endl;
        for (auto &at:encryptedWords) {
            cout << at << " ";
            cipherStream << at << " ";
        }
        cout << endl << endl;
        cout << "Cases: " << endl;
        for (auto &at:cases) {
            cout << at << " ";
            caseStream << at << endl;
        }
        cout << endl << endl;
        cout << "Keys: " << endl;
        for (auto &at:keys) {
            cout << at << " ";
            keyStream << at << endl;
        }
        cout << endl << endl;
    }   //  end of main constructor
};  //  end of class FileEncryption

class FileDecryption {
    /*
        FileDecryption Class,
        2 Constructors (1 empty constructor, 1 constructor as main)
    */
private:
    vector<string> cipherWords;
    vector<int> keys;
    vector<unsigned int> cases;
    /*
        3 vectors,
        cipherWords for get cipher words from cipher file,
        keys for get keys from key file,
        cases for get cases from case file
    */
public:
    FileDecryption() = default;

    FileDecryption(const string &cipher_file, const string &key_file, const string &case_file) {
        ifstream cipher_stream(cipher_file);
        ifstream key_stream(key_file);
        ifstream case_stream(case_file);
        if (cipher_stream.fail() || key_stream.fail() || case_stream.fail()) {
            cerr << "\033[91mError in opening files." << "\033[0m" << endl;
            exit(10);
        }   //  exit with code 10 if any of files was failed
        while (cipher_stream) { //  a loop for get cipher words
            string cipherWord;
            cipher_stream >> cipherWord;
            cipherWords.push_back(cipherWord); // add to cipherWords at line 135
        }
        while (key_stream) {    //  a loop for get keys
            int key;
            key_stream >> key;
            keys.push_back(key);    //  add to keys at line 136
        }
        while (case_stream) {   // a loop for get cases
            unsigned int case_;
            case_stream >> case_;
            cases.push_back(case_); // add to cases at line 137
        }
        cout << "Plain Text: ";
        for (unsigned int at(0); at < (cipherWords.size() - 1); at++) { // a loop for printing the result
            string element = cipherWords[at];
            char plainCharacter = (char) (element[cases[at]] + keys[at]);   //  with ASCII
            cout << plainCharacter;
        }
        cout << endl;
    }   //  end of main constructor
};  // end of FileDecryption class

void arg_error() {
    cerr << "\033[91mInvalid Argument(s)!\nUsing -h for Help\033[0m" << endl;
}

int main(int argc, char *argv[]) {
    if (argv[1] == nullptr) {   // if argv[1] or first argument was null invoke arg_error() and exit with code 9
        arg_error();
        exit(9);
    }
    string argument{argv[1]};   //  use first argument as string
    if (argument == "-e" || argument == "--encrypt") {  // encryption_
        if (argc == 3) {
            FileEncryption en(argv[2]);
        } else {
            arg_error();
        }
    } else if (argument == "-h" || argument == "--help") {  // help_
        cout
                << "Welcome to Advanced Word Cryptography (Advanced Book-Encryption) Version 1.1\nUsing:"
                << endl << "-e --encrypt FILENAME" << endl << "-d --decrypt CIPHER_FILE KEY_FILE CASE_FILE" << endl
                << "-h --help" << endl << "-v --version" << endl;
    } else if (argument == "-v" || argument == "--version") {    // version_
        cout << "\033[93m Advanced Word Cryptography - version 1.1 - Unlicensed" << endl;
    } else if (argument == "-d" || argument == "--decrypt") {   // decryption_
        if (argc == 5) {
            FileDecryption de(argv[2], argv[3], argv[4]);
        } else {
            arg_error();
        }
    } else {
        arg_error();
    }
}