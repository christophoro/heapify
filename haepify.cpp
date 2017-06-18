#include <stdio.h>
#include <stdlib.h>

int n = 0;		/* rozmiar kopca */
bool m = 0;		/* 0 - kopiec max, 1 - kopiec min */
int v = 0;		/* pobrana liczba z stdin */
int h_size = 10;	/* rozm tablicy */

void print(int *H);
void add(int *& H);
void remove(int *& H);
void swap(int *& H);
void heapify(int i, int *& H);
void resize(int *& H);

int main() {
	char input[10000];
	char c;		/* instrukcja */
	char *p;	/* wsk na nast znak z input */
	int i;

	int *H = new int[10];

	while (1) {
		fgets(input, sizeof input, stdin);
		p = input;
		c = *p;
		i = 0;
		for (p = input + 1; p < p + sizeof input; p++) {
			if (*p == '\n')
				break;
			if (*p >= '0' && *p <= '9') {
				v = *p - '0';
				while (*(p + 1) >= '0' && *(p + 1) <= '9') {
					v *= 10;
					v += *(p + 1) - '0';
					p++;
				}
				if (c == 'r' && !i) {
					n = v;
					resize(H);
				}
				if (c == 'r' && i)
					H[i] = v;
				i++;
			}
		}
		if (c == '-')
			remove(H);
		if (c == 'p')
			print(H);
		if (c == 's')
			swap(H);
		if (c == 'q')
			return 0;
		if (c == '+') 
			add(H);
		if (c == 'r') {
			for (i = n / 2; i > 0 ; i--)
				heapify(i, H);	
		}
	}
	return 0;
}

void resize(int *& H) {
	if (n >= h_size) {
		h_size = n * 2;
		int * new_H = new int[h_size];
		int i;
		for (i = 0; i <= n; i++)
			new_H[i] = H[i];
		delete[] H;
		H = new_H;
	}
}

void heapify(int i, int *& H) {
	int t, s;
	int l = i * 2;
	int r = i * 2 + 1;
	if (!m) {						/* max-heapify */
		if (l <= n && H[l] > H[i])
			t = l;
		else
			t = i;
		if (r <= n && H[r] > H[t])
			t = r;
	}
	else {							/* min-heapify */
		if (l <= n && H[l] < H[i])
			t = l;
		else
			t = i;
		if (r <= n && H[r] < H[t])
			t = r;
	}
	if (t != i) {
		s = H[i];
		H[i] = H[t];
		H[t] = s;
		heapify(t, H);
	}
}

void print(int *H) {
	if (n) {
		int i;
		for (i = 1; i <= n; i++)
			printf("%d ", H[i]);
	}
	printf("\n");
}


void add(int *& H) {
	int i, s;
	n++;
	resize(H);
	i = n;
	H[i] = v;
	if (!m) {						/* max-add */
		while (i > 1 && H[i / 2] < H[i]) {
			s = H[i / 2];
			H[i / 2] = H[i];
			H[i] = s;
			i = i / 2;
		}
	}
	else {							/* min-add */
		while (i > 1 && H[i / 2] > H[i]) {
			s = H[i / 2];
			H[i / 2] = H[i];
			H[i] = s;
			i = i / 2;
		}
	}
}

void remove(int *& H) {
	int i;
	if (n) {
		printf("%d\n", H[1]);
		H[1] = H[n];
		n--;
		for (i = n / 2; i > 0; i--)
			heapify(i, H);
	}
}

void swap(int *& H) {
	int i;
	if (m)
		m = 0;
	else
		m = 1;
	for (i = n / 2; i > 0; i--)
		heapify(i, H);
}

