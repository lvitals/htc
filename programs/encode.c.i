# 1 "encode.c"

# 1 "./include/huff.h"





# 1 "../libc/include/stdio.h"









# 13 "../libc/include/stdio.h"





extern	struct	_iobuf
{
    char		*_ptr;
    int			 _cnt;
    char		*_base;
    unsigned short	 _flag;
    char		 _file;
} _iob[	8];










































# 71 "../libc/include/stdio.h"














extern int	 fclose(	struct _iobuf *);
extern int	 fflush(	struct _iobuf *);
extern int	 fgetc(	struct _iobuf *);
extern int	 ungetc(int, 	struct _iobuf *);
extern int	 fputc(int, 	struct _iobuf *);
extern int	 getw(	struct _iobuf *);
extern int	 putw(int, 	struct _iobuf *);
extern char	*gets(char *);
extern int	 puts(char *);
extern int	 fputs(char *, 	struct _iobuf *);
extern int	 fread(void *, unsigned, unsigned, 	struct _iobuf *);
extern int	 fwrite(void *, unsigned, unsigned, 	struct _iobuf *);
extern int	 fseek(	struct _iobuf *, long, int);
extern int	 rewind(	struct _iobuf *);
extern int	 setbuf(	struct _iobuf *, char *);
extern int	 printf(char *, ...);
extern int	 fprintf(	struct _iobuf *, char *, ...);
extern int	 sprintf(char *, char *, ...);
extern int	 scanf(char *, ...);
extern int	 fscanf(	struct _iobuf *, char *, ...);
extern int	 sscanf(char *, char *, ...);
extern int	 remove(char *);
extern 	struct _iobuf	*fopen(char *, char *);
extern 	struct _iobuf	*freopen(char *, char *, 	struct _iobuf *);
extern 	struct _iobuf	*fdopen(int, char *);
extern long	 ftell(	struct _iobuf *);
extern char	*fgets(char *, int, 	struct _iobuf *);
extern char	*_bufallo(void);



# 6 "./include/huff.h"

# 9 "./include/huff.h"
















# 27 "./include/huff.h"


typedef struct node {
	unsigned char		n_c;
	long		n_f;
	struct node *	n_left, * n_right;
}	node;

typedef	struct {
	unsigned char		h_nbits;
	unsigned char		h_cbits[	(1<<8)	/8];
}	h_char;

typedef struct {
	unsigned char		c_chr;
	long		c_freq;
	h_char		c_bits;
}	chent;

typedef	struct {
	char *		f_name;
	long		f_npos;
	long		f_nchrs;
	long		f_pos;
	char		f_asc;
}	filent;

typedef struct {
	short		hd_magic;
	short		hd_nfiles;
	short		hd_alfsiz;
	long		hd_hpos;
}	hdr;


extern node *		root;
extern chent		clist[	(1<<8)	];
extern filent		flist[500		];
extern short		alfused;
extern unsigned char		ascii;
extern unsigned long get4(void);
extern unsigned short get2(void);
extern chent *		cptrs[	(1<<8)	];
extern short		factor;

# 2 "encode.c"

# 1 "../libc/include/stdio.h"






# 114 "../libc/include/stdio.h"


# 3 "encode.c"

# 1 "../libc/include/stdlib.h"






typedef	int		ptrdiff_t;
typedef	unsigned	size_t;





# 16 "../libc/include/stdlib.h"


extern int	errno;




extern double	 atof(char *);
extern int	 atoi(char *);
extern long	 atol(char *);
extern int	 rand(void);
extern void	 srand(unsigned int);
extern void	*calloc(size_t, size_t);
extern void	 free(void *);
extern void	*malloc(size_t);
extern void	*realloc(void *, size_t);
extern void	 abort(void);
extern void	 exit(int);
extern char	*getenv(char *);
extern int	 system(char *);
typedef int (*__qsort_compf)(void *, void *);
extern void	 qsort(void *, size_t, size_t, __qsort_compf);
extern int	 abs(int);
extern long	 labs(long);



# 4 "encode.c"
typedef struct {
	node *	np_node;
	unsigned char	np_len;
}	np;

node *	root;
chent	clist[	(1<<8)	];
filent	flist[500		];
short	alfused;
chent *	cptrs[	(1<<8)	];
static	np	nptrs[	(1<<8)	];
static	unsigned char	p_bit;
static	unsigned char	p_char;
static	unsigned char	level;
static	short	nidx;


extern  void error(char *fmt, ...);

void   make_tree(char **);
node * newnode(void);
node * bld(short, short);
int    cmpr(chent **, chent **);
int    cmpnp(np *, np *);
void   bld_bits(node *, h_char);
void   pinit(void);
void   align(void);
void   put_bit(int);
void   puthch(unsigned char);
void   put_tchrs(node *);
void   walk_tree(node *);
void   put_tree(void);




void make_tree(char ** namlist) {
		struct _iobuf *	fp;
	int	c,  fno;
	h_char	tch;
	register char *	cp;

	fno = 0;
	while(*namlist) {
		if(**namlist == '-')
			switch(namlist[0][1]) {

			case 'a':
			case 'A':
				ascii = 1;
				namlist++;
				continue;

			case 'b':
			case 'B':
				ascii = 0;
				namlist++;
				continue;

			default:
				break;
			}
		if(!(fp = fopen(*namlist, ascii ? "r" : "rb"))) {
			fprintf(	(&_iob[2]), "Can't open %s\n", *namlist++);
			continue;
		}
		flist[fno].f_name = *namlist;
		flist[fno].f_asc = ascii;
		while((c = 		fgetc(fp)) != 	(-1)) {
			clist[c & (	(1<<8)	-1)].c_freq++;
			flist[fno].f_nchrs++;
		}
		fclose(fp);
		for(cp = *namlist ; *cp ; )
			clist[*cp++ & (	(1<<8)	-1)].c_freq++;
		clist[0].c_freq++;
		namlist++;
		fno++;
	}
	for(c =0 ; c < 	(1<<8)	 ; c++) {
		cptrs[c] = clist+c;
		clist[c].c_chr = c;
	}
	qsort(cptrs, 	(1<<8)	, sizeof cptrs[0], cmpr);
	for(alfused = 0 ; alfused < 	(1<<8)	 && cptrs[alfused]->c_freq ; alfused++)
		continue;
	level = 0;
	nidx = 0;
	root = bld(0, alfused-1);
	qsort(nptrs, alfused, sizeof nptrs[0], cmpnp);
	for(c = 0 ; c < alfused ; c++)
		nptrs[c].np_node->n_c = cptrs[c]->c_chr;
	tch.h_nbits = 0;
	bld_bits(root, tch);
}




node * newnode(void) {
	register node *	np;

	if(!(np = (node *)calloc(1, sizeof(node))))
		error("Out of memory");
	return np;
}




node * bld(short first, short last) {
	int	i;
	long	tot, run;
	register node *	l, * np;

	if(first == last) {
		l = newnode();
		nptrs[nidx].np_node = l;
		nptrs[nidx++].np_len = level+1;
		l->n_left = l->n_right = (node *)0;
		return l;
	}
	level++;
	for(i = first, tot = 0 ; i <= last ; i++)
		tot += cptrs[i]->c_freq;
	tot /= factor;
	run = cptrs[i = first]->c_freq;
	while(run < tot && i != last)
		run += cptrs[++i]->c_freq;
	if(i == last)
		i = (first+last)/2;
	if(i == first) {
		l = newnode();
		nptrs[nidx].np_node = l;
		nptrs[nidx++].np_len = level+1;
		l->n_left = l->n_right = (node *)0;
	} else
		l = bld(first, i);
	np = newnode();
	np->n_left = l;
	np->n_right = bld(i+1, last);
	level--;
	return np;
}




int cmpr(register chent ** p1, chent ** p2) {
	long	i;

	i = (*p2)->c_freq - (*p1)->c_freq;
	if(i > 0)
		return 1;
	if(i < 0)
		return -1;
	return 0;
}




int cmpnp(np * p1, np * p2) {

	return p1->np_len - p2->np_len;
}




void bld_bits(register node * nodep, h_char tch) {

	if(!nodep->n_left) {
		clist[nodep->n_c].c_bits = tch;
		return;
	}
		(tch.h_cbits[( tch.h_nbits)/8] |= (1<<(( tch.h_nbits)%8)));
	tch.h_nbits++;
	bld_bits(nodep->n_left, tch);
		(tch.h_cbits[( tch.h_nbits-1)/8] &= ~(1<<(( tch.h_nbits-1)%8)));
	bld_bits(nodep->n_right, tch);
}




void pinit(void) {

	p_char = 0;
	p_bit = 0;
}




void align(void) {

	if(p_bit)
				fputc(p_char,	(&_iob[1]));
	pinit();
}




void put_bit(int i) {

	if(i)
		p_char |= 1 << p_bit;
	if(++p_bit == 8) {
				fputc(p_char,	(&_iob[1]));
		p_char = 0;
		p_bit = 0;
	}
}




void puthch(unsigned char c) {
	h_char	tch;
	short	i;

	tch = clist[c].c_bits;
	for(i = 0 ; i < tch.h_nbits ; i++) {
		if(	((tch.h_cbits[( i)/8] & (1<<(( i)%8)))!=0))
			p_char |= 1 << p_bit;
		if(++p_bit == 8) {
					fputc(p_char,	(&_iob[1]));
			p_char = 0;
			p_bit = 0;
		}
	}
}




void put_tchrs(register node * tp) {

	if(tp->n_left) {
		put_tchrs(tp->n_left);
		put_tchrs(tp->n_right);
	} else
				fputc(tp->n_c,	(&_iob[1]));
}




void walk_tree(register node * tp) {

	if(tp->n_left) {
		put_bit(1);
		walk_tree(tp->n_left);
		put_bit(0);
		walk_tree(tp->n_right);
	}
}




void put_tree(void) {

	put_tchrs(root);
	walk_tree(root);
	put_bit(0);
}
