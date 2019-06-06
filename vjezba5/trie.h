#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

typedef struct trie_node *trie_t;

/* stvara novo trie stablo/granu (cvor) */
trie_t trie_new_node();

/* brise trie stablo/granu (cvor) */
void trie_delete_node(trie_t root);

/* ispisuje sadrzaj trie stabla/grane (cvora)*/
void trie_print_node(trie_t root, char* prefix);

/* ubacuje novu rijec u trie */
void trie_insert_word(trie_t root, char *word);

/* vraca 1 ukoliko trie sadrzi zadanu rijec, a 0 inace */
int trie_search_word(trie_t root, char *word);

/* ispisuje sve rijeci iz triea koje pocinju zadanim prefiksom */
void trie_print_prefixed_word(trie_t root, char *prefix);

#endif /* TRIE_H_INCLUDED */
