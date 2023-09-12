#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
//26 букв и знак '
const int ALPHABET_SIZE = 27;

struct TrieTree {
    TrieTree* alphabet[ALPHABET_SIZE];
    bool isEndOfWord;
    int wordCounter = 0;
};
struct TrieTree* getNode()
{
    struct TrieTree* pNode = new TrieTree;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->alphabet[i] = NULL;

    return pNode;
}

void insert(TrieTree* root, string key)
{
    TrieTree* pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] == '\'' || key[i] >= 'a' && key[i]<= 'z') {
            int index;
            if (key[i] == '\'') {
                index = 26;
            }
            else {
                index = key[i] - 'a';
            }
            if (!pCrawl->alphabet[index])
                pCrawl->alphabet[index] = getNode();

            pCrawl = pCrawl->alphabet[index];
        }
    }

    pCrawl->wordCounter++;
    pCrawl->isEndOfWord = true;
}

void print(struct TrieTree* root, char str[], int level)
{
    if (root -> isEndOfWord)
    {

        str[level] = '\0';

        if (root->wordCounter > 5) {
            cout << str<< '\n';
        }
    }

    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {

        if (root->alphabet[i])
        {
            if (i!=26) {
                str[level] = i + 'a';
            }
            else {
                str[level] = '\'';
            }
            print(root->alphabet[i], str, level + 1);
        }
    }
}

int main() {
    ifstream t("B.txt");
    string str;
    TrieTree* root = getNode();
    while (!t.eof()) {
        t >> str;
        transform(str.begin(), str.end(), str.begin(),
                  [](unsigned char c) { return std::tolower(c); });
        insert(root, str);
    }
    int level = 0;
    char str_2[20];
    print(root, str_2, level);
}
