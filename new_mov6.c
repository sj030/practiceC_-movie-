#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> //이거 필요하나 ? 
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
	load_user_info(user); // 회원 정보 업로드
	char input_id[10], input_pw[10]; //입력받을 id와 pw 변수

	//[로그인 구간] 시작
	int success_id_num;
	printf("반갑습니다. 로그인을 해주세요.\n");
	while (1)
	{
		//[id, pw 입력 구간] 시작 

		printf("id :");
		scanf("%s", input_id);
		printf("pw :");
		scanf("%s", input_pw);
		//[id, pw 입력 구간] 끝

		//[로그인 성공 검사 구간] 시작
		if (check_login(user, input_id, input_pw) == -1) //아이디 불일치로 인한 로그인 실패 
		{
			printf("아이디가 올바르지 않습니다.\n");
			printf("로그인을 실패했습니다. 다시 로그인 해주십시오.\n");
		}
		else if (check_login(user, input_id, input_pw) == -2) //비밀번호 불일치로 인한 로그인 실패 
		{
			printf("비밀번호가 올바르지 않습니다.\n");
			printf("로그인을 실패했습니다. 다시 로그인 해주십시오.\n");
		}
		else// 로그인 성공
		{
			success_id_num = check_login(user, input_id, input_pw);
			break;
		}
		//[로그인 성공 검사 구간] 끝
	}
	printf("로그인에 성공했습니다.\n");
	printf("%d님 반갑습니다.\n", success_id_num);
	//[로그인 구간] 끝

	//[메뉴 구간] 시작
	int seats[3][5] = { 0, }; // 배열 0으로 초기화 
	load_reservation_info(seats); // 기존 예약 정보 불러오기 

	int select;
	do {
		printf("1--좌석확인하기\n");
		printf("2--예약하기\n");
		printf("3--예약취소하기\n");
		printf("4--다른 사용자로 로그인하기\n");
		printf("5--종료하기\n");
		printf("메뉴를 선택하시오:");
		scanf("%d", &select);

		if (select == 1)
		{
			printf("선택된 메뉴는 좌석확인하기입니다.\n\n");
			print_seats(seats);
		}
		else if (select == 2)
		{
			printf("선택하신 메뉴는 예약하기입니다.\n\n");
			char reserve_r;
			int reserve_c;
			printf("예약을 원하는 자리는(예-A2)?");
			int c;
			while (((c = getchar()) != '\n') && (c != EOF)) {};
			scanf("%c%d", &reserve_r, &reserve_c);
			reserve(seats, reserve_r, reserve_c, success_id_num);
			print_seats(seats);
		}
		else if (select == 3)
		{
			printf("선택하신 메뉴는 예약 취소하기입니다.\n\n");
			char cancel_r;
			int cancel_c;
			printf("예약을 원하는 자리는(예-A2)?");
			int c;
			while (((c = getchar()) != '\n') && (c != EOF)) {};
			scanf("%c%d", &cancel_r, &cancel_c);
			cancel(seats, cancel_r, cancel_c, success_id_num);
			print_seats(seats);
		}
		else if (select == 4)
		{
			printf("선택하신 메뉴는 다른 사용자로 로그인하기입니다.\n");
			printf("다시 로그인을 해주십시오.\n");
			while (1)
			{
				//[로그인 구간] 시작 (복사 한거임)
				printf("id :");
				scanf("%s", input_id);
				printf("pw :");
				scanf("%s", input_pw);
				//[id, pw 입력 구간] 끝

				//[로그인 성공 검사 구간] 시작
				if (check_login(user, input_id, input_pw) == -1) //아이디 불일치로 인한 로그인 실패 
				{
					printf("아이디가 올바르지 않습니다.\n");
					printf("로그인을 실패했습니다. 다시 로그인 해주십시오.\n");
				}
				else if (check_login(user, input_id, input_pw) == -2) //비밀번호 불일치로 인한 로그인 실패 
				{
					printf("비밀번호가 올바르지 않습니다.\n");
					printf("로그인을 실패했습니다. 다시 로그인 해주십시오.\n");
				}
				else// 로그인 성공
				{
					success_id_num = check_login(user, input_id, input_pw);
					break;
				}
				//[로그인 성공 검사 구간] 끝
			}
			printf("로그인에 성공했습니다.\n");
			printf("%d님 반갑습니다.\n", success_id_num);
			//[로그인 구간] 끝
		}
	} while (select != 5);

	printf("선택하신 메뉴는 예약하기입니다.\n\n");
	printf("시스템을 종료합니다. 이용해주셔서 감사합니다.");
	//[메뉴 구간] 끝
	return 0;
}



int cancel(int s[3][5], char row, int col, int id)
{
	//[문자형인 row를 정수로 변환해주기 위한 과정] 시작
	char abc[3] = { 'A', 'B', 'C' };
	int index = 0;
	for (; index < 3; index++) //char인 row를 정수로 변환 
	{
		if (abc[index] == row)
			break;
	}
	//[문자형인 row를 정수로 변환해주기 위한 과정] 끝

	if (s[index][col] == id)
	{
		s[index][col] = 0; //예약 취소
		printf("예약 취소가 완료되었습니다.\n");
		//[파일 저장 구간] 시작
		FILE* fp;
		if ((fp = fopen("reservation_data.txt", "w")) == NULL)
		{
			fprintf(stderr, "파일 %s를 열 수 없습니다.\n", "reservation_data.txt");
			return -1;
		}
		for (int i = 0; i < 3; i++)
		{
			fprintf(fp, "%d %d %d %d %d", &s[i][0], &s[i][1], &s[i][2], &s[i][3], &s[i][4]);
			fprintf(fp, "\n");
		}
		fclose(fp);
		//[파일 저장 구간] 끝

		return 1;
	}
	else if (s[index][col] != 0)
	{
		// 예약 불가 상황 (1) : 예약된 아이디가 현재의 아이디와 일치하지 않음 
		printf("다른 사용자가 예약한 자리입니다.\n");
		printf("예약을 취소할 수 없습니다.\n");
		printf("예약 취소를 실패했습니다.\n");
		return -1;
	}
	else
	{
		//예약 불가 상황 (2) : 예약되어 있지 않은 좌석을 선택한 상황
		printf("예약되어 있지 않은 좌석입니다.\n");
		printf("예약 취소를 실패했습니다.\n");
		return -1;
	}

}


int load_reservation_info(int s[3][5])
{
	FILE* fp;
	if ((fp = fopen("reservation_data.txt", "r")) == NULL)
	{
		fprintf(stderr, "파일 %s를 열 수 없습니다.\n", "reservation_data.txt");
		return -1;
	}

	for (int i = 0; i < 3; i++)
		fscanf(fp, "%d %d %d %d %d", &s[i][0], &s[i][1], &s[i][2], &s[i][3], &s[i][4]);
	fclose(fp);
	return 0; //업로드 성공 
}
int reserve(int s[3][5], char row, int col, int id)
{
	//[문자형인 row를 정수로 변환해주기 위한 과정] 시작
	char abc[3] = { 'A', 'B', 'C' };
	int index = 0;
	for (; index < 3; index++) //char인 row를 정수로 변환 
	{
		if (abc[index] == row) //row와 일치하는 값을 배열에서 찾은 경우
			break;
	}
	//[문자형인 row를 정수로 변환해주기 위한 과정] 끝

	if (s[index][col] == 0) //예약되어 있지 않은 자리인 경우 
	{
		s[index][col] = id; //예약
		printf("예약이 완료되었습니다.\n");

		//[파일 저장 과정] 시작
		FILE* fp;
		if ((fp = fopen("reservation_data.txt", "w")) == NULL)
		{
			fprintf(stderr, "파일 %s를 열 수 없습니다.\n", "reservation_data.txt");
			return -1;
		}
		for (int i = 0; i < 3; i++)
		{
			fprintf(fp, "%d %d %d %d %d", &s[i][0], &s[i][1], &s[i][2], &s[i][3], &s[i][4]);
			fprintf(fp, "\n");
		}
		fclose(fp);
		//[파일 저장 과정] 끝

		return 1; //예약 성공
	}
	else
	{
		printf("예약이 불가능한 좌석입니다. \n");
		printf("예약을 실패하였습니다.\n");
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
	//1. id가 arr[i].id와 일치한 것이 있는지 검사 > binary search 사용
	//  > 매칭하는 것이 없으면 return -1; // 해당 아이디가 없음, 함수 종료
	// 2. 매칭하는것이 있음> user[i].password 와 check_pw가 일치하는지 확인
	//  > 매칭하는 것이 없으면 return -2;
	//  > 매칭하는 것이 있으면 return user[i].id_num;
	//성공하면 id_num반환
	if (binary_search_id(arr, check_id) == -1) // 탐색 실패, id가 없음
		return -1;
	else //탐색 성공, id 존재함 
	{
		int index = binary_search_id(arr, check_id);
		if (strcmp(arr[index].password, check_pw) == 0)
			return arr[index].id_num; //로그인 성공
		else
			return -2; //pw로 인한 로그인 실패 
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
			return middle; //탐색 성공
		else if (strcmp(key_id, arr[middle].id) > 0)
			low = middle + 1;
		else
			high = middle - 1;
	}

	return -1; //탐색 실패 
}
int load_user_info(struct user_info arr[USER_NUM])
{
	// 1. 파일을 업로드 (파일 오픈 실패시 return -1)
	FILE* fp;
	if ((fp = fopen("user_data.txt", "r")) == NULL)
	{
		fprintf(stderr, "성적 파일 %s를 열 수 없습니다.\n", "user_data.txt");
		return -1;
	}

	// 2. for loop으로 (파일 내용을) struct 배열에 입력, 업로드 하기 
	for (int i = 0; i < USER_NUM; i++)
	{
		fscanf(fp, "%d %s %s", &arr[i].id_num, arr[i].id, arr[i].password); // 파일 내용을 struct 배열에 업로드
	}
	fclose(fp);

	// 3. selection sort
	int i, j, least;
	struct user_info temp[1];
	for (i = 0; i < USER_NUM - 1; i++)
	{
		least = i; //첫 시작은 i가 제일 작은 상황임. i가 제일 앞에 있을 것임 !! 
		for (j = i + 1; j < USER_NUM; j++)
			if (arr[j].id_num < arr[least].id_num)
				least = j;

		// 교환 과정
		temp[0] = arr[i];
		arr[i] = arr[least];
		arr[least] = temp[0]; //이게 과연 맞을까 ? 
	}

	// 4. 배열 업로드 및 정렬 성공
	return USER_NUM;
}