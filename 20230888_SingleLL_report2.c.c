#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 연락처 노드 구조체 정의
typedef struct Contact {
    char name[30];              // 이름
    char phone[30];             // 전화번호
    struct Contact* next;       // 다음 연락처 주소
} Contact;

// 연락처 추가 함수
Contact* addContact(Contact* head, char name[], char phone[]) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));

    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;

    if (head == NULL) {
        return newContact;
    }

    Contact* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newContact;
    return head;
}

// 연락처 검색 함수
void searchContact(Contact* head, char name[]) {
    if (head == NULL) {
        printf("전화번호부가 비어 있습니다.\n");
        return;
    }

    Contact* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("\n[검색 결과]\n");
            printf("이름: %s\n", current->name);
            printf("전화번호: %s\n", current->phone);
            return;
        }
        current = current->next;
    }

    printf("%s 연락처를 찾을 수 없습니다.\n", name);
}

// 연락처 삭제 함수
Contact* deleteContact(Contact* head, char name[]) {
    if (head == NULL) {
        printf("전화번호부가 비어 있습니다. 삭제할 연락처가 없습니다.\n");
        return NULL;
    }

    if (strcmp(head->name, name) == 0) {
        Contact* temp = head;
        head = head->next;
        free(temp);

        printf("%s 연락처가 삭제되었습니다.\n", name);
        return head;
    }

    Contact* current = head;

    while (current->next != NULL && strcmp(current->next->name, name) != 0) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("%s 연락처를 찾을 수 없습니다.\n", name);
        return head;
    }

    Contact* temp = current->next;
    current->next = current->next->next;
    free(temp);

    printf("%s 연락처가 삭제되었습니다.\n", name);
    return head;
}

// 전화번호부 전체 출력 함수
void printContacts(Contact* head) {
    if (head == NULL) {
        printf("전화번호부가 비어 있습니다.\n");
        return;
    }

    Contact* current = head;

    printf("\n===== 전화번호부 목록 =====\n");

    while (current != NULL) {
        printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
        current = current->next;
    }

    printf("==========================\n");
}

// 전체 메모리 해제 함수
void freeContacts(Contact* head) {
    Contact* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Contact* phoneBook = NULL;

    int choice;
    char name[30];
    char phone[30];

    while (1) {
        printf("\n===== 전화번호부 관리 프로그램 =====\n");
        printf("1. 연락처 추가\n");
        printf("2. 연락처 검색\n");
        printf("3. 연락처 삭제\n");
        printf("4. 전화번호부 출력\n");
        printf("0. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("이름 입력: ");
            scanf("%s", name);

            printf("전화번호 입력: ");
            scanf("%s", phone);

            phoneBook = addContact(phoneBook, name, phone);
            printf("연락처가 추가되었습니다.\n");
            break;

        case 2:
            printf("검색할 이름 입력: ");
            scanf("%s", name);

            searchContact(phoneBook, name);
            break;

        case 3:
            printf("삭제할 이름 입력: ");
            scanf("%s", name);

            phoneBook = deleteContact(phoneBook, name);
            break;

        case 4:
            printContacts(phoneBook);
            break;

        case 0:
            printf("프로그램을 종료합니다.\n");
            freeContacts(phoneBook);
            return 0;

        default:
            printf("잘못된 메뉴입니다. 다시 선택하세요.\n");
        }
    }
}