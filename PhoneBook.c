#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[50];
    char phone[15];
    struct Node *prev, *next;
} Node;

Node *head = NULL; 

Node* createNode(char *name, char *phone) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void addContact(char *name, char *phone) {
    Node *newNode = createNode(name, phone);
    if (!head) {
        head = newNode;
        return;
    }

    Node *temp = head;
    while (temp->next && strcmp(temp->name, name) < 0)
        temp = temp->next;

    if (strcmp(temp->name, name) > 0) {
        newNode->next = temp;
        newNode->prev = temp->prev;

        if (temp->prev)
            temp->prev->next = newNode;
        else
            head = newNode;

        temp->prev = newNode;
    } else {
        newNode->prev = temp;
        newNode->next = temp->next;

        if (temp->next)
            temp->next->prev = newNode;

        temp->next = newNode;
    }
}


void deleteContact(char *name) {
    Node *temp = head;

    while (temp && strcmp(temp->name, name) != 0)
        temp = temp->next;

    if (!temp) {
        printf("Contact not found!\n");
        return;
    }

    if (temp->prev)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next)
        temp->next->prev = temp->prev;

    free(temp);
    printf("Contact deleted successfully!\n");
}


void searchContact(char *name) {
    Node *temp = head;

    while (temp) {
        if (strstr(temp->name, name)) {
            printf("Name: %s, Phone: %s\n", temp->name, temp->phone);
        }
        temp = temp->next;
    }
}

void displayContacts() {
    Node *temp = head;
    printf("Contacts:\n");
    while (temp) {
        printf("Name: %s, Phone: %s\n", temp->name, temp->phone);
        temp = temp->next;
    }
}


int main() {
    int choice;
    char name[50], phone[15];

    do {
        printf("\nPhone Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Phone: ");
                scanf("%s", phone);
                addContact(name, phone);
                break;
            case 2:
                printf("Enter Name to Delete: ");
                scanf("%s", name);
                deleteContact(name);
                break;
            case 3:
                printf("Enter Name to Search: ");
                scanf("%s", name);
                searchContact(name);
                break;
            case 4:
                displayContacts();
                break;
            case 5:
                printf("Exiting Phone Book.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
