//
//  main.cpp
//  Vigenere Cipher
//
//  Created by Berkin İnceoğlu on 12/14/19.
//  Copyright © 2019 Berkin İnceoğlu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void vigenereCipher(string choice, string wholeText, string key, int counter,int replacement){
    if (choice == "1"){
        for (int i=0; i<wholeText.size(); i++){ //encryption
            int remainder = counter % key.size();
            int difference, test;
            test = (int)wholeText[i];
            if (test>= 65 && test <= 90)
            {
                if((int)key[remainder] >= 97 && (int)key[remainder] <= 122)
                    difference = ((int)key[remainder] - 97);
                else if((int)key[remainder] >= 65 && (int)key[remainder] <= 90)
                    difference = ((int)key[remainder] - 65);
                else
                    difference = 0;
                
                if ((int)wholeText[i] + difference > 90 || (int)wholeText[i] + difference > 122)
                    replacement = (int)wholeText[i] + difference - 26;
                else
                    replacement = (int)wholeText[i] + difference;
                
                wholeText[i] = char(replacement);
                counter++;
                
            }
            else if (test>=97 && test <= 122)
            {
                if((int)key[remainder] >= 97 && (int)key[remainder] <= 122)
                    difference = ((int)key[remainder] - 97);
                else if((int)key[remainder] >= 65 && (int)key[remainder] <= 90)
                    difference = ((int)key[remainder] - 65);
                else
                    difference = 0;
                
                if ((int)wholeText[i] + difference > 90 && (int)wholeText[i] + difference < 97 )
                    replacement = (int)wholeText[i] + difference - 26;
                else if ((int)wholeText[i] + difference > 122)
                    replacement = (int)wholeText[i] + difference - 26;
                else
                    replacement = (int)wholeText[i] + difference;
                
                
                wholeText[i] = (char(replacement));
                counter++;
            }
            else if (test>= 48 && test <= 57){
                test += key.size();
                if (test > 57 )
                    test -= 10;
                wholeText[i] = (char)test;
            }
            
        }
        cout<< "Encrypted text with key \"" << key << "\" is:" << endl << wholeText << endl << endl;
    }
    else if (choice == "2"){
        for (int i=0; i<wholeText.size(); i++){ //decyrption
            int remainder = counter % key.size();
            int difference, test;
            test = (int)wholeText[i];
            if (test>= 65 && test <= 90)
            {
                if((int)key[remainder] >= 97 && (int)key[remainder] <= 122)
                    difference = ((int)key[remainder] - 97);
                else if((int)key[remainder] >= 65 && (int)key[remainder] <= 90)
                    difference = ((int)key[remainder] - 65);
                else
                    difference = 0;
                
                if ((int)wholeText[i] - difference < 65)
                    replacement = (int)wholeText[i] - difference + 26;
                else
                    replacement = (int)wholeText[i] - difference;
                
                wholeText[i] = char(replacement);
                counter++;
                
            }
            else if (test>=97 && test <= 122)
            {
                if((int)key[remainder] >= 97 && (int)key[remainder] <= 122)
                    difference = ((int)key[remainder] - 97);
                else if((int)key[remainder] >= 65 && (int)key[remainder] <= 90)
                    difference = ((int)key[remainder] - 65);
                else
                    difference = 0;
                
                if ((int)wholeText[i] - difference < 97 )
                    replacement = (int)wholeText[i] - difference + 26;
                
                else
                    replacement = (int)wholeText[i] - difference;
                
                
                wholeText[i] = (char(replacement));
                counter++;
            }
            else if (test>= 48 && test <= 57){
                test -= key.size();
                if (test < 48 )
                    test += 10;
                wholeText[i] = (char)test;
            }
            
        }
        cout << "Decyrpted text is: " << endl << wholeText << endl;
    }

}


int main(int argc, const char * argv[]) {
    string filename, line, key, choice, textChoice;
    string wholeText = "";
    int counter = 0;
    int replacement=0;
    ifstream file;
    cout << "Enter 1 for opening .txt file or enter 2 for input manually: ";
    cin >> textChoice;
    if (textChoice == "1"){
        cout << "Please enter the file name without extension: ";
        cin>> filename;
        filename += ".txt";
        
        file.open(filename);
        while (file.is_open() == false){
            {
                cout << "Please enter a valid filename:" <<endl;
                cin>> filename;
                filename += ".txt";
                file.open(filename);
            }
        }
        
        while (getline(file, line)) // To get every line of txt file into a string.
        {
            wholeText += line;
        }
        cout << endl <<  wholeText << endl << endl;
        
        cout << "Enter 1 for encryption or 2 for decryption" << endl;
        cin>> choice;
        while (choice != "1" && choice != "2")
        {
            cout << "Please enter a valid choice." << endl;
            cin>>choice;
        }
        
        cout<< "If you want a custom key please enter if not please enter 0: "<<endl;
        cin>> key;
        if (key == "0")
            key = "berkin";
        
        vigenereCipher(choice, wholeText, key, counter, replacement);
    }

    else if (textChoice == "2")
    {
        cout << "Please enter your text: \nAnd press q if your text has finished. ";
        string input="";
        string get;
        cin.ignore();
        while(getline(cin, get))
        {
            if (get == "q" || get == "Q")
                break;
            input += get;
        }
        
        cout << "Enter 1 for encryption or 2 for decryption" << endl;

        cin>> choice;
        while (choice != "1" && choice != "2")
        {
            cout << "Please enter a valid choice." << endl;
            cin>>choice;
        }

        cout<< "If you want a custom key please enter if not please enter 0: "<<endl;
        cin>> key;
        if (key == "0")
            key = "berkin";

        vigenereCipher(choice, input, key, counter, replacement);
    }

    return 0;
}
