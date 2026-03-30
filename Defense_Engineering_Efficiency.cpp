#define _CRT_SECURE_NO_WARNINGS
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
# define PI 3.14159265
#define N 100
#define W 10000

//全局变量定义
int ttch;
int i, j, k, m, t[N + 1];
int cch, ch, ch1, ch2, ch3, ch4;
double x[N + 1], y[N + 1];
double x_1, y_1;
double xd, yd, xdp, ydp, ed, ef, bd, bf, ridp[N + 1], re1, re2, re3, re4;
double xdd, ydd, cep, ridd[N + 1], re11, re22;
int n3, m3;
double h, v11, a, ex, ey, xhd, yhd, re31, re32, hx, hy, rihd[N + 1];
double ed4, ef4, xh, yh, re41, re42, xhj, yhj, bd1, bf1, re43, re44, rihj[N + 1];

//统计模块至结束所需变量
int v1 = 0, v[N + 1];
long m10 = 1, tt[W + 1];
double p = 0.0, temp = 0.0, tt1 = 0.0, tt2 = 0.0, p11 = 0.0, p22 = 0.0, d;
double u1 = 0.0, u2 = 0.0, epsl, p1;
//统计模块至结束所需变量

//目标值的输入函数
void mubiao(void) {
	printf("请输入定位目标M（目标个数）（整数型）的值？\n");
	scanf("%d", &m);
	printf("请输入集群目标坐标值(x[i],y[i])（实数型）(i=1,2,...n.)\n");
	for (i = 1; i <= m; i++) {
		scanf("%lf%lf", &x[i], &y[i]);
	}
	x_1 = x[1]; y_1 = y[1];
	for (i = 2; i <= m; i++) {
		x_1 = x_1 + x[i];
		y_1 = y_1 + y[i];
	}
	x_1 = x_1 / m; y_1 = y_1 / m;
	printf("目标瞄准点为：X1=%1=%lf,Y1= %lf.\n", x_1, y_1);
}

//公共输入函数
void ggshuru(void) {
	printf("请输入各目标的掩蔽数Vi（整数型）(i=1,2,...%d.)\n", m);
	for (i = 1; i <= m; i++) { scanf("%d", &v[i]);}
	for (i = 1; i <= m; i++) { v1 = v1 + v[i];}
	printf("总掩蔽数为：v1=%d.\n", v1);
	printf("请输入模拟精度（实数型）：\n");
	scanf("%lf", &epsl);
	printf("\n");
}

//地面火炮打击程序变量输入函数
void dmshuru(void)
{
	//请输入地面火炮打击程序
	printf("/*请输入地面火炮打击程序中各变量的值*/\n");
	printf("请输入地面火炮攻击的炮弹数(整数型):\n");
	scanf("%d", &ch1);

	printf("请输入诸元中间误差 Ed,Ef(实数型)\n");
	scanf("%lf%lf", &ed, &ef);

	printf("请输入中间误差 Bd,Bf(实数型)\n");
	scanf("%lf%lf", &bd, &bf);

	printf("请输入对目标的等效炸伤圆半径 Ridp[i](实数型)\n");
	for (i = 1; i <= m; i++)
	{
		scanf("%lf", &ridp[i]);
	}
}

//地面火炮打击模块函数
void dmhpdj(void) {
	for (j = 1; j <= ch1; j++) {
		//求出[0,1)均匀分布随机数
		do { re1 = rand() / 32767.0; } while (re1 == 0.0);
		re2 = rand() / 32767.0;
		xd = sqrt(-log(re1) / 0.227468) * cos(2 * PI * re2) * ed + x_1;
		yd = sqrt(-log(re1) / 0.227468) * sin(2 * PI * re2) * ef + y_1;
		do { re3 = rand() / 32767.0; } while (re3 == 0.0);
		re4 = rand() / 32767.0;
		xdp = xd + sqrt(-log(re3) / 0.227468) * cos(2 * PI * re4) * bd;
		ydp = yd + sqrt(-log(re3) / 0.227468) * sin(2 * PI * re4) * bf;
		for (i = 1; i <= m; i++) {
			if (sqrt((xdp - x[i]) * (xdp - x[i]) + (ydp - y[i]) * (ydp - y[i])) < ridp[i])
				t[i] = 1;
		}
	}
}

//地地导弹打击程序变量输入函数
void ddshuru(void) {
	// 请输入地地导弹打击模型中各变量的值
	printf("请输入地地导弹打击模型中各变量的值:\n");

	// 输入导弹数量
	printf("请输入地地导弹攻击的导弹数(整数型):\n");
	scanf("%d", &ch2);

	// 输入导弹圆概率偏差CEP
	printf("请输入导弹圆概率偏差CEP(实数型):\n");
	scanf("%lf", &cep);

	// 输入各目标等效杀伤圆半径
	printf("请输入导弹对各号目标的等效杀伤圆半径Ridd[i](实数型)(i=1,...%d):\n", m);
	for (i = 1; i <= m; i++){
		scanf("%lf", &ridd[i]);
	}
}

//地地导弹打击模块函数
void dddddj(void) {
	for(j=1;j<=ch2;j++){
		//求出[0,1)均匀分布随机数
		do { re11 = rand() / 32767.0; } while (re11 == 0.0);
		re22 = rand() / 32767.0;
		xdd = 0.5731 * sqrt(-log(re11) / 0.227468) * cos(2 * PI * re22) * cep + x_1;
		ydd = 0.5731 * sqrt(-log(re11) / 0.227468) * sin(2 * PI * re22) * cep + y_1;

		for (i = 1; i <= m; i++) {
			if (sqrt((xdd - x[i]) * (xdd - x[i]) + (ydd - y[i]) * (ydd - y[i])) < ridd[i])
				t[i] = 1;
		}
	}
}

//航空火力打击程序变量输入函数 
void hkshuru(void)
{
	// 请输入航空火力打击模型中各变量的值
	printf("/* 请输入航空火力打击模型中各变量的值 */\n");
	printf("请输入飞行高度H(千米)(实型数),速度V(千米/小时)(实型数),\n");
	printf("投弹俯冲角α(度)(实型数):\n");
	scanf("%lf%lf%lf", &h, &v11, &a);
	printf("请输入每架飞机的投弹数m(整型数),每编队飞机架数n(整型数),\n");
	printf("连投炸点间隔hx(实型数),横向编队飞行间隔hy(实型数):\n");
	scanf("%d%d%lf%lf", &m3, &n3, &hx, &hy);
	ch3 = m3 * n3;
	printf("请输入航弹对各号目标的等效炸伤圆半径Rihd[i](实数型)(i=1,...%d):\n", m);
	for (i = 1; i <= m; i++) {
		scanf("%lf", &rihd[i]);
	}
}

//航空火力打击模块函数
void hkhldj(void) {
	for (j = 1; j <= ch3; j++) {
		if (h >= 1.0){
			ex=10*h+0.1*v11*(1-sin(a));ey=ex;
		}
		else {
			if (h <= 0.4) {
				ex = (10 * h + 0.1 * v11 * (1 - sin(a))) * (0.78 + 0.55 * h);
				ey = (10 * h + 0.1 * v11 * (1 - sin(a))) * (0.45 + 0.55 * h);
			}
			else {
				ex = 10 * h + 0.1 * v11 * (1 - sin(a));
				ey = (10 * h + 0.1 * v11 * (1 - sin(a)))* (0.45 + 0.55 * h);
			}
		}
		do { re31 = rand() / 32767.0; } while (re31 == 0); 
		re32 = rand() / 32767.0;
		xhd = sqrt(-log(re31) / 0.227468) * cos(2 * PI * re32) * ex + x_1 + (m3 - 1) * hx;
		yhd = sqrt(-log(re31) / 0.227468) * sin(2 * PI * re32) * ey + y_1 + (n3 - 1) * hy;
		for (i = 1; i <= m; i++) {
			if (sqrt((xhd - x[i]) * (xhd - x[i]) + (yhd - y[i]) * (yhd - y[i])) < rihd[i])
				t[i] = 1;
		}
	}
}

// 武装直升机打击程序变量输入函数
void zsjshuru(void)
{
	// 请输入武装直升机打击模型中各变量的值
	printf("/* 请输入武装直升机打击模型中各变量的值 */\n");
	printf("请输入武装直升机攻击的火箭数(整型数):\n");
	scanf("%d", &ch4);
	printf("请输入射击单位的诸元中间误差 Ed,Ef(实型数):\n");
	scanf("%lf%lf", &ed4, &ef4);
	printf("请输入散布中间误差 Bd,Bf(实型数):\n");
	scanf("%lf%lf", &bd1, &bf1);
	printf("请输入火箭对各号目标的等效杀伤圆半径Rihj[i](实数型)(i=1,...%d):\n", m);
	for (i = 1; i <= m; i++) {
		scanf("%lf", &rihj[i]);
	}
}

//武装直升机打击模块函数
void wzzsjdj(void) {
	for (j = 1; j <= ch4; j++) {
		do { re41 = rand() / 32767.0; } while (re41 == 0.0);
		re42 = rand() / 32767.0;
		xh = sqrt(-log(re41) / 0.227468) * cos(2 * PI * re42) * ed4 + x_1;
		yh = sqrt(-log(re41) / 0.227468) * sin(2 * PI * re42) * ef4 + y_1;
		for (i = 1; i <= m; i++) {
			if (sqrt((xhj - x[i]) * (xhj - x[i]) + (yhj - y[i]) * (yhj - y[i])) <= rihj[i])
				t[i] = 1;
		}
	}
}

// 统计模块函数
void tongji(void)
{
	for (i = 1; i <= m; i++)
		tt[m10] = tt[m10] + t[i];

	p = 0.0;
	for (i = 1; i <= m; i++)
		p = p + t[i] * v[i];
	p = p / v1;
	p = 1.0 - p;
	tt1 = 0.0;
	for (i = 1; i <= m10; i++)
		tt1 = tt1 + tt[i];
	tt1 = tt1 / m10;
	tt2 = tt1 / m;
	p11 = 0.0;
	for (i = 1; i <= m; i++)
		p11 = p11 + t[i] * v[i];
	p22 = p22 + p11;
	p1 = 1.0 - (p22 / m10 / v1);
	d = 0.0;
	if (m10 == 1)
	{
		m10++;
		printf("一次模拟结果输出:\n");
		printf("被毁伤的单位目标个数:%d\n", tt[m10 - 1]);
		printf("相对毁伤目标数:%lf\n", tt2);
		printf("野战防护工程的保存率:%lf\n", p);
		printf("\n");
		/* continue; */
	}
	else
	{
		for (i = 1; i <= m10; i++)
			d = d + (tt1 - tt[i]) * (tt1 - tt[i]);
		d = d / (m10 - 1);
		temp = 2 * sqrt(d / m10);
		u1 = tt1 + temp;
		u2 = tt1 - temp;
		m10++;
	} // endif
}

// 输出模块函数
void shuchu(void)
{
	printf("%d次模拟后的结果输出:\n", m10 - 1);
	printf("目前的精度为:%lf\n", temp);
	printf("防护工程的保存率p1 = %lf,平均毁伤目标数tt1 = %lf\n", p1, tt1);
	printf("平均相对毁伤目标数tt2 = %lf\n", tt2);
	printf("平均毁伤目标数的真实值u1 = %lf,u2 = %lf\n", u1, u2);
	printf("\n");
}

//主程序开始
int main() {//外循环的开始
	do {
		mubiao();//内循环的开始
		do {//变量初始化
			m10 = 10; v1 = 0;
			p = 0.0; temp = 0.0; tt1 = 0.0; tt2 = 0.0; p11 = 0.0; p22 = 0.0; u1 = 0.0; u2 = 0.0;
			for (i = 1; i <= W; i++)
				tt[i] = 0;

			printf("请选择攻击方式:1--单方式攻击;2--双方式攻击;\n");
			printf("                3--三方式攻击;4--四方式攻击;0--退出;\n");
			scanf("%d", &cch);

			switch (cch)
			{
			case 1: {
				printf("请选择单方式攻击类型:1--地面火炮攻击;2--地地导弹攻击;\n");
				printf("3--航空火力攻击;4--武装直升机攻击;\n");
				scanf("%d", &ch);
				switch (ch) {
				case 1: {
					// 地面火炮打击程序
					dmshuru();
					ggshuru();
					do {
						for (i = 1; i <= m; i++)
							t[i] = 0;
						dmhpdj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}

				case 2: {
					// 地地导弹打击模型
					ddshuru();
					ggshuru();
					do {
						for (i = 1; i <= m; i++)
							t[i] = 0;
						dddddj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}

				case 3: {//航空火力打击模型
					hkshuru();
					ggshuru();
					do {
						for (i = 1; i <= m; i++)t[i] = 0;
						hkhldj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}
				case 4: { // 武装直升机打击模型
					zsjshuru();
					ggshuru();
					do
					{
						for (i = 1; i <= m; i++)
							t[i] = 0;
						wzzsjdj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}
				default: {
					break;
				}
				}//end switch(1)
				break;
			}
			case 2: {
				printf("请选择双方式攻击类型:1--地面火炮和地地导弹同时攻击;\n");
				printf("2--地面火炮和航空火力同时攻击;\n");
				printf("3--地面火炮和武装直升机同时攻击;4--地地导弹和航空火力同时攻击;\n");
				printf("5--地地导弹和武装直升机同时攻击;6--航空火力和武装直升机同时攻击;\n");
				scanf("%d", &ch);
				switch (ch)
				{
				case 1: {
					dmshuru();
					ddshuru();
					ggshuru();
					do {
						for (i = 1; i <= m; i++)t[i] = 0;
						dmhpdj();
						dddddj();
						hkhldj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}

				case 2: {
					dmshuru();
					hkshuru();
					ggshuru();
					do {
						for (i = 1; i <= m; i++)t[i] = 0;
						dmhpdj();
						dddddj();
						wzzsjdj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}
				case 3: {
					dmshuru();
					hkshuru();
					zsjshuru();
					ggshuru();
					do {
						for (i = 1; i <= m; i++)t[i] = 0;
						dmhpdj();
						hkhldj();
						wzzsjdj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}
				case 4: {
					ddshuru();
					hkshuru();
					ggshuru();
					do {
						for (i = 1; i <= m; i++)t[i] = 0;
						dmhpdj();
						hkhldj();
						wzzsjdj();
						tongji();
					} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
					shuchu();
					break;
				}default: {
					break;
				}
				}//endswitch(3)
				break;
			}//三方式攻击结束
			case 4: {
				printf("进入四方式攻击类型:地面火炮,地地导弹,航空火力和武装直升机同时攻击;\n");
				dmshuru();
				ddshuru();
				hkshuru();
				zsjshuru();
				ggshuru();
				do {
					for (i = 1; i <= m; i++)t[i] = 0;
					dmhpdj();
					dddddj();
					hkhldj();
					wzzsjdj();
					tongji();
				} while (((temp > epsl) || (temp < 0) || ((m10 - 1) == 1) || (!tt1)) && (m10 < 10001));
				shuchu();
				break;
			}//四方式攻击结束
			default: {
				break;
			}
			}//SWITCH结束
		}while (cch);
		printf("是否继续攻击新的目标(1(Yes)/0(No))>\n");
		scanf("%d", &ttch);
			}while (ttch);
}
