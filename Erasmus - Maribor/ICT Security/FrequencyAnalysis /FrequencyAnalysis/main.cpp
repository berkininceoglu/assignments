//
//  main.cpp
//  FrequencyAnalysis
//
//  Created by Berkin İnceoğlu on 11/14/19.
//  Copyright © 2019 Berkin İnceoğlu. All rights reserved.
//

#include <iostream>
#include <map>
#include <fstream>
#include <set>
#include <vector>
#include <string>

using namespace std;

void creatingMap(string encText, string refText, map<char, int>& mapEnc, map<char, int>& mapRef) {
    char ch;
    for (int i = 0; i < encText.length(); i++)
    {
        ch = encText[i];
        if (encText[i] > 96 && encText[i] < 123) {
            if (mapEnc[ch] == NULL)
                mapEnc[ch] = 1;
            else
                mapEnc[ch] ++;
        }
    }
    for (int i = 0; i < refText.length(); i++)
    {
        ch = refText[i];
        if (refText[i] > 96 && refText[i] < 123) {
            if (mapRef[ch] == NULL)
                mapRef[ch] = 1;
            else
                mapRef[ch] ++;
        }
    }
}

int main(int argc, const char* argv[]) {
    string encLine;
    string refLine;
    string wholeText = "";
    string refText = "";
    
    map<char, int> occurEnc;
    map<char, int>  occurRef;
    ifstream encryptedFile("encrypted_file.txt");
    ifstream referenceFile("reference_file.txt");
    ofstream outputFile("decrypted_file.txt");
    if (encryptedFile.is_open() && referenceFile.is_open())
    {
        while (getline(encryptedFile, encLine), getline(referenceFile, refLine)) // To get every line of txt file into a string.
        {
            wholeText += encLine;
            refText += refLine;
        }
        encryptedFile.clear();
        referenceFile.clear();
        
        encryptedFile.close();
        referenceFile.close();
        
        creatingMap(wholeText, refText, occurEnc, occurRef); // Creates maps for both txts to count letter frequencies
        
        typedef function<bool(pair<char, int>, pair<char, int>)> LetterComparator; // Sorting letters in terms of nummber of occurences descendingly
        LetterComparator alphabetically =
        [](pair<char, int> elem1, pair<char, int> elem2)
        {
            if (elem1.second == elem2.second) {
                return elem1.first < elem2.first;
            }// to avoid missing letters with same occurence because they would not be changed in the first place
            else
                return elem1.second > elem2.second;
        };
        LetterComparator nonAlphabetically =
        [](pair<char, int> elem1, pair<char, int> elem2) // second comparator for random changing
        {
            if (elem1.second == elem2.second) {
                return elem1.first < elem2.first;
            }
            else
                return elem1.second < elem2.second;
        };
        
        // Declared a set that will store the pairs using above comparision logic
        set<pair<char, int>, LetterComparator> encFrequency(occurEnc.begin(), occurEnc.end(), alphabetically);
        set<pair<char, int>, LetterComparator> refFrequency(occurRef.begin(), occurRef.end(), nonAlphabetically);
        
        vector<char> lets;
        
        for (auto encItem : encFrequency)
        {
            cout << "Letter: " << encItem.first << " occurred " << encItem.second << " times in encrypted text." << endl;
        }
        cout << "--------------------------------------------------------------------------------------" << endl;
        for (auto refItem : refFrequency)
        {
            cout << "Letter: " << refItem.first << " occurred " << refItem.second << " times in reference text." << endl;
            lets.push_back(refItem.first);
            
        }
        
        int duplicateCounter;
        char toBeChangedWith = ' ';
        
        for (auto encItem : encFrequency) {
            duplicateCounter = 0;
            for (auto refItem : refFrequency)
            {
                if (encItem.second == refItem.second)
                {
                    toBeChangedWith = toupper(refItem.first);
                    duplicateCounter += 1;
                    
                }
            }
            
            if (duplicateCounter == 1)
            {
                for (int i = 0; i < wholeText.length(); i++)
                {
                    if (wholeText[i] == encItem.first)
                        wholeText[i] = toBeChangedWith;
                }
                lets.pop_back();
            }
            else // to  change randomly unchanged words kind of in random way in partial reveal
            {
                toBeChangedWith = toupper(lets.back());
                lets.pop_back();
                for (int i = 0; i < wholeText.length(); i++)
                {
                    if (wholeText[i] == encItem.first)
                        wholeText[i] = toBeChangedWith;
                }
            }
        }
        
        
        for_each(wholeText.begin(), wholeText.end(), [](char& c) {
            c = ::tolower(c);
        });
        
        
        cout << "You can find the partially revealed text below: \n";
        cout << "--------------------------------------------------------------------------------------" << endl;
        
        cout << wholeText;
        
        while (wholeText != refText) {
            char oldChar, newChar;
            
            cout << "\nPlease enter the character you want to change:";
            cin >> oldChar;
            cout << "Please enter the character you to replace character above:";
            cin >> newChar;
            cout << "--------------------------------------------------------------------------------------" << endl;
            
            for (int i = 0; i < wholeText.length(); i++)
            {
                if (wholeText[i] == oldChar)
                    wholeText[i] = newChar;
                else if (wholeText[i] == newChar)
                    wholeText[i] = oldChar;
            }
            
            cout << wholeText << endl << endl;
            cout << "Letter \"" << oldChar << "\" has been replaced with letter \"" << newChar << "\".";
        }
        
        
        if (outputFile.is_open())
        {
            outputFile << wholeText << endl;
        }
        else
            cout << "Operation of storing decrypted text in \"decrypted_file.txt\" has failed.";
        
        cout << "\n--------------------------------------------------------------------------------------\n";
        cout << "File is decrypted like above and stored in a file called: \"decrypted_file.txt\"\n\n";
        
    }
    else
        cout << "Unable to open file\n";
    
    outputFile.close();
    
    return 0;
}
