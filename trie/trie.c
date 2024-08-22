#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define N 26 // 26 letters in English
#define ROOT_VALUE ' '

// we both define struct name and alias name
typedef struct Trie {
    char value;
    bool isWord;
    struct Trie* children[N];
} Trie;


Trie* trieCreate() {
    // allocate memory & init value as 0
    Trie* node = calloc(1, sizeof(Trie));
    node->value = ROOT_VALUE;
    node->isWord = false;
    for(int i=0; i<N; i++){
        node->children[i]=NULL;
    }
    return node;
}

void trieInsert(Trie* root, char* word, bool isWord) {
    for (int i = 0; i < strlen(word); i++) {
        int id = word[i] - 'a';
        if (root->children[id] == NULL) {
            root->children[id] = trieCreate();
            root->children[id]->value = word[i];
        } 
        root = root->children[id];
    }

    // mark the last node as word
    if (root->value != ROOT_VALUE) {
        root->isWord = isWord;
    }
}

Trie* trieNodeSearch(Trie* root, char* word) {
    for (int i=0; i<strlen(word); i++) {
        int id = word[i] - 'a';
        
        // if the character not found, return false
        if (root->children[id] == NULL) {
            return NULL;
        }

        root = root->children[id];
    }

    // handle case word is empty
    if (root->value == ROOT_VALUE) {
        return NULL;
    }

    return root;
}

// we have flag isWord when inserting word
bool trieSearch(Trie* root, char* word) {
    Trie* foundNode = trieNodeSearch(root, word);

    if (foundNode == NULL) {
        return false;
    }

    return foundNode->isWord;
}

bool trieStartsWith(Trie* root, char* prefix) {
    Trie* foundNode = trieNodeSearch(root, prefix);
    return foundNode != NULL;
}

// free all children node in all levels
void trieFree(Trie* obj) {
    for (int i=0; i<N; i++) {
        if (obj->children[i] != NULL) {
            trieFree(obj->children[i]);
        }
    }
}

int main() {
    Trie* trie = trieCreate();
    trieInsert(trie, "apple", true);
    trieInsert(trie, "application", true);
    trieInsert(trie, "lov", false);
    trieInsert(trie, "lon", true);

    printf("%s word '%s'\n", trieSearch(trie, "apple") ? "Found": "Not found", "apple"); 
    printf("%s word '%s'\n", trieSearch(trie, "application") ? "Found": "Not found", "application");
    printf("%s prefix '%s'\n", trieStartsWith(trie, "application") ? "Found": "Not found", "application");
    printf("%s '%s'\n", trieStartsWith(trie, "lo") ? "Found prefix": "Not found", "lo");
    printf("%s '%s'\n", trieStartsWith(trie, "lon") ? "Found prefix": "Not found", "lon");
    printf("%s '%s'\n", trieStartsWith(trie, "love") ? "Found prefix": "Not found", "lonly");

    trieFree(trie);
    return 0;
}