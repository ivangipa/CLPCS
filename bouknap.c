/* ======================================================================
          BOUKNAP.c, David Pisinger  1993, 1994, revised 1999
   ====================================================================== */

/* This is the C-code corresponding to the paper:
 *
 *   D. Pisinger
 *   A minimal algorithm for the bounded knapsack problem
 *   In: E. Balas, J. Clausen (eds.): Integer Programming and
 *   Combinatorial Optimization, Fourth IPCO conference. 
 *   Lecture Notes in Computer Science, Springer, Berlin, 920, 95-109 (1995). 
 *
 * Further details on the project can also be found in
 *
 *   D. Pisinger
 *   Algorithms for Knapsack Problems
 *   Report 95/1, DIKU, University of Copenhagen
 *   Universitetsparken 1
 *   DK-2100 Copenhagen
 *
 * The algorithm may be used for academic, non-commercial purposes
 * only.
 * -------------------------------------------------------------------
 * The present code is a callable routine which solves a bounded 
 * Knapsack Problem on the form:
 *
 *           maximize   \sum_{j=1}^{n} p_{j} x_{j}
 *           subject to \sum_{j=1}^{n} w_{j} x_{j} \leq c
 *                      x_{j} \in \{0,...,m_{j}\}, j = 1,\ldots,n
 *
 * The bouknap algorithm is called as
 *
 *          z = bouknap(n, p, w, m, x, c)
 *
 * where p[], w[], m[], x[] are arrays of integers. The optimal objective
 * value is returned in z, and x[] gives the solution vector.
 * If you need a different interface for your algorithm, bouknap
 * may easily be adapted to your own datastructures since all tables
 * are copied to the internal representation.
 *
 * Different types should be defined as follows:
 *
 *    itype     should be sufficiently large to hold a profit or weight
 *    stype     should be sufficient to hold sum of profits/weights
 *    ptype     should hold the product of an stype and itype
 *
 * The code has been tested on a hp9000/735, and conforms with the
 * ANSI-C standard.
 *
 * Errors and questions are refered to:
 *
 *   David Pisinger, associate professor
 *   DIKU, University of Copenhagen,
 *   Universitetsparken 1,
 *   DK-2100 Copenhagen.
 *   e-mail: pisinger@diku.dk
 *   fax: +45 35 32 14 01
 */

/* ======================================================================
                                  definitions
   ====================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
//#include <values.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <malloc.h>


/* ======================================================================
				   macros
   ====================================================================== */

#define SYNC            5      /* when to switch to linear scan in bins */
#define SORTSTACK     200      /* depth of stack used in qsort */
#define MINMED        100      /* find exact median in qsort if larger size */

#define TRUE  1
#define FALSE 0

#define LEFT  1
#define RIGHT 2

#define PARTIATE 1
#define SORTALL  2

#define MAXV (8*sizeof(vtype)) /* number of bits in a long integer */
#define PMAX 1                 /* profit of worlds most efficient item  */
#define WMAX 0                 /* weight of worlds most efficient item  */
#define PMIN 0                 /* profit of worlds least efficient item */
#define WMIN 1                 /* weight of worlds least efficient item */

#define DET(a1, a2, b1, b2)    ((a1) * (ptype) (b2) - (a2) * (ptype) (b1))
#define SWAP(a, b)   { register item t; t = *(a); *(a) = *(b); *(b) = t; }
#define NO(a,p)                ((int) ((p) - (a)->fitem + 1))
#define N(a,p)                 ((int) ((p) - (a)->d.fset))
#define SIZE(a)                ((int) (((a)->lset+1)-(a)->fset))


/* ======================================================================
				 type declarations
   ====================================================================== */

typedef int           boolean;
typedef int           ntype;   /* number of states or items           */
typedef int           itype;   /* item profits and weights            */
typedef short         mtype;   /* number of each item                 */
typedef long          stype;   /* sum of pofit or weight              */
typedef double        ptype;   /* product type (sufficient precision) */
typedef unsigned long ltype;   /* positive large sums                 */
typedef unsigned long vtype;   /* representation of vector            */

/* item record */
typedef struct irec {
  itype   p;     /* profit */
  itype   w;     /* weight */
  mtype   m;     /* number of choices */
  int     *x;    /* solution variable */
} item;

/* i-stack */
typedef struct { 
  item  *f;
  item  *l;
} interval;

/* state in dynamic programming */
typedef struct pv {
  stype psum;
  stype wsum;
  vtype vect;
} state;

/* set of states */
typedef struct pset {
  ntype       size;  /* set size                 */
  state       *fset; /* first element in set     */
  state       *lset; /* last element in set      */
} stateset;

/* reference structure */
typedef struct {
  item  *i;          /* item type changed        */
  mtype no;          /* + or - number of items   */
} reftype;

/* solution structure */
typedef struct {
  reftype  list[MAXV];
  ntype    pos;      /* current position in list */
  stype    psum;     /* profit sum of solution   */
  stype    wsum;     /* weight sum of solution   */
  vtype    vect;     /* optimal solution vector  */
  item     *a;       /* start of optimal core    */
  item     *b;       /* end of optimal core      */
} solstrct;

typedef struct { /* all problem information */
  ntype    n;               /* number of items         */
  item     *fitem;          /* first item in problem   */
  item     *litem;          /* last item in problem    */
  item     *ftouch;         /* first item considered for reduction */
  item     *ltouch;         /* last item considered for reduction */
  item     *s;              /* current core is [s,t]   */
  item     *t;              /*                         */
  item     *b;              /* break item              */
  item     *fpart;          /* first item returned by partial sort */
  item     *lpart;          /* last item returned by partial sort */
  stype    wfpart;          /* weight sum up to fpart  */
  item     *fsort;          /* first sorted item       */
  item     *lsort;          /* last sorted item        */
  stype    wfsort;          /* weight sum up to fsort  */
  stype    c;               /* current capacity        */
  stype    cstar;           /* origianl capacity       */
  stype    z;               /* current solution        */
  stype    zstar;           /* optimal solution        */
  stype    zwsum;           /* weight sum of zstar     */
  itype    ps, ws, pt, wt;  /* items for deriving bounds */

  solstrct sol;             /* current solution        */
  solstrct optsol;          /* optimal solution        */

  stype    dantzig;         /* dantzig upper bound     */
  stype    ub;              /* global upper bound      */
  stype    psumb;           /* profit sum up to b      */
  stype    wsumb;           /* weight sum up to b      */
  boolean  firsttime;       /* used for restoring x    */
  boolean  welldef;         /* is x welldefined        */
  stateset  d;              /* set of partial vectors  */
  interval *intv1, *intv2;
  interval *intv1b, *intv2b;

  /* debug */
  boolean  checked;         /* different couters used to obtain */
  long     iterates;        /* specific information about the procedure */
  long     simpreduced;
  long     pireduced;
  long     pitested;
  long     pikill;
  long     brkill;
  long     maxstages;
  long     gmaxstages;
  long     coresize;
  long     time;
} allinfo;


typedef int (*funcptr) (const void *, const void *);


/* ======================================================================
                                  error
   ====================================================================== */

void error(char *str, ...)
{
  va_list args;

  va_start(args, str);
  vprintf(str, args); printf("\n");
  va_end(args);
  printf("Program is terminated !!!\n\n");
  exit(-1);
}


/* ======================================================================
                                  palloc
   ====================================================================== */

void pfree(void *p)
{
  if (p == NULL) error("freeing null");
  free(p);
}


void *palloc(long no, long recsize)
{ 
  long size;
  char *p;

  size = no * recsize;
  if (size == 0) size = 1;
  if (size != (size_t) size) error("Alloc too big %ld", size);
  p = (char*)malloc(size);
  if (p == NULL) error("no memory size %ld", size);
  return p;
}


/* ======================================================================
				  findvect
   ====================================================================== */

state * findvect(stype ws, state *f, state *l)
{
  /* find vector i, so that i->wsum <= ws < (i+1)->wsum */
  state *m;

  /* a set should always have at least one vector */
  if (f > l) error("findvect: empty set");
  if (f->wsum >  ws) return NULL;
  if (l->wsum <= ws) return l;

  while (l - f > SYNC) {
    m = f + (l - f) / 2;
    if (m->wsum > ws) { l = m-1; } else { f = m; }
  }
  while (l->wsum > ws) l--;
  return l;
}


/* ======================================================================
				push/pop
   ====================================================================== */

void push(allinfo *a, int side, item *f, item *l)
{
  register interval *pos;
  switch (side) {
    case LEFT : pos = a->intv1; (a->intv1)++; break;
    case RIGHT: pos = a->intv2; (a->intv2)--; break;
  }
  if (a->intv1 == a->intv2) error("interval stack full");
  pos->f = f; pos->l = l;
}

void pop(allinfo *a, int side, item **f, item **l)
{
  register interval *pos;
  switch (side) {
    case LEFT : if (a->intv1 == a->intv1b) error("pop left");
		(a->intv1)--; pos = a->intv1; break;
    case RIGHT: if (a->intv2 == a->intv2b) error("pop right");
		(a->intv2)++; pos = a->intv2; break;
  }
  *f = pos->f; *l = pos->l;
}


/* ======================================================================
				improvesolution
   ====================================================================== */

void improvesolution(allinfo *a, state *v)
{
  if (v->wsum  > a->c) error("wrong improvesoluton");
  if (v->psum <= a->z) error("not improved solution");

  a->z      = v->psum;
  a->zwsum  = v->wsum;
  a->optsol = a->sol;

  a->optsol.psum = v->psum;
  a->optsol.wsum = v->wsum;
  a->optsol.vect = v->vect;
  a->optsol.a    = a->s;
  a->optsol.b    = a->t;
}


/* ======================================================================
				  definesol
   ====================================================================== */

void definesol(allinfo *a)
{
  item *f, *l, *i;
  mtype m;
  vtype j;
  stype psum, wsum, rem;
  int k;


  if (a->firsttime) {
    a->zstar = a->z + a->psumb;
    a->gmaxstages = a->maxstages;
    a->firsttime = FALSE;
  }

  psum = a->optsol.psum;
  wsum = a->optsol.wsum;
  f    = a->optsol.a;
  l    = a->optsol.b;
  if (a->optsol.a > a->optsol.b) error("no solution found");

  /* find solution vector */
  for (k = 0; k != MAXV; k++) {
    j = a->optsol.vect & ((vtype) 1 << k);
    i = a->optsol.list[k].i;
    m = a->optsol.list[k].no;
    if (i == NULL) continue;
    if (i < a->b) { if (i > f) f = i; } else { if (i < l) l = i; }
    if (j) {
      psum -= i->p * (stype) m;
      wsum -= i->w * (stype) m;
      *(i->x) += m;
    }
  }
  a->welldef = (psum == 0) && (wsum == 0);

  /* prepare for next round */
  if (!a->welldef) {
    /* printf("search again in set ]%d,%d[\n", NO(a,f), NO(a,l)); */
    a->fsort = f; /* We cannot add/subtract one, since */
    a->lsort = l; /* fractions of item f may be neded  */
    a->intv1 = a->intv1b;
    a->intv2 = a->intv2b;

    a->c  = wsum;
    a->z  = psum - 1;
    a->ub = psum;

    a->maxstages = 0;

    /* make empty solution, if not found (should not occur) */
    a->optsol.vect = 0;
    a->optsol.a    = a->b;
    a->optsol.b    = a->b-1;
  }
}


/* ======================================================================
				median
   ====================================================================== */

item *median(item *f1, item *l1, ntype s)
{
  /* Find median r of items [f1, f1+s, f1+2s, ... l1], */
  /* and ensure the ordering f1 >= r >= l1.            */
  register ptype mp, mw;
  register item *i, *j;
  item *f, *l, *k, *m, *q;
  ntype n, d;
  static item r;

  n = (l1 - f1) / s;              /* number of values      */
  f = f1;                         /* calculated first item */
  l = f1 + s * n;                 /* calculated last item  */
  k = l;                          /* saved last item       */
  q = f + s * (n / 2);            /* middle value          */

  for (;;) {
    d = (l - f + s) / s;
    m = f + s * (d / 2);

    if (d > 1) {
      if (DET(f->p, f->w, m->p, m->w) < 0) SWAP(f, m);
      if (d > 2) {
	if (DET(m->p, m->w, l->p, l->w) < 0) {
	  SWAP(m, l);
	  if (DET(f->p, f->w, m->p, m->w) < 0) SWAP(f, m);
	}
      }
    }
    if (d <= 3) { r = *q; break; }

    r.p = mp = m->p; r.w = mw = m->w; i = f; j = l;
    for (;;) {
      do { i += s; } while (DET(i->p, i->w, mp, mw) > 0);
      do { j -= s; } while (DET(j->p, j->w, mp, mw) < 0);
      if (i > j) break;
      SWAP(i, j);
    }

    if ((j <= q) && (q <= i)) break;
    if (i > q) l = j; else f = i;    
  }
  SWAP(k, l1);
  return &r;
}


/* ======================================================================
				partsort
   ====================================================================== */

void partsort(allinfo *a, item *f, item *l, stype ws, int what)
{
  register ptype mp, mw;
  register item *i, *j, *m;
  register ltype wi;
  int d;

  d = l - f + 1;
  if (d < 1) error("negative interval in partsort");
  if (d > MINMED) {
    m = median(f, l, (int) sqrt(d));
  } else {
    if (d > 1) {
      m = f + d / 2;
      if (DET(f->p, f->w, m->p, m->w) < 0) SWAP(f, m);
      if (d > 2) {
        if (DET(m->p, m->w, l->p, l->w) < 0) {
          SWAP(m, l);
          if (DET(f->p, f->w, m->p, m->w) < 0) SWAP(f, m);
        }
      }
    }
  }

  if (d > 3) {
    mp = m->p; mw = m->w; i = f; j = l; wi = ws;
    for (;;) {
      do { wi += i->m*(stype)i->w; i++; } while (DET(i->p,i->w,mp,mw) > 0);
      do {                         j--; } while (DET(j->p,j->w,mp,mw) < 0);
      if (i > j) break;
      SWAP(i, j);
    }

    if (wi <= a->cstar) {
      if (what ==  SORTALL) partsort(a, f, i-1, ws, what);
      if (what == PARTIATE) push(a, LEFT, f, i-1);
      partsort(a, i, l, wi, what);
    } else {
      if (what ==  SORTALL) partsort(a, i, l, wi, what);
      if (what == PARTIATE) push(a, RIGHT, i,  l);
      partsort(a, f, i-1, ws, what);
    }
  }

  if ((d <= 3) || (what == SORTALL)) {
    a->fpart  = f;
    a->lpart  = l;
    a->wfpart = ws;
  }
}


/* ======================================================================
				   merge
   ====================================================================== */

void merge(allinfo *a, item *h, mtype no)
{
  register state *i, *j, *k, *m;
  register stype p, w;
  register vtype mask0, mask1;
  state *r1, *rm, *d;

  if (a->d.size == 0) return;
  p = no * (stype) h->p; w = no * (stype) h->w;

  /* keep track on solution vector */
  a->sol.pos++;
  if (a->sol.pos == MAXV) a->sol.pos = 0;
  mask1 = ((vtype) 1 << a->sol.pos);
  mask0 = ~mask1;
  a->sol.list[a->sol.pos].i  = h;
  a->sol.list[a->sol.pos].no = no;

  /* initialize limits */
  d = (state*)palloc(2*a->d.size+1, sizeof(state));
  r1 = a->d.fset; rm = a->d.lset; k = d; m = rm + 1;
  k->psum = r1->psum - abs(p) - 1;
  k->wsum = r1->wsum + abs(p) + 1;
  m->wsum = rm->wsum + abs(w) + 1;

  for (i = r1, j = r1; (i != m) || (j != m); ) {
    if (i->wsum <= j->wsum + w) {
      if (i->psum > k->psum) {
	if (i->wsum > k->wsum) k++;
	k->psum = i->psum; k->wsum = i->wsum;
	k->vect = i->vect & mask0;
      }
      i++;
    } else {
      if (j->psum + p > k->psum) {
	if (j->wsum + w > k->wsum) k++;
	k->psum = j->psum + p; k->wsum = j->wsum + w;
	k->vect = j->vect | mask1;
      }
      j++;
    }
  } 

  pfree(a->d.fset);
  a->d.fset = d;
  a->d.lset = k;
  a->d.size = SIZE(&a->d);
}


/* ======================================================================
				  multiply
   ====================================================================== */

void multiply(allinfo *a, item *h, itype x, int side)
{
  mtype k;
  state *npos;

  if (a->d.size == 0) return;
  for (k = 1; x != 0; k += k) {
    if (k > x) k = x;
    merge(a, h, (side == LEFT ? -k : k));
    x -= k;
  }
  if (a->d.size > a->maxstages) a->maxstages = a->d.size;
  a->coresize++;
}


/* =========================================================================
				   simpreduce
   ========================================================================= */

void simpreduce(int side, item **f, item **l, allinfo *a)
{
  register item *i, *j, *k;
  register ptype pb, wb;
  register ptype q, r;

  if (a->d.size == 0) { *f = *l+1; return; }
  if (*l < *f) return;

  pb = a->b->p; wb = a->b->w;
  q = DET(a->z+1, a->c, pb, wb);
  r = -DET(a->z+1-a->psumb, a->c-a->wsumb, pb, wb);
  i = *f; j = *l;
  if (side == LEFT) {
    k = a->fsort - 1;
    while (i != j+1) {
      if (DET(j->p, j->w, pb, wb) > r) {
	SWAP(i, j); i++;       /* not feasible */
	a->simpreduced++;
      } else {
	SWAP(j, k); j--; k--;  /* feasible */
      }
    }
    *l = a->fsort - 1; *f = k + 1;
  } else {
    k = a->lsort + 1;
    while (i != j+1) {
      if (DET(i->p, i->w, pb, wb) < q) {
        SWAP(i, j); j--;       /* not feasible */
	a->simpreduced++;
      } else {
        SWAP(i, k); i++; k++;  /* feasible */
      }
    }
    *f = a->lsort + 1; *l = k - 1;
  }
}


/* ======================================================================
				  tighten
   ====================================================================== */

itype tighten(allinfo *a, item *i, int side)
{
  register state *j, *m;
  register ptype p, w, z, c;
  register stype d, h, mx;

  a->pitested += i->m;
  if (a->d.size == 0) {
    mx = 0;
  } else {
    if (side == RIGHT) {
      p = a->ps; w = a->ws;
      d = -DET(i->p, i->w, p, w); if (d == 0) return i->m;
      z = a->z + 1; c = a->c; mx = (c - a->d.fset->wsum) / i->w;
      if (mx >= i->m) return i->m;
      for (j = a->d.fset, m = a->d.lset + 1; j != m; j++) {
        h = DET(j->psum - z, j->wsum - c, p, w) / d;
        if (h > mx) { mx = h; if (mx >= i->m) return i->m; }
      }
    } else {
      p = a->pt; w = a->wt;
      d = DET(i->p, i->w, p, w); if (d == 0) return i->m;
      z = a->z + 1; c = a->c; mx = (a->d.lset->wsum - c) / i->w;
      if (mx >= i->m) return i->m;
      for (j = a->d.lset, m = a->d.fset - 1; j != m; j--) {
        h = DET(j->psum - z, j->wsum - c, p, w) / d;
        if (h > mx) { mx = h; if (mx >= i->m) return i->m; }
      }
    }
  }
  a->pikill += i->m - mx;
  if (mx == 0) a->pireduced++;
  return mx;
}


/* ======================================================================
				  reduceset
   ====================================================================== */

void reduceset(allinfo *a)
{
  register state *i, *m, *k;
  register ptype ps, ws, pt, wt, r;
  stype z, c;
  state *r1, *rm, *v;
  item *f, *l;

  if (a->d.size == 0) return;

  /* initialize limits */
  r1 = a->d.fset; rm = a->d.lset;
  v  = findvect(a->c, r1, rm);
  if (v == NULL) v = r1 - 1; /* all states infeasible */
  else { if (v->psum > a->z) improvesolution(a, v); }

  c  = a->c; z  = a->z + 1; k  = a->d.fset - 1;

  /* expand core, and choose ps, ws */
  if (a->s < a->fsort) {
    if (a->intv1 == a->intv1b) {
      ps = PMAX; ws = WMAX;
    } else {
      pop(a, LEFT, &f, &l);
      if (f < a->ftouch) a->ftouch = f;
      ps = f->p; ws = f->w; /* default: choose item at random */
      simpreduce(LEFT, &f, &l, a);
      if (f != l+1) {
	partsort(a, f, l, 0, SORTALL); a->fsort = f;
	ps = a->s->p; ws = a->s->w;
      }
    }
  } else {
    ps = a->s->p; ws = a->s->w;
  }

  /* expand core, and choose pt, wt */
  if (a->t > a->lsort) {
    if (a->intv2 == a->intv2b) {
      pt = PMIN; wt = WMIN;
    } else {
      pop(a, RIGHT, &f, &l);
      if (l > a->ltouch) a->ltouch = l;
      pt = l->p; wt = l->w; /* default: choose item at random */
      simpreduce(RIGHT, &f, &l, a);
      if (f <= l) {
	partsort(a, f, l, 0, SORTALL); a->lsort = l;
	pt = a->t->p; wt = a->t->w;
      }
    }
  } else {
    pt = a->t->p; wt = a->t->w;
  }

  /* now do the reduction */
  r = DET(z, c, pt, wt);
  for (i = r1, m = v+1; i != m; i++) {
    if (DET(i->psum, i->wsum, pt, wt) >= r) { k++; *k = *i; }
  }

  r = DET(z, c, ps, ws);
  for (i = v+1, m = rm+1; i != m; i++) {
    if (DET(i->psum, i->wsum, ps, ws) >= r) { k++; *k = *i; }
  }

  a->ps = ps; a->ws = ws;
  a->pt = pt; a->wt = wt;
  a->d.lset = k;
  a->d.size = SIZE(&a->d);
}


/* ======================================================================
				  initfirst
   ====================================================================== */

void initfirst(allinfo *a, stype ps, stype ws)
{
  register vtype i;
  state *k;

  a->d.size  = 1;
  a->d.fset  = (state*)palloc(a->d.size+1, sizeof(state)); /* reserve one at end */
  a->d.lset  = a->d.fset;

  /* profit and weight is calculated relatively to psumb, wsumb */
  k = a->d.fset;
  k->psum   = ps;
  k->wsum   = ws;
  k->vect   = 0;

  /* initialize emty solution structure */
  for (i = 0; i != MAXV; i++) a->sol.list[i].i = NULL;
  a->sol.pos = MAXV-1;
  a->optsol.a = a->b;
  a->optsol.b = a->b-1;
}


/* ======================================================================
				findbreak
   ====================================================================== */

void findbreak(allinfo *a)
{
  register item *i, *m;
  register ltype psum, wsum, c;
  register stype x;

  psum = 0; wsum = 0; c = a->cstar;
  for (i = a->fitem; wsum <= c; i++) {
    *(i->x) = i->m;
    psum   += i->p * (stype) i->m;
    wsum   += i->w * (stype) i->m;
//	printf("Iter %d, Psum %d Wsum %d Total %d\n", i->m, psum, wsum,c);
  }
  i--; /* we went one step too far */
  psum -= i->p * (stype) i->m;
  wsum -= i->w * (stype) i->m;

  a->fsort   = a->fpart;
  a->lsort   = a->lpart;
  a->ftouch  = a->fpart;
  a->ltouch  = a->lpart;
  a->b       = i;
  a->psumb   = psum;
  a->wsumb   = wsum;
  a->dantzig = ((c - wsum) * (ptype) i->p) / i->w;

  /* find greedy lower bound */
  for (i = a->b, m = a->litem; i <= m; i++) {
    *(i->x) = 0;
    if (wsum + i->w <= c) {
      x = (c - wsum) / i->w;
      if (x > i->m) x = i->m;
      psum += i->p * (stype) x;
      wsum += i->w * (stype) x;
    }
  }

  a->z       = psum - 1 - a->psumb;
  a->zstar   = -1;
  a->c       = a->cstar - a->wsumb;
}


/* ======================================================================
                                  copyproblem
   ====================================================================== */

void copyproblem(item *f, item *l, int *p, int *w, int *m, int *x)
{
  register item *i, *n;
  register int *pp, *ww, *mm, *xx;

  pp = p; ww = w; mm = m; xx = x; 
  for (i = f, n = l+1; i != n; i++, pp++, ww++, mm++, xx++) {
    i->p = *pp; i->w = *ww; i->m = *mm; i->x = xx;
//	printf("\n%d\t %d\t %d\t %d",i->p, i->w, i->m, i->x);
  }
}



/* ======================================================================
				bouknap
   ====================================================================== */

extern int bouknap(int n, int *p, int *w, int *m, int *x, int c)
{
  allinfo a;
  itype y;
  item *tab;
  interval *inttab;

  /* allocate space for test example and two border items */
  tab = (item *) palloc(n, sizeof(item));
  a.fitem = &tab[0]; a.litem = &tab[n-1];
  copyproblem(a.fitem, a.litem, p, w, m, x);

  /* make test instance */
  a.n           = n;
  a.cstar       = c;

  a.iterates    = 0;
  a.simpreduced = 0;
  a.pireduced   = 0;
  a.pitested    = 0;
  a.pikill      = 0;
  a.brkill      = 0;
  a.maxstages   = 0;
  a.coresize    = 0;

  inttab  = (interval*)palloc(SORTSTACK, sizeof(interval));
  a.intv1 = a.intv1b = &inttab[0];
  a.intv2 = a.intv2b = &inttab[SORTSTACK - 1];
  a.fsort = a.litem; a.lsort = a.fitem;
  partsort(&a, a.fitem, a.litem, 0, PARTIATE);
  findbreak(&a);

  a.ub        = a.dantzig;
  a.firsttime = TRUE;

  for (;;) {
    a.iterates++;

    a.s = a.b-1;
    a.t = a.b;
    initfirst(&a, 0, 0);
    reduceset(&a);

    while ((a.d.size > 0) && (a.z != a.ub)) {
      if (a.t <= a.lsort) {
	y = tighten(&a, a.t, RIGHT);
	if (y != 0) multiply(&a, a.t, y, RIGHT);
	(a.t)++;
      }
      reduceset(&a);
      if (a.s >= a.fsort) {
	y = tighten(&a, a.s, LEFT);
	if (y != 0) multiply(&a, a.s, y, LEFT);
	(a.s)--;
      }
      reduceset(&a);
    }
    pfree(a.d.fset);

    definesol(&a);
    if (a.welldef) break;
  }
  pfree(tab);
  pfree(inttab);
  return a.zstar;
}

/* ======================================================================
                                end
   ====================================================================== */

