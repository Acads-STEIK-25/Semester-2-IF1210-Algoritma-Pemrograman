#define IDX_UNDEF -1
#define CAPACITY 100
#define boolean unsigned char
#define true 1
#define false 0

typedef int ElType;

typedef struct {
    ElType buffer[CAPACITY];
    int idxTop;
} Stack;

#define IDX_TOP(s) (s).idxTop
#define TOP(s) (s).buffer[(s).idxTop]

/*** Konstruktor/Kreator ***/
void CreateStack(Stack *s){
    s->idxTop = IDX_UNDEF;
}
/* I.S. Sembarang */
/* F.S. Membuat sebuah Stack s yang kosong berkapasitas CAPACITY */
/* jadi indeksnya antara 0..CAPACITY-1 */

/* Ciri stack kosong: idxTop bernilai IDX_UNDEF */
/********** Predikat Untuk test keadaan KOLEKSI **********/
boolean isEmpty(Stack s){
    return (s.idxTop == IDX_UNDEF);
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean isFull(Stack s){
    return (s.idxTop == CAPACITY-1);
}
/* Mengirim true jika Stack penuh */

int length(Stack s){
    return (s.idxTop+1);
}
/* Mengirim ukuran Stack s saat ini */

/*********** Menambahkan sebuah elemen ke Stack **********/
void push(Stack *s, ElType val){
    s->idxTop++;
    s->buffer[s->idxTop] = val;
}
/* Menambahkan val sebagai elemen Stack s.
I.S. s mungkin kosong, tidak penuh
F.S. val menjadi TOP yang baru, TOP bertambah 1 */

/*********** Menghapus sebuah elemen Stack **********/
void pop(Stack *s, ElType *val){
    *val = s->buffer[s->idxTop];
    s->idxTop--;
}