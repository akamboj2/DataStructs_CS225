#include <ctime>
#include "epoch.h"
/* Your code here! */
int hours(time_t x){
	return x/3600;
}
int days(time_t x){
	return x/(3600*24);
}

int years(time_t x){
	return x/(3600*24*365);
}
