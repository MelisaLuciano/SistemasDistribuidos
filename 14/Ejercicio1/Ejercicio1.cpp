#include <iostream>
#include <string.h>
#include <cmath>
#include "gfx.h"
#include <unistd.h>
#include<sys/time.h>
using namespace std;

#define ANCHURA 1500
#define ALTURA 230

int main(){
	char buffer[30];
	struct timeval ti;
	time_t curtime;
	int total,segundos,minutos,horas;
	gfx_open(ANCHURA,ALTURA,"Reloj");
	while(1){
		gfx_color(255,0,0);
		gettimeofday(&ti, NULL);
		curtime=ti.tv_sec;
		total=ti.tv_sec;
		segundos=ti.tv_sec%60;
		total=total/60;
		minutos=total%60;
		total=total/60;
		horas=total%24;
		horas=horas-6;
		if(horas<0)
			horas=horas+24;
		gfx_clear();
		gfx_display_ascii(10, 20, 14 , (horas/10)+48);
		gfx_display_ascii(150, 20, 14 , (horas%10)+48);
		gfx_fill_rectangle(300, 60, 20, 20);
		gfx_fill_rectangle(300, 150, 20, 20);
		gfx_display_ascii(365, 20, 14 , (minutos/10)+48);
		gfx_display_ascii(515, 20, 14 , (minutos%10)+48);
		gfx_fill_rectangle(665, 60, 20, 20);
		gfx_fill_rectangle(665, 150, 20, 20);
		gfx_display_ascii(720, 20, 14 , (segundos/10)+48);
		gfx_display_ascii(870, 20, 14 , (segundos%10)+48);
		gfx_fill_rectangle(1020, 60, 20, 20);
		gfx_fill_rectangle(1020, 150, 20, 20);
		gfx_display_ascii(1085, 20, 14 , (ti.tv_usec/100000)+48);
		gfx_display_ascii(1235, 20, 14 , ((ti.tv_usec/10000)%10)+48);
		gfx_flush();
		usleep(1000);
	}
}