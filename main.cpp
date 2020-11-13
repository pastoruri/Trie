#include <iostream>
#include "Trie.h"
int main() {
  Trie t("direcciones.txt");

  t.printPrefix("a");

  t.count("aa1.txt");

}