#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> //�̰� �ʿ��ϳ� ? 
#define USER_NUM	10
struct user_info {
	int id_num;
	char id[10];
	char password[10];
};

int load_user_info(struct user_info arr[USER_NUM]);
int check_login(struct user_info arr[USER_NUM], char check_id[10], char check_pw[10]);
int binary_search_id(struct user_info arr[USER_NUM], char key_id[10]);
int load_reservation_info(int s[3][5]);
void print_seats(int s[3][5]);
int reserve(int s[3][5], char row, int col, int id);
int cancel(int s[3][5], char row, int col, int id);


int main(void)
{
	struct user_info user[USER_NUM];
	load_user_info(user); // ȸ�� ���� ���ε�
	char input_id[10], input_pw[10]; //�Է¹��� id�� pw ����

	//[�α��� ����] ����
	int success_id_num;
	printf("�ݰ����ϴ�. �α����� ���ּ���.\n");
	while (1)
	{
		//[id, pw �Է� ����] ���� 

		printf("id :");
		scanf("%s", input_id);
		printf("pw :");
		scanf("%s", input_pw);
		//[id, pw �Է� ����] ��

		//[�α��� ���� �˻� ����] ����
		if (check_login(user, input_id, input_pw) == -1) //���̵� ����ġ�� ���� �α��� ���� 
		{
			printf("���̵� �ùٸ��� �ʽ��ϴ�.\n");
			printf("�α����� �����߽��ϴ�. �ٽ� �α��� ���ֽʽÿ�.\n");
		}
		else if (check_login(user, input_id, input_pw) == -2) //��й�ȣ ����ġ�� ���� �α��� ���� 
		{
			printf("��й�ȣ�� �ùٸ��� �ʽ��ϴ�.\n");
			printf("�α����� �����߽��ϴ�. �ٽ� �α��� ���ֽʽÿ�.\n");
		}
		else// �α��� ����
		{
			success_id_num = check_login(user, input_id, input_pw);
			break;
		}
		//[�α��� ���� �˻� ����] ��
	}
	printf("�α��ο� �����߽��ϴ�.\n");
	printf("%d�� �ݰ����ϴ�.\n", success_id_num);
	//[�α��� ����] ��

	//[�޴� ����] ����
	int seats[3][5] = { 0, }; // �迭 0���� �ʱ�ȭ 
	load_reservation_info(seats); // ���� ���� ���� �ҷ����� 

	int select;
	do {
		printf("1--�¼�Ȯ���ϱ�\n");
		printf("2--�����ϱ�\n");
		printf("3--��������ϱ�\n");
		printf("4--�ٸ� ����ڷ� �α����ϱ�\n");
		printf("5--�����ϱ�\n");
		printf("�޴��� �����Ͻÿ�:");
		scanf("%d", &select);

		if (select == 1)
		{
			printf("���õ� �޴��� �¼�Ȯ���ϱ��Դϴ�.\n\n");
			print_seats(seats);
		}
		else if (select == 2)
		{
			printf("�����Ͻ� �޴��� �����ϱ��Դϴ�.\n\n");
			char reserve_r;
			int reserve_c;
			printf("������ ���ϴ� �ڸ���(��-A2)?");
			int c;
			while (((c = getchar()) != '\n') && (c != EOF)) {};
			scanf("%c%d", &reserve_r, &reserve_c);
			reserve(seats, reserve_r, reserve_c, success_id_num);
			print_seats(seats);
		}
		else if (select == 3)
		{
			printf("�����Ͻ� �޴��� ���� ����ϱ��Դϴ�.\n\n");
			char cancel_r;
			int cancel_c;
			printf("������ ���ϴ� �ڸ���(��-A2)?");
			int c;
			while (((c = getchar()) != '\n') && (c != EOF)) {};
			scanf("%c%d", &cancel_r, &cancel_c);
			cancel(seats, cancel_r, cancel_c, success_id_num);
			print_seats(seats);
		}
		else if (select == 4)
		{
			printf("�����Ͻ� �޴��� �ٸ� ����ڷ� �α����ϱ��Դϴ�.\n");
			printf("�ٽ� �α����� ���ֽʽÿ�.\n");
			while (1)
			{
				//[�α��� ����] ���� (���� �Ѱ���)
				printf("id :");
				scanf("%s", input_id);
				printf("pw :");
				scanf("%s", input_pw);
				//[id, pw �Է� ����] ��

				//[�α��� ���� �˻� ����] ����
				if (check_login(user, input_id, input_pw) == -1) //���̵� ����ġ�� ���� �α��� ���� 
				{
					printf("���̵� �ùٸ��� �ʽ��ϴ�.\n");
					printf("�α����� �����߽��ϴ�. �ٽ� �α��� ���ֽʽÿ�.\n");
				}
				else if (check_login(user, input_id, input_pw) == -2) //��й�ȣ ����ġ�� ���� �α��� ���� 
				{
					printf("��й�ȣ�� �ùٸ��� �ʽ��ϴ�.\n");
					printf("�α����� �����߽��ϴ�. �ٽ� �α��� ���ֽʽÿ�.\n");
				}
				else// �α��� ����
				{
					success_id_num = check_login(user, input_id, input_pw);
					break;
				}
				//[�α��� ���� �˻� ����] ��
			}
			printf("�α��ο� �����߽��ϴ�.\n");
			printf("%d�� �ݰ����ϴ�.\n", success_id_num);
			//[�α��� ����] ��
		}
	} while (select != 5);

	printf("�����Ͻ� �޴��� �����ϱ��Դϴ�.\n\n");
	printf("�ý����� �����մϴ�. �̿����ּż� �����մϴ�.");
	//[�޴� ����] ��
	return 0;
}



int cancel(int s[3][5], char row, int col, int id)
{
	//[�������� row�� ������ ��ȯ���ֱ� ���� ����] ����
	char abc[3] = { 'A', 'B', 'C' };
	int index = 0;
	for (; index < 3; index++) //char�� row�� ������ ��ȯ 
	{
		if (abc[index] == row)
			break;
	}
	//[�������� row�� ������ ��ȯ���ֱ� ���� ����] ��

	if (s[index][col] == id)
	{
		s[index][col] = 0; //���� ���
		printf("���� ��Ұ� �Ϸ�Ǿ����ϴ�.\n");
		//[���� ���� ����] ����
		FILE* fp;
		if ((fp = fopen("reservation_data.txt", "w")) == NULL)
		{
			fprintf(stderr, "���� %s�� �� �� �����ϴ�.\n", "reservation_data.txt");
			return -1;
		}
		for (int i = 0; i < 3; i++)
		{
			fprintf(fp, "%d %d %d %d %d", &s[i][0], &s[i][1], &s[i][2], &s[i][3], &s[i][4]);
			fprintf(fp, "\n");
		}
		fclose(fp);
		//[���� ���� ����] ��

		return 1;
	}
	else if (s[index][col] != 0)
	{
		// ���� �Ұ� ��Ȳ (1) : ����� ���̵� ������ ���̵�� ��ġ���� ���� 
		printf("�ٸ� ����ڰ� ������ �ڸ��Դϴ�.\n");
		printf("������ ����� �� �����ϴ�.\n");
		printf("���� ��Ҹ� �����߽��ϴ�.\n");
		return -1;
	}
	else
	{
		//���� �Ұ� ��Ȳ (2) : ����Ǿ� ���� ���� �¼��� ������ ��Ȳ
		printf("����Ǿ� ���� ���� �¼��Դϴ�.\n");
		printf("���� ��Ҹ� �����߽��ϴ�.\n");
		return -1;
	}

}


int load_reservation_info(int s[3][5])
{
	FILE* fp;
	if ((fp = fopen("reservation_data.txt", "r")) == NULL)
	{
		fprintf(stderr, "���� %s�� �� �� �����ϴ�.\n", "reservation_data.txt");
		return -1;
	}

	for (int i = 0; i < 3; i++)
		fscanf(fp, "%d %d %d %d %d", &s[i][0], &s[i][1], &s[i][2], &s[i][3], &s[i][4]);
	fclose(fp);
	return 0; //���ε� ���� 
}
int reserve(int s[3][5], char row, int col, int id)
{
	//[�������� row�� ������ ��ȯ���ֱ� ���� ����] ����
	char abc[3] = { 'A', 'B', 'C' };
	int index = 0;
	for (; index < 3; index++) //char�� row�� ������ ��ȯ 
	{
		if (abc[index] == row) //row�� ��ġ�ϴ� ���� �迭���� ã�� ���
			break;
	}
	//[�������� row�� ������ ��ȯ���ֱ� ���� ����] ��

	if (s[index][col] == 0) //����Ǿ� ���� ���� �ڸ��� ��� 
	{
		s[index][col] = id; //����
		printf("������ �Ϸ�Ǿ����ϴ�.\n");

		//[���� ���� ����] ����
		FILE* fp;
		if ((fp = fopen("reservation_data.txt", "w")) == NULL)
		{
			fprintf(stderr, "���� %s�� �� �� �����ϴ�.\n", "reservation_data.txt");
			return -1;
		}
		for (int i = 0; i < 3; i++)
		{
			fprintf(fp, "%d %d %d %d %d", &s[i][0], &s[i][1], &s[i][2], &s[i][3], &s[i][4]);
			fprintf(fp, "\n");
		}
		fclose(fp);
		//[���� ���� ����] ��

		return 1; //���� ����
	}
	else
	{
		printf("������ �Ұ����� �¼��Դϴ�. \n");
		printf("������ �����Ͽ����ϴ�.\n");
		return -1;
	}
}
void print_seats(int s[3][5])
{
	printf(" |0 1 2 3 4 \n");
	printf("--------------\n");
	char abc[3] = { 'A', 'B', 'C' };
	for (int row = 0; row < 3; row++)
	{
		printf("%c|", abc[row]);
		for (int col = 0; col < 5; col++)
		{
			printf("%d ", s[row][col]);
		}
		printf("\n");
	}

}
int check_login(struct user_info arr[USER_NUM], char check_id[10], char check_pw[10])
{
	//1. id�� arr[i].id�� ��ġ�� ���� �ִ��� �˻� > binary search ���
	//  > ��Ī�ϴ� ���� ������ return -1; // �ش� ���̵� ����, �Լ� ����
	// 2. ��Ī�ϴ°��� ����> user[i].password �� check_pw�� ��ġ�ϴ��� Ȯ��
	//  > ��Ī�ϴ� ���� ������ return -2;
	//  > ��Ī�ϴ� ���� ������ return user[i].id_num;
	//�����ϸ� id_num��ȯ
	if (binary_search_id(arr, check_id) == -1) // Ž�� ����, id�� ����
		return -1;
	else //Ž�� ����, id ������ 
	{
		int index = binary_search_id(arr, check_id);
		if (strcmp(arr[index].password, check_pw) == 0)
			return arr[index].id_num; //�α��� ����
		else
			return -2; //pw�� ���� �α��� ���� 
	}


}
int binary_search_id(struct user_info arr[USER_NUM], char key_id[10])
{
	int low, high, middle;
	low = 0;
	high = USER_NUM - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (strcmp(key_id, arr[middle].id) == 0)
			return middle; //Ž�� ����
		else if (strcmp(key_id, arr[middle].id) > 0)
			low = middle + 1;
		else
			high = middle - 1;
	}

	return -1; //Ž�� ���� 
}
int load_user_info(struct user_info arr[USER_NUM])
{
	// 1. ������ ���ε� (���� ���� ���н� return -1)
	FILE* fp;
	if ((fp = fopen("user_data.txt", "r")) == NULL)
	{
		fprintf(stderr, "���� ���� %s�� �� �� �����ϴ�.\n", "user_data.txt");
		return -1;
	}

	// 2. for loop���� (���� ������) struct �迭�� �Է�, ���ε� �ϱ� 
	for (int i = 0; i < USER_NUM; i++)
	{
		fscanf(fp, "%d %s %s", &arr[i].id_num, arr[i].id, arr[i].password); // ���� ������ struct �迭�� ���ε�
	}
	fclose(fp);

	// 3. selection sort
	int i, j, least;
	struct user_info temp[1];
	for (i = 0; i < USER_NUM - 1; i++)
	{
		least = i; //ù ������ i�� ���� ���� ��Ȳ��. i�� ���� �տ� ���� ���� !! 
		for (j = i + 1; j < USER_NUM; j++)
			if (arr[j].id_num < arr[least].id_num)
				least = j;

		// ��ȯ ����
		temp[0] = arr[i];
		arr[i] = arr[least];
		arr[least] = temp[0]; //�̰� ���� ������ ? 
	}

	// 4. �迭 ���ε� �� ���� ����
	return USER_NUM;
}