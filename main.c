#include "abk.h"

int main() {
    int choice;

    while (1) {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_contact(); break;
            case 2: view_contacts(); break;
            case 3: search_contact(); break;
            case 4: edit_contact(); break;
            case 5: delete_contact(); break;
            case 6:
                printf("Exiting Address Book...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
 
