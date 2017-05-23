#pragma once
#define BLANK -1
#define ROW_NUM 10
#define COL_NUM 16
#define PIC_NUM 16
#define LEFT 20
#define TOP 50
#define ELEMW 40
#define ELEMH 40
typedef struct tagVertex {
	int col;
	int row;
	int info;
}Vertex;