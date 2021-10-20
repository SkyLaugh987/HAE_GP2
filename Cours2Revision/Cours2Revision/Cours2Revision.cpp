#include <iostream>


int RecStrLen(const char * chaine) {
	if (!chaine) return 0;
	if (chaine[0] == 0) return 0;
	
	
	return 1 + RecStrLen(chaine + 1);
}

int RecStrCmp(const char * a, const char* b) {
	if (!a) return NULL;
	if (!b) return NULL;
	if ((*a == 0) && (*b == 0)) return 0;
	if (*a == 0) return 1;
	if (*b == 0) return -1;
	
	if (*a == *b) return RecStrCmp(a + 1, b + 1);
	else if (*a > *b) return -1;
	else return 1;
}

void RecStrCpy(char* dst, const char* src) {
	if (!dst) return;
	if (!src) return;
	if (*src == 0) {
		dst[0] = 0;
			return;
	}

	dst[0] = src[0];
	return RecStrCpy(dst + 1, src + 1);
}

char * RecStrCat(char * dst, const char * src) {
	if (!dst) return nullptr;
	if (!src) return nullptr;
	if (*src == 0) return 0;
	if (*dst == 0) {
		RecStrCpy(dst, src);
	}
	else
		return RecStrCat(dst + 1, src);
}

const char * RecStrStr(const char * str, const char * pattern) {
	if (!str) return nullptr;
	if (!pattern) return nullptr;
	if (*str == 0) return nullptr;
	if (RecStrCmp(str,pattern) == 0) {
		return pattern;
		return RecStrStr(str, pattern + 1);
	}
	else
		return RecStrStr(str + 1, pattern);
}
const char* RecStrChr(const char* chaine, char c) {
	if (!chaine) return nullptr;
	if (*chaine == 0) return nullptr;
	if (*chaine == c) return "found";
	else return RecStrChr(chaine + 1, c);
}

int main() {
	const char * chien = "chien";
	const char * chat = "chat";
	char  chatte[15] = {"chatte"};
	char  chienne[15] = { "chienne" };
	const char * chameau = "chameau";
	const char * eau = "eau";
	//char d = 'c';

	int c = RecStrLen(chien);
	int k = RecStrCmp(chien, chat);
	RecStrCpy(chatte, chien);
	printf("%s\n", chatte);
	RecStrCat(chienne, chien);
	printf("%s\n", chienne);
	printf("%s\n",RecStrStr(chameau, eau));
	printf("%s\n", RecStrChr(chien, 'o'));
	return 0;
};
