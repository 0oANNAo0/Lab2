#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book {
  char author[255];
  char title[255];
  int year;
  int pages;
  double price;
  struct book* next;
} Book;

void openBook(char* filename, Book** list);
void printBook(Book* book);
void insertBook(Book** current, Book* book);
void scanBook(Book** book);
void removeBooksWithD(Book** head);
void sortBooks(Book** head);
void swap(Book **head_ref, Book* x, Book* y);
void printBooks(Book* head);

int main() {
  Book* head, *current;
  openBook("dat.txt", &head);

  sortBooks(&head);
  printBooks(head);

  current = head;

  printf("Enter book to insert:\n");
  Book* book;
  scanBook(&book);
  // insert to list
  insertBook(&current, book);


  printf("Books more than 50 pages\n");
  // remove from list
  removeBooksWithD(&head);
  return 0;
}

void openBook(char* filename, Book** list) {
  FILE* file = fopen(filename, "r");
  Book* head = NULL;
  Book* current = NULL;
  while(!feof(file)) {
    Book* book = (Book*) calloc(1, sizeof(Book));
    fscanf(file, "%s%s%d%d%lf", book->author, book->title, &book->year, &book->pages, &book->price);
    if(strlen(book->title) == 0) {
      free(book);
      continue;
    }
    if(head == NULL) {
      head = book;
      current = head;
    } else {
      current->next = book;
      current = book;
    }
  }
  *list = head;
}

void printBooks(Book* head) {
	Book* current = head;
	do {
		printBook(current);
	} while(current = current->next);
}

void printBook(Book* book) {
    printf("Book \"%s\" by %s, %d year, %d pages, $%lf\n", book->title, book->author, book->year, book->pages, book->price);
}

void insertBook(Book** current, Book* book) {
  (*current)->next = book;
  *current = book;
}

void scanBook(Book** book) {
	*book = (Book*) calloc(1, sizeof(Book));
	scanf("%s%s%d%d%lf", (*book)->author, (*book)->title, &(*book)->year, &(*book)->pages, &(*book)->price);
}

void removeBooksWithD(Book** head) {
  Book* current = *head;
  Book* prev = NULL;
  while(current != NULL) {
    Book* book = current;
    if(book->title[0] == 'd' || book->title[0] == 'D') {
      if(book == *head) {
        *head = book->next;
      } else {
        prev->next = book->next;
      }
    } else {
      printBook(book);
      prev = current;
    }
    current = current->next;

  }
}

void swap(Book **head_ref, Book* x, Book* y)
{
	if (x == y) return;

	Book *prevX = NULL, *currX = *head_ref;
	while (currX && currX != x)
	{
	    prevX = currX;
	    currX = currX->next;
	}

	Book *prevY = NULL, *currY = *head_ref;
	while (currY && currY != y)
	{
	    prevY = currY;
	    currY = currY->next;
	}

	if (currX == NULL || currY == NULL)
	    return;

	if (prevX != NULL)
	    prevX->next = currY;
	else
	    *head_ref = currY;

	if (prevY != NULL)
	    prevY->next = currX;
	else
	    *head_ref = currX;

	Book *temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;
}

void sortBooks(Book** books) {
	Book* book, *bookPrev;
	while(1) {
		book = (*books)->next;
		bookPrev = *books;
		int sorted = 1;
		do {
			if(strcmp(book->title, bookPrev->title) < 0) {
				swap(books, book, bookPrev);
				sorted = 0;
				break;
			}
		} while((bookPrev = book) && (book = book->next));

		if(sorted) break;
	}
}
