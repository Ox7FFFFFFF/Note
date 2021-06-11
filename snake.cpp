#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

#define WIDTH 50
#define HEIGHT 25

enum DIRECTION{
	UP=1,LEFT=2,DOWN=3,RIGHT=4
};

typedef struct snake_body{
	int x,y;
	struct snake_body* next;
	struct snake_body* prev;
}body;

DIRECTION direction = UP;
DIRECTION last_direction = UP;
body* dummy = NULL;
body* tail = NULL;
char **map;
int food_flag = false;
int snake_size = 1;

void gotoXY(int x,int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle,coord);
}

void init(){
	srand(time(0));
	map = new char*[HEIGHT+1];
	for(int i=0;i<=HEIGHT;i++){
		map[i] = new char[WIDTH+1];
		for(int j=0;j<=WIDTH;j++){
			if(i==0 || i == HEIGHT || j==0 || j == WIDTH) map[i][j] = '+';
			else map[i][j] = ' ';
		}
	}
	dummy = new body();
	body* head = new body();
	head->x = (WIDTH/2);
	head->y = (HEIGHT/2);
	map[head->y][head->x] = '*';
	dummy->next = head;
	tail = head;
}

void refresh(){
	gotoXY(0,0);
	for(int i=0;i<=HEIGHT;i++){
		for(int j=0;j<=WIDTH;j++){
			cout<<map[i][j];
		}
		cout<<endl;
	}
}

void generateFood(){
	if(!food_flag){
		bool flag = false;
		int x,y;
		while(!flag){
			flag = true;
			x = rand()%(WIDTH-1)+1;
			y = rand()%(HEIGHT-1)+1;	
			body* node = dummy->next;
			while(node!=NULL){
				if(node->x==x && node->y==y){
					flag = false;
					break;
				}
				node = node->next;
			}
		}
		map[y][x] = '$';	
		food_flag = true;
	}
}

void control_mapping(char ch){
	last_direction = direction;
	switch(ch){
		case 'w':
		case 'W':
			direction = UP;
			break;
		case 'a':
		case 'A':
			direction = LEFT;
			break;
		case 's':
		case 'S':
			direction = DOWN;
			break;
		case 'd':
		case 'D':
			direction = RIGHT;
			break;
	}
	if(snake_size!=1 && last_direction%2==direction%2)
		direction = last_direction;
}

void updateSanke(int x,int y){
	if(x<=0) x = WIDTH-1;
	if(y<=0) y = HEIGHT-1;
	if(x>=WIDTH) x = 1;
	if(y>=HEIGHT) y = 1;
	
	
	if(map[y][x] == '$'){
		body* new_tail = new body();
		int t_x = tail->x;
		int t_y = tail->y;
		// genarate at the opposite direction
		if(direction == UP){
			t_y++;
		}
		else if(direction == DOWN){
			t_y--;
		}
		else if(direction == RIGHT){
			t_x--;
		} 
		else if(direction == LEFT){
			t_x++;
		}
		new_tail->x = t_x;
		new_tail->y = t_y;
		tail->next= new_tail;
		new_tail->prev = tail;
		tail = new_tail;
		map[tail->y][tail->x] = '*';
		food_flag = false;
		snake_size++;
	}
	else if(map[y][x] == '*'){
		exit(1);
	}
	
	body* new_head = new body();
	body* head = dummy->next;
	new_head->x = x;
	new_head->y = y;
	new_head->next = head;
	head->prev = new_head;
	dummy->next = new_head;
	map[dummy->next->y][dummy->next->x] = '*';
	map[tail->y][tail->x] = ' ';
	body* pre = tail->prev;
	tail = pre;
	tail->next = NULL;
}

void controller(){
	if(kbhit()) control_mapping(getch());
	body* head = dummy->next;
	int x = head->x;
	int y = head->y;
	if(direction == UP){
		y--;
	}
	else if(direction == DOWN){
		y++;
	}
	else if(direction == RIGHT){
		x++;
	} 
	else if(direction == LEFT){
		x--;
	}
	if(direction==last_direction || direction%2!=last_direction%2)
	updateSanke(x,y);
}



int main(){
	init();
	while(1){
		generateFood();
		controller();
		refresh();
	}
	
	return 0;
}
