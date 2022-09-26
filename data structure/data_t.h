#ifndef DATA_T_H    // DATA_T_H가 정의되어 있지 않다면
#define DATA_T_H    // DATA_T_H 매크로 정의
typedef void* data_t;
typedef enum {
	FALSE,
	TRUE
}eBool_t;

typedef eBool_t is_success_t;
#endif				// #ifndef DATA_T_H 끝