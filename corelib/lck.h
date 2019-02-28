#ifndef LCK_H_
#define LCK_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef void* lck_t;

lck_t lck_new();

lck_t lck_del(lck_t x);

void lck_get(lck_t x);

void lck_rel(lck_t x);


#ifdef __cplusplus
}
#endif


#endif
