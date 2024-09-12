#include "head.h"
/* ����������printf("LOG-....���������Ϊ"�������",��ֱ������ */
/* ��Input_attribute��ʼ��,������Ϊfalse*/
void init_input_attribute(struct Input_attribute* input_attribute) {
	/* ��ʼ��"�������Խṹ��" */
	if (input_attribute == NULL) { //������ʾ
		printf("LOG-init_input_attribure: ERROR! input_attribute == NULL\n");
	}
	input_attribute->if_up = false;
	input_attribute->if_down = false;
	input_attribute->if_left = false;
	input_attribute->if_right = false;
	input_attribute->if_fire = false;
	input_attribute->if_exit = false;
	input_attribute->Illegal_inputs = false;
}

void get_inputs(struct Input_attribute* input_attribute) {
	/* ���ݼ��̰���״̬��ȡ��������㶹�����ƶ����Ƿ����㶹,
	KEY_DOWNΪ�궨��, ����鿴head.h�ļ�, ����GetAsyncKeyState������ʹ����ٶ� */
	init_input_attribute(input_attribute); //�ڻ�ȡ����ǰ�����һ��������
	if (KEY_DOWN(87) || KEY_DOWN(38)) { //���w�����߷����"��"������,��if_up������1
		input_attribute->if_up = true;
	}
	if (KEY_DOWN(65) || KEY_DOWN(37)) { //���a�����߷����"��"������,��if_left������1
		input_attribute->if_left = true;
	}
	if (KEY_DOWN(68) || KEY_DOWN(39)) { //���d�����߷����"��"������,��if_right������1
		input_attribute->if_right = true;
	}
	if (KEY_DOWN(83) || KEY_DOWN(40)) { //���s�����߷����"��"������,��if_down������1
		input_attribute->if_down = true;
	}
	if (KEY_DOWN(88)) { //���x��������,��if_fire������1
		input_attribute->if_fire = true;
	}
	if (KEY_DOWN(27)) { //���esc��,��if_exit������1
		input_attribute->if_exit = true;
	}

}

double get_time() {
	/* ��ȡ�ӳ������п�ʼ���˿̵�ʱ��,��λΪ�� */
	clock_t t = clock();
	double sec = ((double)t / CLOCKS_PER_SEC);
	//printf("LOG-get_time: time == %.5fs \n", sec);
	return sec;
}

int get_Boat_list_len(struct Boat* start) {
	/* ��ȡ"Boat����"�ĳ���,����ȡ�ж���Boat */
	int len = 0;
	struct Boat* temp = start;
	if (temp == NULL) { //������ʾ
		printf("LOG-get_Boat_list_len: start == NULL\n");
		return 0;
	}
	while (temp != NULL) {
		if (temp->if_existed == noEXISTED) { //����if_existedΪ0��Boat������,�ʲ�����
			//printf("LOG-get_Boat_list_len: temp->if_existed == false\n");
			temp = temp->next;
			continue;
		}
		temp = temp->next;
		len++;
	}
	temp = start->last; //��start���������ͷ�ڵ�, ��Ҫ����start�ĸ��ڵ㲢ͳ��Boat������
	while (temp != NULL) {
		if (!temp->if_existed) {
			//printf("LOG-get_Boat_list_len: temp->if_existed == false\n");
			temp = temp->last;
			continue;
		}
		temp = temp->last;
		len++;
	}
	//printf("LOG-get_Boat_list_len: len == %d\n", len);
	return len; //����Boat����
}

int get_Bullet_list_len(struct Bullet* start) {
	/* ��ȡ"�ӵ�����"�ĳ���,����ȡ�ж��ٸ�"�ӵ�",�ú�����get_Boat_list_len���� */
	int len = 0;
	struct Bullet* temp = start;
	if (temp == NULL) {
		printf("LOG-get_Bullet_list_len: start == NULL\n");
		return 0;
	}
	while (temp != NULL) {
		if (!temp->if_existed) {
			//printf("LOG-get_Boat_list_len: temp->if_existed == false\n");
			temp = temp->next;
			continue;
		}
		temp = temp->next;
		len++;
	}
	temp = start->last;
	while (temp != NULL) {
		if (!temp->if_existed) {
			//printf("LOG-get_Boat_list_len: temp->if_existed == false\n");
			temp = temp->last;
			continue;
		}
		temp = temp->last;
		len++;
	}
	return len;
}

struct Boat* get_last_boat_list(struct Boat* start) {
	/* ��ȡ����"Boat����"�����һ���ڵ�,�������½�ʬʱ��Ҫ�õ� */
	if (start == NULL) {
		return NULL;
	}
	while (start->next != NULL) {
		start = start->next;
	}
	return start;
}

struct Bullet* get_last_bullet_list(struct Bullet* start) {
	/* ��ȡ����"�ӵ�����"�����һ���ڵ�,�����ӡ����ӵ���ʱ��Ҫ�õ� */
	if (start == NULL) {
		return NULL;
	}
	while (start->next != NULL) {
		start = start->next;
	}
	return start;
}

void init_peashooter(struct Boat* peashooter) {
	/* ��ʼ���㶹���ֵ����� */
	peashooter->if_existed = EXISTED;
	strcpy(peashooter->image, Image_peashooter_up);
	peashooter->HP = Init_HP;
	peashooter->times_fired[0] = 0.0;
	peashooter->times_fired[1] = 0.0;
	peashooter->times_fired[2] = 0.0;
	peashooter->time_invincibility_started = -1.0;
	peashooter->if_collided = false;
	peashooter->faction = Self;
	peashooter->p.x = Width_Background / 2 - Width_Peashooter_up / 2;
	peashooter->p.y = High_Background - High_Peashooter_up;
	peashooter->high = High_Peashooter_up;
	peashooter->width = Width_Peashooter_up;
	peashooter->last = NULL;
	peashooter->next = NULL;
}

void init_global_attribute(struct Global_attribute* global_attribute) {
	/* ��ʼ��ȫ������ */
	global_attribute->time = get_time();
	global_attribute->scores = Init_scores;
	global_attribute->number_zombie = Init_zombie;
	global_attribute->myHP = Init_HP;
	global_attribute->bossHP = Init_Boss_HP;
	global_attribute->stone_from_zombie = Init_HP;
	global_attribute->range_p1.x = 0; global_attribute->range_p1.y = 0;
	global_attribute->range_p2.x = 0; global_attribute->range_p2.y = 0;
	global_attribute->time_last_generate_zombie = 0;
}

void init_background(struct Background* background) {
	/* ��ʼ���������� */
	background->if_existed = true;
	strcpy(background->image, Gameing_background);
	background->p.x = 0;
	background->p.y = 0;
}

void init_new_enboat(struct Boat* new_zombie, struct Boat* last_zombie) {
	/* ��ʼ���µĽ�ʬ���� */
	new_zombie->if_existed = EXISTED;
	strcpy(new_zombie->image, Image_zombie);
	new_zombie->HP = Init_HP_zombie;
	new_zombie->times_fired[0] = 0;
	new_zombie->times_fired[1] = 0;
	new_zombie->times_fired[2] = 0;
	new_zombie->time_invincibility_started = 0;
	new_zombie->if_collided = false;
	new_zombie->faction = Enemy;
	new_zombie->p.x = rand() % (Width_Background - Width_Zombie);
	new_zombie->p.y = 0 - High_Zombie;
	new_zombie->high = High_Zombie;
	new_zombie->width = Width_Zombie;
	new_zombie->direction_p.x = rand() % (Width_Background - Width_Zombie);
	new_zombie->direction_p.y = new_zombie->p.y;
	new_zombie->last = last_zombie;
	new_zombie->next = NULL;
	last_zombie->next = new_zombie;
}

void init_pea(struct Bullet* pea) {
	/* ��ʼ���㶹���� */
	pea->if_existed = noEXISTED;
	pea->last = NULL;
	pea->next = NULL;
}

void init_stone(struct Bullet* stone) {
	/* ��ʼ��ʯͷ���� */
	stone->if_existed = noEXISTED;
	stone->last = NULL;
	stone->next = NULL;
}

void init_zombie(struct Boat* zombie) {
	/* ��ʼ��"��ʬ����"ͷ�ڵ������ */
	zombie->if_existed = EXISTED;
	strcpy(zombie->image, Image_zombie);
	zombie->HP = Init_HP_zombie;
	zombie->times_fired[0] = 0.0;
	zombie->times_fired[1] = 0.0;
	zombie->times_fired[2] = 0.0;
	zombie->if_collided = noCOLLIDED;
	zombie->faction = Enemy;
	zombie->high = High_Zombie;
	zombie->width = Width_Zombie;
	zombie->p.x = rand() % (Width_Background - Width_Zombie);
	zombie->p.y = 0 - High_Zombie;
	zombie->direction_p.x = rand() % (Width_Background - Width_Zombie);
	zombie->direction_p.y = High_Background;
	zombie->last = NULL;
	zombie->next = NULL;
}

void init_boss(Boss* boss) {
	boss->if_existed = false;
	strcpy(boss->image, Image_boss);
	boss->HP = Init_Boss_HP;
	boss->times_fired_bullet1 = 0.0;
	boss->times_fired_bullet2 = 0.0;
	boss->times_fired_bullet3 = 0.0;
}

void init(
	struct Background* background,
	struct Global_attribute* global_attribute,
	struct Boat* peashooter,
	struct Boat* zombie,
	struct Input_attribute* input_attribute,
	struct Bullet* pea,
	struct Bullet* stone,
	struct Boss* boss,
	struct Bullet* bullet_boss
) {
	/* ͨ��������س�ʼ������, ��ʼ����Ϸ�����ж���,����������Ϸ���� */
	time_t t;
	srand((unsigned)time(&t));
	init_input_attribute(input_attribute);
	init_background(background);
	init_global_attribute(global_attribute);
	init_peashooter(peashooter);
	init_zombie(zombie);
	init_pea(pea);
	init_stone(stone);
	init_stone(bullet_boss);
	init_boss(boss);

	initgraph(Width_Background, High_Background, EW_SHOWCONSOLE); //EasyX����غ���,����ʹ�ü�Ч���ο�EasyX���ֲ�
	setbkcolor(WHITE); //EasyX����غ���,����ʹ�ü�Ч���ο�EasyX���ֲ�
	settextstyle(High_Text, Width_Text, _T("Courier"));	// ��������
	settextcolor(RED);
	cleardevice(); //EasyX����غ���,����ʹ�ü�Ч���ο�EasyX���ֲ�
}

bool if_generate_zombie(struct Global_attribute* global_attribute, struct Boat* zombie) {
	/* ����ȫ�����Ժͽ�ʬ�����ж��Ƿ�����µĽ�ʬ,���򷵻�1,���򷵻�0 */
	int zombie_len = get_Boat_list_len(zombie);
	double gap_time_last_generate_zombie = global_attribute->time - global_attribute->time_last_generate_zombie;
	//printf("LOG-if_generate_enemy: gap_time_last_generate_enemy == %f\n", gap_time_last_generate_enemy);
	if (zombie_len < MAX_zombie && gap_time_last_generate_zombie >= Gap_if_generate_zombie) {
		return true;
	}
	else {
		return false;
	}
}

void generate_boss(struct Global_attribute* global_attribute, struct Boss* boss) {
	/* ����BOSS�ĺ��� */
	if (global_attribute->number_zombie % 20 == 19) {
		boss->if_existed = true;
	}
}

bool if_generate_stone(struct Global_attribute* global_attribute, struct Boat* zombie, struct Bullet* stone) {
	/* �ж��Ƿ����ʯͷ*/
	double status = (rand() % 5 - 2) / 10.0;
	if (global_attribute->time - zombie->times_fired[0] > Gap_if_generate_stone + status) {
		if (get_Bullet_list_len(stone) < MAX_stone) {
			zombie->times_fired[2] = zombie->times_fired[1];
			zombie->times_fired[1] = zombie->times_fired[0];
			zombie->times_fired[0] = global_attribute->time;
			return 1;
		}
	}
	return 0;
}

bool if_generate_bullet_boss_one(struct Global_attribute* Global_attribute, struct Boss* boss, struct Bullet* bullet_boss) {
	/*����*/
	if (Global_attribute->time - boss->times_fired_bullet1 > Boss_bullet_one) {
		boss->times_fired_bullet1 = Global_attribute->time;
		return true;
	}
	return false;
}

bool if_generate_bullet_boss_two(struct Global_attribute* Global_attribute, struct Boss* boss, struct Bullet* bullet_boss) {
	/*��*/
	if (Global_attribute->time - boss->times_fired_bullet2 > Boss_bullet_two) {
		boss->times_fired_bullet2 = Global_attribute->time;
		return true;
	}
	return false;
}
//���
bool if_generate_bullet_boss_the(struct Global_attribute* Global_attribute, struct Boss* boss, struct Bullet* bullet_boss) {
	if (Global_attribute->time - boss->times_fired_bullet3 > Boss_bullet_the) {
		boss->times_fired_bullet3 = Global_attribute->time;
		return true;
	}
	return false;
}

bool if_generate_pea(struct Global_attribute* global_attribute, struct Boat* peashooter, struct Bullet* pea) {
	if (global_attribute->time - peashooter->times_fired[0] > Gap_if_generate_pea) {
		peashooter->times_fired[2] = peashooter->times_fired[1];
		peashooter->times_fired[1] = peashooter->times_fired[0];
		peashooter->times_fired[0] = global_attribute->time;
		return 1;
	}
	return 0;
}

void generate_bullet(struct Global_attribute* global_attribute, struct Boat* peashooter, struct Boat* zombie, struct Input_attribute* input_attribute, struct Bullet* stone, struct Bullet* pea, struct Bullet* bullet_boss, struct Boss* boss) {
	/* �����ҷ��㶹���ֵ����㶹���з���ʬ��ʯͷ.���¡��ӵ����� */
	struct Bullet* new_bullet;
	struct Bullet* temp;
	temp = get_last_bullet_list(pea);
	if (
		input_attribute->if_fire == 1 && peashooter->if_existed == EXISTED && if_generate_pea(global_attribute, peashooter, pea)
		) {
		new_bullet = (struct Bullet*)malloc(sizeof(struct Bullet));
		new_bullet->if_existed = EXISTED;
		new_bullet->faction = Self;
		strcpy(new_bullet->image, Image_pea);
		new_bullet->p.x = peashooter->p.x;
		new_bullet->p.y = peashooter->p.y;
		new_bullet->high = High_Pea;
		new_bullet->width = Width_Pea;
		new_bullet->direction_p.x = peashooter->p.x;
		new_bullet->direction_p.y = 0 - High_Pea;
		new_bullet->last = temp;
		new_bullet->next = NULL;
		temp->next = new_bullet;
	}
	while (zombie != NULL) {
		if (zombie->if_existed == noEXISTED) {
			zombie = zombie->next;
			continue;
		}
		if (if_generate_stone(global_attribute, zombie, stone)) {
			temp = get_last_bullet_list(stone);
			new_bullet = (struct Bullet*)malloc(sizeof(struct Bullet));
			new_bullet->if_existed = EXISTED;
			new_bullet->faction = Enemy;
			strcpy(new_bullet->image, Image_stone);
			new_bullet->p.x = zombie->p.x;
			new_bullet->p.y = zombie->p.y;
			new_bullet->high = High_Stone;
			new_bullet->width = Width_Stone;
			new_bullet->direction_p.x = zombie->p.x;
			new_bullet->direction_p.y = High_Background;
			new_bullet->last = temp;
			new_bullet->next = NULL;
			temp->next = new_bullet;
		}
		zombie = zombie->next;
	}
	if (boss->if_existed == true) {
		if (if_generate_bullet_boss_one(global_attribute, boss, bullet_boss)) {
			temp = get_last_bullet_list(bullet_boss);
			new_bullet = (struct Bullet*)malloc(sizeof(struct Bullet));
			new_bullet->if_existed = EXISTED;
			new_bullet->faction = Enemy;
			strcpy(new_bullet->image, Image_stone);
			new_bullet->p.x = rand() % 200 + 50;
			new_bullet->p.y = 50;
			new_bullet->high = High_Stone;
			new_bullet->width = Width_Stone;
			new_bullet->direction_p.x = new_bullet->p.x;
			new_bullet->direction_p.y = High_Background;
			new_bullet->last = temp;
			new_bullet->next = NULL;
			temp->next = new_bullet;
		}
		if (if_generate_bullet_boss_two(global_attribute, boss, bullet_boss)) {
			for (int i = 10; i <= 400; i += 100) {
				temp = get_last_bullet_list(bullet_boss);
				new_bullet = (struct Bullet*)malloc(sizeof(struct Bullet));
				new_bullet->if_existed = EXISTED;
				new_bullet->faction = Enemy;
				strcpy(new_bullet->image, Image_stone);
				new_bullet->p.x = i;
				new_bullet->p.y = 50;
				new_bullet->high = High_Stone;
				new_bullet->width = Width_Stone;
				new_bullet->direction_p.x = new_bullet->p.x;
				new_bullet->direction_p.y = High_Background;
				new_bullet->last = temp;
				new_bullet->next = NULL;
				temp->next = new_bullet;
			}
		}
		if (if_generate_bullet_boss_the(global_attribute, boss, bullet_boss)) {
			for (int i = 1; i <= 7; i++) {
				temp = get_last_bullet_list(bullet_boss);
				new_bullet = (struct Bullet*)malloc(sizeof(struct Bullet));
				new_bullet->if_existed = EXISTED;
				new_bullet->faction = Enemy;
				strcpy(new_bullet->image, Image_stone);
				new_bullet->p.x = rand() % 200 + 50;
				new_bullet->p.y = rand() % 100 + 10;
				new_bullet->high = High_Stone;
				new_bullet->width = Width_Stone;
				new_bullet->direction_p.x = new_bullet->p.x;
				new_bullet->direction_p.y = High_Background;
				new_bullet->last = temp;
				new_bullet->next = NULL;
				temp->next = new_bullet;
			}
		}
	}
}

bool if_collision_zombie(struct Boat* zombie, struct Bullet* pea) {
	/* �жϽ�ʬ�Ƿ���㶹������ײ
	���򷵻�1, ���򷵻�0 */
	if (!(pea->p.x > zombie->p.x + zombie->width || pea->p.x + pea->width < zombie->p.x)) {
		if (!(pea->p.y > zombie->p.y + zombie->high || pea->p.y + pea->high < zombie->p.y)) {
			return 1;
		}
	}
	return 0;
}

bool if_collision_boss(struct Boss* boss, struct Bullet* pea) {
	if (
		pea->p.y < 30 && pea->p.x > 50 && pea->p.x < 330
		) {
		return 1;
	}
	return 0;
}

bool if_collision_peashooter(struct Boat* peashooter, struct Bullet* stone) {
	/* �ж��㶹�����Ƿ��ʯͷ������ײ
	���򷵻�1, ���򷵻�0 */
	if (!(stone->p.x > peashooter->p.x + peashooter->width || stone->p.x + stone->width < peashooter->p.x)) {
		if (!(stone->p.y > peashooter->p.y + peashooter->high || stone->p.y + stone->high < peashooter->p.y)) {
			return 1;
		}
	}
	return 0;
}

void collision_detect(
	struct Boat* peashooter,
	struct Boat* zombie,
	struct Boss* boss,
	struct Bullet* pea,
	struct Bullet* stone,
	struct Bullet* bullet_boss,
	struct Global_attribute* global_attribute
) {
	/* ��ײ���, ��⡰�ӵ����͡�Boat���Ƿ�����ײ�����������Ե��� */
	struct Bullet* temp = pea;
	while (zombie != NULL) { //ͨ��ѭ���ж�ÿ����ʬ�Ƿ���㶹������ײ
		pea = temp;
		if (zombie->if_existed == 0) {
			zombie = zombie->next;
			continue;
		}
		while (pea != NULL) {//ͨ��ѭ�������ҷ� �㶹
			if (pea->if_existed == 0) {
				pea = pea->next;
				continue;
			}
			if (if_collision_zombie(zombie, pea)) {//���������ײ�򽫽�ʬ���Ը�Ϊ������
				zombie->if_collided = 1;
				zombie->if_existed = 0;
				pea->if_existed = 0;//�㶹������Ը�Ϊ������
				global_attribute->number_zombie++;
				break;
			}
			pea = pea->next;
		}
		zombie = zombie->next;
	}

	while (stone != NULL && peashooter->if_existed == EXISTED) { //ͨ��ѭ���ж�ʯͷ�Ƿ���㶹���ַ�����ײ
		if (stone->if_existed == noEXISTED) {
			stone = stone->next;
			continue;
		}
		//printf("LOG-collision_detect: Test1\n");
		if (if_collision_peashooter(peashooter, stone)) {
			peashooter->if_collided = 1;
			peashooter->HP -= 1;
			if (peashooter->HP <= 0) {
				peashooter->if_existed = noEXISTED;
				peashooter->HP = 0;
			}
			stone->if_existed = 0;
		}
		stone = stone->next;
		//printf("LOG-collision_detect: Test2\n");
	}

	while (bullet_boss != NULL && peashooter->if_existed == EXISTED) { //ͨ��ѭ���ж�BOSS�ġ��ӵ����Ƿ���㶹���ַ�����ײ
		if (bullet_boss->if_existed == noEXISTED) {
			bullet_boss = bullet_boss->next;
			continue;
		}
		//printf("LOG-collision_detect: Test1\n");
		if (if_collision_peashooter(peashooter, bullet_boss)) {
			peashooter->if_collided = 1;
			peashooter->HP -= 1;
			if (peashooter->HP <= 0) {
				peashooter->if_existed = noEXISTED;
				peashooter->HP = 0;
			}
			bullet_boss->if_existed = 0;
		}
		bullet_boss = bullet_boss->next;
		//printf("LOG-collision_detect: Test2\n");
	}

	if (boss->if_existed == true) {
		temp = pea;
		while (pea != NULL) {
			if (pea->if_existed == 0) {
				pea = pea->next;
				continue;
			}
			if (if_collision_boss(boss, pea)) {
				boss->HP--;
				if (boss->HP == 0) {
					init_boss(boss);
				}
				pea->if_existed = 0;
			}
			pea = pea->next;
		}
	}
}

void move_peashooter(struct Boat* peashooter, struct Input_attribute* input_attribute) {
	/* �ƶ��ҷ��㶹����λ�� */
	peashooter->p.x = peashooter->p.x + input_attribute->if_right * Speed_peashooter - input_attribute->if_left * Speed_peashooter;
	peashooter->p.y = peashooter->p.y + input_attribute->if_down * Speed_peashooter - input_attribute->if_up * Speed_peashooter;
	//���µ�if������ֹ�㶹����λ��Խ����Ϸ����
	if (peashooter->p.x > Width_Background - peashooter->width) {
		peashooter->p.x = Width_Background - peashooter->width;
	}
	if (peashooter->p.x < 0) {
		peashooter->p.x = 0;
	}
	if (peashooter->p.y > High_Background - peashooter->high) {
		peashooter->p.y = High_Background - peashooter->high;
	}
	if (peashooter->p.y < 0) {
		peashooter->p.y = 0;
	}
	if (input_attribute->if_left && !input_attribute->if_right) {
		strcpy(peashooter->image, Image_peashooter_left);
		peashooter->high = High_Peashooter_left;
		peashooter->width = Width_Peashooter_left;
	}
	else if (!input_attribute->if_left && input_attribute->if_right) {
		strcpy(peashooter->image, Image_peashooter_right);
		peashooter->high = High_Peashooter_right;
		peashooter->width = Width_Peashooter_right;
	}
	else {
		strcpy(peashooter->image, Image_peashooter_up);
		peashooter->high = High_Peashooter_up;
		peashooter->width = Width_Peashooter_up;
	}
}

void move_zombie(struct Boat* zombie) {
	/* �ƶ���ʬ */
	while (zombie != NULL) {
		if (zombie->if_existed == noEXISTED) {
			zombie = zombie->next;
			continue;
		}
		if (zombie->direction_p.x == zombie->p.x) {
			zombie->direction_p.x = rand() % (Width_Background - zombie->width);
		}
		else {
			zombie->p.x = zombie->p.x + ((zombie->direction_p.x > zombie->p.x) ? 1 : -1) * Speed_zombie;
		}
		zombie->p.y += Speed_zombie;
		if (zombie->p.y > High_Background) {
			zombie->if_existed = noEXISTED;
		}
		zombie = zombie->next;
	}
}

void move_pea(struct Bullet* pea) {
	/* �ƶ��㶹 */
	while (pea != NULL) {
		if (pea->if_existed == 0) {
			pea = pea->next;
			continue;
		}
		if (pea->p.y + High_Pea < 0) {
			pea->if_existed = noEXISTED;
			pea = pea->next;
			continue;
		}
		pea->p.y -= Speed_Bullet;
		pea = pea->next;
	}
}

void move_stone(struct Bullet* stone) {
	/* �ƶ�ʯͷ */
	while (stone != NULL) {
		if (stone->if_existed == 0) {
			stone = stone->next;
			continue;
		}
		if (stone->p.y > High_Background) {
			stone->if_existed = noEXISTED;
			stone = stone->next;
			continue;
		}
		stone->p.y += Speed_Bullet;
		stone = stone->next;
	}
}

void move_game_objects(
	struct Background* background,
	struct Boat* peashooter,
	struct Boat* zombie,
	struct Boss* boss,
	struct Bullet* pea,
	struct Bullet* stone,
	struct Bullet* bullet_boss,
	struct Input_attribute* input_attribute
) {
	/* �ƶ�������Ϸ���� */
	move_peashooter(peashooter, input_attribute);
	move_zombie(zombie);
	move_pea(pea);
	move_stone(stone);
	move_stone(bullet_boss);
}

void display_HP_peashooter(int HP) {
	char* p = (char*)malloc(20 * sizeof(char));
	char* temp = p;
	int x = 10, y = 10;
	_itoa(HP, p, 10);
	outtextxy(x, y, 'H');
	x += Width_Text;
	outtextxy(x, y, 'P');
	x += Width_Text;
	outtextxy(x, y, ':');
	x += Width_Text;
	while (*temp != '\0') {
		outtextxy(x, y, *temp);
		temp++;
		x += Width_Text;
	}
}

void display_game_objects(
	struct Background* background,
	struct Boat* peashooter,
	struct Boat* zombie,
	struct Boss* boss,
	struct Bullet* pea,
	struct Bullet* stone,
	struct Bullet* bullet_boss

) {
	/* ��ʾ������Ϸ��������Ϸ������ */

	IMAGE image_background, image_peashooter, image_zombie, image_pea, image_stone, image_boss, image_bullet_boss;
	loadimage(&image_background, background->image, Width_Background, High_Background);
	loadimage(&image_peashooter, peashooter->image, peashooter->width, peashooter->high);
	loadimage(&image_zombie, Image_zombie, Width_Zombie, High_Zombie);
	loadimage(&image_pea, Image_pea, Width_Pea, High_Pea);
	loadimage(&image_stone, Image_stone, Width_Stone, High_Stone);
	loadimage(&image_bullet_boss, Image_stone, Width_Stone, High_Stone);
	loadimage(&image_boss, Image_boss, Width_Boss, High_Boss);
	putimage(0, 0, &image_background);
	if (peashooter->if_existed == EXISTED) {//�����㶹��������ѡ���Ե���ʾ�㶹����
		transparentimage(NULL, peashooter->p.x, peashooter->p.y, &image_peashooter, 0x000000);
	}
	while (zombie != NULL) { //ͨ��ѭ����ʾ���д��ڵĽ�ʬ
		if (zombie->if_existed == noEXISTED) {
			zombie = zombie->next;
			continue;
		}
		transparentimage(NULL, zombie->p.x, zombie->p.y, &image_zombie, 0x000000);
		//printf("LOG-display_game_objects: enboat->p.x == %d enboat->p.y == %d\n", enboat->p.x, enboat->p.y);
		zombie = zombie->next;
	}
	while (pea != NULL) { //ͨ��ѭ����ʾ���д��ڵ��㶹
		if (pea->if_existed == 0) {
			pea = pea->next;
			continue;
		}
		transparentimage(NULL, pea->p.x + Offset_x_peashooter, pea->p.y + Offset_y_peashooter, &image_pea, 0x000000);
		//printf("LOG-display_game_objects: enboat->p.x == %d enboat->p.y == %d\n", enboat->p.x, enboat->p.y);
		pea = pea->next;
	}

	while (stone != NULL) { //ͨ��ѭ����ʾ���д��ڵ�ʯͷ
		if (stone->if_existed == 0) {
			stone = stone->next;
			continue;
		}
		transparentimage(NULL, stone->p.x + Offset_x_zombie, stone->p.y + Offset_y_zombie, &image_stone, 0x000000);
		//printf("LOG-display_game_objects: enboat->p.x == %d enboat->p.y == %d\n", enboat->p.x, enboat->p.y);
		stone = stone->next;
	}

	while (bullet_boss != NULL) { //ͨ��ѭ����ʾ���д��ڵ�BOSS�ӵ�
		if (bullet_boss->if_existed == 0) {
			bullet_boss = bullet_boss->next;
			continue;
		}
		transparentimage(NULL, bullet_boss->p.x + Offset_x_zombie, bullet_boss->p.y + Offset_y_zombie, &image_stone, 0x000000);
		//printf("LOG-display_game_objects: enboat->p.x == %d enboat->p.y == %d\n", enboat->p.x, enboat->p.y);
		bullet_boss = bullet_boss->next;
	}
	if (boss->if_existed == true) {
		transparentimage(NULL, 50, -50, &image_boss, 0x000000);
	}

	display_HP_peashooter(peashooter->HP);

}

void generate_zombie(struct Global_attribute* global_attribute, struct Boat* zombie, Boss* boss) {
	/* �����������ѡ���Եز����µĽ�ʬ */
	if (boss->if_existed == false) {
		struct Boat* new_boat;
		struct Boat* last_enboat = get_last_boat_list(zombie);
		if (if_generate_zombie(global_attribute, zombie)) { //������Ϸ�滮���ڽ�ʬ��������һ��������,��ͨ��ר�ŵ�if_generate_zombie�����ж�
			new_boat = (struct Boat*)malloc(sizeof(struct Boat));
			init_new_enboat(new_boat, last_enboat);
			global_attribute->time_last_generate_zombie = get_time();
		}
	}
}

void update_global_attributes(struct Global_attribute* global_attribute) {
	/* ����ȫ������, Ŀǰ��������ʱ�� */
	global_attribute->time = get_time();
}

void gaming_round(
	struct Background* background,
	struct Global_attribute* global_attribute,
	struct Boat* myboat,
	struct Boat* zombie,
	struct Boss* boss,
	struct Bullet* stone,
	struct Bullet* pea,
	struct Bullet* bullet_boss,
	struct Input_attribute* input_attribute
) {
	/* ��Ϸ���� */
	get_inputs(input_attribute);
	generate_zombie(global_attribute, zombie, boss);
	generate_boss(global_attribute, boss);
	generate_bullet(global_attribute, myboat, zombie, input_attribute, stone, pea, bullet_boss, boss);
	collision_detect(myboat, zombie, boss, pea, stone, bullet_boss, global_attribute);
	move_game_objects(background, myboat, zombie, boss, pea, stone, bullet_boss, input_attribute);
	display_game_objects(background, myboat, zombie, boss, pea, stone, bullet_boss);
	update_global_attributes(global_attribute);
}

int main() {
	/* ������ */
	struct Background* background = NULL;
	struct Global_attribute* global_attribute = NULL;
	struct Boat* peashooter = NULL; struct Boat* zombie = NULL;
	struct Boss* boss = NULL;
	struct Bullet* pea = NULL;
	struct Bullet* stone = NULL;
	struct Bullet* bullet_boss = NULL;
	struct Input_attribute* input_attribute = NULL;

	boss = (struct Boss*)malloc(sizeof(struct Boss));
	input_attribute = (struct Input_attribute*)malloc(sizeof(struct Input_attribute));
	background = (struct Background*)malloc(sizeof(struct Background));
	global_attribute = (struct Global_attribute*)malloc(sizeof(struct Global_attribute));
	peashooter = (struct Boat*)malloc(sizeof(struct Boat));
	zombie = (struct Boat*)malloc(sizeof(struct Boat));
	pea = (struct Bullet*)malloc(sizeof(struct Boat));
	stone = (struct Bullet*)malloc(sizeof(struct Boat));
	bullet_boss = (struct Bullet*)malloc(sizeof(struct Bullet));
	init(background, global_attribute, peashooter, zombie, input_attribute, pea, stone, boss, bullet_boss);
	while (true) {
		gaming_round(background, global_attribute, peashooter, zombie, boss, stone, pea, bullet_boss, input_attribute);
		//Sleep(1);
	}
	_getch();
	return 0;
}
