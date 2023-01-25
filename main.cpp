#include "LinkedList.h"
#include "SparseArray.h"
#include <iostream>
#include <cctype>
#include <string>
using std::string;
using List = LinkedList <string>;

int main()
{
  string text; // Stores input phrase
  std::cout << "\nEnter a phrase over one or more lines."
            << "Terminate the input with #:\n";
  getline(std::cin, text, '#');


  SparseArray<List> lists; // Sparse array of linked lists to store words
  string letters {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

  // Extract words and store in the list
  string separators(" ,.\"?!;:\n");              // Separators between words
  size_t start {};                               // Start of a word
  size_t end {};                                 // separator position after a word
  string word;
  while(string::npos != (start = text.find_first_not_of(separators, start)))
  {
    end = text.find_first_of(separators, start+1);
    word = text.substr(start,end-start);

    start = end;
    lists[letters.find(std::toupper(word[0]))].addTail(&word);
  }


   // List the words in order 5 to a line
  const size_t perline {5};
  size_t count {};      // Word counter
  string* pStr;
  for (size_t i {}; i < 26; ++i)
  {
    if (!lists.element_exists(i))
      continue;
    pStr = lists[i].getHead();
    char firstCharacter= pStr->front();
    std::cout << "Letters that start with the letter " << firstCharacter<<std::endl;
    count = 0;

    while(pStr)
    {
      std::cout << *pStr << ' ';
      if(!(++count % perline))
        std::cout << std::endl;
      pStr = lists[i].getNext();
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
