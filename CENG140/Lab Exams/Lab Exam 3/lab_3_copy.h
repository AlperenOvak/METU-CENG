#ifndef LAB3_H
#define LAB3_H

typedef struct Article {
    char name[100];
    char** authors;
    int numAuthors;
    struct Article* next;
} Article;

typedef struct Journal {
    char name[100];
    Article* articles;
} Journal;

void insertNewJournal(Journal** journals, int* numJournals, char* name);
void insertNewArticleInAlphabeticOrder(Journal* journals, int numJournals, char* journalName, char* articleName);
void findArticlesByAuthor(Journal* journals, int numJournals, char* authorName);
void printJournalArticleCounts(Journal* journals, int numJournals);
void insertNewAuthor(Journal* journals, int numJournals, char* journalName, char* articleName, char* authorName);

#endif