#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<signal.h>

#include "cell_head.h2"
#include "cell_head.h3"
extern void exit_signaled(int);
extern void set_cell_entry(int, int, float);
float larger(float, float);
extern int which_dim;
extern int which_slice;
extern char *command;

int global_dim_1; 
int global_dim_2; 
int global_dim_3; 
int curr_msgq_length;
static int next_time;
unsigned int _time_step = 0;
unsigned int report_time_step = 1;
unsigned int next_report_time = 0;
int next_read_time = 0;
int NewCellX = 0;
int NewCellY = 0;
FILE *time_file = NULL;

float h=0.001000, _t0=0.0, t0=0.0, t1=0.0; /* _t0 is for rtime, _t0/t0 appear in zhux11 even without OPDE */
#define RNG_CHK(X,UB) X

/*start_up*/
#define neq(X,Y) (\
	(gen_##X != gen_##Y)|| \
	(randd_##X != randd_##Y)|| \
	(birth_##X != birth_##Y)|| \
	(dir_##X != dir_##Y)|| \
	(Ft_all_##X != Ft_all_##Y)|| \
	(F7_all_##X != F7_all_##Y)|| \
	(D_all_##X != D_all_##Y)|| \
	(Ds_all_##X != Ds_all_##Y)|| \
	(D_pol_##X != D_pol_##Y)|| \
	(pol_##X != pol_##Y) \
)

#define changed(X,Y) (0 \
	|| (gen_##X != gen_##Y) \
	|| (randd_##X != randd_##Y) \
	|| (birth_##X != birth_##Y) \
	|| (dir_##X != dir_##Y) \
	|| (Ft_all_##X != Ft_all_##Y) \
	|| (F7_all_##X != F7_all_##Y) \
	|| (D_all_##X != D_all_##Y) \
	|| (Ds_all_##X != Ds_all_##Y) \
	|| (D_pol_##X != D_pol_##Y) \
	|| (pol_##X != pol_##Y) \
)

#define eq(X,Y) (\
	(gen_##X != gen_##Y)&& \
	(randd_##X != randd_##Y)&& \
	(birth_##X != birth_##Y)&& \
	(dir_##X != dir_##Y)&& \
	(Ft_all_##X != Ft_all_##Y)&& \
	(F7_all_##X != F7_all_##Y)&& \
	(D_all_##X != D_all_##Y)&& \
	(Ds_all_##X != Ds_all_##Y)&& \
	(D_pol_##X != D_pol_##Y)&& \
	(pol_##X != pol_##Y) \
)

#define copy_cell(X,Y) { \
	gen_##X = gen_##Y; \
	randd_##X = randd_##Y; \
	birth_##X = birth_##Y; \
	dir_##X = dir_##Y; \
	Ft_all_##X = Ft_all_##Y; \
	F7_all_##X = F7_all_##Y; \
	D_all_##X = D_all_##Y; \
	Ds_all_##X = Ds_all_##Y; \
	D_pol_##X = D_pol_##Y; \
	pol_##X = pol_##Y; \
}

/*gen_cell_copy*/
#define assign_const(X,Y) { \
}

/*gen_cell_copy*/


int msgcount;

struct message {
int sender_cell_1;
int sender_cell_2;
int sender_cell_3;
char sender_obj[10];
char signal[10];
float taginfo;
};

struct message cellmsgq[2][64][64][20];
int cellmsgq_count[2][64][64];
/*end_decl_cells*/
struct Wg_type {
/*declare_fields_obj_name*/
float v;
float v10;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Fz_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct FzB_type {
/*declare_fields_obj_name*/
float v;
float v10;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Ntm_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct X_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Vg_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Fj_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Ds_P_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Ds_D_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Ft_P_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Ft_D_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct F7_P_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct F7_D_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct FtF7_P_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct FtF7_D_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct D_P_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct D_D_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct DDs_P_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct DDs_D_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Wts_type {
/*declare_fields_obj_name*/
float v;
float t;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
struct Yki_type {
/*declare_fields_obj_name*/
float v;
struct message msgq[20];
int count;
};

/*end_obj_fields*/
#define copy_object(X,Y) { \
	Wg#X = Wg#Y; \
	Fz#X = Fz#Y; \
	FzB#X = FzB#Y; \
	Ntm#X = Ntm#Y; \
	X#X = X#Y; \
	Vg#X = Vg#Y; \
	Fj#X = Fj#Y; \
	Ds_P#X = Ds_P#Y; \
	Ds_D#X = Ds_D#Y; \
	Ft_P#X = Ft_P#Y; \
	Ft_D#X = Ft_D#Y; \
	F7_P#X = F7_P#Y; \
	F7_D#X = F7_D#Y; \
	FtF7_P#X = FtF7_P#Y; \
	FtF7_D#X = FtF7_D#Y; \
	D_P#X = D_P#Y; \
	D_D#X = D_D#Y; \
	DDs_P#X = DDs_P#Y; \
	DDs_D#X = DDs_D#Y; \
	Wts#X = Wts#Y; \
	Yki#X = Yki#Y; \
}

/*gen_cell_copy_obj*/
#define assign_object(X,Y) { \
	Wg#X = Wg#Y; \
	Fz#X = Fz#Y; \
	FzB#X = FzB#Y; \
	Ntm#X = Ntm#Y; \
	X#X = X#Y; \
	Vg#X = Vg#Y; \
	Fj#X = Fj#Y; \
	Ds_P#X = Ds_P#Y; \
	Ds_D#X = Ds_D#Y; \
	Ft_P#X = Ft_P#Y; \
	Ft_D#X = Ft_D#Y; \
	F7_P#X = F7_P#Y; \
	F7_D#X = F7_D#Y; \
	FtF7_P#X = FtF7_P#Y; \
	FtF7_D#X = FtF7_D#Y; \
	D_P#X = D_P#Y; \
	D_D#X = D_D#Y; \
	DDs_P#X = DDs_P#Y; \
	DDs_D#X = DDs_D#Y; \
	Wts#X = Wts#Y; \
	Yki#X = Yki#Y; \
}

/*gen_cell_copy_obj*/

static struct Wg_type Wg[2][64][64];

static struct Fz_type Fz[2][64][64];

static struct FzB_type FzB[2][64][64];

static struct Ntm_type Ntm[2][64][64];

static struct X_type X[2][64][64];

static struct Vg_type Vg[2][64][64];

static struct Fj_type Fj[2][64][64];

static struct Ds_P_type Ds_P[2][64][64];

static struct Ds_D_type Ds_D[2][64][64];

static struct Ft_P_type Ft_P[2][64][64];

static struct Ft_D_type Ft_D[2][64][64];

static struct F7_P_type F7_P[2][64][64];

static struct F7_D_type F7_D[2][64][64];

static struct FtF7_P_type FtF7_P[2][64][64];

static struct FtF7_D_type FtF7_D[2][64][64];

static struct D_P_type D_P[2][64][64];

static struct D_D_type D_D[2][64][64];

static struct DDs_P_type DDs_P[2][64][64];

static struct DDs_D_type DDs_D[2][64][64];

static struct Wts_type Wts[2][64][64];

static struct Yki_type Yki[2][64][64];

#define DIMS 2
#define DIM_1_SIZE 64
#define DIM_2_SIZE 64

static float gen_cells[2][64][64] = {0};
static float randd_cells[2][64][64] = {0};
static float birth_cells[2][64][64] = {0};
static float dir_cells[2][64][64] = {0};
static float Ft_all_cells[2][64][64] = {0};
static float F7_all_cells[2][64][64] = {0};
static float D_all_cells[2][64][64] = {0};
static float Ds_all_cells[2][64][64] = {0};
static float D_pol_cells[2][64][64] = {0};
static float pol_cells[2][64][64] = {0};
static unsigned int dim_1_lb = 0;
static unsigned int dim_1_ub = 63;
static unsigned int dim_2_lb = 0;
static unsigned int dim_2_ub = 63;
int newborn[64][64];

#include "common.c"

#include "cell_OPDE.h"

#define in_range(INDEX_1,INDEX_2) (!dim_given || (1 \
	&& (lower[0] <= INDEX_1 && INDEX_1 <= upper[0]) \
	&& (lower[1] <= INDEX_2 && INDEX_2 <= upper[1]) \
))

void get_report_time(FILE *file) {
   int c;
   if (file == NULL) return;
   report_time_step = 0;
   while (next_read_time >= 0)
      if (1 == fscanf(file, "+%u", &report_time_step));
      else if (1 == fscanf(file, "%d", &next_read_time)) break;
      else if ((c = getc(file)) == '!') exit_signaled(0);
      else if (c == ' ' || c == '\n');
      else next_read_time = -1;
   if (report_time_step > 0) {
      next_report_time = _time_step + report_time_step;
      if (next_read_time >= 0 && next_report_time > next_read_time)
         next_report_time = next_read_time;
   } else
      next_report_time = next_read_time;
}

void init_cells(void) {
   int scan_count = scanf("%d ", &next_time);
   if (0 == scan_count || EOF == scan_count) {
      int c = getchar();
      while (c == '\n' || c == '\t' || c == ' ') c = getchar();
      if (c != EOF) {
         fprintf(stderr, "%s: read error at beginning of input file\n", command);
         exit_signaled(1);
      }
      next_time = -1;
   } else if (next_time < 0) {
      fprintf(stderr, "%s: First time in input file must be >= 0\n", command);
      exit_signaled(1);
   }
   {
      register unsigned int normal_size = 2*64*64;
      memset(gen_cells, 0, sizeof(float)*normal_size);
      memset(randd_cells, 0, sizeof(float)*normal_size);
      memset(birth_cells, 0, sizeof(float)*normal_size);
      memset(dir_cells, 0, sizeof(float)*normal_size);
      memset(Ft_all_cells, 0, sizeof(float)*normal_size);
      memset(F7_all_cells, 0, sizeof(float)*normal_size);
      memset(D_all_cells, 0, sizeof(float)*normal_size);
      memset(Ds_all_cells, 0, sizeof(float)*normal_size);
      memset(D_pol_cells, 0, sizeof(float)*normal_size);
      memset(pol_cells, 0, sizeof(float)*normal_size);

      memset(Wg, 0, sizeof(struct Wg_type)*normal_size);
      memset(Fz, 0, sizeof(struct Fz_type)*normal_size);
      memset(FzB, 0, sizeof(struct FzB_type)*normal_size);
      memset(Ntm, 0, sizeof(struct Ntm_type)*normal_size);
      memset(X, 0, sizeof(struct X_type)*normal_size);
      memset(Vg, 0, sizeof(struct Vg_type)*normal_size);
      memset(Fj, 0, sizeof(struct Fj_type)*normal_size);
      memset(Ds_P, 0, sizeof(struct Ds_P_type)*normal_size);
      memset(Ds_D, 0, sizeof(struct Ds_D_type)*normal_size);
      memset(Ft_P, 0, sizeof(struct Ft_P_type)*normal_size);
      memset(Ft_D, 0, sizeof(struct Ft_D_type)*normal_size);
      memset(F7_P, 0, sizeof(struct F7_P_type)*normal_size);
      memset(F7_D, 0, sizeof(struct F7_D_type)*normal_size);
      memset(FtF7_P, 0, sizeof(struct FtF7_P_type)*normal_size);
      memset(FtF7_D, 0, sizeof(struct FtF7_D_type)*normal_size);
      memset(D_P, 0, sizeof(struct D_P_type)*normal_size);
      memset(D_D, 0, sizeof(struct D_D_type)*normal_size);
      memset(DDs_P, 0, sizeof(struct DDs_P_type)*normal_size);
      memset(DDs_D, 0, sizeof(struct DDs_D_type)*normal_size);
      memset(Wts, 0, sizeof(struct Wts_type)*normal_size);
      memset(Yki, 0, sizeof(struct Yki_type)*normal_size);
   }
   signal(SIGFPE, bad_arith);
   get_report_time(time_file);
   const_array_readers();
}

int cellang_main (int output, int view, int filter, int field) {
   int dim_1;
   int dim_2;
   unsigned int entry = 1;
   int read_value;
   float read_float;
   int inrange = 0;
   do {
    	float field_value;
      if (_time_step == next_report_time || _time_step == next_read_time)
         if (output) printf("%lu\n", _time_step);
      entry = 0;
      while (_time_step == next_time) {
         int temp_dim_1;
         int temp_dim_2;
         int scan_count = scanf(" [%d ,%d ", &temp_dim_1, &temp_dim_2);
         dim_1 = temp_dim_1;
         dim_2 = temp_dim_2;
         entry++;
         if (0 == scan_count || EOF == scan_count) {
            scan_count = scanf("%d ", &next_time);
            if (1 == scan_count) {
               if (next_time <= _time_step) {
                  fprintf(stderr, "%s; time %lu, entry %lu: Must go forwards in time.\n", command, _time_step, entry);
                  exit_signaled(1);
               }
            }
            else if (0 == scan_count || EOF == scan_count) {
               int c = getchar();
               while (c == '\n' || c == '\t' || c == ' ') c = getchar();
               if (c != EOF) {
                  fprintf(stderr, "%s; time %lu, entry %lu: read error\n", command, _time_step, entry);
                  exit_signaled(1);
               }
               next_time = -1;
            }
            break;
         }
         else if (scan_count != 2) {
            fprintf(stderr, "%s; time %lu, entry %lu: Incorrect number of dimensions referenced\n", command, _time_step, entry);
            exit_signaled(1);
         }
         if (DIM_1_SIZE-1 < temp_dim_1 || temp_dim_1 < 0) {
            fprintf(stderr, "%s; time %lu, entry %lu: value of index 1 is out of range\n", command, _time_step, entry);
            exit_signaled(1);
         }
         if (DIM_2_SIZE-1 < temp_dim_2 || temp_dim_2 < 0) {
            fprintf(stderr, "%s; time %lu, entry %lu: value of index 2 is out of range\n", command, _time_step, entry);
            exit_signaled(1);
         }
         scanf(" ] =");
         if (output) inrange = in_range(dim_1,dim_2);
         if (_time_step == next_report_time || _time_step == next_read_time)
            if (output && inrange) printf("[%d,%d] =", dim_1, dim_2);
                  /*==========0==========*/
         if (scanf("%f",  &read_float) > 0) {
         if (11 < read_float || read_float < 0) {
            fprintf(stderr, "%s; time %lu, entry %lu: value of field 1 is out of range\n", command, _time_step, entry);
            exit_signaled(1);
         }
         gen_cells[_time_step%2][dim_1][dim_2] = read_float;
         gen_cells[(_time_step+1)%2][dim_1][dim_2] = read_float;
         } else read_float = 0;
         if (_time_step == next_report_time || _time_step == next_read_time) {
            if (output && inrange) printf("%f", read_float);
            if (field + 1 == 1) field_value = read_float;
         }
                  /*==========1==========*/
         if (scanf(" ,%f",  &read_float) > 0) {
         if (11 < read_float || read_float < 0) {
            fprintf(stderr, "%s; time %lu, entry %lu: value of field 2 is out of range\n", command, _time_step, entry);
            exit_signaled(1);
         }
         randd_cells[_time_step%2][dim_1][dim_2] = read_float;
         randd_cells[(_time_step+1)%2][dim_1][dim_2] = read_float;
         } else read_float = 0;
         if (_time_step == next_report_time || _time_step == next_read_time) {
            if (output && inrange) printf(",%f", read_float);
            if (field + 1 == 2) field_value = read_float;
         }
                  /*==========2==========*/
         if (scanf(" ,%f",  &read_float) > 0) {
         if (1001 < read_float || read_float < 0) {
            fprintf(stderr, "%s; time %lu, entry %lu: value of field 3 is out of range\n", command, _time_step, entry);
            exit_signaled(1);
         }
         birth_cells[_time_step%2][dim_1][dim_2] = read_float;
         birth_cells[(_time_step+1)%2][dim_1][dim_2] = read_float;
         } else read_float = 0;
         if (_time_step == next_report_time || _time_step == next_read_time) {
            if (output && inrange) printf(",%f", read_float);
            if (field + 1 == 3) field_value = read_float;
         }
         if (_time_step == next_report_time || _time_step == next_read_time)
            {
               if (field > 34) {
                  fprintf(stderr, "There is no field %d\n", field+1);
                  exit_signaled(1);
               }
               if (view) set_cell_entry(dim_1,  dim_2, field_value);
            }
      }
/*gen_begin_time_loop*/
      clear_screen();

      for (dim_1 = 0; dim_1 < DIM_1_SIZE; dim_1++) {
         for (dim_2 = 0; dim_2 < DIM_2_SIZE; dim_2++) {
            #include "cell_head.h1"
            global_dim_1 = dim_1;
            global_dim_2 = dim_2;
            curr_msgq_length = cellmsgq_count[_time_step%2][dim_1][dim_2];

#include "cell_objs.c"

/*begin_rules*/
         if ((_time_step == 1)) {
            _birth = (30.0 * (random() / 2147483647.0));
         } else {
            _birth = birth_cells[_time_step%2][dim_1][dim_2];
         /*by end_if()*/}
         _randd = (random() / 2147483647.0);
         if (((Vg[_time_step%2][dim_1][dim_2].v > 0.1) && (gen_cells[_time_step%2][dim_1][dim_2] == 0.0))) {
            gen_cells[(_time_step+1)%2][dim_1][dim_2] = 0.1;
         /*by end_if()*/}
         if ((((((gen_cells[_time_step%2][dim_1][dim_2] > 0.0) && (Vg[_time_step%2][dim_1][dim_2].v > 0.2)) && (Yki[_time_step%2][dim_1][dim_2].v > 0.1)) && ((_t0 - _birth) > 30.0)) && (_randd > 0.9998))) {
            if ((fabs(D_pol_cells[_time_step%2][dim_1][dim_2]) >= 2.0)) {
               gen_cells[(_time_step+1)%2][dim_1][dim_2] = (gen_cells[_time_step%2][dim_1][dim_2] + 0.1);
               dir_cells[(_time_step+1)%2][dim_1][dim_2] = 0.1;
               _dir = 0.1;
               birth_cells[(_time_step+1)%2][dim_1][dim_2] = _t0;
{/* -----copyto----- */
int empty, radius=0, emptyi=0, emptyj=0, emptyx=0, emptyy=0, emptyfail, newempx=0, newempy=0;

float old_cel_field[10];
float new_cel_field[10];
float old_obj_field[24];
float new_obj_field[24];

if (newborn[dim_1][dim_2] != 1) { /* 1.[dim_1][dim_2] is the mother cell. If the cell is newborn, skip. */
old_cel_field[0] = gen_cells[_time_step%2][dim_1][dim_2];
new_cel_field[0] = gen_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[1] = randd_cells[_time_step%2][dim_1][dim_2];
new_cel_field[1] = randd_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[2] = birth_cells[_time_step%2][dim_1][dim_2];
new_cel_field[2] = birth_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[3] = dir_cells[_time_step%2][dim_1][dim_2];
new_cel_field[3] = dir_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[4] = Ft_all_cells[_time_step%2][dim_1][dim_2];
new_cel_field[4] = Ft_all_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[5] = F7_all_cells[_time_step%2][dim_1][dim_2];
new_cel_field[5] = F7_all_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[6] = D_all_cells[_time_step%2][dim_1][dim_2];
new_cel_field[6] = D_all_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[7] = Ds_all_cells[_time_step%2][dim_1][dim_2];
new_cel_field[7] = Ds_all_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[8] = D_pol_cells[_time_step%2][dim_1][dim_2];
new_cel_field[8] = D_pol_cells[(_time_step+1) %2][dim_1][dim_2];
old_cel_field[9] = pol_cells[_time_step%2][dim_1][dim_2];
new_cel_field[9] = pol_cells[(_time_step+1) %2][dim_1][dim_2];
old_obj_field[0] = Wg[_time_step %2][dim_1][dim_2].v;
new_obj_field[0] = Wg[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[1] = Wg[_time_step %2][dim_1][dim_2].v10;
new_obj_field[1] = Wg[(_time_step+1) %2][dim_1][dim_2].v10;
old_obj_field[2] = Fz[_time_step %2][dim_1][dim_2].v;
new_obj_field[2] = Fz[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[3] = FzB[_time_step %2][dim_1][dim_2].v;
new_obj_field[3] = FzB[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[4] = FzB[_time_step %2][dim_1][dim_2].v10;
new_obj_field[4] = FzB[(_time_step+1) %2][dim_1][dim_2].v10;
old_obj_field[5] = Ntm[_time_step %2][dim_1][dim_2].v;
new_obj_field[5] = Ntm[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[6] = X[_time_step %2][dim_1][dim_2].v;
new_obj_field[6] = X[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[7] = Vg[_time_step %2][dim_1][dim_2].v;
new_obj_field[7] = Vg[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[8] = Fj[_time_step %2][dim_1][dim_2].v;
new_obj_field[8] = Fj[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[9] = Ds_P[_time_step %2][dim_1][dim_2].v;
new_obj_field[9] = Ds_P[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[10] = Ds_D[_time_step %2][dim_1][dim_2].v;
new_obj_field[10] = Ds_D[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[11] = Ft_P[_time_step %2][dim_1][dim_2].v;
new_obj_field[11] = Ft_P[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[12] = Ft_D[_time_step %2][dim_1][dim_2].v;
new_obj_field[12] = Ft_D[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[13] = F7_P[_time_step %2][dim_1][dim_2].v;
new_obj_field[13] = F7_P[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[14] = F7_D[_time_step %2][dim_1][dim_2].v;
new_obj_field[14] = F7_D[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[15] = FtF7_P[_time_step %2][dim_1][dim_2].v;
new_obj_field[15] = FtF7_P[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[16] = FtF7_D[_time_step %2][dim_1][dim_2].v;
new_obj_field[16] = FtF7_D[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[17] = D_P[_time_step %2][dim_1][dim_2].v;
new_obj_field[17] = D_P[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[18] = D_D[_time_step %2][dim_1][dim_2].v;
new_obj_field[18] = D_D[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[19] = DDs_P[_time_step %2][dim_1][dim_2].v;
new_obj_field[19] = DDs_P[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[20] = DDs_D[_time_step %2][dim_1][dim_2].v;
new_obj_field[20] = DDs_D[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[21] = Wts[_time_step %2][dim_1][dim_2].v;
new_obj_field[21] = Wts[(_time_step+1) %2][dim_1][dim_2].v;
old_obj_field[22] = Wts[_time_step %2][dim_1][dim_2].t;
new_obj_field[22] = Wts[(_time_step+1) %2][dim_1][dim_2].t;
old_obj_field[23] = Yki[_time_step %2][dim_1][dim_2].v;
new_obj_field[23] = Yki[(_time_step+1) %2][dim_1][dim_2].v;

emptyfail = 1;
/* To find an empty unit. It is [index, index] if the target unit in copyto[index, index] is empty, and i=j=radius=0 */
for (emptyi = 0; dim_1+(-1)+emptyi>1  && emptyfail==1; emptyi--) {
empty = 1; /* To temporally assume this is empty. */
if (gen_cells[(_time_step+1) %2][dim_1+(-1)+emptyi][dim_2+(0)+emptyj] != 0)
empty = 0;
if (empty == 1)
{	emptyx = emptyi;  emptyy = emptyj;  emptyfail = 0; } /* if it is trully empty */
}

if (emptyfail == 0) {/* find an empty unit at relative address [emptyi, emptyj], i.e., [emptyx, emptyy] */
while (!(emptyx == 0 && emptyy == 0)) { /* make recursive copyto until emptyx/emptyy==0 (ie current unit become empty) */
if (emptyx > 0  && emptyy > 0) {newempx = emptyx-1; newempy = emptyy-1;}
if (emptyx > 0  && emptyy ==0) {newempx = emptyx-1; newempy = emptyy;	}
if (emptyx > 0  && emptyy < 0) {newempx = emptyx-1; newempy = emptyy+1;}
if (emptyx == 0 && emptyy > 0) {newempx = emptyx;	  newempy = emptyy-1;}
if (emptyx == 0 && emptyy < 0) {newempx = emptyx;	  newempy = emptyy+1;}
if (emptyx < 0  && emptyy > 0) {newempx = emptyx+1; newempy = emptyy-1;}
if (emptyx < 0  && emptyy ==0) {newempx = emptyx+1; newempy = emptyy;	}
if (emptyx < 0  && emptyy < 0) {newempx = emptyx+1; newempy = emptyy+1;}

               gen_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = gen_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               gen_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = gen_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               randd_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = randd_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               randd_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = randd_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               birth_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = birth_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               birth_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = birth_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               dir_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = dir_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               dir_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = dir_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               Ft_all_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = Ft_all_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               Ft_all_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = Ft_all_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               F7_all_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = F7_all_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               F7_all_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = F7_all_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               D_all_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = D_all_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               D_all_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = D_all_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               Ds_all_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = Ds_all_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               Ds_all_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = Ds_all_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               D_pol_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = D_pol_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               D_pol_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = D_pol_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               pol_cells[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = pol_cells[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];
               pol_cells[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy] = pol_cells[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy];

               Wg[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Wg[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Wg[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Wg[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Wg[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v10 = Wg[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v10;
               Wg[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v10 = Wg[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v10;

               Fz[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Fz[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Fz[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Fz[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               FzB[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = FzB[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               FzB[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = FzB[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               FzB[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v10 = FzB[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v10;
               FzB[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v10 = FzB[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v10;

               Ntm[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ntm[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Ntm[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ntm[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               X[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = X[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               X[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = X[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Vg[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Vg[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Vg[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Vg[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Fj[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Fj[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Fj[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Fj[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Ds_P[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ds_P[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Ds_P[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ds_P[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Ds_D[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ds_D[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Ds_D[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ds_D[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Ft_P[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ft_P[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Ft_P[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ft_P[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Ft_D[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ft_D[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Ft_D[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Ft_D[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               F7_P[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = F7_P[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               F7_P[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = F7_P[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               F7_D[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = F7_D[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               F7_D[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = F7_D[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               FtF7_P[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = FtF7_P[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               FtF7_P[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = FtF7_P[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               FtF7_D[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = FtF7_D[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               FtF7_D[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = FtF7_D[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               D_P[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = D_P[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               D_P[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = D_P[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               D_D[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = D_D[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               D_D[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = D_D[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               DDs_P[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = DDs_P[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               DDs_P[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = DDs_P[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               DDs_D[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = DDs_D[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               DDs_D[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = DDs_D[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Wts[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Wts[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Wts[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Wts[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;

               Wts[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].t = Wts[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].t;
               Wts[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].t = Wts[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].t;

               Yki[(_time_step+1) %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Yki[(_time_step+1) %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               Yki[_time_step %2][dim_1+(-1)+emptyx][dim_2+(0)+emptyy].v = Yki[_time_step %2][dim_1+(-1)+newempx][dim_2+(0)+newempy].v;
               emptyx = newempx; emptyy = newempy;
}
gen_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[0];
gen_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[0];
randd_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[1];
randd_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[1];
birth_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[2];
birth_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[2];
dir_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[3];
dir_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[3];
Ft_all_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[4];
Ft_all_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[4];
F7_all_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[5];
F7_all_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[5];
D_all_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[6];
D_all_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[6];
Ds_all_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[7];
Ds_all_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[7];
D_pol_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[8];
D_pol_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[8];
pol_cells[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)] = new_cel_field[9];
pol_cells[_time_step %2][dim_1+(-1)][dim_2+(0)] 	  = old_cel_field[9];
Wg[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[0];
Wg[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[0];
Wg[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v10 = new_obj_field[1];
Wg[_time_step %2][dim_1+(-1)][dim_2+(0)].v10 	  = old_obj_field[1];
Fz[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[2];
Fz[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[2];
FzB[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[3];
FzB[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[3];
FzB[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v10 = new_obj_field[4];
FzB[_time_step %2][dim_1+(-1)][dim_2+(0)].v10 	  = old_obj_field[4];
Ntm[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[5];
Ntm[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[5];
X[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[6];
X[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[6];
Vg[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[7];
Vg[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[7];
Fj[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[8];
Fj[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[8];
Ds_P[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[9];
Ds_P[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[9];
Ds_D[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[10];
Ds_D[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[10];
Ft_P[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[11];
Ft_P[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[11];
Ft_D[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[12];
Ft_D[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[12];
F7_P[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[13];
F7_P[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[13];
F7_D[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[14];
F7_D[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[14];
FtF7_P[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[15];
FtF7_P[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[15];
FtF7_D[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[16];
FtF7_D[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[16];
D_P[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[17];
D_P[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[17];
D_D[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[18];
D_D[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[18];
DDs_P[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[19];
DDs_P[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[19];
DDs_D[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[20];
DDs_D[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[20];
Wts[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[21];
Wts[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[21];
Wts[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].t = new_obj_field[22];
Wts[_time_step %2][dim_1+(-1)][dim_2+(0)].t 	  = old_obj_field[22];
Yki[(_time_step+1) %2][dim_1+(-1)][dim_2+(0)].v = new_obj_field[23];
Yki[_time_step %2][dim_1+(-1)][dim_2+(0)].v 	  = old_obj_field[23];
newborn[dim_1+(-1)][dim_2+(0)] = 1;
NewCellX++;
}/* --if-emptyfail-- */
}/* -----copyto----- */
}/* -----newborn---- */

            /*by end_if()*/}
            {
               register int _i;
               for (_i = INDEX_3_LB; _i <= INDEX_3_UB; _i++) {
/*begin_forall*/
                  {
                     register int _j;
                     for (_j = INDEX_4_LB; _j <= INDEX_4_UB; _j++) {
/*begin_forall*/

                        if ((dim_1+(_i) < 64) && (dim_2+(_j) < 64) && (dim_1+(_i) >= 0) && (dim_2+(_j) >= 0)) {
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].taginfo = _dir;
                        strcpy(Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].signal, "Tsn");
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].sender_cell_1 = dim_1;
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].sender_cell_2 = dim_2;
                        strcpy(Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].sender_obj, "cell");
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count++;
                        if (Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count > 20)
                           printf("Message queue overflow in Wts. msgqsize is too small.");
                        }
                                                                                                                                                                                                                        
/*sendmsg*/

                        if ((dim_1+(_i) < 64) && (dim_2+(_j) < 64) && (dim_1+(_i) >= 0) && (dim_2+(_j) >= 0)) {
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].taginfo = 1.5;
                        strcpy(Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].signal, "Tsn");
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].sender_cell_1 = dim_1;
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].sender_cell_2 = dim_2;
                        strcpy(Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].msgq[Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count].sender_obj, "cell");
                        Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count++;
                        if (Wts[(_time_step+1)%2][dim_1+(_i)][dim_2+(_j)].count > 20)
                           printf("Message queue overflow in Wts. msgqsize is too small.");
                        }
                                                                                                                                                                                                                        
/*sendmsg*/
                     }
                  }
/*end_forall*/
               }
            }
/*end_forall*/
         /*by end_if()*/}
         randd_cells[(_time_step+1)%2][dim_1][dim_2] = _randd;
         birth_cells[(_time_step+1)%2][dim_1][dim_2] = _birth;
         Ft_all_cells[(_time_step+1)%2][dim_1][dim_2] = (Ft_P[_time_step%2][dim_1][dim_2].v + Ft_D[_time_step%2][dim_1][dim_2].v);
         F7_all_cells[(_time_step+1)%2][dim_1][dim_2] = (F7_P[_time_step%2][dim_1][dim_2].v + F7_D[_time_step%2][dim_1][dim_2].v);
         D_all_cells[(_time_step+1)%2][dim_1][dim_2] = (D_P[_time_step%2][dim_1][dim_2].v + D_D[_time_step%2][dim_1][dim_2].v);
         Ds_all_cells[(_time_step+1)%2][dim_1][dim_2] = (Ds_P[_time_step%2][dim_1][dim_2].v + Ds_D[_time_step%2][dim_1][dim_2].v);
         D_pol_cells[(_time_step+1)%2][dim_1][dim_2] = (D_D[_time_step%2][dim_1][dim_2].v / D_P[_time_step%2][dim_1][dim_2].v);
/*1-end_rules*/
{
char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
int rel_1, rel_2, rel_3;

for (msgcount = 0; msgcount < cellmsgq_count[_time_step%2][dim_1][dim_2]; msgcount++) {

rel_1 = cellmsgq[_time_step%2][dim_1][dim_2][msgcount].sender_cell_1 - dim_1;
rel_2 = cellmsgq[_time_step%2][dim_1][dim_2][msgcount].sender_cell_2 - dim_2;
strcpy(signal, cellmsgq[_time_step%2][dim_1][dim_2][msgcount].signal);
strcpy(sender, cellmsgq[_time_step%2][dim_1][dim_2][msgcount].sender_obj);
sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "cell" , tmp1, tmp2);
set_screen(full_signal);

cellmsgq[_time_step%2][dim_1][dim_2][msgcount].taginfo = 0.0;
strcpy(cellmsgq[_time_step%2][dim_1][dim_2][msgcount].signal, "");
strcpy(cellmsgq[_time_step%2][dim_1][dim_2][msgcount].sender_obj, "");
cellmsgq[_time_step%2][dim_1][dim_2][msgcount].sender_cell_1 = 0;
cellmsgq[_time_step%2][dim_1][dim_2][msgcount].sender_cell_2 = 0;
}
cellmsgq_count[_time_step%2][dim_1][dim_2] = 0;
}

}} /* finish the two for-loops executing molecule/cell programs in all cells */

/************************* delayed integration ************************/
/* C data array is from 0~N-1, we use 1~N-2, point 1 and N-2 are therefore boundary points. */
/* For D BC, we give values at point 1 and N-2,								*/
/* For N BC, we give and separately compute values at point 1 and N-2,	*/
/* For P BC, we copy 1<--N-3, N-2<--2, 											*/
/* For J BC, we copy 1<--2*para, N-2<--N-3*para, para = 0.0, 0,1, 1.0..*/
/* For PDE's del(), we compute 2~N-2, 											*/
/* For ODE's derv(), as binding is involved, we also compute 2~N-2		*/
/* u=u0+dudt and err=dudt+dudt0 should also be within 2~N-2 ?				*/
/* Anyway, cross-cellular access occurs only in del() and derv()			*/
/* So, if we build a 50x50 model, we should use 54x54 data arrays,		*/
/* the model with boundary is 52x52, and without boundary is 50x50.		*/
{
	float errfac;
	/* 1--initial, BOTH */
	for (dim_1_ode = 1; dim_1_ode < DIM_1_SIZE-1; dim_1_ode++)
	for (dim_2_ode = 1; dim_2_ode < DIM_2_SIZE-1; dim_2_ode++) {
		global_dim_1 = dim_1_ode;
		global_dim_2 = dim_2_ode;
		initial(dim_1_ode, dim_2_ode);
	}

	eqnerr=1;
	while (eqnerr == 1) {
		eqnerr=0;
		incre=1;

		/* rk2 */
		errfac = 4.0;
		eval = 0;
		boundary(); /* use Dirichlet BC for computing ux and uy at boundary points */
		for (dim_1_ode = 2; dim_1_ode < DIM_1_SIZE-2; dim_1_ode++)
		for (dim_2_ode = 2; dim_2_ode < DIM_2_SIZE-2; dim_2_ode++) {
			dsx(1); dsy(1);
			dsx(4); dsy(4);
			dsx(5); dsy(5);
		}

		boundary(); /* Neumann/Robin BC replace some computed ux and uy for computing dssx and dssy in derv() */ 
		for (dim_1_ode = 2; dim_1_ode < DIM_1_SIZE-2; dim_1_ode++)
		for (dim_2_ode = 2; dim_2_ode < DIM_2_SIZE-2; dim_2_ode++)
			derv(dim_1_ode, dim_2_ode);

		for (dim_1_ode = 1; dim_1_ode < DIM_1_SIZE-1; dim_1_ode++)
		for (dim_2_ode = 1; dim_2_ode < DIM_2_SIZE-1; dim_2_ode++)
		for (neqni=1; neqni<=neqn; neqni++)  
			u[dim_1_ode][dim_2_ode][neqni] = u0[dim_1_ode][dim_2_ode][neqni] + dudt0[dim_1_ode][dim_2_ode][neqni]*h;
		t1=t0+h;

		eval = 1;
		boundary(); /* Dirichlet BC set for computing ux and uy */
		for (dim_1_ode = 2; dim_1_ode < DIM_1_SIZE-2; dim_1_ode++)
		for (dim_2_ode = 2; dim_2_ode < DIM_2_SIZE-2; dim_2_ode++) {
			dsx(1); dsy(1);
			dsx(4); dsy(4);
			dsx(5); dsy(5);
		}

		boundary(); /* Neumann/Robin BC replace some computed ux and uy for computing dssx and dssy in derv() */ 
		for (dim_1_ode = 2; dim_1_ode < DIM_1_SIZE-2; dim_1_ode++)
		for (dim_2_ode = 2; dim_2_ode < DIM_2_SIZE-2; dim_2_ode++)
			derv(dim_1_ode, dim_2_ode);

		for (dim_1_ode = 1; dim_1_ode < DIM_1_SIZE-1; dim_1_ode++)
		for (dim_2_ode = 1; dim_2_ode < DIM_2_SIZE-1; dim_2_ode++)
		for (neqni=1; neqni<=neqn; neqni++)  {
			err[dim_1_ode][dim_2_ode][neqni]=(dudt[dim_1_ode][dim_2_ode][neqni] - dudt0[dim_1_ode][dim_2_ode][neqni])*h/2.0;
			  u[dim_1_ode][dim_2_ode][neqni] =   u[dim_1_ode][dim_2_ode][neqni] +   err[dim_1_ode][dim_2_ode][neqni];
		}

		/* 3a--adaptive h version: reduce h whenever a cell is wrong */
		for (dim_1_ode = 1; dim_1_ode < DIM_1_SIZE-1; dim_1_ode++) {
		if (eqnerr==1) break;
			for (dim_2_ode = 1; dim_2_ode < DIM_2_SIZE-1; dim_2_ode++) {
				if (eqnerr==1) break;				
				for (neqni=1; neqni<=neqn; neqni++)  {
					if (fabs(err[dim_1_ode][dim_2_ode][neqni]) > (fabs(u[dim_1_ode][dim_2_ode][neqni])*relerr+abserr)) {
						eqnerr = 1;
						incre = 0;	
						h = h/2.0;	
						/* if (h<hmin) { h=hmin; eqnerr=0; } */
					}
				}	
			}
		}
		if (eqnerr==0) {
			for (dim_1_ode = 1; dim_1_ode < DIM_1_SIZE-1; dim_1_ode++)
			for (dim_2_ode = 1; dim_2_ode < DIM_2_SIZE-1; dim_2_ode++)
			for (neqni=1; neqni<=neqn; neqni++) {
				u0[dim_1_ode][dim_2_ode][neqni] = u[dim_1_ode][dim_2_ode][neqni];
				if (fabs(err[dim_1_ode][dim_2_ode][neqni]) > ((fabs(u[dim_1_ode][dim_2_ode][neqni])*relerr+abserr)/errfac))
					incre=0;
			}
		}

		/* 4--update t0 and OPDE-computed fields after all cells, BOTH fixed/adjustable t */
		/* Note if in obj a value is assigned to an OPDE-computed field, the assignment is invalid by the updation here. */
		if (eqnerr==0) {
			for (dim_1_ode = 1; dim_1_ode < DIM_1_SIZE-1; dim_1_ode++)
			for (dim_2_ode = 1; dim_2_ode < DIM_2_SIZE-1; dim_2_ode++) {
		/*	Note: initial() is from 0 to DIM_1_SIZE for u0[][] to inherit all values from ato[][][] etc.*/
			Wg[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][1];
			Fz[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][2];
			FzB[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][3];
			Ntm[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][4];
			X[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][5];
			Vg[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][6];
			Fj[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][7];
			Ds_P[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][8];
			Ds_D[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][9];
			Ft_P[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][10];
			Ft_D[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][11];
			F7_P[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][12];
			F7_D[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][13];
			FtF7_P[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][14];
			FtF7_D[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][15];
			D_P[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][16];
			D_D[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][17];
			DDs_P[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][18];
			DDs_D[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][19];
			Wts[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][20];
			Yki[(_time_step+1)%2][dim_1_ode][dim_2_ode].v = u[dim_1_ode][dim_2_ode][21];
			}
			t0=t1; _t0=t0;
			if (incre == 1) {
				h=h*2.0;
			}
		}
	} /* while */
} /* integration */

/************************* delayed integration ************************/

for (dim_1 = 0; dim_1 < DIM_1_SIZE; dim_1++) {
for (dim_2 = 0; dim_2 < DIM_2_SIZE; dim_2++) {

            if (1 == report_time_step || (report_time_step != 1 && (_time_step == next_report_time || _time_step == next_read_time))) {
               if (view && field < 34) {
                     switch (field) {
                     case 0: { field_value =(float)gen_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 1: { field_value =(float)randd_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 2: { field_value =(float)birth_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 3: { field_value =(float)dir_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 4: { field_value =(float)Ft_all_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 5: { field_value =(float)F7_all_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 6: { field_value =(float)D_all_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 7: { field_value =(float)Ds_all_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 8: { field_value =(float)D_pol_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 9: { field_value =(float)pol_cells[(_time_step+1)%2][dim_1][dim_2]; break; }
                     case 10: { field_value = (float)Wg[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 11: { field_value = (float)Wg[(_time_step+1)%2][dim_1][dim_2].v10; break; }
                     case 12: { field_value = (float)Fz[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 13: { field_value = (float)FzB[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 14: { field_value = (float)FzB[(_time_step+1)%2][dim_1][dim_2].v10; break; }
                     case 15: { field_value = (float)Ntm[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 16: { field_value = (float)X[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 17: { field_value = (float)Vg[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 18: { field_value = (float)Fj[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 19: { field_value = (float)Ds_P[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 20: { field_value = (float)Ds_D[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 21: { field_value = (float)Ft_P[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 22: { field_value = (float)Ft_D[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 23: { field_value = (float)F7_P[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 24: { field_value = (float)F7_D[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 25: { field_value = (float)FtF7_P[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 26: { field_value = (float)FtF7_D[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 27: { field_value = (float)D_P[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 28: { field_value = (float)D_D[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 29: { field_value = (float)DDs_P[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 30: { field_value = (float)DDs_D[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 31: { field_value = (float)Wts[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     case 32: { field_value = (float)Wts[(_time_step+1)%2][dim_1][dim_2].t; break; }
                     case 33: { field_value = (float)Yki[(_time_step+1)%2][dim_1][dim_2].v; break; }
                     default: {
                        fprintf(stderr, "There is no field %d\n", field+1);
                        exit_signaled(1);
                     }
                  }
                  set_cell_entry(dim_1,  dim_2, field_value);
               }
               if (output) inrange = in_range(dim_1,dim_2);
               if (output && inrange && (report_time_step != 1 || changed(cells[(_time_step+1)%2][dim_1][dim_2], cells[_time_step%2][dim_1][dim_2]))) {
               printf("[%d,%d] =%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"
                  ,dim_1,dim_2
                  , gen_cells[(_time_step+1)%2][dim_1][dim_2]
                  , randd_cells[(_time_step+1)%2][dim_1][dim_2]
                  , birth_cells[(_time_step+1)%2][dim_1][dim_2]
                  , dir_cells[(_time_step+1)%2][dim_1][dim_2]
                  , Ft_all_cells[(_time_step+1)%2][dim_1][dim_2]
                  , F7_all_cells[(_time_step+1)%2][dim_1][dim_2]
                  , D_all_cells[(_time_step+1)%2][dim_1][dim_2]
                  , Ds_all_cells[(_time_step+1)%2][dim_1][dim_2]
                  , D_pol_cells[(_time_step+1)%2][dim_1][dim_2]
                  , pol_cells[(_time_step+1)%2][dim_1][dim_2]
                  ,Wg[(_time_step+1)%2][dim_1][dim_2].v
                  ,Wg[(_time_step+1)%2][dim_1][dim_2].v10
                  ,Fz[(_time_step+1)%2][dim_1][dim_2].v
                  ,FzB[(_time_step+1)%2][dim_1][dim_2].v
                  ,FzB[(_time_step+1)%2][dim_1][dim_2].v10
                  ,Ntm[(_time_step+1)%2][dim_1][dim_2].v
                  ,X[(_time_step+1)%2][dim_1][dim_2].v
                  ,Vg[(_time_step+1)%2][dim_1][dim_2].v
                  ,Fj[(_time_step+1)%2][dim_1][dim_2].v
                  ,Ds_P[(_time_step+1)%2][dim_1][dim_2].v
                  ,Ds_D[(_time_step+1)%2][dim_1][dim_2].v
                  ,Ft_P[(_time_step+1)%2][dim_1][dim_2].v
                  ,Ft_D[(_time_step+1)%2][dim_1][dim_2].v
                  ,F7_P[(_time_step+1)%2][dim_1][dim_2].v
                  ,F7_D[(_time_step+1)%2][dim_1][dim_2].v
                  ,FtF7_P[(_time_step+1)%2][dim_1][dim_2].v
                  ,FtF7_D[(_time_step+1)%2][dim_1][dim_2].v
                  ,D_P[(_time_step+1)%2][dim_1][dim_2].v
                  ,D_D[(_time_step+1)%2][dim_1][dim_2].v
                  ,DDs_P[(_time_step+1)%2][dim_1][dim_2].v
                  ,DDs_D[(_time_step+1)%2][dim_1][dim_2].v
                  ,Wts[(_time_step+1)%2][dim_1][dim_2].v
                  ,Wts[(_time_step+1)%2][dim_1][dim_2].t
                  ,Yki[(_time_step+1)%2][dim_1][dim_2].v
                  );
               }
            }
      } }	/* finish the two for-loop */

/********** 200610 for copyto *************/
for (dim_1 = 0; dim_1 < DIM_1_SIZE; dim_1++)
for (dim_2 = 0; dim_2 < DIM_2_SIZE; dim_2++)
newborn[dim_1][dim_2] = 0;
/********** 200610 for copyto *************/

      if (output) {
         if (_time_step == next_read_time)
            get_report_time(time_file);
         else if (report_time_step > 0 && _time_step >= next_report_time)
            next_report_time = _time_step + report_time_step;
         if (!view) _time_step++;
      }

   } while (!view);
   return 0;
}

int max_value_width[] = {2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

char field_names[273] = "gen     randd   birth   dir     Ft_all  F7_all  D_all   Ds_all  D_pol   pol     Wg.v    Wg.v10  Fz.v    FzB.v   FzB.v10 Ntm.v   X.v     Vg.v    Fj.v    Ds_P.v  Ds_D.v  Ft_P.v  Ft_D.v  F7_P.v  F7_D.v  FtF7_P.vFtF7_D.vD_P.v   D_D.v   DDs_P.v DDs_D.v Wts.v   Wts.t   Yki.v   ";
int field_name_length = 8;
int field_count = 34;


char signal_names[505] = "FzB_Act_Ntm_0_0   FzB_Act_Vg_0_0    FzB_Act_X_0_0     Ntm_Rep_FzB_0_0   X_Rep_Vg_0_0      Vg_Act_Vg_0_0     Vg_Act_Fj_0_0     Vg_Rep_Ds_P_0_0   Vg_Rep_Ds_D_0_0   F7_P_Ubq_D_P_0_0  F7_P_Ubq_Ds_P_0_0 F7_P_Ubq_DDs_P_0_0F7_D_Ubq_D_D_0_0  F7_D_Ubq_Ds_D_0_0 F7_D_Ubq_DDs_D_0_0D_P_Rep_Wts_0_0   Wts_Rep_Yki_0_0   Yki_Act_Vg_0_0    Yki_Act_Wts_0_0   cell_Tsn_Wts_n1_n1cell_Tsn_Wts_n1_0 cell_Tsn_Wts_n1_p1cell_Tsn_Wts_0_n1 cell_Tsn_Wts_0_0  cell_Tsn_Wts_0_p1 cell_Tsn_Wts_p1_n1cell_Tsn_Wts_p1_0 cell_Tsn_Wts_p1_p1";
int signal_name_length = 18;
int signal_count = 28;


char object_names[127] = "DDs_D DDs_P D_D   D_P   Ds_D  Ds_P  F7_D  F7_P  Fj    FtF7_DFtF7_PFt_D  Ft_P  Fz    FzB   Ntm   Vg    Wg    Wts   X     Yki   ";
int object_name_length = 6;
int object_count = 21;


char message_names[16] = "ActRepP  D  Tsn";
int message_name_length = 3;
int message_count = 5;

int  net[2][21][21];
FILE *net_file = NULL;
char  net_name[100]="";

void net_clear(void);
void net_update(int, int, int);
int  net_change(int, int);

void net_clear() {
	int i,j;
	for (i = 0; i < object_count; i++)
	for (j = 0; j < object_count; j++)
		net[_time_step%2][i][j] = 0;
}
void net_update(obj1, obj2, mess) {
	net[_time_step%2][obj1][obj2] = mess+1;
}
int  net_change(xpos, ypos) {
	int	i, j, changed = 0;
	for (i = 0; i < object_count; i++)
	for (j = 0; j < object_count; j++)
		if (net[_time_step%2][i][j] != net[(_time_step-1)%2][i][j])
			changed = 1;

	if (changed == 1) {
		strncpy(net_name, "", 100);
		sprintf(net_name, "net[%d-%d]at[%d-%0.2f]", xpos, ypos, _time_step, t0);
		net_file = fopen(net_name, "w");
		for (i = 0; i < object_count; i++) {
			for (j = 0; j < object_count; j++)
				fprintf(net_file, "%d ", net[_time_step%2][i][j]);
			fprintf(net_file, "\n");
		}
		fclose(net_file);
	}
	return changed;
}

float get_field(int field, int dim_1, int dim_2) {
switch (field) {
case 0: return (float)gen_cells[(_time_step+1)%2][dim_1][dim_2];
case 1: return (float)randd_cells[(_time_step+1)%2][dim_1][dim_2];
case 2: return (float)birth_cells[(_time_step+1)%2][dim_1][dim_2];
case 3: return (float)dir_cells[(_time_step+1)%2][dim_1][dim_2];
case 4: return (float)Ft_all_cells[(_time_step+1)%2][dim_1][dim_2];
case 5: return (float)F7_all_cells[(_time_step+1)%2][dim_1][dim_2];
case 6: return (float)D_all_cells[(_time_step+1)%2][dim_1][dim_2];
case 7: return (float)Ds_all_cells[(_time_step+1)%2][dim_1][dim_2];
case 8: return (float)D_pol_cells[(_time_step+1)%2][dim_1][dim_2];
case 9: return (float)pol_cells[(_time_step+1)%2][dim_1][dim_2];
case 10: return (float)Wg[(_time_step+1)%2][dim_1][dim_2].v;
case 11: return (float)Wg[(_time_step+1)%2][dim_1][dim_2].v10;
case 12: return (float)Fz[(_time_step+1)%2][dim_1][dim_2].v;
case 13: return (float)FzB[(_time_step+1)%2][dim_1][dim_2].v;
case 14: return (float)FzB[(_time_step+1)%2][dim_1][dim_2].v10;
case 15: return (float)Ntm[(_time_step+1)%2][dim_1][dim_2].v;
case 16: return (float)X[(_time_step+1)%2][dim_1][dim_2].v;
case 17: return (float)Vg[(_time_step+1)%2][dim_1][dim_2].v;
case 18: return (float)Fj[(_time_step+1)%2][dim_1][dim_2].v;
case 19: return (float)Ds_P[(_time_step+1)%2][dim_1][dim_2].v;
case 20: return (float)Ds_D[(_time_step+1)%2][dim_1][dim_2].v;
case 21: return (float)Ft_P[(_time_step+1)%2][dim_1][dim_2].v;
case 22: return (float)Ft_D[(_time_step+1)%2][dim_1][dim_2].v;
case 23: return (float)F7_P[(_time_step+1)%2][dim_1][dim_2].v;
case 24: return (float)F7_D[(_time_step+1)%2][dim_1][dim_2].v;
case 25: return (float)FtF7_P[(_time_step+1)%2][dim_1][dim_2].v;
case 26: return (float)FtF7_D[(_time_step+1)%2][dim_1][dim_2].v;
case 27: return (float)D_P[(_time_step+1)%2][dim_1][dim_2].v;
case 28: return (float)D_D[(_time_step+1)%2][dim_1][dim_2].v;
case 29: return (float)DDs_P[(_time_step+1)%2][dim_1][dim_2].v;
case 30: return (float)DDs_D[(_time_step+1)%2][dim_1][dim_2].v;
case 31: return (float)Wts[(_time_step+1)%2][dim_1][dim_2].v;
case 32: return (float)Wts[(_time_step+1)%2][dim_1][dim_2].t;
case 33: return (float)Yki[(_time_step+1)%2][dim_1][dim_2].v;
default:
fprintf(stderr, "%s: Field %d doesn't exist\n", command, field);
exit_signaled(1);
}
}

float cell_field_value(int field, int dim_1, int dim_2) {
return get_field(field, dim_1, dim_2);
}

int get_msg_screen(int dim_1, int dim_2, int signal) {
return msg_screen[dim_1][dim_2][signal];
}

int pos(int dimension) {
if (dimension==1) return global_dim_1;
if (dimension==2) return global_dim_2;
if (dimension==3) return global_dim_3;
}

float fpos(int dimension) {
if (dimension==1) return global_dim_1;
if (dimension==2) return global_dim_2;
if (dimension==3) return global_dim_3;
}

int position(int dimension) {
if (dimension==1) return global_dim_1;
if (dimension==2) return global_dim_2;
if (dimension==3) return global_dim_3;
}

int length(void) {
return curr_msgq_length;
}

float larger(float a, float b) {
if (a >= b) return a;
else return b;
}

/********* OPDE *********/
void derv(int dim_1, int dim_2) {
	if (eval==0) {
		#include "cell_OPDEderv0.c"
	} else {
		#include "cell_OPDEderv1.c"
	}
}

void initial(int dim_1, int dim_2) {
	if (t0==0) {
		if (Wgff[dim_1][dim_2]==1)
			u0[dim_1][dim_2][1]=1.0;
		if (Wgff[dim_1][dim_2]==2)
			u0[dim_1][dim_2][1]=0.0;
		u0[dim_1][dim_2][2]=0.02;
		u0[dim_1][dim_2][3]=0.0;
		if (Ntmff[dim_1][dim_2]==1)
			u0[dim_1][dim_2][4]=0.0;
		if (Ntmff[dim_1][dim_2]==2)
			u0[dim_1][dim_2][4]=0.0;
		if (Xff[dim_1][dim_2]==1)
			u0[dim_1][dim_2][5]=0.0;
		if (Xff[dim_1][dim_2]==2)
			u0[dim_1][dim_2][5]=0.0;
		u0[dim_1][dim_2][6]=0.0;
		u0[dim_1][dim_2][7]=0.0;
		u0[dim_1][dim_2][8]=0.5;
		u0[dim_1][dim_2][9]=0.5;
		u0[dim_1][dim_2][10]=0.5;
		u0[dim_1][dim_2][11]=0.5;
		u0[dim_1][dim_2][12]=0.5;
		u0[dim_1][dim_2][13]=0.5;
		u0[dim_1][dim_2][14]=0.0;
		u0[dim_1][dim_2][15]=0.0;
		u0[dim_1][dim_2][16]=0.5;
		u0[dim_1][dim_2][17]=0.5;
		u0[dim_1][dim_2][18]=0.0;
		u0[dim_1][dim_2][19]=0.0;
		u0[dim_1][dim_2][20]=0.5;
		u0[dim_1][dim_2][21]=0.5;
	} else {
			u0[dim_1][dim_2][1]=Wg[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][2]=Fz[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][3]=FzB[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][4]=Ntm[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][5]=X[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][6]=Vg[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][7]=Fj[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][8]=Ds_P[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][9]=Ds_D[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][10]=Ft_P[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][11]=Ft_D[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][12]=F7_P[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][13]=F7_D[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][14]=FtF7_P[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][15]=FtF7_D[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][16]=D_P[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][17]=D_D[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][18]=DDs_P[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][19]=DDs_D[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][20]=Wts[_time_step%2][dim_1][dim_2].v;
			u0[dim_1][dim_2][21]=Yki[_time_step%2][dim_1][dim_2].v;
	}
}
void boundary() {
int dim_1, dim_2;
	if (eval==0) {
	/* XL */
	dim_1=1;
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		u0x[1][dim_2][1] =  (-0.5 * Wg[_time_step%2][dim_1][dim_2].v) - 0.0 * u0[1][dim_2][1]; u0[1][dim_2][1] = (dx * (-0.5 * Wg[_time_step%2][dim_1][dim_2].v) + u0[2][dim_2][1])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		u0x[1][dim_2][4] =  (-0.5 * Ntm[_time_step%2][dim_1][dim_2].v) - 0.0 * u0[1][dim_2][4]; u0[1][dim_2][4] = (dx * (-0.5 * Ntm[_time_step%2][dim_1][dim_2].v) + u0[2][dim_2][4])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		u0x[1][dim_2][5] =  (-0.5 * X[_time_step%2][dim_1][dim_2].v) - 0.0 * u0[1][dim_2][5]; u0[1][dim_2][5] = (dx * (-0.5 * X[_time_step%2][dim_1][dim_2].v) + u0[2][dim_2][5])/(1.0 + dx * 0.0);
		}
	/* XU */
	dim_1=DIM_1_SIZE-3;
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		u0x[DIM_1_SIZE-2][dim_2][1] =  0.0 - 0.0 * u0[DIM_1_SIZE-2][dim_2][1]; u0[DIM_1_SIZE-2][dim_2][1] = (dx * 0.0 + u0[DIM_1_SIZE-3][dim_2][1])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		u0x[DIM_1_SIZE-2][dim_2][4] =  0.0 - 0.0 * u0[DIM_1_SIZE-2][dim_2][4]; u0[DIM_1_SIZE-2][dim_2][4] = (dx * 0.0 + u0[DIM_1_SIZE-3][dim_2][4])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		u0x[DIM_1_SIZE-2][dim_2][5] =  0.0 - 0.0 * u0[DIM_1_SIZE-2][dim_2][5]; u0[DIM_1_SIZE-2][dim_2][5] = (dx * 0.0 + u0[DIM_1_SIZE-3][dim_2][5])/(1.0 + dx * 0.0);
		}
	/* YL */
	dim_2=1;
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u0[dim_1][1][1]=u0[dim_1][DIM_2_SIZE-3][1];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u0[dim_1][1][4]=u0[dim_1][DIM_2_SIZE-3][4];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u0[dim_1][1][5]=u0[dim_1][DIM_2_SIZE-3][5];
		}
	/* YU */
	dim_2=DIM_2_SIZE-3;
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u0[dim_1][DIM_2_SIZE-2][1]=u0[dim_1][2][1];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u0[dim_1][DIM_2_SIZE-2][4]=u0[dim_1][2][4];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u0[dim_1][DIM_2_SIZE-2][5]=u0[dim_1][2][5];
		}

	} else {
	/* XL */
	dim_1=1;
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		 ux[1][dim_2][1] =  (-0.5 * Wg[_time_step%2][dim_1][dim_2].v) - 0.0 * u[1][dim_2][1];  u[1][dim_2][1] = (dx * (-0.5 * Wg[_time_step%2][dim_1][dim_2].v) + u[2][dim_2][1])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		 ux[1][dim_2][4] =  (-0.5 * Ntm[_time_step%2][dim_1][dim_2].v) - 0.0 * u[1][dim_2][4];  u[1][dim_2][4] = (dx * (-0.5 * Ntm[_time_step%2][dim_1][dim_2].v) + u[2][dim_2][4])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		 ux[1][dim_2][5] =  (-0.5 * X[_time_step%2][dim_1][dim_2].v) - 0.0 * u[1][dim_2][5];  u[1][dim_2][5] = (dx * (-0.5 * X[_time_step%2][dim_1][dim_2].v) + u[2][dim_2][5])/(1.0 + dx * 0.0);
		}
	/* XU */
	dim_1=DIM_1_SIZE-3;
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		 ux[DIM_1_SIZE-2][dim_2][1] =  0.0 - 0.0 * u[DIM_1_SIZE-2][dim_2][1];  u[DIM_1_SIZE-2][dim_2][1] = (dx * 0.0 + u[DIM_1_SIZE-3][dim_2][1])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		 ux[DIM_1_SIZE-2][dim_2][4] =  0.0 - 0.0 * u[DIM_1_SIZE-2][dim_2][4];  u[DIM_1_SIZE-2][dim_2][4] = (dx * 0.0 + u[DIM_1_SIZE-3][dim_2][4])/(1.0 + dx * 0.0);
		}
		for (dim_2=1; dim_2<DIM_2_SIZE-1; dim_2++) {
		 ux[DIM_1_SIZE-2][dim_2][5] =  0.0 - 0.0 * u[DIM_1_SIZE-2][dim_2][5];  u[DIM_1_SIZE-2][dim_2][5] = (dx * 0.0 + u[DIM_1_SIZE-3][dim_2][5])/(1.0 + dx * 0.0);
		}
	/* YL */
	dim_2=1;
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u[dim_1][1][1]= u[dim_1][DIM_2_SIZE-3][1];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u[dim_1][1][4]= u[dim_1][DIM_2_SIZE-3][4];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u[dim_1][1][5]= u[dim_1][DIM_2_SIZE-3][5];
		}
	/* YU */
	dim_2=DIM_2_SIZE-3;
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u[dim_1][DIM_2_SIZE-2][1]=u[dim_1][2][1];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u[dim_1][DIM_2_SIZE-2][4]=u[dim_1][2][4];
		}
		for (dim_1=1; dim_1<DIM_1_SIZE-1; dim_1++) {
		u[dim_1][DIM_2_SIZE-2][5]=u[dim_1][2][5];
		}
	}
}

void dsx(int num) {
	if (eval==0) {
			u0x[dim_1_ode][dim_2_ode][num] = (1.0/(2*dx))*(u0[dim_1_ode+1][dim_2_ode][num] - u0[dim_1_ode-1][dim_2_ode][num]);
	} else {
			ux[dim_1_ode][dim_2_ode][num] = (1.0/(2*dx))*(u[dim_1_ode+1][dim_2_ode][num] - u[dim_1_ode-1][dim_2_ode][num]);
	}
}

void dsy(int num) {
	if (eval==0) {
			u0y[dim_1_ode][dim_2_ode][num] = (1.0/(2*dy))*(u0[dim_1_ode][dim_2_ode+1][num] - u0[dim_1_ode][dim_2_ode-1][num]);
	} else {
			uy[dim_1_ode][dim_2_ode][num] = (1.0/(2*dy))*(u[dim_1_ode][dim_2_ode+1][num] - u[dim_1_ode][dim_2_ode-1][num]);
	}
}

float dssx(float nouse, int num) {
float dssxv;
	if (eval==0) {
			dssxv=(u0[dim_1_ode+1][dim_2_ode][num] - 2.0*u0[dim_1_ode][dim_2_ode][num] + u0[dim_1_ode-1][dim_2_ode][num])/(dx*dx);
	} else {
			dssxv=(u[dim_1_ode+1][dim_2_ode][num] - 2.0*u[dim_1_ode][dim_2_ode][num] + u[dim_1_ode-1][dim_2_ode][num])/(dx*dx);
	}
return dssxv;
}

float dssy(float nouse, int num) {
float dssyv;
	if (eval==0) {
			dssyv=(u0[dim_1_ode][dim_2_ode+1][num] - 2.0*u0[dim_1_ode][dim_2_ode][num] + u0[dim_1_ode][dim_2_ode-1][num])/(dy*dy);
	} else {
			dssyv=(u[dim_1_ode][dim_2_ode+1][num] - 2.0*u[dim_1_ode][dim_2_ode][num] + u[dim_1_ode][dim_2_ode-1][num])/(dy*dy);
	}
return dssyv;
}

float del(float nouse, int num) {
float delv;
	delv= dssx(nouse, num) + dssy(nouse, num);
return delv;
}
float Ha(float field, float para, float n) {
return pow(field,n)/(pow(para,n)+pow(field,n));
}
float Hr(float field, float para, float n) {
return pow(para,n)/(pow(para,n)+pow(field,n));
}
float Ub(float field, float para, float n) {
return pow(field,n)/(pow(para,n)+pow(field,n));
}

/*2-end_rules*/
